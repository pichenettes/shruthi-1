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

#include "dsp/fx_engine.h"

#include "dsp/buffers.h"

namespace dsp {

/* <static> */
uint8_t FxEngine::cv_[CV_LAST];
/* </static> */

/* extern */
FxEngine fx_engine;

/* static */
void FxEngine::Init() {
}

/* static */
void FxEngine::ProcessBlock() {
  for (uint8_t i = 0; i < kAudioBlockSize; ++i) {
    uint8_t sample = input_buffer.ImmediateRead();
    output_buffer.Overwrite(sample);
  }
}

}  // namespace dsp
