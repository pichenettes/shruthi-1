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

#include "hardware/hal/init_atmega.h"
#include "hardware/hal/devices/output_array.h"
#include "hardware/hal/devices/switch_array.h"
#include "hardware/hal/serial.h"
#include "hardware/hal/time.h"
#include "hardware/utils/output_stream.h"

using namespace hardware_hal;
using namespace hardware_utils;

typedef Serial<SerialPort0, 9600, DISABLED, POLLED> Debug;
OutputStream<Debug> debug_output;

TIMER_0_TICK {
  TickSystemClock();
}

int main(void) {
  InitAtmega(true);
  OutputArray<Gpio<22>, Gpio<7>, Gpio<23>, 8, 4, MSB_FIRST, false> leds;
  SwitchArray<Gpio<22>, Gpio<7>, Gpio<6>, 6> switches;

  uint8_t current_led = 0;
  uint8_t intensity = 15;
  uint8_t divide = 0;

  Debug::Init();
  leds.Init();
  switches.Init();
  uint8_t full = 0;
  while (1) {
    ++divide;
    if ((divide & 3) == 0) {
      switches.Read();
      if (switches.released()) {
        KeyEvent released = switches.key_event();
        debug_output << "id: " << int(released.id);
        debug_output << " hold time:" << int(released.hold_time);
        debug_output << " shifted: " << int(released.shifted) << endl;
        switch (released.id) {
          case 5:
            if (current_led > 0) {
              --current_led;
            }
            break;

          case 4:
            if (current_led < 7) {
              ++current_led;
            }
            break;

          case 3:
            if (intensity > 0) {
              --intensity;
            }
            break;

          case 2:
            if (intensity < 15) {
              ++intensity;
            }
            break;

          case 1:
            intensity = 15;
            current_led = 0;
            full = 0;
            break;

          case 0:
            full = ~full;
            break;
        }
      }
    }
    leds.Clear();
    for (uint8_t i = 0; i < 8; ++i) {
      leds.set_value(i, (i == current_led || full) ? intensity : 0);
    }
    leds.Write();
  }
}
