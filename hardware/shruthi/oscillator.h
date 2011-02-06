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
// Oscillators. Note that the code of each oscillator is duplicated/specialized,
// for a noticeable performance boost.
// Another performance optimization consists in rendering the oscillator at
// a sample rate which is the half of the base sample rate - this is
// particularly useful for oscillators which do not have a rich frequency
// content, but which are very computationnally expensive.

#ifndef HARDWARE_SHRUTHI_OSCILLATOR_H_
#define HARDWARE_SHRUTHI_OSCILLATOR_H_

#include "hardware/base/base.h"
#include "hardware/shruthi/shruthi.h"

#include "hardware/shruthi/patch.h"
#include "hardware/shruthi/resources.h"
#include "hardware/shruthi/synthesis_engine.h"
#include "hardware/utils/random.h"
#include "hardware/utils/op.h"

using namespace hardware_utils_op;
using hardware_utils::Random;

static const uint16_t kWavetableSize = 16 * 129;
static const uint16_t kUserWavetableSize = 8 * 129;

namespace hardware_shruthi {

#define WAV_RES_SINE WAV_RES_BANDLIMITED_TRIANGLE_6

static inline uint8_t ReadSample(const prog_uint8_t* table, uint16_t phase) {
  return ResourcesManager::Lookup<uint8_t, uint8_t>(table, phase >> 8);
}

extern uint8_t user_wavetable[];

#ifdef USE_OPTIMIZED_OP
static inline uint8_t InterpolateSample(
    const prog_uint8_t* table,
    uint16_t phase) {
  uint8_t result;
  asm(
    "movw r30, %A1"           "\n\t"  // copy base address to r30:r31
    "add r30, %B2"            "\n\t"  // increment table address by phaseH
    "adc r31, r1"             "\n\t"  // just carry
    "lpm %0, z+"              "\n\t"  // load sample[n]
    "lpm r1, z+"              "\n\t"  // load sample[n+1]
    "mul %A2, r1"             "\n\t"  // multiply second sample by phaseL
    "movw r30, r0"            "\n\t"  // result to accumulator
    "com %A2"                 "\n\t"  // 255 - phaseL -> phaseL
    "mul %A2, %0"             "\n\t"  // multiply first sample by phaseL
    "com %A2"                 "\n\t"  // 255 - phaseL -> phaseL
    "add r30, r0"             "\n\t"  // accumulate L
    "adc r31, r1"             "\n\t"  // accumulate H
    "eor r1, r1"              "\n\t"  // reset r1 after multiplication
    "mov %0, r31"             "\n\t"  // use sum H as output
    : "=r" (result)
    : "a" (table), "a" (phase)
    : "r30", "r31"
  );
  return result;
}
static inline uint8_t InterpolateSampleRam(
    const uint8_t* table,
    uint16_t phase) {
  uint8_t result;
  asm(
    "movw r30, %A1"           "\n\t"  // copy base address to r30:r31
    "add r30, %B2"            "\n\t"  // increment table address by phaseH
    "adc r31, r1"             "\n\t"  // just carry
    "ld %0, z+"               "\n\t"  // load sample[n]
    "ld r1, z+"               "\n\t"  // load sample[n+1]
    "mul %A2, r1"             "\n\t"  // multiply second sample by phaseL
    "movw r30, r0"            "\n\t"  // result to accumulator
    "com %A2"                 "\n\t"  // 255 - phaseL -> phaseL
    "mul %A2, %0"             "\n\t"  // multiply first sample by phaseL
    "com %A2"                 "\n\t"  // 255 - phaseL -> phaseL
    "add r30, r0"             "\n\t"  // accumulate L
    "adc r31, r1"             "\n\t"  // accumulate H
    "eor r1, r1"              "\n\t"  // reset r1 after multiplication
    "mov %0, r31"             "\n\t"  // use sum H as output
    : "=r" (result)
    : "a" (table), "a" (phase)
    : "r30", "r31"
  );
  return result;
}
#else
static inline uint8_t InterpolateSample(const prog_uint8_t* table,
                                        uint16_t phase) {
  return Mix(
      ResourcesManager::Lookup<uint8_t, uint8_t>(table, phase >> 8),
      ResourcesManager::Lookup<uint8_t, uint8_t>(table, 1 + (phase >> 8)),
      phase & 0xff);
}
static inline uint8_t InterpolateSampleRam(const uint8_t* table,
                                           uint16_t phase) {
  return Mix(table[phase >> 8], table[1 + (phase >> 8)], phase & 0xff);
}
#endif  // USE_OPTIMIZED_OP

static inline uint8_t InterpolateTwoTables(
    const prog_uint8_t* table_a, const prog_uint8_t* table_b,
    uint16_t phase, uint8_t balance) {
  return Mix(
      InterpolateSample(table_a, phase),
      InterpolateSample(table_b, phase),
      balance);
}


static const uint8_t kVowelControlRateDecimation = 4;
static const uint8_t kNumZonesFullSampleRate = 6;
static const uint8_t kNumZonesHalfSampleRate = 5;

struct BandlimitedPwmOscillatorState {
  const prog_uint8_t* wave[2];
  uint8_t balance;
  uint16_t shift;
  uint8_t scale;
};

// Interpolates between two 256-samples wavetables.
struct SawTriangleOscillatorState {
  const prog_uint8_t* wave[2];
  uint8_t balance;
};

struct SweepingWavetableOscillatorState {
  const prog_uint8_t* wave[2];
  uint8_t balance;
};

struct CzOscillatorState {
  uint16_t formant_phase;
  uint16_t formant_phase_increment;
};

struct FmOscillatorState {
  uint16_t modulator_phase;
  uint16_t modulator_phase_increment;
};

struct VowelSynthesizerState {
  uint16_t formant_increment[3];
  uint16_t formant_phase[3];
  uint8_t formant_amplitude[3];
  uint8_t noise_modulation;
  uint8_t update;  // Update only every kVowelControlRateDecimation-th call.
};

struct FilteredNoiseState {
  uint8_t lp_noise_sample;
};

struct QuadSawPadState {
  uint16_t phase_increment[3];
  uint16_t phase[3];
};

struct CrushedSineState {
  uint8_t decimate;
  uint8_t state;
};

union OscillatorState {
  BandlimitedPwmOscillatorState pw;
  SawTriangleOscillatorState st;
  CzOscillatorState cz;
  FmOscillatorState fm;
  VowelSynthesizerState vw;
  FilteredNoiseState no;
  QuadSawPadState qs;
  CrushedSineState cr;
  SweepingWavetableOscillatorState sw;
};

struct AlgorithmFn {
  void (*update)();
  void (*render)(uint8_t* buffer, uint8_t size);
};

template<int id>
class Oscillator {
 public:
  Oscillator() { }

