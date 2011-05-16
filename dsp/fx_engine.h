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
//
// -----------------------------------------------------------------------------
//
// Main definitions.

#ifndef DSP_FX_ENGINE_H_
#define DSP_FX_ENGINE_H_

#include "avrlib/base.h"
#include "dsp/dsp.h"

namespace dsp {

static const uint16_t delay_line_size = 1280;

enum ControlVoltage {
  CV_1,
  CV_2,
  CV_RESONANCE,
  CV_CUTOFF,
  CV_VCA,
  CV_LAST
};

typedef void (*RenderFn)();

struct FxState {
  uint8_t bitcrusher_sample_counter;
  int16_t bitcrusher_held_sample;
  
  int8_t delay_line[delay_line_size + 1];
  uint16_t delay_ptr;
  
  uint16_t ringmod_phase;
  uint8_t delay_sample_counter;
  int16_t delay_delayed_sample;
  int16_t delay_output_sample;
  int16_t delay_input_sample;
  
  uint16_t loop_ptr;
  uint16_t loop_start;
  uint16_t loop_duration;
  uint8_t loop_pitch_ref;
  uint24_t loop_phase;
  
  uint16_t ps_write_ptr;
  uint24_t ps_phase;
};

class FxEngine {
 public:
  FxEngine() { }
  static void Init();
  
  static void set_cv(uint8_t cv_index, uint8_t value) {
    cv_[cv_index] = value;
  }
  
  static uint8_t cv(uint8_t cv_index) {
    return cv_[cv_index];
  }

  static uint8_t filtered_cv(uint8_t cv_index) {
#ifdef USE_ANALOG_CV
    return cv_sum_[cv_index] >> 4;
#else
    return cv_[cv_index];
#endif  // USE_ANALOG_CV
  }
  
  static uint8_t vca() {
    return cv_[CV_VCA];
  }
  
  static void set_tempo(uint8_t tempo) {
    tempo_ = tempo;
  }
  static void set_mode(uint8_t filter_mode) {
    filter_mode_ = filter_mode;
  }
  static void set_fx_program(uint8_t fx_program) {
    fx_program_ = fx_program;
  }
  static void set_mode_byte(uint8_t mode_byte) {
    filter_mode_ = mode_byte >> 4;
    fx_program_ = mode_byte & 0x0f;
  }
  
  static void ProcessBlock();
  
 private:
  static void RenderDca();
  static void RenderDcf();
  static void RenderDistortion();
  static void RenderCrush();
  static void RenderComb();
  static void RenderRingMod();
  static void RenderDelay();
  static void RenderCrushDelay();
  static void RenderLooper();
  static void RenderPitchShifter();
  static void SmoothCv();
  
  static void LooperRecord();
  static void LooperReplay();

  static uint8_t cv_[CV_LAST];
  static uint8_t cv_history_[CV_LAST * 16];
  static uint16_t cv_sum_[CV_LAST];
  static uint8_t cv_ptr_;
  static uint8_t tempo_;
    
  static uint8_t filter_mode_;
  static uint8_t fx_program_;
  static int16_t samples_[kAudioBlockSize];

  // Internal state of the low-pass filter.
  static int16_t pole_[3];
  static RenderFn render_fn_[16];
  
  static FxState fx_state_;
  
  DISALLOW_COPY_AND_ASSIGN(FxEngine);
};

extern FxEngine fx_engine;

}  // namespace dsp

#endif // DSP_FX_ENGINE_H_
