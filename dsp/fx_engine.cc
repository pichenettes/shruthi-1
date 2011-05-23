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

#include "avrlib/gpio.h"
#include "avrlib/op.h"
#include "avrlib/resources_manager.h"

#include "dsp/buffers.h"
#include "dsp/resources.h"

namespace dsp {

using namespace avrlib;

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
uint8_t FxEngine::tempo_;
FxState FxEngine::fx_state_;

int16_t FxEngine::samples_[kAudioBlockSize];
int16_t FxEngine::pole_[3];
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

/* static */
void FxEngine::Init() {
  filter_mode_ = 0;
  fx_program_ = 1;
  pole_[0] = 0;
  pole_[1] = 0;
  pole_[2] = 0;
  cv_ptr_ = 0;
  memset(&cv_sum_, 0, sizeof(cv_sum_));
  memset(&cv_history_, 0, sizeof(cv_history_));
  memset(&fx_state_, 0, sizeof(fx_state_));
}

/* static */
void FxEngine::SmoothCv() {
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
}

/* static */
void FxEngine::RenderDcf() {
  uint8_t cutoff = cv(CV_CUTOFF);
  
  // If you look at the lut_res_integrator_gain table, you'll see that for
  // cutoff > 240, the integrator gain is such that the filter doesn't affect
  // the signal in LP mode. This means that in HP mode, the signal will be 
  // silenced, and we don't want this, so we cap the cutoff to 240 in HP mode.
  if ((filter_mode_ & 1) && cutoff > 240) {
    cutoff = 240;
  }
  
  uint8_t resonance = ResourcesManager<>::Lookup<int16_t, uint8_t>(
      waveform_res_resonance_response, filtered_cv(CV_RESONANCE));
  uint8_t dcf_gain = 255 - U8U8MulShift8(resonance, 208);
  uint16_t integrator_gain = ResourcesManager<>::Lookup<int16_t, uint8_t>(
      lut_res_integrator_gain, cutoff);
  uint8_t resonance_compensation = 96 - U8U8MulShift8(integrator_gain >> 8, 96);
  if (resonance > resonance_compensation) {
    resonance -= resonance_compensation;
  } else {
    resonance = 0;
  }
  for (uint8_t i = 0; i < kAudioBlockSize; ++i) {
    int16_t feedback = S16U8MulShift8(
        pole_[0] - pole_[1], resonance) << 2;
  
    int16_t in = samples_[i];
    pole_[0] += S16U16MulShift16(
        in - pole_[0] + feedback, integrator_gain);
    pole_[1] += S16U16MulShift16(
        pole_[0] - pole_[1], integrator_gain);
    pole_[2] += S16U16MulShift16(
        pole_[1] - pole_[2], integrator_gain);
    
    // What analogue taught me: you only need to do clipping on the first pole.
    if (pole_[0] > 8191) {
      pole_[0] = 8191;
    }
    if (pole_[0] < -8191) {
      pole_[0] = -8191;
    }
  
    int16_t out = pole_[2];
    if (filter_mode_ & 1) {
      out = in - out;
    }
    out = S16U8MulShift8(out, dcf_gain);
    samples_[i] = Clip(out, -2047, 2047);
  }
}

/* static */
void FxEngine::RenderDca() {
  uint8_t dca_gain = filtered_cv(CV_VCA);
  for (uint8_t i = 0; i < kAudioBlockSize; ++i) {
    samples_[i] = S16U8MulShift8(samples_[i], dca_gain);
  }
}

/* static */
void FxEngine::ProcessBlock() {
  SmoothCv();
  for (uint8_t i = 0; i < kAudioBlockSize; ++i) {
    samples_[i] = S8U8Mul(input_buffer.ImmediateRead() + 128, 16);
  }
  if (filter_mode_ >= 2) {
    RenderDca();
    render_fn_[fx_program_]();
    if (filter_mode_ != 4) {
      RenderDcf();
    }
  } else {
    RenderDcf();
    RenderDca();
    render_fn_[fx_program_]();
  }
  for (uint8_t i = 0; i < kAudioBlockSize; ++i) {
    output_buffer.Overwrite(samples_[i] + 2048);
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
    int16_t folded = S16U8MulShift8(samples_[i], fold_dry);
    folded += S16U8MulShift8(fold, fold_wet);
    int16_t fuzz = ResourcesManager<>::Lookup<uint16_t, uint16_t>(
        lut_res_distortion, folded + 2048) - 2048;
    samples_[i] = S16U8MulShift8(folded, fuzz_dry);
    samples_[i] += S16U8MulShift8(fuzz, fuzz_wet);
  }
}

/* static */
void FxEngine::RenderCrush() {
  uint8_t decimate = (filtered_cv(CV_1) >> 3) + 1;
  uint8_t num_bits = 12 - U8U8MulShift8(filtered_cv(CV_2), 12);
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
      fb += S8U8MulShift8(*read_ptr, feedback);
    } else {
      fb -= S8U8MulShift8(*read_ptr, feedback);
    }
    *write_ptr = S16ClipS8(fb);
    // Read delayed signal and mix with original.
    int16_t out = S8U8Mul(*read_ptr, 16);
    out += samples_[i];
    samples_[i] = Clip(out, -2047, 2047);
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
  uint16_t phase_increment = ResourcesManager<>::Lookup<int16_t, uint8_t>(
      lut_res_phase_increment, filtered_cv(CV_1));
  uint8_t wet = filtered_cv(CV_2);
  uint8_t dry = ~wet;
  
