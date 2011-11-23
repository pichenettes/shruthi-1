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

#ifndef OSCLAB_OSCILLATOR_H_
#define OSCLAB_OSCILLATOR_H_

#include "avrlib/base.h"
#include "osclab/osclab.h"

#include "osclab/patch.h"
#include "osclab/resources.h"
#include "avrlib/random.h"
#include "avrlib/op.h"

using namespace avrlib;

static const uint16_t kWavetableSize = 16 * 129;
static const uint16_t kUserWavetableSize = 8 * 129;

namespace osclab {

static inline uint8_t ReadSample(
    const prog_uint8_t* table,
    uint16_t phase) __attribute__((always_inline));
static inline uint8_t ReadSample(
    const prog_uint8_t* table,
    uint16_t phase) {
  return ResourcesManager::Lookup<uint8_t, uint8_t>(table, phase >> 8);
}

extern uint8_t user_wavetable[];

#ifdef USE_OPTIMIZED_OP

static inline uint8_t InterpolateSampleRam(
    const uint8_t* table,
    uint16_t phase) __attribute__((always_inline));


static inline uint8_t InterpolateSampleRam(
    const uint8_t* table,
    uint16_t phase) {
  uint8_t result;
  uint8_t work;
  asm(
    "movw r30, %A2"           "\n\t"  // copy base address to r30:r31
    "add r30, %B3"            "\n\t"  // increment table address by phaseH
    "adc r31, r1"             "\n\t"  // just carry
    "mov %1, %A3"             "\n\t"  // move phaseL to working register
    "ld %0, z+"               "\n\t"  // load sample[n]
    "ld r1, z+"               "\n\t"  // load sample[n+1]
    "mul %1, r1"              "\n\t"  // multiply second sample by phaseL
    "movw r30, r0"            "\n\t"  // result to accumulator
    "com %1"                  "\n\t"  // 255 - phaseL -> phaseL
    "mul %1, %0"              "\n\t"  // multiply first sample by phaseL
    "add r30, r0"             "\n\t"  // accumulate L
    "adc r31, r1"             "\n\t"  // accumulate H
    "eor r1, r1"              "\n\t"  // reset r1 after multiplication
    "mov %0, r31"             "\n\t"  // use sum H as output
    : "=r" (result), "=r" (work)
    : "r" (table), "r" (phase)
    : "r30", "r31"
  );
  return result;
}

#else

static inline uint8_t InterpolateSampleRam(
    const uint8_t* table,
    uint16_t phase) {
  return U8Mix(table[phase >> 8], table[1 + (phase >> 8)], phase & 0xff);
}
#endif  // USE_OPTIMIZED_OP

static inline uint8_t InterpolateTwoTables(
    const prog_uint8_t* table_a, const prog_uint8_t* table_b,
    uint16_t phase, uint8_t gain_a, uint8_t gain_b) {
  return U8Mix(
      InterpolateSample(table_a, phase),
      InterpolateSample(table_b, phase),
      gain_a, gain_b);
}

static const uint8_t kNumZonesFullSampleRate = 6;
static const uint8_t kNumZonesHalfSampleRate = 5;
static const uint8_t kNumBleps = 2;

struct Blep {
  uint16_t phase;
  int8_t scale;
};

struct BlepOscillator {
  uint8_t lru_blep;
  uint8_t up;
  Blep blep_pool[kNumBleps];
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
  uint16_t phase[3];
};

struct CrushedSineState {
  uint8_t decimate;
  uint8_t state;
};

union OscillatorState {
  VowelSynthesizerState vw;
  FilteredNoiseState no;
  QuadSawPadState qs;
  CrushedSineState cr;
  uint16_t secondary_phase;
  BlepOscillator bl;
};

typedef void (*OscRenderFn)(uint8_t* buffer);


#define ACCUMULATE_BLEP(index) \
if (state_.bl.blep_pool[index].scale) { \
  int16_t value = ResourcesManager::Lookup<uint16_t, int16_t>( \
      lut_res_blep, state_.bl.blep_pool[index].phase); \
  output += S16S8MulShift8(value, state_.bl.blep_pool[index].scale) << 1; \
  state_.bl.blep_pool[index].phase += 256; \
  if (state_.bl.blep_pool[index].phase > LUT_RES_BLEP_SIZE) { \
    state_.bl.blep_pool[index].scale = 0; \
  } \
}

template<int id>
class Oscillator {
 public:
  Oscillator() { }

