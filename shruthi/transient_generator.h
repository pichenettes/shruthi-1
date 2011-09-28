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

#ifndef SHRUTHI_TRANSIENT_GENERATOR_H_
#define SHRUTHI_TRANSIENT_GENERATOR_H_

#include "avrlib/base.h"
#include "shruthi/shruthi.h"

#include "shruthi/patch.h"
#include "shruthi/resources.h"
#include "avrlib/random.h"
#include "avrlib/op.h"

namespace shruthi {

typedef uint8_t (*RenderFn)(void);

class TransientGenerator {
 public:
  TransientGenerator() { }

  static inline void Render(uint8_t shape, uint8_t* buffer, uint8_t amount) {
    if (shape < WAVEFORM_SUB_OSC_CLICK)  {
      return;
    }
    if (shape > WAVEFORM_SUB_OSC_POP) {
      shape = WAVEFORM_SUB_OSC_POP;
    }
    RenderFn fn = fn_table_[shape - WAVEFORM_SUB_OSC_CLICK];
    uint8_t size = kAudioBlockSize;
    while (counter_ && size--) {
      uint8_t value = (*fn)();
      uint8_t amplitude = U8U8MulShift8(gain_, amount);
      *buffer++ = U8Mix(*buffer, value, amplitude);
    }
  }
  
  static inline uint8_t Trigger() {
    counter_ = 255;
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
  static RenderFn fn_table_[];
  
  DISALLOW_COPY_AND_ASSIGN(TransientGenerator);
};

/* <static> */
RenderFn TransientGenerator::fn_table_[] = {
  &TransientGenerator::RenderClick,
  &TransientGenerator::RenderGlitch,
  &TransientGenerator::RenderBlow,
  &TransientGenerator::RenderMetallic,
  &TransientGenerator::RenderPop,
};

uint8_t TransientGenerator::counter_;
uint8_t TransientGenerator::rng_state_;
uint8_t TransientGenerator::decimate_;
uint8_t TransientGenerator::gain_;
/* </static> */

}  // namespace shruthi

#endif // SHRUTHI_OSCILLATOR_H_
