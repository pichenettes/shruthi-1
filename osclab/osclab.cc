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
#include "avrlib/gpio.h"
#include "avrlib/boot.h"
#include "avrlib/string.h"
#include "avrlib/time.h"
#include "avrlib/timer.h"
#include "osclab/audio_out.h"
#include "osclab/display.h"
#include "osclab/oscillator.h"
#include "osclab/resources.h"

using namespace avrlib;
using namespace osclab;

typedef AdcInputScanner AnalogInputs;
typedef InputArray<AnalogInputs, 4, 8> Pots;

AnalogInputs analog_inputs;
Pots pots;

PwmOutput<kPinVcfCutoffOut> vcf_cutoff_out;
PwmOutput<kPinVcfResonanceOut> vcf_resonance_out;
PwmOutput<kPinVcaOut> vca_out;

Gpio<PortD, 3> tick;

uint8_t sub_clock = 0;
uint8_t sub_clock_2 = 0;

TIMER_2_TICK {
  audio_out.EmitSample();
  sub_clock = (sub_clock + 1) & 0x0f;
  if (sub_clock == 0) {
    lcd.Tick();
    sub_clock_2 = ~sub_clock_2;
    if (sub_clock_2) {
      TickSystemClock();
    }
  }
}

void UpdateDisplay() {
  display.Tick();
}

static uint8_t settings[4] = { 60, 0, 0, 2 };
static char line_buffer[17];

void ProcessInput() {
  Pots::Event pot_event;
  static uint8_t idle;
  static int8_t delta;
  static uint8_t previous_page;
  
  analog_inputs.Scan();
  pot_event = pots.Read();
  if (pot_event.event != EVENT_NONE) {
    memset(line_buffer, ' ', 16);
    settings[pot_event.id] = pot_event.value >> 3;
    if (pot_event.id == 3) {
      settings[3] >>= 2;
    }
    char* p = line_buffer + 1;
    for (uint8_t i = 0; i < 3; ++i) {
      UnsafeItoa<int16_t>(settings[i], 3, p);
      AlignRight(p, 3);
      p += 4;
    }
    osclab::ResourcesManager::LoadStringResource(STR_RES_NONE + settings[3], p, 3);
    AlignRight(p, 3);
    display.Print(1, line_buffer);
    memcpy_P(line_buffer, PSTR(" coa fin prm wav"), 16);
    display.Print(0, line_buffer);
  }
}

static uint8_t audio_buffer[kAudioBlockSize];
static uint8_t sync_state[kAudioBlockSize];
static const int16_t kLowestNote = 0 * 128;
static const int16_t kHighestNote = 128 * 128;
static const int16_t kOctave = 12 * 128;
static const int16_t kPitchTableStart = 116 * 128;
static Oscillator<1> osc;

void RenderAudio() {
  if (audio_out.writable_block()) {
    int16_t pitch = (settings[0] << 7) | settings[1];
    while (pitch >= kHighestNote) {
      pitch -= kOctave;
    }
    // Extract the pitch increment from the pitch table.
    int16_t ref_pitch = pitch - kPitchTableStart;
    uint8_t num_shifts = 0;
    while (ref_pitch < 0) {
      ref_pitch += kOctave;
      ++num_shifts;
    }
    uint24_t increment;
    increment.integral = osclab::ResourcesManager::Lookup<uint16_t, uint16_t>(
        lut_res_oscillator_increments, ref_pitch >> 1);
    increment.fractional = 0;
    // Divide the pitch increment by the number of octaves we had to transpose
    // to get a value in the lookup table.
    while (num_shifts--) {
      increment = U24ShiftRight(increment);
    }

    // Now the oscillators can recompute all their internal variables!
    int8_t midi_note = U15ShiftRight7(pitch);
    if (midi_note < 12) {
      midi_note = 12;
    }
    osc.set_parameter(settings[2]);
    tick.High();
    osc.Render(settings[3], midi_note, increment, sync_state, audio_buffer);
    tick.Low();
    for (uint8_t i = 0; i < kAudioBlockSize; ++i) {
      audio_out.Overwrite(audio_buffer[i]);
    }
  }
}

void Init() {
  sei();
  UCSR0B = 0;
  UCSR1B = 0;
  
  audio_out.Init();
  analog_inputs.set_num_inputs(4);
  pots.Init();
  tick.set_mode(DIGITAL_OUTPUT);
  
  // Initialize all the PWM outputs to 39kHz, phase correct mode.
  Timer<0>::set_prescaler(1);
  Timer<0>::set_mode(TIMER_PWM_PHASE_CORRECT);
  Timer<1>::set_prescaler(1);
  Timer<1>::set_mode(TIMER_PWM_PHASE_CORRECT);
  Timer<2>::set_prescaler(1);
  Timer<2>::set_mode(TIMER_PWM_PHASE_CORRECT);
  Timer<2>::Start();
  
  lcd.Init();
  display.Init();
  
  vcf_cutoff_out.Init();
  vcf_resonance_out.Init();
  vca_out.Init();
  vcf_cutoff_out.Write(255);
  vcf_resonance_out.Write(0);
  vca_out.Write(255);
}

int main(void) {
  Init();
  while (1) {
    UpdateDisplay();
    ProcessInput();
    RenderAudio();
  }
}
