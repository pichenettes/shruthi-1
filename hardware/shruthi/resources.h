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
#define STR_RES_BELL 31  // bell
#define STR_RES_DRONE 32  // drone
#define STR_RES_FEMALE 33  // female
#define STR_RES_MALE 34  // male
#define STR_RES_SINES 35  // sines
#define STR_RES_WAVES 36  // waves
#define STR_RES_8BITS 37  // 8bits
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
#define STR_RES_MIX 60  // mix
#define STR_RES_NOI 61  // noi
#define STR_RES_SUB 62  // sub
#define STR_RES_RES 63  // res
#define STR_RES__CV1 64  //  cv1
#define STR_RES__CV2 65  //  cv2
#define STR_RES_2BT 66  // 2bt
#define STR_RES_CUTOFF 67  // cutoff
#define STR_RES__VCA 68  //  vca
#define STR_RES_PWM1 69  // pwm1
#define STR_RES_PWM2 70  // pwm2
#define STR_RES_OSC1 71  // osc1
#define STR_RES_OSC2 72  // osc2
#define STR_RES_OSC1S2 73  // osc1+2
#define STR_RES__MIX 74  //  mix
#define STR_RES__NOISE 75  //  noise
#define STR_RES_SUBOSC 76  // subosc
#define STR_RES_RESO 77  // reso
#define STR_RES__CV_1 78  //  cv 1
#define STR_RES__CV_2 79  //  cv 2
#define STR_RES_2_BITS 80  // 2 bits
#define STR_RES_ATK 81  // atk
#define STR_RES_WV1 82  // wv1
#define STR_RES_RT1 83  // rt1
#define STR_RES_WV2 84  // wv2
#define STR_RES_RT2 85  // rt2
#define STR_RES_SRC 86  // src
#define STR_RES_DST 87  // dst
#define STR_RES_AMT 88  // amt
#define STR_RES_CHN 89  // chn
#define STR_RES_BPM 90  // bpm
#define STR_RES_SWG 91  // swg
#define STR_RES_SHAPE 92  // shape
#define STR_RES_ENV1TVCF 93  // env1~vcf
#define STR_RES_LFO2TVCF 94  // lfo2~vcf
#define STR_RES_RESONANCE 95  // resonance
#define STR_RES_ENVELOPE_1 96  // envelope 1
#define STR_RES_ENVELOPE_2 97  // envelope 2
#define STR_RES_SEQUENCER 98  // sequencer
#define STR_RES_ATTACK 99  // attack
#define STR_RES_DECAY 100  // decay
#define STR_RES_SUSTAIN 101  // sustain
#define STR_RES_RELEASE 102  // release
#define STR_RES_RATE 103  // rate
#define STR_RES_MOD_ 104  // mod.
#define STR_RES_SOURCE 105  // source
#define STR_RES_DEST_ 106  // dest.
#define STR_RES_AMOUNT 107  // amount
#define STR_RES_OCTAVE 108  // octave
#define STR_RES_RAGA 109  // raga
#define STR_RES_MIDI_CHAN 110  // midi chan
#define STR_RES_TEMPO 111  // tempo
#define STR_RES_MIXER 112  // mixer
#define STR_RES_FILTER 113  // filter
#define STR_RES_MODULATION 114  // modulation
#define STR_RES_KEYBOARD 115  // keyboard
#define STR_RES_MIDI 116  // midi
#define STR_RES_OFF 117  // off
#define STR_RES_ON 118  // on
#define STR_RES_TRI 119  // tri
#define STR_RES_SQR 120  // sqr
#define STR_RES_S_H 121  // s&h
#define STR_RES_RAMP 122  // ramp
#define STR_RES_STEP 123  // step
#define STR_RES_3 124  // 
#define STR_RES_4 125  // 
#define STR_RES_34 126  // 
#define STR_RES__ 127  // ?
#define STR_RES_LF1 128  // lf1
#define STR_RES_LF2 129  // lf2
#define STR_RES_SEQ 130  // seq
#define STR_RES_SQ1 131  // sq1
#define STR_RES_SQ2 132  // sq2
#define STR_RES__ARP 133  //  arp
#define STR_RES_WHL 134  // whl
#define STR_RES_AFT 135  // aft
#define STR_RES_BND 136  // bnd
#define STR_RES_OFS 137  // ofs
#define STR_RES_CV1 138  // cv1
#define STR_RES_CV2 139  // cv2
#define STR_RES_CV3 140  // cv3
#define STR_RES_CV4 141  // cv4
#define STR_RES__NOI 142  //  noi
#define STR_RES_EN1 143  // en1
#define STR_RES_EN2 144  // en2
#define STR_RES_VEL 145  // vel
#define STR_RES_RND 146  // rnd
#define STR_RES_NOT 147  // not
#define STR_RES_GAT 148  // gat
#define STR_RES_LFO_1 149  // lfo 1
#define STR_RES_LFO_2 150  // lfo 2
#define STR_RES_STPSEQ 151  // stpseq
#define STR_RES_STPSQ1 152  // stpsq1
#define STR_RES_STPSQ2 153  // stpsq2
#define STR_RES___ARP 154  //   arp
#define STR_RES_MWHEEL 155  // mwheel
#define STR_RES_AFTTCH 156  // afttch
#define STR_RES_BENDER 157  // bender
#define STR_RES_OFFSET 158  // offset
#define STR_RES_CV_1 159  // cv 1
#define STR_RES_CV_2 160  // cv 2
#define STR_RES_CV_3 161  // cv 3
#define STR_RES_CV_4 162  // cv 4
#define STR_RES___NOISE 163  //   noise
#define STR_RES_ENV_1 164  // env 1
#define STR_RES_ENV_2 165  // env 2
#define STR_RES_VELO 166  // velo
#define STR_RES_RANDOM 167  // random
#define STR_RES_NOTE 168  // note
#define STR_RES_GATE 169  // gate
#define STR_RES__OFF 170  //  off
#define STR_RES_THRU 171  // thru
#define STR_RES_CTRL 172  // ctrl
#define STR_RES___SEQ 173  //   seq
#define STR_RES_POLY 174  // poly
#define STR_RES_MODE 175  // mode
#define STR_RES_STP 176  // stp
#define STR_RES_ARP 177  // arp
#define STR_RES_ARPSLT 178  // arp+lt
#define STR_RES__SEQ 179  //  seq
#define STR_RES_SEQSLT 180  // seq+lt
#define STR_RES_IMPRO 181  // impro
#define STR_RES_FREE 182  // free
#define STR_RES_SLAVE 183  // slave
#define STR_RES_MASTER 184  // master
#define STR_RES_FLOW 185  // flow
#define STR_RES_T 186  // ~
#define STR_RES___ 187  //  
#define STR_RES_T_ 188  // ~-
#define STR_RES__T_ 189  //  ~
#define STR_RES_KRAMA 190  // krama
#define STR_RES_JATA 191  // jata
#define STR_RES_SIKHA 192  // sikha
#define STR_RES_GHANA 193  // ghana
#define STR_RES_2KRAMA 194  // 2krama
#define STR_RES_2JATA 195  // 2jata
#define STR_RES_2SIKHA 196  // 2sikha
#define STR_RES_2GHANA 197  // 2ghana
#define STR_RES_4KRAMA 198  // 4krama
#define STR_RES_4JATA 199  // 4jata
#define STR_RES_4SIKHA 200  // 4sikha
#define STR_RES_4GHANA 201  // 4ghana
#define STR_RES_270 202  // 270
#define STR_RES_300 203  // 300
#define STR_RES_330 204  // 330
#define STR_RES_360 205  // 360
#define STR_RES_420 206  // 420
#define STR_RES_480 207  // 480
#define STR_RES_600 208  // 600
#define STR_RES_720 209  // 720
#define STR_RES_960 210  // 960
#define STR_RES_GROOVE 211  // groove
#define STR_RES_SWING 212  // swing
#define STR_RES_SHUFFLE 213  // shuffle
#define STR_RES_PUSH 214  // push
#define STR_RES_LAG 215  // lag
#define STR_RES_HUMAN 216  // human
#define STR_RES_TOUCH_A_KNOB_TO 217  // touch a knob to
#define STR_RES_ASSIGN_PARAMETER 218  // assign parameter
#define STR_RES_PATCHES 219  // patches
#define STR_RES_SEQUENCES 220  // sequences
#define STR_RES_SYSTEM_SETTINGS 221  // system settings
#define STR_RES_STEP_SEQUENCER 222  // step sequencer
#define STR_RES_LOAD 223  // load
#define STR_RES_ 224  // ----
#define STR_RES_SAVE 225  // save
#define STR_RES_V 226  // v
#define STR_RES_MUTABLE____V1_00 227  // mutable    v1.00
#define STR_RES_INSTRUMENTS_671 228  // instruments -1
#define STR_RES_EXTERN 229  // extern
#define STR_RES_EQUAL 230  // equal
#define STR_RES_JUST 231  // just
#define STR_RES_PYTHAG 232  // pythag
#define STR_RES_1_4_EB 233  // 1/4 eb
#define STR_RES_1_4_E 234  // 1/4 e
#define STR_RES_1_4_EA 235  // 1/4 ea
#define STR_RES_BHAIRA 236  // bhaira
#define STR_RES_GUNAKR 237  // gunakr
#define STR_RES_MARWA 238  // marwa
#define STR_RES_SHREE 239  // shree
#define STR_RES_PURVI 240  // purvi
#define STR_RES_BILAWA 241  // bilawa
#define STR_RES_YAMAN 242  // yaman
#define STR_RES_KAFI 243  // kafi
#define STR_RES_BHIMPA 244  // bhimpa
#define STR_RES_DARBAR 245  // darbar
#define STR_RES_BAGESH 246  // bagesh
#define STR_RES_RAGESH 247  // ragesh
#define STR_RES_KHAMAJ 248  // khamaj
#define STR_RES_MIMAL 249  // mi'mal
#define STR_RES_PARAME 250  // parame
#define STR_RES_RANGES 251  // ranges
#define STR_RES_GANGES 252  // ganges
#define STR_RES_KAMESH 253  // kamesh
#define STR_RES_PALAS_ 254  // palas 
#define STR_RES_NATBHA 255  // natbha
#define STR_RES_M_KAUN 256  // m.kaun
#define STR_RES_BAIRAG 257  // bairag
#define STR_RES_B_TODI 258  // b.todi
#define STR_RES_CHANDR 259  // chandr
#define STR_RES_KAUSHI 260  // kaushi
#define STR_RES_JOGESH 261  // jogesh
#define STR_RES_RASIA 262  // rasia
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
#define WAV_RES_DISTORTION 34
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