  for (uint8_t i = 0; i < kAudioBlockSize; ++i) {
    fx_state_.ringmod_phase += phase_increment;
    int8_t sample_8bits = samples_[i] >> 4;
    int8_t sine = 128 + \
        InterpolateSample(waveform_res_sine, fx_state_.ringmod_phase);
    int16_t ringmod = S16S8MulShift8(samples_[i], sine);
    samples_[i] = S16U8MulShift8(samples_[i], dry);
    samples_[i] += S16U8MulShift8(ringmod, wet);
  }
}

/* static */
void FxEngine::RenderDelay() {
  uint8_t feedback = 0;
  uint8_t amount = filtered_cv(CV_2);
  uint8_t decimate;
  uint8_t filter_gain;
  uint16_t delay_duration;
  if (fx_program_ >= FX_DELAY && fx_program_ <= FX_DELAY_DUB) {
    uint8_t delay = filtered_cv(CV_1);
    if (fx_program_ == FX_DELAY_FB) {
      feedback = 85;
    } else if (fx_program_ == FX_DELAY_DUB) {
      feedback = 224;
    }
    decimate = ResourcesManager<>::Lookup<uint16_t, uint8_t>(
        lut_res_delay_decimation, delay);
    filter_gain = ResourcesManager<>::Lookup<uint16_t, uint8_t>(
        lut_res_delay_filter_gain, delay);
    delay_duration = ResourcesManager<>::Lookup<uint16_t, uint8_t>(
        lut_res_delay_duration, delay); 
    
  } else {
    uint16_t tempo = tempo_;
    if (tempo > 240) {
      tempo = 240;
    }
    if (tempo < 40) {
      tempo = 40;
    }
    if (fx_program_ == FX_DELAY_16) {
      tempo = U8U8Mul(tempo, 3);
    } else if (fx_program_ == FX_DELAY_12) {
      tempo = U8U8Mul(tempo, 9) >> 2;
    } else if (fx_program_ == FX_DELAY_8) {
      tempo = U8U8Mul(tempo, 3) >> 1;
    }
    tempo -= 40;
    decimate = ResourcesManager<>::Lookup<uint16_t, uint16_t>(
        lut_res_tap_delay_decimation, tempo);
    filter_gain = ResourcesManager<>::Lookup<uint16_t, uint16_t>(
        lut_res_tap_delay_filter_gain, tempo);
    delay_duration = ResourcesManager<>::Lookup<uint16_t, uint16_t>(
        lut_res_tap_delay_duration, tempo);
    feedback = filtered_cv(CV_1);
  }
  
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
      fb += S8U8MulShift8(*read_ptr, feedback);
      *write_ptr = S16ClipS8(fb);
      fx_state_.delay_delayed_sample = S8U8Mul(*read_ptr, 16);
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
    int16_t x = (samples_[i] >> 4) - fx_state_.delay_input_sample;
    fx_state_.delay_input_sample += S16U8MulShift8(x, filter_gain);
    
    // Low-pass filter the output sample.
    x = fx_state_.delay_delayed_sample - fx_state_.delay_output_sample;
    fx_state_.delay_output_sample += S16U8MulShift8(x, filter_gain);
    
    ++fx_state_.delay_sample_counter;
    int16_t out = samples_[i];
    out += S16U8MulShift8(fx_state_.delay_output_sample, amount);
    samples_[i] = Clip(out, -2047, 2047);
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
      lut_res_delay_duration, delay); 
  
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
      fb += S8U8MulShift8(*read_ptr, feedback);
      *write_ptr = S16ClipS8(fb);
      fx_state_.delay_delayed_sample = S8U8Mul(*read_ptr, 16);
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
    out += S16U8MulShift8(fx_state_.delay_delayed_sample, amount);
    samples_[i] = Clip(out, -2047, 2047);
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
      lut_res_delay_duration, fx_state_.loop_pitch_ref);
  uint8_t filter_gain = ResourcesManager<>::Lookup<uint16_t, uint8_t>(
      lut_res_delay_filter_gain, fx_state_.loop_pitch_ref);
  
  int8_t* end = &fx_state_.delay_line[1024];
  int8_t* write_ptr = &fx_state_.delay_line[fx_state_.loop_ptr];
  
  
  for (uint8_t i = 0; i < kAudioBlockSize; ++i) {
    if (fx_state_.delay_sample_counter >= decimate) {
      fx_state_.delay_sample_counter = 0;
      uint8_t s = S16ClipS8(fx_state_.delay_input_sample) + 128;
      *write_ptr++ = s;
      if (write_ptr >= end) {
        *end = s;
        write_ptr -= 1024;
      }
      ++fx_state_.loop_ptr;
    }
    // Low-pass filter the input sample.
    int16_t x = (samples_[i] >> 4) - fx_state_.delay_input_sample;
    fx_state_.delay_input_sample += S16U8MulShift8(x, filter_gain);
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
    phase_increment = S16U16MulShift16(
        phase_increment,
        phase_scaling);
  }
  if (phase_increment == 0) {
    phase_increment = 1;
  }
  
  uint24_t loop_phase_increment;
  loop_phase_increment.integral = phase_increment >> 8;
  loop_phase_increment.fractional = phase_increment & 0xff;
  for (uint8_t i = 0; i < kAudioBlockSize; ++i) {
    uint16_t read_ptr = fx_state_.loop_start + fx_state_.loop_phase.integral;
    read_ptr &= 1023;
    uint8_t x = fx_state_.delay_line[read_ptr];
    uint8_t y = fx_state_.delay_line[read_ptr + 1];
    samples_[i] = (U8MixU16(x, y, fx_state_.loop_phase.fractional) >> 4) - 2048;
    fx_state_.loop_phase = \
        U24Add(fx_state_.loop_phase, loop_phase_increment);
    if (fx_state_.loop_phase.integral >= fx_state_.loop_duration) {
      fx_state_.loop_phase.integral -= fx_state_.loop_duration;
    }
  }
}

