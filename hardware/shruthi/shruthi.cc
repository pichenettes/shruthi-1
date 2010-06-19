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

#include "hardware/hal/adc.h"
#include "hardware/hal/audio_output.h"
#include "hardware/hal/devices/input_array.h"
#include "hardware/hal/devices/output_array.h"
#include "hardware/hal/devices/rotary_encoder.h"
#include "hardware/hal/devices/switch_array.h"
#include "hardware/hal/gpio.h"
#include "hardware/hal/init_atmega.h"
#include "hardware/hal/serial.h"
#include "hardware/hal/time.h"
#include "hardware/hal/timer.h"
#include "hardware/midi/midi.h"
#include "hardware/shruthi/display.h"
#include "hardware/shruthi/editor.h"
#include "hardware/shruthi/midi_in_dispatcher.h"
#include "hardware/shruthi/midi_out_filter.h"
#include "hardware/shruthi/storage.h"
#include "hardware/shruthi/synthesis_engine.h"
#include "hardware/utils/task.h"

using namespace hardware_hal;
using namespace hardware_midi;
using namespace hardware_shruthi;

using hardware_utils::NaiveScheduler;
using hardware_utils::Task;

// Midi input.
Serial<SerialPort1, 31250, BUFFERED, POLLED> midi_io;

// Input event handlers.
typedef MuxedAnalogInput<kPinAnalogInput> PotsMux;
typedef InputArray<PotsMux, kNumEditingPots, 8> Pots;

Pots pots;

// LED array.
OutputArray<
    Gpio<kPinLatch>,
    Gpio<kPinClk>,
    Gpio<kPinData>, kNumLeds, 4, MSB_FIRST, false> leds;

// Switches array
SwitchArray<
  Gpio<kPinLatch>,
  Gpio<kPinClk>,
  Gpio<kPinDigitalInput>,
  kNumSwitches,
  KEY_LOAD_SAVE> switches;

RotaryEncoderBuffer<RotaryEncoder<
    Gpio<kPinEncoderA>,
    Gpio<kPinEncoderB>,
    Gpio<kPinEncoderClick> > > encoder;

AudioOutput<PwmOutput<kPinVcoOut>, kAudioBufferSize, kAudioBlockSize> audio_out;
PwmOutput<kPinVcfCutoffOut> vcf_cutoff_out;
PwmOutput<kPinVcfResonanceOut> vcf_resonance_out;
PwmOutput<kPinVcaOut> vca_out;
PwmOutput<kPinCv1Out> cv_1_out;
PwmOutput<kPinCv2Out> cv_2_out;

MidiStreamParser<MidiInDispatcher> midi_parser;

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
  leds.Output();
}

void UpdateDisplayTask() {
  if (engine.dirty()) {
    editor.Refresh();
  }
  display.Tick();
}

