// Copyright 2009 Emilie Gillet.
//
// Author: Emilie Gillet (emilie.o.gillet@gmail.com)
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

#include "shruthi/sequencer_settings.h"

#include <avr/pgmspace.h>
#include <string.h>

#include "shruthi/resources.h"
#include "avrlib/string.h"

using namespace avrlib;

namespace shruthi {

static const prog_char note_names[] PROGMEM = " CC# DD# E FF# GG# AA# B";
static const prog_char octaves[] PROGMEM = "-012345678";

void SequencerSettings::PrepareForWrite() {
  // Clear all the notes after the cycle mark.
  for (uint8_t i = pattern_size; i < kNumSteps; ++i) {
    steps[i].clear();
  }
}

/* static */
void SequencerSettings::PrintNote(uint8_t note, char* buffer) {
  uint8_t octave = 0;
  while (note >= 12) {
    ++octave;
    note -= 12;
  }
  buffer[0] = ResourcesManager::Lookup<char, uint8_t>(note_names, note << 1);
  buffer[1] = ResourcesManager::Lookup<char, uint8_t>(note_names, 1 + (note << 1));
  buffer[2] = ResourcesManager::Lookup<char, uint8_t>(octaves, octave);
}

void SequencerSettings::PrintStep(uint8_t step, char* buffer) const {
  buffer[1] = 0x7c;
  UnsafeItoa<int16_t>(step, 2, buffer + 2);
  AlignRight(buffer + 2, 2);
  if (buffer[2] == ' ') {
    buffer[2] = '0';
  }
  buffer[4] = 0x7c;
  PrintNote(steps[step].note(), buffer + 5);
  buffer[9] = steps[step].character();
  if (steps[step].gate()) {
    buffer[11] = NibbleToAscii(steps[step].velocity() >> 4);
  }
  buffer[13] = NibbleToAscii(steps[step].controller()),
  buffer[15] = 0x7c;
}

}  // shruthi
