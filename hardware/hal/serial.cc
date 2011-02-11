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

#include <avr/interrupt.h>

#include "hardware/hal/gpio.h"

using namespace hardware_hal;

#ifdef SERIAL_RX_0

ISR(USART0_RX_vect) {
  SerialInput<SerialPort0>::Received();
}

#endif  // SERIAL_RX_0


#ifdef SERIAL_RX_1

ISR(USART1_RX_vect) {
  SerialInput<SerialPort1>::Received();
}

#endif  // SERIAL_RX_1
