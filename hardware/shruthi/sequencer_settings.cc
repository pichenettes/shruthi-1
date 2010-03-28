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
// Sequencer settings.

#include "hardware/shruthi/sequencer_settings.h"

#include <avr/eeprom.h>
#include <avr/pgmspace.h>

namespace hardware_shruthi {

static const uint16_t kSequencerSettingsOffset = sizeof(Patch) * kPatchBankSize;

void SequencerSettings::EepromSave(uint8_t slot) const {
  uint8_t* data = (uint8_t *)(&steps);
  uint8_t* destination = (uint8_t*)(kSequencerSettingsOffset + slot * kSequenceSize);
  eeprom_write_block(data, destination, kSequenceSize);
}

void SequencerSettings::EepromLoad(uint8_t slot) {
  uint8_t* source = (uint8_t*)(kSequencerSettingsOffset + slot * kSequenceSize);
  uint8_t* data = (uint8_t *)(&steps);
  eeprom_read_block(data, source, kSequenceSize);
}

}  // hardware_shruthi
