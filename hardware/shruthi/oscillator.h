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
#include "hardware/utils/random.h"
#include "hardware/utils/op.h"

using namespace hardware_utils_op;
using hardware_utils::Random;

static const uint16_t kWavetableSize = 16 * 257;

namespace hardware_shruthi {

#define WAV_RES_SINE WAV_RES_BANDLIMITED_TRIANGLE_6
#define HALF_SAMPLE_RATE if (engine.oscillator_decimation() & 1) return;

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



static const uint8_t kVowelControlRateDecimation = 4;
static const uint8_t kNumZonesFullSampleRate = 6;
static const uint8_t kNumZonesHalfSampleRate = 5;

struct BandlimitedPwmOscillatorData {
  const prog_uint8_t* wave[2];
  uint8_t balance;
  uint16_t shift;
  uint8_t scale;
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

struct WaveshapperData {
  uint8_t mask;
};

union OscillatorData {
  BandlimitedPwmOscillatorData pw;
  SawTriangleOscillatorData st;
  CzOscillatorData cz;
  FmOscillatorData fm;
  VowelSynthesizerData vw;
  Wavetable64OscillatorData wt;
  FilteredNoiseData no;
  WaveshapperData ws;
};

struct AlgorithmFn {
  void (*update)();
  void (*render)();
};

template<int id>
class Oscillator {
 public:
  Oscillator() { }

  // Called whenever the parameters of the oscillator change. Can be used
  // to pre-compute parameters, set tables, etc.
  static inline void SetupAlgorithm(uint8_t shape) {
    shape_ = shape;
    fn_ = fn_table_[shape];
  }
  
  static inline uint8_t Render() {
    (*fn_.render)();
    return held_sample_;
  }
  
  static inline void Update(
      uint8_t parameter,
      uint8_t note,
      uint16_t increment) {
    note_ = note;
    parameter_ = parameter;
    phase_increment_ = increment;
    // A hack: when pulse width is set to 0, use a simple wavetable.
    if (shape_ == WAVEFORM_SQUARE) {
      fn_ = fn_table_[shape_ + (parameter_ == 0 ? 1 : 0)];
    }
    (*fn_.update)();
  }
  
  static inline void UpdateSecondaryParameter(uint8_t secondary_parameter) {
    data_.fm.modulator_phase_increment = secondary_parameter;
  }
  
  static inline uint16_t phase() { return phase_; }
  static inline void ResetPhase() { phase_ = 0;  }

 private:
  // Current phase of the oscillator.
  static uint16_t phase_;

  // Phase increment (and phase increment x 2, for low-sr oscillators).
  static uint16_t phase_increment_;

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

  // ------- Silence (useful when processing external signals) -----------------
  static void UpdateSilence() {
  }
  
