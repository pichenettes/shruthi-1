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
//
// -----------------------------------------------------------------------------
//
// Resources definitions.
//
// Automatically generated with:
// make resources


#ifndef DSP_RESOURCES_H_
#define DSP_RESOURCES_H_


#include "avrlib/base.h"

#include <avr/pgmspace.h>


namespace dsp {

typedef uint8_t ResourceId;

extern const prog_uint8_t* lut_table[];

extern const prog_uint8_t lut_res_distortion[] PROGMEM;
#define LUT_RES_DISTORTION 0
#define LUT_RES_DISTORTION_SIZE 256

}  // namespace dsp

#endif  // DSP_RESOURCES_H_
