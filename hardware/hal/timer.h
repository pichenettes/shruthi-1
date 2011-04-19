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
// Definitions of timer and related PWM registers.

#ifndef HARDWARE_HAL_TIMER_H_
#define HARDWARE_HAL_TIMER_H_

// interrupt.h is not strictly needed here, but .cc files including the timer
// classes are likely to also define interrupt handlers (and we have macros for
// that).
#include <avr/interrupt.h>
#include <avr/io.h>

#include "hardware/hal/hal.h"

namespace hardware_hal {

SpecialFunctionRegister(TCCR0A);
SpecialFunctionRegister(TCCR0B);
SpecialFunctionRegister(TCCR1A);
SpecialFunctionRegister(TCCR1B);
SpecialFunctionRegister(TCCR2A);
SpecialFunctionRegister(TCCR2B);
SpecialFunctionRegister(TIMSK0);
SpecialFunctionRegister(TIMSK1);
SpecialFunctionRegister(TIMSK2);
SpecialFunctionRegister(TCNT0);
SpecialFunctionRegister(TCNT1);
SpecialFunctionRegister(TCNT2);
SpecialFunctionRegister(OCR0A);
SpecialFunctionRegister(OCR0B);
SpecialFunctionRegister(OCR1A);
SpecialFunctionRegister(OCR1B);
SpecialFunctionRegister(OCR2A);
SpecialFunctionRegister(OCR2B);

#ifdef ATMEGA1284P
SpecialFunctionRegister(TCCR3A);
SpecialFunctionRegister(TCCR3B);
SpecialFunctionRegister(TIMSK3);
SpecialFunctionRegister(TCNT3);
SpecialFunctionRegister(OCR3A);
SpecialFunctionRegister(OCR3B);
#endif  // ATMEGA1284P

enum TimerMode {
  TIMER_NORMAL = 0,
  TIMER_PWM_PHASE_CORRECT = 1,
  TIMER_CTC = 2,
  TIMER_FAST_PWM = 3,
};

template<typename StatusRegisterA,
         typename StatusRegisterB,
         typename ModeRegister,
         typename ValueRegister>
struct TimerImpl {
  typedef StatusRegisterA A;
  typedef StatusRegisterB B;

  static inline uint8_t value() {
    return *ValueRegister::ptr();
  }

  static inline void Start() {
    *ModeRegister::ptr() |= 1;
  }
  static inline void Stop() {
    *ModeRegister::ptr() &= ~1;
  }
  static inline void set_mode(TimerMode mode) {
    // Sets the mode registers.
    *StatusRegisterA::ptr() = (*StatusRegisterA::ptr() & 0xfc) | mode;
  }

  // These are the values for MCUs clocked at 20 MHz
  // 
  // Timer speed
  // value | fast        | accurate
  // --------------------------------------
  // 1     | 78.125 kHz  | 39.062 kHz
  // 2     | 9.765 kHz   | 4.882 kHz
  // 3     | 1220.7 Hz   | 610.3 Hz
  // 4     | 305.2 Hz    | 152.6 Hz
  // 5     | 76.3 Hz     | 38.1 Hz
  static inline void set_prescaler(uint8_t prescaler) {
    *StatusRegisterB::ptr() = (*StatusRegisterB::ptr() & 0xf8) | prescaler;
  }
};

template<int n>
struct NumberedTimer { };

template<> struct NumberedTimer<0> {
  typedef TimerImpl<
      TCCR0ARegister,
      TCCR0BRegister,
      TIMSK0Register,
      TCNT0Register> Impl;
};

template<> struct NumberedTimer<1> {
  typedef TimerImpl<
      TCCR1ARegister,
      TCCR1BRegister,
      TIMSK1Register,
      TCNT1Register> Impl;
};

template<> struct NumberedTimer<2> {
  typedef TimerImpl<
      TCCR2ARegister,
      TCCR2BRegister,
      TIMSK2Register,
      TCNT2Register> Impl;
};

#ifdef ATMEGA1284P
template<> struct NumberedTimer<3> {
  typedef TimerImpl<
      TCCR3ARegister,
      TCCR3BRegister,
      TIMSK3Register,
      TCNT3Register> Impl;
};
#endif  // ATMEGA1284P

template<int n>
struct Timer {
  typedef typename NumberedTimer<n>::Impl Impl;
  static inline uint8_t value() { return Impl::value(); }
  static inline void Start() { Impl::Start(); }
  static inline void Stop() { Impl::Stop(); }
  static inline void set_mode(TimerMode mode) { Impl::set_mode(mode); }
  static inline void set_prescaler(uint8_t prescaler) {
    Impl::set_prescaler(prescaler);
  }
};

template<typename Timer, uint8_t enabled_flag, typename PwmRegister>
struct PwmChannel {
  typedef BitInRegister<typename Timer::Impl::A, enabled_flag> EnabledBit;
  enum {
    analog = 1
  };
  static inline void Start() {
    EnabledBit::set();
  }
  static inline void Stop() {
    EnabledBit::clear();
  }
  static inline void Write(uint8_t value) {
    *PwmRegister::ptr() = value;
  }
};

struct NoPwmChannel {
  enum {
    analog = 0
  };
  static inline void Start() { }
  static inline void Stop() { }
  static inline void Write(uint8_t value) { }
};

typedef PwmChannel<Timer<0>, COM0A1, OCR0ARegister> PwmChannel0A;
typedef PwmChannel<Timer<0>, COM0B1, OCR0BRegister> PwmChannel0B;
typedef PwmChannel<Timer<1>, COM1A1, OCR1ARegister> PwmChannel1A;
typedef PwmChannel<Timer<1>, COM1B1, OCR1BRegister> PwmChannel1B;
typedef PwmChannel<Timer<2>, COM2A1, OCR2ARegister> PwmChannel2A;
typedef PwmChannel<Timer<2>, COM2B1, OCR2BRegister> PwmChannel2B;

// Readable aliases for timer interrupts.
#define TIMER_0_TICK ISR(TIMER0_OVF_vect)
#define TIMER_1_TICK ISR(TIMER1_OVF_vect)
#define TIMER_2_TICK ISR(TIMER2_OVF_vect)

#ifdef ATMEGA1284P
#define TIMER_3_TICK ISR(TIMER3_OVF_vect)
#endif  // ATMEGA1284P

}  // namespace hardware_hal

#endif   // HARDWARE_HAL_TIMER_H_
