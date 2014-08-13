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
// This class dispatches received MIDI events to the different components of the
// synth (synthesis engine, display, editor) that might react to them.

#ifndef SHRUTHI_MIDI_DISPATCHER_H_
#define SHRUTHI_MIDI_DISPATCHER_H_

#include "avrlib/base.h"
#include "avrlib/ring_buffer.h"
#include "midi/midi.h"
#include "shruthi/display.h"
#include "shruthi/editor.h"
#include "shruthi/parameter.h"
#include "shruthi/part.h"
#include "shruthi/storage.h"

namespace shruthi {

const uint8_t kDataEntryResendRate = 32;


struct LowPriorityBufferSpecs {
  enum {
    buffer_size = 128,
    data_size = 8,
  };
  typedef avrlib::DataTypeForSize<data_size>::Type Value;
};

class MidiDispatcher : public midi::MidiDevice {
 public:
  typedef avrlib::RingBuffer<LowPriorityBufferSpecs> OutputBuffer;
  MidiDispatcher() { }

  // ------ MIDI in handling ---------------------------------------------------

  // Forwarded to the controller.
  static inline void NoteOn(uint8_t channel, uint8_t note, uint8_t velocity) {
    display.set_status('\x01');
    if (!editor.OnNoteOn(note, velocity)) {
      part.NoteOn(channel, note, velocity);
    }
  }
  static inline void NoteOff(uint8_t channel, uint8_t note, uint8_t velocity) {
    part.NoteOff(channel, note);
  }

  // Handled.
  static inline void ControlChange(
      uint8_t channel,
      uint8_t controller,
      uint8_t value) {
    if (controller == midi::kBankMsb) {
      current_bank_ = value;
    } else {
      display.set_status('\x05');
      part.ControlChange(controller, value);
    }
  }
  static inline void PitchBend(uint8_t channel, uint16_t pitch_bend) {
    display.set_status('\x02');
    part.PitchBend(pitch_bend);
  }
  static void Aftertouch(uint8_t channel, uint8_t note, uint8_t velocity) {
    part.Aftertouch(note, velocity);
  }
  static void Aftertouch(uint8_t channel, uint8_t velocity) {
    part.Aftertouch(velocity);
  }
  static void AllSoundOff(uint8_t channel) {
    part.AllSoundOff();
  }
  static void ResetAllControllers(uint8_t channel) {
    part.ResetAllControllers();
  }
  static void AllNotesOff(uint8_t channel) {
    part.AllNotesOff();
  }
  static void OmniModeOff(uint8_t channel) {
    part.OmniModeOff(channel);
  }
  static void OmniModeOn(uint8_t channel) {
    part.OmniModeOn();
  }
  
  static void ProgramChange(uint8_t channel, uint8_t program) {
    uint16_t n = program + (current_bank_ << 7);
    // bank above 0x40 treat as sequence change
    if (current_bank_ >= 0x40) {
      uint16_t n = program + ((current_bank_ - 0x40) << 7);
      if (n < Storage::size<SequencerSettings>()) {
        Storage::LoadSequence(n);
        part.Touch(false);
      }
    } else {
      uint16_t n = program + (current_bank_ << 7);
      if (n < Storage::size<Patch>()) {
        editor.set_current_patch_number(n);
        Storage::LoadPatch(n);
        Storage::LoadSequence(n);
        part.Touch(false);
      }
    }
  }
  
  static void Reset() { part.Reset(); }
  static void Clock() { 
    if (!part.internal_clock()) {
      part.Clock(false);
    }
  }
  static void Start() {
    if (!part.internal_clock()) {
      part.Start(false);
    }
  }
  static void Continue() {
    if (!part.internal_clock()) {
      part.Start(false);
    }
  }
  static void Stop() {
    if (!part.internal_clock()) {
      part.Stop(false);
    }
  }
  
  static void SysExStart() {
    ProcessSysEx(0xf0);
  }
  static void SysExByte(uint8_t sysex_byte) {
    ProcessSysEx(sysex_byte);
  }
  static void SysExEnd() {
    ProcessSysEx(0xf7);
    if (Storage::sysex_rx_state() == RECEPTION_OK) {
      display.set_status('+');
      part.Touch(false);
      editor.Refresh();
    } else {
      display.set_status('#');
    }
  }
  
  static uint8_t CheckChannel(uint8_t channel) {
    const SystemSettings& settings = part.system_settings();
    return settings.midi_channel == 0 ||
           settings.midi_channel == (channel + 1);
  }
  
  static void RawMidiData(
      uint8_t status,
      uint8_t* data,
      uint8_t data_size,
      uint8_t accepted_channel) {
    uint8_t hi = status & 0xf0;
    
    // When is parsed midi data forwarded to the MIDI out?
    // - When the data is a channel different from the RX channel.
    // - When we are in "Full" mode.
    // - When the midi message is not a note on/note off.
    if (mode() >= MIDI_OUT_FULL) {
      if (status != 0xf0 && status != 0xf7) {
        if ((hi != 0x80 && hi != 0x90) ||
            mode() == MIDI_OUT_FULL ||
            !accepted_channel) {
          Send(status, data, data_size);
        }
      }
    } else if (mode() == MIDI_OUT_SEQUENCER) {
      if ((hi == 0xf0 && status != 0xf0 && status != 0xf7)) {
        Send(status, NULL, 0);
      }
    }
  }
  
