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

#include "avrlib/resources_manager.h"
#include "shruthi/audio_out.h"
#include "shruthi/midi_dispatcher.h"
#include "shruthi/parameter.h"
#include "shruthi/storage.h"
#include "avrlib/random.h"
#include "avrlib/op.h"

using namespace avrlib;

namespace shruthi {

/* extern */
Part part;

/* <static> */
uint8_t Part::data_access_byte_[1];
Patch Part::patch_;
SequencerSettings Part::sequencer_settings_;
SystemSettings Part::system_settings_;

Voice Part::voice_;
VoiceAllocator Part::polychaining_allocator_;
Lfo Part::lfo_[kNumLfos] = { };
uint8_t Part::previous_lfo_fm_[kNumLfos];
uint8_t Part::nrpn_parameter_number_msb_;
uint8_t Part::nrpn_parameter_number_;
uint8_t Part::data_entry_msb_;
uint8_t Part::num_lfo_reset_steps_;
uint8_t Part::lfo_reset_counter_;
uint8_t Part::lfo_to_reset_;
bool Part::dirty_;
uint8_t Part::ignore_note_off_messages_;
uint8_t Part::volume_;

/* </static> */

/* static */
void Part::Init() {
  polychaining_allocator_.Init();
  ResetPatch();
  ResetSequencerSettings();
  if (!system_settings_.EepromLoad()) {
    ResetSystemSettings();
    system_settings_.EepromSave();
  }
  Reset();
  voice_.Init();
  nrpn_parameter_number_ = 255;
  dirty_ = false;
}

static const prog_char init_patch[] PROGMEM = {
    // Oscillators
    WAVEFORM_SAW, 0, 0, 0,
    WAVEFORM_SQUARE, 16, -12, 12,
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
    SEQUENCER_MODE_STEP, 120, 0, WARP_NORMAL,
    ARPEGGIO_DIRECTION_UP, 1, 0, ARPEGGIO_VELOCITY_SOURCE_KEYBOARD,
    
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
  volume_ = 255;
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
    NoteOff(channel, note, 0);
    return;
  }
  if (system_settings_.midi_out_mode >= MIDI_OUT_1_0) {
    polychaining_allocator_.set_size(
        system_settings_.midi_out_mode - MIDI_OUT_1_0 + 1);
    // Check which unit in the chain is responsible for this note/voice. If this
    // is not the current unit, forward to the next unit in the chain.
    if (polychaining_allocator_.NoteOn(note) == 0) {
      voice_.Trigger(note, velocity, 0);
    } else {
      midi_dispatcher.ForwardNoteOn(note, velocity);
    }
  } else {
    // If the note is above the split point, just forward it.
    if (system_settings_.midi_out_mode == MIDI_OUT_SPLIT &&
        note >= system_settings_.midi_split_point * 12) {
      midi_dispatcher.ForwardNoteOn(note, velocity);
    } else {
      voice_.Trigger(note, velocity, 0);
    }
  }
}

