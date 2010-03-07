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

#ifndef HARDWARE_HAL_WATCHDOG_TIMER_
#define HARDWARE_HAL_WATCHDOG_TIMER_

#include <avr/wdt.h>

#include "hardware/base/base.h"

namespace hardware_hal {
  
// Note: this requires the bootloader to clear the Watchdog timer flags just
// after start-up.
inline void SystemReset(uint8_t interval) {
  wdt_enable(interval);
}

}  // namespace hardware_hal

#endif  // HARDWARE_HAL_WATCHDOG_TIMER_
