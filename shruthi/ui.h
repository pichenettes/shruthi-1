// Copyright 2013 Emilie Gillet.
//
// Author: Emilie Gillet (emilie.o.gillet@gmail.com)
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
// User interface handler.

#ifndef SHRUTHI_UI_H_
#define SHRUTHI_UI_H_

#include "avrlib/adc.h"
#include "avrlib/devices/rotary_encoder.h"
#include "avrlib/spi.h"
#include "avrlib/time.h"
#include "avrlib/ui/event_queue.h"

#include "shruthi/clock.h"
#include "shruthi/display.h"
#include "shruthi/hardware_config.h"

namespace shruthi {

using namespace avrlib;

class Ui {
 public:
  Ui() { }
  ~Ui() { }

  static void Init();
  static void DoEvents();

  static void Poll() {
    lcd.Tick();
    
    int8_t increment = encoder_.ReadEncoder();
    if (increment != 0) {        
      if (switch_state_[SWITCH_SHIFT] == 0x00) {
        increment = increment < 0 ? -10 : 10;
        inhibit_shift_release_ = true;
      }
      queue_.AddEvent(CONTROL_ENCODER, 0, increment);
    }
    sub_clock_ = (sub_clock_ + 1) & 7;
    if (sub_clock_ & 1) {
      TickSystemClock();
      display.BlinkCursor();
    } else {
      WriteShiftRegister();
    }
    if (sub_clock_ == 1) {
      ScanPotentiometers();
    }
    if (sub_clock_ == 3) {
      DebounceSwitches();
    }
  }
  
  static void BeginProgressBar() {
    progress_bar_ = 1;
  }

  static void EndProgressBar() {
    progress_bar_ = 0;
  }

  static void StepProgressBar() {
    progress_bar_ = progress_bar_ == 0xff ? 1 : (progress_bar_ << 1) + 1;
    RefreshLeds();
  }
  
  static void LockPotentiometers();
  static void ShowSplash();
  
 private:
  static void WriteShiftRegister();
  static void DebounceEncoder();
  static void DebounceSwitches();
  static void RefreshLeds();
  static void ScanPotentiometers();

  static uint8_t switch_state_[SWITCH_LAST];
  static uint32_t switch_delay_[SWITCH_LAST];
  static bool inhibit_shift_release_;
  static bool inhibit_encoder_release_;
  static uint8_t sub_clock_;
  static uint8_t sub_clock_2_;
  static uint8_t progress_bar_;
  static uint8_t led_pwm_counter_;
  static uint8_t led_pattern_;
  static uint8_t pots_multiplexer_address_;
  
  static uint8_t adc_hot_address_;
  static uint8_t adc_resume_scan_to_;
  static uint8_t adc_warm_up_cycles_;
  static int16_t adc_values_[36];
  static int8_t adc_thresholds_[36];

  static uint32_t idle_time_;
  static bool freeze_display_;
  
  static EventQueue<> queue_;
  static Adc adc_;
  static SpiMaster<IOEnableLine, MSB_FIRST, 4> io_;
  static SpiMaster<IOEnableLineAux, MSB_FIRST, 4> aux_io_;
  static RotaryEncoder<
      EncoderALine,
      EncoderBLine,
      EncoderClickLine> encoder_;

  DISALLOW_COPY_AND_ASSIGN(Ui);
};

extern Ui ui;

}  // namespace shruthi

#endif // SHRUTHI_UI_H_
