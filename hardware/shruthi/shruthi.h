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

#ifndef HARDWARE_SHRUTHI_SHRUTHI_H_
#define HARDWARE_SHRUTHI_SHRUTHI_H_

#include "hardware/base/base.h"

// The easter egg is a bit lame and takes space which could be used for
// more essential experimental features.
#define HAS_EASTER_EGG
#define USE_OPTIMIZED_OP

namespace hardware_shruthi {

enum LEDS {
  LED_OSC_1,
  LED_OSC_2,
  LED_FILTER,
  LED_MOD_1,
  LED_MOD_2,
  LED_PLAY,
  LED_SYS,
  LED_WRITE,
  LED_OSC_1_MASK = 1 << LED_OSC_1,
  LED_OSC_2_MASK = 1 << LED_OSC_2,
  LED_FILTER_MASK = 1 << LED_FILTER,
  LED_MOD_1_MASK = 1 << LED_MOD_1,
  LED_MOD_2_MASK = 1 << LED_MOD_2,
  LED_PLAY_MASK = 1 << LED_PLAY,
  LED_SYS_MASK = 1 << LED_SYS,
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
static const uint16_t kMainTimerRate = 39062;
static const uint16_t kSampleRate = 39062;

// One control signal sample is generated for each 32 audio sample.
static const uint8_t kControlRate = 32;

// The latency is 1ms, with a buffer storing 4ms of audio.
static const uint8_t kAudioBlockSize = kControlRate;
static const uint8_t kAudioBufferSize = kAudioBlockSize * 4;

// ---- Wirings ----------------------------------------------------------------

// Encoder
static const uint8_t kPinEncoderA = 0;
static const uint8_t kPinEncoderB = 1;
static const uint8_t kPinEncoderClick = 2;

// Shift registers / muxes.
static const uint8_t kPinData = 23;
static const uint8_t kPinDigitalInput = 6;
static const uint8_t kPinLatch = 22;
static const uint8_t kPinClk = 7;

// RS and Enable lines for LCD display
static const uint8_t kPinLcdRs = 20;
static const uint8_t kPinLcdEnable = 21;

// PWM/audio output.
static const uint8_t kPinVcoOut = 12;
static const uint8_t kPinVcaOut = 13;
static const uint8_t kPinVcfCutoffOut = 14;
static const uint8_t kPinVcfResonanceOut = 15;
static const uint8_t kPinCv1Out = 3;
static const uint8_t kPinCv2Out = 4;

static const uint8_t kPinAnalogInput = 0;
static const uint8_t kPinCvInput = 4;

// ---- LCD display type -------------------------------------------------------

static const uint8_t kLcdWidth = 16;
static const uint8_t kLcdHeight = 2;

// ---- Scheduler configuration ------------------------------------------------

static const uint8_t kSchedulerNumSlots = 32;

}  // namespace hardware_shruthi

#endif  // HARDWARE_SHRUTHI_SHRUTHI_H_
