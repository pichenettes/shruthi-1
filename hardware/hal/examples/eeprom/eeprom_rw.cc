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

#include "hardware/hal/devices/external_eeprom.h"
#include "hardware/hal/init_atmega.h"
#include "hardware/hal/serial.h"
#include "hardware/hal/time.h"
#include "hardware/utils/output_stream.h"

using namespace hardware_hal;
using namespace hardware_utils;

// Debug text output.
typedef Serial<SerialPort0, 9600, DISABLED, POLLED> Debug;
OutputStream<Debug> debug_output;

ExternalEeprom<> eeprom;

int main(void) {
  InitAtmega(true);
  Debug::Init();
  eeprom.Init();

  uint8_t buffer[32];
  for (uint8_t i = 0; i < 32; ++i) {
    buffer[i] = i + 100;
  }

  eeprom.WriteWithinBlock(0x20, buffer, 32);
  debug_output << "Written" << endl;
  Delay(4);  // Write/read cycles delay.

  debug_output << "Reading" << endl;
  eeprom.SetAddress(0x20);
  for (uint8_t i = 0; i < 32; ++i) {
    debug_output << int(eeprom.Read()) << endl;
  }
  debug_output << "Done" << endl;

  eeprom.SetAddress(0x20);
  uint8_t buffer2[32];
  eeprom.Read(0x20, 32, buffer2);
  for (uint8_t i = 0; i < 32; ++i) {
    debug_output << int(buffer2[i]) << endl;
  }
  debug_output << "Done" << endl;
}
