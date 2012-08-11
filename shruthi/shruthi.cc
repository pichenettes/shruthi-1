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

#include "avrlib/adc.h"
#include "avrlib/deprecated/devices/input_array.h"
#include "avrlib/deprecated/devices/output_array.h"
#include "avrlib/deprecated/devices/switch_array.h"
#include "avrlib/devices/external_eeprom.h"
#include "avrlib/devices/rotary_encoder.h"
#include "avrlib/gpio.h"
#include "avrlib/boot.h"
#include "avrlib/serial.h"
#include "avrlib/time.h"
#include "avrlib/timer.h"
#include "midi/midi.h"
#include "shruthi/audio_out.h"
#include "shruthi/display.h"
#include "shruthi/editor.h"
#include "shruthi/midi_dispatcher.h"
#include "shruthi/storage.h"
#include "shruthi/synthesis_engine.h"

using namespace avrlib;
using namespace midi;
using namespace shruthi;

// Midi input.
Serial<MidiPort, 31250, POLLED, POLLED> midi_io;
Serial<CvTxPort, 115200, DISABLED, POLLED> cv_io;
RingBuffer<SerialInput<MidiPort> > midi_buffer;

// Input event handlers.
typedef AdcInputScanner AnalogInputs;
typedef InputArray<AnalogInputs, kNumEditingPots, 8> Pots;

Pots pots;
AnalogInputs analog_inputs;

// LED array.
OutputArray<
  IOEnableLine, IOClockLine, IOOutputLine, kNumLeds, 4, MSB_FIRST, false> leds;

IOEnableLineAux aux_ss;

// Switches array
SwitchArray<
  IOEnableLine, IOClockLine, IOInputLine, kNumSwitches, KEY_LOAD_SAVE> switches;

RotaryEncoderTracker<RotaryEncoder<
  EncoderALine, EncoderBLine, EncoderClickLine> > encoder;

PwmOutput<kPinVcfCutoffOut> vcf_cutoff_out;
PwmOutput<kPinVcfResonanceOut> vcf_resonance_out;
PwmOutput<kPinVcaOut> vca_out;
PwmOutput<kPinCv1Out> cv_1_out;
PwmOutput<kPinCv2Out> cv_2_out;

MidiStreamParser<MidiDispatcher> midi_parser;

uint8_t programmer_active_pot = 0;
uint32_t last_input_event_time = 0;

bool aux_uart_enabled = false;

// What follows is a list of "tasks" - short functions handling a particular
// aspect of the synth (rendering audio, updating the LCD display, etc). they
// are called in sequence, with some tasks being more frequently called than
// others, by the Scheduler.
void UpdateLedsTask() {
  // Since the LCD and the shift register are sharing some lines, make sure that
  // the LCD is not currently writing some data before doing some stuff with
  // the shift register.
  leds.Clear();
  if (editor.current_page() == PAGE_PERFORMANCE) {
    // x0x-style chasing lights.
    leds.set_value(engine.voice_controller().step() & 0x07, 15);
  } else {
    // Sequencer blinky on MODE LED.
    if (editor.current_mode() == EDITOR_MODE_SEQUENCE) {
      if (engine.voice_controller().active()) {
        if (!(engine.voice_controller().step() & 3)) {
          leds.set_value(LED_MODE, engine.voice_controller().step() ? 1 : 15);
        }
      }
    } else {
      // MODE LED is on, but the modulation matrix LED can go blink...
      leds.set_value(LED_MODE, 15);
      if (editor.current_page() == PAGE_MOD_MATRIX) {
        uint8_t current_modulation_source_value = engine.modulation_source(0,
            engine.patch().modulation_matrix.modulation[
                editor.subpage()].source);
        leds.set_value(LED_6, current_modulation_source_value >> 4);
      }
      if (editor.current_page() == PAGE_MOD_OPERATORS) {
        uint8_t current_operator_value = engine.modulation_source(0,
            MOD_SRC_OP_1 + editor.subpage());
        leds.set_value(LED_6, current_operator_value >> 4);
      }
    }
    uint8_t pattern = editor.leds_pattern();
    uint8_t mask = 1;
    for (uint8_t i = 0; i < 8; ++i) {
      if (pattern & mask) {
        leds.set_value(i, 15);
      }
      mask <<= 1;
    }
  }
  
  uint8_t filter_board = engine.system_settings().expansion_filter_board;
  leds.Begin();
  if (filter_board == FILTER_BOARD_DLY) {
    Word w;
    w.value = U8U8Mul(engine.voice().cv_1(), 5);
    cv_io.Disable();
    aux_ss.High();
    aux_uart_enabled = false;
    leds.ShiftOutByte(w.bytes[1] | 0x90);
    aux_ss.Low();
    leds.ShiftOutByte(w.bytes[0]);
    w.value = U8U8Mul(pgm_read_byte(wav_res_ssm2164_linearization + \
        (engine.voice().cv_2() >> 2)), 16);
    leds.ShiftOutByte(w.bytes[1] | 0x10);
    aux_ss.High();
    aux_ss.Low();
    leds.ShiftOutByte(w.bytes[0]);
  }
  
  if (filter_board == FILTER_BOARD_SVF) {
    leds.ShiftOutByte(engine.svf_routing_byte());
  }
  if (filter_board == FILTER_BOARD_PVK) {
    leds.ShiftOutByte(engine.pvk_routing_byte());
  }
  if (filter_board == FILTER_BOARD_4PM) {
    leds.ShiftOutByte(engine.four_pole_routing_byte());
  }
  if (engine.system_settings().expansion_cv_mode == CV_MODE_PROGRAMMER) {
    leds.ShiftOutByte(programmer_active_pot);
  }
  leds.ShiftOut();
  aux_ss.High();
  leds.End();
}