void InputTask() {
  KeyEvent switch_event;
  Pots::Event pot_event;
  static uint8_t idle;
  static int8_t delta;
  static uint8_t previous_page;
TASK_BEGIN_NEAR
  while (1) {
    previous_page = editor.current_page();
    idle = 0;

    // Read the switches.
    switches.Read();
    
    // If a button was pressed, perform the action. Otherwise, if nothing
    // happened for 1.5s, update the idle flag.
    if (switches.idle_time() > (engine.system_settings().display_delay << 7)) {
      idle = 1;
    } else {
      if (switches.released()) {
        editor.HandleKeyEvent(switches.key_event());
      }
    }

    // Read the ADC.
    pot_event = pots.Read();
    PotsMux::set_pin(pots.active_input());

    // Update the editor if something happened.
    // Revert back to the main page when nothing happened for 1.5s.
    if (pot_event.event == EVENT_NONE) {
      if (idle &&
          pot_event.time > (engine.system_settings().display_delay << 7)) {
        editor.Relax();
      }
    } else {
      editor.HandleInput(pot_event.id, pot_event.value);
    }
    TASK_SWITCH;

    if (encoder.increment()) {
      switches.Touch();
      editor.HandleIncrement(encoder.increment());
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
    TASK_SWITCH;
  }
TASK_END
}

uint8_t current_cv;

void CvTask() {
  ++current_cv;
  if (current_cv >= kNumCvInputs) {
    current_cv = 0;
  }
  engine.set_cv(current_cv, Adc::Read(kPinCvInput + current_cv) >> 2);
}

void MidiTask() {
  // Try to process as much data as possible from the MIDI buffer.
  while (midi_io.readable()) {
    midi_parser.PushByte(midi_io.ImmediateRead());
  }
  // This is also a good place to do some MIDI output. But because the MIDI
  // output data rate can get intense when tweaking knobs, it's easier to
  // flush the data at a faster rate in the audio sample interrupt.
}

void AudioRenderingTask() {
  if (audio_out.writable_block()) {
    engine.Control();
    if (engine.voice(0).dead()) {
      for (uint8_t i = kAudioBlockSize; i > 0 ; --i) {
        audio_out.Overwrite(128);
      }
    } else {
      for (uint8_t i = kAudioBlockSize; i > 0 ; --i) {
        engine.Audio();
        audio_out.Overwrite(engine.voice(0).signal());
      }
    }
    vcf_cutoff_out.Write(engine.voice(0).cutoff());
    vcf_resonance_out.Write(engine.voice(0).resonance());
    vca_out.Write(engine.voice(0).vca());
    cv_1_out.Write(engine.voice(0).cv_1());
    cv_2_out.Write(engine.voice(0).cv_2());
  }
}

uint16_t previous_num_glitches;

// This task displays a '!' in the status area of the LCD displays whenever
// a discontinuity occurred in the audio rendering. Even if the code is
// optimized in such a way that it never occurs, I'd rather keep it here in
// case new features are implemented and need performance monitoring.
// This code uses 42 bytes.
void AudioGlitchMonitoringTask() {
  uint16_t num_glitches = audio_out.num_glitches();
  if (num_glitches != previous_num_glitches) {
    previous_num_glitches = num_glitches;
    display.set_status('!');
  }
}

typedef NaiveScheduler<kSchedulerNumSlots> Scheduler;

Scheduler scheduler;

/* static */
template<>
Task Scheduler::tasks_[] = {
    { &AudioRenderingTask, 16 },
    { &MidiTask, 6 },
    { &UpdateLedsTask, 4 },
    { &UpdateDisplayTask, 2 },
    { &AudioGlitchMonitoringTask, 1 },
    { &InputTask, 2 },
    { &CvTask, 1 },
};

inline void FlushMidiOut() {
  if (midi_out_filter.readable()) {
    if (midi_io.writable()) {
      midi_io.Overwrite(midi_out_filter.ImmediateRead());
    }
  }
}

uint8_t sub_clock = 0;
uint8_t sub_clock_2 = 0;

TIMER_2_TICK {
  audio_out.EmitSample();
  sub_clock = (sub_clock + 1) & 0x0f;
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
  scheduler.Init();
  audio_out.Init();
  
  // In case the bootloader has not done it, enable the pull-up on the MIDI in.
  DigitalInput<10>::EnablePullUpResistor();
  midi_io.Init();
  pots.Init();
  switches.Init();
  encoder.Init();
  leds.Init();
  
  // Initialize all the PWM outputs, in 31.25kHz, phase correct mode.
  Timer<0>::set_prescaler(1);
  Timer<0>::set_mode(TIMER_PWM_PHASE_CORRECT);
  Timer<1>::set_prescaler(1);
  Timer<1>::set_mode(TIMER_PWM_PHASE_CORRECT);
  Timer<2>::set_prescaler(1);
  Timer<2>::set_mode(TIMER_PWM_PHASE_CORRECT);
  Timer<2>::Start();
  
  vcf_cutoff_out.Init();
  vcf_resonance_out.Init();
  vca_out.Init();
  cv_1_out.Init();
  cv_2_out.Init();

  lcd.Init();
  display.Init();
  lcd.SetCustomCharMapRes(character_table[0], 8, 0);

  editor.Init();

  engine.Init();
  if (engine.system_settings().display_splash_screen) {
    editor.DisplaySplashScreen(STR_RES_V + 1);
  } else {
    editor.Refresh();
  }
}

int main(void) {
  InitAtmega(false);  // Do not initialize timers.
  Init();
  scheduler.Run();
}
