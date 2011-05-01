// Copyright 2011 Olivier Gillet.
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
#include "avrlib/gpio.h"
#include "avrlib/boot.h"
#include "avrlib/ring_buffer.h"
#include "dsp/audio_out.h"
#include "dsp/fx_engine.h"

using namespace dsp;
using namespace avrlib;

Gpio<PortD, 2> led_1;
Gpio<PortD, 3> led_2;

struct InputBufferSpecs {
  typedef uint8_t Value;
  enum {
    buffer_size = kAudioBufferSize,
    data_size = 8,
  };
};
RingBuffer<InputBufferSpecs> input_buffer;

Adc adc;

static uint8_t scanned_cv = 0;
static uint16_t cycle = 0;

// Called at 78kHz, 12us
TIMER_2_TICK {
  /*if (cycle & 1) {
    audio_out.EmitSample();
  }
  // This wait is only here to be on the safe side, since the conversion was
  // started 12us ago, and took 10us. It is thus complete except at warm up.
  adc.Wait();
  if (cycle & 1) {
    input_buffer.Overwrite(adc.ReadOut8());
    adc.StartConversion(scanned_cv + 1);
  } else {
    fx_engine.set_cv(scanned_cv, adc.ReadOut8());
    adc.StartConversion(0);
    ++scanned_cv;
    if (scanned_cv == kNumScannedCv) {
      scanned_cv = 0;
    }
  }*/
  ++cycle;
  led_1.set_value(cycle > 0x8000);
  led_2.set_value(cycle < 0x8000);
}

void Init() {
  sei();
  // Kill the UART.
  UCSR0B = 0;
  
  // Prescaler = 16, ADC clocked at 1.25 MHz.
  // ADC conversion time = 10us
  adc.set_prescaler(4);  
  adc.set_alignemnt(ADC_LEFT_ALIGNED);
  adc.Enable();
  
  // ADC warm-up.
  adc.StartConversion(0);
  adc.Wait();
  
  audio_out.Init();
  
  Timer<2>::set_prescaler(1);
  Timer<2>::set_mode(TIMER_FAST_PWM);
  Timer<2>::Start();
  
  led_1.set_mode(DIGITAL_OUTPUT);
  led_2.set_mode(DIGITAL_OUTPUT);
  led_1.Low();
  led_2.Low();
}

int main(void) {
  Init();
  while (1) {
   /* if (audio_out.writable_block() &&
        input_buffer.readable() == kAudioBufferSize) {
      uint8_t* data;
      data = fx_engine.mutable_buffer();
      for (uint8_t i = 0; i < kAudioBufferSize; ++i) {
        *data++ = input_buffer.ImmediateRead();
      }
      fx_engine.ProcessBlock();
      data = fx_engine.mutable_buffer();
      for (uint8_t i = 0; i < kAudioBufferSize; ++i) {
        audio_out.Overwrite(*data++);
      }
    }*/
  }
}
