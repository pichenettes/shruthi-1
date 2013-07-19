// Copyright 2009 Olivier Gillet.
//
// Author: Olivier Gillet (ol.gillet@gmail.com)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// -----------------------------------------------------------------------------
//
// Main synthesis engine.

#include "shruthi/part.h"

#include <string.h>

#include "avrlib/op.h"
#include "avrlib/random.h"
#include "avrlib/resources_manager.h"

#include "shruthi/audio_out.h"
#include "shruthi/clock.h"
#include "shruthi/midi_dispatcher.h"
#include "shruthi/parameter.h"
#include "shruthi/storage.h"

using namespace avrlib;

namespace shruthi {

/* extern */
Part part;

/* <static> */
uint8_t Part::data_access_byte_[1];
Patch Part::patch_;
SequencerSettings Part::sequencer_settings_;
SystemSettings Part::system_settings_;
bool Part::dirty_;

Voice Part::voice_;
NoteStack Part::pressed_keys_;
NoteStack Part::mono_allocator_;
NoteStack Part::generated_notes_;
VoiceAllocator Part::poly_allocator_;
bool Part::release_latched_keys_on_next_note_on_;
bool Part::ignore_note_off_messages_;

Lfo Part::lfo_[kNumLfos];
uint8_t Part::previous_lfo_fm_[kNumLfos];

bool Part::arp_seq_running_;
uint8_t Part::arp_seq_prescaler_;
uint8_t Part::arp_seq_step_;
int8_t Part::arp_note_;
int8_t Part::arp_octave_;
int8_t Part::arp_direction_;
uint16_t Part::arp_seq_gate_length_counter_;
int8_t Part::swing_amount_;
uint8_t Part::internal_clock_blank_ticks_;
int8_t Part::seq_transposition_;
/* </static> */

/* static */
void Part::Init() {
  ResetPatch();
  ResetSequencerSettings();
  if (!system_settings_.EepromLoad()) {
    ResetSystemSettings();
    system_settings_.EepromSave();
  }
  Reset();
  pressed_keys_.Init();
  mono_allocator_.Init();
  poly_allocator_.Init();
  generated_notes_.Init();
  voice_.Init();
  dirty_ = false;
  arp_seq_running_ = false;
  clock.Update(120);
}

static const prog_char init_patch[] PROGMEM = {
    // Oscillators
    WAVEFORM_SAW, 0, 0, 0,
    WAVEFORM_NONE, 16, -12, 12,
    // Mixer
    32, 0, 0, WAVEFORM_SUB_OSC_SQUARE_1,
    // Filter
    96, 0, 32, 0,
    // ADSR
    0, 50, 20, 60,
    0, 40, 90, 30,
    // LFO
    LFO_WAVEFORM_TRIANGLE, 80, 0, 0,
    LFO_WAVEFORM_TRIANGLE, 3, 0, 0,
    // Routing
    MOD_SRC_LFO_1, MOD_DST_VCO_1, 0,
    MOD_SRC_ENV_1, MOD_DST_VCO_2, 0,
    MOD_SRC_ENV_1, MOD_DST_PWM_1, 0,
    MOD_SRC_LFO_1, MOD_DST_PWM_2, 0,
    MOD_SRC_LFO_2, MOD_DST_MIX_BALANCE, 0,
    MOD_SRC_SEQ, MOD_DST_MIX_BALANCE, 0,
    MOD_SRC_CV_1, MOD_DST_PWM_1, 0,
    MOD_SRC_CV_2, MOD_DST_PWM_2, 0,
    MOD_SRC_ENV_2, MOD_DST_VCA, 63,
    MOD_SRC_VELOCITY, MOD_DST_VCA, 16,
    MOD_SRC_PITCH_BEND, MOD_DST_VCO_1_2_COARSE, 32,
    MOD_SRC_LFO_1, MOD_DST_VCO_1_2_COARSE, 16,
    // Name
    'i', 'n', 'i', 't', ' ', ' ', ' ', ' ',
    // Performance page assignments.
    0, 0,
    0, 0,
    0, 0,
    0, 0,
    // Settings for second filter
    0, 0, 0, 
    0, 0, 0, 0,
    '!',
    0, 0, 0, 0, 0, 0, 0, 0,
};

static const prog_char init_sequence[] PROGMEM = {
    // Sequencer
    SEQUENCER_MODE_SEQ, 120, 0, 0,
    ARPEGGIO_DIRECTION_UP, 1, 0, 7,
    
    // Pattern size and pattern
    16,
    0,
    0x80 | 48, 0x00 | 0x70 | 0x0,
    0x80 | 48, 0x80 | 0x50 | 0x0,
    0x80 | 60, 0x00 | 0x50 | 0x0,
    0x80 | 60, 0x80 | 0x50 | 0x0,

    0x80 | 48, 0x00 | 0x70 | 0xf,
    0x80 | 48, 0x80 | 0x50 | 0xf,
    0x80 | 60, 0x00 | 0x50 | 0xf,
    0x00 | 60, 0x00 | 0x50 | 0xf,

    0x80 | 48, 0x00 | 0x70 | 0xc,
    0x80 | 48, 0x80 | 0x50 | 0xc,
    0x80 | 60, 0x00 | 0x50 | 0xc,
    0x80 | 60, 0x80 | 0x50 | 0xc,

    0x80 | 48, 0x00 | 0x70 | 0x4,
    0x00 | 48, 0x00 | 0x50 | 0x4,
    0x80 | 60, 0x00 | 0x70 | 0x4,
    0x00 | 60, 0x00 | 0x50 | 0x4,
};

static const prog_char init_system_settings[] PROGMEM = {
    // System Settings,
    0, 0, 0, 0,
    0, 1, 1, 5,
    8, 0, 0, 0,
    0, 0, 0,
};

/* static */
void Part::ResetPatch() {
  ResourcesManager::Load(init_patch, 0, &patch_);
  Touch(true);
}

/* static */
void Part::Touch(bool cascade) {
  UpdateModulationRates();
  dirty_ = true;
  if (cascade) {
    if (system_settings_.midi_out_mode >= MIDI_OUT_2_1) {
      Storage::SysExDump(&patch_);
    }
  }
}

/* static */
void Part::ResetSequencerSettings() {
  ResourcesManager::Load(init_sequence, 0, &sequencer_settings_);
}

/* static */
void Part::ResetSequence() {
  ResourcesManager::Load(init_sequence + 10, 0, &sequencer_settings_.steps);
  sequencer_settings_.pattern_size = 16;
}

/* static */
void Part::ResetSystemSettings() {
  ResourcesManager::Load(init_system_settings, 0, &system_settings_);
}

/* static */
void Part::NoteOn(uint8_t channel, uint8_t note, uint8_t velocity) {
  if (!velocity) {
    NoteOff(channel, note);
    return;
  }
  
  if (release_latched_keys_on_next_note_on_) {
    bool still_latched = ignore_note_off_messages_;
    
    // Releasing all latched key will generate "fake" NoteOff messages. We
    // should note ignore them.
    ignore_note_off_messages_ = false;
    ReleaseLatchedNotes();
    
    release_latched_keys_on_next_note_on_ = still_latched;
    ignore_note_off_messages_ = still_latched;
  }
  
  pressed_keys_.NoteOn(note, velocity);
  
  if (!running() && sequencer_settings_.internal_clock()) {
    Start(true);
    Clock(true);
  }
  
  if (sequencer_settings_.mode() == SEQUENCER_MODE_STEP || !running()) {
    InternalNoteOn(note, velocity);
  }
}

/* static */
void Part::NoteOff(uint8_t channel, uint8_t note) {
  if (ignore_note_off_messages_) {
    for (uint8_t i = 1; i <= pressed_keys_.max_size(); ++i) {
      // Flag the note so that it is removed once the sustain pedal is released.
      NoteEntry* e = pressed_keys_.mutable_note(i);
      if (e->note == note && e->velocity) {
        e->velocity |= 0x80;
      }
    }
  } else {
    pressed_keys_.NoteOff(note);
    if (sequencer_settings_.mode() == SEQUENCER_MODE_STEP || !running()) {
      InternalNoteOff(note);
    }
  }
}

/* static */
void Part::ControlChange(uint8_t channel, uint8_t controller,
                                    uint8_t value) {
  /*uint8_t editing_controller = 0;
  if (controller >= midi::kAssignableCcA &&
      controller <= midi::kAssignableCcD) {
    set_modulation_source(MOD_SRC_CC_A + controller -
        midi::kAssignableCcA, value << 1);
  } else if (controller >= 20 && controller <= 31) {
    controller -= 20;  // CCs for oscillators and mixer.
    editing_controller = 1;
  } else if (controller >= 14 && controller <= 15) {
    controller -= 2; // CCs for Cutoff and resonance.
    editing_controller = 1;
  } else if (controller >= 12 && controller <= 13) {
    controller = controller - 12 + 70;  // CCs for cutoff2 and resonance2.
    editing_controller = 1;
  } else if (controller >= 102 && controller <= 119) {
    // CCs for filter mods, envelopes and LFOs.
    controller = controller - 102 + 14;
    editing_controller = 1;
  } else {
    switch (controller) {
      case midi::kModulationWheelMsb:
        set_modulation_source(MOD_SRC_WHEEL, value << 1);
        break;
      case midi::kModulationWheelJoystickMsb:
        break;
      case midi::kDataEntryMsb:
        data_entry_msb_ = value << 7;
        break;
      case midi::kVolume:
        volume_ = value << 1;
        break;
      case midi::kDataEntryLsb:
      case midi::kDataIncrement:
      case midi::kDataDecrement:
        value |= data_entry_msb_;
        if (nrpn_parameter_number_ != 255) {
          dirty_ = 1;
          // Finds the parameter definition id matching this parameter id.
          uint8_t parameter_definition_id = \
              ParameterDefinitions::MemoryOffsetToId(nrpn_parameter_number_);
          const ParameterDefinition& p = (
              ParameterDefinitions::parameter_definition(
                  parameter_definition_id));
          if (controller == midi::kDataEntryLsb) {
            if (p.unit == UNIT_INT8) {
              int8_t signed_value = static_cast<int8_t>(value);
              if (signed_value >= static_cast<int8_t>(p.min_value) &&
                  signed_value <= static_cast<int8_t>(p.max_value)) {
                SetParameter(nrpn_parameter_number_, value, 0);
              }
            } else {
              if (value >= p.min_value && value <= p.max_value) {
                SetParameter(nrpn_parameter_number_, value, 0);
              }
            }
          } else {
            uint8_t old_value = GetParameter(nrpn_parameter_number_);
            uint8_t new_value = ParameterDefinitions::Increment(
                p,
                old_value,
                controller == midi::kDataIncrement ? 1 : -1);
            if (new_value != old_value) {
              SetParameter(nrpn_parameter_number_, new_value, 0);
            }
          }
        }
        break;
      case midi::kHoldPedal:
        if (value >= 64) {
          ignore_note_off_messages_ = 1;
        } else {
          ignore_note_off_messages_ = 0;
          controller_.AllNotesOff();
        }
        break;
      case midi::kPortamentoTimeMsb:
        system_settings_.portamento = value;
        break;
      case midi::kRelease:
        SetParameter(PRM_ENV_RELEASE_2, value, 0);
        break;
      case midi::kAttack:
        SetParameter(PRM_ENV_ATTACK_2, value, 0);
        break;
      case midi::kHarmonicIntensity:
        patch_.filter_resonance = value >> 1;
        break;
      case midi::kBrightness + 16:
        patch_.filter_cutoff_2 = value;
        break;
      case midi::kHarmonicIntensity + 16:
        patch_.filter_resonance_2 = value >> 1;
        break;
      case midi::kBrightness:
        patch_.filter_cutoff = value;
        break;
      case midi::kNrpnLsb:
        nrpn_parameter_number_ = value | nrpn_parameter_number_msb_;
        nrpn_parameter_number_msb_ = 0;
        data_entry_msb_ = 0;
        break;
      case midi::kNrpnMsb:
        nrpn_parameter_number_msb_ = value << 7;
        data_entry_msb_ = 0;
        break;
    }
  }
  if (editing_controller) {
    SetScaledParameter(controller, value, 0);
  }*/
}

/* static */
void Part::AllSoundOff(uint8_t channel) {
  AllNotesOff();
}

/* static */
void Part::AllNotesOff(uint8_t channel) {
  AllNotesOff();
}

/* static */
void Part::ResetAllControllers(uint8_t channel) {
  ignore_note_off_messages_ = false;
  voice_.ResetAllControllers();
}

// When in Omni mode, disable Omni and enable reception only on the channel on
// which this message has been received.
/* static */
void Part::OmniModeOff(uint8_t channel) {
  system_settings_.midi_channel = channel + 1;
}

// Enable Omni mode.
/* static */
void Part::OmniModeOn(uint8_t channel) {
  system_settings_.midi_channel = 0;
}

/* static */
void Part::Reset() {
  ResetAllControllers(0);
  for (uint8_t i = 0; i < kNumLfos; ++i) {
    lfo_[i].Reset();
  }
  AllNotesOff();
}

/* static */
void Part::Clock(bool internal) {
  if (internal) {
    midi_dispatcher.OnClock();
    if (!pressed_keys_.size()) {
      ++internal_clock_blank_ticks_;
      if (internal_clock_blank_ticks_ >= 12) {
        Stop(true);
        return;
      }
    } else {
      internal_clock_blank_ticks_ = 0;
    }
  }
  if (!arp_seq_prescaler_) {
    ClockArpeggiator();
    ClockSequencer();
  }
  if (!arp_seq_gate_length_counter_ && generated_notes_.size()) {
    StopSequencerArpeggiatorNotes();
  } else {
    --arp_seq_gate_length_counter_;
  }
  ++arp_seq_prescaler_;
  if (arp_seq_prescaler_ >= step_duration()) {
    arp_seq_prescaler_ = 0;
  }
}
/* static */
void Part::Start(bool internal) {
  if (internal) {
    midi_dispatcher.OnStart();
  }
  
  poly_allocator_.Clear();
  mono_allocator_.Clear();
  voice_.NoteOff();
  release_latched_keys_on_next_note_on_ = false;
  ignore_note_off_messages_ = false;
  
  arp_seq_prescaler_ = 0;
  arp_seq_step_ = 0;
  arp_seq_running_ = true;
  seq_transposition_ = 0;
  if (sequencer_settings_.arp_direction == ARPEGGIO_DIRECTION_DOWN) {
    arp_note_ = pressed_keys_.size() - 1;
    arp_octave_ = sequencer_settings_.arp_range - 1;
    arp_direction_ = -1;
  } else {
    arp_note_ = 0;
    arp_octave_ = 0;
    arp_direction_ = 1;
  }
  generated_notes_.Clear();
}

/* static */
void Part::Stop(bool internal) {
  arp_seq_running_ = false;
  StopSequencerArpeggiatorNotes();
  AllNotesOff();
  if (internal) {
    midi_dispatcher.OnStop();
  }
}


/* static */
void Part::ClockArpeggiator() {
  uint16_t pattern_mask = 1 << arp_seq_step_;
  uint16_t pattern = ResourcesManager::Lookup<uint16_t, uint8_t>(
        lut_res_arpeggiator_patterns,
        sequencer_settings_.arp_pattern);
  voice_.set_modulation_source(MOD_SRC_STEP, pattern_mask & pattern ? 255 : 0);

  uint8_t num_notes = pressed_keys_.size();
  if (sequencer_settings_.mode() == SEQUENCER_MODE_ARP && 
      (pattern_mask & pattern) && num_notes) {
    // Update arepggiator note/octave counter.
    if (num_notes == 1 && sequencer_settings_.arp_range == 1) {
      // This is a corner case for the Up/down pattern code.
      // Get it out of the way.
      arp_note_ = 0;
      arp_octave_ = 0;
    } else {
      if (sequencer_settings_.arp_direction == ARPEGGIO_DIRECTION_RANDOM) {
        uint8_t random_byte = Random::state_msb();
        arp_octave_ = random_byte & 0xf;
        arp_note_ = (random_byte & 0xf0) >> 4;
        while (arp_octave_ >= sequencer_settings_.arp_range) {
          arp_octave_ -= sequencer_settings_.arp_range;
        }
        while (arp_note_ >= num_notes) {
          arp_note_ -= num_notes;
        }
      } else {
        bool wrapped = true;
        while (wrapped) {
          if (arp_note_ >= num_notes || arp_note_ < 0) {
            arp_octave_ += arp_direction_;
            arp_note_ = arp_direction_ > 0 ? 0 : num_notes - 1;
          }
          wrapped = false;
          if (arp_octave_ >= sequencer_settings_.arp_range || arp_octave_ < 0) {
            arp_octave_ = arp_direction_ > 0
                ? 0
                : sequencer_settings_.arp_range - 1;
            if (sequencer_settings_.arp_direction == \
                ARPEGGIO_DIRECTION_UP_DOWN) {
              arp_direction_ = -arp_direction_;
              arp_note_ = arp_direction_ > 0 ? 1 : num_notes - 2;
              arp_octave_ = arp_direction_ > 0
                  ? 0
                  : sequencer_settings_.arp_range - 1;
              wrapped = true;
            }
          }
        }
      }
    }

    // Kill pending notes (if any).
    StopSequencerArpeggiatorNotes();
    const NoteEntry* arpeggio_note = \
      sequencer_settings_.arp_direction == ARPEGGIO_DIRECTION_PLAYED ?
      &pressed_keys_.played_note(arp_note_) :
      &pressed_keys_.sorted_note(arp_note_);
    uint8_t note = arpeggio_note->note;
    uint8_t velocity = arpeggio_note->velocity & 0x7f;
    note += 12 * arp_octave_;
    while (note > 127) {
      note -= 12;
    }
    generated_notes_.NoteOn(note, velocity);
    InternalNoteOn(note, velocity);
    arp_note_ += arp_direction_;
    arp_seq_gate_length_counter_ = (step_duration() >> 1) + 1;
  }
}

/* static */
void Part::ClockSequencer() {
  uint8_t n = (arp_seq_step_ + sequencer_settings_.pattern_rotation) & 0x0f;
  voice_.set_modulation_source(
      MOD_SRC_SEQ,
      sequencer_settings_.steps[n].controller() << 4);
  n &= 0x7;
  voice_.set_modulation_source(
      MOD_SRC_SEQ_1,
      sequencer_settings_.steps[n].controller() << 4);
  voice_.set_modulation_source(
      MOD_SRC_SEQ_2,
      sequencer_settings_.steps[n + 8].controller() << 4);
  
  if (sequencer_settings_.mode() == SEQUENCER_MODE_SEQ) {
    SequenceStep& step = sequencer_settings_.steps[n];
    if (step.gate()) {
      int8_t transposition = pressed_keys_.size() ?
          pressed_keys_.most_recent_note().note - 60 : seq_transposition_;
      seq_transposition_ = transposition;
      int8_t note = step.note() + transposition;
      while (note < 0) note += 12;
      while (note > 127)  note -= 12;
      if (!step.legato()) {
        StopSequencerArpeggiatorNotes();
        InternalNoteOn(note, step.velocity());
      } else {
        if (generated_notes_.most_recent_note().note != note) {
          InternalNoteOn(note, step.velocity());
          StopSequencerArpeggiatorNotes();
        }
      }
      generated_notes_.NoteOn(note, step.velocity());
      arp_seq_gate_length_counter_ = (step_duration() >> 1) + 1;
    }
  }
  ++arp_seq_step_;
  if (arp_seq_step_ >= sequencer_settings_.pattern_size) {
    arp_seq_step_ = 0;
  }
  if (sequencer_settings_.mode() == SEQUENCER_MODE_SEQ) {
    n = (arp_seq_step_ + sequencer_settings_.pattern_rotation) & 0x0f;
    if (sequencer_settings_.steps[n].legato()) {
      arp_seq_gate_length_counter_ += step_duration();
    }
  }
}

/* static */
void Part::SetName(uint8_t* name) {
  memcpy(patch_.name, name, kPatchNameSize);
  dirty_ = true;
}

/* static */
void Part::SetSequenceStep(
    uint8_t step,
    uint8_t data_a,
    uint8_t data_b) {
  if (step >= kNumSteps) {
    return;
  }
  sequencer_settings_.steps[step].set_raw(data_a, data_b);
  // controller_.TouchSequence();
  dirty_ = true;
}

/* static */
void Part::SetPatternRotation(uint8_t rotation) {
  sequencer_settings_.pattern_rotation = rotation;
  // controller_.TouchSequence();
  dirty_ = true;
}

/* static */
void Part::SetPatternLength(uint8_t length) {
  sequencer_settings_.pattern_size = length & 0xf;
  // controller_.TouchSequence();
  dirty_ = true;
}

/* static */
void Part::SetScaledParameter(
    uint8_t parameter_index,
    uint8_t value,
    bool user_initiated) {
  dirty_ = true;
  const Parameter& parameter = parameter_manager.parameter(parameter_index);
  SetParameter(parameter.offset, parameter.Scale(value), user_initiated);
}

/* static */
void Part::SetParameter(
    uint8_t offset,
    uint8_t value,
    bool user_initiated) {
  if (data_access_byte_[offset + 1] == value) {
    return;
  }
  data_access_byte_[offset + 1] = value;
  if (offset >= PRM_ENV_ATTACK_1 && offset <= PRM_LFO_RETRIGGER_2) {
    UpdateModulationRates();
  } else if (offset == PRM_ARP_DIRECTION) {
    arp_direction_ = \
        sequencer_settings_.arp_direction == ARPEGGIO_DIRECTION_DOWN ? -1 : 1;
  }
  if (user_initiated) {
    midi_dispatcher.OnEdit(offset, value);
  }
}

/* static */
void Part::UpdateModulationRates() {
  // Update the LFO increments.
  for (uint8_t i = 0; i < kNumLfos; ++i) {
    /*if (patch_.lfo[i].rate < 16) {
      num_lfo_reset_steps_ = U8U8Mul(
          num_lfo_reset_steps_ ? num_lfo_reset_steps_ : 1,
          1 + patch_.lfo[i].rate);
      lfo_to_reset_ |= _BV(i);
    }*/
    UpdateLfoRate(i);
  }
  for (uint8_t i = 0; i < kNumEnvelopes; ++i) {
    voice_.mutable_envelope(i)->Update(
        patch_.env[i].attack,
        patch_.env[i].decay,
        patch_.env[i].sustain,
        patch_.env[i].release);
  }
}

/* static */
void Part::UpdateLfoRate(uint8_t i) {
  uint16_t phase_increment;
  // The LFO rates 0 to 15 are translated into a multiple of the step
  // sequencer/arpeggiator step size.
  if (patch_.lfo[i].rate < 16) {
    
  } else {
    int16_t rate = patch_.lfo[i].rate;
    rate += voice_.modulation_destination(MOD_DST_LFO_1 + i);
    rate -= 32;
    if (rate < 0) {
      rate = 0;
    } else if (rate >= 128) {
      rate = 127;
    }
    phase_increment = ResourcesManager::Lookup<uint16_t, uint8_t>(
        lut_res_lfo_increments, rate);
  }
  lfo_[i].Update(
      patch_.lfo[i].waveform,
      phase_increment,
      patch_.lfo[i].attack,
      patch_.lfo[i].retrigger_mode);
}

const prog_uint8_t filter_modes[15] PROGMEM = {
  2, 10, 1, 9, 8, 11, 13, 0, 7, 14, 12, 3, 5, 6, 4
};

/* static */
uint8_t Part::four_pole_routing_byte() {
  uint8_t byte = pgm_read_byte(filter_modes + patch_.filter_1_mode_);
  byte |= U8ShiftLeft4(patch_.filter_2_mode_);
  if (running() && sequencer_settings_.mode() != SEQUENCER_MODE_STEP) {
    if (!(arp_seq_step_ & 3)) {
      byte |= 0xc0;
    }
  } else if (modulation_source(0, MOD_SRC_WHEEL) > 224) {
    uint8_t i = kModulationMatrixSize - 1;
    uint8_t wheel_mod = patch_.modulation_matrix.modulation[i].source;
    wheel_mod = voice_.modulation_source(wheel_mod);
    byte |= (wheel_mod > 0xc0 ? 0x80 : 0x00);
    byte |= (wheel_mod < 0x40 ? 0x40 : 0x00);
  } else if (patch_.filter_resonance > 56) {
    byte |= 0xc0;
  }
  return byte;
}

/* static */
void Part::ProcessBlock() {
  if (sequencer_settings_.internal_clock() && running()) {
    if (clock.Wrap(swing_amount_)) {
      swing_amount_ = S8U8MulShift8(
          ResourcesManager::Lookup<int16_t, uint8_t>(
              LUT_RES_GROOVE_SWING + sequencer_settings_.seq_groove_template,
              arp_seq_step_),
          sequencer_settings_.seq_groove_amount);
      Clock(true);
      clock.Update(sequencer_settings_.seq_tempo);
    }
  }
  
  for (uint8_t i = 0; i < kNumLfos; ++i) {
    voice_.set_modulation_source(MOD_SRC_LFO_1 + i, lfo_[i].Render(
        sequencer_settings_));
  }
  voice_.set_modulation_source(MOD_SRC_NOISE, Random::state_msb());

  // Update the modulation speed if some of the LFO FM parameters have changed.
  for (uint8_t i = 0; i < kNumLfos; ++i) {
    if (previous_lfo_fm_[i] !=
       voice_.modulation_destination(MOD_DST_LFO_1 + i)) {
      previous_lfo_fm_[i] = voice_.modulation_destination(MOD_DST_LFO_1 + i);
      UpdateLfoRate(i);
    }
  }

  // Looping envelopes. Note that the second envelope stops looping after the
  // key is released otherwise the note will never stops playing.
  for (uint8_t j = 0; j < kNumLfos; ++j) {
    if (lfo_[j].triggered() &&
        patch_.lfo[j].retrigger_mode == LFO_MODE_MASTER) {
      voice_.TriggerEnvelope(j, ATTACK);
    }
  }
  voice_.ProcessBlock();
}

/* static */
void Part::AllNotesOff() {
  poly_allocator_.Clear();
  mono_allocator_.Clear();
  pressed_keys_.Clear();
  voice_.NoteOff();
  release_latched_keys_on_next_note_on_ = false;
  ignore_note_off_messages_ = false;
}

/* sattic */
void Part::StopSequencerArpeggiatorNotes() {
  while (generated_notes_.size()) {
    uint8_t note = generated_notes_.sorted_note(0).note;
    generated_notes_.NoteOff(note);
    InternalNoteOff(note);
  }
}

/* static */
void Part::ReleaseLatchedNotes() {
  for (uint8_t i = 1; i <= pressed_keys_.max_size(); ++i) {
    NoteEntry* e = pressed_keys_.mutable_note(i);
    if (e->velocity & 0x80) {
      NoteOff(midi_dispatcher.channel(), e->note);
    }
  }
}

/* static */
uint16_t Part::Tune(uint8_t note) {
  if (system_settings_.raga) {
    int16_t pitch_shift = ResourcesManager::Lookup<int16_t, uint8_t>(
        ResourceId(LUT_RES_SCALE_JUST + part.system_settings_.raga - 1),
        note % 12);
    if (pitch_shift != 32767) {
      return U8U8Mul(note, 128) + pitch_shift;
    } else {
      // Some scales/raga settings might have muted notes. Do not trigger
      // anything in this case!
      return 0;
    }
  } else {
    return U8U8Mul(note, 128);
  }
}

/* static */
void Part::InternalNoteOn(uint8_t note, uint8_t velocity) {
  midi_dispatcher.OnInternalNoteOn(note, velocity);
  
  if (system_settings_.midi_out_mode >= MIDI_OUT_1_0) {
    // Polyphonic mode.
    poly_allocator_.set_size(system_settings_.midi_out_mode - MIDI_OUT_1_0 + 1);
    if (poly_allocator_.NoteOn(note) == 0) {
      voice_.NoteOn(Tune(note), velocity, 0, true);
    } else { 
      midi_dispatcher.ForwardNoteOn(midi_dispatcher.channel(), note, velocity);
    }
  } else {
    const NoteEntry& before = mono_allocator_.most_recent_note();
    mono_allocator_.NoteOn(note, velocity);
    const NoteEntry& after = mono_allocator_.most_recent_note();
    if (before.note != after.note) {
      bool legato = mono_allocator_.size() > 1;
      voice_.NoteOn(
          Tune(after.note),
          after.velocity,
          !system_settings_.legato || legato ? system_settings_.portamento : 0,
          !system_settings_.legato || !legato);
    }
  }
}

const prog_uint8_t clock_divisions[] PROGMEM = {
  96, 48, 32, 24, 16, 12, 8, 6, 4, 3, 2, 1
};

/* static */
uint8_t Part::step_duration() {
  return pgm_read_byte(clock_divisions + sequencer_settings_.arp_clock_division);
}

/* static */
void Part::InternalNoteOff(uint8_t note) {
  midi_dispatcher.OnInternalNoteOff(note);
  
  if (system_settings_.midi_out_mode >= MIDI_OUT_1_0) {
    // Polyphonic mode.
    poly_allocator_.set_size(system_settings_.midi_out_mode - MIDI_OUT_1_0 + 1);
    if (poly_allocator_.NoteOff(note) == 0) {
      voice_.NoteOff();
    } else {
      midi_dispatcher.ForwardNoteOff(midi_dispatcher.channel(), note);
    }
  } else {
    const NoteEntry& before = mono_allocator_.most_recent_note();
    mono_allocator_.NoteOff(note);
    const NoteEntry& after = mono_allocator_.most_recent_note();
    if (mono_allocator_.size() == 0) {
      voice_.NoteOff();
    } else if (before.note != after.note) {
      voice_.NoteOn(
          Tune(after.note),
          after.velocity,
          system_settings_.portamento,
          !system_settings_.legato);
    }
  }
}

}  // namespace shruthi