  // Called whenever the parameters of the oscillator change. Can be used
  // to pre-compute parameters, set tables, etc.
  static inline void SetupAlgorithm(uint8_t shape) {
    if (shape > WAVEFORM_VOWEL) {
      shape = WAVEFORM_VOWEL;
    }
    shape_ = shape;
    fn_ = fn_table_[shape];
  }
  
  static inline void Render(uint8_t* buffer, uint8_t size) {
    (*fn_.render)(buffer, size);
  }
  
  static inline void Update(
      uint8_t parameter,
      uint8_t note,
      uint16_t integral,
      uint8_t fractional) {
    note_ = note;
    parameter_ = parameter;
    phase_increment_.integral = integral;
    phase_increment_.fractional = fractional;
    // A hack: when pulse width is set to 0, use a simple wavetable.
    if (shape_ == WAVEFORM_SQUARE) {
      fn_ = fn_table_[shape_ + (parameter_ == 0 ? 1 : 0)];
    }
    (*fn_.update)();
  }
  
  static inline void UpdateSecondaryParameter(uint8_t secondary_parameter) {
    data_.fm.modulator_phase_increment = secondary_parameter;
  }
  
  static inline uint16_t phase() { return phase_.integral; }
  static inline void ResetPhase() {
    phase_.integral = 0;
    phase_.fractional = 0;
  }

