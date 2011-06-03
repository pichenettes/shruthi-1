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

#include "dsp/dsp.h"

#include "avrlib/adc.h"
#include "avrlib/gpio.h"
#include "avrlib/serial.h"
#include "avrlib/spi.h"
#include "dsp/buffers.h"
#include "dsp/fx_engine.h"

using namespace dsp;
using namespace avrlib;

Gpio<PortD, 2> led_in;
Gpio<PortD, 3> led_out;

Serial<SerialPort0, 115200, BUFFERED, DISABLED> cv_io;

Adc adc;
SpiMaster<NumberedGpio<10>, MSB_FIRST, 2> dac_interface;

static uint8_t dac_word[2];

#ifdef USE_ANALOG_CV
//
//      /\
//    / ! \    This code is deprecated and ugly.
//  /______\
// 
static uint8_t scanned_cv = 0;
static uint8_t cycle = 0;
TIMER_2_TICK {
  if (cycle & 1) {
    uint8_t value = adc.ReadOut8();
    input_buffer.Overwrite(value);
    adc.StartConversion(scanned_cv + 1);
    dac_interface.Strobe();
    led_in.set_value(value > 192);
    dac_interface.Overwrite(dac_word[0]);
    Word x;
    x.value = output_buffer.ImmediateRead();
    dac_word[0] = x.bytes[1] | 0x70;
    dac_interface.Overwrite(dac_word[1]);
    dac_word[1] = x.bytes[0];
  } else {
    fx_engine.set_cv(scanned_cv, adc.ReadOut8());
    adc.StartConversion(0);
    ++scanned_cv;
    if (scanned_cv == kNumScannedCv) {
      scanned_cv = 0;
    }
  }
  ++cycle;
}

#define TIMER_RATE TIMER_FAST_PWM

#else

TIMER_2_TICK {
  uint8_t value = adc.ReadOut8();
  input_buffer.Overwrite(value);
  adc.StartConversion(0);
  dac_interface.Strobe();
  led_in.set_value(value > 192);
  dac_interface.Overwrite(dac_word[0]);
  // Writing a byte to the DAC takes 10 CPU cycles (we are working at the
  // fastest SPI speed allowed). While the next statements are running, the
  // hardware SPI unit is shifting out the first byte.
  Word x;
  x.value = output_buffer.ImmediateRead();
  // Convert to 12 bits and write to DAC
  led_out.set_value(x.bytes[1] > 8);
  dac_word[0] = x.bytes[1] | 0x70;
  // At this stage, we can assume that the first byte has been written, so we
  // shift the second one without checking the transmission status byte.
  dac_interface.Overwrite(dac_word[1]);
  dac_word[1] = x.bytes[0];
}

#define TIMER_RATE TIMER_PWM_PHASE_CORRECT

#endif  // USE_ANALOG_CV

void Init() {
  sei();
  // Kill the UART.
  UCSR0B = 0;
  dac_interface.Init();
  cv_io.Init();
  dac_interface.WriteWord(0, 0);
  
  led_in.set_mode(DIGITAL_OUTPUT);
  led_out.set_mode(DIGITAL_OUTPUT);
  
  // Prescaler = 16, ADC clocked at 1.25 MHz.
  // ADC conversion time = 10us
  adc.set_prescaler(4);  
  adc.set_alignment(ADC_LEFT_ALIGNED);
  adc.Enable();
  fx_engine.Init();
  
  // ADC warm-up.
  adc.StartConversion(0);
  adc.Wait();
  
  Timer<2>::set_prescaler(1);
  Timer<2>::set_mode(TIMER_RATE);
  Timer<2>::Start();
}

static uint8_t cv_io_round_robin = 0xff;
static uint8_t cv_io_byte = 0;

void ParseCvIo() {
  while (cv_io.readable()) {
    uint8_t value = cv_io.ImmediateRead();
    // We are in sync with the transmit cycle.
    if (cv_io_round_robin != 0xff) {
      
      if (cv_io_byte == 0) {
        switch (cv_io_round_robin) {
          case 0:
            if (value != 0xff) {
              // WTF? We have lost sync.
              cv_io_round_robin = 0xff;
            }
            break;
          case 1:
            fx_engine.set_mode_byte(value);
            break;
          case 2:
            fx_engine.set_tempo(value);
            break;
          case 3:
            fx_engine.set_cv(CV_RESONANCE, value);
            break;
          case 4:
            fx_engine.set_cv(CV_1, value);
            break;
          case 5:
            fx_engine.set_cv(CV_2, value);
            break;
        }
      } else {
        fx_engine.set_cv(CV_CUTOFF + (cv_io_round_robin & 1), value);
      }
      cv_io_byte = (cv_io_byte + 1) & 1;
      if (!cv_io_byte) {
        ++cv_io_round_robin;
        if (cv_io_round_robin == 6) {
          cv_io_round_robin = 0;
        }
      } 
    } else {
      // We are not in sync yet, but we have identified the beginning of a
      // transmission sequence.
      if (value == 0xff) {
        cv_io_round_robin = 0;
        cv_io_byte = 1;
      }
    }
  }
}

void FillAudioBuffer() {
  while (output_buffer.writable() >= kAudioBlockSize &&
         input_buffer.readable() >= kAudioBlockSize) {
    // We use the TX pin on the board to time the audio processing code.
    NumberedGpio<1> tx;
    tx.set_mode(DIGITAL_OUTPUT);  
    tx.High();
    fx_engine.ProcessBlock();
    tx.Low();
  }
}

int main(void) {
  Init();
  while (1) {
    FillAudioBuffer();
    ParseCvIo();
  }
}
