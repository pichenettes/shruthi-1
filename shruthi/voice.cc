// Copyright 2009 Emilie Gillet.
//
// Author: Emilie Gillet (emilie.o.gillet@gmail.com)
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
// Main synthesis part.

#include "shruthi/voice.h"

#include <string.h>

#include "avrlib/resources_manager.h"
#include "shruthi/audio_out.h"
#include "shruthi/midi_dispatcher.h"
#include "shruthi/oscillator.h"
#include "shruthi/parameter.h"
#include "shruthi/storage.h"
#include "shruthi/sub_oscillator.h"
#include "shruthi/transient_generator.h"
#include "avrlib/random.h"
#include "avrlib/op.h"

using namespace avrlib;

namespace shruthi {

Oscillator osc_1;
Oscillator osc_2;
SubOscillator sub_osc;
TransientGenerator transient_generator;

/* <static> */
Envelope Voice::envelope_[kNumEnvelopes];
uint8_t Voice::disable_envelope_auto_retriggering_[kNumEnvelopes];
uint8_t Voice::gate_;
int16_t Voice::pitch_increment_;
int16_t Voice::pitch_target_;
int16_t Voice::pitch_value_;
int16_t Voice::pitch_bass_note_;
uint8_t Voice::modulation_sources_[kNumModulationSources];
int8_t Voice::modulation_destinations_[kNumModulationDestinations];
int16_t Voice::dst_[kNumModulationDestinations];
uint8_t Voice::buffer_[kAudioBlockSize];
uint8_t Voice::osc2_buffer_[kAudioBlockSize];
uint8_t Voice::sync_state_[kAudioBlockSize];
uint8_t Voice::no_sync_[kAudioBlockSize];
uint8_t Voice::dummy_sync_state_[kAudioBlockSize];
uint8_t Voice::trigger_count_;
uint8_t Voice::volume_;
/* </static> */

/* static */
void Voice::Init() {
  pitch_value_ = 60 << 7;
  for (uint8_t i = 0; i < kNumEnvelopes; ++i) {
    envelope_[i].Init();
  }
  memset(no_sync_, 0, kAudioBlockSize);
  
  // Fill the "user" wavetable with data from an existing wavetable.
  ResourcesManager::Load(
      wav_res_waves,
      user_wavetable,
      kUserWavetableSize);
  NoteOff();
  
  ResetAllControllers();
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
void Voice::PitchBend(uint16_t value) {
  modulation_sources_[MOD_SRC_PITCH_BEND] = U14ShiftRight6(value);
}

/* static */
void Voice::ResetAllControllers() {
  modulation_sources_[MOD_SRC_VALUE_4] = 4;
  modulation_sources_[MOD_SRC_VALUE_8] = 8;
  modulation_sources_[MOD_SRC_VALUE_16] = 16;
  modulation_sources_[MOD_SRC_VALUE_32] = 32;
  modulation_sources_[MOD_SRC_PITCH_BEND] = 128;
  modulation_sources_[MOD_SRC_WHEEL] = 0;
  modulation_sources_[MOD_SRC_OFFSET] = 255;
  volume_ = 255;
}

/* static */
void Voice::NoteOn(
    uint16_t pitch,
    uint8_t velocity,
    uint8_t portamento,
    bool trigger) {
  if (pitch == 0) {
    return;
  }
  
  pitch_target_ = pitch;
  if (trigger || pitch_value_ == 0) {
    for (uint8_t i = 0; i < kNumEnvelopes; ++i) {
      if (!disable_envelope_auto_retriggering_[i]) {
        envelope_[i].Trigger(ATTACK);
      }
    }
    ++trigger_count_;
    gate_ = 255;
    // The LFOs are shared by all voices, so if there are other voices still
    // playing there will be a discontinuity. We don't care because we're
    // doing monophonic things anyway (and some pseudo-polysynths/organs are
    // doing the same things).
    part.TriggerLfos();
    transient_generator.Trigger();
    modulation_sources_[MOD_SRC_VELOCITY] = velocity << 1;
    modulation_sources_[MOD_SRC_RANDOM] = Random::state_msb();
    osc_1.Reset();
    osc_2.Reset();
  }
  
  if (portamento) {
    int16_t delta = pitch_target_ - pitch_value_;
    int32_t increment = ResourcesManager::Lookup<uint16_t, uint8_t>(
        lut_res_env_portamento_increments,
        portamento);
    pitch_increment_ = (delta * increment) >> 16;
    if (pitch_increment_ == 0) {
      if (delta < 0) {
        pitch_increment_ = -1;
      } else {
        pitch_increment_ = 1;
      }
    }
  } else {
    pitch_value_ = pitch_target_;
    pitch_increment_ = 1;
  }
}

/* static */
void Voice::NoteOff() {
  gate_ = 0;
  TriggerEnvelope(RELEASE);
}

/* static */
inline void Voice::LoadSources() {
  static uint8_t ops[8];
  
  // Rescale the value of each modulation sources. Envelopes are in the
  // 0-16383 range ; just like pitch. All are scaled to 0-255.
  modulation_sources_[MOD_SRC_ENV_1] = envelope_[0].Render();
  modulation_sources_[MOD_SRC_ENV_2] = envelope_[1].Render();
  modulation_sources_[MOD_SRC_NOTE] = U14ShiftRight6(pitch_value_);
  modulation_sources_[MOD_SRC_GATE] = gate_;
  modulation_sources_[MOD_SRC_AUDIO] = buffer_[0];
  
  // Apply the modulation operators
  for (uint8_t i = 0; i < 2; ++i) {
    if (!part.patch_.ops_[i].op) {
      continue;
    }
    uint8_t x = part.patch_.ops_[i].operands[0];
    uint8_t y = part.patch_.ops_[i].operands[1];
    x = modulation_sources_[x];
    y = modulation_sources_[y];
    uint8_t op = part.patch_.ops_[i].op;
    if (op <= OP_CV_LE) {
      if (x > y) {
        ops[3] = x;  ops[6] = 255;
        ops[4] = y;  ops[7] = 0;
      } else {
        ops[3] = y;  ops[6] = 0;
        ops[4] = x;  ops[7] = 255;
      }
      ops[1] = (x >> 1) + (y >> 1);
      ops[2] = U8U8MulShift8(x, y);
      ops[5] = x ^ y;
      modulation_sources_[MOD_SRC_OP_1 + i] = ops[op];
    } else if (op == OP_CV_QUANTIZE) {
      uint8_t mask = 0;
      while (y >>= 1) {
        mask >>= 1;
        mask |= 0x80;
      }
      modulation_sources_[MOD_SRC_OP_1 + i] = x & mask;
    } else if (op == OP_CV_LAG_PROCESSOR) {
      y >>= 2;
      ++y;
      uint16_t v = U8U8Mul(256 - y, modulation_sources_[MOD_SRC_OP_1 + i]);
      v += U8U8Mul(y, x);
      modulation_sources_[MOD_SRC_OP_1 + i] = v >> 8;
    }
  }

  modulation_destinations_[MOD_DST_VCA] = volume_;
  
  // Load and scale to 0-16383 the initial value of each modulated parameter.
  dst_[MOD_DST_FILTER_CUTOFF] = U8U8Mul(
      part.patch_.filter_cutoff, 128);

  dst_[MOD_DST_PWM_1] = U8U8Mul(part.patch_.osc[0].parameter, 128);
  dst_[MOD_DST_PWM_2] = U8U8Mul(part.patch_.osc[1].parameter, 128);

  dst_[MOD_DST_VCO_1_2_COARSE] = dst_[MOD_DST_VCO_1_2_FINE] = 8192;
  dst_[MOD_DST_VCO_1] = dst_[MOD_DST_VCO_2] = 8192;
  dst_[MOD_DST_LFO_1] = dst_[MOD_DST_LFO_2] = 8192;
  dst_[MOD_DST_TRIGGER_ENV_1] = 0;
  dst_[MOD_DST_TRIGGER_ENV_2] = 0;

  dst_[MOD_DST_FILTER_RESONANCE] = part.patch_.filter_resonance << 8;
  dst_[MOD_DST_MIX_BALANCE] = part.patch_.mix_balance << 8;
  dst_[MOD_DST_MIX_NOISE] = part.patch_.mix_noise << 8;
  dst_[MOD_DST_MIX_SUB_OSC] = part.patch_.mix_sub_osc << 8;

  dst_[MOD_DST_ATTACK] = 8192;
  int16_t* envelope_parameters = &dst_[MOD_DST_ATTACK_1];
  for (uint8_t i = 0; i < kNumEnvelopes; ++i) {
    *envelope_parameters++ = U8U8Mul(part.patch_.env[i].attack, 128);
    *envelope_parameters++ = U8U8Mul(part.patch_.env[i].decay, 128);
    *envelope_parameters++ = U8U8Mul(part.patch_.env[i].sustain, 128);
    *envelope_parameters++ = U8U8Mul(part.patch_.env[i].release, 128);
  }
  dst_[MOD_DST_CV_1] = 0;
  dst_[MOD_DST_CV_2] = 0;
  if (part.system_settings_.expansion_filter_board >= FILTER_BOARD_SSM) {
    dst_[MOD_DST_CV_1] = U8U8Mul(
        part.patch_.filter_cutoff_2, 128);
    dst_[MOD_DST_CV_2] = part.patch_.filter_resonance_2 << 8;
  }
}

/* static */
void Voice::ControlChange(uint8_t controller, uint8_t value) {
  value <<= 1;
  switch (controller) {
    case midi::kAssignableCcA:
      modulation_sources_[MOD_SRC_CC_A] = value;
      break;
    case midi::kAssignableCcB:
      modulation_sources_[MOD_SRC_CC_B] = value;
      break;
    case midi::kModulationWheelJoystickMsb:
      modulation_sources_[MOD_SRC_CC_C] = value;
      break;
    case midi::kFootPedalMsb:
      modulation_sources_[MOD_SRC_CC_D] = value;
      break;
    case midi::kModulationWheelMsb:
      modulation_sources_[MOD_SRC_WHEEL] = value;
      break;
    case midi::kVolume:
      volume_ = value;
      break;
  }
}

/* static */
inline void Voice::ProcessModulationMatrix() {
  // Apply the modulations in the modulation matrix.
  for (uint8_t i = 0; i < kNumEnvelopes; ++i) {
    disable_envelope_auto_retriggering_[i] = 0;
  }
  for (uint8_t i = 0; i < kModulationMatrixSize; ++i) {
    int8_t amount = part.patch_.modulation_matrix.modulation[i].amount;
    if (!amount) {
      continue;
    }

    // The rate of the last modulation is adjusted by the wheel.
    if (i == kModulationMatrixSize - 1) {
      amount = S8U8MulShift8(
          amount, modulation_sources_[MOD_SRC_WHEEL]);
    }
    uint8_t source = part.patch_.modulation_matrix.modulation[i].source;
    uint8_t destination =
        part.patch_.modulation_matrix.modulation[i].destination;
    if (destination >= MOD_DST_TRIGGER_ENV_1 &&
        destination <= MOD_DST_TRIGGER_ENV_2) {
      disable_envelope_auto_retriggering_[destination - \
          MOD_DST_TRIGGER_ENV_1] = 1;
    }
    uint8_t source_value;

    source_value = modulation_sources_[source];
    if (destination != MOD_DST_VCA) {
      int16_t modulation = dst_[destination];
      // For those sources, use relative modulation.
      if (source <= MOD_SRC_LFO_2 ||
          source == MOD_SRC_PITCH_BEND ||
          source == MOD_SRC_NOTE ||
          source == MOD_SRC_AUDIO) {
        modulation += S8S8Mul(amount, source_value + 128);
      } else {
        modulation += S8U8Mul(amount, source_value);
      }
      dst_[destination] = S16ClipU14(modulation);
    } else {
      // The VCA modulation is multiplicative, not additive. Yet another
      // Special case :(.
      if (amount < 0) {
        amount = -amount;
        source_value = 255 - source_value;
      }
      if (amount != 63) {
        source_value = U8Mix(255, source_value, amount << 2);
      }
      modulation_destinations_[MOD_DST_VCA] = U8U8MulShift8(
            modulation_destinations_[MOD_DST_VCA],
            source_value);
    }
  }
}

/* static */
inline void Voice::UpdateDestinations() {
  // Hardcoded filter modulations.
  // By default, the resonance tracks the note. Tracking works best when the
  // transistors are thermically coupled. You can disable tracking by applying
  // a negative modulation from NOTE to CUTOFF.
  uint16_t cutoff = dst_[MOD_DST_FILTER_CUTOFF];
  if (part.patch_.osc[0].option != OP_DUO) {
    if (part.system_settings().expansion_filter_board == FILTER_BOARD_PVK) {
      cutoff = S16ClipU14(cutoff + pitch_value_ - 8192 + (16 << 7));
    } else {
      cutoff = S16ClipU14(cutoff + pitch_value_ - 8192);
    }
  }
  cutoff = S16ClipU14(cutoff + S8U8Mul(part.patch_.filter_env,
      modulation_sources_[MOD_SRC_ENV_1]));
  cutoff = S16ClipU14(cutoff + S8S8Mul(part.patch_.filter_lfo,
      modulation_sources_[MOD_SRC_LFO_2] + 128));

  // If the secondary filter is linked to the first one, offset its cutoff
  // by the cutoff value of the first filter.
  if (part.system_settings_.expansion_filter_board == FILTER_BOARD_SVF &&
      part.patch_.filter_1_mode_ >= FILTER_MODE_LP_COUPLED) {
    dst_[MOD_DST_CV_1] = S16ClipU14(dst_[MOD_DST_CV_1] + cutoff - 8192);
  }
  
  // Store in memory all the updated parameters.
  modulation_destinations_[MOD_DST_FILTER_CUTOFF] = U14ShiftRight6(cutoff);
  modulation_destinations_[MOD_DST_FILTER_RESONANCE] = U14ShiftRight6(
      dst_[MOD_DST_FILTER_RESONANCE]);

  modulation_destinations_[MOD_DST_CV_1] = U14ShiftRight6(dst_[MOD_DST_CV_1]);
  modulation_destinations_[MOD_DST_CV_2] = U14ShiftRight6(dst_[MOD_DST_CV_2]);
  modulation_destinations_[MOD_DST_LFO_1] = S16ShiftRight8(dst_[MOD_DST_LFO_1]);
  modulation_destinations_[MOD_DST_LFO_2] = S16ShiftRight8(dst_[MOD_DST_LFO_2]);
  
  if (dst_[MOD_DST_TRIGGER_ENV_1] > 6000) {
    if (!modulation_destinations_[MOD_DST_TRIGGER_ENV_1]) {
      envelope_[0].Trigger(ATTACK);
    }
    modulation_destinations_[MOD_DST_TRIGGER_ENV_1] = 255;
  } else {
    modulation_destinations_[MOD_DST_TRIGGER_ENV_1] = 0;
  }

  if (dst_[MOD_DST_TRIGGER_ENV_2] > 6000) {
    if (!modulation_destinations_[MOD_DST_TRIGGER_ENV_2]) {
      envelope_[1].Trigger(ATTACK);
    }
    modulation_destinations_[MOD_DST_TRIGGER_ENV_2] = 255;
  } else {
    modulation_destinations_[MOD_DST_TRIGGER_ENV_2] = 0;
  }
  
  osc_1.set_parameter(U15ShiftRight7(dst_[MOD_DST_PWM_1]));
  osc_1.set_secondary_parameter(part.patch_.osc[0].range + 24);
  osc_2.set_parameter(U15ShiftRight7(dst_[MOD_DST_PWM_2]));
  osc_2.set_secondary_parameter(part.patch_.osc[1].range + 24);
  
  int8_t attack_mod = (U15ShiftRight7(dst_[MOD_DST_ATTACK]) - 64) << 1;
  int16_t* envelope_parameters = &dst_[MOD_DST_ATTACK_1];
  for (int i = 0; i < kNumEnvelopes; ++i) {
    envelope_[i].Update(
        Clip(U15ShiftRight7(envelope_parameters[0]) - attack_mod, 0, 127),
        U15ShiftRight7(envelope_parameters[1]),
        U15ShiftRight7(envelope_parameters[2]),
        U15ShiftRight7(envelope_parameters[3]));
    envelope_parameters += 4;
  }
}

/* static */
inline void Voice::RenderOscillators() {
  // Apply portamento.
  int16_t base_pitch = pitch_value_ + pitch_increment_;
  if ((pitch_increment_ > 0) ^ (base_pitch < pitch_target_)) {
    base_pitch = pitch_target_;
    pitch_increment_ = 0;
  }
  pitch_value_ = base_pitch;

  // -4 / +4 semitones by the vibrato and pitch bend.
  base_pitch += (dst_[MOD_DST_VCO_1_2_COARSE] - 8192) >> 4;
  // -1 / +1 semitones by the vibrato and pitch bend.
  base_pitch += (dst_[MOD_DST_VCO_1_2_FINE] - 8192) >> 7;
  // -1 / +1 semitones by master tuning.
  base_pitch += part.system_settings_.master_tuning;
  
  // Update the oscillator parameters.
  for (uint8_t i = 0; i < kNumOscillators; ++i) {
    int16_t pitch = base_pitch;
    
    // This is where we look up the list of most recently pressed notes for
    // the duophonic mode.
    if (part.patch_.osc[0].option == OP_DUO && i == 0 && pitch_bass_note_) {
      pitch -= pitch_value_;
      pitch += pitch_bass_note_;
    }
    
    // -24 / +24 semitones by the range controller.
    int8_t range = 0;
    if (part.patch_.osc[i].shape != WAVEFORM_FM) {
      range += part.patch_.osc[i].range;
    }
    range += part.system_settings_.octave * 12;
    // -24 / +24 semitones by the main octave controller.
    pitch += S8U8Mul(range, 128);
    if (i == 1) {
      // 0 / +1 semitones by the detune option for oscillator 2.
      pitch += part.patch_.osc[1].option;
    }
    // -16 / +16 semitones by the routed modulations.
    pitch += (dst_[MOD_DST_VCO_1 + i] - 8192) >> 2;

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
    uint16_t pitch_lookup_index_integral = U16ShiftRight4(ref_pitch);
    uint8_t pitch_lookup_index_fractional = U8ShiftLeft4(ref_pitch);
    uint16_t increment16 = ResourcesManager::Lookup<uint16_t, uint16_t>(
        lut_res_oscillator_increments, pitch_lookup_index_integral);
    uint16_t increment16_next = ResourcesManager::Lookup<uint16_t, uint16_t>(
        lut_res_oscillator_increments, pitch_lookup_index_integral + 1);
    increment.integral = increment16 + U16U8MulShift8(
        increment16_next - increment16, pitch_lookup_index_fractional);
    increment.fractional = 0;
    // Divide the pitch increment by the number of octaves we had to transpose
    // to get a value in the lookup table.
    while (num_shifts--) {
      increment = U24ShiftRight(increment);
    }

    // Now the oscillators can recompute all their internal variables!
    int8_t midi_note = U15ShiftRight7(pitch);
    if (midi_note < 12) {
      midi_note = 12;
    }
    // phase_increment.fractional = 0;
    if (i == 0) {
      sub_osc.set_increment(U24ShiftRight(increment));
      osc_1.Render(
          part.patch_.osc[0].shape,
          midi_note,
          increment,
          no_sync_,
          sync_state_,
          buffer_);
    } else {
      uint8_t shape = part.patch_.osc[1].shape;
      // The sub always plays the lowest note.
      if (part.patch_.osc[0].option == OP_DUO) {
        if (!pitch_bass_note_) {
          shape = 0;
        }
      }
      osc_2.Render(
          shape,
          midi_note,
          increment,
          part.patch_.osc[0].option == OP_SYNC ? sync_state_ : no_sync_,
          dummy_sync_state_,
          osc2_buffer_);
    }
  }
}

const prog_uint8_t eight_step_sequence[8] PROGMEM = {
  4, 1, 8, 8, 2, 4, 8, 2,
};

const prog_uint8_t four_step_sequence[4] PROGMEM = {
  4, 1, 8, 2
};

/* static */
void Voice::ProcessBlock() {
  LoadSources();
  ProcessModulationMatrix();
  UpdateDestinations();
  RenderOscillators();
  
  // Skip the oscillator rendering code if the VCA output has converged to
  // a small value.
  if (vca() == 0) {
    for (uint8_t i = 0; i < kAudioBlockSize; ++i) {
      audio_out.Overwrite(128);
    }
    return;
  }
  
  uint8_t op = part.patch_.osc[0].option;
  // By default, disable rhythmical mixing.
  uint8_t enabled_source_bitmask = 0xff;
  
  // With the sequenced mixing mode, use a different value of the bitmask.
  if (op == OP_PING_PONG_2) {
    enabled_source_bitmask = (trigger_count_ & 1) ? 0x0e : 0x0d;
  } else if (op == OP_PING_PONG_4) {
    enabled_source_bitmask = pgm_read_byte(
        four_step_sequence + (trigger_count_ & 3));
  } else if (op == OP_PING_PONG_8) {
    enabled_source_bitmask = pgm_read_byte(
        eight_step_sequence + (trigger_count_ & 7));
  } else if (op == OP_PING_PONG_SEQ) {
    enabled_source_bitmask = modulation_sources_[MOD_SRC_SEQ] >> 4;
  }
  
  uint8_t osc_2_gain = U14ShiftRight6(dst_[MOD_DST_MIX_BALANCE]);
  uint8_t osc_1_gain = ~osc_2_gain;
  if (enabled_source_bitmask != 0xff && (enabled_source_bitmask & 3) != 3) {
    osc_2_gain = (enabled_source_bitmask & 1) ? 255 : 0;
    osc_1_gain = (enabled_source_bitmask & 2) ? 255 : 0;
  }
  if (!osc_1_gain && !osc_2_gain) {
    memset(buffer_, 128, kAudioBlockSize);
  } else {
    // Mix oscillators.
    switch (op) {
      case OP_RING_MOD:
        for (uint8_t i = 0; i < kAudioBlockSize; ++i) {
          uint8_t ring_mod = S8S8MulShift8(
              buffer_[i] + 128,
              osc2_buffer_[i] + 128) + 128;
          buffer_[i] = U8Mix(buffer_[i], ring_mod, osc_1_gain, osc_2_gain);
        }
        break;
      case OP_FUZZ:
        for (uint8_t i = 0; i < kAudioBlockSize; ++i) {
          buffer_[i] >>= 1;
          buffer_[i] += (osc2_buffer_[i] >> 1);
          buffer_[i] = U8Mix(
              buffer_[i],
              ResourcesManager::Lookup<uint8_t, uint8_t>(
                  wav_res_distortion, buffer_[i]),
              osc_1_gain,
              osc_2_gain);
        }
        break;
      case OP_XOR:
        for (uint8_t i = 0; i < kAudioBlockSize; ++i) {
          buffer_[i] ^= osc2_buffer_[i];
          buffer_[i] ^= osc_2_gain;
        }
        break;
      case OP_FOLD:
        for (uint8_t i = 0; i < kAudioBlockSize; ++i) {
          buffer_[i] >>= 1;
          buffer_[i] += (osc2_buffer_[i] >> 1);
          buffer_[i] = U8Mix(
              buffer_[i],
              buffer_[i] + 128,
              osc_1_gain,
              osc_2_gain);
        }
        break;
      case OP_BITS:
        {
          osc_2_gain >>= 5;
          osc_2_gain = 255 - ((1 << osc_2_gain) - 1);
          for (uint8_t i = 0; i < kAudioBlockSize; ++i) {
            buffer_[i] >>= 1;
            buffer_[i] += (osc2_buffer_[i] >> 1);
            buffer_[i] &= osc_2_gain;
          }
        }
        break;
      default:
        for (uint8_t i = 0; i < kAudioBlockSize; ++i) {
          buffer_[i] = U8Mix(
              buffer_[i],
              osc2_buffer_[i],
              osc_1_gain,
              osc_2_gain);
        }
        break;
    }    
  }
  uint8_t decimate = 1;
  if (op == OP_CRUSH_4) {
    decimate = 4;
  } else if (op == OP_CRUSH_8) {
    decimate = 8;
  }
  
  // Mix-in sub oscillator or transient generator.
  uint8_t sub_gain = U15ShiftRight7(dst_[MOD_DST_MIX_SUB_OSC]);
  if (enabled_source_bitmask != 0xff) {
    sub_gain = (enabled_source_bitmask & 4) ? sub_gain : 0;
    if ((enabled_source_bitmask & 3) == 0) {
      sub_gain <<= 1;
    }
  }
  if (part.patch_.mix_sub_osc_shape < WAVEFORM_SUB_OSC_CLICK) {
    sub_osc.Render(part.patch_.mix_sub_osc_shape, buffer_, sub_gain);
  } else {
    if (sub_gain < 128) {
      sub_gain <<= 1;
    }
    transient_generator.Render(
        part.patch_.mix_sub_osc_shape, buffer_, sub_gain);
  }
  
  // Apply optional bitcrushing.
  if (decimate > 1) {
    uint8_t* buffer = buffer_;
    for (uint8_t i = 0; i < kAudioBlockSize; i += decimate) {
      uint8_t value = *buffer++;
      for (uint8_t j = 1; j < decimate; ++j) {
        *buffer++ = value;
      }
    }
  }
  
  // Mix with noise and output.
  uint8_t noise = Random::GetByte();
  uint8_t noise_gain = S16ShiftRight8(dst_[MOD_DST_MIX_NOISE]);
  if (enabled_source_bitmask != 0xff) {
    noise_gain = (enabled_source_bitmask & 8) ? noise_gain : 0;
    if (enabled_source_bitmask == 8) {
      noise_gain <<= 1;
    }
  }
  uint8_t mix_gain = ~noise_gain;
  for (uint8_t i = 0; i < kAudioBlockSize; ++i) {
    noise = (noise * 73) + 1;
    audio_out.Overwrite(U8Mix(buffer_[i], noise, mix_gain, noise_gain));
  }
}

}  // namespace shruthi
