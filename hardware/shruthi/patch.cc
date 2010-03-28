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
// Patch.

#include "hardware/shruthi/patch.h"

#include <avr/eeprom.h>
#include <avr/pgmspace.h>

#include "hardware/hal/serial.h"
#include "hardware/shruthi/display.h"
#include "hardware/utils/op.h"

using namespace hardware_hal;
using namespace hardware_utils_op;

namespace hardware_shruthi {

void Patch::Pack(uint8_t* patch_buffer) const {
  STATIC_ASSERT(kPatchSize == sizeof(Patch));
  
  uint8_t* data = (uint8_t*)(this);
  memcpy(patch_buffer, data, sizeof(Patch));
}

uint8_t Patch::CheckBuffer() {
  // No checksum, but since most parameters do not have their MSB set, we can
  // use this property to detect random data.
  for (uint8_t i = 8; i < 32; ++i) {
    if (load_save_buffer_[i] >= 128) {
      return 0;
    }
  }
  return 1;
}

void Patch::Unpack(const uint8_t* patch_buffer) {
  uint8_t* data = (uint8_t*)(this);
  memcpy(data, patch_buffer, sizeof(Patch));
}

void Patch::EepromSave(uint8_t slot) const {
  Pack(load_save_buffer_);
  uint8_t* destination = (uint8_t*)(slot * sizeof(Patch));
  eeprom_write_block(load_save_buffer_, destination, sizeof(Patch));
}

void Patch::EepromLoad(uint8_t slot) {
  uint8_t* source = (uint8_t*)(slot * sizeof(Patch));
  eeprom_read_block(load_save_buffer_, source, sizeof(Patch));
  if (CheckBuffer()) {
    Unpack(load_save_buffer_);
  } else {
    name[0] = '?';
  }
}

static const prog_char sysex_header[] PROGMEM = {
  0xf0,  // <SysEx>
  0x00, 0x20, 0x77,  // TODO(pichenettes): register manufacturer ID.
  0x00, 0x01,  // Product ID for Shruti-1.
  0x01,  // Command: patch transfer.
  0x00,  // Argument: none.
};

void Patch::SysExSend() const {
  Serial<SerialPort0, 31250, DISABLED, POLLED> midi_output;

  Pack(load_save_buffer_);

  // Outputs the SysEx header.
  for (uint8_t i = 0; i < sizeof(sysex_header); ++i) {
    midi_output.Write(pgm_read_byte(sysex_header + i));
  }

  // Outputs the patch data, in high-low nibblized form.
  uint8_t checksum = 0;  // Sum of all patch data bytes.
  for (uint8_t i = 0; i < sizeof(Patch); ++i) {
    checksum += load_save_buffer_[i];
    midi_output.Write(ShiftRight4(load_save_buffer_[i]));
    midi_output.Write(load_save_buffer_[i] & 0x0f);
  }

  midi_output.Write(ShiftRight4(checksum));
  midi_output.Write(checksum & 0x0f);

  midi_output.Write(0xf7);  // </SysEx>
}

void Patch::SysExReceive(uint8_t sysex_byte) {
  if (sysex_byte == 0xf0) {
    sysex_reception_checksum_ = 0;
    sysex_bytes_received_ = 0;
    sysex_reception_state_ = RECEIVING_HEADER;
  }
  switch (sysex_reception_state_) {
    case RECEIVING_HEADER:
      if (pgm_read_byte(sysex_header + sysex_bytes_received_) == sysex_byte) {
        sysex_bytes_received_++;
        if (sysex_bytes_received_ >= sizeof(sysex_header)) {
          sysex_reception_state_ = RECEIVING_DATA;
          sysex_bytes_received_ = 0;
        }
      } else {
        sysex_reception_state_ = RECEIVING_FOOTER;
      }
      break;

    case RECEIVING_DATA:
      {
        uint8_t i = sysex_bytes_received_ >> 1;
        if (sysex_bytes_received_ & 1) {
          load_save_buffer_[i] |= sysex_byte & 0xf;
          if (i < sizeof(Patch)) {
            sysex_reception_checksum_ += load_save_buffer_[i];
          }
        } else {
          load_save_buffer_[i] = ShiftLeft4(sysex_byte);
        }
        sysex_bytes_received_++;
        if (sysex_bytes_received_ >= (sizeof(Patch) + 1) * 2) {
          sysex_reception_state_ = RECEIVING_FOOTER;
        }
      }
    break;

  case RECEIVING_FOOTER:
    if (sysex_byte == 0xf7 &&
        sysex_reception_checksum_ == load_save_buffer_[sizeof(Patch)] &&
        CheckBuffer()) {
      Unpack(load_save_buffer_);
      sysex_reception_state_ = RECEPTION_OK;
    } else {
      sysex_reception_state_ = RECEPTION_ERROR;
    }
    break;
  }
}

void Patch::Backup() const {
  Pack(undo_buffer_);
}

void Patch::Restore() {
  Unpack(undo_buffer_);
}

/* static */
uint8_t Patch::load_save_buffer_[sizeof(Patch) + 1];

/* static */
uint8_t Patch::undo_buffer_[sizeof(Patch)];

/* static */
uint8_t Patch::sysex_bytes_received_;

/* static */
uint8_t Patch::sysex_reception_checksum_;

/* static */
uint8_t Patch::sysex_reception_state_;

}  // hardware_shruthi
