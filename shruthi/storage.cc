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
// Storage for patches, sequences and system settings.

#include "shruthi/storage.h"

#include <avr/pgmspace.h>

#include "avrlib/devices/shift_register.h"
#include "avrlib/serial.h"
#include "shruthi/display.h"
#include "shruthi/editor.h"
#include "shruthi/midi_dispatcher.h"
#include "shruthi/oscillator.h"
#include "shruthi/part.h"
#include "shruthi/ui.h"
#include "avrlib/op.h"

using namespace avrlib;

static const uint8_t kSysExBulkDumpBlockSize = 128;

namespace shruthi {

ExternalEeprom<kMaxNumBanks * kBankSize> external_eeprom;

SpiMaster<IOEnableLine, MSB_FIRST, 4> ProgressBar;

/* static */
uint8_t Storage::load_buffer_[sizeof(Patch)];

/* static */
uint8_t Storage::sysex_rx_buffer_[129];

/* static */
uint8_t* Storage::sysex_rx_destination_;

/* static */
uint8_t Storage::undo_buffer_[128];

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

/* static */
uint8_t Storage::num_accessible_banks_;


static const prog_char sysex_rx_header[] PROGMEM = {
  0xf0,  // <SysEx>
  0x00, 0x21, 0x02,  // Mutable Instruments manufacturer ID.
  0x00, 0x02,  // Product ID for Shruthi-1.
  // Then:
  // * Command byte:
  // - 0x01: patch transfer
  // - 0x02: sequence transfer
  // - 0x03: waveform transfer
  // - 0x11: patch transfer request
  // - 0x12: sequence transfer request
  // - 0x21: patch write request
  // - 0x22: sequence write request
  // - 0x4n: big dump, n-th 16kb of addressable space
  // * Argument byte:
  // Not used for 0x01-0x22, but used for block numbering for 0x4n.
};

static const prog_char sysex_rx_header_old[] PROGMEM = {
  0xf0,  // <SysEx>
  0x00, 0x20, 0x77,
  0x00, 0x02,  // Product ID for Shruthi-1.
};

/* static */
void Storage::WritePatch(uint16_t slot) {
  Write(part.mutable_patch(), slot);
}

/* static */
void Storage::WriteSequence(uint16_t slot) {
  Write(part.mutable_sequencer_settings(), slot);
}

/* static */
void Storage::LoadPatch(uint16_t slot) {
  Load(part.mutable_patch(), slot);
}

/* static */
void Storage::LoadSequence(uint16_t slot) {
  Load(part.mutable_sequencer_settings(), slot);
}

/* static */
void Storage::SysExDumpBuffer(
    uint8_t* data,
    uint8_t command,
    uint8_t argument,
    uint8_t size) {
  Serial<MidiPort, 31250, DISABLED, POLLED> midi_output;
  midi_dispatcher.Flush();
  // Outputs the SysEx header.
  for (uint8_t i = 0; i < sizeof(sysex_rx_header); ++i) {
    midi_output.Write(pgm_read_byte(sysex_rx_header + i));
  }
  midi_output.Write(command);
  midi_output.Write(argument);

  uint8_t checksum = 0;
  for (uint8_t i = 0; i < size; ++i) {
    checksum += data[i];
    midi_output.Write(U8ShiftRight4(data[i]));
    midi_output.Write(data[i] & 0x0f);
  }

  midi_output.Write(U8ShiftRight4(checksum));
  midi_output.Write(checksum & 0x0f);

  midi_output.Write(0xf7);  // </SysEx>
}

/* static */
void Storage::SysExBulkDump() {
  uint8_t message_id = 0x40;
  uint8_t block_id = 0;
  uint16_t delay;

  ui.BeginProgressBar();
  for (uint16_t start = 0;
       start < addressable_space_size();
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
        message_id,
        block_id++,
        kSysExBulkDumpBlockSize);
    if (block_id == 128) {
      block_id = 0;
      ++message_id;
    }
    ui.StepProgressBar();
    Delay(delay);
  }
  ui.EndProgressBar();
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

