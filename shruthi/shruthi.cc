// Copyright 2009 Emilie Gillet.
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

#include "avrlib/devices/external_eeprom.h"
#include "avrlib/gpio.h"
#include "avrlib/boot.h"
#include "avrlib/serial.h"
#include "avrlib/timer.h"
#include "midi/midi.h"
#include "shruthi/audio_out.h"
#include "shruthi/midi_dispatcher.h"
#include "shruthi/part.h"
#include "shruthi/storage.h"
#include "shruthi/ui.h"

using namespace avrlib;
using namespace midi;
using namespace shruthi;

Serial<MidiPort, 31250, POLLED, POLLED> midi_io;
Serial<CvTxPort, 115200, DISABLED, POLLED> cv_io;
RingBuffer<SerialInput<MidiPort> > midi_buffer;

PwmOutput<kPinVcfCutoffOut> vcf_cutoff_out;
PwmOutput<kPinVcfResonanceOut> vcf_resonance_out;
PwmOutput<kPinVcaOut> vca_out;
PwmOutput<kPinCv1Out> cv_1_out;
PwmOutput<kPinCv2Out> cv_2_out;

MidiStreamParser<MidiDispatcher> midi_parser;

bool aux_uart_enabled = false;

ISR(TIMER2_OVF_vect) {
  static uint8_t clock_divider_midi = 0;
  static uint8_t clock_divider_ui = 0;

  // 40kHz: audio sample
  audio_out.EmitSample();

  // 10kHz: MIDI I/O
  --clock_divider_midi;
  if (!clock_divider_midi) {
    if (midi_io.readable()) {
      midi_buffer.NonBlockingWrite(midi_io.ImmediateRead());
    }
    if (midi_dispatcher.readable()) {
      if (midi_io.writable()) {
        midi_io.Overwrite(midi_dispatcher.ImmediateRead());
      }
    }
    clock_divider_midi = 4;
  }
  
  // 2.0kHz: UI polling
  --clock_divider_ui;
  if (!clock_divider_ui) {
    clock_divider_ui = 20;
    
    // The absolutely insane line of code that follows deserves a comment.
    // Ideally, we would have written: ui.Poll() to call the UI polling
    // routine. The problem is that the code in ui.Poll() thrash almost all
    // registers. gcc would have detected this and would have made sure that
    // (almost) all registers would have been pushed/popped in this ISR
    // prelude/postlude. As a result, 19 out 20 calls to this ISR, we
    // push/pop a dozen of registers for absolutely no useful purpose. This has
    // a cost of 40 CPU cycles per sample, and we don't want to spend that.
    // We want ui.Poll() [and all the necessary push/pop] to run in a different
    // context than this ISR - but still outside of the main loop.
    // Ideally, we would have loved to use user interrupts for that, but the AVR
    // doesn't have anything like this, so we enable a timer interrupt to jump
    // into its ISR ASAP...
    Timer<1>::Start();
  }
}

ISR(TIMER1_OVF_vect, ISR_NOBLOCK) {
  // ... and we disable the timer immediately!
  Timer<1>::Stop();
  ui.Poll();
}

void DSPFilterBoardWrite() {
  static uint8_t cv_io_round_robin = 0;
  
  uint8_t v;
  if (!aux_uart_enabled) {
    cv_io.Init();
    aux_uart_enabled = true;
  }
  
  // Shove two bytes to the serial output used for transmitting CVs to the
  // digital filter board.
  if (cv_io_round_robin == 0) {
    cv_io.Overwrite(0xff);
  } else if (cv_io_round_robin == 1) {
    cv_io.Overwrite(part.fx_control_byte());
  } else if (cv_io_round_robin == 2) {
    cv_io.Overwrite(part.sequencer_settings().seq_tempo);
  } else {
    v = part.voice().modulation_destination(
        MOD_DST_FILTER_RESONANCE + cv_io_round_robin - 3);
    if (v == 0xff) {
      v = 0xfe;
    }
    cv_io.Overwrite(v);
  }
  v = part.voice().modulation_destination(
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

void FillAudioBuffer() {
  if (!audio_out.writable_block()) {
    return;
  }

  part.ProcessBlock();
  uint8_t filter_board = part.system_settings().expansion_filter_board;
  uint8_t resonance = part.voice().resonance();
  uint8_t gain = part.voice().vca();
  uint8_t cv_1 = part.voice().cv_1();
  uint8_t cv_2 = part.voice().cv_2();
  vcf_cutoff_out.Write(part.voice().cutoff());

  if (filter_board == FILTER_BOARD_DSP) {
    DSPFilterBoardWrite();
  } else if (filter_board == FILTER_BOARD_PVK) {
    // Mirror unprocessed Cutoff/Resonance values for Shruthi-XP.
    if (part.system_settings().programmer == PROGRAMMER_FCD) {
      uint8_t adjusted_cutoff = part.voice().cutoff();
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
    if (aux_uart_enabled) {
      cv_io.Disable();
      aux_uart_enabled = false;
    }
    uint8_t level = part.patch().filter_1_mode_;
    uint8_t tilt = part.patch().filter_2_mode_ << 1;
    uint8_t gain;
    gain = U8U8Mul(level, tilt < 16 ? tilt : 16);
    cv_2 = pgm_read_byte(wav_res_ssm2164_linearization + (gain >> 2));
    gain = U8U8Mul(level, tilt > 16 ? (30 - tilt) : 16);
    cv_1 = pgm_read_byte(wav_res_ssm2164_linearization + (gain >> 2));
    // Apply a knee to the resonance curve.
    resonance = ~resonance;
    resonance = U8U8MulShift8(resonance, resonance);
    resonance = U8U8MulShift8(~resonance, 160) + 48;
  } else if (filter_board == FILTER_BOARD_4PM) {
    // Mirror unprocessed Cutoff/Resonance values for Shruthi-XP.
    if (part.system_settings().programmer == PROGRAMMER_FCD) {
      cv_1 = resonance;
      cv_2 = part.voice().cutoff();
    }
    // If the resonance overdrive mode is not selected, half the scale of
    // the resonance setting. Resonance overdrive needs a very strong control
    // current on the OTA to kick in.
    if ((part.patch().filter_2_mode_ & 1) == 0) {
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
  
  if (audio_out.num_glitches()) {
    audio_out.ResetGlitchCounter();
    display.set_status('!');
  }
}

void ProcessMidi() {
  while (midi_buffer.readable()) {
    midi_parser.PushByte(midi_buffer.ImmediateRead());
  }
}

void Init() {
  sei();
  audio_out.Init();
  midi_io.Init();
  
  // Initialize all the PWM outputs to 39kHz, phase correct mode.
  Timer<0>::set_prescaler(1);
  Timer<0>::set_mode(TIMER_PWM_PHASE_CORRECT);
  Timer<1>::set_prescaler(1);
  Timer<1>::set_mode(TIMER_PWM_PHASE_CORRECT);
  Timer<2>::set_prescaler(1);
  Timer<2>::set_mode(TIMER_PWM_PHASE_CORRECT);
  
  vcf_cutoff_out.Init();
  vcf_resonance_out.Init();
  vca_out.Init();
  cv_1_out.Init();
  cv_2_out.Init();

  ui.Init();
  Storage::Init();
  part.Init();
  
  ui.ShowSplash();
  Timer<2>::Start();
}

int main(void) {
  Init();
  while (1) {
    FillAudioBuffer();
    ProcessMidi();
    ui.DoEvents();
  }
}