 private:
  // Current phase of the oscillator.
  static uint24_t phase_;

  // Phase increment (and phase increment x 2, for low-sr oscillators).
  static uint24_t phase_increment_;

  // Copy of the shape used by this oscillator. When changing this, you
  // should also update the Update/Render pointers.
  static uint8_t shape_;
  static uint8_t shape_corrected_;
  // Whether we are sweeping through the algorithms.
  static uint8_t sweeping_;

  // Current value of the oscillator parameter.
  static uint8_t parameter_;

  // Current MIDI note (used for wavetable selection).
  static uint8_t note_;

  // Union of state data used by each algorithm.
  static OscillatorState data_;

  // A pair of pointers to the update/render functions. update function might be
  // NULL.
  static AlgorithmFn fn_;

  static AlgorithmFn fn_table_[];

  // ------- Silence (useful when processing external signals) -----------------
  static void UpdateSilence() {
  }
  
  static void RenderSilence(uint8_t* buffer, uint8_t size) {
    while (size--) {
      *buffer++ = 128;
    }
  }

  // ------- Band-limited PWM --------------------------------------------------
  static void UpdateBandlimitedPwm() {
    uint8_t balance_index = Swap4(note_ - 12);
    data_.pw.balance = balance_index & 0xf0;

    uint8_t wave_index = balance_index & 0xf;
    data_.pw.wave[0] = waveform_table[WAV_RES_BANDLIMITED_SAW_1 + wave_index];
    wave_index = AddClip(wave_index, 1, kNumZonesHalfSampleRate);
    data_.pw.wave[1] = waveform_table[WAV_RES_BANDLIMITED_SAW_1 + wave_index];    
    data_.pw.shift = static_cast<uint16_t>(parameter_ + 128) << 8;
    // For higher pitched notes, simply use 128
    data_.pw.scale = 192 - (parameter_ >> 1);
    if (note_ > 64) {
      data_.pw.scale = Mix(data_.pw.scale, 104, (note_ - 64) << 2);
      data_.pw.scale = Mix(data_.pw.scale, 104, (note_ - 64) << 2);
    }
    phase_increment_ = Lsr24(phase_increment_);
  }
  static void RenderBandlimitedPwm(uint8_t* buffer, uint8_t size) {
    while (size) {
      phase_ = Add24(phase_, phase_increment_);
      uint8_t a = InterpolateTwoTables(
          data_.pw.wave[0],
          data_.pw.wave[1],
          phase_.integral,
          data_.pw.balance);
      a = MulScale8(a, data_.pw.scale);
      uint8_t b = InterpolateSample(
          data_.pw.wave[0],
          phase_.integral + data_.pw.shift);
      b = MulScale8(b, data_.pw.scale);
      a = a - b + 128;
      *buffer++ = a;
      *buffer++ = a;
      size -= 2;
    }
  }

  // ------- Interpolation between two waveforms from two wavetables -----------
  // The position is determined by the note pitch, to prevent aliasing.
  static void UpdateSimpleWavetable() {
    uint8_t balance_index = Swap4(note_ - 12);
    data_.st.balance = balance_index & 0xf0;

    uint8_t wave_index = balance_index & 0xf;
    uint8_t base_resource_id = shape_ == WAVEFORM_SAW ?
        WAV_RES_BANDLIMITED_SAW_0 :
        (shape_ == WAVEFORM_SQUARE ? WAV_RES_BANDLIMITED_SQUARE_0  : 
        WAV_RES_BANDLIMITED_TRIANGLE_0);

    data_.st.wave[0] = waveform_table[base_resource_id + wave_index];
    wave_index = AddClip(wave_index, 1, kNumZonesFullSampleRate);
    data_.st.wave[1] = waveform_table[base_resource_id + wave_index];
  }
  static void RenderSimpleWavetable(uint8_t* buffer, uint8_t size) {
    while (size--) {
      phase_ = Add24(phase_, phase_increment_);
      uint8_t sample = InterpolateTwoTables(
          data_.st.wave[0], data_.st.wave[1],
          phase_.integral, data_.st.balance);
      // To produce pulse width-modulated variants, we shift (saw) or set to
      // a constant (triangle) a portion of the waveform within an increasingly
      // large fraction of the period. Note that this is pure waveshapping - the
      // phase information is not used to determine when/where to shift.
      //
      //     /|            /|          /\             /\
      //    / |           / |         /  \           /  \
      //   /  |    =>  /|/  |        /    \  =>  ___/    \
      //  /   |       /     |/      /      \
      // /    |/                   /        \
      //
      if (sample < parameter_) {
        if (shape_ == WAVEFORM_SAW) {
          // Add a discontinuity.
          sample += parameter_ >> 1;
        } else {
          // Clip.
          sample = parameter_;
        }
      }
      *buffer++ = sample;
    }
  }
  
