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
#include "shruthi/part.h"

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
uint8_t Ui::pots_multiplexer_address_;
int16_t Ui::adc_values_[36];
int8_t Ui::adc_thresholds_[36];
uint8_t Ui::adc_warm_up_cycles_;
Adc Ui::adc_;
EventQueue<> Ui::queue_;
SpiMaster<IOEnableLine, MSB_FIRST, 4> Ui::io_;
SpiMaster<IOEnableLineAux, MSB_FIRST, 4> Ui::aux_io_;
RotaryEncoder<EncoderALine, EncoderBLine, EncoderClickLine> Ui::encoder_;

static const int16_t kAdcThresholdLocked = 32;
static const int16_t kAdcThresholdUnlocked = 8;

/* static */
void Ui::Init() {
  io_.Init();
  aux_io_.Init();
  encoder_.Init();

  lcd.Init();
  display.Init();
  lcd.SetCustomCharMapRes(character_table[0], 7, 1);

  editor.Init();
  queue_.Flush();

  progress_bar_ = 0;
  pots_multiplexer_address_ = 0;

  memset(switch_inhibit_release_, 0, sizeof(switch_inhibit_release_));
  memset(switch_state_, 0xff, sizeof(switch_state_));
  
  adc_.Init();
  adc_.set_reference(ADC_DEFAULT);
  adc_.set_alignment(ADC_RIGHT_ALIGNED);
  adc_.StartConversion(0);
  pots_multiplexer_address_ = 0;
    
  for (uint8_t i = 0; i < 36; ++i) {
    adc_values_[i] = -1;
    adc_thresholds_[i] = kAdcThresholdUnlocked;
  }
  adc_warm_up_cycles_ = 8;
}

/* static */
void Ui::ShowSplash() {
  if (part.system_settings().start_page == 0) {
    editor.DisplaySplashScreen(STR_RES_V + 1);
  } else if (part.system_settings().start_page == 2) {
    editor.BootOnPatchBrowsePage(part.system_settings().last_patch);
  } else {
    editor.Refresh();
  }
}

/* static */
void Ui::LockPotentiometers() {
  uint8_t programmer = part.system_settings().programmer;
  adc_thresholds_[0] = kAdcThresholdLocked;
  adc_thresholds_[1] = kAdcThresholdLocked;
  adc_thresholds_[2] = kAdcThresholdLocked;
  adc_thresholds_[3] = kAdcThresholdLocked;
}

const prog_uint8_t xp_parameter_mapping[] PROGMEM = {
  4 + 29,  // PRM_LFO_ATTACK_2
  4 + 30,  // PRM_LFO_RATE_2
  4 + 26,  // PRM_LFO_RATE_1
  4 + 25,  // PRM_LFO_ATTACK_1
  4 + 20,  // PRM_ENV_ATTACK_2
  4 + 23,  // PRM_ENV_RELEASE_2
  4 + 21,  // PRM_ENV_DECAY_2
  4 + 22,  // PRM_ENV_SUSTAIN_2
  
  4 + 18,  // PRM_ENV_SUSTAIN_1
  4 + 17,  // PRM_ENV_DECAY_1
  0xff,  // Software volume... TODO
  4 + 19,  // PRM_ENV_RELEASE_1
  4 + 16,  // PRM_ENV_ATTACK_1
  0xff,  // Unassigned
  0xff,  // Unassigned
  0xff,  // Unassigned
  
  4 + 6,  // PRM_OSC_RANGE_2
  4 + 1,  // PRM_OSC_PARAMETER_1
  4 + 5,  // PRM_OSC_PARAMETER_2
  4 + 2,  // PRM_OSC_RANGE_1
  4 + 7,  // PRM_OSC_OPTION_2
  4 + 10, // PRM_MIX_SUB_OSC
  4 + 9,  // PRM_MIX_BALANCE
  4 + 11, // PRM_MIX_NOISE
  
  0,
  1,
  2,
  3,
  4 + 12,  // PRM_FILTER_CUTOFF
  4 + 13,  // PRM_FILTER_RESONANCE
  4 + 14,  // PRM_FILTER_ENV
  4 + 15,  // PRM_FILTER_LFO
};

/* static */
void Ui::ScanPotentiometers() {
  adc_.Wait();
  uint8_t address = pots_multiplexer_address_;
  int16_t value = adc_.ReadOut();
  
  if (part.system_settings().programmer == PROGRAMMER_NONE) {
    *PortA::Mode::ptr() = 0x00;
    pots_multiplexer_address_ = (pots_multiplexer_address_ + 1) & 7;
    adc_.StartConversion(pots_multiplexer_address_);
    if (address >= 4) {
      part.mutable_voice()->set_modulation_source(
          MOD_SRC_CV_1 + address - 4, value >> 2);
      address = 0xff;
    }
  } else if (part.system_settings().programmer == PROGRAMMER_FCD) {
    *PortA::Mode::ptr() = 0x00;
    pots_multiplexer_address_++;
    if (pots_multiplexer_address_ >= 36) {
      pots_multiplexer_address_ = 0;
    }
    if (pots_multiplexer_address_ < 4) {
      adc_.StartConversion(pots_multiplexer_address_);
    } else {
      WriteShiftRegister();
      adc_.StartConversion(4);
    }
  } else if (part.system_settings().programmer == PROGRAMMER_XT) {
    *PortA::Mode::ptr() = 0xfe;
    pots_multiplexer_address_ = (pots_multiplexer_address_ + 1) & 31;
    uint8_t byte = (pots_multiplexer_address_ << 1) & 0x0f;
    uint8_t range = pots_multiplexer_address_ >> 3;
    byte |= (~(0x10 << range)) & 0xf0;
    *PortA::Output::ptr() = byte;
    adc_.StartConversion(0);
    address = pgm_read_byte(xp_parameter_mapping + address);
  }
  
  if (address != 0xff) {
    if (adc_warm_up_cycles_) {
      // Register the value and move on.
      adc_values_[address] = value;
      if (address == 0) {
        --adc_warm_up_cycles_;
      }
    } else {
      int16_t previous_value = adc_values_[address];
      int16_t delta = value - previous_value;
      int16_t threshold = adc_thresholds_[address];
      if (delta > threshold || delta < -threshold) {
        adc_thresholds_[address] = kAdcThresholdUnlocked;
        queue_.AddEvent(CONTROL_POT, address, value >> 3);
        adc_values_[address] = value;
      }
    }
  }
}

