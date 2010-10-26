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
//
// -----------------------------------------------------------------------------
//
// Driver for an external rotary encoder.

#ifndef HARDWARE_HAL_DEVICES_ROTARY_ENCODER_H_
#define HARDWARE_HAL_DEVICES_ROTARY_ENCODER_H_

#include "hardware/hal/devices/debounce.h"
#include "hardware/hal/gpio.h"
#include "hardware/hal/time.h"

namespace hardware_hal {

template<typename A, typename B, typename Click, uint16_t debounce_time = 1>
class RotaryEncoder {
 public:
  typedef DebouncedSwitch<A> SwitchA;
  typedef DebouncedSwitch<B> SwitchB;
  typedef DebouncedSwitch<Click> SwitchClick;
 
  RotaryEncoder() { }

  static void Init() {
    SwitchA::Init();
    SwitchB::Init();
    SwitchClick::Init();
    next_readout_ = 0;
  }

  static inline int8_t TimedRead() {
    uint32_t t = milliseconds();
    int8_t increment = 0;
    if (t >= next_readout_) {
      next_readout_ = t + debounce_time;
      increment = Read();
    }
    return increment;
  }

  static inline int8_t Read() {
    int8_t increment = 0;
    SwitchA::Read();
    SwitchB::Read();
    SwitchClick::Read();
    if (SwitchA::lowered()) {
      if ((SwitchB::state() & 0xf0) == 0x00) {
        increment = 1;
      }
    }
    if (SwitchB::lowered()) {
      if ((SwitchA::state() & 0xf0) == 0x00) {
        increment = -1;
      }
    }
    return increment;
  }

  static uint8_t clicked() { return SwitchClick::raised(); }

 private:
  static uint32_t next_readout_;

  DISALLOW_COPY_AND_ASSIGN(RotaryEncoder);
};

template<typename Encoder>
class RotaryEncoderBuffer {
 public:
  RotaryEncoderBuffer() { }
  
  static void Init() {
    Encoder::Init();
  }
  
  static inline void Read() {
    if (!increment_) {
      increment_ = Encoder::Read();
    }
    if (!clicked_) {
      clicked_ = Encoder::clicked();
    }
  }
  
  static inline uint8_t clicked() { return clicked_; }
  static inline uint8_t increment() { return increment_; }
  static void Flush() {
    increment_ = 0;
    clicked_ = 0; 
  }
  
 private:
  static int8_t increment_;
  static uint8_t clicked_;

  DISALLOW_COPY_AND_ASSIGN(RotaryEncoderBuffer);
};

/* static */
template<typename A, typename B, typename Click, uint16_t debounce_time>
uint32_t RotaryEncoder<A, B, Click, debounce_time>::next_readout_;

/* static */
template<typename Encoder> uint8_t RotaryEncoderBuffer<Encoder>::clicked_;

/* static */
template<typename Encoder> int8_t RotaryEncoderBuffer<Encoder>::increment_;

}  // namespace hardware_hal

#endif  // HARDWARE_HAL_DEVICES_SHIFT_REGISTER_H_
