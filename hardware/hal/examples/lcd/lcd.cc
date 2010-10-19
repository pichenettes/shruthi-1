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

#include "hardware/hal/devices/buffered_display.h"
#include "hardware/hal/devices/hd44780_lcd.h"
#include "hardware/hal/gpio.h"
#include "hardware/hal/parallel_io.h"
#include "hardware/hal/init_atmega.h"
#include "hardware/hal/time.h"
#include "hardware/utils/string.h"

using namespace hardware_hal;
using namespace hardware_utils;

typedef Hd44780Lcd<
    Gpio<18>,
    Gpio<19>,
    ParallelPort<PortC, PARALLEL_NIBBLE_HIGH> > Lcd;

Lcd lcd;
BufferedDisplay<Lcd> display;

uint8_t chars[] = {
   0,      0,      0,      0,      0,      0,      0,      0,
   2,      3,      3,      2,      2,     14,     30,     12,
   0,      0,      0,      4,      4,     14,     17,     31,
   4,     14,     21,      4,      4,      4,      4,      0,
   0,      4,      4,      4,      4,     21,     14,      4,
   0,      0,      0,      8,     21,      2,      0,      0,
   8,     20,      9,     21,      3,      5,     17,     14,
  14,     17,     31,     17,     23,     21,     21,      0,
};

static uint8_t cpt;

TIMER_2_TICK {
  cpt = (cpt + 1) & 0x0f;
  if (cpt == 0) {
    lcd.Tick();
  }
}

TIMER_0_TICK {
  TickSystemClock();
}

int main(void) {
  InitAtmega(true);
  lcd.Init();
  Timer<2>::set_prescaler(1);
  Timer<2>::set_mode(TIMER_PWM_PHASE_CORRECT);
  Timer<2>::Start();

  display.Init();

  lcd.SetCustomCharMap(chars, 8, 0);

  display.Print(0, "hello \x01\x02\x03\x04\x05\x06\x07");
  uint16_t cpt = 0;
  display.set_cursor_position(31);
  
  while (1) {
    cpt = (cpt + 1) & 0x07ff;
    if (cpt == 1) {
      display.set_status('@');
    }
    char buff[5];
    display.Tick();
    UnsafeItoa(cpt, 5, buff);
    ++cpt;
    display.Print(1, buff);
    Delay(1);
  }
}