  static inline void Render(
      uint8_t shape,
      uint8_t note,
      uint24_t increment,
      uint8_t* sync_state,
      uint8_t* buffer) {
    shape_ = shape;
    note_ = note;
    phase_increment_ = increment;
    sync_state_ = sync_state;
    OscRenderFn fn = fn_table_[
        shape > WAVEFORM_VOWEL ? WAVEFORM_WAVETABLE_1 : shape];
    (*fn)(buffer);
  }
  
  static inline void set_parameter(uint8_t parameter) {
    parameter_ = parameter;
  }
  
  static inline void set_secondary_parameter(uint8_t secondary_parameter) {
    secondary_parameter_ = secondary_parameter;
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

  // Current value of the oscillator parameter.
  static uint8_t parameter_;
  static uint8_t secondary_parameter_;
  static uint8_t note_;

  // Union of state data used by each algorithm.
  static OscillatorState state_;

  // A pointer to the render function.
  static OscRenderFn fn_table_[];
  
  // A flag set to true when sync is enabled ; and a table to record the
  // position of phrase wraps
  static uint8_t* sync_state_;

  static inline uint8_t UpdatePhase() __attribute__((always_inline)) {
    if (id == 1) {
      uint24c_t phi = U24AddC(phase_, phase_increment_);
      *sync_state_++ = phi.carry;
      phase_.fractional = phi.fractional;
      phase_.integral = phi.integral;
      return phi.carry;
    } else {
      if (*sync_state_++) {
        phase_.integral = 0;
        phase_.fractional = 0;
        return 1;
      }
      uint24c_t phi = U24AddC(phase_, phase_increment_);
      phase_.fractional = phi.fractional;
      phase_.integral = phi.integral;
      return phi.carry;
    }
  }
  
  // ------- Silence (useful when processing external signals) -----------------
  static void RenderSilence(uint8_t* buffer) {
    uint8_t size = kAudioBlockSize;
    while (size--) {
      *buffer++ = 128;
    }
  }
  
  // ------- BLEP oscillators --------------------------------------------------
  static inline void AddBlep(
      uint24_t phase_residue,
      int8_t scale) __attribute__((always_inline)) {
    // The code that follows computes phase_residue / phase_increment * 256.
    // It works by:
    // - Shifting phase_residue and phase_residue until they are in the 
    //   [0-255] range (using the property a / b ~= (a >> 1) / (b >> 1))
    // - Using a lookup table for computing the reciprocal of phase_increment
    //   and multiplying it by phase_residue to compute the division.
    uint16_t a, b;
    if (static_cast<uint8_t>(phase_increment_.integral >> 8) & 0xff) {
      a = phase_residue.integral;
      b = phase_increment_.integral;
    } else {
      a = (phase_residue.integral << 8) | phase_residue.fractional;
      b = (phase_increment_.integral << 8) | phase_increment_.fractional;
    }
    while (static_cast<uint8_t>(b >> 8)) {
      b >>= 1;
      a >>= 1;
    }
    
    // At this stage, b < 256. There are situations where a > b -- this happens
    // for example when PWM is modulated and there is suddenly a large
    // difference between the phase counter and the pulse width comparator
    // position.
    uint16_t blep_phase = 0;
    while (a > b) {
      blep_phase += 256;
      a -= b;
    }
    blep_phase += U16U8MulShift8(
        ResourcesManager::Lookup<uint16_t, uint8_t>(lut_res_reciprocal, b), a);
    state_.bl.lru_blep = (state_.bl.lru_blep + 1) % kNumBleps;
    Blep& blep = state_.bl.blep_pool[state_.bl.lru_blep];
    blep.phase = blep_phase;
    blep.scale = scale;
  }
  
  static void RenderBandlimitedPwm(uint8_t* buffer) {
    uint8_t size = kAudioBlockSize;
    uint8_t pw = 128 - parameter_;
    while (size--) {
      uint8_t wrap = UpdatePhase();
      if (state_.bl.up) {
        // Add a blep from up to down when the phase exceeds the pulse width.
        if (static_cast<uint8_t>(phase_.integral >> 8) >= pw) {
          uint24_t offset;
          offset.integral = pw << 8;
          offset.fractional = 0;
          AddBlep(U24Sub(phase_, offset), 127);
          state_.bl.up = 0;
        }
      } else {
        // Add a blep from down to up when there is a phase reset.
        if (wrap) {
          AddBlep(phase_, -127);
          state_.bl.up = 1;
        }
      }
      int16_t output = state_.bl.up ? 16383 : -16384;
      ACCUMULATE_BLEP(0)
      ACCUMULATE_BLEP(1)
      *buffer++ = (output >> 8) + 128;
    }
  }

  static void RenderBandlimitedSaw(uint8_t* buffer) {
    uint8_t size = kAudioBlockSize;
    while (size--) {
      uint8_t previous_position = phase_.integral >> 9;
      if (UpdatePhase()) {
        AddBlep(phase_, previous_position);
      }
      int16_t output = (phase_.integral >> 1) - 16384;
      ACCUMULATE_BLEP(0)
      ACCUMULATE_BLEP(1)
      *buffer++ = (output >> 8) + 128;
    }
  }

  // ------- Interpolation between two waveforms from two wavetables -----------
  static void RenderInterpolatedWavetable(uint8_t* buffer) {
    uint8_t index = shape_ >= WAVEFORM_WAVETABLE_9 ? 
        shape_ - WAVEFORM_WAVETABLE_9 + 8 :
        shape_ - WAVEFORM_WAVETABLE_1;
    
    // Which wavetable should we play?.
    const prog_uint8_t* wavetable_definition = 
        wav_res_wavetables + U8U8Mul(index, 18);
    // Get a 8:8 value with the wave index in the first byte, and the
    // balance amount in the second byte.
    uint8_t num_steps = ResourcesManager::Lookup<uint8_t, uint8_t>(
        wavetable_definition,
        0);
    uint16_t pointer = U8U8Mul(parameter_ << 1, num_steps);
    uint16_t wave_index_1 = ResourcesManager::Lookup<uint8_t, uint8_t>(
        wavetable_definition,
        1 + (pointer >> 8));
    uint16_t wave_index_2 = ResourcesManager::Lookup<uint8_t, uint8_t>(
        wavetable_definition,
        2 + (pointer >> 8));
    uint8_t gain_2 = pointer & 0xff;
    uint8_t gain_1 = ~gain_2;
    const prog_uint8_t* wave_1 = wav_res_waves + U8U8Mul(
        wave_index_1,
        129);
    const prog_uint8_t* wave_2 = wav_res_waves + U8U8Mul(
        wave_index_2,
        129);
    uint8_t size = kAudioBlockSize;
    while (size--) {
      UpdatePhase();
      uint16_t phase = phase_.integral;
      phase >>= 1;
      *buffer++ = InterpolateTwoTables(wave_1, wave_2, phase, gain_1, gain_2);
    }
  }  
  // The position is freely determined by the parameter
  static void RenderSweepingWavetableRam(uint8_t* buffer) {
    uint8_t balance_index = U8Swap4(parameter_);
    uint8_t wave_index = balance_index & 0xf;
    uint8_t gain_2 = balance_index & 0xf0;
    uint8_t gain_1 = ~gain_2;
    
    uint16_t offset = wave_index << 7;
    offset += wave_index;
    const uint8_t* wave_1 = user_wavetable + offset;
    const uint8_t* wave_2 = wave_1;
    if (offset < kUserWavetableSize - 129) {
      wave_2 += 129;
    }
    
    uint8_t size = kAudioBlockSize;
    while (size--) {
      UpdatePhase();
      uint16_t phase = phase_.integral;
      phase >>= 1;
      *buffer++ = U8Mix(
          InterpolateSampleRam(wave_1, phase),
          InterpolateSampleRam(wave_2, phase),
          gain_1, gain_2);
    }
  }

  // ------- Casio CZ-like synthesis -------------------------------------------
  static uint16_t UpdateCz() __attribute__((noinline)) {
    return phase_increment_.integral + (
        (phase_increment_.integral * uint32_t(parameter_)) >> 3);
  }
  
  static void RenderCzSaw(uint8_t* buffer) {
    uint8_t size = kAudioBlockSize;
    while (size--) {
      UpdatePhase();
      uint8_t phase = phase_.integral >> 8;
      uint8_t clipped_phase = phase < 0x20 ? phase << 3 : 0xff;
      // Interpolation causes more aliasing here.
      *buffer++ = ReadSample(wav_res_sine,
          U8MixU16(phase, clipped_phase, parameter_ << 1));
    }
  }
  
  static void RenderCzPulseReso(uint8_t* buffer) {
    uint16_t increment = UpdateCz() << 1;
    uint8_t size = kAudioBlockSize;
    while (size--) {
      if (UpdatePhase()) {
        state_.secondary_phase = 32768;
      }
      state_.secondary_phase += increment;
      uint8_t result = ReadSample(wav_res_sine, state_.secondary_phase);
      result >>= 1;
      result += 128;   
      if (phase_.integral < 0x4000) {
        *buffer = result;
      } else if (phase_.integral < 0x8000) {
        *buffer = U8U8MulShift8(result, ~(phase_.integral - 0x4000) >> 6);
      } else {
        *buffer = 0;
      }
      ++buffer;
    }
  }
  
  static void RenderCzReso(uint8_t* buffer) {
    uint16_t increment = UpdateCz();
    uint8_t size = kAudioBlockSize;
    while (size--) {
      if (UpdatePhase()) {
        state_.secondary_phase = 0;
      }
      state_.secondary_phase += increment;
      uint8_t carrier = InterpolateSample(wav_res_sine, state_.secondary_phase);
      if (shape_ == WAVEFORM_CZ_SYNC) {
        *buffer++ = phase_.integral < 0x8000 ? carrier : 128;
      } else {
        uint8_t window = 0;
        if (shape_ == WAVEFORM_CZ_RESO) {
          window = ~(phase_.integral >> 8);
        } else {
          window = (phase_.integral & 0x8000) ?
                ~static_cast<uint8_t>(phase_.integral >> 7) :
                phase_.integral >> 7;
        }
        *buffer++ = U8U8MulShift8(carrier, window);
      }
    }
  }
  
  // ------- FM ----------------------------------------------------------------
  static void RenderFm(uint8_t* buffer) {
    uint8_t offset = secondary_parameter_;
    if (offset < 12) {
      offset = 0;
    } else if (offset > 36) {
      offset = 24;
    } else {
      offset = offset - 12;
    }
    uint16_t multiplier = ResourcesManager::Lookup<uint16_t, uint8_t>(
        lut_res_fm_frequency_ratios, offset);
    uint16_t increment = (
        static_cast<int32_t>(phase_increment_.integral) * multiplier) >> 8;
    parameter_ <<= 1;
    
    // The modulator will have a 16 bits phase increment, so we need to drop
    // the fractional part to 0 to ensure that the modulator frequency is
    // the correct multiple of the carrier frequency.
    phase_.fractional = 0;
    uint8_t size = kAudioBlockSize;
    while (size--) {
      UpdatePhase();
      state_.secondary_phase += increment;
      uint8_t modulator = InterpolateSample(wav_res_sine,
          state_.secondary_phase);
      uint16_t modulation = modulator * parameter_;
      *buffer++ = InterpolateSample(wav_res_sine,
          phase_.integral + modulation);
    }
  }

  // ------- 8-bit land --------------------------------------------------------
  static void Render8BitLand(uint8_t* buffer) {
    uint8_t size = kAudioBlockSize;
    while (size--) {
      UpdatePhase();
      uint8_t x = parameter_;
      *buffer++ = (((phase_.integral >> 8) ^ (x << 1)) & (~x)) + (x >> 1);
    }
  }

  // ------- 8-bit land --------------------------------------------------------
  static void RenderCrushedSine(uint8_t* buffer) {
    uint8_t size = kAudioBlockSize;
    while (size--) {
      UpdatePhase();
      ++state_.cr.decimate;
      if (parameter_ <= 63) {
        if (state_.cr.decimate >= parameter_ + 1) {
          state_.cr.decimate = 0;
          state_.cr.state = InterpolateSample(wav_res_sine, phase_.integral);
        }
      } else {
        if (state_.cr.decimate >= 128 - parameter_) {
          state_.cr.decimate = 0;
          state_.cr.state = InterpolateSample(wav_res_triangle, phase_.integral);
        }
      }
      *buffer++ = state_.cr.state;
    }
  }
  
  static void RenderVowel(uint8_t* buffer) {
    if (id == 2) {
      return;  // Do not duplicate this code for the second oscillator.
    }
    state_.vw.update = (state_.vw.update + 1) & 3;
    if (!state_.vw.update) {
      uint8_t offset_1 = U8ShiftRight4(parameter_);
      offset_1 = U8U8Mul(offset_1, 7);
      uint8_t offset_2 = offset_1 + 7;
      uint8_t balance = parameter_ & 15;
      
      // Interpolate formant frequencies.
      for (uint8_t i = 0; i < 3; ++i) {
        state_.vw.formant_increment[i] = U8U4MixU12(
            ResourcesManager::Lookup<uint8_t, uint8_t>(
                wav_res_vowel_data, offset_1 + i),
            ResourcesManager::Lookup<uint8_t, uint8_t>(
                wav_res_vowel_data, offset_2 + i),
            balance);
        state_.vw.formant_increment[i] <<= 3;
      }
      
      // Interpolate formant amplitudes.
      for (uint8_t i = 0; i < 4; ++i) {
        uint8_t amplitude_a = ResourcesManager::Lookup<uint8_t, uint8_t>(
            wav_res_vowel_data,
            offset_1 + 3 + i);
        uint8_t amplitude_b = ResourcesManager::Lookup<uint8_t, uint8_t>(
            wav_res_vowel_data,
            offset_2 + 3 + i);
        state_.vw.formant_amplitude[i] = U8U4MixU8(
            amplitude_a,
            amplitude_b, balance);
      }
    }
    uint8_t size = kAudioBlockSize;
    while (size) {
      int8_t result = 0;
      for (uint8_t i = 0; i < 3; ++i) {
        state_.vw.formant_phase[i] += state_.vw.formant_increment[i];
        result += ResourcesManager::Lookup<uint8_t, uint8_t>(
            i == 2 ? wav_res_formant_square : wav_res_formant_sine,
            ((state_.vw.formant_phase[i] >> 8) & 0xf0) |
              state_.vw.formant_amplitude[i]);
      }
      result = S8U8MulShift8(result, ~(phase_.integral >> 8));
      phase_.integral += phase_increment_.integral;
      int16_t phase_noise = int8_t(Random::state_msb()) *
          int8_t(state_.vw.noise_modulation);
      if ((phase_.integral + phase_noise) < phase_increment_.integral) {
        state_.vw.formant_phase[0] = 0;
        state_.vw.formant_phase[1] = 0;
        state_.vw.formant_phase[2] = 0;
      }
      uint8_t x = S16ClipS8(4 * result) + 128;
      *buffer++ = x;
      *buffer++ = x;
      size -= 2;
    }
  }

  // ------- Dirty Pwm (kills kittens) -----------------------------------------
  static void RenderDirtyPwm(uint8_t* buffer) {
    uint8_t size = kAudioBlockSize;
    while (size--) {
      UpdatePhase();
      *buffer++ = (phase_.integral >> 8) < 127 + parameter_ ? 0 : 255;
    }
  }
  
  // ------- Quad saw (mit aliasing) -------------------------------------------
  static void RenderQuadSawPad(uint8_t* buffer) {
    uint16_t phase_spread = (
        static_cast<uint32_t>(phase_increment_.integral) * parameter_) >> 13;
    ++phase_spread;
    uint16_t phase_increment = phase_increment_.integral;
    uint16_t increments[3];
    for (uint8_t i = 0; i < 3; ++i) {
      phase_increment += phase_spread;
      increments[i] = phase_increment;
    }
    
    uint8_t size = kAudioBlockSize;
    while (size--) {
      UpdatePhase();
      state_.qs.phase[0] += increments[0];
      state_.qs.phase[1] += increments[1];
      state_.qs.phase[2] += increments[2];
      uint8_t value = (phase_.integral >> 10);
      value += (state_.qs.phase[0] >> 10);
      value += (state_.qs.phase[1] >> 10);
      value += (state_.qs.phase[2] >> 10);
      *buffer++ = value;
    }
  }

  // ------- Low-passed, then high-passed white noise --------------------------
  static void RenderFilteredNoise(uint8_t* buffer) {
    uint8_t size = kAudioBlockSize;
    while (size--) {
      uint8_t innovation = Random::GetByte();
      // This trick is used to avoid having a DC component (no innovation) when
      // the parameter is set to its minimal or maximal value.
      uint8_t offset = parameter_ == 127 ? 0 : 2;
      state_.no.lp_noise_sample = U8Mix(
          state_.no.lp_noise_sample,
          innovation,
          offset + (parameter_ << 2));
      if (parameter_ >= 64) {
        *buffer++ = innovation - state_.no.lp_noise_sample - 128;
      } else {
        *buffer++ = state_.no.lp_noise_sample;
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
template<int id> uint8_t Oscillator<id>::secondary_parameter_;
template<int id> uint8_t Oscillator<id>::note_;
template<int id> uint8_t* Oscillator<id>::sync_state_;

template<int id> OscillatorState Oscillator<id>::state_;

template<int id> OscRenderFn Oscillator<id>::fn_table_[] = {
  &Osc::RenderSilence,

  &Osc::RenderBandlimitedSaw,
  &Osc::RenderBandlimitedPwm,
  &Osc::RenderBandlimitedSaw,

  &Osc::RenderCzSaw,
  &Osc::RenderCzReso,
  &Osc::RenderCzReso,
  &Osc::RenderCzPulseReso,
  &Osc::RenderCzReso,
  
  &Osc::RenderQuadSawPad,
  
  &Osc::RenderFm,
  
  &Osc::RenderInterpolatedWavetable,
  &Osc::RenderInterpolatedWavetable,
  &Osc::RenderInterpolatedWavetable,
  &Osc::RenderInterpolatedWavetable,
  &Osc::RenderInterpolatedWavetable,
  &Osc::RenderInterpolatedWavetable,
  &Osc::RenderInterpolatedWavetable,
  &Osc::RenderInterpolatedWavetable,
  &Osc::RenderSweepingWavetableRam,
  
  &Osc::Render8BitLand,
  &Osc::RenderCrushedSine,
  &Osc::RenderDirtyPwm,
  &Osc::RenderFilteredNoise,
  
  &Osc::RenderVowel,
  
  &Osc::RenderInterpolatedWavetable,
};

}  // namespace osclab

#endif // OSCLAB_OSCILLATOR_H_
