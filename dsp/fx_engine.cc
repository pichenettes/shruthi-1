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

namespace dsp {

/* <static> */
uint8_t FxEngine::data_access_byte_[1];
uint8_t FxEngine::cv_1_;
uint8_t FxEngine::cv_2_;
uint8_t FxEngine::resonance_;
uint8_t FxEngine::cutoff_;
uint8_t FxEngine::vca_;
uint8_t FxEngine::buffer_[kAudioBlockSize];
/* </static> */

/* extern */
FxEngine fx_engine;

/* static */
void FxEngine::Init() {
  
}

/* static */
void FxEngine::ProcessBlock() {
  
}

}  // namespace dsp
