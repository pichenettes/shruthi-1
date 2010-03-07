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

}  // namespace hardware_hal

#endif  // HARDWARE_HAL_TIME_H_