    case 0x04:  // System settings transfer
      sysex_rx_expected_size_ = sizeof(SystemSettings);
      break;

    case 0x05:  // Step sequencer transfer
      sysex_rx_expected_size_ = 2;
      break;

    case 0x06:  // Patch name transfer
      sysex_rx_expected_size_ = kPatchNameSize;
      break;

    case 0x07:  // Full sequencer state transfer
      sysex_rx_expected_size_ = sizeof(SequencerSettings);
      break;

    case 0x11:  // Patch request
    case 0x12:  // Sequence request
    case 0x14:  // System settings request
    case 0x15:  // Sequence step request
    case 0x16:  // Patch name request
    case 0x17:  // Full sequencer state request
    case 0x1a:  // Current patch and sequence numbers request
    case 0x1b:  // Num banks request
    case 0x1c:  // Version request
      sysex_rx_expected_size_ = 0;
      break;

    case 0x21:  // Patch write request
    case 0x22:  // Sequence write request
      sysex_rx_expected_size_ = 2;
      break;

    case 0x31:  // Patch randomize
    case 0x32:  // Sequence randomize
      sysex_rx_expected_size_ = 0;
      break;

    case 0x40:  // Bulk transfer
    case 0x41:
    case 0x42:
    case 0x43:
      sysex_rx_expected_size_ = kSysExBulkDumpBlockSize;
      break;

    case 0x50:  // Bulk transfer requests
      sysex_rx_expected_size_ = 0;
      break;

    default:
      sysex_rx_state_ = RECEIVING_FOOTER;
      break;
  }
}