void UpdateDisplayTask() {
  // Check if some patch settings have been modified by a SysEx or NRPN. If this
  // is the case, refresh the content of the LCD display.
  if (engine.dirty()) {
    editor.Refresh();
  }
  // The display can now blink the cursor and/or output modified characters.
  display.Tick();
}

uint8_t previous_page;

void SwitchesTask() {
  uint8_t idle;
  Pots::Event pot_event;
  
  previous_page = editor.current_page();
  idle = 0;

  // Read the switches.
  switches.Read();
  
  // If a button was pressed, perform the action. Otherwise, if nothing
  // happened for 1.5s, update the idle flag.
  if (switches.idle_time() > (engine.system_settings().display_delay << 7)) {
    idle = 1;
  } else {
    KeyEvent e = switches.key_event();
    if (e.id != KEY_NONE) {
      editor.HandleKeyEvent(e);
    }
  }

  // Read the ADC.
  analog_inputs.Scan();
  pot_event = pots.Read();

  // Update the editor if something happened.
  // Revert back to the main page when nothing happened for 1.5s.
  if (pot_event.event == EVENT_NONE) {
    if (idle && 
        milliseconds() - last_input_event_time >
          (engine.system_settings().display_delay << 7)) {
      editor.Relax();
    }
  } else {
    last_input_event_time = milliseconds();
    editor.HandleInput(pot_event.id, pot_event.value);
  }
}

void EncoderTask() {
  if (encoder.increment()) {
    switches.Touch();
    int8_t increment = encoder.increment();
    if (switches.shifted()) {
      switches.InhibitShiftRelease();
      increment *= 10;
    }
    editor.HandleIncrement(increment);
  } else {
    if (encoder.clicked()) {
      switches.Touch();
      editor.HandleClick();
    }
  }
  encoder.Flush();
  // In case we have moved to a different page, make the pots less sensitive
  // to changes to make sure that a subtle change to a pot won't create a
  // discontinuity.
  if (editor.current_page() != previous_page) {
    pots.Lock(32);
  }
}

void CvTask() {
  static uint8_t current_cv;
  static uint8_t programmer_counter = 0;
  static uint8_t currently_tweaked_pot;
  static int16_t pots_value[32];

  analog_inputs.Scan();
  if (engine.system_settings().expansion_cv_mode == CV_MODE_4CV_IN) {
    analog_inputs.set_num_inputs(8);
    ++current_cv;
    if (current_cv >= kNumCvInputs) {
      current_cv = 0;
    }
    engine.set_modulation_source(
        MOD_SRC_CV_1 + current_cv,
        analog_inputs.Read(kPinCvInput + current_cv) >> 2);
  } else if (engine.system_settings().expansion_cv_mode == CV_MODE_PROGRAMMER) {
    analog_inputs.set_num_inputs(4);
    int16_t value = analog_inputs.Sync(kPinCvInput);
    // Read the pot selected on the multiplexer. If it has been touched, 
    // change the corresponding parameter in the editor, and instruct the
    // scanner to spend more time scanning this pot.
    if ((pots_value[programmer_active_pot] - value > 8) ||
        (pots_value[programmer_active_pot] - value < -8)) {
      engine.SetScaledParameter(programmer_active_pot, value >> 3, 1);
      // Show tweaked param on display
      editor.HandleProgrammerInput(programmer_active_pot, value);
      last_input_event_time = milliseconds();
      currently_tweaked_pot = programmer_active_pot;
      pots_value[programmer_active_pot] = value;
    }
    ++programmer_counter;
    if (programmer_counter & 1) {
      programmer_active_pot = currently_tweaked_pot;
    } else {
      programmer_active_pot = (programmer_counter >> 1) & 0x1f;
    }
  } else {
    analog_inputs.set_num_inputs(7);
    uint8_t value = analog_inputs.Read(kPinCvInput + current_cv) >> 2;
    if (current_cv <= 1) {
      value >>= 1;
      uint8_t offset = current_cv * 4;
      engine.SetParameter(PRM_OSC_PARAMETER_1 + offset, value, 1);
      ++current_cv;
    } else {
      engine.set_unregistered_modulation_source(0, value);
      current_cv = 0;
    }
  }
}

