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

#define SubClip16(a, b) asm( \
    "sub %A0, %A1"    "\n\t" \
    "sbc %B0, %B1"    "\n\t" \
    "brvc .+4"        "\n\t" \
    "ldi %A0, 1"      "\n\t" \
    "ldi %B0, 128"    "\n\t" \
    : "+a" (a) \
    : "a" (b))

#define AddClip16(a, b) asm( \
    "add %A0, %A1"    "\n\t" \
    "adc %B0, %B1"    "\n\t" \
    "brvc .+4"        "\n\t" \
    "ldi %A0, 255"    "\n\t" \
    "ldi %B0, 127"    "\n\t" \
    : "+a" (a) \
    : "a" (b))

#define Clip12(a) if (a > 2047) a = 2047; if (a < -2047) a = -2047; 

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

enum FxProgram {
  FX_DISTORTION,
  FX_CRUSH,
  FX_COMB_POSITIVE,
  FX_COMB_NEGATIVE,
  FX_RINGMOD,
  FX_DELAY,
  FX_DELAY_FB,
  FX_DELAY_DUB,
  FX_CRUSH_DELAY_FB,
  FX_CRUSH_DELAY_DUB,
  FX_DELAY_16,
  FX_DELAY_12,
  FX_DELAY_8,
  FX_DELAY_3_16,
  FX_LOOPER,
  FX_PITCH_SHIFTER,
};

/* <static> */
uint8_t FxEngine::cv_[CV_LAST];
uint8_t FxEngine::cv_ptr_;
uint8_t FxEngine::cv_history_[CV_LAST * 16];
uint16_t FxEngine::cv_sum_[CV_LAST];
uint8_t FxEngine::filter_mode_;
uint8_t FxEngine::fx_program_;
FxState FxEngine::fx_state_;

int16_t FxEngine::samples_[kAudioBlockSize];
int16_t FxEngine::pole_[2];
RenderFn FxEngine::render_fn_[16] = {
  &FxEngine::RenderDistortion,
  &FxEngine::RenderCrush,
  &FxEngine::RenderComb,
  &FxEngine::RenderComb,
  &FxEngine::RenderRingMod,
  &FxEngine::RenderDelay,
  &FxEngine::RenderDelay,
  &FxEngine::RenderDelay,
  &FxEngine::RenderCrushDelay,
  &FxEngine::RenderCrushDelay,
  &FxEngine::RenderDelay,
  &FxEngine::RenderDelay,
  &FxEngine::RenderDelay,
  &FxEngine::RenderDelay,
  &FxEngine::RenderLooper,
  &FxEngine::RenderPitchShifter,
};
/* </static> */

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
  pole_[0] = 0;
  pole_[1] = 0;
  cv_ptr_ = 0;
  memset(&cv_sum_, 0, sizeof(cv_sum_));
  memset(&cv_history_, 0, sizeof(cv_history_));
  memset(&fx_state_, 0, sizeof(fx_state_));
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
  uint8_t input_gain = 16;
  
  uint16_t vcf_ota_gain = ResourcesManager<>::Lookup<int16_t, uint8_t>(
      lut_res_vcf_ota_gain, cutoff);
  uint8_t max_resonance = 255 - (vcf_ota_gain >> 8);
  if (resonance > max_resonance) {
    resonance = max_resonance;
  }
  if (resonance > 128) {
    input_gain = 16 - MulScale8(resonance, 12);
  }
  
  if (filter_mode_ & 1) {
    // VCA > FX > Filter
    for (uint8_t i = 0; i < kAudioBlockSize; ++i) {
      uint8_t sample_8bits = input_buffer.ImmediateRead();
      int16_t sample = SignedUnsignedMul(sample_8bits + 128, 16);
      samples_[i] = SignedUnsignedMul168Scale8(sample, vca);
    }
    render_fn_[fx_program_]();
    // Filter the samples through the digital filter.
    for (uint8_t i = 0; i < kAudioBlockSize; ++i) {
      int16_t input;
      int16_t output;
    
      int16_t feedback = pole_[0];
      SubClip16(feedback, pole_[1]);
      feedback = SignedUnsignedMul168Scale8(feedback, resonance);
      feedback += feedback;
    
      input = samples_[i];
      SubClip16(input, pole_[0]);
      AddClip16(input, feedback);
      output = SignedUnsignedMul16Scale16(input, vcf_ota_gain);
      AddClip16(pole_[0], output);
    
      input = pole_[0];
      SubClip16(input, pole_[1]);
      output = SignedUnsignedMul16Scale16(input, vcf_ota_gain);
      AddClip16(pole_[1], output);
    
      output = pole_[1];
      Clip12(output);
      output_buffer.Overwrite(output + 2048);
    }
  } else {
    // Filter > VCA > FX
    if (filter_mode_ != 4) {
      for (uint8_t i = 0; i < kAudioBlockSize; ++i) {
        int16_t input;
        int16_t output;
    
        int16_t feedback = pole_[0];
        SubClip16(feedback, pole_[1]);
        feedback = SignedUnsignedMul168Scale8(feedback, resonance);
        feedback += feedback;
    
        uint8_t sample_8bits = input_buffer.ImmediateRead();
        input = SignedUnsignedMul(sample_8bits + 128, 16);
        SubClip16(input, pole_[0]);
        AddClip16(input, feedback);
        output = SignedUnsignedMul16Scale16(input, vcf_ota_gain);
        AddClip16(pole_[0], output);
    
        input = pole_[0];
        SubClip16(input, pole_[1]);
        output = SignedUnsignedMul16Scale16(input, vcf_ota_gain);
        AddClip16(pole_[1], output);
    
        output = pole_[1];
        Clip12(output);
        samples_[i] = SignedUnsignedMul168Scale8(output, vca);
      }
    } else {
      for (uint8_t i = 0; i < kAudioBlockSize; ++i) {
        uint8_t sample_8bits = input_buffer.ImmediateRead();
        int16_t sample = SignedUnsignedMul(sample_8bits + 128, 16);
        samples_[i] = SignedUnsignedMul168Scale8(sample, vca);
      }
    }
    render_fn_[fx_program_]();
    for (uint8_t i = 0; i < kAudioBlockSize; ++i) {
      output_buffer.Overwrite(samples_[i] + 2048);
    }
  }
}

