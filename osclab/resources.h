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


#ifndef OSCLAB_RESOURCES_H_
#define OSCLAB_RESOURCES_H_


#include "avrlib/base.h"

#include <avr/pgmspace.h>


#include "avrlib/resources_manager.h"

namespace osclab {

typedef uint8_t ResourceId;

extern const prog_char* string_table[];

extern const prog_uint16_t* lookup_table_table[];

extern const prog_uint8_t* waveform_table[];

extern const prog_uint16_t lut_res_oscillator_increments[] PROGMEM;
extern const prog_uint16_t lut_res_fm_frequency_ratios[] PROGMEM;
extern const prog_uint16_t lut_res_blep[] PROGMEM;
extern const prog_uint16_t lut_res_reciprocal[] PROGMEM;
extern const prog_uint8_t wav_res_formant_sine[] PROGMEM;
extern const prog_uint8_t wav_res_formant_square[] PROGMEM;
extern const prog_uint8_t wav_res_sine[] PROGMEM;
extern const prog_uint8_t wav_res_triangle[] PROGMEM;
extern const prog_uint8_t wav_res_vowel_data[] PROGMEM;
extern const prog_uint8_t wav_res_waves[] PROGMEM;
extern const prog_uint8_t wav_res_wavetables[] PROGMEM;
#define STR_RES_NONE 0  // none
#define STR_RES_SAW 1  // saw
#define STR_RES_SQUARE 2  // square
#define STR_RES_TRIANG 3  // triang
#define STR_RES_ZSAW 4  // zsaw
#define STR_RES_ZRESO 5  // zreso
#define STR_RES_ZTRI 6  // ztri
#define STR_RES_ZPULSE 7  // zpulse
#define STR_RES_ZSYNC 8  // zsync
#define STR_RES_PAD 9  // pad
#define STR_RES_FM 10  // fm
#define STR_RES_WAVES 11  // waves
#define STR_RES_TAMPUR 12  // tampur
#define STR_RES_DIGITL 13  // digitl
#define STR_RES_METALL 14  // metall
#define STR_RES_BOWED 15  // bowed
#define STR_RES_SLAP 16  // slap
#define STR_RES_ORGAN 17  // organ
#define STR_RES_MALE 18  // male
#define STR_RES_USER 19  // user
#define STR_RES_8BITS 20  // 8bits
#define STR_RES_CRUSH 21  // crush
#define STR_RES_PWM 22  // pwm
#define STR_RES_NOISE 23  // noise
#define STR_RES_VOWEL 24  // vowel
#define STR_RES_BELISH 25  // belish
#define STR_RES_POLATD 26  // polatd
#define STR_RES_CELLO 27  // cello
#define STR_RES_CLPSWP 28  // clpswp
#define STR_RES_FEMALE 29  // female
#define STR_RES_FMTVOC 30  // fmtvoc
#define STR_RES_FRMNT2 31  // frmnt2
#define STR_RES_RES3HP 32  // res3hp
#define STR_RES_ELECTP 33  // electp
#define STR_RES_VIBES 34  // vibes
#define LUT_RES_OSCILLATOR_INCREMENTS 0
#define LUT_RES_OSCILLATOR_INCREMENTS_SIZE 768
#define LUT_RES_FM_FREQUENCY_RATIOS 1
#define LUT_RES_FM_FREQUENCY_RATIOS_SIZE 25
#define LUT_RES_BLEP 2
#define LUT_RES_BLEP_SIZE 5430
#define LUT_RES_RECIPROCAL 3
#define LUT_RES_RECIPROCAL_SIZE 256
#define WAV_RES_FORMANT_SINE 0
#define WAV_RES_FORMANT_SINE_SIZE 256
#define WAV_RES_FORMANT_SQUARE 1
#define WAV_RES_FORMANT_SQUARE_SIZE 256
#define WAV_RES_SINE 2
#define WAV_RES_SINE_SIZE 257
#define WAV_RES_TRIANGLE 3
#define WAV_RES_TRIANGLE_SIZE 257
#define WAV_RES_VOWEL_DATA 4
#define WAV_RES_VOWEL_DATA_SIZE 63
#define WAV_RES_WAVES 5
#define WAV_RES_WAVES_SIZE 16512
#define WAV_RES_WAVETABLES 6
#define WAV_RES_WAVETABLES_SIZE 324
typedef avrlib::ResourcesManager<
    ResourceId,
    avrlib::ResourcesTables<
        string_table,
        lookup_table_table> > ResourcesManager; 

}  // namespace osclab

#endif  // OSCLAB_RESOURCES_H_
