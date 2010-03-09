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
#include "hardware/hal/input_array.h"
#include "hardware/hal/devices/output_array.h"
#include "hardware/hal/serial.h"
#include "hardware/utils/pretty_printer.h"

using namespace hardware_hal;
using namespace hardware_utils;

typedef InputArray<
    DigitalInput<23>,
    6> Switches;

typedef Serial<SerialPort0, 9600, DISABLED, POLLED> Debug;
PrettyPrinter<Debug> debug_output;

int main(void) {
  InitAtmega(true);
  OutputArray<Gpio<22>, Gpio<20>, Gpio<16>, 11, 4, MSB_FIRST, false> leds;
  Switches switches;
  uint8_t current_led = 0;
  uint8_t intensity = 15;
  uint8_t divide = 0;
  Debug::Init();

  switches.Init();
  leds.Init();
  DigitalInput<23>::EnablePullUpResistor();
  uint8_t full = 0;
  while (1) {
    ++divide;
    if ((divide & 3) == 0) {
      Switches::Event event = switches.Read();
      if (event.event == EVENT_RAISED && event.time > 100) {
        debug_output << "id: " << int(event.id) << endl;
        switch (event.id) {
          case 0:
            if (current_led > 0) {
              --current_led;
            }
            break;
          
          case 1:
            if (current_led < 7) {
              ++current_led;
            }
            break;
          
          case 2:
            if (intensity > 0) {
              --intensity;
            }
            break;

          case 3:
            if (intensity < 15) {
              ++intensity;
            }
            break;

          case 4:
            intensity = 15;
            current_led = 0;
            full = 0;
            break;
            
          case 5:
            full = ~full;
            break;
        }
      }
    }
    leds.Clear();
    for (uint8_t i = 0; i < 8; ++i) {
      leds.set_value(i, (i == current_led || full) ? intensity : 0);
    }
    uint8_t muxed = switches.active_input();
    leds.set_value(8, muxed & 1 ? 15 : 0);
    leds.set_value(9, muxed & 2 ? 15 : 0);
    leds.set_value(10, muxed & 4 ? 15 : 0);
    leds.Output();
  }
}
