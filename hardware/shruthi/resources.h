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
extern const prog_uint8_t wav_res_wavetable_3[] PROGMEM;
extern const prog_uint8_t wav_res_wavetable_5[] PROGMEM;
extern const prog_uint8_t wav_res_wavetable_6[] PROGMEM;
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
#define STR_RES_METALC 32  // metalc
#define STR_RES_BOWED 33  // bowed
#define STR_RES_TAMPURA 34  // tampura
#define STR_RES_ORGAN 35  // organ
#define STR_RES_8BITS 36  // 8bits
#define STR_RES_CRUSH 37  // crush
#define STR_RES_PWM 38  // pwm
#define STR_RES_NOISE 39  // noise
#define STR_RES_VOWEL 40  // vowel
#define STR_RES__SQUARE 41  //  square
#define STR_RES__TRIANG 42  //  triang
#define STR_RES_CLICK 43  // click
#define STR_RES_GLITCH 44  // glitch
#define STR_RES_BLOW 45  // blow
#define STR_RES_METAL 46  // metal
#define STR_RES_POP 47  // pop
#define STR_RES_SUM 48  // sum
#define STR_RES_SYNC 49  // sync
#define STR_RES_RING 50  // ring
#define STR_RES_XOR 51  // xor
#define STR_RES_FUZZ 52  // fuzz
#define STR_RES_CUT 53  // cut
#define STR_RES_VCA 54  // vca
#define STR_RES_PW1 55  // pw1
#define STR_RES_PW2 56  // pw2
#define STR_RES_51 57  // 1
#define STR_RES_52 58  // 2
#define STR_RES_5 59  // 
#define STR_RES_5F 60  // f
#define STR_RES_MIX 61  // mix
#define STR_RES_NOI 62  // noi
#define STR_RES_SUB 63  // sub
#define STR_RES_RES 64  // res
#define STR_RES__CV1 65  //  cv1
#define STR_RES__CV2 66  //  cv2
#define STR_RES_2BT 67  // 2bt
#define STR_RES_CUTOFF 68  // cutoff
#define STR_RES__VCA 69  //  vca
#define STR_RES_PWM1 70  // pwm1
#define STR_RES_PWM2 71  // pwm2
#define STR_RES_OSC1 72  // osc1
#define STR_RES_OSC2 73  // osc2
#define STR_RES_OSC1S2 74  // osc1+2
#define STR_RES_FINE 75  // fine
#define STR_RES__MIX 76  //  mix
#define STR_RES__NOISE 77  //  noise
#define STR_RES_SUBOSC 78  // subosc
#define STR_RES_RESO 79  // reso
#define STR_RES__CV_1 80  //  cv 1
#define STR_RES__CV_2 81  //  cv 2
#define STR_RES_2_BITS 82  // 2 bits
#define STR_RES_ATK 83  // atk
#define STR_RES_WV1 84  // wv1
#define STR_RES_RT1 85  // rt1
#define STR_RES_WV2 86  // wv2
#define STR_RES_RT2 87  // rt2
#define STR_RES_SRC 88  // src
#define STR_RES_DST 89  // dst
#define STR_RES_AMT 90  // amt
#define STR_RES_CHN 91  // chn
#define STR_RES_BPM 92  // bpm
#define STR_RES_SWG 93  // swg
#define STR_RES_SHAPE 94  // shape
#define STR_RES_ENV1TVCF 95  // env1~vcf
#define STR_RES_LFO2TVCF 96  // lfo2~vcf
#define STR_RES_RESONANCE 97  // resonance
#define STR_RES_ENVELOPE_1 98  // envelope 1
#define STR_RES_ENVELOPE_2 99  // envelope 2
#define STR_RES_SEQUENCER 100  // sequencer
#define STR_RES_ATTACK 101  // attack
#define STR_RES_DECAY 102  // decay
#define STR_RES_SUSTAIN 103  // sustain
#define STR_RES_RELEASE 104  // release
#define STR_RES_RATE 105  // rate
#define STR_RES_MOD_ 106  // mod.
#define STR_RES_SOURCE 107  // source
#define STR_RES_DEST_ 108  // dest.
#define STR_RES_AMOUNT 109  // amount
#define STR_RES_OCTAVE 110  // octave
#define STR_RES_RAGA 111  // raga
#define STR_RES_MIDI_CHAN 112  // midi chan
#define STR_RES_TEMPO 113  // tempo
#define STR_RES_MIXER 114  // mixer
#define STR_RES_FILTER 115  // filter
#define STR_RES_MODULATION 116  // modulation
#define STR_RES_KEYBOARD 117  // keyboard
#define STR_RES_MIDI 118  // midi
#define STR_RES_OFF 119  // off
#define STR_RES_ON 120  // on
#define STR_RES_TRI 121  // tri
#define STR_RES_SQR 122  // sqr
#define STR_RES_S_H 123  // s&h
#define STR_RES_RAMP 124  // ramp
#define STR_RES_STEP 125  // step
#define STR_RES_3 126  // 
#define STR_RES_4 127  // 
#define STR_RES_34 128  // 
#define STR_RES__ 129  // ?
#define STR_RES_LF1 130  // lf1
#define STR_RES_LF2 131  // lf2
#define STR_RES_SEQ 132  // seq
#define STR_RES_SQ1 133  // sq1
#define STR_RES_SQ2 134  // sq2
#define STR_RES__ARP 135  //  arp
#define STR_RES_WHL 136  // whl
#define STR_RES_AFT 137  // aft
#define STR_RES_BND 138  // bnd
#define STR_RES_OFS 139  // ofs
#define STR_RES_CV1 140  // cv1
#define STR_RES_CV2 141  // cv2
#define STR_RES_CV3 142  // cv3
#define STR_RES_CV4 143  // cv4
#define STR_RES_CCA 144  // ccA
#define STR_RES_CCB 145  // ccB
#define STR_RES_CCC 146  // ccC
#define STR_RES_CCD 147  // ccD
#define STR_RES__NOI 148  //  noi
#define STR_RES_EN1 149  // en1
#define STR_RES_EN2 150  // en2
#define STR_RES_VEL 151  // vel
#define STR_RES_RND 152  // rnd
#define STR_RES_NOT 153  // not
#define STR_RES_GAT 154  // gat
#define STR_RES_AUD 155  // aud
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
#define STR_RES_AUDIO 181  // audio
#define STR_RES__OFF 182  //  off
#define STR_RES_THRU 183  // thru
#define STR_RES_CTRL 184  // ctrl
#define STR_RES___SEQ 185  //   seq
#define STR_RES_1__ 186  // 1>|
#define STR_RES_2_1 187  // 2>1
#define STR_RES_3_2 188  // 3>2
#define STR_RES_4_3 189  // 4>3
#define STR_RES_5_4 190  // 5>4
#define STR_RES_6_5 191  // 6>5
#define STR_RES_7_6 192  // 7>6
#define STR_RES_8_7 193  // 8>7
#define STR_RES_MODE 194  // mode
#define STR_RES_STP 195  // stp
#define STR_RES_ARP 196  // arp
#define STR_RES_ARPSLT 197  // arp+lt
#define STR_RES__SEQ 198  //  seq
#define STR_RES_SEQSLT 199  // seq+lt
#define STR_RES_IMPRO 200  // impro
#define STR_RES_FREE 201  // free
#define STR_RES_SLAVE 202  // slave
#define STR_RES_MASTER 203  // master
#define STR_RES_270 204  // 270
#define STR_RES_300 205  // 300
#define STR_RES_330 206  // 330
#define STR_RES_360 207  // 360
#define STR_RES_420 208  // 420
#define STR_RES_480 209  // 480
#define STR_RES_600 210  // 600
#define STR_RES_720 211  // 720
#define STR_RES_960 212  // 960
#define STR_RES_GROOVE 213  // groove
#define STR_RES_SWING 214  // swing
#define STR_RES_SHUFFLE 215  // shuffle
#define STR_RES_PUSH 216  // push
#define STR_RES_LAG 217  // lag
#define STR_RES_HUMAN 218  // human
#define STR_RES_START 219  // start
#define STR_RES_LENGTH 220  // length
#define STR_RES_FLOW 221  // flow
#define STR_RES_T 222  // ~
#define STR_RES___ 223  //  
#define STR_RES_T_ 224  // ~-
#define STR_RES__T_ 225  //  ~
#define STR_RES_KRAMA 226  // krama
#define STR_RES_JATA 227  // jata
#define STR_RES_SIKHA 228  // sikha
#define STR_RES_GHANA 229  // ghana
#define STR_RES_2KRAMA 230  // 2krama
#define STR_RES_2JATA 231  // 2jata
#define STR_RES_2SIKHA 232  // 2sikha
#define STR_RES_2GHANA 233  // 2ghana
#define STR_RES_4KRAMA 234  // 4krama
#define STR_RES_4JATA 235  // 4jata
#define STR_RES_4SIKHA 236  // 4sikha
#define STR_RES_4GHANA 237  // 4ghana
#define STR_RES_TOUCH_A_KNOB_TO 238  // touch a knob to
#define STR_RES_ASSIGN_PARAMETER 239  // assign parameter
#define STR_RES_PATCH 240  // patch
#define STR_RES_SEQUENCE 241  // sequence
#define STR_RES_SAVE_MIDI_KBD 242  // save midi/kbd
#define STR_RES_SETTINGS_ 243  // settings?
#define STR_RES_START_FULL_MIDI 244  // start full MIDI
#define STR_RES_BACKUP_ 245  // backup?
#define STR_RES_STEP_SEQUENCER 246  // step sequencer
#define STR_RES_LOAD 247  // load
#define STR_RES_SAVE 248  // save
#define STR_RES_COMPARE 249  // compare
#define STR_RES_ 250  // ----
#define STR_RES_V 251  // v
#define STR_RES_MUTABLE____V1_00 252  // mutable    v1.00
#define STR_RES_INSTRUMENTS_671 253  // instruments -1
#define STR_RES_EXTERN 254  // extern
#define STR_RES_EQUAL 255  // equal
#define STR_RES_JUST 256  // just
#define STR_RES_PYTHAG 257  // pythag
#define STR_RES_1_4_EB 258  // 1/4 eb
#define STR_RES_1_4_E 259  // 1/4 e
#define STR_RES_1_4_EA 260  // 1/4 ea
#define STR_RES_BHAIRA 261  // bhaira
#define STR_RES_GUNAKR 262  // gunakr
#define STR_RES_MARWA 263  // marwa
#define STR_RES_SHREE 264  // shree
#define STR_RES_PURVI 265  // purvi
#define STR_RES_BILAWA 266  // bilawa
#define STR_RES_YAMAN 267  // yaman
#define STR_RES_KAFI 268  // kafi
#define STR_RES_BHIMPA 269  // bhimpa
#define STR_RES_DARBAR 270  // darbar
#define STR_RES_BAGESH 271  // bagesh
#define STR_RES_RAGESH 272  // ragesh
#define STR_RES_KHAMAJ 273  // khamaj
#define STR_RES_MIMAL 274  // mi'mal
#define STR_RES_PARAME 275  // parame
#define STR_RES_RANGES 276  // ranges
#define STR_RES_GANGES 277  // ganges
#define STR_RES_KAMESH 278  // kamesh
#define STR_RES_PALAS_ 279  // palas 
#define STR_RES_NATBHA 280  // natbha
#define STR_RES_M_KAUN 281  // m.kaun
#define STR_RES_BAIRAG 282  // bairag
#define STR_RES_B_TODI 283  // b.todi
#define STR_RES_CHANDR 284  // chandr
#define STR_RES_KAUSHI 285  // kaushi
#define STR_RES_JOGESH 286  // jogesh
#define STR_RES_RASIA 287  // rasia
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
#define WAV_RES_WAVETABLE_3 24
#define WAV_RES_WAVETABLE_3_SIZE 4112
#define WAV_RES_WAVETABLE_5 25
#define WAV_RES_WAVETABLE_5_SIZE 4112
#define WAV_RES_WAVETABLE_6 26
#define WAV_RES_WAVETABLE_6_SIZE 4112
#define WAV_RES_WAVETABLE_8 27
#define WAV_RES_WAVETABLE_8_SIZE 4112
#define WAV_RES_VOWEL_DATA 28
#define WAV_RES_VOWEL_DATA_SIZE 45
#define WAV_RES_EXPANSION_KRAMA 29
#define WAV_RES_EXPANSION_KRAMA_SIZE 30
#define WAV_RES_EXPANSION_JATA 30
#define WAV_RES_EXPANSION_JATA_SIZE 90
#define WAV_RES_EXPANSION_SIKHA 31
#define WAV_RES_EXPANSION_SIKHA_SIZE 126
#define WAV_RES_EXPANSION_GHANA 32
#define WAV_RES_EXPANSION_GHANA_SIZE 182
#define WAV_RES_DISTORTION 33
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
