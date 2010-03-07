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
// An alternative gpio library based on templates.
//
// Examples of use:
//
// Gpio<3>::set_mode(DIGITAL_INPUT)
// Gpio<4>::set_mode(DIGITAL_OUTPUT)
// Gpio<3>::value()
// Gpio<4>::High()
// Gpio<4>::Low()
// Gpio<4>::set_value(1)
// Gpio<4>::set_value(0)
//
// Using the logging facilities in logging.h, this can also generates debugging
// code (for compilation on desktop computers) which logs to stderr the activity
// on the pin.

#ifndef HARDWARE_HAL_GPIO_H_
#define HARDWARE_HAL_GPIO_H_

#include <avr/io.h>

#include "hardware/hal/hal.h"
#include "hardware/hal/timer.h"

namespace hardware_hal {

enum PinMode {
  DIGITAL_INPUT = 0,
  DIGITAL_OUTPUT = 1,
  ANALOG_OUTPUT = 2
};

// All the registers used in the following definitions are wrapped here.
IORegister(DDRB);
IORegister(DDRC);
IORegister(DDRD);

IORegister(PORTB);
IORegister(PORTC);
IORegister(PORTD);

IORegister(PINB);
IORegister(PINC);
IORegister(PIND);

// Represents a i/o port, which has input, output and mode registers.
template<typename InputRegister, typename OutputRegister,
         typename ModeRegister>
struct Port {
  typedef InputRegister Input;
  typedef OutputRegister Output;
  typedef ModeRegister Mode;
};

// Definition of I/O ports.
typedef Port<PINBRegister, PORTBRegister, DDRBRegister> PortB;
typedef Port<PINCRegister, PORTCRegister, DDRCRegister> PortC;
typedef Port<PINDRegister, PORTDRegister, DDRDRegister> PortD;

// The actual implementation of a pin, not very convenient to use because it
// requires the actual parameters of the pin to be passed as template
// arguments.
template<typename Port, typename PwmChannel, uint8_t bit, bool safe>
struct GpioImpl {
  typedef BitInRegister<typename Port::Mode, bit> ModeBit;
  typedef BitInRegister<typename Port::Output, bit> OutputBit;
  typedef BitInRegister<typename Port::Input, bit> InputBit;
  
  // Mode change.
  static inline void set_mode(uint8_t mode) {
    if (mode == DIGITAL_INPUT) {
      ModeBit::clear();
    } else if (mode == DIGITAL_OUTPUT || mode == ANALOG_OUTPUT) {
      ModeBit::set();
    }
    if (mode == ANALOG_OUTPUT) {
      PwmChannel::Start();
    } else {
      PwmChannel::Stop();
    }
  }

  // Digital Write.
  static inline void High() {
    if (safe) {
      set_mode(DIGITAL_OUTPUT);
    }
    OutputBit::set();
  }
  static inline void Low() {
    if (safe) {
      set_mode(DIGITAL_OUTPUT);
    }
    OutputBit::clear();
  }
  static inline void set_value(uint8_t value) {
    if (value == 0) {
      Low();
    } else {
      High();
    }
  }
  static inline void set_analog_value(uint8_t value) {
    if (safe) {
      set_mode(ANALOG_OUTPUT);
    }
    if (PwmChannel::analog) {
      PwmChannel::Write(value);
    } else {
      set_value(value);
    }
  }

  // Digital read.
  static inline uint8_t value() {
    if (safe) {
      set_mode(DIGITAL_INPUT);
    }
    return InputBit::value();
  }
};

// A template that will be specialized for each pin, allowing the pin number to
// be specified as a template parameter.
template<int n, bool safe>
struct NumberedGpio { };

// Macro to make the pin definitions (template specializations) easier to read.
#define SetupGpio(n, port, timer, bit) \
template<bool safe> struct NumberedGpio<n, safe> { \
  typedef GpioImpl<port, timer, bit, safe> Impl; };

SetupGpio(0,  PortB, NoPwmChannel, 0);
SetupGpio(1,  PortB, NoPwmChannel, 1);
SetupGpio(2,  PortB, NoPwmChannel, 2);
SetupGpio(3,  PortB, PwmChannel0A, 3);
SetupGpio(4,  PortB, PwmChannel0B, 4);
SetupGpio(5,  PortB, NoPwmChannel, 5);
SetupGpio(6,  PortB, NoPwmChannel, 6);
SetupGpio(7,  PortB, NoPwmChannel, 7);

SetupGpio(8,  PortD, NoPwmChannel, 0);
SetupGpio(9,  PortD, NoPwmChannel, 1);
SetupGpio(10, PortD, NoPwmChannel, 2);
SetupGpio(11, PortD, NoPwmChannel, 3);
SetupGpio(12, PortD, PwmChannel1B, 4);
SetupGpio(13, PortD, PwmChannel1A, 5);
SetupGpio(14, PortD, PwmChannel2B, 6);
SetupGpio(15, PortD, PwmChannel2A, 7);

SetupGpio(16, PortC, NoPwmChannel, 0);
SetupGpio(17, PortC, NoPwmChannel, 1);
SetupGpio(18, PortC, NoPwmChannel, 2);
SetupGpio(19, PortC, NoPwmChannel, 3);
SetupGpio(20, PortC, NoPwmChannel, 4);
SetupGpio(21, PortC, NoPwmChannel, 5);
SetupGpio(22, PortC, NoPwmChannel, 6);
SetupGpio(23, PortC, NoPwmChannel, 7);

// Two specializations of the numbered pin template, one which clears the timer
// for each access to the PWM pins, as does the original Arduino wire lib,
// the other that does not (use with care!).
template<int n, bool safe = false>
struct Gpio {
  typedef typename NumberedGpio<n, safe>::Impl Impl;
  static void set_mode(uint8_t mode) { Impl::set_mode(mode); }
  static void High() { Impl::High(); }
  static void Low() { Impl::Low(); }
  static void set_value(uint8_t value) { Impl::set_value(value); }
  static void set_analog_value(uint8_t value) { Impl::set_analog_value(value); }
  static uint8_t value() { return Impl::value(); }
  static uint8_t number() { return n; }
};

template<int pin>
struct DigitalInput {
  enum {
    buffer_size = 0,
    data_size = 1,
  };
  static void Init() {
    Gpio<pin>::set_mode(DIGITAL_INPUT);
  }
  static void EnablePullUpResistor() {
    Gpio<pin>::High();
  }
  static uint8_t Read() {
    return Gpio<pin>::value();
  }
};

template<int pin>
struct PwmOutput {
  enum {
    buffer_size = 0,
    data_size = 8,
  };
  static void Init() {
    Gpio<pin>::set_mode(ANALOG_OUTPUT);
  }
  static void Write(uint8_t value) {
    return Gpio<pin>::set_analog_value(value);
  }
};

}  // namespace hardware_hal

#endif   // HARDWARE_HAL_GPIO_H_
