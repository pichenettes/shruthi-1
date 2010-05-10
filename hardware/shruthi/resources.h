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
#define STR_RES_1S2 48  // 1+2
#define STR_RES_1_2 49  // 1>2
#define STR_RES_1P2 50  // 1*2
#define STR_RES_1X2 51  // 1^2
#define STR_RES_CUT 52  // cut
#define STR_RES_VCA 53  // vca
#define STR_RES_PW1 54  // pw1
#define STR_RES_PW2 55  // pw2
#define STR_RES_51 56  // 1
#define STR_RES_52 57  // 2
#define STR_RES_5 58  // 
#define STR_RES_MIX 59  // mix
#define STR_RES_NOI 60  // noi
#define STR_RES_SUB 61  // sub
#define STR_RES_RES 62  // res
#define STR_RES__CV1 63  //  cv1
#define STR_RES__CV2 64  //  cv2
#define STR_RES_2BT 65  // 2bt
#define STR_RES_CUTOFF 66  // cutoff
#define STR_RES__VCA 67  //  vca
#define STR_RES_PWM1 68  // pwm1
#define STR_RES_PWM2 69  // pwm2
#define STR_RES_OSC1 70  // osc1
#define STR_RES_OSC2 71  // osc2
#define STR_RES_OSC1S2 72  // osc1+2
#define STR_RES__MIX 73  //  mix
#define STR_RES__NOISE 74  //  noise
#define STR_RES_SUBOSC 75  // subosc
#define STR_RES_RESO 76  // reso
#define STR_RES__CV_1 77  //  cv 1
#define STR_RES__CV_2 78  //  cv 2
#define STR_RES_2_BITS 79  // 2 bits
#define STR_RES_ATK 80  // atk
#define STR_RES_WV1 81  // wv1
#define STR_RES_RT1 82  // rt1
#define STR_RES_WV2 83  // wv2
#define STR_RES_RT2 84  // rt2
#define STR_RES_SRC 85  // src
#define STR_RES_DST 86  // dst
#define STR_RES_AMT 87  // amt
#define STR_RES_CHN 88  // chn
#define STR_RES_BPM 89  // bpm
#define STR_RES_SWG 90  // swg
#define STR_RES_SHAPE 91  // shape
#define STR_RES_ENV1TVCF 92  // env1~vcf
#define STR_RES_LFO2TVCF 93  // lfo2~vcf
#define STR_RES_RESONANCE 94  // resonance
#define STR_RES_ENVELOPE_1 95  // envelope 1
#define STR_RES_ENVELOPE_2 96  // envelope 2
#define STR_RES_SEQUENCER 97  // sequencer
#define STR_RES_ATTACK 98  // attack
#define STR_RES_DECAY 99  // decay
#define STR_RES_SUSTAIN 100  // sustain
#define STR_RES_RELEASE 101  // release
#define STR_RES_RATE 102  // rate
#define STR_RES_MOD_ 103  // mod.
#define STR_RES_SOURCE 104  // source
#define STR_RES_DEST_ 105  // dest.
#define STR_RES_AMOUNT 106  // amount
#define STR_RES_OCTAVE 107  // octave
#define STR_RES_RAGA 108  // raga
#define STR_RES_MIDI_CHAN 109  // midi chan
#define STR_RES_TEMPO 110  // tempo
#define STR_RES_MIXER 111  // mixer
#define STR_RES_FILTER 112  // filter
#define STR_RES_MODULATION 113  // modulation
#define STR_RES_KEYBOARD 114  // keyboard
#define STR_RES_MIDI 115  // midi
#define STR_RES_OFF 116  // off
#define STR_RES_ON 117  // on
#define STR_RES_TRI 118  // tri
#define STR_RES_SQR 119  // sqr
#define STR_RES_S_H 120  // s&h
#define STR_RES_RAMP 121  // ramp
#define STR_RES_STEP 122  // step
#define STR_RES_3 123  // 
#define STR_RES_4 124  // 
#define STR_RES_34 125  // 
#define STR_RES__ 126  // ?
#define STR_RES_LF1 127  // lf1
#define STR_RES_LF2 128  // lf2
#define STR_RES_SEQ 129  // seq
#define STR_RES_SQ1 130  // sq1
#define STR_RES_SQ2 131  // sq2
#define STR_RES__ARP 132  //  arp
#define STR_RES_WHL 133  // whl
#define STR_RES_AFT 134  // aft
#define STR_RES_BND 135  // bnd
#define STR_RES_OFS 136  // ofs
#define STR_RES_CV1 137  // cv1
#define STR_RES_CV2 138  // cv2
#define STR_RES_CV3 139  // cv3
#define STR_RES_CV4 140  // cv4
#define STR_RES__NOI 141  //  noi
#define STR_RES_EN1 142  // en1
#define STR_RES_EN2 143  // en2
#define STR_RES_VEL 144  // vel
#define STR_RES_RND 145  // rnd
#define STR_RES_NOT 146  // not
#define STR_RES_GAT 147  // gat
#define STR_RES_LFO_1 148  // lfo 1
#define STR_RES_LFO_2 149  // lfo 2
#define STR_RES_STPSEQ 150  // stpseq
#define STR_RES_STPSQ1 151  // stpsq1
#define STR_RES_STPSQ2 152  // stpsq2
#define STR_RES___ARP 153  //   arp
#define STR_RES_MWHEEL 154  // mwheel
#define STR_RES_AFTTCH 155  // afttch
#define STR_RES_BENDER 156  // bender
#define STR_RES_OFFSET 157  // offset
#define STR_RES_CV_1 158  // cv 1
#define STR_RES_CV_2 159  // cv 2
#define STR_RES_CV_3 160  // cv 3
#define STR_RES_CV_4 161  // cv 4
#define STR_RES___NOISE 162  //   noise
#define STR_RES_ENV_1 163  // env 1
#define STR_RES_ENV_2 164  // env 2
#define STR_RES_VELO 165  // velo
#define STR_RES_RANDOM 166  // random
#define STR_RES_NOTE 167  // note
#define STR_RES_GATE 168  // gate
#define STR_RES__OFF 169  //  off
#define STR_RES_THRU 170  // thru
#define STR_RES_CTRL 171  // ctrl
#define STR_RES___SEQ 172  //   seq
#define STR_RES_POLY 173  // poly
#define STR_RES_MODE 174  // mode
#define STR_RES_STP 175  // stp
#define STR_RES_ARP 176  // arp
#define STR_RES_ARPSLT 177  // arp+lt
#define STR_RES__SEQ 178  //  seq
#define STR_RES_SEQSLT 179  // seq+lt
#define STR_RES_IMPRO 180  // impro
#define STR_RES_FREE 181  // free
#define STR_RES_SLAVE 182  // slave
#define STR_RES_MASTER 183  // master
#define STR_RES_FLOW 184  // flow
#define STR_RES_T 185  // ~
#define STR_RES___ 186  //  
#define STR_RES_T_ 187  // ~-
#define STR_RES__T_ 188  //  ~
#define STR_RES_KRAMA 189  // krama
#define STR_RES_JATA 190  // jata
#define STR_RES_SIKHA 191  // sikha
#define STR_RES_GHANA 192  // ghana
#define STR_RES_2KRAMA 193  // 2krama
#define STR_RES_2JATA 194  // 2jata
#define STR_RES_2SIKHA 195  // 2sikha
#define STR_RES_2GHANA 196  // 2ghana
#define STR_RES_4KRAMA 197  // 4krama
#define STR_RES_4JATA 198  // 4jata
#define STR_RES_4SIKHA 199  // 4sikha
#define STR_RES_4GHANA 200  // 4ghana
#define STR_RES_270 201  // 270
#define STR_RES_300 202  // 300
#define STR_RES_330 203  // 330
#define STR_RES_360 204  // 360
#define STR_RES_420 205  // 420
#define STR_RES_480 206  // 480
#define STR_RES_600 207  // 600
#define STR_RES_720 208  // 720
#define STR_RES_960 209  // 960
#define STR_RES_GROOVE 210  // groove
#define STR_RES_SWING 211  // swing
#define STR_RES_SHUFFLE 212  // shuffle
#define STR_RES_PUSH 213  // push
#define STR_RES_LAG 214  // lag
#define STR_RES_HUMAN 215  // human
#define STR_RES_TOUCH_A_KNOB_TO 216  // touch a knob to
#define STR_RES_ASSIGN_PARAMETER 217  // assign parameter
#define STR_RES_PATCHES 218  // patches
#define STR_RES_SEQUENCES 219  // sequences
#define STR_RES_SYSTEM_SETTINGS 220  // system settings
#define STR_RES_STEP_SEQUENCER 221  // step sequencer
#define STR_RES_LOAD 222  // load
#define STR_RES_ 223  // ----
#define STR_RES_SAVE 224  // save
#define STR_RES_V 225  // v
#define STR_RES_MUTABLE____V1_00 226  // mutable    v1.00
#define STR_RES_INSTRUMENTS_671 227  // instruments -1
#define STR_RES_EXTERN 228  // extern
#define STR_RES_EQUAL 229  // equal
#define STR_RES_JUST 230  // just
#define STR_RES_PYTHAG 231  // pythag
#define STR_RES_1_4_EB 232  // 1/4 eb
#define STR_RES_1_4_E 233  // 1/4 e
#define STR_RES_1_4_EA 234  // 1/4 ea
#define STR_RES_BHAIRA 235  // bhaira
#define STR_RES_GUNAKR 236  // gunakr
#define STR_RES_MARWA 237  // marwa
#define STR_RES_SHREE 238  // shree
#define STR_RES_PURVI 239  // purvi
#define STR_RES_BILAWA 240  // bilawa
#define STR_RES_YAMAN 241  // yaman
#define STR_RES_KAFI 242  // kafi
#define STR_RES_BHIMPA 243  // bhimpa
#define STR_RES_DARBAR 244  // darbar
#define STR_RES_BAGESH 245  // bagesh
#define STR_RES_RAGESH 246  // ragesh
#define STR_RES_KHAMAJ 247  // khamaj
#define STR_RES_MIMAL 248  // mi'mal
#define STR_RES_PARAME 249  // parame
#define STR_RES_RANGES 250  // ranges
#define STR_RES_GANGES 251  // ganges
#define STR_RES_KAMESH 252  // kamesh
#define STR_RES_PALAS_ 253  // palas 
#define STR_RES_NATBHA 254  // natbha
#define STR_RES_M_KAUN 255  // m.kaun
#define STR_RES_BAIRAG 256  // bairag
#define STR_RES_B_TODI 257  // b.todi
#define STR_RES_CHANDR 258  // chandr
#define STR_RES_KAUSHI 259  // kaushi
#define STR_RES_JOGESH 260  // jogesh
#define STR_RES_RASIA 261  // rasia
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
#define CHR_RES_SPECIAL_CHARACTERS 0
#define CHR_RES_SPECIAL_CHARACTERS_SIZE 64
typedef hardware_resources::ResourcesManager<
    ResourceId,
    hardware_resources::ResourcesTables<
        string_table,
        lookup_table_table> > ResourcesManager; 

}  // namespace hardware_shruthi

#endif  // HARDWARE_SHRUTHI_RESOURCES_H_
