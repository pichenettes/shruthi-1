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

#include "hardware/shruthi/midi_out_filter.h"

namespace hardware_shruthi {

/* static */
uint8_t MidiOutFilter::mode_;

/* static */
uint8_t MidiOutFilter::channel_;

/* static */
uint8_t MidiOutFilter::current_parameter_index_;

/* static */
uint8_t MidiOutFilter::data_entry_counter_;

MidiOutFilter midi_out_filter;

const uint8_t kDataEntryResendRate = 32;

/* static */
void MidiOutFilter::UpdateSystemSettings(
    const SystemSettings& system_settings) {
  channel_ = system_settings.midi_channel == 0
      ? 0
      : system_settings.midi_channel - 1;
  mode_ = system_settings.midi_out_mode;
}

/* static */
void MidiOutFilter::NoteKilled(uint8_t note) {
  if (mode_ == MIDI_OUT_SEQUENCER) {
    OutputBuffer::Overwrite(0x90 | channel_);
    OutputBuffer::Overwrite(note);
    OutputBuffer::Overwrite(0);
  }
}

/* static */
void MidiOutFilter::NoteTriggered(uint8_t note, uint8_t velocity) {
  if (mode_ == MIDI_OUT_SEQUENCER) {
    OutputBuffer::Overwrite(0x90 | channel_);
    OutputBuffer::Overwrite(note);
    OutputBuffer::Overwrite(velocity);
  }
}

/* static */
void MidiOutFilter::Send(uint8_t status, uint8_t* data, uint8_t size) {
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
void MidiOutFilter::Send3(uint8_t status, uint8_t a, uint8_t b) {
  OutputBuffer::Overwrite(status);
  OutputBuffer::Overwrite(a);
  OutputBuffer::Overwrite(b);
}

/* static */
void MidiOutFilter::SendParameter(uint8_t index, uint8_t value) {
  // Do not forward changes of system settings!
  if (index >= sizeof(Patch)) {
    return;
  }
  ++data_entry_counter_;
  if (mode_ >= MIDI_OUT_FULL) {
    if (current_parameter_index_ != index || \
        data_entry_counter_ >= kDataEntryResendRate) {
      OutputBuffer::Overwrite(0xb0 | channel_);
      OutputBuffer::Overwrite(hardware_midi::kNrpnLsb);
      OutputBuffer::Overwrite(index);
      current_parameter_index_ = index;
      data_entry_counter_ = 0;
    }
    if (value & 0x80) {
      OutputBuffer::Overwrite(0xb0 | channel_);
      OutputBuffer::Overwrite(hardware_midi::kDataEntryMsb);
      OutputBuffer::Overwrite(1);
    }
    OutputBuffer::Overwrite(0xb0 | channel_);
    OutputBuffer::Overwrite(hardware_midi::kDataEntryLsb);
    OutputBuffer::Overwrite(value & 0x7f);
  }
}

}  // namespace hardware_shruthi
