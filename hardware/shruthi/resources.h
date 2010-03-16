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
extern const prog_uint8_t wav_res_wavetable_1[] PROGMEM;
extern const prog_uint8_t wav_res_wavetable_2[] PROGMEM;
extern const prog_uint8_t wav_res_wavetable_3[] PROGMEM;
extern const prog_uint8_t wav_res_wavetable_4[] PROGMEM;
extern const prog_uint8_t wav_res_wavetable_5[] PROGMEM;
extern const prog_uint8_t wav_res_wavetable_6[] PROGMEM;
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
#define STR_RES_RESET 8  // reset
#define STR_RES_RST 9  // rst
#define STR_RES_PARAMETER 10  // parameter
#define STR_RES_RANGE 11  // range
#define STR_RES_OPERATOR 12  // operator
#define STR_RES_DETUNE 13  // detune
#define STR_RES_OSC_BAL 14  // osc bal
#define STR_RES_SUB_OSC_ 15  // sub osc.
#define STR_RES_PATTERN 16  // pattern
#define STR_RES_SWING 17  // swing
#define STR_RES_OSCILLATOR_1 18  // oscillator 1
#define STR_RES_OSCILLATOR_2 19  // oscillator 2
#define STR_RES_ARPEGGIO 20  // arpeggio
#define STR_RES_PERFORMANCE 21  // performance
#define STR_RES_NONE 22  // none
#define STR_RES_BLIT 23  // blit
#define STR_RES_SAW 24  // saw
#define STR_RES_SQUARE 25  // square
#define STR_RES_TRIANG 26  // triang
#define STR_RES_CZSAW 27  // czsaw
#define STR_RES_CZRES 28  // czres
#define STR_RES_CZTRI 29  // cztri
#define STR_RES_CZPULS 30  // czpuls
#define STR_RES_FM 31  // fm
#define STR_RES_BELL 32  // bell
#define STR_RES_DRONE 33  // drone
#define STR_RES_FEMALE 34  // female
#define STR_RES_MALE 35  // male
#define STR_RES_SINES 36  // sines
#define STR_RES_WAVES 37  // waves
#define STR_RES_SHAPER 38  // shaper
#define STR_RES_8BITS 39  // 8bits
#define STR_RES_PWM 40  // pwm
#define STR_RES_NOISE 41  // noise
#define STR_RES_VOWEL 42  // vowel
#define STR_RES_1S2 43  // 1+2
#define STR_RES_1_2 44  // 1>2
#define STR_RES_1P2 45  // 1*2
#define STR_RES_1X2 46  // 1^2
#define STR_RES_CUT 47  // cut
#define STR_RES_VCA 48  // vca
#define STR_RES_PW1 49  // pw1
#define STR_RES_PW2 50  // pw2
#define STR_RES_51 51  // 1
#define STR_RES_52 52  // 2
#define STR_RES_5 53  // 
#define STR_RES_MIX 54  // mix
#define STR_RES_NOI 55  // noi
#define STR_RES_SUB 56  // sub
#define STR_RES_RES 57  // res
#define STR_RES__CV1 58  //  cv1
#define STR_RES__CV2 59  //  cv2
#define STR_RES_BIT 60  // bit
#define STR_RES_CUTOFF 61  // cutoff
#define STR_RES__VCA 62  //  vca
#define STR_RES_PWM1 63  // pwm1
#define STR_RES_PWM2 64  // pwm2
#define STR_RES_OSC1 65  // osc1
#define STR_RES_OSC2 66  // osc2
#define STR_RES_OSC1S2 67  // osc1+2
#define STR_RES__MIX 68  //  mix
#define STR_RES__NOISE 69  //  noise
#define STR_RES_SUBOSC 70  // subosc
#define STR_RES_RESO 71  // reso
#define STR_RES__CV_1 72  //  cv 1
#define STR_RES__CV_2 73  //  cv 2
#define STR_RES_2_BITS 74  // 2 bits
#define STR_RES_MUTABLE 75  // mutable
#define STR_RES_INSTRUMENTS_671 76  // instruments -1
#define STR_RES_ATK 77  // atk
#define STR_RES_WV1 78  // wv1
#define STR_RES_RT1 79  // rt1
#define STR_RES_WV2 80  // wv2
#define STR_RES_RT2 81  // rt2
#define STR_RES_SRC 82  // src
#define STR_RES_DST 83  // dst
#define STR_RES_AMT 84  // amt
#define STR_RES_CHN 85  // chn
#define STR_RES_BPM 86  // bpm
#define STR_RES_SWG 87  // swg
#define STR_RES_SHAPE 88  // shape
#define STR_RES_ENV1TVCF 89  // env1~vcf
#define STR_RES_LFO2TVCF 90  // lfo2~vcf
#define STR_RES_RESONANCE 91  // resonance
#define STR_RES_ENVELOPE_1 92  // envelope 1
#define STR_RES_ENVELOPE_2 93  // envelope 2
#define STR_RES_SEQUENCER 94  // sequencer
#define STR_RES_ATTACK 95  // attack
#define STR_RES_DECAY 96  // decay
#define STR_RES_SUSTAIN 97  // sustain
#define STR_RES_RELEASE 98  // release
#define STR_RES_RATE 99  // rate
#define STR_RES_MOD_ 100  // mod.
#define STR_RES_SOURCE 101  // source
#define STR_RES_DEST_ 102  // dest.
#define STR_RES_AMOUNT 103  // amount
#define STR_RES_OCTAVE 104  // octave
#define STR_RES_RAGA 105  // raga
#define STR_RES_MIDI_CHAN 106  // midi chan
#define STR_RES_TEMPO 107  // tempo
#define STR_RES_MIXER 108  // mixer
#define STR_RES_FILTER 109  // filter
#define STR_RES_MODULATION 110  // modulation
#define STR_RES_KEYBOARD 111  // keyboard
#define STR_RES_MIDI 112  // midi
#define STR_RES_OFF 113  // off
#define STR_RES_ON 114  // on
#define STR_RES_TRI 115  // tri
#define STR_RES_SQR 116  // sqr
#define STR_RES_S_H 117  // s&h
#define STR_RES_3 118  // 
#define STR_RES_LF1 119  // lf1
#define STR_RES_LF2 120  // lf2
#define STR_RES_SEQ 121  // seq
#define STR_RES_ARP 122  // arp
#define STR_RES_WHL 123  // whl
#define STR_RES_BND 124  // bnd
#define STR_RES_OFS 125  // ofs
#define STR_RES_CV1 126  // cv1
#define STR_RES_CV2 127  // cv2
#define STR_RES_CV3 128  // cv3
#define STR_RES_RND 129  // rnd
#define STR_RES_EN1 130  // en1
#define STR_RES_EN2 131  // en2
#define STR_RES_VEL 132  // vel
#define STR_RES_NOT 133  // not
#define STR_RES_GAT 134  // gat
#define STR_RES_LFO_1 135  // lfo 1
#define STR_RES_LFO_2 136  // lfo 2
#define STR_RES_STPSEQ 137  // stpseq
#define STR_RES__ARP 138  //  arp
#define STR_RES_MWHEEL 139  // mwheel
#define STR_RES_BENDER 140  // bender
#define STR_RES_OFFSET 141  // offset
#define STR_RES_CV_1 142  // cv 1
#define STR_RES_CV_2 143  // cv 2
#define STR_RES_CV_3 144  // cv 3
#define STR_RES_RANDOM 145  // random
#define STR_RES_ENV_1 146  // env 1
#define STR_RES_ENV_2 147  // env 2
#define STR_RES_VELO 148  // velo
#define STR_RES_NOTE 149  // note
#define STR_RES_GATE 150  // gate
#define STR_RES__OFF 151  //  off
#define STR_RES_THRU 152  // thru
#define STR_RES_CTRL 153  // ctrl
#define STR_RES__SEQ 154  //  seq
#define STR_RES_POLY 155  // poly
#define STR_RES_TOUCH_A_KNOB_TO 156  // touch a knob to
#define STR_RES_ASSIGN_PARAMETER 157  // assign parameter
#define STR_RES_READY 158  // ready
#define STR_RES_FOR_OS_UPDATE 159  // for os update
#define STR_RES_PATCH_BANK 160  // patch bank
#define STR_RES_STEP_SEQUENCER 161  // step sequencer
#define STR_RES_LOAD 162  // load
#define STR_RES_ 163  // ----
#define STR_RES_SAVE 164  // save
#define STR_RES_EXTERN 165  // extern
#define STR_RES_EQUAL 166  // equal
#define STR_RES_JUST 167  // just
#define STR_RES_PYTHAG 168  // pythag
#define STR_RES_1_4_EB 169  // 1/4 eb
#define STR_RES_1_4_E 170  // 1/4 e
#define STR_RES_1_4_EA 171  // 1/4 ea
#define STR_RES_KANAKA 172  // kanaka
#define STR_RES_RATNAN 173  // ratnan
#define STR_RES_GANAMU 174  // ganamu
#define STR_RES_VANASP 175  // vanasp
#define STR_RES_MANAVA 176  // manava
#define STR_RES_TANARU 177  // tanaru
#define STR_RES_SENAVA 178  // senava
#define STR_RES_HANUMA 179  // hanuma
#define STR_RES_DHENUK 180  // dhenuk
#define STR_RES_NATAKA 181  // nataka
#define STR_RES_KOKILA 182  // kokila
#define STR_RES_RUPAVA 183  // rupava
#define STR_RES_GAYAKA 184  // gayaka
#define STR_RES_VAKULA 185  // vakula
#define STR_RES_MAYAMA 186  // mayama
#define STR_RES_CHAKRA 187  // chakra
#define STR_RES_SURYAK 188  // suryak
#define STR_RES_HATAKA 189  // hataka
#define STR_RES_JHANKA 190  // jhanka
#define STR_RES_NATABH 191  // natabh
#define STR_RES_KEERAV 192  // keerav
#define STR_RES_KHARAH 193  // kharah
#define STR_RES_GOURIM 194  // gourim
#define STR_RES_VARUNA 195  // varuna
#define STR_RES_MARARA 196  // marara
#define STR_RES_CHARUK 197  // charuk
#define STR_RES_SARASA 198  // sarasa
#define STR_RES_HARIKA 199  // harika
#define STR_RES_DHEERA 200  // dheera
#define STR_RES_NAGANA 201  // nagana
#define STR_RES_YAGAPR 202  // yagapr
#define STR_RES_RAGAVA 203  // ragava
#define STR_RES_GANGEY 204  // gangey
#define STR_RES_VAGADH 205  // vagadh
#define STR_RES_SHULIN 206  // shulin
#define STR_RES_CHALAN 207  // chalan
#define STR_RES_SALAGA 208  // salaga
#define STR_RES_JALARN 209  // jalarn
#define STR_RES_JHALAV 210  // jhalav
#define STR_RES_NAVANE 211  // navane
#define STR_RES_PAVANI 212  // pavani
#define STR_RES_RAGHUP 213  // raghup
#define STR_RES_GAVAMB 214  // gavamb
#define STR_RES_BHAVAP 215  // bhavap
#define STR_RES_SHUBHA 216  // shubha
#define STR_RES_SHADVI 217  // shadvi
#define STR_RES_SUVARN 218  // suvarn
#define STR_RES_DIVYAM 219  // divyam
#define STR_RES_DHAVAL 220  // dhaval
#define STR_RES_NAMANA 221  // namana
#define STR_RES_KAMAVA 222  // kamava
#define STR_RES_RAMAPR 223  // ramapr
#define STR_RES_GAMANA 224  // gamana
#define STR_RES_VISHWA 225  // vishwa
#define STR_RES_SHAMAL 226  // shamal
#define STR_RES_SHANMU 227  // shanmu
#define STR_RES_SIMHEN 228  // simhen
#define STR_RES_HEMAVA 229  // hemava
#define STR_RES_DHARMA 230  // dharma
#define STR_RES_NEETIM 231  // neetim
#define STR_RES_KANTAM 232  // kantam
#define STR_RES_RISHAB 233  // rishab
#define STR_RES_LATANG 234  // latang
#define STR_RES_VACHAS 235  // vachas
#define STR_RES_MECHAK 236  // mechak
#define STR_RES_CHITRA 237  // chitra
#define STR_RES_SUCHAR 238  // suchar
#define STR_RES_JYOTIS 239  // jyotis
#define STR_RES_DHATUV 240  // dhatuv
#define STR_RES_NASIKA 241  // nasika
#define STR_RES_KOSALA 242  // kosala
#define STR_RES_RASIKA 243  // rasika
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
#define WAV_RES_WAVETABLE_1 29
#define WAV_RES_WAVETABLE_1_SIZE 4112
#define WAV_RES_WAVETABLE_2 30
#define WAV_RES_WAVETABLE_2_SIZE 4112
#define WAV_RES_WAVETABLE_3 31
#define WAV_RES_WAVETABLE_3_SIZE 4112
#define WAV_RES_WAVETABLE_4 32
#define WAV_RES_WAVETABLE_4_SIZE 4112
#define WAV_RES_WAVETABLE_5 33
#define WAV_RES_WAVETABLE_5_SIZE 4112
#define WAV_RES_WAVETABLE_6 34
#define WAV_RES_WAVETABLE_6_SIZE 4112
#define WAV_RES_VOWEL_DATA 35
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
