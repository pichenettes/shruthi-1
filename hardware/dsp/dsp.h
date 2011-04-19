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

#ifndef HARDWARE_DSP_DSP_H_
#define HARDWARE_DSP_DSP_H_

#include "hardware/base/base.h"

#include <avr/pgmspace.h>

#define USE_OPTIMIZED_OP

namespace hardware_dsp {

// Rate of the main timer. For now, 1 sample is generated per tick, but we might
// want to do something different to achieve other sample rates
// (20kHz or 16kHz).
static const uint16_t kSampleRate = 39062;

// The latency is 1ms, with a buffer storing 4ms of audio.
static const uint8_t kAudioBlockSize = 32;
static const uint8_t kAudioBufferSize = 64;

static const uint8_t kNumScannedCv = 5;

// ---- Wirings ----------------------------------------------------------------

static const uint8_t kPinDacSlaveSelect = 10;
static const uint8_t kPinLed1 = 2;
static const uint8_t kPinLed2 = 3;

}  // namespace hardware_dsp

#endif  // HARDWARE_DSP_DSP_H_