  // ------- Interpolation between two waveforms from two wavetables -----------
  // The position is freely determined by the parameter
  static void UpdateSweepingWavetable() {
    uint8_t balance_index = Swap4(parameter_ << 1);
    data_.sw.balance = balance_index & 0xf0;
    uint8_t wave_index = balance_index & 0xf;
    
    uint16_t offset = wave_index << 8;
    offset >>= 1;

    offset += wave_index;
    const prog_uint8_t* base_address = waveform_table[
        WAV_RES_WAVETABLE_1 + shape_ - WAVEFORM_WAVETABLE_1];
    data_.sw.wave[0] = base_address + offset;
    data_.sw.wave[1] = data_.sw.wave[0];
    if (offset < kWavetableSize - 129) {
      data_.sw.wave[1] += 129;
    }
  }
  
  static void RenderSweepingWavetable(uint8_t* buffer, uint8_t size) {
    while (size--) {
      phase_ = Add24(phase_, phase_increment_);
      uint16_t phase = phase_.integral;
      phase >>= 1;
      *buffer++ = InterpolateTwoTables(
          data_.st.wave[0], data_.st.wave[1],
          phase, data_.st.balance);
    }
  }
  
  // The position is freely determined by the parameter
  static void UpdateSweepingWavetableRam() {
    uint8_t balance_index = Swap4(parameter_);
    data_.sw.balance = balance_index & 0xf0;
    uint8_t wave_index = balance_index & 0xf;
    
    uint16_t offset = wave_index << 7;
    offset += wave_index;
    data_.sw.wave[0] = user_wavetable + offset;
    data_.sw.wave[1] = data_.sw.wave[0];
    if (offset < kUserWavetableSize - 129) {
      data_.sw.wave[1] += 129;
    }
  }
  
  static void RenderSweepingWavetableRam(uint8_t* buffer, uint8_t size) {
    while (size--) {
      phase_ = Add24(phase_, phase_increment_);
      uint16_t phase = phase_.integral;
      phase >>= 1;
      *buffer++ = Mix(
          InterpolateSampleRam(data_.sw.wave[0], phase),
          InterpolateSampleRam(data_.sw.wave[1], phase),
          data_.st.balance);
    }
  }

  // ------- Casio CZ-like synthesis -------------------------------------------
  static void UpdateCz() {
    data_.cz.formant_phase_increment = phase_increment_.integral + (
        (phase_increment_.integral * uint32_t(parameter_)) >> 3);
  }
  
  static void RenderCzSaw(uint8_t* buffer, uint8_t size) {
    while (size--) {
      phase_ = Add24(phase_, phase_increment_);
      uint8_t phase = phase_.integral >> 8;
      uint8_t clipped_phase = phase < 0x20 ? phase << 3 : 0xff;
      *buffer++ = InterpolateSample(waveform_table[WAV_RES_SINE],
          Mix16(phase, clipped_phase, parameter_ << 1));
    }
  }
  
