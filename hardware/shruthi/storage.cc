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
#include "hardware/hal/devices/external_eeprom.h"
#include "hardware/hal/devices/shift_register.h"
#include "hardware/shruthi/display.h"
#include "hardware/shruthi/oscillator.h"
#include "hardware/shruthi/synthesis_engine.h"
#include "hardware/utils/op.h"

using namespace hardware_hal;
using namespace hardware_utils_op;

static const uint8_t kSysExBulkDumpBlockSize = 128;

namespace hardware_shruthi {
  
// We directly address the facade LEDs to show a progress bar of the data
// dump.
typedef ShiftRegisterOutput<
    Gpio<kPinLatch>,
    Gpio<kPinClk>,
    Gpio<kPinData>,
    kNumLeds,
    MSB_FIRST> ProgressBar;

/* static */
uint8_t Storage::load_buffer_[sizeof(Patch)];

/* static */
uint8_t Storage::sysex_rx_buffer_[129];

/* static */
uint8_t* Storage::sysex_rx_destination_;

/* static */
uint8_t Storage::undo_buffer_[sizeof(Patch)];

/* static */
uint16_t Storage::sysex_rx_bytes_received_;

/* static */
uint8_t Storage::sysex_rx_checksum_;

/* static */
uint8_t Storage::sysex_rx_state_;

/* static */
uint16_t Storage::sysex_rx_expected_size_;

/* static */
uint8_t Storage::sysex_rx_command_[2];


static const prog_char sysex_rx_header[] PROGMEM = {
  0xf0,  // <SysEx>
  0x00, 0x20, 0x77,  // TODO(pichenettes): register manufacturer ID.
  0x00, 0x02,  // Product ID for Shruthi-1.
  // Then:
  // * Command byte:
  // - 0x01: patch transfer
  // - 0x02: sequence transfer
  // - 0x03: waveform transfer
  // - 0x40: big dump
  // * Argument byte:
  // Not used for 0x01-0x03, but used for block numbering for 0x40.
};


/* static */
void Storage::SysExDumpBuffer(
    uint8_t* data,
    uint8_t command,
    uint8_t argument,
    uint8_t size) {
  Serial<MidiPort, 31250, DISABLED, POLLED> midi_output;
  // Outputs the SysEx header.
  for (uint8_t i = 0; i < sizeof(sysex_rx_header); ++i) {
    midi_output.Write(pgm_read_byte(sysex_rx_header + i));
  }
  midi_output.Write(command);
  midi_output.Write(argument);

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
void Storage::SysExBulkDump() {
  // Check at compile-time that the sizes won't cause overflows.
  STATIC_ASSERT((kInternalEepromSize + kDefaultExternalEepromSize) % \
      kSysExBulkDumpBlockSize == 0);
  STATIC_ASSERT((kInternalEepromSize + kDefaultExternalEepromSize) / \
      kSysExBulkDumpBlockSize < 128);
    
  uint8_t block_id = 0;
  uint8_t progress_leds = 1;
  uint16_t delay;
  for (uint16_t start = 0;
       start < kInternalEepromSize + kDefaultExternalEepromSize;
       start += kSysExBulkDumpBlockSize) {
    if (start < kInternalEepromSize) {
      eeprom_read_block(
          sysex_rx_buffer_,
          (void*)(start),
          kSysExBulkDumpBlockSize);
      delay = 500;
    } else {
      ReadExternal(
          sysex_rx_buffer_,
          start - kInternalEepromSize,
          kSysExBulkDumpBlockSize);
      delay = 100;
    }
    SysExDumpBuffer(
        sysex_rx_buffer_,
        0x40,
        block_id++,
        kSysExBulkDumpBlockSize);
    ProgressBar::Write(progress_leds);
    progress_leds = progress_leds == 255 ? 1 : (progress_leds << 1) + 1;
    Delay(delay);
  }
}

/* static */
void Storage::SysExParseCommand() {
  sysex_rx_bytes_received_ = 0;
  sysex_rx_state_ = RECEIVING_DATA;
  sysex_rx_destination_ = sysex_rx_buffer_;
  switch (sysex_rx_command_[0]) {
    case 0x01:  // Patch transfer
      sysex_rx_expected_size_ = StorageConfiguration<Patch>::size;
      break;
    
    case 0x02:  // Sequence transfer
      sysex_rx_expected_size_ = \
          StorageConfiguration<SequencerSettings>::size;
      break;
      
    case 0x03:  // Wavetable dump
      sysex_rx_destination_ = user_wavetable;
      sysex_rx_expected_size_ = kUserWavetableSize;
      break;
        
    case 0x40:  // Raw data dump
      sysex_rx_expected_size_ = kSysExBulkDumpBlockSize;
      break;
    
    default:
      sysex_rx_state_ = RECEIVING_FOOTER;
      break;
  }
}

/* static */
void Storage::SysExAcceptBuffer() {
  uint8_t success = 0;
  switch (sysex_rx_command_[0]) {
    case 0x01:  // Patch transfer
      success = AcceptData(engine.mutable_patch(), sysex_rx_buffer_);
      break;
      
    case 0x02:  // Sequence transfer
      success = AcceptData(engine.mutable_sequencer_settings(),
                           sysex_rx_buffer_);
      break;
    
    case 0x03:
      success = 1;
      break;
    
    case 0x40:  // Raw data dump
      {
        ProgressBar::Write((1 << (sysex_rx_command_[1] & 7)) * 2 - 1);
        uint16_t address = sysex_rx_command_[1] * kSysExBulkDumpBlockSize;
        success = address < (kInternalEepromSize + kDefaultExternalEepromSize);
        if (address < kInternalEepromSize) {
          eeprom_write_block(
              sysex_rx_buffer_,
              (void*)(address),
              kSysExBulkDumpBlockSize);
        } else {
          address -= kInternalEepromSize;
          WriteExternal(
              sysex_rx_buffer_,
              address,
              kSysExBulkDumpBlockSize);
        }
      }
      break;
  }
  sysex_rx_state_ = success ? RECEPTION_OK : RECEPTION_ERROR;
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
        SysExParseCommand();
      }
      break;

    case RECEIVING_DATA:
      {
        uint16_t i = sysex_rx_bytes_received_ >> 1;
        if (sysex_rx_bytes_received_ & 1) {
          sysex_rx_destination_[i] |= sysex_rx_byte & 0xf;
          if (i < sysex_rx_expected_size_) {
            sysex_rx_checksum_ += sysex_rx_destination_[i];
          }
        } else {
          sysex_rx_destination_[i] = ShiftLeft4(sysex_rx_byte);
        }
        sysex_rx_bytes_received_++;
        if (sysex_rx_bytes_received_ >= (1 + sysex_rx_expected_size_) * 2) {
          sysex_rx_state_ = RECEIVING_FOOTER;
        }
      }
    break;

  case RECEIVING_FOOTER:
    if (sysex_rx_byte == 0xf7 &&
        sysex_rx_checksum_ == sysex_rx_destination_[sysex_rx_expected_size_]) {
      SysExAcceptBuffer();
    } else {
      sysex_rx_state_ = RECEPTION_ERROR;
    }
    break;
  }
}

/* static */
void Storage::WriteExternal(
    const uint8_t* data,
    uint16_t address,
    uint8_t size) {
  ExternalEeprom<> e;
#ifdef HARDWARE_REV_02
  lcd.DisableRefresh();
  e.Init();
#endif
  uint16_t written = e.Write(address, data, size);
#ifdef HARDWARE_REV_02
  e.Done();
  lcd.EnableRefresh();
#endif
}

/* static */
void Storage::ReadExternal(
    uint8_t* data,
    uint16_t address,
    uint8_t size) {
  ExternalEeprom<> e;
#ifdef HARDWARE_REV_02
  lcd.DisableRefresh();
  e.Init();
#endif
  e.Read(address, size, data);
#ifdef HARDWARE_REV_02
  e.Done();
#endif
  lcd.EnableRefresh();  
}

}  // hardware_shruthi
