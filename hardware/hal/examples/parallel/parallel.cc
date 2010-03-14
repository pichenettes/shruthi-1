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
#include "hardware/hal/parallel_io.h"
#include "hardware/hal/time.h"

using namespace hardware_hal;

int main(void) {
  InitAtmega(true);

  ParallelPort<PortC, PARALLEL_NIBBLE_HIGH> count;
  ParallelPort<PortC, PARALLEL_NIBBLE_LOW> scroll;
  uint8_t counter = 0;

  count.set_mode(DIGITAL_OUTPUT);
  scroll.set_mode(DIGITAL_OUTPUT);

  while (1) {
    Delay(100);
    count.Write((++counter) & 15);
    scroll.Write(1 << (counter & 3));
  }
}
