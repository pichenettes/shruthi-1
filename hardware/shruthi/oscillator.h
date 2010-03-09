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
//
// The template parameter mode determines the features supported by
// an oscillator:
//
//          full      low complexity   sub oscillator
// Blit     sr/2      sr/2             n/a
// Square   sr        sr               sr/4
// Pulse    sr/2      sr/2             n/a
// Saw      sr        sr               n/a
// Triangle sr        sr               sr/4
// CZ       sr        n/a              n/a
// FM       sr        n/a              n/a
// 8-bits   sr        n/a              n/a
// Vowel    sr/2      n/a              n/a
// Table    sr/2      n/a              n/a
// Sweep    ?         n/a              n/a

#ifndef HARDWARE_SHRUTHI_OSCILLATOR_H_
#define HARDWARE_SHRUTHI_OSCILLATOR_H_

#include "hardware/base/base.h"
#include "hardware/shruthi/shruthi.h"

#include "hardware/shruthi/patch.h"
#include "hardware/shruthi/resources.h"
#include "hardware/utils/random.h"
#include "hardware/utils/op.h"

using namespace hardware_utils_op;
using hardware_utils::Random;

namespace hardware_shruthi {

#define WAV_RES_SINE WAV_RES_BANDLIMITED_TRIANGLE_6
#define HALF_SAMPLE_RATE if (engine.oscillator_decimation() & 1) return;
#define FOURTH_SAMPLE_RATE if (engine.oscillator_decimation()) return;

enum OscillatorMode {
  FULL = 0,
  LOW_COMPLEXITY = 1,
  SUB_OSCILLATOR = 2
};

static const uint8_t kVowelControlRateDecimation = 4;
static const uint8_t kNumZonesFullSampleRate = 6;
static const uint8_t kNumZonesHalfSampleRate = 5;

struct PulseSquareOscillatorData {
  const prog_uint8_t* wave[2];
  uint8_t balance;
  uint16_t shift;
  int8_t square;
  uint8_t leak;
};

// Interpolates between two 256-samples wavetables.
struct SawTriangleOscillatorData {
  const prog_uint8_t* wave[2];
  uint8_t balance;
};

// Interpolates between two different points in a 64-samples wavetable.
struct Wavetable64OscillatorData {
  int16_t smooth_parameter;
};

struct CzOscillatorData {
  uint16_t formant_phase;
  uint16_t formant_phase_increment;
};

struct FmOscillatorData {
  uint16_t modulator_phase;
  uint16_t modulator_phase_increment;
};

struct VowelSynthesizerData {
  uint16_t formant_increment[3];
  uint16_t formant_phase[3];
  uint8_t formant_amplitude[3];
  uint8_t noise_modulation;
  uint8_t update;  // Update only every kVowelControlRateDecimation-th call.
};

struct FilteredNoiseData {
  uint8_t lp_noise_sample;
};

union OscillatorData {
  PulseSquareOscillatorData sq;
  SawTriangleOscillatorData st;
  CzOscillatorData cz;
  FmOscillatorData fm;
  VowelSynthesizerData vw;
  Wavetable64OscillatorData wt;
  FilteredNoiseData no;
};

struct AlgorithmFn {
  void (*update)();
  void (*render)();
};

template<int id, OscillatorMode mode>
class Oscillator {
 public:
   Oscillator() { }

   // Called whenever the parameters of the oscillator change. Can be used
   // to pre-compute parameters, set tables, etc.
   static inline void SetupAlgorithm(uint8_t shape) {
     if (shape != shape_ || (sweeping_ && shape != WAVEFORM_ANALOG_WAVETABLE)) {
       shape_ = shape;
       if (mode == FULL) {
         fn_ = fn_table_[shape];
         sweeping_ = shape_ == WAVEFORM_ANALOG_WAVETABLE;
       }
       Reset();
     }
  }
  static inline uint8_t Render() {
    // Updating the phase by the increment here is a bad idea, because it will
    // be reloaded from memory anyway in the oscillator code @@, and because we
    // might use a different increment (FM), or because we might need to
    // check if we have completed a cycle to sync to another waveform.
    if (mode == SUB_OSCILLATOR) {
      RenderSub();
    } else if (mode == LOW_COMPLEXITY) {
      if (shape_corrected_ & 1) {
        RenderPulseSquare();
      } else {
        RenderSimpleWavetable();
      }
    } else {
      (*fn_.render)();
    }
    return held_sample_;
  }
  static inline void Reset() {
    if (mode == FULL && shape_ == WAVEFORM_WAVETABLE) {
      data_.wt.smooth_parameter = parameter_ * 64;
    }
  }
  static inline void Update(
      uint8_t parameter,
      uint8_t note,
      uint16_t increment) {
    note_ = note;

    if (mode == SUB_OSCILLATOR) {
      phase_increment_ = increment << 2;
      UpdateSub();
    } else {
      parameter_ = parameter;
      phase_increment_ = increment;
      phase_increment_2_ = increment << 1;
      if (mode == LOW_COMPLEXITY) {
        if (shape_ == WAVEFORM_SQUARE && parameter_ == 0) {
          shape_corrected_ = shape_ + 1;
        } else {
          shape_corrected_ = shape_;
        }
        if (shape_corrected_ & 1) {
          UpdatePulseSquare();
        } else {
          UpdateSimpleWavetable();
        }
      } else {
        if (sweeping_) {
          shape_ = (parameter >> 5) + 1;
          fn_ = fn_table_[shape_];
          parameter_ = (parameter & 0x1f) << 2;
        }
        // A hack: when pulse width is set to 0, use a simple wavetable.
        if (shape_ == WAVEFORM_SQUARE) {
          fn_ = fn_table_[shape_ + (parameter_ == 0 ? 1 : 0)];
        }
        if (fn_.update) {
          (*fn_.update)();
        }
      }
    }
  }
  static inline void UpdateSecondaryParameter(uint8_t secondary_parameter) {
    if (mode == FULL) {
      data_.fm.modulator_phase_increment = secondary_parameter;
    }
  }
  static inline uint16_t phase() { return phase_; }
  static inline void ResetPhase() { phase_ = 0;  }