/* static */
void FxEngine::RenderPitchShifter() {
  uint16_t phase_increment = ResourcesManager<>::Lookup<uint16_t, uint8_t>(
        lut_res_pitch_ratio, filtered_cv(CV_1));
  
  uint16_t buffer_duration = 1024;
  uint16_t half_buffer_duration = buffer_duration >> 1;
  
  int8_t* write_ptr = &fx_state_.delay_line[fx_state_.ps_write_ptr];
  int8_t* end = &fx_state_.delay_line[buffer_duration];
  
  uint24_t ps_phase_increment;
  ps_phase_increment.integral = phase_increment >> 8;
  ps_phase_increment.fractional = phase_increment & 0xff;
  
  uint8_t wet = filtered_cv(CV_2);
  uint8_t dry = ~wet;
  
  for (uint8_t i = 0; i < kAudioBlockSize; ++i) {
    // Write the sample to the delay line.
    uint8_t s = (samples_[i] >> 4) + 128;
    *write_ptr++ = s;
    if (write_ptr >= end) {
      *end = s;
      write_ptr -= buffer_duration;
    }
    
    // Read samples at two locations: at the read pointer, and at the read
    // pointer shifted by half the buffer duration.
    int8_t* read_ptr = &fx_state_.delay_line[fx_state_.ps_phase.integral];
    uint8_t a = read_ptr[0];
    // Ideally, we should do this:
    // uint8_t a = U8Mix(read_ptr[0], read_ptr[1], fx_state_.ps_phase.fractional);
    
    read_ptr += half_buffer_duration;
    if (read_ptr >= end) {
      read_ptr -= buffer_duration;
    } 
    uint8_t b = read_ptr[0];
    // Ideally, we should do this:
    // uint8_t b = U8Mix(read_ptr[0], read_ptr[1], fx_state_.ps_phase.fractional);

    // Among the two samples, the one who is the farthest apart from the
    // discontinuity created at the write head location should be given a
    // highest weight. The extreme case is when one of the read heads is at
    // the same position at the write head: this read head should be given
    // a null weight.
    //
    //                                       ___
    //                                ___---    ---___
    //                          ___---                ---___
    //   ___             ___---                             ---
    //      ---______---                                  
    //  |---------W----R1-------------------------R2-----------|
    //  W, R1, R2: position of the write, read1 and read2 heads.
    //  Plotted here is the weight of a read head given the position of W.
    //
    uint16_t distance = (read_ptr - write_ptr + buffer_duration);
    if (distance >= buffer_duration) {
      distance -= buffer_duration;
    }
    if (distance >= half_buffer_duration) {
      distance = buffer_duration - distance - 1;
    }
    uint8_t crossfade = distance >> 1;
    int16_t pitch_shift = U8U8Mul(U8Mix(a, b, crossfade), 16) - 2048;
    samples_[i] = S16U8MulShift8(samples_[i], dry);
    samples_[i] += S16U8MulShift8(pitch_shift, wet);
    
    fx_state_.ps_phase = U24Add(fx_state_.ps_phase, ps_phase_increment);
    if (fx_state_.ps_phase.integral >= buffer_duration) {
      fx_state_.ps_phase.integral -= buffer_duration;
    }
  }
  fx_state_.ps_write_ptr = (fx_state_.ps_write_ptr + kAudioBlockSize);
  if (fx_state_.ps_write_ptr >= buffer_duration) {
    fx_state_.ps_write_ptr -= buffer_duration;
  }
}


}  // namespace dsp
