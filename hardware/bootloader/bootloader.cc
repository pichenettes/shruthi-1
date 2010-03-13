// Copyright 2009 Olivier Gillet.
//
// Adapted by Olivier Gillet (ol.gillet@gmail.com) from the original Arduino
// bootloader contributed by: D. Mellis, D. Cuartielles, Dr. Erik Lins,
// Karl Pitrich, Jason P. Kyle. Some of the makefile settings used here
// are from D. Brink's 1k bootloader.
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
// Bootloader compatible with STK500 and MIDI SysEx, for ATMega644p.
//
// Caveat: assumes the firmware flashing is always done from first to last
// block, in increasing order. Random access flashing is not supported!

#include <avr/boot.h>
#include <avr/pgmspace.h>

#include "hardware/bootloader/shruthi1_status_leds.h"
#include "hardware/hal/devices/shift_register.h"
#include "hardware/hal/gpio.h"
#include "hardware/hal/serial.h"
#include "hardware/shruthi/shruthi.h"

using namespace hardware_hal;
using namespace hardware_shruthi;

Shruthi1StatusIndicator status_leds;
ShiftRegisterInput<Gpio<22>, Gpio<7>, Gpio<6>, 8, LSB_FIRST> switches;

Serial<SerialPort0, 57600, POLLED, POLLED> serial_programmer;
Serial<SerialPort1, 31250, POLLED, DISABLED> midi;

const uint8_t kProgrammerId[] = { 0x14, 'A', 'V', 'R', ' ', 'I', 'S', 'P', 0x10 };
const uint8_t kSignature[] = { 0x14, 0x1e, 0x096, 0x0a, 0x10 };
const uint8_t kVersion[] = { 0x02, 0x01, 0x10 };

const uint8_t kNeverUsedResponseByte = 0xfa;
const uint8_t kMaxErrorCount = 5;


uint16_t page = 0;
uint8_t eeprom;
uint8_t rx_buffer[257];
uint8_t num_failures = 0;

Word address;
Word length;

void (*main_entry_point)(void) = 0x0000;

inline void Init() {
  cli();

  status_leds.Init();
  switches.Init();

  // Enable pull-up resistor on RX pins.
  DigitalInput<8>::EnablePullUpResistor();
  DigitalInput<10>::EnablePullUpResistor();
}

void Write(uint8_t value) {
  serial_programmer.Write(value);
}

uint8_t ReadOrTimeout() {
  uint32_t count = F_CPU >> 5;
  while (!serial_programmer.readable()) {
    if (--count == 0) {
      ++num_failures;
      return 0xff;
    }
  }
  return serial_programmer.ImmediateRead();
}

void SkipInput(uint8_t count) {
  while (count--) {
    ReadOrTimeout();
    if (num_failures > kMaxErrorCount) {
      return;
    }
  }
}

void StkWriteByte(uint8_t value) {
  if (ReadOrTimeout() == ' ') {
    Write(0x14);
    if (value != kNeverUsedResponseByte) {
      Write(value);
    }
    Write(0x10);
  } else {
    ++num_failures;
  }
}

inline void WriteBuffer(const uint8_t* buffer, uint8_t size) {
  while (size--) {
    Write(*buffer++);
  }
}

void WriteBufferToFlash() {
  status_leds.Flash();

  uint16_t i;
  const uint8_t* p = rx_buffer;
  eeprom_busy_wait();

  boot_page_erase(page);
  boot_spm_busy_wait();

  for (i = 0; i < SPM_PAGESIZE; i += 2) {
    uint16_t w = *p++;
    w |= (*p++) << 8;
    boot_page_fill(page + i, w);
  }

  boot_page_write(page);
  boot_spm_busy_wait();
  boot_rww_enable();
}

void ReadRegionSpecs() {
  length.bytes[1] = ReadOrTimeout();
  length.bytes[0] = ReadOrTimeout();
  eeprom = ReadOrTimeout() == 'E' ? 1 : 0;
  if (eeprom) {
    status_leds.SetProgress(1 + (address.value >> 9));
  } else {
    status_leds.SetProgress(1 + (address.value >> 13));
  }
}

static const uint8_t sysex_header[] = {
  0xf0,  // <SysEx>
  0x00, 0x20, 0x77,  // TODO(pichenettes): register manufacturer ID.
  0x00, 0x01,  // Product ID for Shruthi-1.
};

enum SysExReceptionState {
  MATCHING_HEADER = 0,
  READING_COMMAND = 1,
  READING_DATA = 2,
};

