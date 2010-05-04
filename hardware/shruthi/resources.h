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
#define STR_RES_1S2 41  // 1+2
#define STR_RES_1_2 42  // 1>2
#define STR_RES_1P2 43  // 1*2
#define STR_RES_1X2 44  // 1^2
#define STR_RES_CUT 45  // cut
#define STR_RES_VCA 46  // vca
#define STR_RES_PW1 47  // pw1
#define STR_RES_PW2 48  // pw2
#define STR_RES_51 49  // 1
#define STR_RES_52 50  // 2
#define STR_RES_5 51  // 
#define STR_RES_MIX 52  // mix
#define STR_RES_NOI 53  // noi
#define STR_RES_SUB 54  // sub
#define STR_RES_RES 55  // res
#define STR_RES__CV1 56  //  cv1
#define STR_RES__CV2 57  //  cv2
#define STR_RES_2BT 58  // 2bt
#define STR_RES_CUTOFF 59  // cutoff
#define STR_RES__VCA 60  //  vca
#define STR_RES_PWM1 61  // pwm1
#define STR_RES_PWM2 62  // pwm2
#define STR_RES_OSC1 63  // osc1
#define STR_RES_OSC2 64  // osc2
#define STR_RES_OSC1S2 65  // osc1+2
#define STR_RES__MIX 66  //  mix
#define STR_RES__NOISE 67  //  noise
#define STR_RES_SUBOSC 68  // subosc
#define STR_RES_RESO 69  // reso
#define STR_RES__CV_1 70  //  cv 1
#define STR_RES__CV_2 71  //  cv 2
#define STR_RES_2_BITS 72  // 2 bits
#define STR_RES_ATK 73  // atk
#define STR_RES_WV1 74  // wv1
#define STR_RES_RT1 75  // rt1
#define STR_RES_WV2 76  // wv2
#define STR_RES_RT2 77  // rt2
#define STR_RES_SRC 78  // src
#define STR_RES_DST 79  // dst
#define STR_RES_AMT 80  // amt
#define STR_RES_CHN 81  // chn
#define STR_RES_BPM 82  // bpm
#define STR_RES_SWG 83  // swg
#define STR_RES_SHAPE 84  // shape
#define STR_RES_ENV1TVCF 85  // env1~vcf
#define STR_RES_LFO2TVCF 86  // lfo2~vcf
#define STR_RES_RESONANCE 87  // resonance
#define STR_RES_ENVELOPE_1 88  // envelope 1
#define STR_RES_ENVELOPE_2 89  // envelope 2
#define STR_RES_SEQUENCER 90  // sequencer
#define STR_RES_ATTACK 91  // attack
#define STR_RES_DECAY 92  // decay
#define STR_RES_SUSTAIN 93  // sustain
#define STR_RES_RELEASE 94  // release
#define STR_RES_RATE 95  // rate
#define STR_RES_MOD_ 96  // mod.
#define STR_RES_SOURCE 97  // source
#define STR_RES_DEST_ 98  // dest.
#define STR_RES_AMOUNT 99  // amount
#define STR_RES_OCTAVE 100  // octave
#define STR_RES_RAGA 101  // raga
#define STR_RES_MIDI_CHAN 102  // midi chan
#define STR_RES_TEMPO 103  // tempo
#define STR_RES_MIXER 104  // mixer
#define STR_RES_FILTER 105  // filter
#define STR_RES_MODULATION 106  // modulation
#define STR_RES_KEYBOARD 107  // keyboard
#define STR_RES_MIDI 108  // midi
#define STR_RES_OFF 109  // off
#define STR_RES_ON 110  // on
#define STR_RES_TRI 111  // tri
#define STR_RES_SQR 112  // sqr
#define STR_RES_S_H 113  // s&h
#define STR_RES_RAMP 114  // ramp
#define STR_RES_STEP 115  // step
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
#define STR_RES_ARPSLT 170  // arp+lt
#define STR_RES__SEQ 171  //  seq
#define STR_RES_SEQSLT 172  // seq+lt
#define STR_RES_IMPRO 173  // impro
#define STR_RES_FREE 174  // free
#define STR_RES_SLAVE 175  // slave
#define STR_RES_MASTER 176  // master
#define STR_RES_FLOW 177  // flow
#define STR_RES_T 178  // ~
#define STR_RES___ 179  //  
#define STR_RES_T_ 180  // ~-
#define STR_RES__T_ 181  //  ~
#define STR_RES_KRAMA 182  // krama
#define STR_RES_JATA 183  // jata
#define STR_RES_SIKHA 184  // sikha
#define STR_RES_GHANA 185  // ghana
#define STR_RES_2KRAMA 186  // 2krama
#define STR_RES_2JATA 187  // 2jata
#define STR_RES_2SIKHA 188  // 2sikha
#define STR_RES_2GHANA 189  // 2ghana
#define STR_RES_4KRAMA 190  // 4krama
#define STR_RES_4JATA 191  // 4jata
#define STR_RES_4SIKHA 192  // 4sikha
#define STR_RES_4GHANA 193  // 4ghana
#define STR_RES_270 194  // 270
#define STR_RES_300 195  // 300
#define STR_RES_330 196  // 330
#define STR_RES_360 197  // 360
#define STR_RES_420 198  // 420
#define STR_RES_480 199  // 480
#define STR_RES_600 200  // 600
#define STR_RES_720 201  // 720
#define STR_RES_960 202  // 960
#define STR_RES_GROOVE 203  // groove
#define STR_RES_SWING 204  // swing
#define STR_RES_SHUFFLE 205  // shuffle
#define STR_RES_PUSH 206  // push
#define STR_RES_LAG 207  // lag
#define STR_RES_HUMAN 208  // human
#define STR_RES_TOUCH_A_KNOB_TO 209  // touch a knob to
#define STR_RES_ASSIGN_PARAMETER 210  // assign parameter
#define STR_RES_PATCHES 211  // patches
#define STR_RES_SEQUENCES 212  // sequences
#define STR_RES_SYSTEM_SETTINGS 213  // system settings
#define STR_RES_STEP_SEQUENCER 214  // step sequencer
#define STR_RES_LOAD 215  // load
#define STR_RES_ 216  // ----
#define STR_RES_SAVE 217  // save
#define STR_RES_V 218  // v
#define STR_RES_MUTABLE____V1_00 219  // mutable    v1.00
#define STR_RES_INSTRUMENTS_671 220  // instruments -1
#define STR_RES_EXTERN 221  // extern
#define STR_RES_EQUAL 222  // equal
#define STR_RES_JUST 223  // just
#define STR_RES_PYTHAG 224  // pythag
#define STR_RES_1_4_EB 225  // 1/4 eb
#define STR_RES_1_4_E 226  // 1/4 e
#define STR_RES_1_4_EA 227  // 1/4 ea
#define STR_RES_BHAIRA 228  // bhaira
#define STR_RES_GUNAKR 229  // gunakr
#define STR_RES_MARWA 230  // marwa
#define STR_RES_SHREE 231  // shree
#define STR_RES_PURVI 232  // purvi
#define STR_RES_BILAWA 233  // bilawa
#define STR_RES_YAMAN 234  // yaman
#define STR_RES_KAFI 235  // kafi
#define STR_RES_BHIMPA 236  // bhimpa
#define STR_RES_DARBAR 237  // darbar
#define STR_RES_BAGESH 238  // bagesh
#define STR_RES_RAGESH 239  // ragesh
#define STR_RES_KHAMAJ 240  // khamaj
#define STR_RES_MIMAL 241  // mi'mal
#define STR_RES_PARAME 242  // parame
#define STR_RES_RANGES 243  // ranges
#define STR_RES_GANGES 244  // ganges
#define STR_RES_KAMESH 245  // kamesh
#define STR_RES_PALAS_ 246  // palas 
#define STR_RES_NATBHA 247  // natbha
#define STR_RES_M_KAUN 248  // m.kaun
#define STR_RES_BAIRAG 249  // bairag
#define STR_RES_B_TODI 250  // b.todi
#define STR_RES_CHANDR 251  // chandr
#define STR_RES_KAUSHI 252  // kaushi
#define STR_RES_JOGESH 253  // jogesh
#define STR_RES_RASIA 254  // rasia
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
