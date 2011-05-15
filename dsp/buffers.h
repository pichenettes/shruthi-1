// Copyright 2011 Olivier Gillet.
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
// Instance of the audio out class, configured for the Shruthi-1 DSP project.

#ifndef DSP_BUFFERS_H_
#define DSP_BUFFERS_H_

#include "avrlib/base.h"
#include "avrlib/ring_buffer.h"
#include "dsp/dsp.h"

namespace dsp {

using namespace avrlib;

struct OutputBufferSpecs {
  typedef uint16_t Value;
  enum {
    buffer_size = kAudioBufferSize,
    data_size = 16,
  };
};
extern RingBuffer<OutputBufferSpecs> output_buffer;

struct InputBufferSpecs {
  typedef uint8_t Value;
  enum {
    buffer_size = kAudioBufferSize,
    data_size = 8,
  };
};
extern RingBuffer<InputBufferSpecs> input_buffer;

}  // namespace dsp

#endif // DSP_BUFFERS_H_
