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

#include "shruthi/ui.h"

#include "shruthi/editor.h"
#include "shruthi/part.h"

namespace shruthi {

using namespace avrlib;

/* static */
bool Ui::inhibit_shift_release_;
bool Ui::inhibit_encoder_release_;
uint8_t Ui::switch_state_[SWITCH_LAST];
uint32_t Ui::switch_delay_[SWITCH_LAST];
uint8_t Ui::sub_clock_;
uint8_t Ui::sub_clock_2_;
uint8_t Ui::progress_bar_;
uint8_t Ui::led_pattern_;
uint8_t Ui::led_pwm_counter_;
uint8_t Ui::pots_multiplexer_address_;
int16_t Ui::adc_values_[36];
int8_t Ui::adc_thresholds_[36];
uint8_t Ui::adc_warm_up_cycles_;
uint8_t Ui::adc_hot_address_;
uint8_t Ui::adc_resume_scan_to_;
uint32_t Ui::idle_time_;
bool Ui::freeze_display_;
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

  inhibit_shift_release_ = false;
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
  adc_hot_address_ = 0;
  adc_resume_scan_to_ = 0;
}

/* static */
void Ui::ShowSplash() {
  if (!encoder_.immediate_value()) {
    SystemSettings* settings = part.mutable_system_settings();
    settings->programmer = settings->programmer + 1;
    if (settings->programmer > PROGRAMMER_XT) {
      settings->programmer = 0;
    }
    settings->EepromSave();
    editor.DisplaySplashScreen(
        STR_RES_SHRUTHI_CLASSIC + (settings->programmer << 1));
    freeze_display_ = true;
  } else if (part.system_settings().start_page == START_PAGE_SPLASH) {
    editor.DisplaySplashScreen(STR_RES_V + 1);
  } else if (part.system_settings().start_page == START_PAGE_LAST_PATCH) {
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

const prog_uint8_t xt_parameter_mapping[] PROGMEM = {
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
  4 + 31,  // SOFTWARE VOLUME
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
  uint8_t physical_address = address;
  int16_t value = adc_.ReadOut();
  
  if (part.system_settings().programmer == PROGRAMMER_NONE) {
    *PortA::Mode::ptr() = 0x00;
    pots_multiplexer_address_ = (pots_multiplexer_address_ + 1) & 7;
    if (adc_resume_scan_to_ == 0) {
      adc_resume_scan_to_ = pots_multiplexer_address_ + 1;
      pots_multiplexer_address_ = adc_hot_address_;
    } else {
      pots_multiplexer_address_ = adc_resume_scan_to_ - 1;
      adc_resume_scan_to_ = 0;
    }    
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
    if (adc_resume_scan_to_ == 0) {
      adc_resume_scan_to_ = pots_multiplexer_address_ + 1;
      pots_multiplexer_address_ = adc_hot_address_;
    } else {
      pots_multiplexer_address_ = adc_resume_scan_to_ - 1;
      adc_resume_scan_to_ = 0;
    }    
    uint8_t byte = (pots_multiplexer_address_ << 1) & 0x0f;
    uint8_t range = pots_multiplexer_address_ >> 3;
    byte |= (~(0x10 << range)) & 0xf0;
    *PortA::Output::ptr() = byte;
    adc_.StartConversion(0);
    address = pgm_read_byte(xt_parameter_mapping + address);
  }
  
  if (address != 0xff) {
    if (adc_warm_up_cycles_) {
      // Register the value and move on.
      adc_values_[address] = value;
      if (address == 0) {
        --adc_warm_up_cycles_;
        if (adc_warm_up_cycles_ == 0) {
          // Send a message for the volume knob
          if (part.system_settings().programmer == PROGRAMMER_XT) {
            queue_.AddEvent(CONTROL_POT, 35, adc_values_[35]);
          }
        }
      }
    } else {
      int16_t previous_value = adc_values_[address];
      int16_t delta = value - previous_value;
      int16_t threshold = adc_thresholds_[address];
      if (delta > threshold || delta < -threshold) {
        adc_hot_address_ = physical_address;
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
      
    case FILTER_BOARD_SP:
      io_.Send(part.sp_routing_byte());
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
  
  // Handle basic switches
  for (uint8_t i = 0; i <= SWITCH_MODE; ++i) {
    if (switch_state_[i] == 0x80) {
      if (switch_state_[SWITCH_SHIFT] == 0x00) {
        queue_.AddEvent(CONTROL_SWITCH, i, 0xff);
        inhibit_shift_release_ = true;
      } else {
        queue_.AddEvent(CONTROL_SWITCH, i, 0);
      }
    }
  }
  
  // Handle shift switch
  if (switch_state_[SWITCH_SHIFT] == 0x7f) {
    if (!inhibit_shift_release_) {
      queue_.AddEvent(CONTROL_SWITCH, SWITCH_SHIFT, 0);
    }
    inhibit_shift_release_ = false;
  }
  
  // Handle encoder
  if (switch_state_[SWITCH_ENCODER] == 0x80) {
    switch_delay_[SWITCH_ENCODER] = milliseconds() + 1000;
    inhibit_encoder_release_ = false;
  } else if (switch_state_[SWITCH_ENCODER] == 0x00) {
    uint32_t now = milliseconds();
    int32_t delta = now - switch_delay_[SWITCH_ENCODER];
    if (!inhibit_encoder_release_ && delta > 0) {
      queue_.AddEvent(CONTROL_SWITCH, SWITCH_ENCODER, 6);
      inhibit_encoder_release_ = true;
    }
  } else if (switch_state_[SWITCH_ENCODER] == 0x7f) {
    if (!inhibit_encoder_release_) {
      queue_.AddEvent(CONTROL_SWITCH, SWITCH_ENCODER, 0);
    }
    inhibit_encoder_release_ = false;
  }
  
  for (uint8_t i = SWITCH_OSC_2_MINUS; i <= last_switch; ++i) {
    if (switch_state_[i] == 0x80) {
      switch_delay_[i] = milliseconds() + 480;
      queue_.AddEvent(CONTROL_SWITCH, i, 0);
    } else if (switch_state_[i] == 0x00) {
      uint32_t now = milliseconds();
      int32_t delta = now - switch_delay_[i];
      if (delta > 0) {
        queue_.AddEvent(CONTROL_SWITCH, i, 0);
        switch_delay_[i] = now + 90;
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
  if (editor.current_page() == PAGE_JAM) {
    led_pattern |= 1 << (part.step() & 0x7);
  } else if (editor.current_mode() == EDITOR_MODE_SEQUENCE) {
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
        editor.OnIncrement(e.value);
        break;

      case CONTROL_SWITCH:
        if (e.control_id <= SWITCH_LOAD_SAVE) {
          editor.OnSwitch(e);
        } else if (e.control_id == SWITCH_ENCODER) {
          if (e.value < 6) {
            editor.OnClick();
          } else {
            editor.OnLongClick();
          }
        } else {
          editor.OnProgrammerSwitch(e);
        }
        break;

      case CONTROL_POT:
        if (e.control_id == 35 &&
            part.system_settings().programmer == PROGRAMMER_XT) {
          editor.OnVolume(e.value);
        } else {
          editor.OnInput(e.control_id, e.value);
        }
        break;
    }
    idle_time_ = 0;
    refresh_display = true;
  }

  if (editor.current_page() != previous_page) {
    LockPotentiometers();
  }

  uint16_t pause_ms = ((part.system_settings().display_delay & 0xf) << 7) + 100;
  if (queue_.idle_time_ms() > pause_ms) {
    idle_time_ += queue_.idle_time_ms();
    queue_.Touch();
    refresh_display |= editor.Relax();
    bool show_screen_saver = idle_time_ >= 100000 && \
        (part.system_settings().display_delay & 0x10);
    if (show_screen_saver) {
      idle_time_ = 100000;
      editor.ScreenSaver();
    }
    if (part.dirty()) {
      refresh_display = true;
    }
  }
  
  if (queue_.idle_time_ms() > 80 &&
      (editor.FinishLoadingPatch() || part.dirty())) {
    queue_.Touch();
    refresh_display = true;
    idle_time_ = 0;
  }
  
  if (!encoder_.immediate_value() && freeze_display_) {
    refresh_display = false;
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
