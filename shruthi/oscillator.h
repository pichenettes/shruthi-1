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

#ifndef SHRUTHI_OSCILLATOR_H_
#define SHRUTHI_OSCILLATOR_H_

#include "avrlib/base.h"
#include "shruthi/shruthi.h"

#include "shruthi/patch.h"
#include "shruthi/resources.h"
#include "shruthi/synthesis_engine.h"
#include "avrlib/random.h"
#include "avrlib/op.h"

using namespace avrlib;

static const uint16_t kWavetableSize = 16 * 129;
static const uint16_t kUserWavetableSize = 8 * 129;

namespace shruthi {

#define WAV_RES_SINE WAV_RES_BANDLIMITED_TRIANGLE_6


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

static const uint8_t kVowelControlRateDecimation = 4;
static const uint8_t kNumZonesFullSampleRate = 6;
static const uint8_t kNumZonesHalfSampleRate = 5;

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
};

typedef void (*OscRenderFn)(uint8_t* buffer);

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
    // A hack: when pulse width is set to 0, use a simple wavetable.
    if (shape_ == WAVEFORM_SQUARE) {
      uint8_t shape = shape_;
      if (parameter_ == 0) {
        RenderSimpleWavetable(buffer);
      } else {
        RenderBandlimitedPwm(buffer);
      }
    } else {
      OscRenderFn fn = fn_table_[
          shape > WAVEFORM_VOWEL ? WAVEFORM_WAVETABLE_1 : shape];
      (*fn)(buffer);
    }
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
  static OscillatorState data_;

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

  // ------- Band-limited PWM --------------------------------------------------
  static void RenderBandlimitedPwm(uint8_t* buffer) {
    uint8_t balance_index = U8Swap4(note_ - 12);
    uint8_t gain_2 = balance_index & 0xf0;
    uint8_t gain_1 = ~gain_2;

    uint8_t wave_index = balance_index & 0xf;
    const prog_uint8_t* wave_1 = waveform_table[
        WAV_RES_BANDLIMITED_SAW_1 + wave_index];
    wave_index = U8AddClip(wave_index, 1, kNumZonesHalfSampleRate);
    const prog_uint8_t* wave_2 = waveform_table[
        WAV_RES_BANDLIMITED_SAW_1 + wave_index];
    
    uint16_t shift = static_cast<uint16_t>(parameter_ + 128) << 8;
    // For higher pitched notes, simply use 128
    uint8_t scale = 192 - (parameter_ >> 1);
    if (note_ > 64) {
      scale = U8Mix(scale, 102, (note_ - 64) << 2);
      scale = U8Mix(scale, 102, (note_ - 64) << 2);
    }
    uint8_t size = kAudioBlockSize;
    while (size) {
      UpdatePhase();
      UpdatePhase();
      uint8_t a = InterpolateTwoTables(
          wave_1, wave_2,
          phase_.integral, gain_1, gain_2);
      
      a = U8U8MulShift8(a, scale);
      // This was used in the previous version, doesn't sound much worse
      // and could save 100 bytes. Using the crossfaded version for sake of
      // correctness.
      // uint8_t b = InterpolateSample(wave_1, phase_.integral + shift);
      uint8_t b = InterpolateTwoTables(
          wave_1, wave_2,
          phase_.integral + shift, gain_1, gain_2);
      b = U8U8MulShift8(b, scale);
      a = a - b + 128;
      *buffer++ = a;
      *buffer++ = a;
      size -= 2;
    }
  }

  // ------- Interpolation between two waveforms from two wavetables -----------
  // The position is determined by the note pitch, to prevent aliasing.

  static void RenderSimpleWavetable(uint8_t* buffer) {
    uint8_t balance_index = U8Swap4(note_ - 12);
    uint8_t gain_2 = balance_index & 0xf0;
    uint8_t gain_1 = ~gain_2;

    uint8_t wave_index = balance_index & 0xf;
    uint8_t base_resource_id = shape_ == WAVEFORM_SAW ?
        WAV_RES_BANDLIMITED_SAW_0 :
        (shape_ == WAVEFORM_SQUARE ? WAV_RES_BANDLIMITED_SQUARE_0  : 
        WAV_RES_BANDLIMITED_TRIANGLE_0);

    const prog_uint8_t* wave_1 = waveform_table[base_resource_id + wave_index];
    wave_index = U8AddClip(wave_index, 1, kNumZonesFullSampleRate);
    const prog_uint8_t* wave_2 = waveform_table[base_resource_id + wave_index];
    
    uint8_t size = kAudioBlockSize;
    while (size--) {
      UpdatePhase();
      uint8_t sample = InterpolateTwoTables(
          wave_1, wave_2,
          phase_.integral, gain_1, gain_2);
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
      *buffer++ = ReadSample(waveform_table[WAV_RES_SINE],
          U8MixU16(phase, clipped_phase, parameter_ << 1));
    }
  }
  
  static void RenderCzPulseReso(uint8_t* buffer) {
    uint16_t increment = UpdateCz() << 1;
    uint8_t size = kAudioBlockSize;
    while (size--) {
      if (UpdatePhase()) {
        data_.secondary_phase = 32768;
      }
      data_.secondary_phase += increment;
      uint8_t result = ReadSample(
          waveform_table[WAV_RES_SINE],
          data_.secondary_phase);
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
  
  static void RenderCzSawReso(uint8_t* buffer) {
    uint16_t increment = UpdateCz();
    uint8_t size = kAudioBlockSize;
    while (size--) {
      if (UpdatePhase()) {
        data_.secondary_phase = 0;
      }
      data_.secondary_phase += increment;
      uint8_t result = InterpolateSample(
          waveform_table[WAV_RES_SINE],
          data_.secondary_phase);
      *buffer++ = U8U8MulShift8(result, ~(phase_.integral >> 8));
    }
  }
  
  static void RenderCzTriReso(uint8_t* buffer) {
    uint16_t increment = UpdateCz();
    uint8_t size = kAudioBlockSize;
    while (size--) {
      if (UpdatePhase()) {
        data_.secondary_phase = 0;
      }
      data_.secondary_phase += increment;
      uint8_t result = InterpolateSample(
          waveform_table[WAV_RES_SINE],
          data_.secondary_phase);
      uint8_t triangle =  (phase_.integral & 0x8000) ?
            ~static_cast<uint8_t>(phase_.integral >> 7) :
            phase_.integral >> 7;
      *buffer++ = U8U8MulShift8(result, triangle);
    }
  }

  static void RenderCzSyncReso(uint8_t* buffer) {
    uint16_t increment = UpdateCz();
    uint8_t size = kAudioBlockSize;
    while (size--) {
      if (UpdatePhase()) {
        data_.secondary_phase = 0;
      }
      data_.secondary_phase += increment;
      uint8_t result = InterpolateSample(
          waveform_table[WAV_RES_SINE],
          data_.secondary_phase);
      *buffer++ = phase_.integral < 0x8000 ? result : 128;
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
      data_.secondary_phase += increment;
      uint8_t modulator = InterpolateSample(waveform_table[WAV_RES_SINE],
          data_.secondary_phase);
      uint16_t modulation = modulator * parameter_;
      *buffer++ = InterpolateSample(waveform_table[WAV_RES_SINE],
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
  
  static void RenderVowel(uint8_t* buffer) {
    if (id == 2) {
      return;  // Do not duplicate this code for the second oscillator.
    }
    data_.vw.update++;
    if (data_.vw.update == kVowelControlRateDecimation) {
      data_.vw.update = 0;
      uint8_t offset_1 = U8ShiftRight4(parameter_);
      offset_1 = (offset_1 << 2) + offset_1;  // offset_1 * 5
      uint8_t offset_2 = offset_1 + 5;
      uint8_t balance = parameter_ & 15;
      for (uint8_t i = 0; i < 3; ++i) {
        data_.vw.formant_increment[i] = U8U4MixU12(
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

        data_.vw.formant_amplitude[2 * i + 1] = U8U4MixU8(
            amplitude_a & 0x0f,
            amplitude_b & 0x0f, balance);
        amplitude_a = U8ShiftRight4(amplitude_a);
        amplitude_b = U8ShiftRight4(amplitude_b);
        data_.vw.formant_amplitude[2 * i] = U8U4MixU8(
            amplitude_a,
            amplitude_b, balance);
      }
    }
    uint8_t size = kAudioBlockSize;
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
      result = S8U8MulShift8(result, ~(phase_.integral >> 8));
      phase_.integral += phase_increment_.integral;
      int16_t phase_noise = int8_t(Random::state_msb()) *
          int8_t(data_.vw.noise_modulation);
      if ((phase_.integral + phase_noise) < phase_increment_.integral) {
        data_.vw.formant_phase[0] = 0;
        data_.vw.formant_phase[1] = 0;
        data_.vw.formant_phase[2] = 0;
      }
      uint8_t x = S16ClipS8(4 * result) + 128;
      *buffer = x;
      *buffer = x;
      buffer += 2;
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
      data_.qs.phase[0] += increments[0];
      data_.qs.phase[1] += increments[1];
      data_.qs.phase[2] += increments[2];
      uint8_t value = (phase_.integral >> 10);
      value += (data_.qs.phase[0] >> 10);
      value += (data_.qs.phase[1] >> 10);
      value += (data_.qs.phase[2] >> 10);
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
      data_.no.lp_noise_sample = U8Mix(
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
template<int id> uint8_t Oscillator<id>::secondary_parameter_;
template<int id> uint8_t Oscillator<id>::note_;
template<int id> uint8_t* Oscillator<id>::sync_state_;

template<int id> OscillatorState Oscillator<id>::data_;

template<int id> OscRenderFn Oscillator<id>::fn_table_[] = {
  &Osc::RenderSilence,

  &Osc::RenderSimpleWavetable,
  &Osc::RenderBandlimitedPwm,
  &Osc::RenderSimpleWavetable,

  &Osc::RenderCzSaw,
  &Osc::RenderCzSawReso,
  &Osc::RenderCzTriReso,
  &Osc::RenderCzPulseReso,
  &Osc::RenderCzSyncReso,
  
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

template<int id>
class SubOscillator {
 public:
  SubOscillator() { }

  // Called whenever the parameters of the oscillator change. Can be used
  // to pre-compute parameters, set tables, etc.
  static inline void SetupAlgorithm() {
  }
  
  static inline void Render(
      uint8_t shape,
      uint24_t increment,
      uint8_t* buffer) {
    if (shape >= 3) {
      increment = U24ShiftRight(increment);
      shape -= 3;
    }
    uint8_t pulse_width = shape == 0 ? 0x80 : 0x40;
    uint8_t size = kAudioBlockSize;
    while (size--) {
      phase_ = U24Add(phase_, increment);
      if (shape != 1) {
        *buffer++ = \
            static_cast<uint8_t>(phase_.integral >> 8) < pulse_width ? 0 : 255;
      } else {
        uint8_t tri = phase_.integral >> 7;
        *buffer++ = phase_.integral & 0x8000 ? tri : ~tri;
      }
    }
  }

 private:
  // Current phase of the oscillator.
  static uint24_t phase_;

  DISALLOW_COPY_AND_ASSIGN(SubOscillator);
};

/* <static> */
template<int id> uint24_t SubOscillator<id>::phase_;

/* </static> */

}  // namespace shruthi

#endif // SHRUTHI_OSCILLATOR_H_
