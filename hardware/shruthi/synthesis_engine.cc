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

#include "hardware/shruthi/synthesis_engine.h"

#include <string.h>

#include "hardware/resources/resources_manager.h"
#include "hardware/shruthi/audio_out.h"
#include "hardware/shruthi/midi_dispatcher.h"
#include "hardware/shruthi/oscillator.h"
#include "hardware/shruthi/parameter_definitions.h"
#include "hardware/shruthi/storage.h"
#include "hardware/shruthi/transient_generator.h"
#include "hardware/utils/random.h"
#include "hardware/utils/op.h"

using namespace hardware_utils_op;

namespace hardware_shruthi {

/* extern */
SynthesisEngine engine;

Oscillator<1> osc_1;
Oscillator<2> osc_2;
SubOscillator<1> sub_osc;
TransientGenerator<1> transient_generator;

/* <static> */
uint8_t SynthesisEngine::data_access_byte_[1];
Patch SynthesisEngine::patch_;
SequencerSettings SynthesisEngine::sequencer_settings_;
SystemSettings SynthesisEngine::system_settings_;

Voice SynthesisEngine::voice_[kNumVoices];
VoiceController SynthesisEngine::controller_;
VoiceAllocator SynthesisEngine::polychaining_allocator_;
Lfo SynthesisEngine::lfo_[kNumLfos] = { };
uint8_t SynthesisEngine::previous_lfo_fm_[kNumLfos];
uint8_t SynthesisEngine::nrpn_parameter_number_msb_;
uint8_t SynthesisEngine::nrpn_parameter_number_;
uint8_t SynthesisEngine::data_entry_msb_;
uint8_t SynthesisEngine::num_lfo_reset_steps_;
uint8_t SynthesisEngine::lfo_reset_counter_;
uint8_t SynthesisEngine::lfo_to_reset_;
uint8_t SynthesisEngine::dirty_;
uint8_t SynthesisEngine::ignore_note_off_messages_;
uint8_t SynthesisEngine::volume_;

/* </static> */

/* static */
void SynthesisEngine::Init() {
  controller_.Init(&sequencer_settings_, voice_, kNumVoices);
  polychaining_allocator_.Init();
  ResetPatch();
  ResetSequencerSettings();
  if (!system_settings_.EepromLoad()) {
    ResetSystemSettings();
    system_settings_.EepromSave();
  }
  Reset();
  for (uint8_t i = 0; i < kNumVoices; ++i) {
    voice_[i].Init();
  }
  nrpn_parameter_number_ = 255;
  dirty_ = 0;
  
  // Fill the "user" wavetable with data from an existing wavetable.
  ResourcesManager::Load(
      wav_res_wavetable_3,
      user_wavetable,
      kUserWavetableSize);
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
    1, 0,
    PRM_FILTER_CUTOFF, 0,
    PRM_FILTER_RESONANCE, 0,
    PRM_FILTER_ENV, 0,
    // Settings for second filter
    0, 0, 0 /* LP in parallel with a second LP */, 
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
void SynthesisEngine::ResetPatch() {
  ResourcesManager::Load(init_patch, 0, &patch_);
  TouchPatch(1);
}

/* static */
void SynthesisEngine::TouchPatch(uint8_t cascade) {
  UpdateModulationRates();
  UpdateOscillatorAlgorithms();
  dirty_ = 1;
  if (cascade) {
    if (system_settings_.midi_out_mode >= MIDI_OUT_2_1) {
      Storage::SysExDump(&patch_);
    }
  }
  volume_ = 255;
}

/* static */
void SynthesisEngine::ResetSequencerSettings() {
  ResourcesManager::Load(init_sequence, 0, &sequencer_settings_);
  controller_.TouchSequence();
}

/* static */
void SynthesisEngine::ResetSequence() {
  ResourcesManager::Load(init_sequence + 10, 0, &sequencer_settings_.steps);
  sequencer_settings_.pattern_size = 16;
  controller_.TouchSequence();
}

/* static */
void SynthesisEngine::ResetSystemSettings() {
  ResourcesManager::Load(init_system_settings, 0, &system_settings_);
}

/* static */
void SynthesisEngine::NoteOn(uint8_t channel, uint8_t note, uint8_t velocity) {
  if (system_settings_.midi_out_mode >= MIDI_OUT_1_0) {
    polychaining_allocator_.set_size(
        system_settings_.midi_out_mode - MIDI_OUT_1_0 + 1);
    // Check which unit in the chain is responsible for this note/voice. If this
    // is not the current unit, forward to the next unit in the chain.
    if (polychaining_allocator_.NoteOn(note) == 0) {
      voice_[0].Trigger(note, velocity, 0);
    } else {
      midi_dispatcher.Send3(0x90 | channel, note, velocity);
    }
  } else {
    // If the note is above the split point, just forward it.
    if (system_settings_.midi_out_mode == MIDI_OUT_SPLIT &&
        note >= system_settings_.midi_split_point * 12) {
      midi_dispatcher.Send3(0x90 | channel, note, velocity);
    } else {
      // If the note controller is not active, we are not currently playing a
      // sequence, so we retrigger the LFOs.
      if (!controller_.active()) {
        lfo_reset_counter_ = num_lfo_reset_steps_ - 1;
      }
      controller_.NoteOn(note, velocity);
    }
  }
}

/* static */
void SynthesisEngine::NoteOff(uint8_t channel, uint8_t note, uint8_t velocity) {
  if (ignore_note_off_messages_) {
    return;
  }
  if (system_settings_.midi_out_mode >= MIDI_OUT_1_0) {
    polychaining_allocator_.set_size(
        system_settings_.midi_out_mode - MIDI_OUT_1_0 + 1);
    // Check which unit in the chain is responsible for this note/voice. If this
    // is not the current unit, forward to the next unit in the chain.
    if (polychaining_allocator_.NoteOff(note) == 0) {
      voice_[0].Release();
    } else { 
      midi_dispatcher.Send3(0x80 | channel, note, 0);
    }
  } else {
    // If the note is above the split point, just forward it.
    if (system_settings_.midi_out_mode == MIDI_OUT_SPLIT &&
        note >= system_settings_.midi_split_point * 12) {
      midi_dispatcher.Send3(0x80 | channel, note, 0);
    } else {
      controller_.NoteOff(note);
    }
  }
}

/* static */
void SynthesisEngine::ControlChange(uint8_t channel, uint8_t controller,
                                    uint8_t value) {
  uint8_t editing_controller = 0;
  if (controller >= hardware_midi::kAssignableCcA &&
      controller <= hardware_midi::kAssignableCcD) {
    set_modulation_source(MOD_SRC_CC_A + controller -
        hardware_midi::kAssignableCcA, value << 1);
  } else if (controller >= 20 && controller <= 31) {
    controller -= 20;  // CCs for oscillators and mixer.
    editing_controller = 1;
  } else if (controller >= 14 && controller <= 15) {
    controller -= 2; // CCs for Cutoff and resonance.
    editing_controller = 1;
  } else if (controller >= 102 && controller <= 119) {
    controller -= (102 - 14); // CCs for filter mods, envelopes and LFOs.
    editing_controller = 1;
  } else {
    switch (controller) {
      case hardware_midi::kModulationWheelMsb:
        set_modulation_source(MOD_SRC_WHEEL, value << 1);
        break;
      case hardware_midi::kModulationWheelJoystickMsb:
        set_unregistered_modulation_source(0, value << 1);
        break;
      case hardware_midi::kDataEntryMsb:
        data_entry_msb_ = value << 7;
        break;
      case hardware_midi::kVolume:
        volume_ = value << 1;
        break;
      case hardware_midi::kDataEntryLsb:
      case hardware_midi::kDataIncrement:
      case hardware_midi::kDataDecrement:
        value |= data_entry_msb_;
        if (nrpn_parameter_number_ != 255) {
          dirty_ = 1;
          // Finds the parameter definition id matching this parameter id.
          uint8_t parameter_definition_id = nrpn_parameter_number_;
          if (parameter_definition_id >= PRM_SEQ_MODE) {
            parameter_definition_id -= PRM_SEQ_MODE;
            parameter_definition_id += PRM_MOD_ROW + 1;
          } else if (parameter_definition_id >= PRM_MOD_SOURCE) {
            while (parameter_definition_id > PRM_MOD_AMOUNT) {
              parameter_definition_id -= 3;
            }
            ++parameter_definition_id;
          }
          const ParameterDefinition& p = (
              ParameterDefinitions::parameter_definition(
                  parameter_definition_id));
          if (controller == hardware_midi::kDataEntryLsb) {
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
                controller == hardware_midi::kDataIncrement ? 1 : -1);
            if (new_value != old_value) {
              SetParameter(nrpn_parameter_number_, new_value, 0);
            }
          }
        }
        data_entry_msb_ = 0;
        break;
      case hardware_midi::kHoldPedal:
        if (value >= 64) {
          ignore_note_off_messages_ = 1;
        } else {
          ignore_note_off_messages_ = 0;
          controller_.AllNotesOff();
        }
        break;
      case hardware_midi::kPortamentoTimeMsb:
        system_settings_.portamento = value;
        break;
      case hardware_midi::kRelease:
        SetParameter(PRM_ENV_RELEASE_2, value, 0);
        break;
      case hardware_midi::kAttack:
        SetParameter(PRM_ENV_ATTACK_2, value, 0);
        break;
      case hardware_midi::kHarmonicIntensity:
        patch_.filter_resonance = value >> 1;
        break;
      case hardware_midi::kBrightness:
        patch_.filter_cutoff = value;
        break;
      case hardware_midi::kNrpnLsb:
        nrpn_parameter_number_ = value | nrpn_parameter_number_msb_;
        nrpn_parameter_number_msb_ = 0;
        data_entry_msb_ = 0;
        break;
      case hardware_midi::kNrpnMsb:
        nrpn_parameter_number_msb_ = value << 7;
        data_entry_msb_ = 0;
        break;
    }
  }
  if (editing_controller) {
    SetScaledParameter(controller, value, 0);
  }
}

/* static */
void SynthesisEngine::PitchBend(uint8_t channel, uint16_t pitch_bend) {
  uint8_t value = pitch_bend >> 6;
  set_modulation_source(MOD_SRC_PITCH_BEND, value);
}

/* static */
void SynthesisEngine::Aftertouch(uint8_t channel, uint8_t note,
                                 uint8_t velocity) {
                                   
  set_modulation_source(MOD_SRC_AFTERTOUCH, velocity << 1);
}

/* static */
void SynthesisEngine::Aftertouch(uint8_t channel, uint8_t velocity) {
  set_modulation_source(MOD_SRC_AFTERTOUCH, velocity << 1);
}

/* static */
void SynthesisEngine::AllSoundOff(uint8_t channel) {
  controller_.AllSoundOff();
}

/* static */
void SynthesisEngine::AllNotesOff(uint8_t channel) {
  controller_.AllNotesOff();
}

/* static */
void SynthesisEngine::ResetAllControllers(uint8_t channel) {
  set_modulation_source(MOD_SRC_PITCH_BEND, 128);
  set_modulation_source(MOD_SRC_WHEEL, 0);
  set_unregistered_modulation_source(0, 0);
  set_modulation_source(MOD_SRC_OFFSET, 255);
  volume_ = 255;
}

// When in Omni mode, disable Omni and enable reception only on the channel on
// which this message has been received.
/* static */
void SynthesisEngine::OmniModeOff(uint8_t channel) {
  system_settings_.midi_channel = channel + 1;
}

// Enable Omni mode.
/* static */
void SynthesisEngine::OmniModeOn(uint8_t channel) {
  system_settings_.midi_channel = 0;
}

/* static */
void SynthesisEngine::Reset() {
  controller_.Reset();
  controller_.AllSoundOff();
  ResetAllControllers(0);
  for (uint8_t i = 0; i < kNumLfos; ++i) {
    lfo_[i].Reset();
  }
}

/* static */
void SynthesisEngine::Clock() {
  controller_.ExternalSync();
}

/* static */
void SynthesisEngine::Start() {
  if (sequencer_settings_.seq_mode >= SEQUENCER_MODE_RPS) {
    controller_.NoteOn(60, 100);
  }
  controller_.Start();
}

/* static */
void SynthesisEngine::Stop() {
  controller_.StopAndKillNotes();
}

/* static */
void SynthesisEngine::SetScaledParameter(
    uint8_t parameter_index,
    uint8_t value,
    uint8_t user_initiated) {
  dirty_ = 1;
  const ParameterDefinition& parameter = (
      ParameterDefinitions::parameter_definition(parameter_index));
  SetParameter(
      parameter.id,
      ParameterDefinitions::Scale(parameter, value),
      user_initiated);
}

/* static */
void SynthesisEngine::SetParameter(
    uint8_t parameter_index,
    uint8_t parameter_value,
    uint8_t user_initiated) {
  if (data_access_byte_[parameter_index + 1] == parameter_value) {
    return;
  }
  data_access_byte_[parameter_index + 1] = parameter_value;
  if (parameter_index >= PRM_ENV_ATTACK_1 &&
      parameter_index <= PRM_LFO_RETRIGGER_2) {
    UpdateModulationRates();
  } else if ((parameter_index <= PRM_OSC_SHAPE_2) ||
             (parameter_index == PRM_MIX_SUB_OSC_SHAPE)) {
    UpdateOscillatorAlgorithms();
  } else if (parameter_index >= PRM_SEQ_MODE &&
             parameter_index < PRM_SYS_OCTAVE) {
    // A copy of those parameters is stored by the note dispatcher/arpeggiator,
    // so any parameter change must be forwarded to it.
    controller_.TouchSequence();
  }
  midi_dispatcher.SendParameter(
      parameter_index, parameter_value, user_initiated);
}

/* static */
void SynthesisEngine::UpdateOscillatorAlgorithms() {
  osc_1.SetupAlgorithm(patch_.osc[0].shape);
  osc_2.SetupAlgorithm(patch_.osc[1].shape);
  sub_osc.SetupAlgorithm(patch_.mix_sub_osc_shape);
  transient_generator.SetupAlgorithm(patch_.mix_sub_osc_shape);
}

/* static */
void SynthesisEngine::UpdateModulationRates() {
  // Update the LFO increments.
  num_lfo_reset_steps_ = 0;
  lfo_to_reset_ = 0;
  for (uint8_t i = 0; i < kNumLfos; ++i) {
    if (patch_.lfo[i].rate < 16) {
      num_lfo_reset_steps_ = UnsignedUnsignedMul(
          num_lfo_reset_steps_ ? num_lfo_reset_steps_ : 1,
          1 + patch_.lfo[i].rate);
      lfo_to_reset_ |= _BV(i);
    }
    UpdateLfoRate(i);
  }
  for (uint8_t i = 0; i < kNumEnvelopes; ++i) {
    for (uint8_t j = 0; j < kNumVoices; ++j) {
      voice_[j].mutable_envelope(i)->Update(
          patch_.env[i].attack,
          patch_.env[i].decay,
          patch_.env[i].sustain,
          patch_.env[i].release);
    }
  }
}

/* static */
void SynthesisEngine::UpdateLfoRate(uint8_t i) {
  uint16_t phase_increment;
  // The LFO rates 0 to 15 are translated into a multiple of the step
  // sequencer/arpeggiator step size.
  if (patch_.lfo[i].rate < 16) {
    phase_increment = 65536 / (controller_.estimated_beat_duration() *
                         (1 + patch_.lfo[i].rate) / 4);
  } else {
    uint16_t rate = patch_.lfo[i].rate;
    rate += voice_[0].modulation_destination(MOD_DST_LFO_1 + i);
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

/* static */
void SynthesisEngine::ProcessBlock() {
  for (uint8_t i = 0; i < kNumLfos; ++i) {
    set_modulation_source(MOD_SRC_LFO_1 + i, lfo_[i].Render(
        sequencer_settings_));
  }
  set_modulation_source(MOD_SRC_NOISE, Random::state_msb());

  // Update the arpeggiator / step sequencer.
  if (controller_.Control()) {
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
  }

  // Read/shift the value of the step sequencer.
  uint8_t step = (controller_.step() + \
      sequencer_settings_.pattern_rotation) & 0x0f;
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
      controller_.has_arpeggiator_note() ? 255 : 0);
      
  // Update the modulation speed if some of the LFO FM parameters have changed.
  for (uint8_t i = 0; i < kNumLfos; ++i) {
    if (previous_lfo_fm_[i] !=
       voice_[0].modulation_destination(MOD_DST_LFO_1 + i)) {
      previous_lfo_fm_[i] = voice_[0].modulation_destination(MOD_DST_LFO_1 + i);
      UpdateLfoRate(i);
    }
  }

  for (uint8_t i = 0; i < kNumVoices; ++i) {
    // Looping envelopes. Note that the second envelope stops looping after the
    // key is released otherwise the note will never stops playing.
    for (uint8_t j = 0; j < kNumLfos; ++j) {
      if (lfo_[j].triggered() &&
          patch_.lfo[j].retrigger_mode == LFO_MODE_MASTER) {
        voice_[i].TriggerEnvelope(j, ATTACK);
      }
    }
    voice_[i].ProcessBlock();
  }
}

/* <static> */
Envelope Voice::envelope_[kNumEnvelopes];
uint8_t Voice::dead_;
int16_t Voice::pitch_increment_;
int16_t Voice::pitch_target_;
int16_t Voice::pitch_value_;
uint8_t Voice::modulation_sources_[kNumModulationSources];
uint8_t Voice::unregistered_modulation_sources_[1];
int8_t Voice::modulation_destinations_[kNumModulationDestinations];
uint8_t Voice::osc1_phase_msb_;
uint8_t Voice::last_note_;
int16_t Voice::dst_[kNumModulationDestinations];
uint8_t Voice::buffer_[kAudioBlockSize];
uint8_t Voice::osc2_buffer_[kAudioBlockSize];
uint8_t Voice::sub_osc_buffer_[kAudioBlockSize];
uint8_t Voice::sync_state_[kAudioBlockSize];
uint8_t Voice::no_sync_[kAudioBlockSize];
/* </static> */

/* static */
void Voice::Init() {
  pitch_value_ = 0;
  last_note_ = 0;
  for (uint8_t i = 0; i < kNumEnvelopes; ++i) {
    envelope_[i].Init();
  }
  memset(no_sync_, 0, kAudioBlockSize);
}

/* static */
void Voice::TriggerEnvelope(uint8_t stage) {
  for (uint8_t i = 0; i < kNumEnvelopes; ++i) {
    envelope_[i].Trigger(stage);
  }
}

/* static */
void Voice::TriggerEnvelope(uint8_t index, uint8_t stage) {
  envelope_[index].Trigger(stage);
}

/* static */
void Voice::Trigger(uint8_t note, uint8_t velocity, uint8_t legato) {
  if (engine.system_settings_.raga) {
    int16_t pitch_shift = ResourcesManager::Lookup<int16_t, uint8_t>(
        ResourceId(LUT_RES_SCALE_JUST + engine.system_settings_.raga - 1),
        note % 12);
    if (pitch_shift != 32767) {
      // Some scales/raga settings might have muted notes. Do not trigger
      // anything in this case!
      pitch_target_ = (static_cast<uint16_t>(note) * 128) + pitch_shift;
    } else {
      if (legato) {
        legato = 255;
      }
    }
  } else {
    pitch_target_ = UnsignedUnsignedMul(note, 128);
  }
  if (!legato || (!engine.system_settings_.legato && legato != 255)) {
    TriggerEnvelope(PRE_ATTACK);
    // The LFOs are shared by all voices, so if there are other voices still
    // playing there will be a discontinuity. We don't care because we're
    // doing monophonic things anyway (and some pseudo-polysynths/organs are
    // doing the same things).
    engine.TriggerLfos();
    transient_generator.Trigger();
    modulation_sources_[MOD_SRC_VELOCITY] = velocity << 1;
    modulation_sources_[MOD_SRC_RANDOM] = Random::state_msb();
  }
  // At boot up, or when the note is not played legato and the portamento
  // is in auto mode, do not ramp up the pitch but jump straight to the target
  // pitch.
  if (pitch_value_ == 0 || (!legato && engine.system_settings_.legato)) {
    pitch_value_ = pitch_target_;
  }
  int16_t delta = pitch_target_ - pitch_value_;
  int32_t increment = ResourcesManager::Lookup<uint16_t, uint8_t>(
      lut_res_env_portamento_increments,
      engine.system_settings_.portamento);
  pitch_increment_ = (delta * increment) >> 15;
  if (pitch_increment_ == 0) {
    if (delta < 0) {
      pitch_increment_ = -1;
    } else {
      pitch_increment_ = 1;
    }
  }
  // If this note is triggered by the sequencer/arpeggiator, we might have to
  // forward it to the MIDI out too.
  if (last_note_ != note || !legato) {
    if (last_note_ != 0) {
      midi_dispatcher.NoteKilled(last_note_);
    }
    midi_dispatcher.NoteTriggered(note, velocity);
  }
  last_note_ = note;
}

/* static */
void Voice::Release() {
  TriggerEnvelope(RELEASE_1);
  if (last_note_ != 0) {
    midi_dispatcher.NoteKilled(last_note_);
    last_note_ = 0;
  }
}

/* static */
inline void Voice::LoadSources() {
  static uint8_t ops[7];
  
  // Rescale the value of each modulation sources. Envelopes are in the
  // 0-16383 range ; just like pitch. All are scaled to 0-255.
  modulation_sources_[MOD_SRC_ENV_1] = ShiftRight6(envelope_[0].value());
  modulation_sources_[MOD_SRC_ENV_2] = ShiftRight6(envelope_[1].value());
  modulation_sources_[MOD_SRC_NOTE] = ShiftRight6(pitch_value_);
  modulation_sources_[MOD_SRC_GATE] = envelope_[0].stage() >= RELEASE_1 ? 0 : 255;
  modulation_sources_[MOD_SRC_AUDIO] = buffer_[0];
  
  // Apply the modulation operators
  for (uint8_t i = 0; i < 2; ++i) {
    uint8_t x = engine.patch_.ops_[i].operands[0];
    uint8_t y = engine.patch_.ops_[i].operands[1];
    x = modulation_sources_[x];
    y = modulation_sources_[y];
    if (x > y) {
      ops[2] = x;  ops[5] = 255;
      ops[3] = y;  ops[6] = 0;
    } else {
      ops[2] = y;  ops[5] = 0;
      ops[3] = x;  ops[6] = 255;
    }
    ops[0] = (x >> 1) + (y >> 1);
    ops[1] = MulScale8(x, y);
    ops[4] = x ^ y;
    modulation_sources_[MOD_SRC_OP_1 + i] = ops[engine.patch_.ops_[i].op];
  }

  modulation_destinations_[MOD_DST_VCA] = engine.volume_;
  
  // Load and scale to 0-16383 the initial value of each modulated parameter.
  dst_[MOD_DST_FILTER_CUTOFF] = UnsignedUnsignedMul(
      engine.patch_.filter_cutoff, 128);
  dst_[MOD_DST_FILTER_RESONANCE] = engine.patch_.filter_resonance << 8;
  dst_[MOD_DST_PWM_1] = UnsignedUnsignedMul(engine.patch_.osc[0].parameter, 128);
  dst_[MOD_DST_PWM_2] = UnsignedUnsignedMul(engine.patch_.osc[1].parameter, 128);
  dst_[MOD_DST_VCO_1_2_COARSE] = dst_[MOD_DST_VCO_1_2_FINE] =
      dst_[MOD_DST_VCO_2] = dst_[MOD_DST_VCO_1] = 8192;
  dst_[MOD_DST_VCO_2] = dst_[MOD_DST_VCO_1] = 8192;
  dst_[MOD_DST_MIX_BALANCE] = engine.patch_.mix_balance << 8;
  dst_[MOD_DST_MIX_NOISE] = engine.patch_.mix_noise << 8;
  dst_[MOD_DST_MIX_SUB_OSC] = engine.patch_.mix_sub_osc << 8;
  dst_[MOD_DST_CV_1] = 0;
  dst_[MOD_DST_CV_2] = 0;
  if (engine.system_settings_.expansion_filter_board >= FILTER_BOARD_SSM) {
    dst_[MOD_DST_CV_1] = UnsignedUnsignedMul(
        engine.patch_.filter_cutoff_2, 128);
    dst_[MOD_DST_CV_2] = UnsignedUnsignedMul(
        engine.patch_.filter_resonance_2, 128);
  }
  dst_[MOD_DST_ATTACK] = 0;
  dst_[MOD_DST_LFO_1] = 8192;
  dst_[MOD_DST_LFO_2] = 8192;
}

/* static */
inline void Voice::ProcessModulationMatrix() {
  // Apply the modulations in the modulation matrix.
  for (uint8_t i = 0; i < kModulationMatrixSize; ++i) {
    int8_t amount = engine.patch_.modulation_matrix.modulation[i].amount;
    if (!amount) {
      continue;
    }

    // The rate of the last modulation is adjusted by the wheel.
    if (i == kModulationMatrixSize - 1) {
      amount = SignedMulScale8(
          amount,
          modulation_sources_[MOD_SRC_WHEEL]);
    }
    uint8_t source = engine.patch_.modulation_matrix.modulation[i].source;
    uint8_t destination =
        engine.patch_.modulation_matrix.modulation[i].destination;
    uint8_t source_value;

    source_value = modulation_sources_[source];
    if (destination != MOD_DST_VCA) {
      int16_t modulation = dst_[destination];
      modulation += SignedUnsignedMul(amount, source_value);
      // For those sources, use relative modulation.
      if (source <= MOD_SRC_LFO_2 ||
          source == MOD_SRC_PITCH_BEND ||
          source == MOD_SRC_NOTE ||
          source == MOD_SRC_AUDIO) {
        modulation -= SignedUnsignedMul(amount, 128);
      }
      dst_[destination] = Clip(modulation, 0, 16383);
    } else {
      // The VCA modulation is multiplicative, not additive. Yet another
      // Special case :(.
      if (amount < 0) {
        amount = -amount;
        source_value = 255 - source_value;
      }
      modulation_destinations_[MOD_DST_VCA] = MulScale8(
          modulation_destinations_[MOD_DST_VCA],
          Mix(255, source_value, amount << 2));
    }
  }
}

/* static */
inline void Voice::UpdateDestinations() {
  // Hardcoded filter modulations.
  // By default, the resonance tracks the note. Tracking works best when the
  // transistors are thermically coupled. You can disable tracking by applying
  // a negative modulation from NOTE to CUTOFF.
  dst_[MOD_DST_FILTER_CUTOFF] = Clip(
      dst_[MOD_DST_FILTER_CUTOFF] + pitch_value_ - 8192,
      0,
      16383);
  dst_[MOD_DST_FILTER_CUTOFF] = Clip(
      dst_[MOD_DST_FILTER_CUTOFF] + SignedUnsignedMul(
          engine.patch_.filter_env,
          modulation_sources_[MOD_SRC_ENV_1]),
      0,
      16383);
  dst_[MOD_DST_FILTER_CUTOFF] = Clip(
      dst_[MOD_DST_FILTER_CUTOFF] + (
          unregistered_modulation_sources_[0] << 6),
      0,
      16383);
  dst_[MOD_DST_FILTER_CUTOFF] = Clip(
      dst_[MOD_DST_FILTER_CUTOFF] + SignedUnsignedMul(
          engine.patch_.filter_lfo,
          modulation_sources_[MOD_SRC_LFO_2]) -
      UnsignedUnsignedMul(engine.patch_.filter_lfo, 128),
      0,
      16383);
  
  // Store in memory all the updated parameters.
  modulation_destinations_[MOD_DST_FILTER_CUTOFF] = ShiftRight6(
      dst_[MOD_DST_FILTER_CUTOFF]);

  modulation_destinations_[MOD_DST_FILTER_RESONANCE] = ShiftRight6(
      dst_[MOD_DST_FILTER_RESONANCE]);

  modulation_destinations_[MOD_DST_CV_1] = ShiftRight6(
        dst_[MOD_DST_CV_1]);
  modulation_destinations_[MOD_DST_CV_2] = ShiftRight6(
        dst_[MOD_DST_CV_2]);
  modulation_destinations_[MOD_DST_PWM_1] = dst_[MOD_DST_PWM_1] >> 7;
  modulation_destinations_[MOD_DST_PWM_2] = dst_[MOD_DST_PWM_2] >> 7;
  modulation_destinations_[MOD_DST_LFO_1] = dst_[MOD_DST_LFO_1] >> 8;
  modulation_destinations_[MOD_DST_LFO_2] = dst_[MOD_DST_LFO_2] >> 8;
  
  modulation_destinations_[MOD_DST_MIX_BALANCE] = ShiftRight6(
      dst_[MOD_DST_MIX_BALANCE]);
  
  modulation_destinations_[MOD_DST_MIX_NOISE] = dst_[MOD_DST_MIX_NOISE] >> 8;
  modulation_destinations_[MOD_DST_MIX_SUB_OSC] = dst_[MOD_DST_MIX_SUB_OSC] >> 7;
  
  envelope_[0].SetVelocity(dst_[MOD_DST_ATTACK] >> 7);
  envelope_[1].SetVelocity(dst_[MOD_DST_ATTACK] >> 7);
}

/* static */
inline void Voice::UpdatePhaseIncrements() {
  // Update the oscillator parameters.
  for (uint8_t i = 0; i < kNumOscillators; ++i) {
    int16_t pitch = pitch_value_;
    // -24 / +24 semitones by the range controller.
    if (engine.patch_.osc[i].shape == WAVEFORM_FM) {
      if (i == 0) {
        osc_1.UpdateSecondaryParameter(engine.patch_.osc[i].range + 24);
      } else {
        osc_2.UpdateSecondaryParameter(engine.patch_.osc[i].range + 24);
      }
    } else {
      pitch += SignedUnsignedMul(engine.patch_.osc[i].range, 128);
    }
    // -24 / +24 semitones by the main octave controller.
    pitch += static_cast<int16_t>(engine.system_settings_.octave) * kOctave;
    if (i == 1) {
      // 0 / +1 semitones by the detune option for oscillator 2.
      pitch += engine.patch_.osc[1].option;
    }
    // -16 / +16 semitones by the routed modulations.
    pitch += (dst_[MOD_DST_VCO_1 + i] - 8192) >> 2;
    // -4 / +4 semitones by the vibrato and pitch bend.
    pitch += (dst_[MOD_DST_VCO_1_2_COARSE] - 8192) >> 4;
    // -1 / +1 semitones by the vibrato and pitch bend.
    pitch += (dst_[MOD_DST_VCO_1_2_FINE] - 8192) >> 7;
    // -1 / +1 semitones by master tuning.
    pitch += engine.system_settings_.master_tuning;

    while (pitch >= kHighestNote) {
      pitch -= kOctave;
    }
    // Extract the pitch increment from the pitch table.
    int16_t ref_pitch = pitch - kPitchTableStart;
    uint8_t num_shifts = 0;
    while (ref_pitch < 0) {
      ref_pitch += kOctave;
      ++num_shifts;
    }
    uint24_t increment;
    increment.integral = ResourcesManager::Lookup<uint16_t, uint16_t>(
        lut_res_oscillator_increments, ref_pitch >> 1);
    increment.fractional = 0;
    // Divide the pitch increment by the number of octaves we had to transpose
    // to get a value in the lookup table.
    while (num_shifts--) {
      increment = Lsr24(increment);
    }

    // Now the oscillators can recompute all their internal variables!
    int8_t midi_note = pitch >> 7;
    if (midi_note < 12) {
      midi_note = 12;
    }
    // phase_increment.fractional = 0;
    if (i == 0) {
      osc_1.Render(
          modulation_destinations_[MOD_DST_PWM_1],
          midi_note,
          increment,
          sync_state_,
          buffer_);
      increment = Lsr24(increment);
      if (engine.patch_.mix_sub_osc_shape < WAVEFORM_SUB_OSC_CLICK) {
        sub_osc.Render(increment, sub_osc_buffer_);
      }
    } else {
      osc_2.Render(
          modulation_destinations_[MOD_DST_PWM_2],
          midi_note,
          increment,
          engine.patch_.osc[0].option == OP_SYNC ? sync_state_ : no_sync_,
          osc2_buffer_);
    }
  }
}

/* static */
inline void Voice::ProcessBlock() {
  // Update the envelopes.
  for (uint8_t i = 0; i < kNumEnvelopes; ++i) {
    envelope_[i].Render();
  }
  
  pitch_value_ += pitch_increment_;
  if ((pitch_increment_ > 0) ^ (pitch_value_ < pitch_target_)) {
    pitch_value_ = pitch_target_;
    pitch_increment_ = 0;
  }

  LoadSources();
  ProcessModulationMatrix();
  UpdateDestinations();
  UpdatePhaseIncrements();
  
  // Skip the oscillator rendering code is the VCA output has converged to
  // a small value.
  if (vca() < 2) {
    for (uint8_t i = 0; i < kAudioBlockSize; ++i) {
      audio_out.Overwrite(128);
    }
    return;
  }
  uint8_t op = engine.patch_.osc[0].option;

  // Mix oscillators.
  switch (op) {
    case OP_RING_MOD:
      for (uint8_t i = 0; i < kAudioBlockSize; ++i) {
        uint8_t ring_mod = SignedSignedMulScale8(
            buffer_[i] + 128,
            osc2_buffer_[i] + 128) + 128;
        buffer_[i] = Mix(
          buffer_[i],
          ring_mod,
          modulation_destinations_[MOD_DST_MIX_BALANCE]);
      }
      break;
    case OP_XOR:
      for (uint8_t i = 0; i < kAudioBlockSize; ++i) {
        buffer_[i] ^= osc2_buffer_[i];
        buffer_[i] ^= modulation_destinations_[MOD_DST_MIX_BALANCE];
      }
      break;
    case OP_FUZZ:
      for (uint8_t i = 0; i < kAudioBlockSize; ++i) {
        buffer_[i] >>= 1;
        buffer_[i] += (osc2_buffer_[i] >> 1);
        buffer_[i] = Mix(
            buffer_[i],
            ResourcesManager::Lookup<uint8_t, uint8_t>(
                wav_res_distortion, buffer_[i]),
            modulation_destinations_[MOD_DST_MIX_BALANCE]);
      }
      break;
    default:
      for (uint8_t i = 0; i < kAudioBlockSize; ++i) {
        buffer_[i] = Mix(
          buffer_[i],
          osc2_buffer_[i],
          modulation_destinations_[MOD_DST_MIX_BALANCE]);
      }
      break;
  }
  
  uint8_t decimate = 1;
  if (op == OP_CRUSH_4) {
    decimate = 4;
  } else if (op == OP_CRUSH_8) {
    decimate = 8;
  }
  
  // Mix-in sub oscillator or transient generator.
  if (engine.patch_.mix_sub_osc_shape < WAVEFORM_SUB_OSC_CLICK) {
    for (uint8_t i = 0; i < kAudioBlockSize; i += decimate) {
      buffer_[i] = Mix(
        buffer_[i],
        sub_osc_buffer_[i],
        modulation_destinations_[MOD_DST_MIX_SUB_OSC]);
    }
  } else {
    transient_generator.Render(
        buffer_,
        modulation_destinations_[MOD_DST_MIX_SUB_OSC] << 1);
  }
  
  // Apply optional bitcrushing.
  if (decimate > 1) {
    for (uint8_t i = 0; i < kAudioBlockSize; ) {
      uint8_t value = buffer_[i++];
      for (uint8_t j = 1; j < decimate; ++j) {
        buffer_[i++] = value;
      }
    }
  }
  
  // Mix with noise and output.
  uint8_t noise = Random::GetByte();
  for (uint8_t i = 0; i < kAudioBlockSize; ++i) {
    noise = (noise * 73) + 1;
    audio_out.Overwrite(Mix(
        buffer_[i],
        noise,
        modulation_destinations_[MOD_DST_MIX_NOISE]));
  }
}

}  // namespace hardware_shruthi