  static void RawByte(uint8_t byte) {
    // Report that some data has been received. The MIDI Out filter might
    // propagate it directly to the output if "Soft Thru" is enabled.
    if (mode() == MIDI_OUT_SOFT_THRU) {
      OutputBuffer::Overwrite(byte);
    }
  }
  
  static uint8_t readable() {
    return OutputBuffer::readable();
  }

  static uint8_t ImmediateRead() {
    return OutputBuffer::ImmediateRead();
  }
  
  // ------ MIDI out handling --------------------------------------------------
  static inline void OnInternalNoteOff(uint8_t note) {
    if (mode() == MIDI_OUT_SEQUENCER) {
      Send3(0x90 | channel(), note, 0);
    }
  }
  
  static inline void OnInternalNoteOn(uint8_t note, uint8_t velocity) {
    if (mode() == MIDI_OUT_SEQUENCER) {
      Send3(0x90 | channel(), note, velocity);
    }
  }
  
  static inline void ForwardNoteOn(
      uint8_t channel,
      uint8_t note,
      uint8_t velocity) {
    Send3(0x90 | channel, note, velocity);
  }
  
  static inline void ForwardNoteOff(uint8_t channel, uint8_t note) {
    Send3(0x90 | channel, note, 0);
  }

  static inline void OnStart() {
    if (mode() == MIDI_OUT_SEQUENCER) {
      SendNow(0xfa);
    }
  }

  static inline void OnStop() {
    if (mode() == MIDI_OUT_SEQUENCER) {
      SendNow(0xfc);
    }
  }
  
  static inline void OnClock() {
    if (mode() == MIDI_OUT_SEQUENCER) {
      SendNow(0xf8);
    }
  }
  
  static inline void OnProgramChange(uint16_t n) {
    uint8_t channel = (part.system_settings().midi_channel - 1) & 0xf;
    if (mode() >= MIDI_OUT_FULL) {
      Send3(0xb0 | channel, midi::kBankMsb, n >> 7);
      Send3(0xc0 | channel, n & 0x7f, 0xfe /* Dummy active sensing */);
    }
  }
  
  static inline void OnEdit(uint8_t index, uint8_t offset, uint8_t value) {
    // Do not forward changes of system settings!
    if (offset >= PRM_SYS_MASTER_TUNING) {
      return;
    }
    if (mode() < MIDI_OUT_FULL && mode() != MIDI_OUT_CONTROLLER) {
      return;
    }
    
    const Parameter& parameter = parameter_manager.parameter(index);
    if (parameter.midi_cc[0]) {
      uint8_t original = value;
      if (parameter.unit != UNIT_RAW_UINT8) {
        value -= parameter.min_value;
        uint8_t range = parameter.max_value - parameter.min_value + 1;
        value = U8U8Mul(value, 128) / range;
        if (value != 127 && parameter.Scale(value) != original) {
          ++value;
        }
        if (value != 0 && parameter.Scale(value) != original) {
          --value;
        }
      }
      Send3(0xb0 | channel(), parameter.midi_cc[0], value);
    } else {
      Send3(0xb0 | channel(), midi::kNrpnMsb, 0);
      Send3(0xb0 | channel(), midi::kNrpnLsb, offset);
      uint8_t msb = (value & 0x80) ? 1 : 0;
      Send3(0xb0 | channel(), midi::kDataEntryMsb, msb);
      Send3(0xb0 | channel(), midi::kDataEntryLsb, value & 0x7f);
    }
  }
  
  static void Flush() {
    running_status_ = 0;
    while (OutputBuffer::readable());
  }
  
  static void Send3(uint8_t a, uint8_t b, uint8_t c);
  static uint8_t channel() {
    return part.system_settings().midi_channel == 0
        ? 0
        : part.system_settings().midi_channel - 1;
  }
  
 private:
  static void Send(uint8_t status, uint8_t* data, uint8_t size);
  static void SendNow(uint8_t byte);
  
  static void ProcessSysEx(uint8_t byte) {
    if (mode() >= MIDI_OUT_FULL) {
      Send(byte, NULL, 0);
    }
    Storage::SysExReceive(byte);
  }
  
  static uint8_t mode() { return part.system_settings().midi_out_mode; }
  
  static uint8_t current_bank_;
  static uint8_t running_status_;
  
  DISALLOW_COPY_AND_ASSIGN(MidiDispatcher);
};

extern MidiDispatcher midi_dispatcher;

}  // namespace shruthi

#endif // SHRUTHI_MIDI_DISPATCHER_H_
