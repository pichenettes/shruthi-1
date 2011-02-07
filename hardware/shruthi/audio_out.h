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
// Instance of the audio out class, configured for the Shruthi-1 project.

#ifndef HARDWARE_SHRUTHI_AUDIO_OUT_H_
#define HARDWARE_SHRUTHI_AUDIO_OUT_H_

#include "hardware/base/base.h"
#include "hardware/hal/audio_output.h"
#include "hardware/hal/gpio.h"
#include "hardware/shruthi/shruthi.h"

using hardware_hal::AudioOutput;
using hardware_hal::PwmOutput;

namespace hardware_shruthi {

extern hardware_hal::AudioOutput<
    hardware_hal::PwmOutput<kPinVcoOut>,
    kAudioBufferSize,
    kAudioBlockSize> audio_out;

}  // namespace hardware_shruthi

#endif  // HARDWARE_SHRUTHI_AUDIO_OUT_H_
