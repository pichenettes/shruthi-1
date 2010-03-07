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
// Important: All buffer sizes are expected to be less than 256! (fit in 8
// bits), and must be powers of 2.

#ifndef HARDWARE_HAL_RING_BUFFER_H_
#define HARDWARE_HAL_RING_BUFFER_H_

#include "hardware/base/base.h"
#include "hardware/hal/hal.h"

namespace hardware_hal {

// Circular buffer, used for example for Serial input, Software serial output,
// Audio rendering... A buffer is created for each Owner - for example,
// Buffer<AudioClient> represents the audio buffer used by AudioClient.
template<typename Owner>
class Buffer : public Input, Output {
 public:
  typedef typename Owner::Value Value;
  enum {
    size = Owner::buffer_size,
    data_size = Owner::data_size
  };
  static inline uint8_t capacity() { return size; }
  static inline void Write(Value v) {
    while (!writable());
    Overwrite(v);
  }
  static inline uint8_t writable() {
    return (read_ptr_ - write_ptr_ - 1) & (size - 1);
  }
  static inline uint8_t NonBlockingWrite(Value v) {
    if (writable()) {
      Overwrite(v);
      return 1;
    } else {
      return 0;
    }
  }
  static inline void Overwrite(Value v) {
    buffer_[write_ptr_] = v;
    write_ptr_ = (write_ptr_ + 1) & (size - 1);
  }
  static inline uint8_t Requested() { return 0; }
  static inline Value Read() {
    while (!readable());
    return ImmediateRead();
  }
  static inline uint8_t readable() {
    return (write_ptr_ - read_ptr_) & (size - 1);
  }
  static inline int16_t NonBlockingRead() {
    if (readable()) {
      return ImmediateRead();
    } else {
      return -1;
    }
  }
  static inline Value ImmediateRead() {
    Value result = buffer_[read_ptr_];
    read_ptr_ = (read_ptr_ + 1) & (size - 1);
    return result;
  }
  static inline void Flush() {
    write_ptr_ = read_ptr_;
  }
 private:
  static Value buffer_[size];
  static volatile uint8_t read_ptr_;
  static volatile uint8_t write_ptr_;

  DISALLOW_COPY_AND_ASSIGN(Buffer);
};

// Static variables created for each buffer.
template<typename T> volatile uint8_t Buffer<T>::read_ptr_ = 0;
template<typename T> volatile uint8_t Buffer<T>::write_ptr_ = 0;
template<typename T> typename T::Value Buffer<T>::buffer_[];

}  // namespace hardware_hal

#endif   // HARDWARE_HAL_RING_BUFFER_H_
