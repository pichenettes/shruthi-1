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
  uint16_t rng_state;
  uint16_t rng_reset_value;
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

class Oscillator {
 public:
  typedef void (Oscillator::*RenderFn)(uint8_t*);
   
  Oscillator() { }
  ~Oscillator() { }
  
  inline void Reset() {
    data_.no.rng_reset_value = Random::GetByte() + 1;
  }

  inline void Render(
      uint8_t shape,
      uint8_t note,
      uint24_t increment,
      uint8_t* sync_input,
      uint8_t* sync_output,
      uint8_t* buffer) {
    shape_ = shape;
    note_ = note;
    phase_increment_ = increment;
    sync_input_ = sync_input;
    sync_output_ = sync_output;
    // A hack: when pulse width is set to 0, use a simple wavetable.
    if (shape_ == WAVEFORM_SQUARE) {
      uint8_t shape = shape_;
      if (parameter_ == 0) {
        RenderSimpleWavetable(buffer);
      } else {
        RenderBandlimitedPwm(buffer);
      }
    } else {
      uint8_t index = shape > WAVEFORM_VOWEL ? WAVEFORM_WAVETABLE_1 : shape;
      RenderFn fn;
      ResourcesManager::Load(fn_table_, index, &fn);
      (this->*fn)(buffer);
    }
  }
  
  inline void set_parameter(uint8_t parameter) {
    parameter_ = parameter;
  }
  
  inline void set_secondary_parameter(uint8_t secondary_parameter) {
    secondary_parameter_ = secondary_parameter;
  }
  
 private:
  // Current phase of the oscillator.
  uint24_t phase_;

  // Phase increment (and phase increment x 2, for low-sr oscillators).
  uint24_t phase_increment_;

  // Copy of the shape used by this oscillator. When changing this, you
  // should also update the Update/Render pointers.
  uint8_t shape_;

  // Current value of the oscillator parameter.
  uint8_t parameter_;
  uint8_t secondary_parameter_;
  uint8_t note_;

  // Union of state data used by each algorithm.
  OscillatorState data_;

  // A pointer to the render function.
  static RenderFn fn_table_[];
  
  // A flag set to true when sync is enabled ; and a table to record the
  // position of phrase wraps
  uint8_t* sync_input_;
  uint8_t* sync_output_;
  
  void RenderSilence(uint8_t* buffer);
  
  // Since this is the most computationally expensive function, we still
  // duplicated it into a "master" and a "slave" version for OSC1 and OSC2,
  // with the corresponding oscillators sync code stripped away.
  void RenderBandlimitedPwm(uint8_t* buffer);
  
  void RenderSimpleWavetable(uint8_t* buffer);
  void RenderInterpolatedWavetable(uint8_t* buffer);
  void RenderSweepingWavetableRam(uint8_t* buffer);
  void RenderCzSaw(uint8_t* buffer);
  void RenderCzPulseReso(uint8_t* buffer);
  void RenderCzReso(uint8_t* buffer);
  void RenderFm(uint8_t* buffer);
  void Render8BitLand(uint8_t* buffer);
  void RenderCrushedSine(uint8_t* buffer);
  void RenderVowel(uint8_t* buffer);
  void RenderDirtyPwm(uint8_t* buffer);
  void RenderQuadSawPad(uint8_t* buffer);
  void RenderFilteredNoise(uint8_t* buffer);

  DISALLOW_COPY_AND_ASSIGN(Oscillator);
};

}  // namespace shruthi

#endif // SHRUTHI_OSCILLATOR_H_
