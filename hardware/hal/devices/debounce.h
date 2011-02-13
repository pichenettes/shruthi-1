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
    state_ = 0xff;
  }

  // To be called at a rate < 1000 Hz.
  static inline uint8_t Read() {
    state_ = (state_ << 1) | Input::value();
    return state_;
  }

  static inline uint8_t lowered() { return state_ == 0x80; }
  static inline uint8_t raised() { return state_ == 0x7f; }
  static inline uint8_t high() { return state_ == 0xff; }
  static inline uint8_t low() { return state_ == 0x00; }
  static inline uint8_t state() { return state_; }
  static inline uint8_t immediate_value() { return Input::value(); }
  
 private:
  static uint8_t state_;

  DISALLOW_COPY_AND_ASSIGN(DebouncedSwitch);
};

/* static */
template<typename Input, bool pulled_up>
uint8_t DebouncedSwitch<Input, pulled_up>::state_;

}  // namespace hardware_hal

#endif  // HARDWARE_HAL_DEVICES_DEBOUNCE_H_
