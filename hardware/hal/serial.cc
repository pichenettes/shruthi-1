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
// Fast serial (for the onboard UART), using compile time optimizations.

#include "hardware/hal/serial.h"
#include "hardware/hal/gpio.h"

#include <avr/interrupt.h>

using namespace hardware_hal;

ISR(USART_RX_vect) {
   // We don't know which uart generated the interrupt, so we tried to read
   // the data on both.
   SerialInput<SerialPort0>::Received();
   SerialInput<SerialPort1>::Received();
}
