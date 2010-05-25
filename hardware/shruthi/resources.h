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
extern const prog_uint16_t lut_res_scale_bhairav[] PROGMEM;
extern const prog_uint16_t lut_res_scale_gunakri[] PROGMEM;
extern const prog_uint16_t lut_res_scale_marwa[] PROGMEM;
extern const prog_uint16_t lut_res_scale_shree[] PROGMEM;
extern const prog_uint16_t lut_res_scale_purvi[] PROGMEM;
extern const prog_uint16_t lut_res_scale_bilawal[] PROGMEM;
extern const prog_uint16_t lut_res_scale_yaman[] PROGMEM;
extern const prog_uint16_t lut_res_scale_kafi[] PROGMEM;
extern const prog_uint16_t lut_res_scale_bhimpalasree[] PROGMEM;
extern const prog_uint16_t lut_res_scale_darbari[] PROGMEM;
extern const prog_uint16_t lut_res_scale_rageshree[] PROGMEM;
extern const prog_uint16_t lut_res_scale_khamaj[] PROGMEM;
extern const prog_uint16_t lut_res_scale_mimal[] PROGMEM;
extern const prog_uint16_t lut_res_scale_parameshwari[] PROGMEM;
extern const prog_uint16_t lut_res_scale_rangeshwari[] PROGMEM;
extern const prog_uint16_t lut_res_scale_gangeshwari[] PROGMEM;
extern const prog_uint16_t lut_res_scale_kameshwari[] PROGMEM;
extern const prog_uint16_t lut_res_scale_palas_kafi[] PROGMEM;
extern const prog_uint16_t lut_res_scale_natbhairav[] PROGMEM;
extern const prog_uint16_t lut_res_scale_m_kauns[] PROGMEM;
extern const prog_uint16_t lut_res_scale_bairagi[] PROGMEM;
extern const prog_uint16_t lut_res_scale_b_todi[] PROGMEM;
extern const prog_uint16_t lut_res_scale_chandradeep[] PROGMEM;
extern const prog_uint16_t lut_res_scale_kaushik_todi[] PROGMEM;
extern const prog_uint16_t lut_res_scale_jogeshwari[] PROGMEM;
extern const prog_uint16_t lut_res_arpeggiator_patterns[] PROGMEM;
extern const prog_uint16_t lut_res_turbo_tempi[] PROGMEM;
extern const prog_uint16_t lut_res_groove_swing[] PROGMEM;
extern const prog_uint16_t lut_res_groove_shuffle[] PROGMEM;
extern const prog_uint16_t lut_res_groove_push[] PROGMEM;
extern const prog_uint16_t lut_res_groove_lag[] PROGMEM;
extern const prog_uint16_t lut_res_groove_human[] PROGMEM;
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
extern const prog_uint8_t wav_res_wavetable_7[] PROGMEM;
extern const prog_uint8_t wav_res_wavetable_8[] PROGMEM;
extern const prog_uint8_t wav_res_vowel_data[] PROGMEM;
extern const prog_uint8_t wav_res_expansion_krama[] PROGMEM;
extern const prog_uint8_t wav_res_expansion_jata[] PROGMEM;
extern const prog_uint8_t wav_res_expansion_sikha[] PROGMEM;
extern const prog_uint8_t wav_res_expansion_ghana[] PROGMEM;
extern const prog_uint8_t wav_res_distortion[] PROGMEM;
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
#define STR_RES_DIRECTION 14  // direction
#define STR_RES_PATTERN 15  // pattern
#define STR_RES_OSCILLATOR_1 16  // oscillator 1
#define STR_RES_OSCILLATOR_2 17  // oscillator 2
#define STR_RES_ARPEGGIO 18  // arpeggio
#define STR_RES_PERFORMANCE 19  // performance
#define STR_RES_NONE 20  // none
#define STR_RES_SAW 21  // saw
#define STR_RES_SQUARE 22  // square
#define STR_RES_TRIANG 23  // triang
#define STR_RES_ZSAW 24  // zsaw
#define STR_RES_ZRESO 25  // zreso
#define STR_RES_ZTRI 26  // ztri
#define STR_RES_ZPULSE 27  // zpulse
#define STR_RES_ZSYNC 28  // zsync
#define STR_RES_PAD 29  // pad
#define STR_RES_FM 30  // fm
#define STR_RES_WAVES 31  // waves
#define STR_RES_DIGITL 32  // digitl
#define STR_RES_METALC 33  // metalc
#define STR_RES_SLAP 34  // slap
#define STR_RES_BOWED 35  // bowed
#define STR_RES_TAMPURA 36  // tampura
#define STR_RES_MALE 37  // male
#define STR_RES_ORGAN 38  // organ
#define STR_RES_8BITS 39  // 8bits
#define STR_RES_CRUSH 40  // crush
#define STR_RES_PWM 41  // pwm
#define STR_RES_NOISE 42  // noise
#define STR_RES_VOWEL 43  // vowel
#define STR_RES__SQUARE 44  //  square
#define STR_RES__TRIANG 45  //  triang
#define STR_RES_CLICK 46  // click
#define STR_RES_GLITCH 47  // glitch
#define STR_RES_BLOW 48  // blow
#define STR_RES_METAL 49  // metal
#define STR_RES_POP 50  // pop
#define STR_RES_SUM 51  // sum
#define STR_RES_SYNC 52  // sync
#define STR_RES_RING 53  // ring
#define STR_RES_XOR 54  // xor
#define STR_RES_FUZZ 55  // fuzz
#define STR_RES_CUT 56  // cut
#define STR_RES_VCA 57  // vca
#define STR_RES_PW1 58  // pw1
#define STR_RES_PW2 59  // pw2
#define STR_RES_51 60  // 1
#define STR_RES_52 61  // 2
#define STR_RES_5 62  // 
#define STR_RES_MIX 63  // mix
#define STR_RES_NOI 64  // noi
#define STR_RES_SUB 65  // sub
#define STR_RES_RES 66  // res
#define STR_RES__CV1 67  //  cv1
#define STR_RES__CV2 68  //  cv2
#define STR_RES_2BT 69  // 2bt
#define STR_RES_CUTOFF 70  // cutoff
#define STR_RES__VCA 71  //  vca
#define STR_RES_PWM1 72  // pwm1
#define STR_RES_PWM2 73  // pwm2
#define STR_RES_OSC1 74  // osc1
#define STR_RES_OSC2 75  // osc2
#define STR_RES_OSC1S2 76  // osc1+2
#define STR_RES__MIX 77  //  mix
#define STR_RES__NOISE 78  //  noise
#define STR_RES_SUBOSC 79  // subosc
#define STR_RES_RESO 80  // reso
#define STR_RES__CV_1 81  //  cv 1
#define STR_RES__CV_2 82  //  cv 2
#define STR_RES_2_BITS 83  // 2 bits
#define STR_RES_ATK 84  // atk
#define STR_RES_WV1 85  // wv1
#define STR_RES_RT1 86  // rt1
#define STR_RES_WV2 87  // wv2
#define STR_RES_RT2 88  // rt2
#define STR_RES_SRC 89  // src
#define STR_RES_DST 90  // dst
#define STR_RES_AMT 91  // amt
#define STR_RES_CHN 92  // chn
#define STR_RES_BPM 93  // bpm
#define STR_RES_SWG 94  // swg
#define STR_RES_SHAPE 95  // shape
#define STR_RES_ENV1TVCF 96  // env1~vcf
#define STR_RES_LFO2TVCF 97  // lfo2~vcf
#define STR_RES_RESONANCE 98  // resonance
#define STR_RES_ENVELOPE_1 99  // envelope 1
#define STR_RES_ENVELOPE_2 100  // envelope 2
#define STR_RES_SEQUENCER 101  // sequencer
#define STR_RES_ATTACK 102  // attack
#define STR_RES_DECAY 103  // decay
#define STR_RES_SUSTAIN 104  // sustain
#define STR_RES_RELEASE 105  // release
#define STR_RES_RATE 106  // rate
#define STR_RES_MOD_ 107  // mod.
#define STR_RES_SOURCE 108  // source
#define STR_RES_DEST_ 109  // dest.
#define STR_RES_AMOUNT 110  // amount
#define STR_RES_OCTAVE 111  // octave
#define STR_RES_RAGA 112  // raga
#define STR_RES_MIDI_CHAN 113  // midi chan
#define STR_RES_TEMPO 114  // tempo
#define STR_RES_MIXER 115  // mixer
#define STR_RES_FILTER 116  // filter
#define STR_RES_MODULATION 117  // modulation
#define STR_RES_KEYBOARD 118  // keyboard
#define STR_RES_MIDI 119  // midi
#define STR_RES_OFF 120  // off
#define STR_RES_ON 121  // on
#define STR_RES_TRI 122  // tri
#define STR_RES_SQR 123  // sqr
#define STR_RES_S_H 124  // s&h
#define STR_RES_RAMP 125  // ramp
#define STR_RES_STEP 126  // step
#define STR_RES_3 127  // 
#define STR_RES_4 128  // 
#define STR_RES_34 129  // 
#define STR_RES__ 130  // ?
#define STR_RES_LF1 131  // lf1
#define STR_RES_LF2 132  // lf2
#define STR_RES_SEQ 133  // seq
#define STR_RES_SQ1 134  // sq1
#define STR_RES_SQ2 135  // sq2
#define STR_RES__ARP 136  //  arp
#define STR_RES_WHL 137  // whl
#define STR_RES_AFT 138  // aft
#define STR_RES_BND 139  // bnd
#define STR_RES_OFS 140  // ofs
#define STR_RES_CV1 141  // cv1
#define STR_RES_CV2 142  // cv2
#define STR_RES_CV3 143  // cv3
#define STR_RES_CV4 144  // cv4
#define STR_RES_CCA 145  // ccA
#define STR_RES_CCB 146  // ccB
#define STR_RES_CCC 147  // ccC
#define STR_RES_CCD 148  // ccD
#define STR_RES__NOI 149  //  noi
#define STR_RES_EN1 150  // en1
#define STR_RES_EN2 151  // en2
#define STR_RES_VEL 152  // vel
#define STR_RES_RND 153  // rnd
#define STR_RES_NOT 154  // not
#define STR_RES_GAT 155  // gat
#define STR_RES_LFO_1 156  // lfo 1
#define STR_RES_LFO_2 157  // lfo 2
#define STR_RES_STPSEQ 158  // stpseq
#define STR_RES_STPSQ1 159  // stpsq1
#define STR_RES_STPSQ2 160  // stpsq2
#define STR_RES___ARP 161  //   arp
#define STR_RES_MWHEEL 162  // mwheel
#define STR_RES_AFTTCH 163  // afttch
#define STR_RES_BENDER 164  // bender
#define STR_RES_OFFSET 165  // offset
#define STR_RES_CV_1 166  // cv 1
#define STR_RES_CV_2 167  // cv 2
#define STR_RES_CV_3 168  // cv 3
#define STR_RES_CV_4 169  // cv 4
#define STR_RES_CC_A 170  // cc A
#define STR_RES_CC_B 171  // cc B
#define STR_RES_CC_C 172  // cc C
#define STR_RES_CC_D 173  // cc D
#define STR_RES___NOISE 174  //   noise
#define STR_RES_ENV_1 175  // env 1
#define STR_RES_ENV_2 176  // env 2
#define STR_RES_VELO 177  // velo
#define STR_RES_RANDOM 178  // random
#define STR_RES_NOTE 179  // note
#define STR_RES_GATE 180  // gate
#define STR_RES__OFF 181  //  off
#define STR_RES_THRU 182  // thru
#define STR_RES_CTRL 183  // ctrl
#define STR_RES___SEQ 184  //   seq
#define STR_RES_POLY 185  // poly
#define STR_RES_MODE 186  // mode
#define STR_RES_STP 187  // stp
#define STR_RES_ARP 188  // arp
#define STR_RES_ARPSLT 189  // arp+lt
#define STR_RES__SEQ 190  //  seq
#define STR_RES_SEQSLT 191  // seq+lt
#define STR_RES_IMPRO 192  // impro
#define STR_RES_FREE 193  // free
#define STR_RES_SLAVE 194  // slave
#define STR_RES_MASTER 195  // master
#define STR_RES_270 196  // 270
#define STR_RES_300 197  // 300
#define STR_RES_330 198  // 330
#define STR_RES_360 199  // 360
#define STR_RES_420 200  // 420
#define STR_RES_480 201  // 480
#define STR_RES_600 202  // 600
#define STR_RES_720 203  // 720
#define STR_RES_960 204  // 960
#define STR_RES_GROOVE 205  // groove
#define STR_RES_SWING 206  // swing
#define STR_RES_SHUFFLE 207  // shuffle
#define STR_RES_PUSH 208  // push
#define STR_RES_LAG 209  // lag
#define STR_RES_HUMAN 210  // human
#define STR_RES_START 211  // start
#define STR_RES_LENGTH 212  // length
#define STR_RES_FLOW 213  // flow
#define STR_RES_T 214  // ~
#define STR_RES___ 215  //  
#define STR_RES_T_ 216  // ~-
#define STR_RES__T_ 217  //  ~
#define STR_RES_KRAMA 218  // krama
#define STR_RES_JATA 219  // jata
#define STR_RES_SIKHA 220  // sikha
#define STR_RES_GHANA 221  // ghana
#define STR_RES_2KRAMA 222  // 2krama
#define STR_RES_2JATA 223  // 2jata
#define STR_RES_2SIKHA 224  // 2sikha
#define STR_RES_2GHANA 225  // 2ghana
#define STR_RES_4KRAMA 226  // 4krama
#define STR_RES_4JATA 227  // 4jata
#define STR_RES_4SIKHA 228  // 4sikha
#define STR_RES_4GHANA 229  // 4ghana
#define STR_RES_TOUCH_A_KNOB_TO 230  // touch a knob to
#define STR_RES_ASSIGN_PARAMETER 231  // assign parameter
#define STR_RES_PATCHES 232  // patches
#define STR_RES_SEQUENCES 233  // sequences
#define STR_RES_SYSTEM_SETTINGS 234  // system settings
#define STR_RES_STEP_SEQUENCER 235  // step sequencer
#define STR_RES_LOAD 236  // load
#define STR_RES_ 237  // ----
#define STR_RES_SAVE 238  // save
#define STR_RES_V 239  // v
#define STR_RES_MUTABLE____V1_00 240  // mutable    v1.00
#define STR_RES_INSTRUMENTS_671 241  // instruments -1
#define STR_RES_EXTERN 242  // extern
#define STR_RES_EQUAL 243  // equal
#define STR_RES_JUST 244  // just
#define STR_RES_PYTHAG 245  // pythag
#define STR_RES_1_4_EB 246  // 1/4 eb
#define STR_RES_1_4_E 247  // 1/4 e
#define STR_RES_1_4_EA 248  // 1/4 ea
#define STR_RES_BHAIRA 249  // bhaira
#define STR_RES_GUNAKR 250  // gunakr
#define STR_RES_MARWA 251  // marwa
#define STR_RES_SHREE 252  // shree
#define STR_RES_PURVI 253  // purvi
#define STR_RES_BILAWA 254  // bilawa
#define STR_RES_YAMAN 255  // yaman
#define STR_RES_KAFI 256  // kafi
#define STR_RES_BHIMPA 257  // bhimpa
#define STR_RES_DARBAR 258  // darbar
#define STR_RES_BAGESH 259  // bagesh
#define STR_RES_RAGESH 260  // ragesh
#define STR_RES_KHAMAJ 261  // khamaj
#define STR_RES_MIMAL 262  // mi'mal
#define STR_RES_PARAME 263  // parame
#define STR_RES_RANGES 264  // ranges
#define STR_RES_GANGES 265  // ganges
#define STR_RES_KAMESH 266  // kamesh
#define STR_RES_PALAS_ 267  // palas 
#define STR_RES_NATBHA 268  // natbha
#define STR_RES_M_KAUN 269  // m.kaun
#define STR_RES_BAIRAG 270  // bairag
#define STR_RES_B_TODI 271  // b.todi
#define STR_RES_CHANDR 272  // chandr
#define STR_RES_KAUSHI 273  // kaushi
#define STR_RES_JOGESH 274  // jogesh
#define STR_RES_RASIA 275  // rasia
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
#define LUT_RES_SCALE_BHAIRAV 9
#define LUT_RES_SCALE_BHAIRAV_SIZE 12
#define LUT_RES_SCALE_GUNAKRI 10
#define LUT_RES_SCALE_GUNAKRI_SIZE 12
#define LUT_RES_SCALE_MARWA 11
#define LUT_RES_SCALE_MARWA_SIZE 12
#define LUT_RES_SCALE_SHREE 12
#define LUT_RES_SCALE_SHREE_SIZE 12
#define LUT_RES_SCALE_PURVI 13
#define LUT_RES_SCALE_PURVI_SIZE 12
#define LUT_RES_SCALE_BILAWAL 14
#define LUT_RES_SCALE_BILAWAL_SIZE 12
#define LUT_RES_SCALE_YAMAN 15
#define LUT_RES_SCALE_YAMAN_SIZE 12
#define LUT_RES_SCALE_KAFI 16
#define LUT_RES_SCALE_KAFI_SIZE 12
#define LUT_RES_SCALE_BHIMPALASREE 17
#define LUT_RES_SCALE_BHIMPALASREE_SIZE 12
#define LUT_RES_SCALE_DARBARI 18
#define LUT_RES_SCALE_DARBARI_SIZE 12
#define LUT_RES_SCALE_BAGESHREE 19
#define LUT_RES_SCALE_BAGESHREE_SIZE 12
#define LUT_RES_SCALE_RAGESHREE 20
#define LUT_RES_SCALE_RAGESHREE_SIZE 12
#define LUT_RES_SCALE_KHAMAJ 21
#define LUT_RES_SCALE_KHAMAJ_SIZE 12
#define LUT_RES_SCALE_MIMAL 22
#define LUT_RES_SCALE_MIMAL_SIZE 12
#define LUT_RES_SCALE_PARAMESHWARI 23
#define LUT_RES_SCALE_PARAMESHWARI_SIZE 12
#define LUT_RES_SCALE_RANGESHWARI 24
#define LUT_RES_SCALE_RANGESHWARI_SIZE 12
#define LUT_RES_SCALE_GANGESHWARI 25
#define LUT_RES_SCALE_GANGESHWARI_SIZE 12
#define LUT_RES_SCALE_KAMESHWARI 26
#define LUT_RES_SCALE_KAMESHWARI_SIZE 12
#define LUT_RES_SCALE_PALAS_KAFI 27
#define LUT_RES_SCALE_PALAS_KAFI_SIZE 12
#define LUT_RES_SCALE_NATBHAIRAV 28
#define LUT_RES_SCALE_NATBHAIRAV_SIZE 12
#define LUT_RES_SCALE_M_KAUNS 29
#define LUT_RES_SCALE_M_KAUNS_SIZE 12
#define LUT_RES_SCALE_BAIRAGI 30
#define LUT_RES_SCALE_BAIRAGI_SIZE 12
#define LUT_RES_SCALE_B_TODI 31
#define LUT_RES_SCALE_B_TODI_SIZE 12
#define LUT_RES_SCALE_CHANDRADEEP 32
#define LUT_RES_SCALE_CHANDRADEEP_SIZE 12
#define LUT_RES_SCALE_KAUSHIK_TODI 33
#define LUT_RES_SCALE_KAUSHIK_TODI_SIZE 12
#define LUT_RES_SCALE_JOGESHWARI 34
#define LUT_RES_SCALE_JOGESHWARI_SIZE 12
#define LUT_RES_SCALE_RASIA 35
#define LUT_RES_SCALE_RASIA_SIZE 12
#define LUT_RES_ARPEGGIATOR_PATTERNS 36
#define LUT_RES_ARPEGGIATOR_PATTERNS_SIZE 15
#define LUT_RES_TURBO_TEMPI 37
#define LUT_RES_TURBO_TEMPI_SIZE 9
#define LUT_RES_GROOVE_SWING 38
#define LUT_RES_GROOVE_SWING_SIZE 16
#define LUT_RES_GROOVE_SHUFFLE 39
#define LUT_RES_GROOVE_SHUFFLE_SIZE 16
#define LUT_RES_GROOVE_PUSH 40
#define LUT_RES_GROOVE_PUSH_SIZE 16
#define LUT_RES_GROOVE_LAG 41
#define LUT_RES_GROOVE_LAG_SIZE 16
#define LUT_RES_GROOVE_HUMAN 42
#define LUT_RES_GROOVE_HUMAN_SIZE 16
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
#define WAV_RES_WAVETABLE_7 29
#define WAV_RES_WAVETABLE_7_SIZE 4112
#define WAV_RES_WAVETABLE_8 30
#define WAV_RES_WAVETABLE_8_SIZE 4112
#define WAV_RES_VOWEL_DATA 31
#define WAV_RES_VOWEL_DATA_SIZE 45
#define WAV_RES_EXPANSION_KRAMA 32
#define WAV_RES_EXPANSION_KRAMA_SIZE 30
#define WAV_RES_EXPANSION_JATA 33
#define WAV_RES_EXPANSION_JATA_SIZE 90
#define WAV_RES_EXPANSION_SIKHA 34
#define WAV_RES_EXPANSION_SIKHA_SIZE 126
#define WAV_RES_EXPANSION_GHANA 35
#define WAV_RES_EXPANSION_GHANA_SIZE 182
#define WAV_RES_DISTORTION 36
#define WAV_RES_DISTORTION_SIZE 256
#define CHR_RES_SPECIAL_CHARACTERS 0
#define CHR_RES_SPECIAL_CHARACTERS_SIZE 64
typedef hardware_resources::ResourcesManager<
    ResourceId,
    hardware_resources::ResourcesTables<
        string_table,
        lookup_table_table> > ResourcesManager; 

}  // namespace hardware_shruthi

#endif  // HARDWARE_SHRUTHI_RESOURCES_H_
