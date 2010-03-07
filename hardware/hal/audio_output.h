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
// Audio output. Supports PWM (through a PwmOutput object) and DAC (through a
// Dac object, for example the one defined in mcp492x.h).

#ifndef HARDWARE_HAL_AUDIO_OUTPUT_H_
#define HARDWARE_HAL_AUDIO_OUTPUT_H_

#include "hardware/base/base.h"
#include "hardware/hal/hal.h"
#include "hardware/hal/ring_buffer.h"

namespace hardware_hal {

enum UnderrunPolicy {
  EMIT_CLICK = 0,
  HOLD_SAMPLE = 1
};

template<typename OutputPort,
         uint8_t buffer_size_ = 32,
         uint8_t block_size = 16,
         UnderrunPolicy underrun_policy = HOLD_SAMPLE>
class AudioOutput {
 public:
  AudioOutput() { }
  enum {
    buffer_size = buffer_size_,
    data_size = OutputPort::data_size,
  };
  typedef AudioOutput<OutputPort, buffer_size_, block_size, underrun_policy> Me;
  typedef typename DataTypeForSize<data_size>::Type Value;
  typedef Buffer<Me> OutputBuffer;
  
  static inline void Init() {
    OutputPort::Init();
  }
  
  static inline void Write(Value v) { while (!writable()); Overwrite(v); }
  static inline void Overwrite(Value v) { OutputBuffer::Overwrite(v); }
  
  static inline uint8_t writable() { return OutputBuffer::writable(); }
  static inline uint8_t writable_block() {
    return OutputBuffer::writable() >= block_size;
  }
  static inline uint8_t NonBlockingWrite(Value v) {
    if (!writable()) {
      return 0;
    }
    Overwrite(v);
    return 1;
  }
  
  // Called from data emission interrupt.
  static inline void EmitSample() {
    int16_t v = OutputBuffer::NonBlockingRead();
    if (v >= 0) {
      OutputPort::Write(Value(v));
    } else {
      ++num_glitches_;
      if (underrun_policy == EMIT_CLICK) {
        // Introduces clicks to allow underruns to be easily detected.
        OutputPort::Write(0);
      }
    }
  }
  static uint16_t num_glitches() { return num_glitches_; }

 private:
  static uint16_t num_glitches_;
  
  DISALLOW_COPY_AND_ASSIGN(AudioOutput);
};

/* static */
template<typename OutputPort, uint8_t buffer_size_, uint8_t block_size,
         UnderrunPolicy underrun_policy>
uint16_t AudioOutput<OutputPort, buffer_size_, block_size,
                     underrun_policy>::num_glitches_ = 0;

}  // namespace hardware_hal

#endif  // HARDWARE_HAL_AUDIO_OUTPUT_H_
