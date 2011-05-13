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

extern const prog_uint8_t* waveshaper_table[];

extern const prog_uint16_t* lut_table[];

extern const prog_uint8_t waveshaper_res_distortion[] PROGMEM;
extern const prog_uint8_t waveshaper_res_fold[] PROGMEM;
extern const prog_uint8_t waveshaper_res_sine[] PROGMEM;
extern const prog_uint16_t lut_res_integrator_step[] PROGMEM;
extern const prog_uint16_t lut_res_damp_factor[] PROGMEM;
extern const prog_uint16_t lut_res_damp_stability_bound[] PROGMEM;
extern const prog_uint16_t lut_res_comb_delays[] PROGMEM;
extern const prog_uint16_t lut_res_phase_increment[] PROGMEM;
#define WAVESHAPER_RES_DISTORTION 0
#define WAVESHAPER_RES_DISTORTION_SIZE 256
#define WAVESHAPER_RES_FOLD 1
#define WAVESHAPER_RES_FOLD_SIZE 256
#define WAVESHAPER_RES_SINE 2
#define WAVESHAPER_RES_SINE_SIZE 257
#define LUT_RES_INTEGRATOR_STEP 0
#define LUT_RES_INTEGRATOR_STEP_SIZE 256
#define LUT_RES_DAMP_FACTOR 1
#define LUT_RES_DAMP_FACTOR_SIZE 256
#define LUT_RES_DAMP_STABILITY_BOUND 2
#define LUT_RES_DAMP_STABILITY_BOUND_SIZE 256
#define LUT_RES_COMB_DELAYS 3
#define LUT_RES_COMB_DELAYS_SIZE 256
#define LUT_RES_PHASE_INCREMENT 4
#define LUT_RES_PHASE_INCREMENT_SIZE 256

}  // namespace dsp

#endif  // DSP_RESOURCES_H_
