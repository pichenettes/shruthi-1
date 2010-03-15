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
#include "hardware/shruthi/oscillator.h"
#include "hardware/utils/random.h"
#include "hardware/utils/op.h"

using namespace hardware_utils_op;

namespace hardware_shruthi {

/* extern */
SynthesisEngine engine;

Oscillator<1, FULL> osc_1;
Oscillator<2, LOW_COMPLEXITY> osc_2;
Oscillator<3, SUB_OSCILLATOR> sub_osc;

/* <static> */
uint8_t SynthesisEngine::modulation_sources_[kNumGlobalModulationSources];

uint8_t SynthesisEngine::oscillator_decimation_;

Patch SynthesisEngine::patch_;
Voice SynthesisEngine::voice_[kNumVoices];
VoiceController SynthesisEngine::controller_;
Lfo SynthesisEngine::lfo_[kNumLfos];
uint8_t SynthesisEngine::qux_[2];
uint8_t SynthesisEngine::nrpn_parameter_number_;
uint8_t SynthesisEngine::data_entry_msb_;
uint8_t SynthesisEngine::num_lfo_reset_steps_;
uint8_t SynthesisEngine::lfo_reset_counter_;
uint8_t SynthesisEngine::lfo_to_reset_;

/* </static> */

/* static */
void SynthesisEngine::Init() {
  controller_.Init(voice_, kNumVoices);
  ResetPatch();
  Reset();
  for (uint8_t i = 0; i < kNumVoices; ++i) {
    voice_[i].Init();
  }
}

static const prog_char empty_patch[] PROGMEM = {
    99,
    // Oscillators
    WAVEFORM_SAW, 0, 0, 0,
    WAVEFORM_SQUARE, 24, -12, 12,
    // Mixer
    16, 0, 0, WAVEFORM_SQUARE,
    // Filter
    90, 0, 20, 0,
    // ADSR
    20, 60, 20, 60,
    0, 40, 80, 40,
    // LFO
    LFO_WAVEFORM_TRIANGLE, 96, 0, 1,
    LFO_WAVEFORM_TRIANGLE, 3, 0, 1,
    // Routing
    MOD_SRC_LFO_1, MOD_DST_VCO_1, 0,
    MOD_SRC_LFO_1, MOD_DST_VCO_2, 0,
    MOD_SRC_LFO_1, MOD_DST_PWM_1, 0,
    MOD_SRC_LFO_1, MOD_DST_PWM_2, 0,
    MOD_SRC_LFO_2, MOD_DST_MIX_BALANCE, 0,
    // By default, the resonance tracks the note. This value was empirically
    // obtained and it is not clear whether it depends on the positive supply
    // voltage, and if it varies from chip to chip.
    MOD_SRC_NOTE, MOD_DST_FILTER_CUTOFF, 58,
    MOD_SRC_ENV_2, MOD_DST_VCA, 63,
    MOD_SRC_VELOCITY, MOD_DST_VCA, 16,
    MOD_SRC_PITCH_BEND, MOD_DST_VCO_1_2_FINE, 32,
    MOD_SRC_CV_1, MOD_DST_PWM_1, 0,
    MOD_SRC_CV_2, MOD_DST_PWM_2, 0,
    MOD_SRC_LFO_1, MOD_DST_VCO_1_2_FINE, 16,
    // Name
    'n', 'e', 'w', ' ', ' ', ' ', ' ', ' ', 
    // Keyboard
    0, 0, 0, 0,
    // MIDI
    0, 1, 1, 1,
    // Tempo
    120, 0, 0, 0,
    // Sequence
    0x00, 0x00, 0xff, 0xff, 0xcc, 0xcc, 0x44, 0x44,
    // Note sequence
    60, 0, 0, 0, 60, 0, 0, 0, 60, 0, 60, 0, 60, 61, 63, 58,
    // Pattern size
    16
};

/* static */
void SynthesisEngine::ResetPatch() {
  ResourcesManager::Load(empty_patch, 0, &patch_);
  TouchPatch();
}

/* static */
void SynthesisEngine::NoteOn(uint8_t channel, uint8_t note, uint8_t velocity) {
  // If the note controller is not active, we are not currently playing a
  // sequence, so we retrigger the LFOs.
  if (!controller_.active()) {
    lfo_reset_counter_ = num_lfo_reset_steps_ - 1;
  }
  controller_.NoteOn(note, velocity);
}

/* static */
void SynthesisEngine::NoteOff(uint8_t channel, uint8_t note, uint8_t velocity) {
  controller_.NoteOff(note);
}

/* static */
void SynthesisEngine::ControlChange(uint8_t channel, uint8_t controller,
                                    uint8_t value) {
  switch (controller) {
    case hardware_midi::kModulationWheelMsb:
      modulation_sources_[MOD_SRC_WHEEL] = (value << 1);
      break;
    case hardware_midi::kDataEntryMsb:
      data_entry_msb_ = value << 7;
      break;
    case hardware_midi::kDataEntryLsb:
      value = value | data_entry_msb_;
      if (nrpn_parameter_number_ < sizeof(Patch) - 1) {
        SetParameter(nrpn_parameter_number_, value);
      }
      break;
    case hardware_midi::kPortamentoTimeMsb:
      patch_.sys_portamento = value;
      break;
    case hardware_midi::kRelease:
      patch_.env[1].release = value;
      break;
    case hardware_midi::kAttack:
      patch_.env[1].attack = value;
      break;
    case hardware_midi::kHarmonicIntensity:
      patch_.filter_resonance = value;
      break;
    case hardware_midi::kBrightness:
      patch_.filter_cutoff = value;
      break;
    case hardware_midi::kNrpnLsb:
      nrpn_parameter_number_ = value;
      data_entry_msb_ = 0;
      break;
  }
}

/* static */
uint8_t SynthesisEngine::CheckChannel(uint8_t channel) {
  return patch_.sys_midi_channel == 0 ||
         patch_.sys_midi_channel == (channel + 1);
}

/* static */
void SynthesisEngine::PitchBend(uint8_t channel, uint16_t pitch_bend) {
  modulation_sources_[MOD_SRC_PITCH_BEND] = ShiftRight6(pitch_bend);
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
  patch_.sys_midi_channel = channel + 1;
}

// Enable Omni mode.
/* static */
void SynthesisEngine::OmniModeOn(uint8_t channel) {
  patch_.sys_midi_channel = 0;
}

/* static */
void SynthesisEngine::SysExStart() {
  patch_.SysExReceive(0xf0);
}

/* static */
void SynthesisEngine::SysExByte(uint8_t sysex_byte) {
  patch_.SysExReceive(sysex_byte);
}

/* static */
void SynthesisEngine::SysExEnd() {
  patch_.SysExReceive(0xf7);
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
  controller_.Start();
}

/* static */
void SynthesisEngine::Stop() {
  controller_.Stop();
}

/* static */
void SynthesisEngine::SetParameter(
    uint8_t parameter_index,
    uint8_t parameter_value) {
  patch_.keep_me_at_the_top[parameter_index + 1] = parameter_value;
  if (parameter_index >= PRM_ENV_ATTACK_1 &&
      parameter_index <= PRM_LFO_RATE_2) {
    UpdateModulationIncrements();
  } else if ((parameter_index <= PRM_OSC_SHAPE_2) ||
             (parameter_index == PRM_MIX_SUB_OSC_SHAPE)) {
    UpdateOscillatorAlgorithms();
  } else if (parameter_index >= PRM_ARP_TEMPO) {
    // A copy of those parameters is stored by the note dispatcher/arpeggiator,
    // so any parameter change must be forwarded to it.
    controller_.UpdateArpeggiatorParameters(patch_);
  } else if (parameter_index >= PRM_SYS_MIDI_CHANNEL && 
      parameter_index <= PRM_SYS_MIDI_OUT_CHAIN) {
    // A copy of those parameters are used by the MIDI out dispatcher.
    midi_out_filter.UpdateParameters(patch_);
  }
}

/* static */
void SynthesisEngine::UpdateOscillatorAlgorithms() {
  osc_1.SetupAlgorithm(patch_.osc[0].shape);
  osc_2.SetupAlgorithm(patch_.osc[1].shape);
  sub_osc.SetupAlgorithm(patch_.mix_sub_osc_shape);
}

/* static */
void SynthesisEngine::UpdateModulationIncrements() {
  // Update the LFO increments.
  num_lfo_reset_steps_ = 0;
  lfo_to_reset_ = 0;
  for (uint8_t i = 0; i < kNumLfos; ++i) {
    uint16_t phase_increment;
    // The LFO rates 0 to 15 are translated into a multiple of the step
    // sequencer/arpeggiator step size.
    if (patch_.lfo[i].rate < 16) {
      phase_increment = 65536 / (controller_.estimated_beat_duration() *
                           (1 + patch_.lfo[i].rate) / 4);
      num_lfo_reset_steps_ = UnsignedUnsignedMul(
          num_lfo_reset_steps_ ? num_lfo_reset_steps_ : 1,
          1 + patch_.lfo[i].rate);
      lfo_to_reset_ |= _BV(i);
    } else {
      phase_increment = ResourcesManager::Lookup<uint16_t, uint8_t>(
          lut_res_lfo_increments, patch_.lfo[i].rate - 16);
    }
    uint16_t envelope_increment = ResourcesManager::Lookup<uint16_t, uint8_t>(
        lut_res_lfo_increments, patch_.lfo[i].rate - 16);
    lfo_[i].Update(
        patch_.lfo[i].waveform,
        phase_increment,
        patch_.lfo[i].attack,
        patch_.lfo[i].retrigger);

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
void SynthesisEngine::Control() {
  for (uint8_t i = 0; i < kNumLfos; ++i) {
    modulation_sources_[MOD_SRC_LFO_1 + i] = lfo_[i].Render();
  }
  modulation_sources_[MOD_SRC_RANDOM] = Random::state_msb();
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
      UpdateModulationIncrements();
      for (uint8_t i = 0; i < kNumLfos; ++i) {
        if (lfo_to_reset_ & _BV(i)) {
          lfo_[i].Reset();
        }
      }
      lfo_reset_counter_ = 0;
    }
  }

  // Read/shift the value of the step sequencer.
  modulation_sources_[MOD_SRC_SEQ] = patch_.sequence_step(controller_.step());
  modulation_sources_[MOD_SRC_STEP] = (
      controller_.has_arpeggiator_note() ? 255 : 0);

  for (uint8_t i = 0; i < kNumVoices; ++i) {
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

  controller_.Audio();
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
void Voice::Trigger(uint8_t note, uint8_t velocity, uint8_t legato) {
  if (!legato || !engine.patch_.sys_legato) {
    TriggerEnvelope(ATTACK);
    osc_1.Reset();
    osc_2.Reset();
    sub_osc.Reset();
    // The LFOs are shared by all voices, so if there are other voices still
    // playing there will be a discontinuity. We don't care because we're
    // doing monophonic things anyway (and some pseudo-polysynths/organs are
    // doing the same things).
    engine.TriggerLfos();
    modulation_sources_[MOD_SRC_VELOCITY - kNumGlobalModulationSources] =
        velocity << 1;
  }
  pitch_target_ = static_cast<uint16_t>(note) << 7;
  if (engine.patch_.sys_raga) {
    pitch_target_ += ResourcesManager::Lookup<int8_t, uint8_t>(
        ResourceId(LUT_RES_SCALE_JUST + engine.patch_.sys_raga - 1),
        note % 12);
  }
  // At boot up, or when the note is note played legato and the portamento
  // is in auto mode, do not ramp up the pitch but jump straight to the target
  // pitch.
  if (pitch_value_ == 0 || (!legato && engine.patch_.sys_legato)) {
    pitch_value_ = pitch_target_;
  }
  int16_t delta = pitch_target_ - pitch_value_;
  int32_t increment = ResourcesManager::Lookup<uint16_t, uint8_t>(
      lut_res_env_portamento_increments,
      engine.patch_.sys_portamento);
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
  if (last_note_ != 0) {
    midi_out_filter.NoteKilled(last_note_);
  }
  midi_out_filter.NoteTriggered(note, velocity);
  last_note_ = note;
}

/* static */
void Voice::Control() {
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
      envelope_[0].stage() >= RELEASE ? 0 : 255;

  modulation_destinations_[MOD_DST_VCA] = 255;

  // Load and scale to 0-16383 the initial value of each modulated parameter.
  dst[MOD_DST_FILTER_CUTOFF] = engine.patch_.filter_cutoff << 7;
  dst[MOD_DST_PWM_1] = engine.patch_.osc[0].parameter << 7;
  dst[MOD_DST_PWM_2] = engine.patch_.osc[1].parameter << 7;
  dst[MOD_DST_VCO_1_2_FINE] = dst[MOD_DST_VCO_2] = dst[MOD_DST_VCO_1] = 8192;
  dst[MOD_DST_MIX_BALANCE] = engine.patch_.mix_balance << 8;
  dst[MOD_DST_MIX_NOISE] = engine.patch_.mix_noise << 8;
  dst[MOD_DST_MIX_SUB_OSC] = engine.patch_.mix_sub_osc << 8;
  dst[MOD_DST_FILTER_RESONANCE] = engine.patch_.filter_resonance << 8;
  dst[MOD_DST_CV_1] = 0;
  dst[MOD_DST_CV_2] = 0;
  dst[MOD_DST_2_BITS] = 0;

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
          source == MOD_SRC_NOTE) {
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

  modulation_destinations_[MOD_DST_MIX_BALANCE] = ShiftRight6(
      dst[MOD_DST_MIX_BALANCE]);
  modulation_destinations_[MOD_DST_MIX_NOISE] = dst[MOD_DST_MIX_NOISE] >> 8;
  modulation_destinations_[MOD_DST_MIX_SUB_OSC] = dst[MOD_DST_MIX_SUB_OSC] >> 7;

  // Update the oscillator parameters.
  for (uint8_t i = 0; i < kNumOscillators; ++i) {
    int16_t pitch = pitch_value_;
    // -24 / +24 semitones by the range controller.
    if (engine.patch_.osc[i].shape == WAVEFORM_FM) {
      osc_1.UpdateSecondaryParameter(engine.patch_.osc[i].range + 12);
    } else {
      pitch += static_cast<int16_t>(engine.patch_.osc[i].range) << 7;
    }
    // -24 / +24 semitones by the main octave controller.
    pitch += static_cast<int16_t>(engine.patch_.sys_octave) * kOctave;
    if (i == 1) {
      // 0 / +1 semitones by the detune option for oscillator 2.
      pitch += engine.patch_.osc[1].option;
    }
    // -16 / +16 semitones by the routed modulations.
    pitch += (dst[MOD_DST_VCO_1 + i] - 8192) >> 2;
    // -4 / +4 semitones by the vibrato and pitch bend.
    pitch += (dst[MOD_DST_VCO_1_2_FINE] - 8192) >> 4;
    // -1 / +1 semitones by master tuning.
    pitch += engine.patch_.sys_master_tuning;

    // Wrap pitch to a reasonable range.
    while (pitch < kLowestNote) {
      pitch += kOctave;
    }
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
    uint8_t midi_note = pitch >>= 7;
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
void Voice::Audio() {
  if (dead_) {
    signal_ = 128;
    return;
  }

  uint8_t osc_2_signal = osc_2.Render();
  uint8_t mix = osc_1.Render();
  uint8_t op = engine.patch_.osc[0].option;
  if (op == RING_MOD) {
    mix = SignedSignedMulScale8(mix + 128, osc_2_signal + 128) + 128;
  } else if (op == XOR) {
    mix ^= osc_2_signal;
    mix += modulation_destinations_[MOD_DST_MIX_BALANCE];
  } else {
    mix = Mix(
        mix,
        osc_2_signal,
        modulation_destinations_[MOD_DST_MIX_BALANCE]);
    // If the phase of oscillator 1 has wrapped and if sync is enabled, reset
    // the phase of the second oscillator.
    if (op == SYNC) {
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
  }

  // Disable sub oscillator and noise when the "vowel" waveform is used - it is
  // just too costly.
  if (engine.patch_.osc[0].shape != WAVEFORM_VOWEL) {
    mix = Mix(
        mix,
        sub_osc.Render(),
        modulation_destinations_[MOD_DST_MIX_SUB_OSC]);
    mix = Mix(
        mix,
        Random::state_msb(),
        modulation_destinations_[MOD_DST_MIX_NOISE]);
  }

  signal_ = mix;
}

}  // namespace hardware_shruthi
