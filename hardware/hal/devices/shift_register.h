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
// Driver for a 8-bits shift register.

#ifndef HARDWARE_HAL_DEVICES_SHIFT_REGISTER_H_
#define HARDWARE_HAL_DEVICES_SHIFT_REGISTER_H_

#include "hardware/hal/gpio.h"
#include "hardware/hal/size_to_type.h"

namespace hardware_hal {

template<typename Latch, typename Clock, typename Data>
struct BaseShiftRegister {
  BaseShiftRegister() { }
  static void Init() {
    Clock::set_mode(DIGITAL_OUTPUT);
    Latch::set_mode(DIGITAL_OUTPUT);
    Data::set_mode(DIGITAL_OUTPUT);
    Latch::High();
  }
};

template<typename Latch, typename Clock, typename Data,
         uint8_t size = 8, DataOrder order = LSB_FIRST>
struct ShiftRegister : public BaseShiftRegister<Latch, Clock, Data> {
};

template<typename Latch, typename Clock, typename Data,
         uint8_t size>
struct ShiftRegister<Latch, Clock, Data, size, LSB_FIRST>
  : public BaseShiftRegister<Latch, Clock, Data> {
  ShiftRegister() { }
  static void Write(typename DataTypeForSize<size>::Type data) {
    LOG(INFO) << "pin_" << Data::number() << "\tshift\t" << int(data);
    Latch::Low();
    Data::Low();
    for (uint8_t i = size; i > 0; --i) {
      Clock::Low();
      Data::set_value(data & 1);
      data >>= 1;
      Clock::High();
      Data::Low();
    }
    Clock::Low();
    Latch::High();
  }
};

template<typename Latch, typename Clock, typename Data, uint8_t size>
struct ShiftRegister<Latch, Clock, Data, size, MSB_FIRST>
  : public BaseShiftRegister<Latch, Clock, Data> {
  ShiftRegister() { }
  typedef typename DataTypeForSize<size>::Type T;
  static void Write(T data) {
    LOG(INFO) << "pin_" << Data::number() << "\tshift\t" << int(data);
    Latch::Low();
    Data::Low();
    T mask = (T(1) << (size - 1));
    for (uint8_t i = size; i > 0; --i) {
      Clock::Low();
      if (data & mask) {
        Data::High();
      } else {
        Data::Low();
      }
      mask >>= 1;
      Clock::High();
      Data::Low();
    }
    Clock::Low();
    Latch::High();
  }
};

}  // namespace hardware_hal

#endif  // HARDWARE_HAL_DEVICES_SHIFT_REGISTER_H_
