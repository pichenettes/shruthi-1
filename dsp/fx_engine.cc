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

// FX          CV1         CV2
//
// NONE        None        None
// DISTORTION  Fold        Fuzz
// CRUSH       Decimate    Bitreduce
// COMB        Delay       Feedback
// RINGMOD     Freq        Amount
// DELAY       Delay       Amount
// DELAY0.25   Delay       Amount
// DELAY0.75   Delay       Amount
// TAP1/4      Feedback    Amount
// TAP1/3      Feedback    Amount
// TAP1/2      Feedback    Amount
// TAP3/4      Feedback    Amount
// TAP1/1      Feedback    Amount
// FLANGER1    Amount      Speed
// FLANGER2    Amount      Speed
// FLANGER3    Amount      Speed

/* <static> */
uint8_t FxEngine::cv_[CV_LAST];
uint8_t FxEngine::filter_mode_;
int16_t FxEngine::svf_hp_;
int16_t FxEngine::svf_lp_;
int16_t FxEngine::svf_bp_;
/* </static> */

/* extern */
FxEngine fx_engine;

/* static */
void FxEngine::Init() {
  filter_mode_ = 0;
  svf_lp_ = 0;
  svf_bp_ = 0;
  svf_hp_ = 0;
}

/* static */
void FxEngine::ProcessBlock() {
  // Compute the filter variables.
  uint8_t cutoff = cv(CV_CUTOFF);
  uint8_t resonance = cv(CV_RESONANCE);
  
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
    int16_t sample = SignedUnsignedMul(sample_8bits + 128, 64);
    int16_t result = 0;
    int16_t damped;
    svf_lp_ += SignedUnsignedMul16Scale15(svf_bp_, integrator_step);
    damped = SignedUnsignedMul16Scale15(svf_bp_, damp_factor);
    svf_hp_ = sample - damped - svf_lp_;
    svf_bp_ += SignedUnsignedMul16Scale15(svf_hp_, integrator_step);
    result = (&svf_lp_)[filter_mode_];
    svf_lp_ += SignedUnsignedMul16Scale15(svf_bp_, integrator_step);
    damped = SignedUnsignedMul16Scale15(svf_bp_, damp_factor);
    svf_hp_ = sample - damped - svf_lp_;
    svf_bp_ += SignedUnsignedMul16Scale15(svf_hp_, integrator_step);
    result += (&svf_lp_)[filter_mode_];
    if (result > 16384) {
      result = 16384;
    }
    if (result < -16384) {
      result = -16384;
    }
    result += result;
    output_buffer.Overwrite((result >> 8) + 128);
    asm volatile("nop\n\t"
                 "nop\n\t"
                 "nop\n\t"
                 "nop\n\t"
                 ::);
  }
}

}  // namespace dsp
