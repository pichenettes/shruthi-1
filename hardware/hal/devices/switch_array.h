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
// Controller for an array of switches read through a parallel-in > serial out
// shift register. Includes debouncing.

#ifndef HARDWARE_HAL_DEVICES_SWITCH_ARRAY_H_
#define HARDWARE_HAL_DEVICES_SWITCH_ARRAY_H_

#include "hardware/hal/size_to_type.h"
#include "hardware/hal/time.h"

namespace hardware_hal {

struct SwitchState {
  uint8_t changed;
  uint8_t state;
  uint8_t debounced_state;
  uint32_t time;
};

struct ReleasedEvent {
  uint8_t id;
  uint8_t shifted;
  uint8_t duration;
};

template<typename ShiftRegisterInput, uint8_t num_inputs, uint8_t shift = 0>
class SwitchArray {
 public:
  SwitchArray() { }
  typedef typename DataTypeForSize<Input::data_size>::Type T;
  
  static void Init() {
    for (uint8_t i = 0; i < num_inputs; ++i) {
      switch_state_[i].state = 0xff;
      switch_state_[i].debounced_state = HIGH;
      switch_state_[i].time = 0;
    }
    last_event_time_ = 0;
    ShiftRegisterInput::Init();
  }

  static uint32_t last_event_time() { return last_event_time_; }
  static uint32_t idle_time() { return milliseconds() - last_event_time_; }
  static const SwitchState& switch_state(uint8_t i) { return switch_state_[i]; }
  static uint8_t released() {
    for (uint8_t i = 0; i < num_inputs; ++i) {
      if (switch_state_[i].state == 0x7f) {
        return 1;
      }
    }
    return 0;
  }
  static ReleasedEvent released_event() {
    ReleasedEvent e;
    for (uint8_t i = 0; i < num_inputs; ++i) {
      if (switch_state_[i].state == 0x7f) {
        e.id = i;
        e.shifted = (switch_state_[shift].state == 0x00) ? 1 : 0;
        e.duration = static_cast<uint16_t>(
            last_event_time_ - switch_state_[i].time) >> 8;
      }
    }
    return e;
  }
  
  static uint8_t Read() {
    T value = ShiftRegisterInput::Read();
    uint32_t now = milliseconds();
    for (uint8_t i = 0; i < num_inputs; ++i) {
      switch_state_[i].state = (switch_state_[i].state << 1) | (value & 1);
      if (switch_state_[i].state == 0x80) {
        last_event_time_ = now;
        switch_state_[i].debounced_state = LOW;
        switch_state_[i].time = now;
      } else if (switch_state_[i].state == 0x7f) {
        last_event_time_ = now;
        switch_state_[i].debounced_state = HIGH;
      }
      value >>= 1;
    }
  }
  
 private:
  static uint32_t last_event_time_;
  static SwitchState switch_state_[num_inputs];
  
  DISALLOW_COPY_AND_ASSIGN(SwitchArray);
};

template<typename ShiftRegisterInput, uint8_t num_inputs, uint8_t shift>
SwitchState SwitchArray<ShiftRegisterInput, num_inputs, shift>::switch_state_[num_inputs];

template<typename ShiftRegisterInput, uint8_t num_inputs, uint8_t shift>
uint32_t SwitchArray<ShiftRegisterInput, num_inputs, shift>::last_event_time_;


}  // namespace hardware_hal

#endif   // HARDWARE_HAL_DEVICES_SWITCH_ARRAY_H_
