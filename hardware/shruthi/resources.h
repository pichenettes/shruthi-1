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
// Resources definitions.
//
// Automatically generated with:
// make resources


#ifndef HARDWARE_SHRUTHI_RESOURCES_H_
#define HARDWARE_SHRUTHI_RESOURCES_H_


#include "hardware/base/base.h"

#include <avr/pgmspace.h>


#include "hardware/resources/resources_manager.h"
namespace hardware_shruthi {

typedef uint8_t ResourceId;

extern const prog_char* string_table[];

extern const prog_uint16_t* lookup_table_table[];

extern const prog_uint8_t* waveform_table[];

extern const prog_uint8_t* character_table[];

extern const prog_uint16_t lut_res_lfo_increments[] PROGMEM;
extern const prog_uint16_t lut_res_env_portamento_increments[] PROGMEM;
extern const prog_uint16_t lut_res_oscillator_increments[] PROGMEM;
extern const prog_uint16_t lut_res_fm_frequency_ratios[] PROGMEM;
extern const prog_uint16_t lut_res_scale_just[] PROGMEM;
extern const prog_uint16_t lut_res_scale_pythagorean[] PROGMEM;
extern const prog_uint16_t lut_res_scale_1_4_eb[] PROGMEM;
extern const prog_uint16_t lut_res_scale_1_4_e[] PROGMEM;
extern const prog_uint16_t lut_res_scale_1_4_ea[] PROGMEM;
extern const prog_uint16_t lut_res_scale_kanakangi[] PROGMEM;
extern const prog_uint16_t lut_res_scale_vanaspati[] PROGMEM;
extern const prog_uint16_t lut_res_scale_tanarupi[] PROGMEM;
extern const prog_uint16_t lut_res_scale_jhankaradhwani[] PROGMEM;
extern const prog_uint16_t lut_res_scale_kharaharapriya[] PROGMEM;
extern const prog_uint16_t lut_res_scale_varunapriya[] PROGMEM;
extern const prog_uint16_t lut_res_scale_yagapriya[] PROGMEM;
extern const prog_uint16_t lut_res_scale_vagadheeswari[] PROGMEM;
extern const prog_uint16_t lut_res_scale_chalanata[] PROGMEM;
extern const prog_uint16_t lut_res_arpeggiator_patterns[] PROGMEM;
extern const prog_uint8_t wav_res_formant_sine[] PROGMEM;
extern const prog_uint8_t wav_res_formant_square[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_pulse_1[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_pulse_2[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_pulse_3[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_pulse_4[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_pulse_5[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_pulse_6[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_square_0[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_square_1[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_square_2[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_square_3[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_square_4[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_square_5[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_square_6[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_saw_0[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_saw_1[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_saw_2[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_saw_3[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_saw_4[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_saw_5[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_triangle_0[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_triangle_1[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_triangle_2[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_triangle_3[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_triangle_4[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_triangle_5[] PROGMEM;
extern const prog_uint8_t wav_res_wavetable[] PROGMEM;
extern const prog_uint8_t wav_res_vowel_data[] PROGMEM;
extern const prog_uint8_t chr_res_special_characters[] PROGMEM;
#define STR_RES_PRM 0  // prm
#define STR_RES_RNG 1  // rng
#define STR_RES_OP_ 2  // op.
#define STR_RES_TUNING 3  // tuning
#define STR_RES_PRT 4  // prt
#define STR_RES_PORTA 5  // porta
#define STR_RES_LEGATO 6  // legato
#define STR_RES_MIDI_OUT 7  // midi out
#define STR_RES_PARAMETER 8  // parameter
#define STR_RES_RANGE 9  // range
#define STR_RES_OPERATOR 10  // operator
#define STR_RES_DETUNE 11  // detune
#define STR_RES_OSC_BAL 12  // osc bal
#define STR_RES_SUB_OSC_ 13  // sub osc.
#define STR_RES_PATTERN 14  // pattern
#define STR_RES_SWING 15  // swing
#define STR_RES_OSCILLATOR_1 16  // oscillator 1
#define STR_RES_OSCILLATOR_2 17  // oscillator 2
#define STR_RES_ARPEGGIO 18  // arpeggio
#define STR_RES_PERFORMANCE 19  // performance
#define STR_RES_NONE 20  // none
#define STR_RES_BLIT 21  // blit
#define STR_RES_SAW 22  // saw
#define STR_RES_SQUARE 23  // square
#define STR_RES_TRIANG 24  // triang
#define STR_RES_CZ 25  // cz
#define STR_RES_FM 26  // fm
#define STR_RES_8BITS 27  // 8bits
#define STR_RES_PWM 28  // pwm
#define STR_RES_NOISE 29  // noise
#define STR_RES_VOWEL 30  // vowel
#define STR_RES_TABLE 31  // table
#define STR_RES_SWEEP 32  // sweep
#define STR_RES_1S2 33  // 1+2
#define STR_RES_1_2 34  // 1>2
#define STR_RES_1P2 35  // 1*2
#define STR_RES_1X2 36  // 1^2
#define STR_RES_CUT 37  // cut
#define STR_RES_VCA 38  // vca
#define STR_RES_PW1 39  // pw1
#define STR_RES_PW2 40  // pw2
#define STR_RES_51 41  // 1
#define STR_RES_52 42  // 2
#define STR_RES_5 43  // 
#define STR_RES_MIX 44  // mix
#define STR_RES_NOI 45  // noi
#define STR_RES_SUB 46  // sub
#define STR_RES_RES 47  // res
#define STR_RES___CV1 48  //   cv1
#define STR_RES___CV2 49  //   cv2
#define STR_RES_BIT 50  // bit
#define STR_RES_CUTOFF 51  // cutoff
#define STR_RES__VCA 52  //  vca
#define STR_RES_PWM1 53  // pwm1
#define STR_RES_PWM2 54  // pwm2
#define STR_RES_OSC1 55  // osc1
#define STR_RES_OSC2 56  // osc2
#define STR_RES_OSC1S2 57  // osc1+2
#define STR_RES__MIX 58  //  mix
#define STR_RES__NOISE 59  //  noise
#define STR_RES_SUBOSC 60  // subosc
#define STR_RES_RESO 61  // reso
#define STR_RES____CV1 62  //    cv1
#define STR_RES____CV2 63  //    cv2
#define STR_RES_2_BITS 64  // 2 bits
#define STR_RES_MUTABLE 65  // mutable
#define STR_RES_INSTRUMENTS_671 66  // instruments -1
#define STR_RES_ATK 67  // atk
#define STR_RES_WV1 68  // wv1
#define STR_RES_RT1 69  // rt1
#define STR_RES_WV2 70  // wv2
#define STR_RES_RT2 71  // rt2
#define STR_RES_SRC 72  // src
#define STR_RES_DST 73  // dst
#define STR_RES_AMT 74  // amt
#define STR_RES_CHN 75  // chn
#define STR_RES_BPM 76  // bpm
#define STR_RES_SWG 77  // swg
#define STR_RES_SHAPE 78  // shape
#define STR_RES_ENV1TVCF 79  // env1~vcf
#define STR_RES_LFO2TVCF 80  // lfo2~vcf
#define STR_RES_RESONANCE 81  // resonance
#define STR_RES_ENVELOPE_1 82  // envelope 1
#define STR_RES_ENVELOPE_2 83  // envelope 2
#define STR_RES_SEQUENCER 84  // sequencer
#define STR_RES_ATTACK 85  // attack
#define STR_RES_DECAY 86  // decay
#define STR_RES_SUSTAIN 87  // sustain
#define STR_RES_RELEASE 88  // release
#define STR_RES_LFO1_WAVE 89  // lfo1 wave
#define STR_RES_LFO1_RATE 90  // lfo1 rate
#define STR_RES_LFO2_WAVE 91  // lfo2 wave
#define STR_RES_LFO2_RATE 92  // lfo2 rate
#define STR_RES_MOD_ 93  // mod.
#define STR_RES_SOURCE 94  // source
#define STR_RES_DEST_ 95  // dest.
#define STR_RES_AMOUNT 96  // amount
#define STR_RES_OCTAVE 97  // octave
#define STR_RES_RAGA 98  // raga
#define STR_RES_MIDI_CHAN 99  // midi chan
#define STR_RES_TEMPO 100  // tempo
#define STR_RES_MIXER 101  // mixer
#define STR_RES_FILTER 102  // filter
#define STR_RES_LFOS 103  // lfos
#define STR_RES_MODULATION 104  // modulation
#define STR_RES_KEYBOARD 105  // keyboard
#define STR_RES_MIDI 106  // midi
#define STR_RES_OFF 107  // off
#define STR_RES_ON 108  // on
#define STR_RES_TRI 109  // tri
#define STR_RES_SQR 110  // sqr
#define STR_RES_S_H 111  // s&h
#define STR_RES_3 112  // 
#define STR_RES_LF1 113  // lf1
#define STR_RES_LF2 114  // lf2
#define STR_RES_SEQ 115  // seq
#define STR_RES_ARP 116  // arp
#define STR_RES_WHL 117  // whl
#define STR_RES_BND 118  // bnd
#define STR_RES_OFS 119  // ofs
#define STR_RES_CV1 120  // cv1
#define STR_RES_CV2 121  // cv2
#define STR_RES_CV3 122  // cv3
#define STR_RES_RND 123  // rnd
#define STR_RES_EN1 124  // en1
#define STR_RES_EN2 125  // en2
#define STR_RES_VEL 126  // vel
#define STR_RES_NOT 127  // not
#define STR_RES_GAT 128  // gat
#define STR_RES_LFO1 129  // lfo1
#define STR_RES_LFO2 130  // lfo2
#define STR_RES_STPSEQ 131  // stpseq
#define STR_RES__ARP 132  //  arp
#define STR_RES_MWHEEL 133  // mwheel
#define STR_RES_BENDER 134  // bender
#define STR_RES_OFFSET 135  // offset
#define STR_RES__CV1 136  //  cv1
#define STR_RES__CV2 137  //  cv2
#define STR_RES__CV3 138  //  cv3
#define STR_RES_RANDOM 139  // random
#define STR_RES_ENV1 140  // env1
#define STR_RES_ENV2 141  // env2
#define STR_RES_VELO 142  // velo
#define STR_RES_NOTE 143  // note
#define STR_RES_GATE 144  // gate
#define STR_RES__OFF 145  //  off
#define STR_RES_THRU 146  // thru
#define STR_RES_CTRL 147  // ctrl
#define STR_RES_POLY 148  // poly
#define STR_RES_TOUCH_A_KNOB_TO 149  // touch a knob to
#define STR_RES_ASSIGN_PARAMETER 150  // assign parameter
#define STR_RES_READY 151  // ready
#define STR_RES_FOR_OS_UPDATE 152  // for os update
#define STR_RES_PATCH_BANK 153  // patch bank
#define STR_RES_STEP_SEQUENCER 154  // step sequencer
#define STR_RES_LOAD 155  // load
#define STR_RES_ 156  // ----
#define STR_RES_SAVE 157  // save
#define STR_RES_EXTERN 158  // extern
#define STR_RES_EQUAL 159  // equal
#define STR_RES_JUST 160  // just
#define STR_RES_PYTHAG 161  // pythag
#define STR_RES_1_4_EB 162  // 1/4 eb
#define STR_RES_1_4_E 163  // 1/4 e
#define STR_RES_1_4_EA 164  // 1/4 ea
#define STR_RES_KANAKA 165  // kanaka
#define STR_RES_RATNAN 166  // ratnan
#define STR_RES_GANAMU 167  // ganamu
#define STR_RES_VANASP 168  // vanasp
#define STR_RES_MANAVA 169  // manava
#define STR_RES_TANARU 170  // tanaru
#define STR_RES_SENAVA 171  // senava
#define STR_RES_HANUMA 172  // hanuma
#define STR_RES_DHENUK 173  // dhenuk
#define STR_RES_NATAKA 174  // nataka
#define STR_RES_KOKILA 175  // kokila
#define STR_RES_RUPAVA 176  // rupava
#define STR_RES_GAYAKA 177  // gayaka
#define STR_RES_VAKULA 178  // vakula
#define STR_RES_MAYAMA 179  // mayama
#define STR_RES_CHAKRA 180  // chakra
#define STR_RES_SURYAK 181  // suryak
#define STR_RES_HATAKA 182  // hataka
#define STR_RES_JHANKA 183  // jhanka
#define STR_RES_NATABH 184  // natabh
#define STR_RES_KEERAV 185  // keerav
#define STR_RES_KHARAH 186  // kharah
#define STR_RES_GOURIM 187  // gourim
#define STR_RES_VARUNA 188  // varuna
#define STR_RES_MARARA 189  // marara
#define STR_RES_CHARUK 190  // charuk
#define STR_RES_SARASA 191  // sarasa
#define STR_RES_HARIKA 192  // harika
#define STR_RES_DHEERA 193  // dheera
#define STR_RES_NAGANA 194  // nagana
#define STR_RES_YAGAPR 195  // yagapr
#define STR_RES_RAGAVA 196  // ragava
#define STR_RES_GANGEY 197  // gangey
#define STR_RES_VAGADH 198  // vagadh
#define STR_RES_SHULIN 199  // shulin
#define STR_RES_CHALAN 200  // chalan
#define STR_RES_SALAGA 201  // salaga
#define STR_RES_JALARN 202  // jalarn
#define STR_RES_JHALAV 203  // jhalav
#define STR_RES_NAVANE 204  // navane
#define STR_RES_PAVANI 205  // pavani
#define STR_RES_RAGHUP 206  // raghup
#define STR_RES_GAVAMB 207  // gavamb
#define STR_RES_BHAVAP 208  // bhavap
#define STR_RES_SHUBHA 209  // shubha
#define STR_RES_SHADVI 210  // shadvi
#define STR_RES_SUVARN 211  // suvarn
#define STR_RES_DIVYAM 212  // divyam
#define STR_RES_DHAVAL 213  // dhaval
#define STR_RES_NAMANA 214  // namana
#define STR_RES_KAMAVA 215  // kamava
#define STR_RES_RAMAPR 216  // ramapr
#define STR_RES_GAMANA 217  // gamana
#define STR_RES_VISHWA 218  // vishwa
#define STR_RES_SHAMAL 219  // shamal
#define STR_RES_SHANMU 220  // shanmu
#define STR_RES_SIMHEN 221  // simhen
#define STR_RES_HEMAVA 222  // hemava
#define STR_RES_DHARMA 223  // dharma
#define STR_RES_NEETIM 224  // neetim
#define STR_RES_KANTAM 225  // kantam
#define STR_RES_RISHAB 226  // rishab
#define STR_RES_LATANG 227  // latang
#define STR_RES_VACHAS 228  // vachas
#define STR_RES_MECHAK 229  // mechak
#define STR_RES_CHITRA 230  // chitra
#define STR_RES_SUCHAR 231  // suchar
#define STR_RES_JYOTIS 232  // jyotis
#define STR_RES_DHATUV 233  // dhatuv
#define STR_RES_NASIKA 234  // nasika
#define STR_RES_KOSALA 235  // kosala
#define STR_RES_RASIKA 236  // rasika
#define LUT_RES_LFO_INCREMENTS 0
#define LUT_RES_LFO_INCREMENTS_SIZE 128
#define LUT_RES_ENV_PORTAMENTO_INCREMENTS 1
#define LUT_RES_ENV_PORTAMENTO_INCREMENTS_SIZE 128
#define LUT_RES_OSCILLATOR_INCREMENTS 2
#define LUT_RES_OSCILLATOR_INCREMENTS_SIZE 768
#define LUT_RES_FM_FREQUENCY_RATIOS 3
#define LUT_RES_FM_FREQUENCY_RATIOS_SIZE 25
#define LUT_RES_SCALE_JUST 4
#define LUT_RES_SCALE_JUST_SIZE 12
#define LUT_RES_SCALE_PYTHAGOREAN 5
#define LUT_RES_SCALE_PYTHAGOREAN_SIZE 12
#define LUT_RES_SCALE_1_4_EB 6
#define LUT_RES_SCALE_1_4_EB_SIZE 12
#define LUT_RES_SCALE_1_4_E 7
#define LUT_RES_SCALE_1_4_E_SIZE 12
#define LUT_RES_SCALE_1_4_EA 8
#define LUT_RES_SCALE_1_4_EA_SIZE 12
#define LUT_RES_SCALE_KANAKANGI 9
#define LUT_RES_SCALE_KANAKANGI_SIZE 12
#define LUT_RES_SCALE_RATNANGI 10
#define LUT_RES_SCALE_RATNANGI_SIZE 12
#define LUT_RES_SCALE_GANAMURTI 11
#define LUT_RES_SCALE_GANAMURTI_SIZE 12
#define LUT_RES_SCALE_VANASPATI 12
#define LUT_RES_SCALE_VANASPATI_SIZE 12
#define LUT_RES_SCALE_MANAVATI 13
#define LUT_RES_SCALE_MANAVATI_SIZE 12
#define LUT_RES_SCALE_TANARUPI 14
#define LUT_RES_SCALE_TANARUPI_SIZE 12
#define LUT_RES_SCALE_SENAVATI 15
#define LUT_RES_SCALE_SENAVATI_SIZE 12
#define LUT_RES_SCALE_HANUMATODI 16
#define LUT_RES_SCALE_HANUMATODI_SIZE 12
#define LUT_RES_SCALE_DHENUKA 17
#define LUT_RES_SCALE_DHENUKA_SIZE 12
#define LUT_RES_SCALE_NATAKAPRIYA 18
#define LUT_RES_SCALE_NATAKAPRIYA_SIZE 12
#define LUT_RES_SCALE_KOKILAPRIYA 19
#define LUT_RES_SCALE_KOKILAPRIYA_SIZE 12
#define LUT_RES_SCALE_RUPAVATI 20
#define LUT_RES_SCALE_RUPAVATI_SIZE 12
#define LUT_RES_SCALE_GAYAKAPRIYA 21
#define LUT_RES_SCALE_GAYAKAPRIYA_SIZE 12
#define LUT_RES_SCALE_VAKULABHARANAM 22
#define LUT_RES_SCALE_VAKULABHARANAM_SIZE 12
#define LUT_RES_SCALE_MAYAMALAVAGOWLA 23
#define LUT_RES_SCALE_MAYAMALAVAGOWLA_SIZE 12
#define LUT_RES_SCALE_CHAKRAVAKAM 24
#define LUT_RES_SCALE_CHAKRAVAKAM_SIZE 12
#define LUT_RES_SCALE_SURYAKANTAM 25
#define LUT_RES_SCALE_SURYAKANTAM_SIZE 12
#define LUT_RES_SCALE_HATAKAMBARI 26
#define LUT_RES_SCALE_HATAKAMBARI_SIZE 12
#define LUT_RES_SCALE_JHANKARADHWANI 27
#define LUT_RES_SCALE_JHANKARADHWANI_SIZE 12
#define LUT_RES_SCALE_NATABHAIRAVI 28
#define LUT_RES_SCALE_NATABHAIRAVI_SIZE 12
#define LUT_RES_SCALE_KEERAVANI 29
#define LUT_RES_SCALE_KEERAVANI_SIZE 12
#define LUT_RES_SCALE_KHARAHARAPRIYA 30
#define LUT_RES_SCALE_KHARAHARAPRIYA_SIZE 12
#define LUT_RES_SCALE_GOURIMANOHARI 31
#define LUT_RES_SCALE_GOURIMANOHARI_SIZE 12
#define LUT_RES_SCALE_VARUNAPRIYA 32
#define LUT_RES_SCALE_VARUNAPRIYA_SIZE 12
#define LUT_RES_SCALE_MARARANJANI 33
#define LUT_RES_SCALE_MARARANJANI_SIZE 12
#define LUT_RES_SCALE_CHARUKESI 34
#define LUT_RES_SCALE_CHARUKESI_SIZE 12
#define LUT_RES_SCALE_SARASANGI 35
#define LUT_RES_SCALE_SARASANGI_SIZE 12
#define LUT_RES_SCALE_HARIKAMBHOJI 36
#define LUT_RES_SCALE_HARIKAMBHOJI_SIZE 12
#define LUT_RES_SCALE_DHEERASANKARABHARANAM 37
#define LUT_RES_SCALE_DHEERASANKARABHARANAM_SIZE 12
#define LUT_RES_SCALE_NAGANANDINI 38
#define LUT_RES_SCALE_NAGANANDINI_SIZE 12
#define LUT_RES_SCALE_YAGAPRIYA 39
#define LUT_RES_SCALE_YAGAPRIYA_SIZE 12
#define LUT_RES_SCALE_RAGAVARDHINI 40
#define LUT_RES_SCALE_RAGAVARDHINI_SIZE 12
#define LUT_RES_SCALE_GANGEYABHUSHANI 41
#define LUT_RES_SCALE_GANGEYABHUSHANI_SIZE 12
#define LUT_RES_SCALE_VAGADHEESWARI 42
#define LUT_RES_SCALE_VAGADHEESWARI_SIZE 12
#define LUT_RES_SCALE_SHULINI 43
#define LUT_RES_SCALE_SHULINI_SIZE 12
#define LUT_RES_SCALE_CHALANATA 44
#define LUT_RES_SCALE_CHALANATA_SIZE 12
#define LUT_RES_SCALE_SALAGAM 45
#define LUT_RES_SCALE_SALAGAM_SIZE 12
#define LUT_RES_SCALE_JALARNAVAM 46
#define LUT_RES_SCALE_JALARNAVAM_SIZE 12
#define LUT_RES_SCALE_JHALAVARALI 47
#define LUT_RES_SCALE_JHALAVARALI_SIZE 12
#define LUT_RES_SCALE_NAVANEETAM 48
#define LUT_RES_SCALE_NAVANEETAM_SIZE 12
#define LUT_RES_SCALE_PAVANI 49
#define LUT_RES_SCALE_PAVANI_SIZE 12
#define LUT_RES_SCALE_RAGHUPRIYA 50
#define LUT_RES_SCALE_RAGHUPRIYA_SIZE 12
#define LUT_RES_SCALE_GAVAMBHODI 51
#define LUT_RES_SCALE_GAVAMBHODI_SIZE 12
#define LUT_RES_SCALE_BHAVAPRIYA 52
#define LUT_RES_SCALE_BHAVAPRIYA_SIZE 12
#define LUT_RES_SCALE_SHUBHAPANTUVARALI 53
#define LUT_RES_SCALE_SHUBHAPANTUVARALI_SIZE 12
#define LUT_RES_SCALE_SHADVIDAMARGINI 54
#define LUT_RES_SCALE_SHADVIDAMARGINI_SIZE 12
#define LUT_RES_SCALE_SUVARNANGI 55
#define LUT_RES_SCALE_SUVARNANGI_SIZE 12
#define LUT_RES_SCALE_DIVYAMANI 56
#define LUT_RES_SCALE_DIVYAMANI_SIZE 12
#define LUT_RES_SCALE_DHAVALAMBARI 57
#define LUT_RES_SCALE_DHAVALAMBARI_SIZE 12
#define LUT_RES_SCALE_NAMANARAYANI 58
#define LUT_RES_SCALE_NAMANARAYANI_SIZE 12
#define LUT_RES_SCALE_KAMAVARDANI 59
#define LUT_RES_SCALE_KAMAVARDANI_SIZE 12
#define LUT_RES_SCALE_RAMAPRIYA 60
#define LUT_RES_SCALE_RAMAPRIYA_SIZE 12
#define LUT_RES_SCALE_GAMANASHRAMA 61
#define LUT_RES_SCALE_GAMANASHRAMA_SIZE 12
#define LUT_RES_SCALE_VISHWAMBARI 62
#define LUT_RES_SCALE_VISHWAMBARI_SIZE 12
#define LUT_RES_SCALE_SHAMALANGI 63
#define LUT_RES_SCALE_SHAMALANGI_SIZE 12
#define LUT_RES_SCALE_SHANMUKHAPRIYA 64
#define LUT_RES_SCALE_SHANMUKHAPRIYA_SIZE 12
#define LUT_RES_SCALE_SIMHENDRAMADHYAMAM 65
#define LUT_RES_SCALE_SIMHENDRAMADHYAMAM_SIZE 12
#define LUT_RES_SCALE_HEMAVATI 66
#define LUT_RES_SCALE_HEMAVATI_SIZE 12
#define LUT_RES_SCALE_DHARMAVATI 67
#define LUT_RES_SCALE_DHARMAVATI_SIZE 12
#define LUT_RES_SCALE_NEETIMATI 68
#define LUT_RES_SCALE_NEETIMATI_SIZE 12
#define LUT_RES_SCALE_KANTAMANI 69
#define LUT_RES_SCALE_KANTAMANI_SIZE 12
#define LUT_RES_SCALE_RISHABHAPRIYA 70
#define LUT_RES_SCALE_RISHABHAPRIYA_SIZE 12
#define LUT_RES_SCALE_LATANGI 71
#define LUT_RES_SCALE_LATANGI_SIZE 12
#define LUT_RES_SCALE_VACHASPATI 72
#define LUT_RES_SCALE_VACHASPATI_SIZE 12
#define LUT_RES_SCALE_MECHAKALYANI 73
#define LUT_RES_SCALE_MECHAKALYANI_SIZE 12
#define LUT_RES_SCALE_CHITRAMBARI 74
#define LUT_RES_SCALE_CHITRAMBARI_SIZE 12
#define LUT_RES_SCALE_SUCHARITRA 75
#define LUT_RES_SCALE_SUCHARITRA_SIZE 12
#define LUT_RES_SCALE_JYOTISWARUPINI 76
#define LUT_RES_SCALE_JYOTISWARUPINI_SIZE 12
#define LUT_RES_SCALE_DHATUVARDANI 77
#define LUT_RES_SCALE_DHATUVARDANI_SIZE 12
#define LUT_RES_SCALE_NASIKABHUSHANI 78
#define LUT_RES_SCALE_NASIKABHUSHANI_SIZE 12
#define LUT_RES_SCALE_KOSALAM 79
#define LUT_RES_SCALE_KOSALAM_SIZE 12
#define LUT_RES_SCALE_RASIKAPRIYA 80
#define LUT_RES_SCALE_RASIKAPRIYA_SIZE 12
#define LUT_RES_ARPEGGIATOR_PATTERNS 81
#define LUT_RES_ARPEGGIATOR_PATTERNS_SIZE 15
#define WAV_RES_FORMANT_SINE 0
#define WAV_RES_FORMANT_SINE_SIZE 256
#define WAV_RES_FORMANT_SQUARE 1
#define WAV_RES_FORMANT_SQUARE_SIZE 256
#define WAV_RES_BANDLIMITED_PULSE_1 2
#define WAV_RES_BANDLIMITED_PULSE_1_SIZE 257
#define WAV_RES_BANDLIMITED_PULSE_2 3
#define WAV_RES_BANDLIMITED_PULSE_2_SIZE 257
#define WAV_RES_BANDLIMITED_PULSE_3 4
#define WAV_RES_BANDLIMITED_PULSE_3_SIZE 257
#define WAV_RES_BANDLIMITED_PULSE_4 5
#define WAV_RES_BANDLIMITED_PULSE_4_SIZE 257
#define WAV_RES_BANDLIMITED_PULSE_5 6
#define WAV_RES_BANDLIMITED_PULSE_5_SIZE 257
#define WAV_RES_BANDLIMITED_PULSE_6 7
#define WAV_RES_BANDLIMITED_PULSE_6_SIZE 257
#define WAV_RES_BANDLIMITED_SQUARE_0 8
#define WAV_RES_BANDLIMITED_SQUARE_0_SIZE 257
#define WAV_RES_BANDLIMITED_SQUARE_1 9
#define WAV_RES_BANDLIMITED_SQUARE_1_SIZE 257
#define WAV_RES_BANDLIMITED_SQUARE_2 10
#define WAV_RES_BANDLIMITED_SQUARE_2_SIZE 257
#define WAV_RES_BANDLIMITED_SQUARE_3 11
#define WAV_RES_BANDLIMITED_SQUARE_3_SIZE 257
#define WAV_RES_BANDLIMITED_SQUARE_4 12
#define WAV_RES_BANDLIMITED_SQUARE_4_SIZE 257
#define WAV_RES_BANDLIMITED_SQUARE_5 13
#define WAV_RES_BANDLIMITED_SQUARE_5_SIZE 257
#define WAV_RES_BANDLIMITED_SQUARE_6 14
#define WAV_RES_BANDLIMITED_SQUARE_6_SIZE 257
#define WAV_RES_BANDLIMITED_SAW_0 15
#define WAV_RES_BANDLIMITED_SAW_0_SIZE 257
#define WAV_RES_BANDLIMITED_SAW_1 16
#define WAV_RES_BANDLIMITED_SAW_1_SIZE 257
#define WAV_RES_BANDLIMITED_SAW_2 17
#define WAV_RES_BANDLIMITED_SAW_2_SIZE 257
#define WAV_RES_BANDLIMITED_SAW_3 18
#define WAV_RES_BANDLIMITED_SAW_3_SIZE 257
#define WAV_RES_BANDLIMITED_SAW_4 19
#define WAV_RES_BANDLIMITED_SAW_4_SIZE 257
#define WAV_RES_BANDLIMITED_SAW_5 20
#define WAV_RES_BANDLIMITED_SAW_5_SIZE 257
#define WAV_RES_BANDLIMITED_SAW_6 21
#define WAV_RES_BANDLIMITED_SAW_6_SIZE 257
#define WAV_RES_BANDLIMITED_TRIANGLE_0 22
#define WAV_RES_BANDLIMITED_TRIANGLE_0_SIZE 257
#define WAV_RES_BANDLIMITED_TRIANGLE_1 23
#define WAV_RES_BANDLIMITED_TRIANGLE_1_SIZE 257
#define WAV_RES_BANDLIMITED_TRIANGLE_2 24
#define WAV_RES_BANDLIMITED_TRIANGLE_2_SIZE 257
#define WAV_RES_BANDLIMITED_TRIANGLE_3 25
#define WAV_RES_BANDLIMITED_TRIANGLE_3_SIZE 257
#define WAV_RES_BANDLIMITED_TRIANGLE_4 26
#define WAV_RES_BANDLIMITED_TRIANGLE_4_SIZE 257
#define WAV_RES_BANDLIMITED_TRIANGLE_5 27
#define WAV_RES_BANDLIMITED_TRIANGLE_5_SIZE 257
#define WAV_RES_BANDLIMITED_TRIANGLE_6 28
#define WAV_RES_BANDLIMITED_TRIANGLE_6_SIZE 257
#define WAV_RES_WAVETABLE 29
#define WAV_RES_WAVETABLE_SIZE 2145
#define WAV_RES_VOWEL_DATA 30
#define WAV_RES_VOWEL_DATA_SIZE 45
#define CHR_RES_SPECIAL_CHARACTERS 0
#define CHR_RES_SPECIAL_CHARACTERS_SIZE 64
typedef hardware_resources::ResourcesManager<
    ResourceId,
    hardware_resources::ResourcesTables<
        string_table,
        lookup_table_table> > ResourcesManager; 

}  // namespace hardware_shruthi

#endif  // HARDWARE_SHRUTHI_RESOURCES_H_