  static void RenderCzPulseReso(uint8_t* buffer, uint8_t size) {
    while (size--) {
      uint8_t old_phase_msb = phase_.integral >> 8;
      phase_.integral += phase_increment_.integral;
      // phase_ = Add24(phase_, phase_increment_);
      uint8_t phase_msb = phase_.integral >> 8;
      if (phase_msb < old_phase_msb) {
        data_.cz.formant_phase = 0;
      }
      data_.cz.formant_phase += data_.cz.formant_phase_increment;
      uint8_t result = InterpolateSample(
          waveform_table[WAV_RES_SINE],
          data_.cz.formant_phase);
      if (phase_.integral < 0x4000) {
        *buffer++ = result;
      } else if (phase_.integral < 0x8000) {
        *buffer++ = MulScale8(result, ~(phase_.integral - 0x4000) >> 6);
      } else {
        *buffer++ = 0;
      }
    }
  }
  
  static void RenderCzSawReso(uint8_t* buffer, uint8_t size) {
    while (size--) {
      uint8_t old_phase_msb = phase_.integral >> 8;
      phase_ = Add24(phase_, phase_increment_);
      uint8_t phase_msb = phase_.integral >> 8;
      if (phase_msb < old_phase_msb) {
        data_.cz.formant_phase = 0;
      }
      data_.cz.formant_phase += data_.cz.formant_phase_increment;
      uint8_t result = InterpolateSample(
          waveform_table[WAV_RES_SINE],
          data_.cz.formant_phase);
      *buffer++ = MulScale8(result, ~phase_msb);
    }
  }
  
  static void RenderCzTriReso(uint8_t* buffer, uint8_t size) {
    while (size--) {
      uint8_t old_phase_msb = phase_.integral >> 8;
      phase_ = Add24(phase_, phase_increment_);
      uint8_t phase_msb = phase_.integral >> 8;
      if (phase_msb < old_phase_msb) {
        data_.cz.formant_phase = 0;
      }
      data_.cz.formant_phase += data_.cz.formant_phase_increment;
      uint8_t result = InterpolateSample(
          waveform_table[WAV_RES_SINE],
          data_.cz.formant_phase);
      uint8_t triangle =  (phase_.integral & 0x8000) ?
            ~static_cast<uint8_t>(phase_.integral >> 7) :
            phase_.integral >> 7;
      *buffer++ = MulScale8(result, triangle);
    }
  }

  static void RenderCzSyncReso(uint8_t* buffer, uint8_t size) {
    while (size--) {
      uint8_t old_phase_msb = phase_.integral >> 8;
      phase_ = Add24(phase_, phase_increment_);
      uint8_t phase_msb = phase_.integral >> 8;
      if (phase_msb < old_phase_msb) {
        data_.cz.formant_phase = 0;
      }
      data_.cz.formant_phase += data_.cz.formant_phase_increment;
      uint8_t result = InterpolateSample(
          waveform_table[WAV_RES_SINE],
          data_.cz.formant_phase);
      *buffer++ = phase_.integral < 0x8000 ? result : 128;
    }
  }
  
  // ------- FM ----------------------------------------------------------------
  static void UpdateFm() {
    uint8_t offset = data_.fm.modulator_phase_increment;
    if (offset < 12) {
      offset = 0;
    } else if (offset > 36) {
      offset = 24;
    } else {
      offset = offset - 12;
    }
    uint16_t multiplier = ResourcesManager::Lookup<uint16_t, uint8_t>(
        lut_res_fm_frequency_ratios, offset);
    data_.fm.modulator_phase_increment = (
        static_cast<int32_t>(phase_increment_.integral) * multiplier) >> 8;
    parameter_ <<= 1;
  }
  static void RenderFm(uint8_t* buffer, uint8_t size) {
    while (size--) {
      phase_ = Add24(phase_, phase_increment_);
      data_.fm.modulator_phase += data_.fm.modulator_phase_increment;
      uint8_t modulator = ReadSample(waveform_table[WAV_RES_SINE],
                                     data_.fm.modulator_phase);
      uint16_t modulation = modulator * parameter_;
      *buffer++ = InterpolateSample(waveform_table[WAV_RES_SINE],
          phase_.integral + modulation);
    }
  }

