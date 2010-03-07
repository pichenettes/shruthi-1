// Copyright 2010 Olivier Gillet.
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

#include "hardware/hal/devices/rotary_encoder.h"
#include "hardware/hal/init_atmega.h"
#include "hardware/hal/serial.h"
#include "hardware/hal/time.h"
#include "hardware/utils/pretty_printer.h"

using namespace hardware_hal;
using namespace hardware_utils;

typedef Serial<SerialPort0, 9600, DISABLED, POLLED> Debug;
typedef RotaryEncoder<Gpio<0>, Gpio<1>, Gpio<2> > Encoder;

int main(void) {
  PrettyPrinter<Debug> debug_output;
  Encoder encoder;
  int16_t value = 0;
  
  InitAtmega(true);
  Debug::Init();
  encoder.Init();
  while (1) {
    int8_t delta = encoder.Read();
    value += delta;
    if (delta != 0) {
      debug_output << value << " " << int(delta) << endl;
    }
    if (encoder.clicked()) {
      debug_output << "clicked!" << endl;
    }
  }
}
