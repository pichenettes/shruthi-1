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
// Global clock. This works as a 31-bit phase increment counter. To implement
// swing, the value at which the counter wraps is (1 << 31) times a swing
// factor.

#ifndef SHRUTHI_CLOCK_H_
#define SHRUTHI_CLOCK_H_

#include "avrlib/base.h"

namespace shruthi {

class Clock {
 public:
  Clock() { }
  ~Clock() { }
   
  static inline void Init() {
    Update(120);
  }
  static void Update(uint8_t bpm);
  
  static inline void Reset() {
    phase_ = 0;
  }
  
  static inline void Tick() { phase_ += phase_increment_; }
  static inline bool Wrap(int8_t amount) {
    LongWord* w = (LongWord*)(&phase_);
    if (w->bytes[3] >= 128 + amount) {
      w->bytes[3] -= (128 + amount);
      return true;
    } else {
      return false;
    }
  }
  
 private:
  static uint16_t bpm_;
  static uint32_t phase_;
  static uint32_t phase_increment_;
  
  DISALLOW_COPY_AND_ASSIGN(Clock);
};

extern Clock clock;

}  // namespace shruthi

#endif // SHRUTHI_CLOCK_H_
