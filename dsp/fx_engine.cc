// Copyright 2011 Olivier Gillet.
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

#include "dsp/fx_engine.h"

#include "avrlib/op.h"
#include "avrlib/resources_manager.h"

#include "dsp/buffers.h"
#include "dsp/resources.h"

namespace dsp {

using namespace avrlib;

/* <static> */
uint8_t FxEngine::cv_[CV_LAST];
uint8_t FxEngine::cv_ptr_;
uint8_t FxEngine::cv_history_[CV_LAST * 16];
uint16_t FxEngine::cv_sum_[CV_LAST];
uint8_t FxEngine::filter_mode_;
uint8_t FxEngine::fx_program_;
FxState FxEngine::fx_state_;

int8_t FxEngine::samples_[kAudioBlockSize];
int16_t FxEngine::state_[3];
RenderFn FxEngine::render_fn_[16] = {
  &FxEngine::RenderNone,
  &FxEngine::RenderDistortion,
  &FxEngine::RenderCrush,
  &FxEngine::RenderComb,
  &FxEngine::RenderComb,
  &FxEngine::RenderRingMod,
  &FxEngine::RenderDelay,
  &FxEngine::RenderDelay,
  &FxEngine::RenderDelay,
  &FxEngine::RenderDelay,
  &FxEngine::RenderDelay,
  &FxEngine::RenderDelay,
  &FxEngine::RenderDelay,
  &FxEngine::RenderFlanger,
  &FxEngine::RenderFlanger
};
/* </static> */


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

/* extern */
FxEngine fx_engine;

enum SvfNodes {
  LP,
  BP,
  HP
};

/* static */
void FxEngine::Init() {
  filter_mode_ = 0;
  fx_program_ = 1;
  state_[LP] = 0;
  state_[BP] = 0;
  state_[HP] = 0;
  cv_ptr_ = 0;
  memset(&cv_sum_, 0, sizeof(cv_sum_));
  memset(&cv_history_, 0, sizeof(cv_history_));
  memset(fx_state_.delay_line, 0, 1024);
}

/* static */
void FxEngine::ProcessBlock() {
  // Smooth CVs.
#ifdef USE_ANALOG_CV
  uint8_t* history = cv_history_ + cv_ptr_;
  for (uint8_t i = 0; i < CV_LAST; ++i) {
    cv_sum_[i] -= *history;
    *history = cv_[i];
    cv_sum_[i] += cv_[i];
    history += 16;
  }
  cv_ptr_ = (cv_ptr_ + 1) & 15;
#endif  // USE_ANALOG_CV
  
  // Compute the filter variables.
  uint8_t cutoff = cv(CV_CUTOFF);
  uint8_t resonance = filtered_cv(CV_RESONANCE);
  uint8_t vca = filtered_cv(CV_VCA);
  
  uint16_t integrator_step = ResourcesManager<>::Lookup<int16_t, uint8_t>(
      lut_res_integrator_step, cutoff);
  uint16_t max_damp_factor = ResourcesManager<>::Lookup<int16_t, uint8_t>(
      lut_res_damp_stability_bound, cutoff);
  uint16_t damp_factor = ResourcesManager<>::Lookup<int16_t, uint8_t>(
      lut_res_damp_factor, resonance);
      
  if (damp_factor > max_damp_factor) {
    damp_factor = max_damp_factor;
  }
  
  // Filter the samples through the SVF.
  for (uint8_t i = 0; i < kAudioBlockSize; ++i) {
    uint8_t sample_8bits = input_buffer.ImmediateRead();
    /*int16_t sample = SignedUnsignedMul(sample_8bits + 128, 64);
    int16_t result = 0;
    int16_t damped;
    state_[LP] += SignedUnsignedMul16Scale15(state_[BP], integrator_step);
    damped = SignedUnsignedMul16Scale15(state_[BP], damp_factor);
    state_[HP] = sample - damped - state_[LP];
    state_[BP] += SignedUnsignedMul16Scale15(state_[HP], integrator_step);
    if (state_[0] > 16383) {
      state_[0] = 16383;
    }
    if (state_[0] < -16383) {
      state_[0] = -16383;
    }
    if (state_[1] > 16383) {
      state_[1] = 16383;
    }
    if (state_[1] < -16383) {
      state_[1] = -16383;
    }
    if (state_[2] > 16383) {
      state_[2] = 16383;
    }
    if (state_[2] < -16383) {
      state_[2] = -16383;
    }
    result = state_[filter_mode_];
    result += result;
    samples_[i] = (result >> 8);*/
    samples_[i] = SignedUnsignedMulScale8(sample_8bits + 128, vca);
  }
  render_fn_[fx_program_]();
  for (uint8_t i = 0; i < kAudioBlockSize; ++i) {
    output_buffer.Overwrite(samples_[i]);
  }
}

/* static */
void FxEngine::RenderDistortion() {
  uint8_t fold_wet = filtered_cv(CV_1);
  uint8_t fold_dry = ~fold_wet;
  uint8_t fuzz_wet = filtered_cv(CV_2);
  uint8_t fuzz_dry = ~fuzz_wet;
  for (uint8_t i = 0; i < kAudioBlockSize; ++i) {
    uint8_t s = samples_[i] + 128;
    uint8_t fold = ResourcesManager<>::Lookup<uint8_t, uint8_t>(
        waveshaper_res_fold, s);
    s = Mix(s, fold, fold_dry, fold_wet);
    uint8_t fuzz = ResourcesManager<>::Lookup<uint8_t, uint8_t>(
        waveshaper_res_distortion, s);
    s = Mix(s, fuzz, fuzz_dry, fuzz_wet);
    samples_[i] = s + 128;
  }
}

/* static */
void FxEngine::RenderCrush() {
  uint8_t decimate = (filtered_cv(CV_1) >> 2) + 1;
  uint8_t num_bits = 8 - (ShiftRight4(filtered_cv(CV_2)) >> 1);
  int8_t mask = -128;
  while (--num_bits) {
    mask >>= 1;
  }
  for (uint8_t i = 0; i < kAudioBlockSize; ++i) {
    if (fx_state_.bitcrusher_sample_counter >= decimate) {
      fx_state_.bitcrusher_sample_counter = 0;
      fx_state_.bitcrusher_held_sample= samples_[i] & mask;
    }
    ++fx_state_.bitcrusher_sample_counter;
    samples_[i] = fx_state_.bitcrusher_held_sample;
  }
}

/* static */
void FxEngine::RenderComb() {
  uint8_t feedback = filtered_cv(CV_2);
  uint16_t delay = ResourcesManager<>::Lookup<int16_t, uint8_t>(
      lut_res_comb_delays, filtered_cv(CV_1));
  int8_t* write_ptr = &fx_state_.delay_line[fx_state_.delay_ptr];
  int8_t* read_ptr = &fx_state_.delay_line[
      (fx_state_.delay_ptr - delay) & 1023];
  int8_t* start = &fx_state_.delay_line[0];
  int8_t* end = &fx_state_.delay_line[1024];
  
  for (uint8_t i = 0; i < kAudioBlockSize; ++i) {
    // Feedback signal to delay line.
    int16_t fb = samples_[i];
    if (fx_program_ == 3) {
      fb += SignedUnsignedMulScale8(*read_ptr, feedback);
    } else {
      fb -= SignedUnsignedMulScale8(*read_ptr, feedback);
    }
    *write_ptr = SignedClip8(fb);
    // Read delayed signal and mix with original.
    int16_t out = *read_ptr;
    out += samples_[i];
    samples_[i] = SignedClip8(out);
    ++read_ptr;
    ++write_ptr;
    if (read_ptr == end) {
      read_ptr = start;
    }
    if (write_ptr == end) {
      write_ptr = start;
    }
  }
  fx_state_.delay_ptr = (fx_state_.delay_ptr + kAudioBlockSize) & 1023;
}

/* static */
void FxEngine::RenderRingMod() {
  // RINGMOD     Freq        Amount
  uint16_t phase_increment = ResourcesManager<>::Lookup<int16_t, uint8_t>(
      lut_res_phase_increment, filtered_cv(CV_1));
  uint8_t wet = filtered_cv(CV_2);
  uint8_t dry = ~wet;
  
  for (uint8_t i = 0; i < kAudioBlockSize; ++i) {
    fx_state_.ringmod_phase += phase_increment;
    int8_t sine = 128 + \
        InterpolateSample(waveshaper_res_sine, fx_state_.ringmod_phase);
    int8_t ringmod = SignedSignedMulScale8(samples_[i], sine);
    samples_[i] = SignedMix(samples_[i], ringmod, dry, wet);
  }
}

/* static */
void FxEngine::RenderDelay() {
  // DELAY       Delay       Amount
  // DELAY0.25   Delay       Amount
  // DELAY0.75   Delay       Amount
  // TAP1/4      Feedback    Amount
  // TAP1/3      Feedback    Amount
  // TAP1/2      Feedback    Amount
  // TAP3/4      Feedback    Amount
  // TAP1/1      Feedback    Amount
  
}

/* static */
void FxEngine::RenderFlanger() {
  // FLANGER1    Speed       Amount
  // FLANGER2    Speed       Amount
  // FLANGER3    Speed       Amount
  
}

}  // namespace dsp