  static void RenderSilence() {
    held_sample_ = 128;
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
      data_.pw.scale = Mix(data_.pw.scale, 128, (note_ - 64) << 2);
      data_.pw.scale = Mix(data_.pw.scale, 128, (note_ - 64) << 2);
    }
  }
  static void RenderBandlimitedPwm() {
    phase_ += phase_increment_;
    HALF_SAMPLE_RATE;
    
    uint8_t a = InterpolateTwoTables(
        data_.pw.wave[0],
        data_.pw.wave[1],
        phase_,
        data_.pw.balance);
    a = MulScale8(a, data_.pw.scale);
    uint8_t b = InterpolateSample(
        data_.pw.wave[0],
        phase_ + data_.pw.shift);
    b = MulScale8(b, data_.pw.scale);
    held_sample_ = a - b + 128;
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
  
  // ------- Interpolation between two waveforms from two wavetables -----------
  // The position is freely determined by the parameter
  static void UpdateSweepingWavetable() {
    uint8_t balance_index = Swap4(parameter_ << 1);
    data_.st.balance = balance_index & 0xf0;
    uint8_t wave_index = balance_index & 0xf;
    
    uint16_t offset = wave_index << 8;
    offset += wave_index;
    const prog_uint8_t* base_address = waveform_table[
        WAV_RES_WAVETABLE_1 + shape_ - WAVEFORM_WAVETABLE_1];
    data_.st.wave[0] = base_address + offset;
    if (offset < kWavetableSize - 257) {
      data_.st.wave[1] = base_address + (offset + 257);
    } else {
      data_.st.wave[1] = base_address + offset;
    }
  }
  static void RenderSweepingWavetable() {
    phase_ += phase_increment_;
    uint8_t sample = InterpolateTwoTables(
        data_.st.wave[0], data_.st.wave[1],
        phase_, data_.st.balance);
    held_sample_ = sample;
  }

  // ------- Casio CZ-like synthesis -------------------------------------------
  static void UpdateCz() {
    data_.cz.formant_phase_increment = phase_increment_ + (
        (phase_increment_ * uint32_t(parameter_)) >> 3);
  }
  
  static void RenderCzPulseReso() {
    uint8_t old_phase_msb = phase_ >> 8;
    phase_ += phase_increment_;
    uint8_t phase_msb = phase_ >> 8;
    if (phase_msb < old_phase_msb) {
      data_.cz.formant_phase = 0;
    }
    data_.cz.formant_phase += data_.cz.formant_phase_increment;
    uint8_t result = InterpolateSample(
        waveform_table[WAV_RES_SINE],
        data_.cz.formant_phase);
    if (phase_ < 0x4000) {
      held_sample_ = result;
    } else if (phase_ < 0x8000) {
      held_sample_ = MulScale8(result, ~(phase_ - 0x4000) >> 6);
    } else {
      held_sample_ = 0;
    }
  }
  
  // A lot of duplicated code... but this avoids a bunch of cycles
  static void RenderCzSawReso() {
    uint8_t old_phase_msb = phase_ >> 8;
    phase_ += phase_increment_;
    uint8_t phase_msb = phase_ >> 8;
    if (phase_msb < old_phase_msb) {
      data_.cz.formant_phase = 0;
    }
    data_.cz.formant_phase += data_.cz.formant_phase_increment;
    uint8_t result = InterpolateSample(
        waveform_table[WAV_RES_SINE],
        data_.cz.formant_phase);
    held_sample_ = MulScale8(result, ~phase_msb);
  }
  
  // TODO(pichenettes): check those waveforms on a scope, there's some serious
  // mis-synchronisation going on here.
  static void RenderCzTriReso() {
    uint8_t old_phase_msb = phase_ >> 8;
    phase_ += phase_increment_;
    uint8_t phase_msb = phase_ >> 8;
    if (phase_msb < old_phase_msb) {
      data_.cz.formant_phase = 0;
    }
    data_.cz.formant_phase += data_.cz.formant_phase_increment;
    uint8_t result = InterpolateSample(
        waveform_table[WAV_RES_SINE],
        data_.cz.formant_phase);
    uint8_t triangle =  (phase_ & 0x8000) ?
          ~static_cast<uint8_t>(phase_ >> 7) :
          phase_ >> 7;
    held_sample_ = MulScale8(result, triangle);
  }

  static void RenderCzSyncReso() {
    uint8_t old_phase_msb = phase_ >> 8;
    phase_ += phase_increment_;
    uint8_t phase_msb = phase_ >> 8;
    if (phase_msb < old_phase_msb) {
      data_.cz.formant_phase = 0;
    }
    data_.cz.formant_phase += data_.cz.formant_phase_increment;
    uint8_t result = InterpolateSample(
        waveform_table[WAV_RES_SINE],
        data_.cz.formant_phase);
    held_sample_ = phase_ < 0x8000 ? result : 128;
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
  
  // ------- Dirty waveshaper --------------------------------------------------
  static void UpdateShaper() {
  }
  
  static void RenderShaper() {
  }

  // ------- Vowel ------------------------------------------------------------
  //
  // The algorithm used here is a reimplementation of the synthesis algorithm
  // used in Cantarino, the Arduino speech synthesizer, by Peter Knight.
  // http://code.google.com/p/tinkerit/wiki/Cantarino
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

  // ------- Dirty Pwm (kills kittens) -----------------------------------------
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

#define Osc Oscillator<id>

template<int id> uint16_t Oscillator<id>::phase_increment_;

template<int id> uint16_t Oscillator<id>::phase_;
template<int id> uint8_t Oscillator<id>::shape_;
template<int id> uint8_t Oscillator<id>::shape_corrected_;
template<int id> uint8_t Oscillator<id>::parameter_;
template<int id> uint8_t Oscillator<id>::note_;
template<int id> uint8_t Oscillator<id>::sweeping_;

template<int id> uint8_t Oscillator<id>::held_sample_;

template<int id> OscillatorData Oscillator<id>::data_;

template<int id> AlgorithmFn Oscillator<id>::fn_;
template<int id> AlgorithmFn Oscillator<id>::fn_table_[] = {
  { &Osc::UpdateSilence, &Osc::RenderSilence },

  { &Osc::UpdateSimpleWavetable, &Osc::RenderSimpleWavetable },
  { &Osc::UpdateBandlimitedPwm, &Osc::RenderBandlimitedPwm },
  { &Osc::UpdateSimpleWavetable, &Osc::RenderSimpleWavetable },
  
  { &Osc::UpdateCz, &Osc::RenderCzSawReso },
  { &Osc::UpdateCz, &Osc::RenderCzTriReso },
  { &Osc::UpdateCz, &Osc::RenderCzPulseReso },
  { &Osc::UpdateCz, &Osc::RenderCzSyncReso },
  
  { &Osc::UpdateFm, &Osc::RenderFm },
  
  { &Osc::UpdateSweepingWavetable, &Osc::RenderSweepingWavetable },
  { &Osc::UpdateSweepingWavetable, &Osc::RenderSweepingWavetable },
  { &Osc::UpdateSweepingWavetable, &Osc::RenderSweepingWavetable },
  { &Osc::UpdateSweepingWavetable, &Osc::RenderSweepingWavetable },
  { &Osc::UpdateSweepingWavetable, &Osc::RenderSweepingWavetable },
  { &Osc::UpdateSweepingWavetable, &Osc::RenderSweepingWavetable },
  
  { &Osc::UpdateShaper, &Osc::RenderShaper },
  { &Osc::UpdateSilence, &Osc::Render8BitLand },
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
    base_resource_id_ = shape == WAVEFORM_SQUARE ?
        WAV_RES_BANDLIMITED_SQUARE_1 :
        WAV_RES_BANDLIMITED_TRIANGLE_1;
  }
  static inline uint8_t Render() {
    if (!engine.oscillator_decimation()) {
      phase_ += phase_increment_;
      held_sample_ = InterpolateTwoTables(
          data_.st.wave[0], data_.st.wave[1],
          phase_, data_.st.balance);
    }
    return held_sample_;
  }

  static inline void Update(
      uint8_t parameter,
      uint8_t note,
      uint16_t increment) {
    phase_increment_ = increment << 2;
    
    uint8_t balance_index = Swap4(note);
    data_.st.balance = balance_index & 0xf0;

    uint8_t wave_index = balance_index & 0x0f;
    wave_index = AddClip(wave_index, 1, kNumZonesHalfSampleRate);
    data_.st.wave[0] = waveform_table[base_resource_id_ + wave_index];
    wave_index = AddClip(wave_index, 1, kNumZonesHalfSampleRate);
    data_.st.wave[1] = waveform_table[base_resource_id_ + wave_index];
  }

 private:
  // Current phase of the oscillator.
  static uint16_t phase_;
  static uint16_t phase_increment_;

  static uint8_t base_resource_id_;

  // Sample generated in the previous full call.
  static uint8_t held_sample_;

  // Union of state data used by each algorithm.
  static OscillatorData data_;

  DISALLOW_COPY_AND_ASSIGN(SubOscillator);
};

/* <static> */
template<int id> uint16_t SubOscillator<id>::phase_;
template<int id> uint16_t SubOscillator<id>::phase_increment_;
template<int id> uint8_t SubOscillator<id>::base_resource_id_;
template<int id> uint8_t SubOscillator<id>::held_sample_;
template<int id> OscillatorData SubOscillator<id>::data_;

/* </static> */

}  // namespace hardware_shruthi

#endif  // HARDWARE_SHRUTHI_OSCILLATOR_H_
