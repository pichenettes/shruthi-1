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

#ifndef OSCLAB_OSCLAB_H_
#define OSCLAB_OSCLAB_H_

#include "avrlib/base.h"

#include <avr/pgmspace.h>

namespace osclab {

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

}  // namespace osclab

#endif // OSCLAB_OSCLAB_H_
