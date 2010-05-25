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
// Storage for patches, sequences and system settings.

#include "hardware/shruthi/storage.h"

#include <avr/pgmspace.h>

#include "hardware/hal/serial.h"
#include "hardware/shruthi/display.h"
#include "hardware/shruthi/synthesis_engine.h"
#include "hardware/utils/op.h"

using namespace hardware_hal;
using namespace hardware_utils_op;

namespace hardware_shruthi {

/* static */
uint8_t Storage::load_buffer_[sizeof(Patch)];

/* static */
uint8_t Storage::sysex_rx_buffer_[sizeof(Patch) + 1];

/* static */
uint8_t Storage::undo_buffer_[sizeof(Patch)];

/* static */
uint8_t Storage::sysex_rx_bytes_received_;

/* static */
uint8_t Storage::sysex_rx_checksum_;

/* static */
uint8_t Storage::sysex_rx_state_;

/* static */
uint8_t Storage::sysex_rx_expected_size_;

/* static */
uint8_t Storage::sysex_rx_command_[2];


static const prog_char sysex_rx_header[] PROGMEM = {
  0xf0,  // <SysEx>
  0x00, 0x20, 0x77,  // TODO(pichenettes): register manufacturer ID.
  0x00, 0x02,  // Product ID for Shruthi-1.
  // 0x01: patch transfer, 0x02: sequence transfer, 0x03: big dump
  // 0x00: extra argument byte not used!
};


/* static */
void Storage::SysExDumpBuffer(uint8_t* data, uint8_t code, uint8_t size) {
  Serial<SerialPort1, 31250, DISABLED, POLLED> midi_output;
  // Outputs the SysEx header.
  for (uint8_t i = 0; i < sizeof(sysex_rx_header); ++i) {
    midi_output.Write(pgm_read_byte(sysex_rx_header + i));
  }
  midi_output.Write(code);
  midi_output.Write(0x00);

  uint8_t checksum = 0;
  for (uint8_t i = 0; i < size; ++i) {
    checksum += data[i];
    midi_output.Write(ShiftRight4(data[i]));
    midi_output.Write(data[i] & 0x0f);
  }

  midi_output.Write(ShiftRight4(checksum));
  midi_output.Write(checksum & 0x0f);

  midi_output.Write(0xf7);  // </SysEx>
}

/* static */
void Storage::SysExReceive(uint8_t sysex_rx_byte) {
  if (sysex_rx_byte == 0xf0) {
    sysex_rx_checksum_ = 0;
    sysex_rx_bytes_received_ = 0;
    sysex_rx_state_ = RECEIVING_HEADER;
  }
  switch (sysex_rx_state_) {
    case RECEIVING_HEADER:
      if (pgm_read_byte(sysex_rx_header + sysex_rx_bytes_received_) == \
          sysex_rx_byte) {
        sysex_rx_bytes_received_++;
        if (sysex_rx_bytes_received_ >= sizeof(sysex_rx_header)) {
          sysex_rx_state_ = RECEIVING_COMMAND;
          sysex_rx_bytes_received_ = 0;
        }
      } else {
        sysex_rx_state_ = RECEIVING_FOOTER;
      }
      break;

    case RECEIVING_COMMAND:
      sysex_rx_command_[sysex_rx_bytes_received_++] = sysex_rx_byte;
      if (sysex_rx_bytes_received_ == 2) {
        sysex_rx_expected_size_ = sysex_rx_command_[0] == 0x01
          ? StorageConfiguration<Patch>::size
          : StorageConfiguration<SequencerSettings>::size;
        sysex_rx_state_ = RECEIVING_DATA;
        sysex_rx_bytes_received_ = 0;
      }
      break;

    case RECEIVING_DATA:
      {
        uint8_t i = sysex_rx_bytes_received_ >> 1;
        if (sysex_rx_bytes_received_ & 1) {
          sysex_rx_buffer_[i] |= sysex_rx_byte & 0xf;
          if (i < sysex_rx_expected_size_) {
            sysex_rx_checksum_ += sysex_rx_buffer_[i];
          }
        } else {
          sysex_rx_buffer_[i] = ShiftLeft4(sysex_rx_byte);
        }
        sysex_rx_bytes_received_++;
        if (sysex_rx_bytes_received_ >= (1 + sysex_rx_expected_size_) * 2) {
          sysex_rx_state_ = RECEIVING_FOOTER;
        }
      }
    break;

  case RECEIVING_FOOTER:
    if (sysex_rx_byte == 0xf7 &&
        sysex_rx_checksum_ == sysex_rx_buffer_[sysex_rx_expected_size_]) {
      uint8_t success = 0;
      if (sysex_rx_command_[0] == 0x01) {
        success = AcceptData(engine.mutable_patch(), sysex_rx_buffer_);
      } else {
        success = AcceptData(engine.mutable_sequencer_settings(), sysex_rx_buffer_);
      }
      sysex_rx_state_ = success ? RECEPTION_OK : RECEPTION_ERROR;
    } else {
      sysex_rx_state_ = RECEPTION_ERROR;
    }
    break;
  }
}

}  // hardware_shruthi