/* static */
void Part::NoteOff(uint8_t channel, uint8_t note, uint8_t velocity) {
  if (system_settings_.midi_out_mode >= MIDI_OUT_1_0) {
    polychaining_allocator_.set_size(
        system_settings_.midi_out_mode - MIDI_OUT_1_0 + 1);
    // Check which unit in the chain is responsible for this note/voice. If this
    // is not the current unit, forward to the next unit in the chain.
    if (polychaining_allocator_.NoteOff(note) == 0) {
      voice_.Release();
    } else { 
      midi_dispatcher.ForwardNoteOff(note);
    }
  } else {
    // If the note is above the split point, just forward it.
    if (system_settings_.midi_out_mode == MIDI_OUT_SPLIT &&
        note >= system_settings_.midi_split_point * 12) {
      midi_dispatcher.Send3(0x80 | channel, note, 0);
    } else {
      midi_dispatcher.ForwardNoteOff(note);
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
        set_unregistered_modulation_source(0, value << 1);
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
void Part::PitchBend(uint8_t channel, uint16_t pitch_bend) {
  uint8_t value = U14ShiftRight6(pitch_bend);
  set_modulation_source(MOD_SRC_PITCH_BEND, value);
}

/* static */
void Part::Aftertouch(uint8_t channel, uint8_t note,
                                 uint8_t velocity) {
                                   
  set_modulation_source(MOD_SRC_AFTERTOUCH, velocity << 1);
}

/* static */
void Part::Aftertouch(uint8_t channel, uint8_t velocity) {
  set_modulation_source(MOD_SRC_AFTERTOUCH, velocity << 1);
}

/* static */
void Part::AllSoundOff(uint8_t channel) {
  // controller_.AllSoundOff();
}

/* static */
void Part::AllNotesOff(uint8_t channel) {
  // controller_.AllNotesOff();
}

/* static */
void Part::ResetAllControllers(uint8_t channel) {
  set_modulation_source(MOD_SRC_PITCH_BEND, 128);
  set_modulation_source(MOD_SRC_WHEEL, 0);
  set_unregistered_modulation_source(0, 0);
  set_modulation_source(MOD_SRC_OFFSET, 255);
  volume_ = 255;
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
  // controller_.Reset();
  // controller_.AllSoundOff();
  ResetAllControllers(0);
  for (uint8_t i = 0; i < kNumLfos; ++i) {
    lfo_[i].Reset();
  }
}

/* static */
void Part::Clock() {
  // controller_.ExternalSync();
}

/* static */
void Part::Start() {
}

/* static */
void Part::Stop() {
  // controller_.StopAndKillNotes();
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
  } else if (offset >= PRM_SEQ_MODE && offset < PRM_SYS_OCTAVE) {
    // controller_.TouchSequence();
  }
  midi_dispatcher.OnEdit(offset, value, user_initiated);
}

/* static */
void Part::UpdateModulationRates() {
  // Update the LFO increments.
  num_lfo_reset_steps_ = 0;
  lfo_to_reset_ = 0;
  for (uint8_t i = 0; i < kNumLfos; ++i) {
    if (patch_.lfo[i].rate < 16) {
      num_lfo_reset_steps_ = U8U8Mul(
          num_lfo_reset_steps_ ? num_lfo_reset_steps_ : 1,
          1 + patch_.lfo[i].rate);
      lfo_to_reset_ |= _BV(i);
    }
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
  if (running() &&
      sequencer_settings_.seq_mode >= SEQUENCER_MODE_ARP_LATCH &&
      sequencer_settings_.seq_mode <= SEQUENCER_MODE_RPS_LATCH) {
    /*if (!(controller_.step() & 3)) {
      byte |= 0xc0;
    }*/
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
  for (uint8_t i = 0; i < kNumLfos; ++i) {
    set_modulation_source(MOD_SRC_LFO_1 + i, lfo_[i].Render(
        sequencer_settings_));
  }
  set_modulation_source(MOD_SRC_NOISE, Random::state_msb());

  // Update the arpeggiator / step sequencer.
  /*if (controller_.Control()) {
    // We need to do a couple of things when the step sequencer advances to the
    // next step:
    // - periodically (eg whenever we move to step 0), recompute the LFO
    // increments from the tempo, (if the LFO follows the tempo), since the
    // tempo might have been modified by the user or the rate of the MIDI clock
    // messages.
    // - Reset the LFO value to 0 every n-th step. Otherwise, there might be a
    // "synchronization drift" because of rounding errors.
    ++lfo_reset_counter_;
    if (lfo_reset_counter_ == num_lfo_reset_steps_) {
      UpdateModulationRates();
      for (uint8_t i = 0; i < kNumLfos; ++i) {
        if (lfo_to_reset_ & _BV(i)) {
          lfo_[i].ResetPhase();
        }
      }
      lfo_reset_counter_ = 0;
    }
  }*/

  // Read/shift the value of the step sequencer.
  /*uint8_t step = (controller_.step() + \
      sequencer_settings_.pattern_rotation) & 0x0f;*/
  uint8_t step = 0;
  set_modulation_source(
      MOD_SRC_SEQ,
      sequencer_settings_.steps[step].controller() << 4);
  step &= 0x7;
  set_modulation_source(
      MOD_SRC_SEQ_1,
      sequencer_settings_.steps[step].controller() << 4);
  set_modulation_source(
      MOD_SRC_SEQ_2,
      sequencer_settings_.steps[step + 8].controller() << 4);
  set_modulation_source(
      MOD_SRC_STEP,
      /*controller_.has_arpeggiator_note() ? 255 : 0*/ 255);
      
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

}  // namespace shruthi