  // ------- 8-bit land --------------------------------------------------------
  static void Render8BitLand(uint8_t* buffer, uint8_t size) {
    while (size--) {
      phase_ = Add24(phase_, phase_increment_);
      uint8_t x = parameter_;
      *buffer++ = (((phase_.integral >> 8) ^ (x << 1)) & (~x)) + (x >> 1);
    }
  }

  // ------- 8-bit land --------------------------------------------------------
  static void RenderCrushedSine(uint8_t* buffer, uint8_t size) {
    while (size--) {
      phase_ = Add24(phase_, phase_increment_);
      ++data_.cr.decimate;
      if (parameter_ <= 63) {
        if (data_.cr.decimate >= parameter_ + 1) {
          data_.cr.decimate = 0;
          data_.cr.state = InterpolateSample(
              waveform_table[WAV_RES_SINE],
              phase_.integral);
        }
      } else {
        if (data_.cr.decimate >= 128 - parameter_) {
          data_.cr.decimate = 0;
          data_.cr.state = InterpolateSample(
              waveform_table[WAV_RES_BANDLIMITED_TRIANGLE_0],
              phase_.integral);
        }
      }
      *buffer++ = data_.cr.state;
    }
  }
  
  // ------- Vowel ------------------------------------------------------------
  //
  // The algorithm used here is a reimplementation of the synthesis algorithm
  // used in Cantarino, the Arduino speech synthesizer, by Peter Knight.
  // http://code.google.com/p/tinkerit/wiki/Cantarino
  static void UpdateVowel() {
    if (id == 2) {
      return;  // Do not duplicate this code for the second oscillator.
    }
    data_.vw.update++;
    if (data_.vw.update == kVowelControlRateDecimation) {
      data_.vw.update = 0;
    } else {
      return;
    }

    uint8_t offset_1 = ShiftRight4(parameter_);
    offset_1 = (offset_1 << 2) + offset_1;  // offset_1 * 5
    uint8_t offset_2 = offset_1 + 5;
    uint8_t balance = parameter_ & 15;
    for (uint8_t i = 0; i < 3; ++i) {
      data_.vw.formant_increment[i] = UnscaledMix4(
          ResourcesManager::Lookup<uint8_t, uint8_t>(
              waveform_table[WAV_RES_VOWEL_DATA], offset_1 + i),
          ResourcesManager::Lookup<uint8_t, uint8_t>(
              waveform_table[WAV_RES_VOWEL_DATA], offset_2 + i),
          balance);
      data_.vw.formant_increment[i] <<= 3;
    }
    for (uint8_t i = 0; i < 2; ++i) {
      uint8_t amplitude_a = ResourcesManager::Lookup<uint8_t, uint8_t>(
          waveform_table[WAV_RES_VOWEL_DATA],
          offset_1 + 3 + i);
      uint8_t amplitude_b = ResourcesManager::Lookup<uint8_t, uint8_t>(
          waveform_table[WAV_RES_VOWEL_DATA],
          offset_2 + 3 + i);

      data_.vw.formant_amplitude[2 * i + 1] = Mix4(
          amplitude_a & 0x0f,
          amplitude_b & 0x0f, balance);
      amplitude_a = ShiftRight4(amplitude_a);
      amplitude_b = ShiftRight4(amplitude_b);
      data_.vw.formant_amplitude[2 * i] = Mix4(
          amplitude_a,
          amplitude_b, balance);
    }
  }
  static void RenderVowel(uint8_t* buffer, uint8_t size) {
    if (id == 2) {
      return;  // Do not duplicate this code for the second oscillator.
    }
    while (size) {
      int8_t result = 0;
      for (uint8_t i = 0; i < 3; ++i) {
        data_.vw.formant_phase[i] += data_.vw.formant_increment[i];
        result += ResourcesManager::Lookup<uint8_t, uint8_t>(
            i == 2 ? waveform_table[WAV_RES_FORMANT_SQUARE] :
                     waveform_table[WAV_RES_FORMANT_SINE],
            ((data_.vw.formant_phase[i] >> 8) & 0xf0) |
              data_.vw.formant_amplitude[i]);
      }
      result = SignedMulScale8(result, ~(phase_.integral >> 8));
      phase_.integral += phase_increment_.integral;
      int16_t phase_noise = int8_t(Random::state_msb()) *
          int8_t(data_.vw.noise_modulation);
      if ((phase_.integral + phase_noise) < phase_increment_.integral) {
        data_.vw.formant_phase[0] = 0;
        data_.vw.formant_phase[1] = 0;
        data_.vw.formant_phase[2] = 0;
      }
      uint8_t x = SignedClip8(4 * result) + 128;
      *buffer++ = x;
      *buffer++ = x;
      size -= 2;
    }
  }

