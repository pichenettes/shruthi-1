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

#ifndef SHRUTHI_SUB_OSCILLATOR_H_
#define SHRUTHI_SUB_OSCILLATOR_H_

#include "avrlib/base.h"
#include "shruthi/shruthi.h"

#include "shruthi/patch.h"
#include "shruthi/resources.h"
#include "shruthi/synthesis_engine.h"
#include "avrlib/op.h"

using namespace avrlib;

namespace shruthi {

class SubOscillator {
 public:
  SubOscillator() { }

  static inline void set_increment(uint24_t increment) {
    phase_increment_ = increment;
  }

  static inline void Render(uint8_t shape, uint8_t* buffer, uint8_t amount) {
    uint24_t increment = phase_increment_;
    if (shape >= 3) {
      increment = U24ShiftRight(increment);
      shape -= 3;
    }
    uint8_t size = kAudioBlockSize;
    uint8_t pulse_width = shape == 0 ? 0x80 : 0x40;
    uint8_t sub_gain = amount;
    uint8_t mix_gain = ~sub_gain;
    while (size--) {
      phase_ = U24Add(phase_, increment);
      uint8_t v;
      if (shape != 1) {
        v = static_cast<uint8_t>(phase_.integral >> 8) < pulse_width ? 0 : 255;
      } else {
        uint8_t tri = phase_.integral >> 7;
        v = phase_.integral & 0x8000 ? tri : ~tri;
      }
      *buffer++ = U8Mix(*buffer, v, mix_gain, sub_gain);
    }
  }

 private:
  // Current phase of the oscillator.
  static uint24_t phase_;
  static uint24_t phase_increment_;

  DISALLOW_COPY_AND_ASSIGN(SubOscillator);
};

/* static */
uint24_t SubOscillator::phase_;

/* static */
uint24_t SubOscillator::phase_increment_;

}  // namespace shruthi

#endif // SHRUTHI_SUB_OSCILLATOR_H_
