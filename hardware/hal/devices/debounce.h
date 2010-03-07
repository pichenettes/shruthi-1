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
// Switch debouncing.

#ifndef HARDWARE_HAL_DEVICES_DEBOUNCE_H_
#define HARDWARE_HAL_DEVICES_DEBOUNCE_H_

#include "hardware/hal/gpio.h"

namespace hardware_hal {
  
template<typename Input, bool pulled_up = true>
class DebouncedSwitch {
 public:
  DebouncedSwitch() { }
  
  static inline void Init() {
    Input::set_mode(DIGITAL_INPUT);
    if (pulled_up) {
      Input::High();
    }
    state_ = 0xffff;
  }
  
  // To be called at a rate < 1000 Hz.
  static inline void Read() {
    state_ = (state_ << 1) | Input::value() | 0xe000;
    if (raised()) {
      debounced_value_ = 1;
    } else if (lowered()) {
      debounced_value_ = 0;
    }
  }
  
  static inline uint8_t lowered() { return state_ == 0xf000; }
  static inline uint8_t raised() { return state_ == 0xefff; }
  
  static inline uint8_t debounced_value() { return debounced_value_; }
  
 private:
  static uint16_t state_;
  static uint8_t debounced_value_;
  
  DISALLOW_COPY_AND_ASSIGN(DebouncedSwitch);
};

/* static */
template<typename Input, bool pulled_up>
uint16_t DebouncedSwitch<Input, pulled_up>::state_;

/* static */
template<typename Input, bool pulled_up>
uint8_t DebouncedSwitch<Input, pulled_up>::debounced_value_;

}  // namespace hardware_hal

#endif  // HARDWARE_HAL_DEVICES_DEBOUNCE_H_