void MidiTask() {
  // Try to process as much data as possible from the MIDI buffer.
  while (midi_buffer.readable()) {
    midi_parser.PushByte(midi_buffer.ImmediateRead());
  }
  // This is also a good place to do some MIDI output. But because the MIDI
  // output data rate can get intense when tweaking knobs, it's easier to
  // flush the data at a faster rate in the audio sample interrupt.
}

void AudioRenderingTask() {
  static uint8_t cv_io_round_robin = 0;

  // Run only when there's a block of 40 samples to fill...
  if (audio_out.writable_block()) {
    engine.ProcessBlock();
    uint8_t v;
#ifndef SERIAL_PATCH_DUMP
    if (engine.system_settings().expansion_filter_board == FILTER_BOARD_DSP) {
      if (!aux_uart_enabled) {
        cv_io.Init();
        aux_uart_enabled = true;
      }
      // Shove two bytes to the serial output used for transmitting CVs to the
      // digital filter board.
      if (cv_io_round_robin == 0) {
        cv_io.Overwrite(0xff);
      } else if (cv_io_round_robin == 1) {
        cv_io.Overwrite(engine.fx_control_byte());
      } else if (cv_io_round_robin == 2) {
        cv_io.Overwrite(engine.sequencer_settings().seq_tempo);
      } else {
        v = engine.voice().modulation_destination(
            MOD_DST_FILTER_RESONANCE + cv_io_round_robin - 3);
        if (v == 0xff) {
          v = 0xfe;
        }
        cv_io.Overwrite(v);
      }
      v = engine.voice().modulation_destination(
          MOD_DST_FILTER_CUTOFF + (cv_io_round_robin & 1));
      if (v == 0xff) {
        v = 0xfe;
      }
      cv_io.Overwrite(v);
      cv_io_round_robin = (cv_io_round_robin + 1);
      if (cv_io_round_robin == 6) {
        cv_io_round_robin = 0;
      }
    }
#endif  // SERIAL_PATCH_DUMP
    vcf_cutoff_out.Write(engine.voice().cutoff());
    uint8_t filter_board = engine.system_settings().expansion_filter_board;
    uint8_t resonance = engine.voice().resonance();
    uint8_t gain = engine.voice().vca();
    uint8_t cv_1 = engine.voice().cv_1();
    uint8_t cv_2 = engine.voice().cv_2();
    if (filter_board == FILTER_BOARD_PVK) {
      // Mirror unprocessed Cutoff/Resonance values for Shruthi-XP.
      if (engine.system_settings().expansion_cv_mode == CV_MODE_PROGRAMMER) {
        uint8_t adjusted_cutoff = engine.voice().cutoff();
        if (adjusted_cutoff > 24) {
          adjusted_cutoff -= 24;
        } else {
          adjusted_cutoff = 0;
        }
        cv_1 = resonance;
        cv_2 = adjusted_cutoff;
      }
      // Apply a knee to the resonance curve.
      resonance = (resonance >> 1) + (resonance < 128 ? resonance : 128);
      if (resonance >= 252) {
        resonance = 255;
      }
    } else if (filter_board == FILTER_BOARD_DLY) {
      uint8_t level = engine.patch().filter_1_mode_;
      uint8_t tilt = engine.patch().filter_2_mode_ << 1;
      uint8_t gain;
      gain = U8U8Mul(level, tilt < 16 ? tilt : 16);
      cv_2 = pgm_read_byte(wav_res_ssm2164_linearization + (gain >> 2));
      gain = U8U8Mul(level, tilt > 16 ? (30 - tilt) : 16);
      cv_1 = pgm_read_byte(wav_res_ssm2164_linearization + (gain >> 2));
      // Apply a knee to the resonance curve.
      resonance = ~resonance;
      resonance = U8U8MulShift8(resonance, resonance);
      resonance = U8U8MulShift8(~resonance, 160) + 48;
    } if (filter_board == FILTER_BOARD_4PM) {
      // Mirror unprocessed Cutoff/Resonance values for Shruthi-XP.
      if (engine.system_settings().expansion_cv_mode == CV_MODE_PROGRAMMER) {
        cv_1 = resonance;
        cv_2 = engine.voice().cutoff();
      }
      // If the resonance overdrive mode is not selected, half the scale of
      // the resonance setting. Resonance overdrive needs a very strong control
      // current on the OTA to kick in.
      if ((engine.patch().filter_2_mode_ & 1) == 0) {
        resonance = U8U8MulShift8(resonance, 92);
      } else {
        gain = ~gain;
        gain = U8U8MulShift8(gain, gain);
        gain = ~gain;
      }
    }
    vcf_resonance_out.Write(resonance);
    vca_out.Write(gain);
    cv_1_out.Write(cv_1);
    cv_2_out.Write(cv_2);
  }
}

