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

typedef uint16_t ResourceId;

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
extern const prog_uint8_t wav_res_expansion_krama[] PROGMEM;
extern const prog_uint8_t wav_res_expansion_jata[] PROGMEM;
extern const prog_uint8_t wav_res_expansion_sikha[] PROGMEM;
extern const prog_uint8_t wav_res_expansion_ghana[] PROGMEM;
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
#define STR_RES_DIRECTION 16  // direction
#define STR_RES_PATTERN 17  // pattern
#define STR_RES_SWING 18  // swing
#define STR_RES_OSCILLATOR_1 19  // oscillator 1
#define STR_RES_OSCILLATOR_2 20  // oscillator 2
#define STR_RES_ARPEGGIO 21  // arpeggio
#define STR_RES_PERFORMANCE 22  // performance
#define STR_RES_NONE 23  // none
#define STR_RES_SAW 24  // saw
#define STR_RES_SQUARE 25  // square
#define STR_RES_TRIANG 26  // triang
#define STR_RES_ZSAW 27  // zsaw
#define STR_RES_ZRESO 28  // zreso
#define STR_RES_ZTRI 29  // ztri
#define STR_RES_ZPULSE 30  // zpulse
#define STR_RES_ZSYNC 31  // zsync
#define STR_RES_FM 32  // fm
#define STR_RES_BELL 33  // bell
#define STR_RES_DRONE 34  // drone
#define STR_RES_FEMALE 35  // female
#define STR_RES_MALE 36  // male
#define STR_RES_SINES 37  // sines
#define STR_RES_WAVES 38  // waves
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
#define STR_RES_2BT 60  // 2bt
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
#define STR_RES_ATK 75  // atk
#define STR_RES_WV1 76  // wv1
#define STR_RES_RT1 77  // rt1
#define STR_RES_WV2 78  // wv2
#define STR_RES_RT2 79  // rt2
#define STR_RES_SRC 80  // src
#define STR_RES_DST 81  // dst
#define STR_RES_AMT 82  // amt
#define STR_RES_CHN 83  // chn
#define STR_RES_BPM 84  // bpm
#define STR_RES_SWG 85  // swg
#define STR_RES_SHAPE 86  // shape
#define STR_RES_ENV1TVCF 87  // env1~vcf
#define STR_RES_LFO2TVCF 88  // lfo2~vcf
#define STR_RES_RESONANCE 89  // resonance
#define STR_RES_ENVELOPE_1 90  // envelope 1
#define STR_RES_ENVELOPE_2 91  // envelope 2
#define STR_RES_SEQUENCER 92  // sequencer
#define STR_RES_ATTACK 93  // attack
#define STR_RES_DECAY 94  // decay
#define STR_RES_SUSTAIN 95  // sustain
#define STR_RES_RELEASE 96  // release
#define STR_RES_RATE 97  // rate
#define STR_RES_MOD_ 98  // mod.
#define STR_RES_SOURCE 99  // source
#define STR_RES_DEST_ 100  // dest.
#define STR_RES_AMOUNT 101  // amount
#define STR_RES_OCTAVE 102  // octave
#define STR_RES_RAGA 103  // raga
#define STR_RES_MIDI_CHAN 104  // midi chan
#define STR_RES_TEMPO 105  // tempo
#define STR_RES_MIXER 106  // mixer
#define STR_RES_FILTER 107  // filter
#define STR_RES_MODULATION 108  // modulation
#define STR_RES_KEYBOARD 109  // keyboard
#define STR_RES_MIDI 110  // midi
#define STR_RES_OFF 111  // off
#define STR_RES_ON 112  // on
#define STR_RES_TRI 113  // tri
#define STR_RES_SQR 114  // sqr
#define STR_RES_S_H 115  // s&h
#define STR_RES_3 116  // 
#define STR_RES_4 117  // 
#define STR_RES_34 118  // 
#define STR_RES__ 119  // ?
#define STR_RES_LF1 120  // lf1
#define STR_RES_LF2 121  // lf2
#define STR_RES_SEQ 122  // seq
#define STR_RES_SQ1 123  // sq1
#define STR_RES_SQ2 124  // sq2
#define STR_RES__ARP 125  //  arp
#define STR_RES_WHL 126  // whl
#define STR_RES_AFT 127  // aft
#define STR_RES_BND 128  // bnd
#define STR_RES_OFS 129  // ofs
#define STR_RES_CV1 130  // cv1
#define STR_RES_CV2 131  // cv2
#define STR_RES_CV3 132  // cv3
#define STR_RES_CV4 133  // cv4
#define STR_RES__NOI 134  //  noi
#define STR_RES_EN1 135  // en1
#define STR_RES_EN2 136  // en2
#define STR_RES_VEL 137  // vel
#define STR_RES_RND 138  // rnd
#define STR_RES_NOT 139  // not
#define STR_RES_GAT 140  // gat
#define STR_RES_LFO_1 141  // lfo 1
#define STR_RES_LFO_2 142  // lfo 2
#define STR_RES_STPSEQ 143  // stpseq
#define STR_RES_STPSQ1 144  // stpsq1
#define STR_RES_STPSQ2 145  // stpsq2
#define STR_RES___ARP 146  //   arp
#define STR_RES_MWHEEL 147  // mwheel
#define STR_RES_AFTTCH 148  // afttch
#define STR_RES_BENDER 149  // bender
#define STR_RES_OFFSET 150  // offset
#define STR_RES_CV_1 151  // cv 1
#define STR_RES_CV_2 152  // cv 2
#define STR_RES_CV_3 153  // cv 3
#define STR_RES_CV_4 154  // cv 4
#define STR_RES___NOISE 155  //   noise
#define STR_RES_ENV_1 156  // env 1
#define STR_RES_ENV_2 157  // env 2
#define STR_RES_VELO 158  // velo
#define STR_RES_RANDOM 159  // random
#define STR_RES_NOTE 160  // note
#define STR_RES_GATE 161  // gate
#define STR_RES__OFF 162  //  off
#define STR_RES_THRU 163  // thru
#define STR_RES_CTRL 164  // ctrl
#define STR_RES___SEQ 165  //   seq
#define STR_RES_POLY 166  // poly
#define STR_RES_MODE 167  // mode
#define STR_RES_STP 168  // stp
#define STR_RES_ARP 169  // arp
#define STR_RES__SEQ 170  //  seq
#define STR_RES_RPS 171  // rps
#define STR_RES_FLOW 172  // flow
#define STR_RES_T 173  // ~
#define STR_RES___ 174  //  
#define STR_RES_T_ 175  // ~-
#define STR_RES__T_ 176  //  ~
#define STR_RES_KRAMA 177  // krama
#define STR_RES_JATA 178  // jata
#define STR_RES_SIKHA 179  // sikha
#define STR_RES_GHANA 180  // ghana
#define STR_RES_2KRAMA 181  // 2krama
#define STR_RES_2JATA 182  // 2jata
#define STR_RES_2SIKHA 183  // 2sikha
#define STR_RES_2GHANA 184  // 2ghana
#define STR_RES_4KRAMA 185  // 4krama
#define STR_RES_4JATA 186  // 4jata
#define STR_RES_4SIKHA 187  // 4sikha
#define STR_RES_4GHANA 188  // 4ghana
#define STR_RES_KBD 189  // kbd
#define STR_RES____SEQ 190  //    seq
#define STR_RES_TOUCH_A_KNOB_TO 191  // touch a knob to
#define STR_RES_ASSIGN_PARAMETER 192  // assign parameter
#define STR_RES_READY 193  // ready
#define STR_RES_FOR_OS_UPDATE 194  // for os update
#define STR_RES_PATCH_BANK 195  // patch bank
#define STR_RES_SEQUENCES 196  // sequences
#define STR_RES_SYSTEM_SETTINGS 197  // system settings
#define STR_RES_STEP_SEQUENCER 198  // step sequencer
#define STR_RES_LOAD 199  // load
#define STR_RES_ 200  // ----
#define STR_RES_SAVE 201  // save
#define STR_RES_V 202  // v
#define STR_RES_MUTABLE____V1_00 203  // mutable    v1.00
#define STR_RES_INSTRUMENTS_671 204  // instruments -1
#define STR_RES_EXTERN 205  // extern
#define STR_RES_EQUAL 206  // equal
#define STR_RES_JUST 207  // just
#define STR_RES_PYTHAG 208  // pythag
#define STR_RES_1_4_EB 209  // 1/4 eb
#define STR_RES_1_4_E 210  // 1/4 e
#define STR_RES_1_4_EA 211  // 1/4 ea
#define STR_RES_KANAKA 212  // kanaka
#define STR_RES_RATNAN 213  // ratnan
#define STR_RES_GANAMU 214  // ganamu
#define STR_RES_VANASP 215  // vanasp
#define STR_RES_MANAVA 216  // manava
#define STR_RES_TANARU 217  // tanaru
#define STR_RES_SENAVA 218  // senava
#define STR_RES_HANUMA 219  // hanuma
#define STR_RES_DHENUK 220  // dhenuk
#define STR_RES_NATAKA 221  // nataka
#define STR_RES_KOKILA 222  // kokila
#define STR_RES_RUPAVA 223  // rupava
#define STR_RES_GAYAKA 224  // gayaka
#define STR_RES_VAKULA 225  // vakula
#define STR_RES_MAYAMA 226  // mayama
#define STR_RES_CHAKRA 227  // chakra
#define STR_RES_SURYAK 228  // suryak
#define STR_RES_HATAKA 229  // hataka
#define STR_RES_JHANKA 230  // jhanka
#define STR_RES_NATABH 231  // natabh
#define STR_RES_KEERAV 232  // keerav
#define STR_RES_KHARAH 233  // kharah
#define STR_RES_GOURIM 234  // gourim
#define STR_RES_VARUNA 235  // varuna
#define STR_RES_MARARA 236  // marara
#define STR_RES_CHARUK 237  // charuk
#define STR_RES_SARASA 238  // sarasa
#define STR_RES_HARIKA 239  // harika
#define STR_RES_DHEERA 240  // dheera
#define STR_RES_NAGANA 241  // nagana
#define STR_RES_YAGAPR 242  // yagapr
#define STR_RES_RAGAVA 243  // ragava
#define STR_RES_GANGEY 244  // gangey
#define STR_RES_VAGADH 245  // vagadh
#define STR_RES_SHULIN 246  // shulin
#define STR_RES_CHALAN 247  // chalan
#define STR_RES_SALAGA 248  // salaga
#define STR_RES_JALARN 249  // jalarn
#define STR_RES_JHALAV 250  // jhalav
#define STR_RES_NAVANE 251  // navane
#define STR_RES_PAVANI 252  // pavani
#define STR_RES_RAGHUP 253  // raghup
#define STR_RES_GAVAMB 254  // gavamb
#define STR_RES_BHAVAP 255  // bhavap
#define STR_RES_SHUBHA 256  // shubha
#define STR_RES_SHADVI 257  // shadvi
#define STR_RES_SUVARN 258  // suvarn
#define STR_RES_DIVYAM 259  // divyam
#define STR_RES_DHAVAL 260  // dhaval
#define STR_RES_NAMANA 261  // namana
#define STR_RES_KAMAVA 262  // kamava
#define STR_RES_RAMAPR 263  // ramapr
#define STR_RES_GAMANA 264  // gamana
#define STR_RES_VISHWA 265  // vishwa
#define STR_RES_SHAMAL 266  // shamal
#define STR_RES_SHANMU 267  // shanmu
#define STR_RES_SIMHEN 268  // simhen
#define STR_RES_HEMAVA 269  // hemava
#define STR_RES_DHARMA 270  // dharma
#define STR_RES_NEETIM 271  // neetim
#define STR_RES_KANTAM 272  // kantam
#define STR_RES_RISHAB 273  // rishab
#define STR_RES_LATANG 274  // latang
#define STR_RES_VACHAS 275  // vachas
#define STR_RES_MECHAK 276  // mechak
#define STR_RES_CHITRA 277  // chitra
#define STR_RES_SUCHAR 278  // suchar
#define STR_RES_JYOTIS 279  // jyotis
#define STR_RES_DHATUV 280  // dhatuv
#define STR_RES_NASIKA 281  // nasika
#define STR_RES_KOSALA 282  // kosala
#define STR_RES_RASIKA 283  // rasika
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
#define WAV_RES_BANDLIMITED_SQUARE_0 2
#define WAV_RES_BANDLIMITED_SQUARE_0_SIZE 257
#define WAV_RES_BANDLIMITED_SQUARE_1 3
#define WAV_RES_BANDLIMITED_SQUARE_1_SIZE 257
#define WAV_RES_BANDLIMITED_SQUARE_2 4
#define WAV_RES_BANDLIMITED_SQUARE_2_SIZE 257
#define WAV_RES_BANDLIMITED_SQUARE_3 5
#define WAV_RES_BANDLIMITED_SQUARE_3_SIZE 257
#define WAV_RES_BANDLIMITED_SQUARE_4 6
#define WAV_RES_BANDLIMITED_SQUARE_4_SIZE 257
#define WAV_RES_BANDLIMITED_SQUARE_5 7
#define WAV_RES_BANDLIMITED_SQUARE_5_SIZE 257
#define WAV_RES_BANDLIMITED_SQUARE_6 8
#define WAV_RES_BANDLIMITED_SQUARE_6_SIZE 257
#define WAV_RES_BANDLIMITED_SAW_0 9
#define WAV_RES_BANDLIMITED_SAW_0_SIZE 257
#define WAV_RES_BANDLIMITED_SAW_1 10
#define WAV_RES_BANDLIMITED_SAW_1_SIZE 257
#define WAV_RES_BANDLIMITED_SAW_2 11
#define WAV_RES_BANDLIMITED_SAW_2_SIZE 257
#define WAV_RES_BANDLIMITED_SAW_3 12
#define WAV_RES_BANDLIMITED_SAW_3_SIZE 257
#define WAV_RES_BANDLIMITED_SAW_4 13
#define WAV_RES_BANDLIMITED_SAW_4_SIZE 257
#define WAV_RES_BANDLIMITED_SAW_5 14
#define WAV_RES_BANDLIMITED_SAW_5_SIZE 257
#define WAV_RES_BANDLIMITED_SAW_6 15
#define WAV_RES_BANDLIMITED_SAW_6_SIZE 257
#define WAV_RES_BANDLIMITED_TRIANGLE_0 16
#define WAV_RES_BANDLIMITED_TRIANGLE_0_SIZE 257
#define WAV_RES_BANDLIMITED_TRIANGLE_1 17
#define WAV_RES_BANDLIMITED_TRIANGLE_1_SIZE 257
#define WAV_RES_BANDLIMITED_TRIANGLE_2 18
#define WAV_RES_BANDLIMITED_TRIANGLE_2_SIZE 257
#define WAV_RES_BANDLIMITED_TRIANGLE_3 19
#define WAV_RES_BANDLIMITED_TRIANGLE_3_SIZE 257
#define WAV_RES_BANDLIMITED_TRIANGLE_4 20
#define WAV_RES_BANDLIMITED_TRIANGLE_4_SIZE 257
#define WAV_RES_BANDLIMITED_TRIANGLE_5 21
#define WAV_RES_BANDLIMITED_TRIANGLE_5_SIZE 257
#define WAV_RES_BANDLIMITED_TRIANGLE_6 22
#define WAV_RES_BANDLIMITED_TRIANGLE_6_SIZE 257
#define WAV_RES_WAVETABLE_1 23
#define WAV_RES_WAVETABLE_1_SIZE 4112
#define WAV_RES_WAVETABLE_2 24
#define WAV_RES_WAVETABLE_2_SIZE 4112
#define WAV_RES_WAVETABLE_3 25
#define WAV_RES_WAVETABLE_3_SIZE 4112
#define WAV_RES_WAVETABLE_4 26
#define WAV_RES_WAVETABLE_4_SIZE 4112
#define WAV_RES_WAVETABLE_5 27
#define WAV_RES_WAVETABLE_5_SIZE 4112
#define WAV_RES_WAVETABLE_6 28
#define WAV_RES_WAVETABLE_6_SIZE 4112
#define WAV_RES_VOWEL_DATA 29
#define WAV_RES_VOWEL_DATA_SIZE 45
#define WAV_RES_EXPANSION_KRAMA 30
#define WAV_RES_EXPANSION_KRAMA_SIZE 30
#define WAV_RES_EXPANSION_JATA 31
#define WAV_RES_EXPANSION_JATA_SIZE 90
#define WAV_RES_EXPANSION_SIKHA 32
#define WAV_RES_EXPANSION_SIKHA_SIZE 126
#define WAV_RES_EXPANSION_GHANA 33
#define WAV_RES_EXPANSION_GHANA_SIZE 182
#define CHR_RES_SPECIAL_CHARACTERS 0
#define CHR_RES_SPECIAL_CHARACTERS_SIZE 64
typedef hardware_resources::ResourcesManager<
    ResourceId,
    hardware_resources::ResourcesTables<
        string_table,
        lookup_table_table> > ResourcesManager; 

}  // namespace hardware_shruthi

#endif  // HARDWARE_SHRUTHI_RESOURCES_H_
