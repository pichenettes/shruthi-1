// Copyright 2011 Olivier Gillet.
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
// Resources definitions.
//
// Automatically generated with:
// make resources


#ifndef HARDWARE_BURNITO_RESOURCES_H_
#define HARDWARE_BURNITO_RESOURCES_H_


#include "hardware/base/base.h"

#include <avr/pgmspace.h>


namespace hardware_burnito {

typedef uint8_t ResourceId;

extern const prog_uint8_t* blob_table[];

extern const prog_uint8_t blob_res_eeprom_content[] PROGMEM;
extern const prog_uint8_t blob_res_eeprom_content_tail[] PROGMEM;
#define BLOB_RES_EEPROM_CONTENT 0
#define BLOB_RES_EEPROM_CONTENT_SIZE 32767
#define BLOB_RES_EEPROM_CONTENT_TAIL 1
#define BLOB_RES_EEPROM_CONTENT_TAIL_SIZE 24577

}  // namespace hardware_burnito

#endif  // HARDWARE_BURNITO_RESOURCES_H_
