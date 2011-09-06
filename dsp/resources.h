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

extern const prog_uint8_t* waveform_table[];

extern const prog_uint16_t* lut_table[];

extern const prog_uint8_t waveform_res_resonance_response[] PROGMEM;
extern const prog_uint8_t waveform_res_sine[] PROGMEM;
extern const prog_uint16_t lut_res_distortion[] PROGMEM;
extern const prog_uint16_t lut_res_fold[] PROGMEM;
extern const prog_uint16_t lut_res_integrator_gain[] PROGMEM;
extern const prog_uint16_t lut_res_comb_delays[] PROGMEM;
extern const prog_uint16_t lut_res_phase_increment[] PROGMEM;
extern const prog_uint16_t lut_res_delay_duration[] PROGMEM;
extern const prog_uint16_t lut_res_delay_decimation[] PROGMEM;
extern const prog_uint16_t lut_res_delay_filter_gain[] PROGMEM;
extern const prog_uint16_t lut_res_delay_phase_scaling[] PROGMEM;
extern const prog_uint16_t lut_res_tap_delay_duration[] PROGMEM;
extern const prog_uint16_t lut_res_tap_delay_decimation[] PROGMEM;
extern const prog_uint16_t lut_res_tap_delay_filter_gain[] PROGMEM;
extern const prog_uint16_t lut_res_pitch_ratio[] PROGMEM;
#define WAVEFORM_RES_RESONANCE_RESPONSE 0
#define WAVEFORM_RES_RESONANCE_RESPONSE_SIZE 256
#define WAVEFORM_RES_SINE 1
#define WAVEFORM_RES_SINE_SIZE 257
#define LUT_RES_DISTORTION 0
#define LUT_RES_DISTORTION_SIZE 4096
#define LUT_RES_FOLD 1
#define LUT_RES_FOLD_SIZE 4096
#define LUT_RES_INTEGRATOR_GAIN 2
#define LUT_RES_INTEGRATOR_GAIN_SIZE 256
#define LUT_RES_COMB_DELAYS 3
#define LUT_RES_COMB_DELAYS_SIZE 256
#define LUT_RES_PHASE_INCREMENT 4
#define LUT_RES_PHASE_INCREMENT_SIZE 256
#define LUT_RES_DELAY_DURATION 5
#define LUT_RES_DELAY_DURATION_SIZE 256
#define LUT_RES_DELAY_DECIMATION 6
#define LUT_RES_DELAY_DECIMATION_SIZE 256
#define LUT_RES_DELAY_FILTER_GAIN 7
#define LUT_RES_DELAY_FILTER_GAIN_SIZE 256
#define LUT_RES_DELAY_PHASE_SCALING 8
#define LUT_RES_DELAY_PHASE_SCALING_SIZE 256
#define LUT_RES_TAP_DELAY_DURATION 9
#define LUT_RES_TAP_DELAY_DURATION_SIZE 681
#define LUT_RES_TAP_DELAY_DECIMATION 10
#define LUT_RES_TAP_DELAY_DECIMATION_SIZE 681
#define LUT_RES_TAP_DELAY_FILTER_GAIN 11
#define LUT_RES_TAP_DELAY_FILTER_GAIN_SIZE 681
#define LUT_RES_PITCH_RATIO 12
#define LUT_RES_PITCH_RATIO_SIZE 256

}  // namespace dsp

#endif  // DSP_RESOURCES_H_
