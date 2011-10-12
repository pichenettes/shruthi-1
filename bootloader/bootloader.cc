// Copyright 2011 Olivier Gillet.
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
// Bootloader supporting MIDI SysEx update.
//
// Caveat: assumes the firmware flashing is always done from first to last
// block, in increasing order. Random access flashing is not supported!

#include <avr/boot.h>
#include <avr/pgmspace.h>

#include "avrlib/devices/shift_register.h"
#include "avrlib/gpio.h"
#include "avrlib/serial.h"

using namespace avrlib;

ShiftRegisterInput<NumberedGpio<10>, NumberedGpio<7>, NumberedGpio<6>, 8, LSB_FIRST> switches;
ShiftRegisterOutput<NumberedGpio<10>, NumberedGpio<7>, NumberedGpio<5>, 8, MSB_FIRST> status_leds;
Serial<SerialPort0, 31250, POLLED, DISABLED> midi;

uint16_t page = 0;
uint8_t rx_buffer[2 * (SPM_PAGESIZE + 1)];

void (*main_entry_point)(void) = 0x0000;

inline void Init() {
  cli();

  status_leds.Init();
  switches.Init();
}

void WriteBufferToFlash() {
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

static const uint8_t sysex_header_old[] = {
  0xf0,  // <SysEx>
  0x00, 0x20, 0x77,
  0x00, 0x02,  // Product ID for Shruthi-1.
};

static const uint8_t sysex_header[] = {
  0xf0,  // <SysEx>
  0x00, 0x21, 0x02,  // Manufacturer ID for Mutable instruments.
  0x00, 0x02,  // Product ID for Shruthi-1.
};

enum SysExReceptionState {
  MATCHING_HEADER = 0,
  MATCHING_OLD_HEADER = 1,
  READING_COMMAND = 2,
  READING_DATA = 3,
};

inline void MidiLoop() {
  uint8_t byte;
  uint16_t bytes_read = 0;
  uint16_t rx_buffer_index;
  uint8_t state = MATCHING_HEADER;
  uint8_t checksum;
  uint8_t sysex_commands[2];
  uint8_t current_led = 1;
  uint8_t status = 0;
  uint8_t progress_counter = 0;

  midi.Init();
  page = 0;
  status_leds.Write(0x55);
  while (1) {
    byte = midi.Read();
    // In case we see a realtime message in the stream, safely ignore it.
    if (byte > 0xf0 && byte != 0xf7) {
      continue;
    }
    status_leds.Write(status);
    switch (state) {
      case MATCHING_HEADER:
        if (byte == sysex_header[bytes_read]) {
          ++bytes_read;
          if (bytes_read == sizeof(sysex_header)) {
            bytes_read = 0;
            state = READING_COMMAND;
          }
        } else if (byte == sysex_header_old[bytes_read]) {
          ++bytes_read;
          state = MATCHING_OLD_HEADER;
        } else {
          bytes_read = 0;
        }
        break;
        
      case MATCHING_OLD_HEADER:
        if (byte == sysex_header_old[bytes_read]) {
          ++bytes_read;
          if (bytes_read == sizeof(sysex_header_old)) {
            bytes_read = 0;
            state = READING_COMMAND;
          }
        } else {
          bytes_read = 0;
        }
        break;

      case READING_COMMAND:
        if (byte < 0x80) {
          sysex_commands[bytes_read++] = byte;
          if (bytes_read == 2) {
            bytes_read = 0;
            rx_buffer_index = 0;
            checksum = 0;
            state = READING_DATA;
          }
        } else {
          state = MATCHING_HEADER;
          current_led = 1;
          status = 0;
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
            ++progress_counter;
            if (progress_counter == 32) {
              status |= current_led;
              current_led <<= 1;
              if (current_led == 0) {
                current_led = 1;
                status = 0;
              }
              progress_counter = 0;
            }
            status ^= current_led;
          } else {
            current_led = 1;
            status = 0;
          }
          state = MATCHING_HEADER;
          bytes_read = 0;
        }
        break;
    }
  }
}

int main(void) {
  uint8_t watchdog_status = MCUSR;
  MCUSR = 0;
  WDTCSR |= _BV(WDCE) | _BV(WDE);
  WDTCSR = 0;

  Init();
  if ((switches.Read() & 1) == 0) {
    MidiLoop();
  }
  main_entry_point();
  status_leds.Write(0xaa);
}
