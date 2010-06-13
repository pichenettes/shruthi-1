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
// Real time clock.

#ifndef HARDWARE_HAL_TIME_H_
#define HARDWARE_HAL_TIME_H_

#include "hardware/base/base.h"

namespace hardware_hal {

uint32_t milliseconds();
uint32_t Delay(uint32_t delay);

void InitClock();

const uint32_t microseconds_per_timer0_overflow =
    (64 * 256) / (F_CPU / 1000000L);
const uint32_t milliseconds_increment =
    microseconds_per_timer0_overflow / 1000;

const uint32_t fractional_increment = (
    microseconds_per_timer0_overflow % 1000) >> 3;

const uint8_t fractional_max = 1000 >> 3;

extern volatile uint32_t timer0_milliseconds;
extern uint8_t timer0_fractional;

inline void TickSystemClock() {
  // Compile-time optimization: with a 20Mhz clock rate, milliseconds_increment
  // is always null, so we have to increment it only when there's a
  // fractional overflow!
  if (milliseconds_increment) {
    timer0_milliseconds += milliseconds_increment;
  }
  timer0_fractional += fractional_increment;
  if (timer0_fractional >= fractional_max) {
    timer0_fractional -= fractional_max;
    ++timer0_milliseconds;
  }
}

}  // namespace hardware_hal

#endif  // HARDWARE_HAL_TIME_H_
