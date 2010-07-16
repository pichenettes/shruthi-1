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
uint8_t SynthesisEngine::modulation_sources_[kNumGlobalModulationSources];

uint8_t SynthesisEngine::oscillator_decimation_;

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
      wav_res_low_res_wavetable_2,
      user_wavetable,
      kUserWavetableSize);
}

static const prog_char init_patch[] PROGMEM = {
    // Oscillators
    WAVEFORM_SAW, 0, 0, 0,
    WAVEFORM_SQUARE, 16, -12, 12,
    // Mixer
    32, 0, 0, WAVEFORM_SUB_OSC_SQUARE,
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
    MOD_SRC_CV_1, MOD_DST_PWM_1, 0,
    MOD_SRC_CV_2, MOD_DST_PWM_2, 0,
    // By default, the resonance tracks the note. Tracking works best when the
    // transistors are thermically coupled.
    MOD_SRC_NOTE, MOD_DST_FILTER_CUTOFF, 63,
    MOD_SRC_ENV_2, MOD_DST_VCA, 63,
    MOD_SRC_VELOCITY, MOD_DST_VCA, 16,
    MOD_SRC_PITCH_BEND, MOD_DST_VCO_1_2_COARSE, 32,
    MOD_SRC_LFO_1, MOD_DST_VCO_1_2_COARSE, 16,
    // Name
    'i', 'n', 'i', 't', ' ', ' ', ' ', ' ',
    // Performance page assignments.
    1, 0,
    PRM_FILTER_CUTOFF, 0,
    PRM_FILTER_ENV, 0,
    25, 0,
    // Extra padding for future improvements.
    'p', 'a', 'd', 'd', 'i', 'n', 'g', '!'
};

static const prog_char init_sequence[] PROGMEM = {
    // Sequencer
    SEQUENCER_MODE_STEP, 120, 0, FLOW_NORMAL,
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
    12, 0, 1, 0,
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
      return;
    }
    // If the note controller is not active, we are not currently playing a
    // sequence, so we retrigger the LFOs.
    if (!controller_.active()) {
      lfo_reset_counter_ = num_lfo_reset_steps_ - 1;
    }
    controller_.NoteOn(note, velocity);
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
      return;
    }
    controller_.NoteOff(note);
  }
}

