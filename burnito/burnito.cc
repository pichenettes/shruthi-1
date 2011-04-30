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

#include "avrlib/devices/buffered_display.h"
#include "avrlib/devices/external_eeprom.h"
#include "avrlib/devices/hd44780_lcd.h"
#include "avrlib/devices/shift_register.h"
#include "avrlib/gpio.h"
#include "avrlib/boot.h"
#include "avrlib/parallel_io.h"
#include "avrlib/time.h"
#include "avrlib/string.h"

#include "burnito/resources.h"

using namespace avrlib;
using namespace avrlib;

static const uint16_t kBankSize = 8192;
static const uint16_t kMaxNumBanks = 7;
static const uint8_t kBlockSize = 64;

typedef Hd44780Lcd<
    Gpio<PortC, 2>,
    Gpio<PortC, 3>,
    ParallelPort<PortC, PARALLEL_NIBBLE_HIGH> > Lcd;

ShiftRegisterOutput<
    Gpio<PortD, 2>,
    Gpio<PortB, 7>,
    Gpio<PortB, 5>, 8, MSB_FIRST> status_leds;

Lcd lcd;
BufferedDisplay<Lcd> display;
ExternalEeprom<kMaxNumBanks * kBankSize> external_eeprom;


static uint8_t cpt;
TIMER_2_TICK {
  cpt = (cpt + 1) & 0x0f;
  if (cpt == 0) {
    lcd.Tick();
  }
}

TIMER_0_TICK {
  TickSystemClock();
}

static uint8_t num_banks;

static const uint16_t kTotalSize = BLOB_RES_EEPROM_CONTENT_SIZE + \
    BLOB_RES_EEPROM_CONTENT_TAIL_SIZE;

void DetectEepromSize() {
  external_eeprom.Init();
  uint16_t address = kMaxNumBanks * kBankSize - 2;
  uint16_t data;
  // Write the sequence 0xfadN at the end of each bank, where N is the
  // bank number.
  for (uint8_t i = kMaxNumBanks; i > 0; --i) {
    data = 0xfad0 + i;
    external_eeprom.Write(address, (uint8_t*)&data, 2);
    address -= kBankSize;
  }
  // Try to read back this data to figure out the actual number of banks.
  address = kMaxNumBanks * kBankSize - 2;
  num_banks = kMaxNumBanks;
  while (num_banks > 0) {
    external_eeprom.Read(address, 2, (uint8_t*)&data);
    if (data == 0xfad0 + num_banks) {
      break;
    }
    --num_banks;
    address -= kBankSize;
  }
  
  char line_buffer[16];
  line_buffer[0] = '\0';
  strcpy(line_buffer, "Size: ");
  UnsafeItoa(num_banks * (kBankSize / 1024 * 8), 5, line_buffer + 6);
  strcat(line_buffer, "kb");
  display.Print(0, line_buffer);
}

uint8_t buffer[kBlockSize];
uint8_t buffer2[kBlockSize];

uint8_t Copy() {
  display.Print(1, "Copying...      ");
  
  uint16_t address = 0;
  uint8_t progress = 0;
  for (uint8_t i = 0; i < num_banks; ++i) {
    for (uint16_t j = 0; j < kBankSize; j += kBlockSize) {
      display.Tick();
      memcpy_P(
          buffer,
          burnito::blob_res_eeprom_content + address,
          kBlockSize);
      if (external_eeprom.Write(address, buffer, kBlockSize) != kBlockSize) {
        return 0;
      }
      address += kBlockSize;
      status_leds.Write((1 << (progress + 1)) - 1);
      progress = (progress + 1) & 7;
      if (address == kTotalSize) {
        break;
      }
    }
  }
  return 1;
}

uint8_t Verify() {
  display.Print(1, "Verifying...    ");
  
  uint16_t address = 0;
  uint8_t progress = 0;
  for (uint8_t i = 0; i < num_banks; ++i) {
    for (uint16_t j = 0; j < kBankSize; j += kBlockSize) {
      display.Tick();
      memcpy_P(
          buffer,
          burnito::blob_res_eeprom_content + address,
          kBlockSize);
      if (external_eeprom.Read(address, kBlockSize, buffer2) != kBlockSize) {
        return 0;
      }
      if (memcmp(buffer2, buffer, kBlockSize)) {
        return 0;
      }
      address += kBlockSize;
      status_leds.Write((1 << (progress + 1)) - 1);
      progress = (progress + 1) & 7;
      if (address == kTotalSize) {
        break;
      }
    }
  }
  return 1;
}

int main(void) {
  Boot(true);
  lcd.Init();
  status_leds.Init();
  Timer<2>::set_prescaler(1);
  Timer<2>::set_mode(TIMER_PWM_PHASE_CORRECT);
  Timer<2>::Start();
  display.Init();
  DetectEepromSize();
  if (!Copy()) {
    display.Print(1, "Copy error!     ");
    status_leds.Write(0x55);
  } else {
    if (!Verify()) {
      display.Print(1, "Read error!     ");
      status_leds.Write(0x55);
    } else {
      display.Print(1, "EEPROM ok!      ");
      status_leds.Write(0xff);
    }
  }
  while (1) {
    display.Tick();
    Delay(1);
  }
}