 private:
  // Current phase of the oscillator.
  static uint16_t phase_;
  
  // Phase increment (and phase increment x 2, for low-sr oscillators).
  static uint16_t phase_increment_;
  static uint16_t phase_increment_2_;
  
  // Copy of the shape used by this oscillator. When changing this, you
  // should also update the Update/Render pointers.
  static uint8_t shape_;
  static uint8_t shape_corrected_;
  // Whether we are sweeping through the algorithms.
  static uint8_t sweeping_;
  
  // Current value of the oscillator parameter.
  static uint8_t parameter_;
  
  // Sample generated in the previous full call.
  static uint8_t held_sample_;
  
  // Current MIDI note (used for wavetable selection).
  static uint8_t note_;
  
  // Union of state data used by each algorithm.
  static OscillatorData data_;
  
  // A pair of pointers to the update/render functions. update function might be
  // NULL.
  static AlgorithmFn fn_;
  
  static AlgorithmFn fn_table_[];
  
  static inline uint8_t ReadSample(const prog_uint8_t* table, uint16_t phase) {
    return ResourcesManager::Lookup<uint8_t, uint8_t>(table, phase >> 8);
  }
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
#else
  static inline uint8_t InterpolateSample(const prog_uint8_t* table,
                                          uint16_t phase) {
    return Mix(
        ResourcesManager::Lookup<uint8_t, uint8_t>(table, phase >> 8),
        ResourcesManager::Lookup<uint8_t, uint8_t>(table, 1 + (phase >> 8)),
        phase & 0xff);
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
  
  // ------- Silence (useful when processing external signals) -----------------
  static void RenderSilence() {
    held_sample_ = 128;
  }
  
  // ------- Band-limited waveforms with variable pulse width ------------------
  static void UpdatePulseSquare() {
    uint8_t note = note_ - 12;
    data_.sq.leak = 255 - (note >> 3);
    
    uint8_t balance_index = Swap4(note);
    data_.sq.balance = balance_index & 0xf0;
    
    uint8_t wave_index = balance_index & 0xf;
    data_.sq.shift = static_cast<uint16_t>(parameter_ + 127) << 8;
    data_.sq.wave[0] = waveform_table[WAV_RES_BANDLIMITED_PULSE_1 + wave_index];
    wave_index = AddClip(wave_index, 1, kNumZonesHalfSampleRate);
    data_.sq.wave[1] = waveform_table[WAV_RES_BANDLIMITED_PULSE_1 + wave_index];
  }
  static void RenderPulseSquare() {
    HALF_SAMPLE_RATE;
    phase_ += phase_increment_2_;
    
    int16_t blit = InterpolateTwoTables(
        data_.sq.wave[0],
        data_.sq.wave[1],
        phase_,
        data_.sq.balance) - InterpolateSample(
            data_.sq.wave[0],
            phase_ + data_.sq.shift);
    if (shape_ == WAVEFORM_IMPULSE_TRAIN) {
      held_sample_ = Clip8(blit + 128);
    } else {
      int8_t square = SignedClip8(
          SignedMulScale8(data_.sq.square, data_.sq.leak) + blit);
      data_.sq.square = square;
      held_sample_ = square + 128;
    }
  }
  
  // ------- Minimal version of the square and triangle oscillators ------------
  static void UpdateSub() {
    uint8_t balance_index = Swap4(note_);
    data_.st.balance = balance_index & 0xf0;
    
    uint8_t wave_index = balance_index & 0x0f;
    uint8_t base_resource_id = shape_ == WAVEFORM_SQUARE ?
        WAV_RES_BANDLIMITED_SQUARE_1 :
        WAV_RES_BANDLIMITED_TRIANGLE_1;

    wave_index = AddClip(wave_index, 1, kNumZonesHalfSampleRate);
    data_.st.wave[0] = waveform_table[base_resource_id + wave_index];
    wave_index = AddClip(wave_index, 1, kNumZonesHalfSampleRate);
    data_.st.wave[1] = waveform_table[base_resource_id + wave_index];
  }
  static void RenderSub() {
    FOURTH_SAMPLE_RATE;
    phase_ += phase_increment_;
    held_sample_ = InterpolateTwoTables(
        data_.st.wave[0], data_.st.wave[1],
        phase_, data_.st.balance);
  }

  // ------- Interpolation between two waveforms from two wavetables -----------
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
  static void RenderSimpleWavetable() {
    phase_ += phase_increment_;
    uint8_t sample = InterpolateTwoTables(
        data_.st.wave[0], data_.st.wave[1],
        phase_, data_.st.balance);

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
    held_sample_ = sample;
  }

  // ------- Interpolation between two offsets of a wavetable ------------------
  // 64 samples per cycle.
  static void UpdateWavetable64() {
    // Since the wavetable is very crowded (32 waveforms) and the parameter
    // value has a low resolution (4 positions between each waveform), the
    // parameter value is smoothed to avoid rough stepping.
    int16_t target_parameter = parameter_ * 64;
    int16_t increment = target_parameter - data_.wt.smooth_parameter >> 4;
    if (increment == 0) {
      if (target_parameter < data_.wt.smooth_parameter) {
        increment = -1;
      } else if (target_parameter > data_.wt.smooth_parameter) {
        increment = +1;
      }
    }
    data_.wt.smooth_parameter += increment;
  }
  static void RenderWavetable64() {
    HALF_SAMPLE_RATE;
    phase_ += phase_increment_2_;
    
    uint8_t p = data_.wt.smooth_parameter >> 8;
    uint16_t offset_a = (p << 6) + p;  // p * 65
    offset_a += phase_ >> 10;
    const prog_uint8_t* wav_res_wavetable = waveform_table[WAV_RES_WAVETABLE];
    wav_res_wavetable += offset_a;
    uint8_t lo = (phase_ >> 2) & 0xff;
    held_sample_ = InterpolateTwoTables(
        wav_res_wavetable,
        wav_res_wavetable + 65,
        lo,
        data_.wt.smooth_parameter & 0xff);
  }
  
  // ------- Casio CZ-like synthesis -------------------------------------------
  static void UpdateCz() {
    data_.cz.formant_phase_increment = phase_increment_ + (
        (phase_increment_ * uint32_t(parameter_)) >> 3);
  }
  static void RenderCz() {
    uint8_t old_phase_msb = phase_ >> 8;
    phase_ += phase_increment_;
    uint8_t phase_msb = phase_ >> 8;
    if (phase_msb < old_phase_msb) {
      data_.cz.formant_phase = 0;
    }
    // TODO(pichenettes): limit increment to avoid aliasing (this will be
    // equivalent to clipping a VCF control signal).
    data_.cz.formant_phase += data_.cz.formant_phase_increment;
    uint8_t result = InterpolateSample(
        waveform_table[WAV_RES_SINE],
        data_.cz.formant_phase);
    held_sample_ = MulScale8(result, ~phase_msb);
  }
  
  // ------- FM ----------------------------------------------------------------
  static void UpdateFm() {
    uint16_t multiplier = ResourcesManager::Lookup<uint16_t, uint8_t>(
        lut_res_fm_frequency_ratios, data_.fm.modulator_phase_increment);
    data_.fm.modulator_phase_increment = (
        static_cast<int32_t>(phase_increment_) * multiplier) >> 8;
    parameter_ <<= 1;
  }
  static void RenderFm() {
    phase_ += phase_increment_;
    data_.fm.modulator_phase += data_.fm.modulator_phase_increment;
    uint8_t modulator = ReadSample(waveform_table[WAV_RES_SINE],
                                   data_.fm.modulator_phase);
    uint16_t modulation = modulator * parameter_;
    held_sample_ = InterpolateSample(waveform_table[WAV_RES_SINE],
        phase_ + modulation);
  }
  
  // ------- 8-bit land --------------------------------------------------------
  static void Render8BitLand() {
    phase_ += phase_increment_;
    uint8_t x = parameter_;
    held_sample_ = (((phase_ >> 8) ^ (x << 1)) & (~x)) + (x >> 1);
  }
  
  // ------- Vowel ------------------------------------------------------------
  //
  // The algorithm used here is a reimplementation of the synthesis algorithm
  // used in Cantarino, the Arduino speech synthesizer, by Peter Knight.
  // http://code.google.com/p/tinkerit/wiki/Cantarino
  //
  static void UpdateVowel() {
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
  static void RenderVowel() {
    HALF_SAMPLE_RATE;
    
    int8_t result = 0;
    for (uint8_t i = 0; i < 3; ++i) {
      data_.vw.formant_phase[i] += data_.vw.formant_increment[i];
      result += ResourcesManager::Lookup<uint8_t, uint8_t>(
          i == 2 ? waveform_table[WAV_RES_FORMANT_SQUARE] :
                   waveform_table[WAV_RES_FORMANT_SINE],
          ((data_.vw.formant_phase[i] >> 8) & 0xf0) |
            data_.vw.formant_amplitude[i]);
    }
    result = SignedMulScale8(result, ~(phase_ >> 8));

    phase_ += phase_increment_;
    int16_t phase_noise = int8_t(Random::state_msb()) *
        int8_t(data_.vw.noise_modulation);
    if ((phase_ + phase_noise) < phase_increment_) {
      data_.vw.formant_phase[0] = 0;
      data_.vw.formant_phase[1] = 0;
      data_.vw.formant_phase[2] = 0;
    }
    held_sample_ = SignedClip8(4 * result) + 128;
  }
  
  // ------- Dirty PWM (kills kittens) -----------------------------------------
  static void RenderDirtyPwm() {
    phase_ += phase_increment_;
    held_sample_ = (phase_ >> 8) < 127 + parameter_ ? 0 : 255;
  }
  
  // ------- Low-passed, then high-passed white noise --------------------------
  static void RenderFilteredNoise() {
    uint8_t innovation = Random::GetByte();
    // This trick is used to avoid having a DC component (no innovation) when
    // the parameter is set to its minimal or maximal value.
    uint8_t offset = parameter_ == 127 ? 0 : 2;
    data_.no.lp_noise_sample = Mix(
        data_.no.lp_noise_sample,
        innovation,
        offset + (parameter_ << 2));
    if (parameter_ >= 64) {
      held_sample_ = innovation - data_.no.lp_noise_sample;
    } else {
      held_sample_ = data_.no.lp_noise_sample;
    }
  }
  
  DISALLOW_COPY_AND_ASSIGN(Oscillator);
};

#define Osc Oscillator<id, mode>

template<int id, OscillatorMode mode>
uint16_t Oscillator<id, mode>::phase_increment_;
template<int id, OscillatorMode mode>
uint16_t Oscillator<id, mode>::phase_increment_2_;

template<int id, OscillatorMode mode> uint16_t Oscillator<id, mode>::phase_;
template<int id, OscillatorMode mode> uint8_t Oscillator<id, mode>::shape_;
template<int id, OscillatorMode mode>
uint8_t Oscillator<id, mode>::shape_corrected_;
template<int id, OscillatorMode mode> uint8_t Oscillator<id, mode>::parameter_;
template<int id, OscillatorMode mode> uint8_t Oscillator<id, mode>::note_;
template<int id, OscillatorMode mode> uint8_t Oscillator<id, mode>::sweeping_;

template<int id, OscillatorMode mode>
uint8_t Oscillator<id, mode>::held_sample_;

template<int id, OscillatorMode mode>
OscillatorData Oscillator<id, mode>::data_;

template<int id, OscillatorMode mode> AlgorithmFn Oscillator<id, mode>::fn_;
template<int id, OscillatorMode mode>
AlgorithmFn Oscillator<id, mode>::fn_table_[] = {
  { NULL, &Osc::RenderSilence },
  { &Osc::UpdatePulseSquare, &Osc::RenderPulseSquare },
  { &Osc::UpdateSimpleWavetable, &Osc::RenderSimpleWavetable },
  { &Osc::UpdatePulseSquare, &Osc::RenderPulseSquare },
  { &Osc::UpdateSimpleWavetable, &Osc::RenderSimpleWavetable },
  { &Osc::UpdateCz, &Osc::RenderCz },
  { &Osc::UpdateFm, &Osc::RenderFm },
  { NULL, &Osc::Render8BitLand },
  { NULL, &Osc::RenderDirtyPwm },
  { NULL, &Osc::RenderFilteredNoise },
  { &Osc::UpdateVowel, &Osc::RenderVowel },
  { &Osc::UpdateWavetable64, &Osc::RenderWavetable64 },
  { &Osc::RenderSimpleWavetable, &Osc::RenderSimpleWavetable },
};

}  // namespace hardware_shruthi

#endif  // HARDWARE_SHRUTHI_OSCILLATOR_H_
