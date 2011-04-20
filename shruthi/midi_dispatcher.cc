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
// Instance of the midi out filter class.

#include "shruthi/midi_dispatcher.h"

namespace shruthi {

/* static */
uint8_t MidiDispatcher::current_parameter_index_;

/* static */
uint8_t MidiDispatcher::data_entry_counter_;

/* static */
uint8_t MidiDispatcher::current_bank_ = 0;

MidiDispatcher midi_dispatcher;

/* static */
void MidiDispatcher::Send(uint8_t status, uint8_t* data, uint8_t size) {
  OutputBuffer::Overwrite(status);
  if (size) {
    OutputBuffer::Overwrite(*data++);
    --size;
  }
  if (size) {
    OutputBuffer::Overwrite(*data++);
    --size;
  }
}

/* static */
void MidiDispatcher::Send3(uint8_t status, uint8_t a, uint8_t b) {
  OutputBuffer::Overwrite(status);
  OutputBuffer::Overwrite(a);
  OutputBuffer::Overwrite(b);
}

}  // namespace shruthi
