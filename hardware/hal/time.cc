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
// Real time clock. Based on the code in the arduino core library
// by David A. Mellis.

#include "hardware/hal/time.h"

#include "hardware/hal/timer.h"

namespace hardware_hal {

const uint32_t microseconds_per_timer0_overflow =
    (64 * 256) / (F_CPU / 1000000L);
const uint32_t milliseconds_increment =
    microseconds_per_timer0_overflow / 1000;

const uint32_t fractional_increment = (
    microseconds_per_timer0_overflow % 1000) >> 3;

const uint32_t fractional_max = 1000 >> 3;

volatile uint32_t timer0_milliseconds = 0;
static uint8_t timer0_fractional = 0;

TIMER_0_TICK {
  uint32_t m = timer0_milliseconds;
  uint8_t f = timer0_fractional;

  m += milliseconds_increment;
  f += fractional_increment;
  if (f >= fractional_max) {
    f -= fractional_max;
    m += 1;
  }

  timer0_fractional = f;
  timer0_milliseconds = m;
}

uint32_t Delay(uint32_t delay) {
  uint32_t t = milliseconds() + delay;
  while (milliseconds() < t);
}

uint32_t milliseconds() {
  uint32_t m;
  uint8_t oldSREG = SREG;
  cli();
  m = timer0_milliseconds;
  SREG = oldSREG;
  return m;
}

void InitClock() {
  MutableTimer0::set_prescaler(3);
  MutableTimer0::set_mode(TIMER_FAST_PWM);
  MutableTimer0::Start();
}

}  //namespace hardware_hal