  // ------- Dirty Pwm (kills kittens) -----------------------------------------
  static void RenderDirtyPwm(uint8_t* buffer, uint8_t size) {
    while (size--) {
      phase_ = Add24(phase_, phase_increment_);
      *buffer++ = (phase_.integral >> 8) < 127 + parameter_ ? 0 : 255;
    }
  }
  
  // ------- Quad saw (mit aliasing) -------------------------------------------
  static void UpdateQuadSawPad() {
    uint16_t phase_spread = (
        static_cast<uint32_t>(phase_increment_.integral) * parameter_) >> 13;
    ++phase_spread;
    uint16_t phase_increment = phase_increment_.integral;
    for (uint8_t i = 0; i < 3; ++i) {
      phase_increment += phase_spread;
      data_.qs.phase_increment[i] = phase_increment;
    }
  }

  static void RenderQuadSawPad(uint8_t* buffer, uint8_t size) {
    while (size--) {
      phase_ = Add24(phase_, phase_increment_);
      data_.qs.phase[0] += data_.qs.phase_increment[0];
      data_.qs.phase[1] += data_.qs.phase_increment[1];
      data_.qs.phase[2] += data_.qs.phase_increment[2];
      *buffer = (phase_.integral >> 10);
      *buffer += (data_.qs.phase[0] >> 10);
      *buffer += (data_.qs.phase[1] >> 10);
      *buffer++ += (data_.qs.phase[2] >> 10);
    }
  }

  // ------- Low-passed, then high-passed white noise --------------------------
  static void RenderFilteredNoise(uint8_t* buffer, uint8_t size) {
    while (size--) {
      uint8_t innovation = Random::GetByte();
      // This trick is used to avoid having a DC component (no innovation) when
      // the parameter is set to its minimal or maximal value.
      uint8_t offset = parameter_ == 127 ? 0 : 2;
      data_.no.lp_noise_sample = Mix(
          data_.no.lp_noise_sample,
          innovation,
          offset + (parameter_ << 2));
      if (parameter_ >= 64) {
        *buffer++ = innovation - data_.no.lp_noise_sample;
      } else {
        *buffer++ = data_.no.lp_noise_sample;
      }
    }
  }

