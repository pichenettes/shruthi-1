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
// Display indicator for the Shruthi-1 12 LEDs + 3 multiplexer bits.

#ifndef HARDWARE_BOOTLOADER_SHRUTHI1_STATUS_LEDS_H_
#define HARDWARE_BOOTLOADER_SHRUTHI1_STATUS_LEDS_H_

#include "hardware/base/base.h"
#include "hardware/hal/devices/shift_register.h"
#include "hardware/shruthi/shruthi.h"

using namespace hardware_hal;
using namespace hardware_shruthi;

class Shruthi1StatusIndicator {
 public:
  static void Clear() {
    led_status_ = 0x0000;
    Update();
  }
  static void ReportError() {
    led_status_ |= 0xff;
    Update();
  }
  static void ClearError() {
    led_status_ = reception_mode_mask_;
    Update();
  }
  static void Flash() {
    led_status_ ^= reception_mode_mask_;
    Update();
  }
  static void DebugByte(uint8_t byte) {
    led_status_ = byte;
    Update();
  }
  static void WaitForData() {
    led_status_ |= reception_mode_mask_;
    Update();
  }
  static void SetProgress(uint8_t progress) {
    uint8_t mask = 1;
    led_status_ = reception_mode_mask_;
    if (progress > 6) {
      progress = 6;
    }
    for (uint8_t i = 0; i < progress; ++i) {
      led_status_ |= mask;
      mask <<= 1;
    }
    Update();
  }
  static void set_reception_mode_mask(uint8_t mask) {
    led_status_ &= ~reception_mode_mask_;
    reception_mode_mask_ = mask;
  }
  static void Init() {
    leds_.Init();
    led_status_ = 0xc0;
    Update();
    led_status_ = 0x00;
  }
 private:
   static void Update() {
     leds_.Write(led_status_);
   }
   static uint8_t reception_mode_mask_;
   static uint8_t led_status_;
   static ShiftRegisterOutput<
       Gpio<kPinLatch>,
       Gpio<kPinClk>,
       Gpio<kPinData>, 8, MSB_FIRST> leds_;
};

/* static */
uint8_t Shruthi1StatusIndicator::reception_mode_mask_;

/* static */
uint8_t Shruthi1StatusIndicator::led_status_;

/* static */
ShiftRegisterOutput<
     Gpio<kPinLatch>,
     Gpio<kPinClk>,
     Gpio<kPinData>, 8, MSB_FIRST> Shruthi1StatusIndicator::leds_;

#endif  // HARDWARE_BOOTLOADER_SHRUTHI1_STATUS_LEDS_H_