/* static */
void Ui::WriteShiftRegister() {
  uint8_t filter_board = part.system_settings().expansion_filter_board;
  led_pwm_counter_ += 16;
  io_.Begin();

  switch (filter_board) {
    case FILTER_BOARD_DLY:
      {
        Word w;
        w.value = U8U8Mul(part.voice().cv_1(), 5);
        aux_io_.End();
        aux_io_.Send(w.bytes[1] | 0x90);
        aux_io_.Begin();
        aux_io_.Send(w.bytes[0]);

        w.value = U8U8Mul(pgm_read_byte(wav_res_ssm2164_linearization + \
            (part.voice().cv_2() >> 2)), 16);
        aux_io_.Send(w.bytes[1] | 0x10);
        aux_io_.End();
        aux_io_.Begin();
        aux_io_.Send(w.bytes[0]);
      }
      break;

    case FILTER_BOARD_SVF:
      io_.Send(part.svf_routing_byte());
      break;

    case FILTER_BOARD_PVK:
      io_.Send(part.pvk_routing_byte());
      break;

    case FILTER_BOARD_4PM:
      io_.Send(part.four_pole_routing_byte());
      break;
  }

  if (part.system_settings().programmer == PROGRAMMER_FCD) {
    io_.Send(
        pots_multiplexer_address_ >= 4 ? pots_multiplexer_address_ - 4 : 0);
  }

  io_.Send(led_pattern_);
  io_.End();
}

/* static */
void Ui::DebounceSwitches() {
  io_.Begin();
  io_.End();
  
  uint8_t last_switch;
  uint8_t switch_data[3];
  
  if (part.system_settings().programmer == PROGRAMMER_XT) {
    switch_data[1] = io_.Receive();
    switch_data[0] = io_.Receive();
    switch_data[2] = io_.Receive();
    last_switch = SWITCH_LAST - 1;
  } else {
    switch_data[0] = io_.Receive();
    switch_data[1] = 0xff;
    switch_data[2] = 0xff;
    last_switch = SWITCH_ENCODER;
  }
  
  uint8_t data = switch_data[0];
  uint8_t mask = 0x20;
  for (uint8_t i = 0; i <= last_switch; ++i) {
    if (i == SWITCH_ENCODER) {
      switch_state_[i] = encoder_.ReadSwitch();
      continue;
    } else if (i == SWITCH_OSC_2_MINUS) {
      data = switch_data[1];
      mask = 0x80;
    } else if (i == SWITCH_LFO_1_SHAPE_MINUS) {
      data = switch_data[2];
      mask = 0x10;
    }
    switch_state_[i] <<= 1;
    if (data & mask) {
      switch_state_[i] |= 1;
    }
    mask >>= 1;
  }

  for (uint8_t i = 0; i <= last_switch; ++i) {
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
          queue_.AddEvent(CONTROL_SWITCH, i, 0xff);
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
    if (part.running()) {
      if (!(part.step() & 3)) {
        led_pattern |= LED_MODE_MASK;
      }
    }
  } else {
    led_pattern |= LED_MODE_MASK;
    if (editor.current_page() == PAGE_MOD_MATRIX) {
      uint8_t current_modulation_source_value = part.modulation_source(0,
          part.patch().modulation_matrix.modulation[
              editor.subpage()].source);
      if (current_modulation_source_value > led_pwm_counter_) {
        led_pattern |= LED_6_MASK;
      }
    } else if (editor.current_page() == PAGE_MOD_OPERATORS) {
      uint8_t current_operator_value = part.modulation_source(0,
          MOD_SRC_OP_1 + editor.subpage());
      if (current_operator_value > led_pwm_counter_) {
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
      case CONTROL_ENCODER:
        editor.HandleIncrement(e.value);
        break;

      case CONTROL_SWITCH:
        if (e.control_id <= SWITCH_LOAD_SAVE) {
          editor.HandleSwitch(e);
        } else if (e.control_id == SWITCH_ENCODER) {
          if (e.value < 6) {
            editor.HandleClick();
          } else {
            editor.HandleLongClick();
          }
        } else {
          editor.HandleProgrammerSwitch(e);
        }
        break;

      case CONTROL_POT:
        if (e.control_id < 4) {
          editor.HandleInput(e.control_id, e.value);
        } else {
          editor.HandleProgrammerInput(e.control_id - 4, e.value);
        }
        break;
    }
    refresh_display = true;
  }

  if (editor.current_page() != previous_page) {
    LockPotentiometers();
  }

  if (queue_.idle_time_ms() > (part.system_settings().display_delay << 7)) {
    queue_.Touch();
    editor.Relax();
    refresh_display = true;
  }
  
  if (queue_.idle_time_ms() > 100 && part.dirty()) {
    queue_.Touch();
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
