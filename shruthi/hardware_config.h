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
//
// -----------------------------------------------------------------------------
//
// Main definitions.

#ifndef SHRUTHI_HARDWARE_CONFIG_H_
#define SHRUTHI_HARDWARE_CONFIG_H_

#include "avrlib/base.h"
#include "avrlib/gpio.h"
#include "avrlib/parallel_io.h"
#include "avrlib/serial.h"

namespace shruthi {

using avrlib::Gpio;
using avrlib::PARALLEL_NIBBLE_HIGH;
using avrlib::ParallelPort;
using avrlib::PortB;
using avrlib::PortC;
using avrlib::PortD;
using avrlib::SerialPort0;
using avrlib::SerialPort1;

// MIDI
typedef SerialPort0 MidiPort;
typedef SerialPort1 CvTxPort;

// LCD
typedef Gpio<PortC, 2> LcdRsLine;
typedef Gpio<PortC, 3> LcdEnableLine;
typedef ParallelPort<PortC, PARALLEL_NIBBLE_HIGH> LcdDataBus;

// Encoder
typedef Gpio<PortB, 1> EncoderALine;
typedef Gpio<PortB, 0> EncoderBLine;
typedef Gpio<PortB, 2> EncoderClickLine;

// Shift registers / muxes.
typedef Gpio<PortB, 7> IOClockLine;
typedef Gpio<PortB, 6> IOInputLine;
typedef Gpio<PortB, 5> IOOutputLine;
typedef Gpio<PortD, 2> IOEnableLine;
typedef Gpio<PortD, 3> IOEnableLineAux;

// PWM/audio output.
static const uint8_t kPinVcoOut = 12;
static const uint8_t kPinVcaOut = 13;
static const uint8_t kPinVcfCutoffOut = 14;
static const uint8_t kPinVcfResonanceOut = 15;
static const uint8_t kPinCv1Out = 3;
static const uint8_t kPinCv2Out = 4;

static const uint8_t kPinAnalogInput = 0;
static const uint8_t kPinCvInput = 4;

static const uint16_t kInternalEepromSize = 2048;

}  // namespace shruthi

#endif // SHRUTHI_HARDWARE_CONFIG_H_