  DISALLOW_COPY_AND_ASSIGN(Oscillator);
};

#define Osc Oscillator<id>

template<int id> uint24_t Oscillator<id>::phase_increment_;

template<int id> uint24_t Oscillator<id>::phase_;
template<int id> uint8_t Oscillator<id>::shape_;
template<int id> uint8_t Oscillator<id>::shape_corrected_;
template<int id> uint8_t Oscillator<id>::parameter_;
template<int id> uint8_t Oscillator<id>::note_;
template<int id> uint8_t Oscillator<id>::sweeping_;

template<int id> OscillatorState Oscillator<id>::data_;

template<int id> AlgorithmFn Oscillator<id>::fn_;
template<int id> AlgorithmFn Oscillator<id>::fn_table_[] = {
  { &Osc::UpdateSilence, &Osc::RenderSilence },

  { &Osc::UpdateSimpleWavetable, &Osc::RenderSimpleWavetable },
  { &Osc::UpdateBandlimitedPwm, &Osc::RenderBandlimitedPwm },
  { &Osc::UpdateSimpleWavetable, &Osc::RenderSimpleWavetable },

  { &Osc::UpdateSilence, &Osc::RenderCzSaw },  
  { &Osc::UpdateCz, &Osc::RenderCzSawReso },
  { &Osc::UpdateCz, &Osc::RenderCzTriReso },
  { &Osc::UpdateCz, &Osc::RenderCzPulseReso },
  { &Osc::UpdateCz, &Osc::RenderCzSyncReso },
  
  { &Osc::UpdateQuadSawPad, &Osc::RenderQuadSawPad },
  
  { &Osc::UpdateFm, &Osc::RenderFm },
  
  { &Osc::UpdateSweepingWavetable, &Osc::RenderSweepingWavetable },
  { &Osc::UpdateSweepingWavetable, &Osc::RenderSweepingWavetable },
  { &Osc::UpdateSweepingWavetable, &Osc::RenderSweepingWavetable },
  { &Osc::UpdateSweepingWavetable, &Osc::RenderSweepingWavetable },
  { &Osc::UpdateSweepingWavetable, &Osc::RenderSweepingWavetable },
  { &Osc::UpdateSweepingWavetable, &Osc::RenderSweepingWavetable },
  { &Osc::UpdateSweepingWavetable, &Osc::RenderSweepingWavetable },
  { &Osc::UpdateSweepingWavetable, &Osc::RenderSweepingWavetable },
  { &Osc::UpdateSweepingWavetableRam, &Osc::RenderSweepingWavetableRam },
  
  { &Osc::UpdateSilence, &Osc::Render8BitLand },
  { &Osc::UpdateSilence, &Osc::RenderCrushedSine },
  { &Osc::UpdateSilence, &Osc::RenderDirtyPwm },
  { &Osc::UpdateSilence, &Osc::RenderFilteredNoise },
  
  { &Osc::UpdateVowel, &Osc::RenderVowel },
};

template<int id>
class SubOscillator {
 public:
  SubOscillator() { }

  // Called whenever the parameters of the oscillator change. Can be used
  // to pre-compute parameters, set tables, etc.
  static inline void SetupAlgorithm(uint8_t shape) {
    shift_ = 0;
    if (shape >= 3) {
      shift_ = 1;
      shape -= 3;
    }
    is_square_ = shape != 1;
    pulse_width_ = shape == 0 ? 0x80 : 0x40;
  }
  static inline uint8_t Render(uint8_t* buffer, uint8_t size) {
    while (size--) {
      phase_ = Add24(phase_, phase_increment_);
      if (is_square_) {
        *buffer++ = \
            static_cast<uint8_t>(phase_.integral >> 8) < pulse_width_ ? 0 : 255;
      } else {
        *buffer++ = phase_.integral & 0x8000
          ? phase_.integral >> 7
          : ~static_cast<uint8_t>(phase_.integral >> 7);
      }
    }
  }
  static inline void Update(
      uint8_t parameter,
      uint16_t integral,
      uint8_t fractional) {
    phase_increment_.integral = integral;
    phase_increment_.fractional = fractional;
    if (shift_) {
      phase_increment_ = Lsr24(phase_increment_);
    }
  }

 private:
  // Current phase of the oscillator.
  static uint24_t phase_;
  static uint24_t phase_increment_;

  static uint8_t shift_;
  static uint8_t pulse_width_;
  static uint8_t is_square_;

  DISALLOW_COPY_AND_ASSIGN(SubOscillator);
};

/* <static> */
template<int id> uint24_t SubOscillator<id>::phase_;
template<int id> uint24_t SubOscillator<id>::phase_increment_;
template<int id> uint8_t SubOscillator<id>::shift_;
template<int id> uint8_t SubOscillator<id>::pulse_width_;
template<int id> uint8_t SubOscillator<id>::is_square_;

/* </static> */

}  // namespace hardware_shruthi

#endif  // HARDWARE_SHRUTHI_OSCILLATOR_H_