// This task displays a '!' in the status area of the LCD whenever
// a discontinuity occurred in the audio rendering. Even if the code is
// optimized in such a way that it never occurs, I'd rather keep it here in
// case new features are implemented and need performance monitoring.
// This code uses 22 bytes.
void AudioGlitchMonitoringTask() {
  if (audio_out.num_glitches()) {
    audio_out.ResetGlitchCounter();
    display.set_status('!');
  }
}

inline void FlushMidiOut() {
  if (midi_dispatcher.readable()) {
    if (midi_io.writable()) {
      midi_io.Overwrite(midi_dispatcher.ImmediateRead());
    }
  }
}

TIMER_2_TICK {
  static uint8_t sub_clock = 0;
  static uint8_t sub_clock_2 = 0;

  audio_out.EmitSample();
  sub_clock = (sub_clock + 1) & 0x0f;
  if (midi_io.readable()) {
    midi_buffer.NonBlockingWrite(midi_io.ImmediateRead());
  }
  if (sub_clock == 0) {
    lcd.Tick();
    encoder.Read();
    // Flush to the output the buffered MIDI data.
    FlushMidiOut();
    sub_clock_2 = ~sub_clock_2;
    if (sub_clock_2) {
      TickSystemClock();
    }
  }
}

void Init() {
  sei();
  audio_out.Init();
  midi_io.Init();
  pots.Init();
  switches.Init();
  encoder.Init();
  leds.Init();
  
  // Initialize all the PWM outputs to 39kHz, phase correct mode.
  Timer<0>::set_prescaler(1);
  Timer<0>::set_mode(TIMER_PWM_PHASE_CORRECT);
  Timer<1>::set_prescaler(1);
  Timer<1>::set_mode(TIMER_PWM_PHASE_CORRECT);
  Timer<2>::set_prescaler(1);
  Timer<2>::set_mode(TIMER_PWM_PHASE_CORRECT);
  Timer<2>::Start();
  aux_ss.set_mode(DIGITAL_OUTPUT);
  
  vcf_cutoff_out.Init();
  vcf_resonance_out.Init();
  vca_out.Init();
  cv_1_out.Init();
  cv_2_out.Init();

  lcd.Init();
  display.Init();
  lcd.SetCustomCharMapRes(character_table[0], 7, 1);
  editor.Init();
  Storage::Init();

  engine.Init();

  // If the encoder is pressed at startup, toggle the "Boot on patch page"
  // flag.
  if (encoder.immediate_value() == 0) {
    engine.mutable_system_settings()->patch_restore_on_boot ^= 0x8000;
    engine.system_settings().EepromSave();
  }
  
  // When booting on the patch page, jump to the patch page and restore the
  // previously loaded patch.
  if (engine.system_settings().patch_restore_on_boot & 0x8000) {
    editor.BootOnPatchBrowsePage(
        engine.system_settings().patch_restore_on_boot & 0x7fff);
  } else {
    editor.DisplaySplashScreen(STR_RES_V + 1);
  }
}

typedef void (*Task)();

Task task_sequence[] = {
  &AudioGlitchMonitoringTask,
  &UpdateLedsTask,
  &SwitchesTask,
  &UpdateDisplayTask,
  &UpdateLedsTask,

  &CvTask,
  &UpdateLedsTask,
  &EncoderTask,
  &UpdateDisplayTask,
  &UpdateLedsTask,
};

int main(void) {
  Init();
  uint8_t task = 0;
  while (1) {
    AudioRenderingTask();
    MidiTask();
    AudioRenderingTask();
    task_sequence[task]();
    ++task;
    if (task >= sizeof(task_sequence) / sizeof(Task)) {
      task = 0;
    }
  }
}