inline void MidiLoop() {
  uint8_t byte;
  uint16_t bytes_read = 0;
  uint8_t rx_buffer_index;
  uint8_t state = MATCHING_HEADER;
  uint8_t checksum;
  uint8_t sysex_commands[2];

  midi.Init();
  status_leds.set_reception_mode_mask(0x80);
  status_leds.WaitForData();
  page = 0;
  while (1) {
    byte = midi.Read();
    // In case we see a realtime message in the stream, safely ignore it.
    if (byte > 0xf0 && byte != 0xf7) {
      continue;
    }

    switch (state) {
      case MATCHING_HEADER:
        if (byte == sysex_header[bytes_read]) {
          ++bytes_read;
          if (bytes_read == sizeof(sysex_header)) {
            bytes_read = 0;
            state = READING_COMMAND;
          }
        } else {
          status_leds.ReportError();
          bytes_read = 0;
        }
        break;

      case READING_COMMAND:
        if (byte < 0x80) {
          status_leds.ClearError();
          sysex_commands[bytes_read++] = byte;
          if (bytes_read == 2) {
            bytes_read = 0;
            rx_buffer_index = 0;
            checksum = 0;
            state = READING_DATA;
          }
        } else {
          status_leds.ReportError();
          state = MATCHING_HEADER;
          bytes_read = 0;
        }
        break;

      case READING_DATA:
        if (byte < 0x80) {
          if (bytes_read & 1) {
            rx_buffer[rx_buffer_index] |= byte & 0xf;
            if (rx_buffer_index < SPM_PAGESIZE) {
              checksum += rx_buffer[rx_buffer_index];
            }
            ++rx_buffer_index;
          } else {
            rx_buffer[rx_buffer_index] = (byte << 4);
          }
          ++bytes_read;
        } else if (byte == 0xf7) {
          if (sysex_commands[0] == 0x7f &&
              sysex_commands[1] == 0x00 &&
              bytes_read == 0) {
            // Reset.
            return;
          } else if (rx_buffer_index == SPM_PAGESIZE + 1 &&
                     sysex_commands[0] == 0x7e &&
                     sysex_commands[1] == 0x00 &&
                     rx_buffer[rx_buffer_index - 1] == checksum) {
            // Block write.
            WriteBufferToFlash();
            page += SPM_PAGESIZE;
            status_leds.SetProgress(1 + (page >> 13));
          } else {
            status_leds.ReportError();
          }
          state = MATCHING_HEADER;
          bytes_read = 0;
        }
        break;
    }
  }
}

inline void StkLoop() {
  uint8_t byte;

  serial_programmer.Init();
  status_leds.set_reception_mode_mask(0x40);
  page = 0;
  while (num_failures < kMaxErrorCount) {
    byte = ReadOrTimeout();
    switch (byte) {
      case '0':
        StkWriteByte(kNeverUsedResponseByte);
        break;

      case '1':
        if (ReadOrTimeout() == ' ') {
          WriteBuffer(kProgrammerId, sizeof(kProgrammerId));
        } else {
          ++num_failures;
        }
        break;

      case '@':
        byte = ReadOrTimeout();
        if (byte > 0x85) {
          ReadOrTimeout();
        }
        StkWriteByte(kNeverUsedResponseByte);
        break;

      case 'A':
        byte = ReadOrTimeout();
        if (byte == 0x80) {
          StkWriteByte(kVersion[0]);
        } else if (byte == 0x81) {
          StkWriteByte(kVersion[1]);
        } else if (byte == 0x82) {
          StkWriteByte(kVersion[2]);
        } else if (byte == 0x98) {
          StkWriteByte(0x03);
        } else {
          StkWriteByte(0x00);
        }
        break;

      case 'B':
        SkipInput(20);
        StkWriteByte(kNeverUsedResponseByte);
        break;

      case 'E':
        SkipInput(5);
        StkWriteByte(kNeverUsedResponseByte);
        break;

      case 'P':
      case 'Q':
      case 'R':
        StkWriteByte(kNeverUsedResponseByte);
        break;

      case 'U':
        address.bytes[0] = ReadOrTimeout();
        address.bytes[1] = ReadOrTimeout();
        address.value <<= 1;
        StkWriteByte(kNeverUsedResponseByte);
        break;

      case 'V':
        if (ReadOrTimeout() == 0x30) {
          ReadOrTimeout();
          byte = ReadOrTimeout();
          ReadOrTimeout();
          StkWriteByte(kSignature[byte + 1]);
        } else {
          SkipInput(3);
          StkWriteByte(0x00);
        }
        break;

      case 'd':
        ReadRegionSpecs();
        for (uint16_t i = 0; i < length.value; ++i) {
          rx_buffer[i] = ReadOrTimeout();
        }
        if (ReadOrTimeout() == ' ') {
          if (eeprom) {
            for (uint16_t i = 0; i < length.value; ++i) {
              eeprom_write_byte((uint8_t*)address.value, rx_buffer[i]);
              ++address.value;
            }
          } else {
            // Ignore address...
            WriteBufferToFlash();
            page += SPM_PAGESIZE;
          }
          Write(0x14);
          Write(0x10);
        } else {
          ++num_failures;
        }
        break;

      case 't':
        ReadRegionSpecs();
        if (ReadOrTimeout() == ' ') {
          Write(0x14);
          for (uint16_t i = 0; i < length.value; ++i) {
            if (eeprom) {
              Write(eeprom_read_byte((uint8_t*)address.value));
            } else {
              Write(pgm_read_byte_near(address.value));
            }
            ++address.value;
          }
          Write(0x10);
        } else {
          ++num_failures;
        }
        break;

      case 'u':
        if (ReadOrTimeout() == ' ') {
          WriteBuffer(kSignature, sizeof(kSignature));
        } else {
          ++num_failures;
        }
        break;

      case 'v':
        StkWriteByte(0x00);
        break;

      case 0xff:
        goto fail;
        break;

      default:
        ++num_failures;
    }
    status_leds.WaitForData();
  }
fail:
  status_leds.ReportError();
}

int main(void) {
  // Initialize watchdog timer and check whether we should enter the SysEx
  // loop because of a firmware-initiated reset.
  uint8_t watchdog_status = MCUSR;
  MCUSR = 0;
  WDTCSR |= _BV(WDCE) | _BV(WDE);
  WDTCSR = 0;

  Init();
  if ((watchdog_status & _BV(WDRF)) || (switches.Read() & 1) == 0) {
    MidiLoop();
  } else {
    StkLoop();
  }
  main_entry_point();
  // Believe it or not, there is a weird situation in which the previous
  // instruction is not executed. It seemed to be related to the disabling
  // of the default startup code (--nostartfiles). Even if it uses more space
  // I re-enabled this so as to not trigger the bug.
  status_leds.DebugByte(0x55);
}
