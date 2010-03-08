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
// Interface to the onboard ADC converter, and analog multiplexer.

#ifndef HARDWARE_HAL_ADC_H_
#define HARDWARE_HAL_ADC_H_

#include <avr/io.h>

#include "hardware/hal/hal.h"

namespace hardware_hal {

enum AdcReference {
  ADC_EXTERNAL = 0,
  ADC_DEFAULT = 1,
  ADC_INTERNAL = 3
};

IORegister(ADCSRA);

typedef BitInRegister<ADCSRARegister, ADSC> AdcConvert;
typedef BitInRegister<ADCSRARegister, ADEN> AdcEnabled;

class Adc {
 public:
  static inline void set_prescaler(uint8_t factor) {
    ADCSRA = (ADCSRA & ~0x07) | (factor & 0x07);
  }
  static inline void set_reference(AdcReference reference) {
    reference_ = reference << 6;
  }
  static inline void Enable() {
    AdcEnabled::set();
  }
  static inline void Disable() {
    AdcEnabled::clear();
  }
  // TODO(pichenettes): add function to modify sampling rate.
  static inline int16_t Read(uint8_t pin) {
    StartConversion(pin);
    Wait();
    return ReadOut();
  }

 private:
  static uint8_t reference_;
 
  static inline void StartConversion(uint8_t pin) {
    ADMUX = reference_ | (pin & 0x07);
    AdcConvert::set();
  }
  static inline void Wait() {
    while (AdcConvert::value());
  }
  static inline int16_t ReadOut() {
    uint8_t low = ADCL;
    uint8_t high = ADCH;
    return (high << 8) | low;
  }
  DISALLOW_COPY_AND_ASSIGN(Adc);
};

template<int pin>
struct AnalogInput {
  enum {
    buffer_size = 0,
    data_size = 16,
  };
  static void Init() { }
  static int16_t Read() {
    return Adc::Read(pin);
  }
};

template<int id>
class MuxedAnalogInput {
 public:
  enum {
    buffer_size = 0,
    data_size = 16,
  };
  static void Init() { }
  static int16_t Read() {
    return Adc::Read(current_pin_);
  }
  static void set_pin(uint8_t current_pin) {
    current_pin_ = current_pin;
  }
  
 private:
  static uint8_t current_pin_;
};

/* static */
template<int id>
uint8_t MuxedAnalogInput<id>::current_pin_ = 0;

}  // namespace hardware_hal

#endif  // HARDWARE_HAL_ADC_H_
