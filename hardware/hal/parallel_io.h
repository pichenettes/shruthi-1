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
// Templates for using full ports or half-ports for parallel output

#ifndef HARDWARE_HAL_PARALLEL_H_
#define HARDWARE_HAL_PARALLEL_H_

#include <avr/io.h>

#include "hardware/hal/gpio.h"

namespace hardware_hal {

enum ParallelPortMode {
  PARALLEL_BYTE,
  PARALLEL_NIBBLE_HIGH,
  PARALLEL_NIBBLE_LOW
};

template<ParallelPortMode mode>
struct ShiftMasks {
  enum Masks {
    mask = 0xff,
    shift = 0
  };
};

template<>
struct ShiftMasks<PARALLEL_NIBBLE_HIGH> {
  enum Masks {
    mask = 0xf0,
    shift = 4,
  };
};

template<>
struct ShiftMasks<PARALLEL_NIBBLE_LOW> {
  enum Masks {
    mask = 0x0f,
    shift = 0,
  };
};

template<typename Port, ParallelPortMode parallel_mode = PARALLEL_BYTE>
struct ParallelPort {
  typedef ShiftMasks<parallel_mode> Masks;

  // Mode change.
  static inline void set_mode(uint8_t mode) {
    uint8_t preserve = (*Port::Mode::ptr() & ~Masks::mask);
    if (mode == DIGITAL_INPUT) {
      *Port::Mode::ptr() = preserve;
    } else if (mode == DIGITAL_OUTPUT) {
      *Port::Mode::ptr() = preserve | Masks::mask;
    }
  }

  static inline void Write(uint8_t value) {
    uint8_t preserve = *Port::Output::ptr() & ~Masks::mask;
    *Port::Output::ptr() = preserve | (value << Masks::shift);
  }

  static inline void EnablePullUpResistors() {
    Write(Masks::mask);
  }

  static inline void Read(uint8_t value) {
    return (*Port::Input::ptr() & Masks::mask) >> Masks::shift;
  }
};

}  // namespace hardware_hal

#endif   // HARDWARE_HAL_PARALLEL_H_