/* static */
void SynthesisEngine::ControlChange(uint8_t channel, uint8_t controller,
                                    uint8_t value) {
  uint8_t editing_controller = 0;
  if (controller >= hardware_midi::kAssignableCcA &&
      controller <= hardware_midi::kAssignableCcD) {
    modulation_sources_[MOD_SRC_CC_A + controller -
        hardware_midi::kAssignableCcA] = value << 1;
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
        modulation_sources_[MOD_SRC_WHEEL] = value << 1;
        break;
      case hardware_midi::kDataEntryMsb:
        data_entry_msb_ = value << 7;
        break;
      case hardware_midi::kDataEntryLsb:
        value |= data_entry_msb_;
        if (nrpn_parameter_number_ != 255) {
          dirty_ = 1;
          const ParameterDefinition& p = (
              ParameterDefinitions::parameter_definition(
                  nrpn_parameter_number_));
          if (p.unit == UNIT_INT8) {
            int8_t signed_value = static_cast<int8_t>(value);
            if (signed_value >= static_cast<int8_t>(p.min_value) &&
                signed_value <= static_cast<int8_t>(p.max_value)) {
              SetParameter(nrpn_parameter_number_, value);
            }
          } else {
            if (value >= p.min_value && value <= p.max_value) {
              SetParameter(nrpn_parameter_number_, value);
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
        SetParameter(PRM_ENV_RELEASE_2, value);
        break;
      case hardware_midi::kAttack:
        SetParameter(PRM_ENV_ATTACK_2, value);
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
    const ParameterDefinition& parameter = (
        ParameterDefinitions::parameter_definition(controller));
    SetParameter(parameter.id, ParameterDefinitions::Scale(parameter, value));
  }
}

/* static */
void SynthesisEngine::PitchBend(uint8_t channel, uint16_t pitch_bend) {
  uint8_t value = ShiftRight6(pitch_bend);
  modulation_sources_[MOD_SRC_PITCH_BEND] = value;
}

/* static */
void SynthesisEngine::Aftertouch(uint8_t channel, uint8_t note,
                                 uint8_t velocity) {
                                   
  modulation_sources_[MOD_SRC_AFTERTOUCH] = velocity << 1;
}

/* static */
void SynthesisEngine::Aftertouch(uint8_t channel, uint8_t velocity) {
  modulation_sources_[MOD_SRC_AFTERTOUCH] = velocity << 1;
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
  modulation_sources_[MOD_SRC_PITCH_BEND] = 128;
  modulation_sources_[MOD_SRC_WHEEL] = 0;
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
  memset(modulation_sources_, 0, kNumGlobalModulationSources);
  modulation_sources_[MOD_SRC_PITCH_BEND] = 128;
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
void SynthesisEngine::SetParameter(
    uint8_t parameter_index,
    uint8_t parameter_value) {
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
  midi_dispatcher.SendParameter(parameter_index, parameter_value);
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
void SynthesisEngine::Control() {
  for (uint8_t i = 0; i < kNumLfos; ++i) {
    modulation_sources_[MOD_SRC_LFO_1 + i] = lfo_[i].Render(
        sequencer_settings_);
  }
  modulation_sources_[MOD_SRC_NOISE] = Random::state_msb();
  modulation_sources_[MOD_SRC_OFFSET] = 255;

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
  modulation_sources_[MOD_SRC_SEQ] = (
      sequencer_settings_.steps[step].controller() << 4);
  step &= 0x7;
  modulation_sources_[MOD_SRC_SEQ_1] = (
      sequencer_settings_.steps[step].controller() << 4);
  modulation_sources_[MOD_SRC_SEQ_2] = (
      sequencer_settings_.steps[step + 8].controller() << 4);
  modulation_sources_[MOD_SRC_STEP] = (
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
          patch_.lfo[j].retrigger_mode == LFO_MODE_MASTER &&
          (j != 1 || voice_[i].mutable_envelope(j)->stage() <= RELEASE_1)) {
        voice_[i].TriggerEnvelope(j, ATTACK);
      }
    }
    voice_[i].Control();
  }
}

/* static */
void SynthesisEngine::Audio() {
  // Tick the noise generator.
  oscillator_decimation_ = (oscillator_decimation_ + 1) & 3;
  if (!oscillator_decimation_) {
    Random::Update();
  }
  for (uint8_t i = 0; i < kNumVoices; ++i) {
    voice_[i].Audio();
  }
}

/* <static> */
Envelope Voice::envelope_[kNumEnvelopes];
uint8_t Voice::dead_;
int16_t Voice::pitch_increment_;
int16_t Voice::pitch_target_;
int16_t Voice::pitch_value_;
uint8_t Voice::modulation_sources_[kNumVoiceModulationSources];
int8_t Voice::modulation_destinations_[kNumModulationDestinations];
uint8_t Voice::signal_;
uint8_t Voice::osc1_phase_msb_;
uint8_t Voice::last_note_;
/* </static> */

/* static */
void Voice::Init() {
  pitch_value_ = 0;
  last_note_ = 0;
  signal_ = 128;
  for (uint8_t i = 0; i < kNumEnvelopes; ++i) {
    envelope_[i].Init();
  }
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
      pitch_target_ = (static_cast<uint16_t>(note) << 7) + pitch_shift;
    } else {
      if (legato) {
        legato = 255;
      }
    }
  } else {
    pitch_target_ = (static_cast<uint16_t>(note) << 7);
  }
  if (!legato || (!engine.system_settings_.legato && legato != 255)) {
    TriggerEnvelope(ATTACK);
    // The LFOs are shared by all voices, so if there are other voices still
    // playing there will be a discontinuity. We don't care because we're
    // doing monophonic things anyway (and some pseudo-polysynths/organs are
    // doing the same things).
    engine.TriggerLfos();
    transient_generator.Trigger();
    modulation_sources_[MOD_SRC_VELOCITY - kNumGlobalModulationSources] =
        velocity << 1;
    modulation_sources_[MOD_SRC_RANDOM - kNumGlobalModulationSources] =
        Random::state_msb();
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
inline void Voice::Control() {
  // Update the envelopes.
  dead_ = 1;
  for (uint8_t i = 0; i < kNumEnvelopes; ++i) {
    envelope_[i].Render();
    dead_ = dead_ && envelope_[i].dead();
  }

  pitch_value_ += pitch_increment_;
  if ((pitch_increment_ > 0) ^ (pitch_value_ < pitch_target_)) {
    pitch_value_ = pitch_target_;
    pitch_increment_ = 0;
  }

  // Used temporarily, then scaled to modulation_destinations_. This does not
  // need to be static, but if allocated on the heap, we get many push/pops,
  // and the resulting code is slower.
  static int16_t dst[kNumModulationDestinations];

  uint8_t has_2_bits_cv = 0;

  // Rescale the value of each modulation sources. Envelopes are in the
  // 0-16383 range ; just like pitch. All are scaled to 0-255.
  modulation_sources_[MOD_SRC_ENV_1 - kNumGlobalModulationSources] = 
      ShiftRight6(envelope_[0].value());
  modulation_sources_[MOD_SRC_ENV_2 - kNumGlobalModulationSources] = 
      ShiftRight6(envelope_[1].value());
  modulation_sources_[MOD_SRC_NOTE - kNumGlobalModulationSources] =
      ShiftRight6(pitch_value_);
  modulation_sources_[MOD_SRC_GATE - kNumGlobalModulationSources] =
      envelope_[0].stage() >= RELEASE_1 ? 0 : 255;

  modulation_destinations_[MOD_DST_VCA] = 255;
  modulation_sources_[MOD_SRC_AUDIO - kNumGlobalModulationSources] = signal_;

  // Load and scale to 0-16383 the initial value of each modulated parameter.
  dst[MOD_DST_FILTER_CUTOFF] = engine.patch_.filter_cutoff << 7;
  dst[MOD_DST_FILTER_RESONANCE] = engine.patch_.filter_resonance << 8;
  dst[MOD_DST_PWM_1] = engine.patch_.osc[0].parameter << 7;
  dst[MOD_DST_PWM_2] = engine.patch_.osc[1].parameter << 7;
  dst[MOD_DST_VCO_1_2_COARSE] = dst[MOD_DST_VCO_1_2_FINE] =
      dst[MOD_DST_VCO_2] = dst[MOD_DST_VCO_1] = 8192;
  dst[MOD_DST_VCO_2] = dst[MOD_DST_VCO_1] = 8192;
  dst[MOD_DST_MIX_BALANCE] = engine.patch_.mix_balance << 8;
  dst[MOD_DST_MIX_NOISE] = engine.patch_.mix_noise << 8;
  dst[MOD_DST_MIX_SUB_OSC] = engine.patch_.mix_sub_osc << 8;
  dst[MOD_DST_CV_1] = 0;
  dst[MOD_DST_CV_2] = 0;
  dst[MOD_DST_2_BITS] = 0;
  dst[MOD_DST_LFO_1] = 8192;
  dst[MOD_DST_LFO_2] = 8192;
  
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
          engine.modulation_sources_[MOD_SRC_WHEEL]);
    }
    uint8_t source = engine.patch_.modulation_matrix.modulation[i].source;
    uint8_t destination =
        engine.patch_.modulation_matrix.modulation[i].destination;
    uint8_t source_value;

    if (source < kNumGlobalModulationSources) {
      // Global sources, read from the engine.
      source_value = engine.modulation_sources_[source];
    } else {
      // Voice specific sources, read from the voice.
      source_value = modulation_sources_[source - kNumGlobalModulationSources];
    }
    if (destination == MOD_DST_2_BITS) {
      has_2_bits_cv = 1;
    }
    if (destination != MOD_DST_VCA) {
      int16_t modulation = dst[destination];
      modulation += SignedUnsignedMul(amount, source_value);
      // For those sources, use relative modulation.
      if (source <= MOD_SRC_LFO_2 ||
          source == MOD_SRC_PITCH_BEND ||
          source == MOD_SRC_NOTE ||
          source == MOD_SRC_AUDIO) {
        modulation -= amount << 7;
      }
      dst[destination] = Clip(modulation, 0, 16383);
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
  // Hardcoded filter modulations.
  dst[MOD_DST_FILTER_CUTOFF] = Clip(
      dst[MOD_DST_FILTER_CUTOFF] + SignedUnsignedMul(
          engine.patch_.filter_env,
          modulation_sources_[MOD_SRC_ENV_1 - kNumGlobalModulationSources]),
      0,
      16383);
  dst[MOD_DST_FILTER_CUTOFF] = Clip(
      dst[MOD_DST_FILTER_CUTOFF] + SignedUnsignedMul(
          engine.patch_.filter_lfo,
          engine.modulation_sources_[MOD_SRC_LFO_2]) -
      (engine.patch_.filter_lfo << 7),
      0,
      16383);
  
  // Store in memory all the updated parameters.
  modulation_destinations_[MOD_DST_FILTER_CUTOFF] = ShiftRight6(
      dst[MOD_DST_FILTER_CUTOFF]);

  modulation_destinations_[MOD_DST_FILTER_RESONANCE] = ShiftRight6(
      dst[MOD_DST_FILTER_RESONANCE]);

  modulation_destinations_[MOD_DST_CV_1] = ShiftRight6(
        dst[MOD_DST_CV_1]);
  modulation_destinations_[MOD_DST_CV_2] = ShiftRight6(
        dst[MOD_DST_CV_2]);
  if (has_2_bits_cv) {
    modulation_destinations_[MOD_DST_2_BITS] = static_cast<uint8_t>(
        dst[MOD_DST_2_BITS] >> 8);
  } else {
    modulation_destinations_[MOD_DST_2_BITS] = 0xff;
  }
  modulation_destinations_[MOD_DST_PWM_1] = dst[MOD_DST_PWM_1] >> 7;
  modulation_destinations_[MOD_DST_PWM_2] = dst[MOD_DST_PWM_2] >> 7;
  modulation_destinations_[MOD_DST_LFO_1] = dst[MOD_DST_LFO_1] >> 8;
  modulation_destinations_[MOD_DST_LFO_2] = dst[MOD_DST_LFO_2] >> 8;
  
  modulation_destinations_[MOD_DST_MIX_BALANCE] = ShiftRight6(
      dst[MOD_DST_MIX_BALANCE]);
  
  modulation_destinations_[MOD_DST_MIX_NOISE] = dst[MOD_DST_MIX_NOISE] >> 8;
  modulation_destinations_[MOD_DST_MIX_SUB_OSC] = dst[MOD_DST_MIX_SUB_OSC] >> 7;
  
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
      pitch += static_cast<int16_t>(engine.patch_.osc[i].range) << 7;
    }
    // -24 / +24 semitones by the main octave controller.
    pitch += static_cast<int16_t>(engine.system_settings_.octave) * kOctave;
    if (i == 1) {
      // 0 / +1 semitones by the detune option for oscillator 2.
      pitch += engine.patch_.osc[1].option;
    }
    // -16 / +16 semitones by the routed modulations.
    pitch += (dst[MOD_DST_VCO_1 + i] - 8192) >> 2;
    // -4 / +4 semitones by the vibrato and pitch bend.
    pitch += (dst[MOD_DST_VCO_1_2_COARSE] - 8192) >> 4;
    // -1 / +1 semitones by the vibrato and pitch bend.
    pitch += (dst[MOD_DST_VCO_1_2_FINE] - 8192) >> 7;
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
    uint16_t increment = ResourcesManager::Lookup<uint16_t, uint16_t>(
        lut_res_oscillator_increments, ref_pitch >> 1);
    // Divide the pitch increment by the number of octaves we had to transpose
    // to get a value in the lookup table.
    increment >>= num_shifts;

    // Now the oscillators can recompute all their internal variables!
    int8_t midi_note = pitch >> 7;
    if (midi_note < 12) {
      midi_note = 12;
    }
    if (i == 0) {
      osc_1.Update(
          modulation_destinations_[MOD_DST_PWM_1],
          midi_note,
          increment);
      sub_osc.Update(
          0,
          midi_note - 12,
          increment >> 1);
    } else {
      osc_2.Update(
          modulation_destinations_[MOD_DST_PWM_2],
          midi_note,
          increment);
    }
  }
}

