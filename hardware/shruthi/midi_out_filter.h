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
//
// -----------------------------------------------------------------------------
//
// This class is responsible for collecting from various sources messages that
// might be potentially translated into output on the MIDI OUT.

#ifndef HARDWARE_SHRUTHI_MIDI_OUT_FILTER_H_
#define HARDWARE_SHRUTHI_MIDI_OUT_FILTER_H_

#include "hardware/base/base.h"
#include "hardware/hal/ring_buffer.h"
#include "hardware/midi/midi.h"
#include "hardware/shruthi/shruthi.h"
#include "hardware/shruthi/system_settings.h"

namespace hardware_shruthi {

class MidiOutFilter {
 public:
  enum {
    buffer_size = 128,
    data_size = 8,
  };
  typedef hardware_hal::Buffer<MidiOutFilter> OutputBuffer;
  typedef hardware_hal::DataTypeForSize<data_size>::Type Value;

  MidiOutFilter() { }
  
  static void UpdateSystemSettings(const SystemSettings& system_settings) {
    channel_ = system_settings.midi_channel == 0
        ? 0
        : system_settings.midi_channel - 1;
    mode_ = system_settings.midi_out_mode;
  }
  
  static void NoteKilled(uint8_t note) {
    if (mode_ == MIDI_OUT_SEQUENCER) {
      OutputBuffer::Overwrite(0x90 | channel_);
      OutputBuffer::Overwrite(note);
      OutputBuffer::Overwrite(0);
    }
  }

  static void NoteTriggered(uint8_t note, uint8_t velocity) {
    if (mode_ == MIDI_OUT_SEQUENCER) {
      OutputBuffer::Overwrite(0x90 | channel_);
      OutputBuffer::Overwrite(note);
      OutputBuffer::Overwrite(velocity);
    }
  }
  
  static void Send(uint8_t status, uint8_t* data, uint8_t size) {
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
  
  static void Send3(uint8_t status, uint8_t a, uint8_t b) {
    OutputBuffer::Overwrite(status);
    OutputBuffer::Overwrite(a);
    OutputBuffer::Overwrite(b);
  }
  
  static void SendParameter(uint8_t index, uint8_t value) {
    if (mode_ >= MIDI_OUT_FULL) {
      if (current_parameter_index_ != index) {
        OutputBuffer::Overwrite(0xb0 | channel_);
        OutputBuffer::Overwrite(hardware_midi::kNrpnLsb);
        OutputBuffer::Overwrite(index);
        current_parameter_index_ = index;
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
  
  static uint8_t readable() {
    return OutputBuffer::readable();
  }

  static uint8_t ImmediateRead() {
    return OutputBuffer::ImmediateRead();
  }
  
  static void RawDataReceived(uint8_t data) {
    if (mode_ == MIDI_OUT_SOFT_THRU) {
      OutputBuffer::Overwrite(data);
    }
  }
    
  static uint8_t mode_;
  static uint8_t channel_;
  static uint8_t current_parameter_index_;

  DISALLOW_COPY_AND_ASSIGN(MidiOutFilter);
};

extern MidiOutFilter midi_out_filter;

}  // namespace hardware_shruthi

#endif  // HARDWARE_SHRUTHI_MIDI_OUT_FILTER_H_
