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
// Main definitions.

#ifndef SHRUTHI_SHRUTHI_H_
#define SHRUTHI_SHRUTHI_H_

#include "avrlib/base.h"

#include <avr/pgmspace.h>

namespace shruthi {

enum KEYS {
  KEY_1,
  KEY_2,
  KEY_3,
  KEY_4,
  KEY_MODE,
  KEY_LOAD_SAVE,
  KEY_NONE,
};

enum LEDS {
  LED_1,
  LED_2,
  LED_3,
  LED_4,
  LED_5,
  LED_6,
  LED_MODE,
  LED_WRITE,
  LED_1_MASK = 1 << LED_1,
  LED_2_MASK = 1 << LED_2,
  LED_3_MASK = 1 << LED_3,
  LED_4_MASK = 1 << LED_4,
  LED_5_MASK = 1 << LED_5,
  LED_6_MASK = 1 << LED_6,
  LED_MODE_MASK = 1 << LED_MODE,
  LED_WRITE_MASK = 1 << LED_WRITE,
};

// Set this flag to 6 to get a nice polysynth (humour).
static const uint8_t kNumVoices = 1;
static const uint8_t kPolyphony = 1;

static const uint8_t kNumEditingPots = 4;
static const uint8_t kNumCvInputs = 4;
static const uint8_t kNumLeds = 8;
static const uint8_t kNumSwitches = 6;

// Rate of the main timer. For now, 1 sample is generated per tick, but we might
// want to do something different to achieve other sample rates
// (20kHz or 16kHz).
static const uint16_t kSampleRate = 20000000L / 510;

// One control signal sample is generated for each 40 audio sample (this gives
// the same resolution as for the Shruti-1: 31250/32 ~= 39062/40)
static const uint8_t kControlRate = 40;

// The latency is 1ms, with a buffer storing 4ms of audio.
static const uint8_t kAudioBlockSize = kControlRate;
static const uint8_t kAudioBufferSize = 128;

// ---- LCD display type -------------------------------------------------------

static const uint8_t kLcdWidth = 16;
static const uint8_t kLcdHeight = 2;

// ---- Scheduler configuration ------------------------------------------------

static const uint8_t kSchedulerNumSlots = 32;

// ---- EEPROM size ------------------------------------------------------------

static const uint16_t kBankSize = 8192;
static const uint16_t kMaxNumBanks = 7;  // Tested for 128kb eeprom

}  // namespace shruthi

#endif // SHRUTHI_SHRUTHI_H_