/* static */
inline void Voice::Audio() {
  uint8_t osc_2_signal = osc_2.Render();
  uint8_t mix = osc_1.Render();
  switch (engine.patch_.osc[0].option) {
    case OP_SYNC:
      {
        uint8_t phase_msb = osc_1.phase() >> 8;
        if (phase_msb < osc1_phase_msb_) {
          osc_2.ResetPhase();
        }
        // Store the phase of the oscillator to check later whether the phase has
        // been wrapped. Because the phase increment is likely to be below
        // 65536 - 256, we can use the most significant byte only to detect
        // wrapping.
        osc1_phase_msb_ = phase_msb;
      }
      // Fall through!
    case OP_SUM:
      mix = Mix(
          mix,
          osc_2_signal,
          modulation_destinations_[MOD_DST_MIX_BALANCE]);
      break;
    case OP_RING_MOD:
      mix = SignedSignedMulScale8(mix + 128, osc_2_signal + 128) + 128;
      break;
    case OP_XOR:
      mix ^= osc_2_signal;
      mix ^= modulation_destinations_[MOD_DST_MIX_BALANCE];
      break;
    case OP_WAVESHAPPER:
      mix >>= 1;
      mix += osc_2_signal >> 1;
      mix = Mix(
          mix,
          ResourcesManager::Lookup<uint8_t, uint8_t>(
              wav_res_distortion, mix),
          modulation_destinations_[MOD_DST_MIX_BALANCE]);
  }
  // Disable sub oscillator and noise when the "vowel" waveform is used - it is
  // just too costly.
  if (engine.patch_.osc[0].shape != WAVEFORM_VOWEL) {
    if (engine.patch_.mix_sub_osc_shape <= WAVEFORM_SUB_OSC_TRIANGLE) {
      mix = Mix(
          mix,
          sub_osc.Render(),
          modulation_destinations_[MOD_DST_MIX_SUB_OSC]);
    } else {
      uint8_t amplitude = MulScale8(
          transient_generator.gain(),
          modulation_destinations_[MOD_DST_MIX_SUB_OSC] << 1);
      mix = Mix(
          mix,
          transient_generator.Render(),
          amplitude);
    }
    mix = Mix(
        mix,
        Random::state_msb(),
        modulation_destinations_[MOD_DST_MIX_NOISE]);
  }
  signal_ = mix;
}

}  // namespace hardware_shruthi
