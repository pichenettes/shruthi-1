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

#include "hardware/shruthi/midi_dispatcher.h"

namespace hardware_shruthi {

/* static */
uint8_t MidiDispatcher::current_parameter_index_;

/* static */
uint8_t MidiDispatcher::data_entry_counter_;

/* static */
uint8_t MidiDispatcher::current_bank_ = 0;

MidiDispatcher midi_dispatcher;

const uint8_t kDataEntryResendRate = 32;

/* static */
void MidiDispatcher::NoteKilled(uint8_t note) {
  if (mode() == MIDI_OUT_SEQUENCER) {
    Send3(0x90 | channel(), note, 0);
  }
}

/* static */
void MidiDispatcher::NoteTriggered(uint8_t note, uint8_t velocity) {
  if (mode() == MIDI_OUT_SEQUENCER) {
    Send3(0x90 | channel(), note, velocity);
  }
}

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
void MidiDispatcher::Send2(uint8_t status, uint8_t a) {
  OutputBuffer::Overwrite(status);
  OutputBuffer::Overwrite(a);
}

/* static */
void MidiDispatcher::Send3(uint8_t status, uint8_t a, uint8_t b) {
  OutputBuffer::Overwrite(status);
  OutputBuffer::Overwrite(a);
  OutputBuffer::Overwrite(b);
}

/* static */
void MidiDispatcher::SendParameter(uint8_t index, uint8_t value) {
  // Do not forward changes of system settings!
  if (index >= sizeof(Patch)) {
    return;
  }
  ++data_entry_counter_;
  if (mode() >= MIDI_OUT_FULL) {
    if (current_parameter_index_ != index || \
        data_entry_counter_ >= kDataEntryResendRate) {
      Send3(0xb0 | channel(), hardware_midi::kNrpnLsb, index);
      current_parameter_index_ = index;
      data_entry_counter_ = 0;
    }
    if (value & 0x80) {
      Send3(0xb0 | channel(), hardware_midi::kDataEntryMsb, 1);
    }
    Send3(0xb0 | channel(), hardware_midi::kDataEntryLsb, value & 0x7f);
  }
}

}  // namespace hardware_shruthi
