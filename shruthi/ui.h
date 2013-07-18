// Copyright 2013 Olivier Gillet.
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

  static inline void Poll() {
    ++sub_clock_;
    
    uint8_t sub_clock_10k = sub_clock_ & 0x03;
    if (sub_clock_10k == 0) {
      clock.Tick();
      return;
    }
    
    uint8_t sub_clock_2500 = sub_clock_ & 0x0f;
    if (sub_clock_2500 == 1) {
      lcd.Tick();
      int8_t increment = encoder_.ReadEncoder();
      if (increment != 0) {        
        if (switch_state_[SWITCH_SHIFT] == 0x00) {
          increment = increment < 0 ? -10 : 10;
          switch_inhibit_release_[SWITCH_SHIFT] == true;
        }
        queue_.AddEvent(CONTROL_ENCODER, 0, increment);
      }
      return;
    }
    uint8_t sub_clock_1250 = sub_clock_ & 0x1f;
    uint8_t sub_clock_625 = sub_clock_ & 0x3f;

    if (sub_clock_625 == 2) {
      WriteShiftRegister();
    } else if (sub_clock_625 == 3) {
      DebounceSwitches();
    } else if (sub_clock_1250 == 5) {
      ScanPotentiometers();
    } else if (sub_clock_1250 == 6) {
      TickSystemClock();
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
  }
  
  static void LockPotentiometers();
  
 private:
  static void WriteShiftRegister();
  static void DebounceSwitches();
  static void RefreshLeds();
  static void ScanPotentiometers();

  static bool switch_inhibit_release_[SWITCH_LAST];
  static uint8_t switch_state_[SWITCH_LAST];
  static uint32_t switch_press_time_[SWITCH_LAST];
  static uint32_t encoder_press_time_;
  static bool inhibit_encoder_release_;
  static uint8_t sub_clock_;
  static uint8_t progress_bar_;
  static uint8_t led_pwm_counter_;
  static uint8_t led_pattern_;
  static uint8_t pots_multiplexer_address_;
  
  static int16_t adc_values_[36];
  static int8_t adc_thresholds_[36];
  
  static EventQueue<> queue_;
  static Adc adc_;
  static SpiMaster<IOEnableLine, MSB_FIRST, 4> io_;
  static SpiMaster<IOEnableLineAux, MSB_FIRST, 4> aux_io_;
  static RotaryEncoder<EncoderALine, EncoderBLine, EncoderClickLine> encoder_;

  DISALLOW_COPY_AND_ASSIGN(Ui);
};

extern Ui ui;

}  // namespace shruthi

#endif // SHRUTHI_UI_H_
