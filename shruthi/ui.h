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

#include "shruthi/hardware_config.h"
#include "shruthi/display.h"

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

    // 40kHz / 16 -> refresh LCD and debounce encoder.
    if ((sub_clock_ & 0xf) == 0) {
      lcd.Tick();
      int8_t increment = encoder_.Read();
      if (increment != 0) {        
        if (switch_state_[SWITCH_SHIFT] == 0x00) {
          increment = increment < 0 ? -10 : 10;
          switch_inhibit_release_[SWITCH_SHIFT] == true;
        }
        queue_.AddEvent(CONTROL_ENCODER, 0, increment);
      }
      if (encoder_.clicked()) {
        queue_.AddEvent(CONTROL_ENCODER_CLICK, 0, 1);
      }
    }
    
    // Sub tasks at 40kHz / 32
    uint8_t subtask = sub_clock_ & 0x1f;
    if (subtask == 1) {
      WriteShiftRegister();
    } else if (subtask == 2) {
      DebounceSwitches();
    } else if (subtask == 3) {
      ScanPotentiometers();
    } else if (subtask == 4) {
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
