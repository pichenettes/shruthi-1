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
// Fast SPI communication (using the hardware implementation). This will take
// ownership of the pins 11 (data output),  12 (data input) and 13 (clock), +
// a user-definable pin for slave selection (10 is recommended, or 10, or... 10)
//
// This is a fairly basic implementation:
// - nothing is buffered, since the overhead of managing a circular buffer is
//   around 15 cycles (not including the interrupt prelude/postlude), which is
//   close to the transmission time at the fastest speed.
// - the atmega is always configured as a master.
// - no support for reading back from the slave.

#ifndef HARDWARE_HAL_SPI_H_
#define HARDWARE_HAL_SPI_H_

#include "hardware/hal/hal.h"
#include "hardware/hal/gpio.h"

namespace hardware_hal {

const uint8_t kSpiDataOutPin = 11;
const uint8_t kSpiDataInPin = 12;
const uint8_t kSpiClockPin = 13;

IORegister(SPSR);
typedef BitInRegister<SPSRRegister, SPI2X> DoubleSpeed;
typedef BitInRegister<SPSRRegister, SPIF> TransferComplete;

template<uint8_t slave_select_pin = 10,
         DataOrder order = MSB_FIRST,
         uint8_t speed = 4>
class Spi {
 public:
  enum {
    buffer_size = 0,
    data_size = 8
  };
  
  static void Init() {
    Clock::set_mode(DIGITAL_OUTPUT);
    DataIn::set_mode(DIGITAL_INPUT);
    DataOut::set_mode(DIGITAL_OUTPUT);
    SlaveSelect::set_mode(DIGITAL_OUTPUT);
    
    SlaveSelect::High();
    
    // SPI enabled, configured as master.
    uint8_t configuration = _BV(SPE) | _BV(MSTR);
    if (order == LSB_FIRST) {
      configuration |= _BV(DORD);
    }
    switch (speed) {
      case 2:
        DoubleSpeed::set();
      case 4:
        break;
      case 8:
        DoubleSpeed::set();
      case 16:
        configuration |= _BV(SPR0);
        break;
      case 32:
        DoubleSpeed::set();
      case 64:
        configuration |= _BV(SPR1);
        break;
      case 128:
        configuration |= _BV(SPR0);
        configuration |= _BV(SPR1);
        break;
    }
    SPCR = configuration;
  }
  
  static inline void Write(uint8_t v) {
    SlaveSelect::Low();
    SPDR = v;
    while (!TransferComplete::value());
    SlaveSelect::High();
  }

  static inline void WriteWord(uint8_t a, uint8_t b) {
    SlaveSelect::Low();
    SPDR = a;
    while (!TransferComplete::value());
    SPDR = b;
    while (!TransferComplete::value());
    SlaveSelect::High();
  }
  
 private:
  typedef Gpio<slave_select_pin> SlaveSelect;
  typedef Gpio<kSpiDataOutPin> DataOut;
  typedef Gpio<kSpiDataInPin> DataIn;
  typedef Gpio<kSpiClockPin> Clock;
};

}  // namespace hardware_hal

#endif HARDWARE_HAL_SPI_H_
