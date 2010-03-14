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
// LFO (cheap oscillator).
//
// Contrary to oscillators which are templatized "static singletons", to
// generate the fastest, most specialized code, LFOs are less
// performance-sensitive and are thus implemented as a traditional class.

#ifndef HARDWARE_SHRUTHI_LFO_H_
#define HARDWARE_SHRUTHI_LFO_H_

#include "hardware/base/base.h"
#include "hardware/shruthi/shruthi.h"

#include "hardware/shruthi/patch.h"
#include "hardware/utils/random.h"

using hardware_utils::Random;

namespace hardware_shruthi {

class Lfo {
 public:
  Lfo() { }
  uint8_t Render() {
    switch (shape_) {
      case LFO_WAVEFORM_S_H:
        if (phase_ < previous_phase_) {
          value_ = Random::GetByte();
        }
        previous_phase_ = phase_;
        return value_;

      case LFO_WAVEFORM_TRIANGLE:
        return (phase_ & 0X8000) ?
            phase_ >> 7 :
            ~static_cast<uint8_t>(phase_ >> 7);

      case LFO_WAVEFORM_SQUARE:
        return (phase_ & 0x8000) ? 255 : 0;

      default:
        return phase_ >> 8;
    }
  }
  void Reset() {
    phase_ = 0;
  }
  void Increment() {
    phase_ += phase_increment_;
  }
  void Update(uint8_t shape, uint16_t increment) {
    shape_ = shape;
    phase_increment_ = increment;
  }

 private:
  // Phase increment.
  uint16_t phase_increment_;

  // Current phase of the lfo.
  uint16_t phase_;
  uint16_t previous_phase_;

  // Copy of the shape used by this lfo.
  uint8_t shape_;

  // Current value of S&H.
  uint8_t value_;

  DISALLOW_COPY_AND_ASSIGN(Lfo);
};

}  // namespace hardware_shruthi

#endif  // HARDWARE_SHRUTHI_OSCILLATOR_H_
