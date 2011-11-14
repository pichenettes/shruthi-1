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
// Patch definition. The order of the fields must match the numbering of the
// parameters defined later. Contains methods for packing/unpacking to a
// buffer of bytes (the compression is not optimal, but a more optimal
// compression that would use, for example, the MSB of all parameters in the
// 0-127 range, would result in a high code size).
// Also includes code for checking whether a buffer looks like a reasonable
// patch.

#ifndef OSCLAB_PATCH_H_
#define OSCLAB_PATCH_H_

#include "avrlib/base.h"

namespace osclab {

enum OscillatorAlgorithm {
  WAVEFORM_NONE,
  WAVEFORM_SAW,
  WAVEFORM_SQUARE,
  WAVEFORM_TRIANGLE,
  WAVEFORM_CZ_SAW,
  WAVEFORM_CZ_RESO,
  WAVEFORM_CZ_TRIANGLE,
  WAVEFORM_CZ_PULSE,
  WAVEFORM_CZ_SYNC,
  WAVEFORM_QUAD_SAW_PAD,
  WAVEFORM_FM,
  WAVEFORM_WAVETABLE_1,
  WAVEFORM_WAVETABLE_2,
  WAVEFORM_WAVETABLE_3,
  WAVEFORM_WAVETABLE_4,
  WAVEFORM_WAVETABLE_5,
  WAVEFORM_WAVETABLE_6,
  WAVEFORM_WAVETABLE_7,
  WAVEFORM_WAVETABLE_8,
  WAVEFORM_WAVETABLE_USER,
  WAVEFORM_8BITLAND,
  WAVEFORM_CRUSHED_SINE,
  WAVEFORM_DIRTY_PWM,
  WAVEFORM_FILTERED_NOISE,
  WAVEFORM_VOWEL,
  WAVEFORM_WAVETABLE_9,
  WAVEFORM_WAVETABLE_18 = WAVEFORM_WAVETABLE_9 - 1 + 10,
  WAVEFORM_LAST
};

}  // namespace osclab

#endif // OSCLAB_PATCH_H_
