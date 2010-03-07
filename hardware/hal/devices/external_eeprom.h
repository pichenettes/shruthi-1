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
// Driver for Atmel I2C eeproms (AT24C64 for example).
//
// Supports an "auto-banking" mode in which the address space is split into
// multiple chips. For example, if four 16k chips (AT24C128) are connected on the
// bus, R/W to addresses 0x0000 - 0x4000 will be addressed to chip 1, 
// R/W to addresses 0x4000 - 0x8000 will be addressed to chip 2, etc.

#ifndef HARDWARE_HAL_DEVICES_EXTERNAL_EEPROM_H_
#define HARDWARE_HAL_DEVICES_EXTERNAL_EEPROM_H_

#include "hardware/hal/i2c/i2c.h"

namespace hardware_hal {

template<uint16_t eeprom_size = 8192 /* bytes */,
        typename Bus = I2cMaster<8, 64>,
        uint8_t base_address = 0,
        bool auto_banking = true>
class ExternalEeprom {
 public:
  ExternalEeprom() { }
  
  static void Init() {
    Bus::Init();
  }
  
  static void set_bank(uint8_t bank) {
    bank_ = bank;
  }

  static uint8_t Read(uint8_t size, uint8_t* data) {
    uint8_t remaining = size;
    while (1) {
      // Try to read as much as possible from the buffer from the previous op.
      while (Bus::readable() && remaining) {
        --remaining;
        *data++ = Bus::ImmediateRead();
      }
      if (remaining == 0) {
        break;
      }
      // We need to request more data!
      Bus::Wait();
      uint8_t requested = Bus::Request((base_address + bank_) | 0x50, remaining);
      if (Bus::Wait() != I2C_ERROR_NONE) {
        return size - remaining;
      }
    }
    return size;
  }
  
  static uint8_t SetAddress(uint16_t address) {
    uint8_t header[2];
    if (auto_banking) {
      bank_ = (address / eeprom_size);
      address %= eeprom_size;
    }
    header[0] = address >> 8;
    header[1] = address & 0xff;
    if (Write(header, 2, NULL, 0) == 2) {
      // Invalidate pending read operations.
      Bus::FlushInputBuffer(); 
      return 1;
    } else {
      return 0;
    }
  }
  
  static uint8_t Write(uint16_t address, const uint8_t* data, uint8_t size) {
    uint8_t header[2];
    if (auto_banking) {
      bank_ = (address / eeprom_size);
      address %= eeprom_size;
    }
    header[0] = address >> 8;
    header[1] = address & 0xff;
    if (Write(header, 2, data, size) == size + 2) {
      return size;
    } else {
      return 0;
    }
  }
  
  static uint8_t Read() {
    uint8_t data;
    if (Read(1, &data) == 1) {
      return data;
    } else {
      return 0xff;
    }
  }
  
  static uint8_t Read(uint16_t address) {
    if (!SetAddress(address)) {
      return 0xff;
    }
    return Read();
  }
  
  static uint8_t Read(uint16_t address, uint8_t size, uint8_t* data) {
    if (!SetAddress(address)) {
      return 0;
    } else {
      return Read(size, data);
    }
  }

  static uint8_t Write(uint16_t address, uint8_t byte) {
    uint8_t data = byte;
    return Write(&data, 1);
  }
   
 private:
  static uint8_t Write(const uint8_t* header, uint8_t header_size, 
                       const uint8_t* payload, uint8_t payload_size) {
    uint8_t size = header_size + payload_size;
    if (size >= Bus::Output::capacity()) {
      return 0;  // Hopeless, it won't fit in one write.
    }
    // Wait until the buffer is flushed, and write to the buffer.
    while (Bus::writable() < size) { }
    for (uint8_t i = 0; i < header_size; ++i) {
      Bus::Output::Overwrite(header[i]);
    }
    for (uint8_t i = 0; i < payload_size; ++i) {
      Bus::Overwrite(payload[i]);
    }
    // Wait until the line is available.
    Bus::Wait();
    // Send the data in the buffer.
    if (Bus::Send((base_address + bank_) | 0x50)) {
      uint8_t error = Bus::Wait();
      if (error == I2C_ERROR_NONE) {
        return size;
      } else {
        return 0;
      }
    } else {
      return 0;
    }
  }
  
  static uint8_t bank_;
  
  DISALLOW_COPY_AND_ASSIGN(ExternalEeprom);
};

/* static */
template<uint16_t eeprom_size, typename Bus, uint8_t base_address,
         bool auto_banking>
uint8_t ExternalEeprom<eeprom_size, Bus, base_address, auto_banking>::bank_ = 0;

}  // namespace hardware_hal

#endif   // HARDWARE_HAL_DEVICES_EXTERNAL_EEPROM_H_
