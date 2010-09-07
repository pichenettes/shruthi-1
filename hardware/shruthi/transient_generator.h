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

#ifndef HARDWARE_SHRUTHI_TRANSIENT_GENERATOR_H_
#define HARDWARE_SHRUTHI_TRANSIENT_GENERATOR_H_

#include "hardware/base/base.h"
#include "hardware/shruthi/shruthi.h"

#include "hardware/shruthi/patch.h"
#include "hardware/shruthi/resources.h"
#include "hardware/utils/random.h"
#include "hardware/utils/op.h"

namespace hardware_shruthi {

typedef uint8_t (*RenderFn)(void);

template<int id>
class TransientGenerator {
 public:
  TransientGenerator() { }

  // Called whenever the parameters of the oscillator change. Can be used
  // to pre-compute parameters, set tables, etc.
  static inline void SetupAlgorithm(uint8_t shape) {
    if (shape < WAVEFORM_SUB_OSC_CLICK)  {
      return;  // Not my business... handled by the sub oscillator!
    }
    if (shape > WAVEFORM_SUB_OSC_POP) {
      shape = WAVEFORM_SUB_OSC_POP;
    }
    fn_ = fn_table_[shape - WAVEFORM_SUB_OSC_CLICK];
  }
  
  static inline uint8_t Render() {
    if (counter_ == 0) {
      return 0;
    }
    return (*fn_)();
  }
  
  static inline uint8_t Trigger() {
    counter_ = 255;
  }
  
  static inline uint8_t gain() {
    return gain_;
  }
  
 private:
  static uint8_t RenderClick() {
    gain_ = counter_;
    --counter_;
    return counter_ < 32 ? 255 : 0;
  }
  static uint8_t RenderGlitch() {
    gain_ = counter_;
    --counter_;
    rng_state_ = rng_state_ * 73 + counter_;
    return rng_state_;
  }
  static uint8_t RenderBlow() {
    decimate_ += 2;
    if (decimate_ >= 16) {
      decimate_ -= 17;
      rng_state_ = rng_state_ * 73 + counter_;
      if (decimate_ == 0) {
        --counter_;
        gain_ = (counter_ & 0x80) ? ~counter_ : counter_;
      }
    }
    return rng_state_;
  }
  static uint8_t RenderMetallic() {
    --counter_;
    gain_ = counter_ >= 64 ? 255 : counter_ << 2;
    return counter_ * 57;
  }
  static uint8_t RenderPop() {
    --counter_;
    gain_ = counter_ > 0 ? 255 : 0;
    return 0;
  }
   
  static uint8_t rng_state_;
  static uint8_t decimate_;
  static uint8_t gain_;
  static uint8_t counter_;
  static RenderFn fn_;
  static RenderFn fn_table_[];
  
  DISALLOW_COPY_AND_ASSIGN(TransientGenerator);
};

/* <static> */
template<int id> RenderFn TransientGenerator<id>::fn_table_[] = {
  &TransientGenerator<id>::RenderClick,
  &TransientGenerator<id>::RenderGlitch,
  &TransientGenerator<id>::RenderBlow,
  &TransientGenerator<id>::RenderMetallic,
  &TransientGenerator<id>::RenderPop,
};

template<int id> uint8_t TransientGenerator<id>::counter_;
template<int id> uint8_t TransientGenerator<id>::rng_state_;
template<int id> uint8_t TransientGenerator<id>::decimate_;
template<int id> uint8_t TransientGenerator<id>::gain_;
template<int id> RenderFn TransientGenerator<id>::fn_;
/* </static> */

}  // namespace hardware_shruthi

#endif  // HARDWARE_SHRUTHI_OSCILLATOR_H_
