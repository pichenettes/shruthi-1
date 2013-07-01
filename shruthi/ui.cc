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

#include "shruthi/ui.h"

#include "shruthi/editor.h"
#include "shruthi/synthesis_engine.h"

namespace shruthi {

using namespace avrlib;

/* static */
bool Ui::switch_inhibit_release_[SWITCH_LAST];
uint8_t Ui::switch_state_[SWITCH_LAST];
uint32_t Ui::switch_press_time_[SWITCH_LAST];
uint8_t Ui::sub_clock_;
uint8_t Ui::progress_bar_;
uint8_t Ui::led_pattern_;
uint8_t Ui::led_pwm_counter_;
uint8_t Ui::programmer_active_pot_;
EventQueue<> Ui::queue_;
SpiMaster<IOEnableLine, MSB_FIRST, 4> Ui::io_;
SpiMaster<IOEnableLineAux, MSB_FIRST, 4> Ui::aux_io_;
RotaryEncoder<EncoderALine, EncoderBLine, EncoderClickLine> Ui::encoder_;

/* static */
void Ui::Init() {
  io_.Init();
  aux_io_.Init();
  encoder_.Init();

  lcd.Init();
  display.Init();
  lcd.SetCustomCharMapRes(character_table[0], 7, 1);

  editor.Init();
  editor.DisplaySplashScreen(STR_RES_V + 1);

  queue_.Flush();

  progress_bar_ = 0;
  programmer_active_pot_ = 0;

  memset(switch_inhibit_release_, 0, sizeof(switch_inhibit_release_));
  memset(switch_state_, 0xff, sizeof(switch_state_));
}

/* static */
void Ui::WriteShiftRegister() {
  uint8_t filter_board = engine.system_settings().expansion_filter_board;
  led_pwm_counter_ += 16;
  io_.Begin();

  switch (filter_board) {
    case FILTER_BOARD_DLY:
      {
        Word w;
        w.value = U8U8Mul(engine.voice().cv_1(), 5);
        aux_io_.End();
        aux_io_.Send(w.bytes[1] | 0x90);
        aux_io_.Begin();
        aux_io_.Send(w.bytes[0]);

        w.value = U8U8Mul(pgm_read_byte(wav_res_ssm2164_linearization + \
            (engine.voice().cv_2() >> 2)), 16);
        aux_io_.Send(w.bytes[1] | 0x10);
        aux_io_.End();
        aux_io_.Begin();
        aux_io_.Send(w.bytes[0]);
      }
      break;

    case FILTER_BOARD_SVF:
      io_.Send(engine.svf_routing_byte());
      break;

    case FILTER_BOARD_PVK:
      io_.Send(engine.pvk_routing_byte());
      break;

    case FILTER_BOARD_4PM:
      io_.Send(engine.four_pole_routing_byte());
      break;
  }

  if (engine.system_settings().expansion_cv_mode == CV_MODE_PROGRAMMER) {
    io_.Send(programmer_active_pot_);
  }

  io_.Send(led_pattern_);
  io_.End();
}

/* static */
void Ui::DebounceSwitches() {
  io_.Begin();
  io_.End();
  uint8_t bits = io_.Receive();
  uint8_t mask = 0x20;
  for (uint8_t i = 0; i < SWITCH_LAST; ++i) {
    switch_state_[i] <<= 1;
    if (bits & mask) {
      switch_state_[i] |= 1;
    }
    mask >>= 1;

    if (switch_state_[i] == 0x80) {
      switch_press_time_[i] = milliseconds();
      switch_inhibit_release_[i] = false;
    } else if (switch_state_[i] == 0x00) {
      int8_t hold_time = static_cast<int8_t>((milliseconds() - switch_press_time_[i]) >> 8);
      if (hold_time > 6 && !switch_inhibit_release_[i]) {
        queue_.AddEvent(CONTROL_SWITCH, i, hold_time);
        switch_inhibit_release_[i] = true;
      }
    } else if (switch_state_[i] == 0x7f) {
      if (!switch_inhibit_release_[i]) {
        if (switch_state_[SWITCH_SHIFT] == 0x00) {
          queue_.AddEvent(CONTROL_SWITCH, i | 0x80, 0);
          switch_inhibit_release_[SWITCH_SHIFT] = true;
        } else {
          queue_.AddEvent(CONTROL_SWITCH, i, 0);
        }
      }
    }
  }
}

/* static */
void Ui::RefreshLeds() {
  // The progress bar overrides the default pattern.
  if (progress_bar_) {
    led_pattern_ = progress_bar_;
    return;
  }

  uint8_t led_pattern = editor.leds_pattern();
  if (editor.current_mode() == EDITOR_MODE_SEQUENCE) {
    if (engine.voice_controller().active()) {
      if (!(engine.voice_controller().step() & 3)) {
        led_pattern |= LED_MODE_MASK;
      }
    }
  } else {
    led_pattern |= LED_MODE_MASK;
    if (editor.current_page() == PAGE_MOD_MATRIX) {
      uint8_t current_modulation_source_value = engine.modulation_source(0,
          engine.patch().modulation_matrix.modulation[
              editor.subpage()].source);
      if (current_modulation_source_value >= led_pwm_counter_) {
        led_pattern |= LED_6_MASK;
      }
    } else if (editor.current_page() == PAGE_MOD_OPERATORS) {
      uint8_t current_operator_value = engine.modulation_source(0,
          MOD_SRC_OP_1 + editor.subpage());
      if (current_operator_value >= led_pwm_counter_) {
        led_pattern |= LED_6_MASK;
      }
    }
  }
  led_pattern_ = led_pattern;
}

/* static */
void Ui::DoEvents() {
  bool refresh_display = false;

  uint8_t previous_page = editor.current_page();

  while (queue_.available()) {
    Event e = queue_.PullEvent();
    queue_.Touch();
    switch (e.control_type) {
      case CONTROL_ENCODER_CLICK:
        editor.HandleClick();
        break;

      case CONTROL_ENCODER:
        editor.HandleIncrement(e.value);
        break;

      case CONTROL_SWITCH:
        editor.HandleSwitchEvent(e);
        break;

      case CONTROL_POT:
        //
        break;
    }
    refresh_display = true;
  }

  if (editor.current_page() != previous_page) {
    // LockPots();
  }

  if (queue_.idle_time_ms() > (engine.system_settings().display_delay << 7)) {
    queue_.Touch();
    editor.Relax();
  }

  if (engine.dirty()) {
    refresh_display = true;
  }

  if (refresh_display) {
    editor.Refresh();
  }

  RefreshLeds();
  display.Tick();
}

/* extern */
Ui ui;

}  // namespace shruthi