/* static */
void Storage::SysExAcceptBuffer() {
  uint8_t success = 0;

  // Add a delay for Request commands
  if ((sysex_rx_command_[0] & 0xf0) == 0x10 ||
      (sysex_rx_command_[0] & 0xf0) == 0x50) {
    Delay(100);
    success = 1;
  }

  switch (sysex_rx_command_[0]) {
    case 0x01:  // Patch transfer
      success = AcceptData(part.mutable_patch(), sysex_rx_buffer_);
      break;

    case 0x02:  // Sequence transfer
      success = AcceptData(
          part.mutable_sequencer_settings(),
          sysex_rx_buffer_);
      break;

    case 0x03:
      success = 1;
      break;

    case 0x04:
      memcpy(
          (uint8_t*) part.mutable_system_settings(),
          sysex_rx_buffer_,
          sizeof(SystemSettings));
      part.mutable_system_settings()->EepromSave();
      success = 1;
      break;

    case 0x05:
      {
        uint8_t step_index = sysex_rx_command_[1] & 0x0f;
        part.SetSequenceStep(
            step_index,
            sysex_rx_buffer_[0],
            sysex_rx_buffer_[1]);
      }
      break;

    case 0x06:
      part.SetName(sysex_rx_buffer_);
      break;

    case 0x07:
      memcpy(
          (uint8_t*) part.mutable_sequencer_settings(),
          sysex_rx_buffer_,
         sizeof(SequencerSettings));
      part.mutable_sequencer_settings()->Update();
      success = 1;
      break;

    case 0x11:
      Storage::SysExDump(part.mutable_patch());
      break;

    case 0x12:
      Storage::SysExDump(part.mutable_sequencer_settings());
      break;

    case 0x14:
      Storage::SysExDumpBuffer(
          (uint8_t*) part.mutable_system_settings(),
          0x04,
          0,
          sizeof(SystemSettings));
      break;

    case 0x15:
      {
        uint8_t step_index = sysex_rx_command_[1] & 0x0f;
        Storage::SysExDumpBuffer(
            part.mutable_sequencer_settings()-> \
            steps[step_index].data_,
            0x05,
            step_index,
            2);
      }
      break;

    case 0x16:
      Storage::SysExDumpBuffer(
          (uint8_t*) part.mutable_patch()->name,
          0x06,
          0,
          kPatchNameSize);
      break;

    case 0x17:
      Storage::SysExDumpBuffer(
          (uint8_t*) part.mutable_sequencer_settings(),
          0x07,
          0,
          sizeof(SequencerSettings));
      break;

    case 0x1a:
      {
        uint16_t current_indices[2];
        current_indices[0] = editor.current_patch_number();
        current_indices[1] = editor.current_patch_number();
        Storage::SysExDumpBuffer(
            (uint8_t*)&current_indices, 0x0a,
            0,
            sizeof(current_indices));
      }
      break;

    case 0x1b:
      Storage::SysExDumpBuffer(
          (uint8_t*) NULL,
          0x0b,
          num_accessible_banks(),
          0);
      break;

    case 0x1c:
      {
        uint8_t version[2];
        version[0] = pgm_read_byte(waveform_table[WAV_RES_VERSION]);
        version[1] = pgm_read_byte(waveform_table[WAV_RES_VERSION] + 1);
        Storage::SysExDumpBuffer(version, 0x0c, 0, 2);
      }
      break;

    case 0x21:
      WritePatch((sysex_rx_buffer_[0] << 8) | (sysex_rx_buffer_[1]));
      success = 1;
      break;

    case 0x22:
      WriteSequence((sysex_rx_buffer_[0] << 8) | (sysex_rx_buffer_[1]));
      success = 1;
      break;

    case 0x31:
      editor.RandomizePatch();
      success = 1;
      break;

    case 0x32:
      editor.RandomizeSequence();
      success = 1;
      break;

    case 0x40:  // Raw data dump
    case 0x41:
    case 0x42:
    case 0x43:
      {
        uint16_t address = sysex_rx_command_[1] * kSysExBulkDumpBlockSize;
        while (sysex_rx_command_[0] > 0x40) {
          address += kSysExBulkDumpBlockSize * 128;
          --sysex_rx_command_[0];
        }
        success = address < addressable_space_size();
        if (!success) {
          break;
        }
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

    case 0x50:
      SysExBulkDump();
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
      } else if (pgm_read_byte(sysex_rx_header_old + sysex_rx_bytes_received_) == \
            sysex_rx_byte) {
        sysex_rx_bytes_received_++;
        sysex_rx_state_ = RECEIVING_OLD_HEADER;
      } else {
        sysex_rx_state_ = RECEIVING_FOOTER;
      }
      break;

    case RECEIVING_OLD_HEADER:
      if (pgm_read_byte(sysex_rx_header_old + sysex_rx_bytes_received_) == \
          sysex_rx_byte) {
        sysex_rx_bytes_received_++;
        if (sysex_rx_bytes_received_ >= sizeof(sysex_rx_header_old)) {
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
          sysex_rx_destination_[i] = U8ShiftLeft4(sysex_rx_byte);
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
  uint16_t written = external_eeprom.Write(address, data, size);
}

/* static */
void Storage::ReadExternal(
    uint8_t* data,
    uint16_t address,
    uint8_t size) {
  external_eeprom.Read(address, size, data);
}

/* static */
void Storage::Init() {
  uint16_t data;
  external_eeprom.Init();
  uint16_t address = kMaxNumBanks * kBankSize - 2;
  // Write the sequence 0xfadN at the end of each bank, where N is the
  // bank number.
  for (uint8_t i = kMaxNumBanks; i > 0; --i) {
    data = 0xfad0 + i;
    WriteExternal((uint8_t*)&data, address, 2);
    address -= kBankSize;
  }
  // Try to read back this data to figure out the actual number of banks.
  address = kMaxNumBanks * kBankSize - 2;
  num_accessible_banks_ = kMaxNumBanks;
  while (num_accessible_banks_ > 0) {
    ReadExternal((uint8_t*)&data, address, 2);
    if (data == 0xfad0 + num_accessible_banks_) {
      break;
    }
    --num_accessible_banks_;
    address -= kBankSize;
  }
}

}  // shruthi
