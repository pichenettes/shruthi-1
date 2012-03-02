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
// System settings.

#include "shruthi/system_settings.h"

#include <avr/eeprom.h>
#include <avr/pgmspace.h>
#include <string.h>

namespace shruthi {

void SystemSettings::EepromSave() const {
  uint8_t* data = (uint8_t *)(this);
  uint8_t checksum = 0;
  uint8_t* destination = (uint8_t*)(0);
  for (int16_t i = 0; i < sizeof(SystemSettings); ++i) {
    checksum += data[i];
  }
  eeprom_write_block(data, destination, sizeof(SystemSettings));
  eeprom_write_byte(destination + sizeof(SystemSettings), -checksum);
}

uint8_t SystemSettings::EepromLoad() {
  uint8_t buffer[sizeof(SystemSettings) + 1];
  uint8_t* source = (uint8_t*)(0);
  uint8_t checksum = 0;
  eeprom_read_block(buffer, source, sizeof(SystemSettings) + 1);
  for (int16_t i = 0; i < sizeof(SystemSettings) + 1; ++i) {
    checksum += buffer[i];
  }
  if (checksum == 0) {
    uint8_t* data = (uint8_t *)(this);
    memcpy(data, buffer, sizeof(SystemSettings));
  }
  return checksum == 0;
}

void ExtraSystemSettings::EepromSave() const {
  uint8_t* data = (uint8_t *)(this);
  uint8_t* destination = (uint8_t*)(E2END - 32);
  eeprom_write_block(data, destination, sizeof(ExtraSystemSettings));
}

void ExtraSystemSettings::EepromLoad() {
  uint8_t* data = (uint8_t *)(this);
  uint8_t* source = (uint8_t*)(E2END - 32);
  eeprom_read_block(data, source, sizeof(ExtraSystemSettings));
}

}  // shruthi
