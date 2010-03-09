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
// Instance of the display class, configured for the Shruti-1 project.

#ifndef HARDWARE_SHRUTHI_DISPLAY_H_
#define HARDWARE_SHRUTHI_DISPLAY_H_

#include "hardware/base/base.h"
#include "hardware/hal/devices/buffered_display.h"
#include "hardware/hal/devices/hd44780_lcd.h"
#include "hardware/hal/gpio.h"
#include "hardware/hal/parallel_io.h"
#include "hardware/shruthi/shruthi.h"

using hardware_hal::BufferedDisplay;
using hardware_hal::Gpio;
using hardware_hal::Hd44780Lcd;
using hardware_hal::PARALLEL_NIBBLE_LOW;
using hardware_hal::ParallelPort;
using hardware_hal::PortC;

namespace hardware_shruthi {

typedef Hd44780Lcd<
    Gpio<kPinLcdRs>,
    Gpio<kPinLcdEnable>,
    ParallelPort<PortC, PARALLEL_NIBBLE_LOW> > Lcd;

extern Lcd lcd;
extern BufferedDisplay<Lcd> display;

}  // namespace hardware_shruthi

#endif  // HARDWARE_SHRUTHI_DISPLAY_H_
