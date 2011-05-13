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
#include "avrlib/boot.h"
#include "avrlib/gpio.h"
#include "avrlib/op.h"
#include "avrlib/ring_buffer.h"
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

static uint8_t scanned_cv = 0;
static uint8_t cycle = 0;
static uint8_t byte_a, byte_b;

#ifdef USE_ANALOG_CV

TIMER_2_TICK {
  // This wait is only here to be on the safe side, since the conversion was
  // started 12us ago, and took 10us. It is thus complete except at warm up.
  // adc.Wait();
  if (cycle & 1) {
    uint8_t value = adc.ReadOut8();
    input_buffer.Overwrite(value);
    adc.StartConversion(scanned_cv + 1);
    dac_interface.Strobe();
    led_in.set_value(value > 192);
    dac_interface.Overwrite(byte_a);
    Word x;
    x.value = SignedUnsignedMul(
        output_buffer.ImmediateRead(),
        255) + 32768;
    led_out.set_value(x.bytes[1] > 192);
    
    // Convert to 12 bits and write to DAC
    x.bytes[0] = Swap4(x.bytes[0]);
    x.bytes[1] = Swap4(x.bytes[1]);
    byte_a = (x.bytes[1] & 0x0f) | 0x70;
    dac_interface.Overwrite(byte_b);
    byte_b = (x.bytes[1] & 0xf0) | (x.bytes[0] & 0x0f);
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
  dac_interface.Overwrite(byte_a);
  Word x;
  value = output_buffer.ImmediateRead();
  x.value = SignedUnsignedMul(value, 16) + 2048;
  // Convert to 12 bits and write to DAC
  led_out.set_value(x.bytes[1] > 10);
  byte_a = x.bytes[1] | 0x70;
  dac_interface.Overwrite(byte_b);
  byte_b = x.bytes[0];
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
  // Prescaler = 16, ADC clocked at 1.25 MHz.
  // ADC conversion time = 10us
  adc.set_prescaler(4);  
  adc.set_alignemnt(ADC_LEFT_ALIGNED);
  adc.Enable();
  fx_engine.Init();
  
  // ADC warm-up.
  adc.StartConversion(0);
  adc.Wait();
  
  Timer<2>::set_prescaler(1);
  Timer<2>::set_mode(TIMER_RATE);
  Timer<2>::Start();
  
  led_in.set_mode(DIGITAL_OUTPUT);
  led_out.set_mode(DIGITAL_OUTPUT);
  led_in.Low();
  led_out.Low();
}

void FillAudioBuffer() {
  while (output_buffer.writable() >= kAudioBlockSize &&
         input_buffer.readable() >= kAudioBlockSize) {
    NumberedGpio<1> tx;
    tx.set_mode(DIGITAL_OUTPUT);  
    tx.High();
    fx_engine.ProcessBlock();
    tx.Low();
  }
}

static uint8_t cv_io_round_robin = 0xff;
static uint8_t cv_io_byte = 0;

void ParseCvIo() {
  if (cv_io.readable()) {
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
            // TEMPO!
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

int main(void) {
  // Sample some junk.
  for (uint8_t i = 0; i < kAudioBlockSize; ++i) {
    input_buffer.Overwrite(128);
    output_buffer.Overwrite(128);
  }
  Init();
  while (1) {
    FillAudioBuffer();
    ParseCvIo();
  }
}
