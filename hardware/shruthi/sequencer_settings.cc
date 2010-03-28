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
#include <string.h>

#include "hardware/shruthi/resources.h"
#include "hardware/utils/string.h"

using namespace hardware_utils;
using namespace hardware_resources;

namespace hardware_shruthi {

static const uint16_t kSequencerSettingsOffset = sizeof(Patch) * kPatchBankSize;

void SequencerSettings::EepromSave(uint8_t slot) {
  uint8_t* data = (uint8_t *)(steps);
  uint8_t* destination = (uint8_t*)(
      kSequencerSettingsOffset + slot * kSequenceSize);
  // Clear all the notes after the cycle mark.
  for (uint8_t i = pattern_size; i < kNumSteps; ++i) {
    steps[i].clear();
  }
  eeprom_write_block(data, destination, kSequenceSize);
}

void SequencerSettings::EepromLoad(uint8_t slot) {
  uint8_t* source = (uint8_t*)(kSequencerSettingsOffset + slot * kSequenceSize);
  uint8_t* data = (uint8_t *)(steps);
  eeprom_read_block(data, source, kSequenceSize);
  pattern_size = kNumSteps;
  for (uint8_t i = 0; i < kNumSteps; ++i) {
    if (steps[i].blank()) {
      pattern_size = i;
      break;
    }
  }
}

void SequencerSettings::Backup() const {
  memcpy(undo_buffer_, steps, sizeof(SequenceStep) * kNumSteps);
}

void SequencerSettings::Restore() {
  memcpy(steps, undo_buffer_, sizeof(SequenceStep) * kNumSteps);
}

static const prog_char note_names[] PROGMEM = " CC# DD# E FF# GG# AA# B";
static const prog_char octaves[] PROGMEM = "_-01234567";

void SequencerSettings::PrintStep(uint8_t step, char* buffer) const {
  buffer[1] = 0x7c;
  UnsafeItoa<int16_t>(step, 2, buffer + 2);
  AlignRight(buffer + 2, 2);
  if (buffer[2] == ' ') {
    buffer[2] = '0';
  }
  uint8_t note = steps[step].note();
  uint8_t octave = 0;
  while (note >= 12) {
    ++octave;
    note -= 12;
  }
  buffer[4] = 0x7c;
  buffer[5] = SimpleResourcesManager::Lookup<char, uint8_t>(note_names,
                                                            note << 1);
  buffer[6] = SimpleResourcesManager::Lookup<char, uint8_t>(note_names,
                                                            1 + (note << 1));
  buffer[7] = SimpleResourcesManager::Lookup<char, uint8_t>(octaves, octave);
  buffer[9] = steps[step].character();
  if (steps[step].gate()) {
    buffer[11] = NibbleToAscii(steps[step].velocity() >> 4);
  }
  buffer[13] = NibbleToAscii(steps[step].controller()),
  buffer[15] = 0x7c;
}

/* static */
uint8_t SequencerSettings::undo_buffer_[sizeof(SequenceStep) * kNumSteps];

}  // hardware_shruthi