/* static */
void FxEngine::RenderDistortion() {
  uint8_t fold_wet = filtered_cv(CV_1);
  uint8_t fold_dry = ~fold_wet;
  uint8_t fuzz_wet = filtered_cv(CV_2);
  uint8_t fuzz_dry = ~fuzz_wet;
  for (uint8_t i = 0; i < kAudioBlockSize; ++i) {
    int16_t fold = ResourcesManager<>::Lookup<uint16_t, uint16_t>(
        lut_res_fold, samples_[i] + 2048) - 2048;
    int16_t folded = SignedUnsignedMul168Scale8(samples_[i], fold_dry);
    folded += SignedUnsignedMul168Scale8(fold, fold_wet);
    int16_t fuzz = ResourcesManager<>::Lookup<uint16_t, uint16_t>(
        lut_res_distortion, folded + 2048) - 2048;
    samples_[i] = SignedUnsignedMul168Scale8(folded, fuzz_dry);
    samples_[i] += SignedUnsignedMul168Scale8(fuzz, fuzz_wet);
  }
}

/* static */
void FxEngine::RenderCrush() {
  uint8_t decimate = (filtered_cv(CV_1) >> 2) + 1;
  uint8_t num_bits = 12 - (ShiftRight4(filtered_cv(CV_2)) >> 1);
  int16_t mask = -2048;
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
  int8_t* end = &fx_state_.delay_line[1024];
  
  for (uint8_t i = 0; i < kAudioBlockSize; ++i) {
    // Feedback signal to delay line.
    int16_t fb = (samples_[i] >> 4);
    if (fx_program_ == FX_COMB_POSITIVE) {
      fb += SignedUnsignedMulScale8(*read_ptr, feedback);
    } else {
      fb -= SignedUnsignedMulScale8(*read_ptr, feedback);
    }
    *write_ptr = SignedClip8(fb);
    // Read delayed signal and mix with original.
    int16_t out = SignedUnsignedMul(*read_ptr, 16);
    out += samples_[i];
    Clip12(out);
    samples_[i] = out;
    ++read_ptr;
    ++write_ptr;
    if (read_ptr >= end) {
      read_ptr -= 1024;
    }
    if (write_ptr >= end) {
      write_ptr -= 1024;
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
    int8_t sample_8bits = samples_[i] >> 4;
    int8_t sine = 128 + \
        InterpolateSample(waveform_res_sine, fx_state_.ringmod_phase);
    int16_t ringmod = SignedSignedMul168Scale8(samples_[i], sine);
    samples_[i] = SignedUnsignedMul168Scale8(samples_[i], dry);
    samples_[i] += SignedUnsignedMul168Scale8(ringmod, wet);
  }
}

/* static */
void FxEngine::RenderDelay() {
  uint8_t delay = 0;
  uint8_t feedback = 0;
  uint8_t amount = 0;
  if (fx_program_ >= FX_DELAY && fx_program_ <= FX_DELAY_DUB) {
    delay = filtered_cv(CV_1);
    if (fx_program_ == FX_DELAY_FB) {
      feedback = 85;
    } else if (fx_program_ == FX_DELAY_DUB) {
      feedback = 224;
    }
    amount = filtered_cv(CV_2);
  }
  uint8_t decimate = ResourcesManager<>::Lookup<uint16_t, uint8_t>(
      lut_res_delay_decimation, delay);
  uint8_t filter_gain = ResourcesManager<>::Lookup<uint16_t, uint8_t>(
      lut_res_delay_filter_gain, delay);
  uint16_t delay_duration = ResourcesManager<>::Lookup<uint16_t, uint8_t>(
      lut_res_delay_line_size, delay); 
  
  int8_t* end = &fx_state_.delay_line[delay_line_size];
  int8_t* write_ptr = &fx_state_.delay_line[fx_state_.delay_ptr];
  int8_t* read_ptr = &fx_state_.delay_line[
      (fx_state_.delay_ptr - delay_duration + delay_line_size)];
  while (read_ptr >= end) {
    read_ptr -= delay_line_size;  // Cheap modulo.
  }
  for (uint8_t i = 0; i < kAudioBlockSize; ++i) {
    if (fx_state_.delay_sample_counter >= decimate) {
      fx_state_.delay_sample_counter = 0;
      // Read the delayed sample and write back to the delay line.
      int16_t fb = fx_state_.delay_input_sample;
      fb += SignedUnsignedMulScale8(*read_ptr, feedback);
      *write_ptr = SignedClip8(fb);
      fx_state_.delay_delayed_sample = SignedUnsignedMul(*read_ptr, 16);
      ++read_ptr;
      ++write_ptr;
      if (read_ptr >= end) {
        read_ptr -= delay_line_size;
      }
      if (write_ptr >= end) {
        write_ptr -= delay_line_size;
      }
      ++fx_state_.delay_ptr;
    }
    // Low-pass filter the input sample.
    int16_t x = samples_[i] >> 4;
    SubClip16(x, fx_state_.delay_input_sample);
    fx_state_.delay_input_sample += SignedUnsignedMul168Scale8(x, filter_gain);
    
    // Low-pass filter the output sample.
    x = fx_state_.delay_delayed_sample;
    SubClip16(x, fx_state_.delay_output_sample);
    fx_state_.delay_output_sample += SignedUnsignedMul168Scale8(x, filter_gain);
    
    ++fx_state_.delay_sample_counter;
    int16_t out = samples_[i];
    out += SignedUnsignedMul168Scale8(fx_state_.delay_output_sample, amount);
    Clip12(out);
    samples_[i] = out;
  }
  while (fx_state_.delay_ptr > delay_line_size) {
    fx_state_.delay_ptr -= delay_line_size;
  }
}

/* static */
void FxEngine::RenderCrushDelay() {
  uint8_t delay = 0;
  uint8_t feedback = 0;
  uint8_t amount = 0;
  delay = filtered_cv(CV_1);
  if (fx_program_ == FX_CRUSH_DELAY_FB) {
    feedback = 85;
  } else if (fx_program_ == FX_CRUSH_DELAY_DUB) {
    feedback = 224;
  }
  amount = filtered_cv(CV_2);

  uint8_t decimate = ResourcesManager<>::Lookup<uint16_t, uint8_t>(
      lut_res_delay_decimation, delay);
  uint16_t delay_duration = ResourcesManager<>::Lookup<uint16_t, uint8_t>(
      lut_res_delay_line_size, delay); 
  
  int8_t* end = &fx_state_.delay_line[delay_line_size];
  int8_t* write_ptr = &fx_state_.delay_line[fx_state_.delay_ptr];
  int8_t* read_ptr = &fx_state_.delay_line[
      (fx_state_.delay_ptr - delay_duration + delay_line_size)];
  while (read_ptr >= end) {
    read_ptr -= delay_line_size;  // Cheap modulo.
  }
  for (uint8_t i = 0; i < kAudioBlockSize; ++i) {
    if (fx_state_.delay_sample_counter >= decimate) {
      fx_state_.delay_sample_counter = 0;
      // Read the delayed sample and write back to the delay line.
      int16_t fb = samples_[i] >> 4;
      fb += SignedUnsignedMulScale8(*read_ptr, feedback);
      *write_ptr = SignedClip8(fb);
      fx_state_.delay_delayed_sample = SignedUnsignedMul(*read_ptr, 16);
      ++read_ptr;
      ++write_ptr;
      if (read_ptr >= end) {
        read_ptr -= delay_line_size;
      }
      if (write_ptr >= end) {
        write_ptr -= delay_line_size;
      }
      ++fx_state_.delay_ptr;
    }
    ++fx_state_.delay_sample_counter;
    int16_t out = samples_[i];
    out += SignedUnsignedMul168Scale8(fx_state_.delay_delayed_sample, amount);
    Clip12(out);
    samples_[i] = out;
  }
  while (fx_state_.delay_ptr > delay_line_size) {
    fx_state_.delay_ptr -= delay_line_size;
  }
}

/* static */
void FxEngine::RenderLooper() {
  uint8_t trigger = filtered_cv(CV_2);
  if (trigger < 128) {
    LooperRecord();
  } else {
    LooperReplay();
  }
}

/* static */
void FxEngine::LooperRecord() {
  fx_state_.loop_pitch_ref = filtered_cv(CV_1);
  uint8_t decimate = ResourcesManager<>::Lookup<uint16_t, uint8_t>(
      lut_res_delay_decimation, fx_state_.loop_pitch_ref);
  uint16_t loop_duration = ResourcesManager<>::Lookup<uint16_t, uint8_t>(
      lut_res_delay_line_size, fx_state_.loop_pitch_ref);
  uint8_t filter_gain = ResourcesManager<>::Lookup<uint16_t, uint8_t>(
      lut_res_delay_filter_gain, fx_state_.loop_pitch_ref);
  
  int8_t* end = &fx_state_.delay_line[1024];
  int8_t* write_ptr = &fx_state_.delay_line[fx_state_.loop_ptr];
  
  
  for (uint8_t i = 0; i < kAudioBlockSize; ++i) {
    if (fx_state_.delay_sample_counter >= decimate) {
      fx_state_.delay_sample_counter = 0;
      uint8_t s = SignedClip8(fx_state_.delay_input_sample) + 128;
      *write_ptr++ = s;
      if (write_ptr >= end) {
        *end = s;
        write_ptr -= 1024;
      }
      ++fx_state_.loop_ptr;
    }
    // Low-pass filter the input sample.
    int16_t x = samples_[i] >> 4;
    SubClip16(x, fx_state_.delay_input_sample);
    fx_state_.delay_input_sample += SignedUnsignedMul168Scale8(x, filter_gain);
    ++fx_state_.delay_sample_counter;
  }
  fx_state_.loop_ptr &= 1023;
  fx_state_.loop_start = (fx_state_.loop_ptr + 1024 - loop_duration) & 1023;
  fx_state_.loop_phase.integral = 0;
  fx_state_.loop_phase.fractional = 0;
  fx_state_.loop_duration = loop_duration;
}

/* static */
void FxEngine::LooperReplay() {
  uint8_t pitch_shift = 128 + \
      -(filtered_cv(CV_1) >> 1) + (fx_state_.loop_pitch_ref >> 1);
  
  uint16_t phase_increment = ResourcesManager<>::Lookup<uint16_t, uint8_t>(
        lut_res_pitch_ratio, pitch_shift);
  
  uint16_t phase_scaling = ResourcesManager<>::Lookup<uint16_t, uint8_t>(
        lut_res_delay_phase_scaling, fx_state_.loop_pitch_ref);
  
  // If we record a long loop, we need to divide the phase increment by
  // the sample reduction factor.
  if (phase_scaling != 0) {
    phase_increment = SignedUnsignedMul16Scale16(
        phase_increment,
        phase_scaling);
  }
  if (phase_increment == 0) {
    phase_increment = 1;
  }
  
  fx_state_.loop_phase_increment.integral = phase_increment >> 8;
  fx_state_.loop_phase_increment.fractional = phase_increment & 0xff;
  for (uint8_t i = 0; i < kAudioBlockSize; ++i) {
    uint16_t read_ptr = fx_state_.loop_start + fx_state_.loop_phase.integral;
    read_ptr &= 1023;
    uint8_t x = fx_state_.delay_line[read_ptr];
    uint8_t y = fx_state_.delay_line[read_ptr + 1];
    samples_[i] = (Mix16(x, y, fx_state_.loop_phase.fractional) >> 4) - 2048;
    fx_state_.loop_phase = \
        Add24(fx_state_.loop_phase, fx_state_.loop_phase_increment);
    while (fx_state_.loop_phase.integral >= fx_state_.loop_duration) {
      fx_state_.loop_phase.integral -= fx_state_.loop_duration;
    }
  }
}

/* static */
void FxEngine::RenderPitchShifter() {
}


}  // namespace dsp
