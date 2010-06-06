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
extern const prog_uint8_t wav_res_low_res_wavetable_1[] PROGMEM;
extern const prog_uint8_t wav_res_low_res_wavetable_2[] PROGMEM;
extern const prog_uint8_t wav_res_low_res_wavetable_3[] PROGMEM;
extern const prog_uint8_t wav_res_low_res_wavetable_4[] PROGMEM;
extern const prog_uint8_t wav_res_low_res_wavetable_5[] PROGMEM;
extern const prog_uint8_t wav_res_low_res_wavetable_6[] PROGMEM;
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
#define STR_RES_TAMPUR 32  // tampur
#define STR_RES_DIGITL 33  // digitl
#define STR_RES_METALL 34  // metall
#define STR_RES_BOWED 35  // bowed
#define STR_RES_SLAP 36  // slap
#define STR_RES_ORGAN 37  // organ
#define STR_RES_MALE 38  // male
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
#define STR_RES_5F 63  // f
#define STR_RES_MIX 64  // mix
#define STR_RES_NOI 65  // noi
#define STR_RES_SUB 66  // sub
#define STR_RES_RES 67  // res
#define STR_RES__CV1 68  //  cv1
#define STR_RES__CV2 69  //  cv2
#define STR_RES_2BT 70  // 2bt
#define STR_RES_CUTOFF 71  // cutoff
#define STR_RES__VCA 72  //  vca
#define STR_RES_PWM1 73  // pwm1
#define STR_RES_PWM2 74  // pwm2
#define STR_RES_OSC1 75  // osc1
#define STR_RES_OSC2 76  // osc2
#define STR_RES_OSC1S2 77  // osc1+2
#define STR_RES_FINE 78  // fine
#define STR_RES__MIX 79  //  mix
#define STR_RES__NOISE 80  //  noise
#define STR_RES_SUBOSC 81  // subosc
#define STR_RES_RESO 82  // reso
#define STR_RES__CV_1 83  //  cv 1
#define STR_RES__CV_2 84  //  cv 2
#define STR_RES_2_BITS 85  // 2 bits
#define STR_RES_ATK 86  // atk
#define STR_RES_WV1 87  // wv1
#define STR_RES_RT1 88  // rt1
#define STR_RES_WV2 89  // wv2
#define STR_RES_RT2 90  // rt2
#define STR_RES_SRC 91  // src
#define STR_RES_DST 92  // dst
#define STR_RES_AMT 93  // amt
#define STR_RES_CHN 94  // chn
#define STR_RES_BPM 95  // bpm
#define STR_RES_SWG 96  // swg
#define STR_RES_SHAPE 97  // shape
#define STR_RES_ENV1TVCF 98  // env1~vcf
#define STR_RES_LFO2TVCF 99  // lfo2~vcf
#define STR_RES_RESONANCE 100  // resonance
#define STR_RES_ENVELOPE_1 101  // envelope 1
#define STR_RES_ENVELOPE_2 102  // envelope 2
#define STR_RES_SEQUENCER 103  // sequencer
#define STR_RES_ATTACK 104  // attack
#define STR_RES_DECAY 105  // decay
#define STR_RES_SUSTAIN 106  // sustain
#define STR_RES_RELEASE 107  // release
#define STR_RES_RATE 108  // rate
#define STR_RES_MOD_ 109  // mod.
#define STR_RES_SOURCE 110  // source
#define STR_RES_DEST_ 111  // dest.
#define STR_RES_AMOUNT 112  // amount
#define STR_RES_OCTAVE 113  // octave
#define STR_RES_RAGA 114  // raga
#define STR_RES_MIDI_CHAN 115  // midi chan
#define STR_RES_TEMPO 116  // tempo
#define STR_RES_MIXER 117  // mixer
#define STR_RES_FILTER 118  // filter
#define STR_RES_MODULATION 119  // modulation
#define STR_RES_KEYBOARD 120  // keyboard
#define STR_RES_MIDI 121  // midi
#define STR_RES_OFF 122  // off
#define STR_RES_ON 123  // on
#define STR_RES_TRI 124  // tri
#define STR_RES_SQR 125  // sqr
#define STR_RES_S_H 126  // s&h
#define STR_RES_RAMP 127  // ramp
#define STR_RES_STEP 128  // step
#define STR_RES_3 129  // 
#define STR_RES_4 130  // 
#define STR_RES_34 131  // 
#define STR_RES__ 132  // ?
#define STR_RES_LF1 133  // lf1
#define STR_RES_LF2 134  // lf2
#define STR_RES_SEQ 135  // seq
#define STR_RES_SQ1 136  // sq1
#define STR_RES_SQ2 137  // sq2
#define STR_RES__ARP 138  //  arp
#define STR_RES_WHL 139  // whl
#define STR_RES_AFT 140  // aft
#define STR_RES_BND 141  // bnd
#define STR_RES_OFS 142  // ofs
#define STR_RES_CV1 143  // cv1
#define STR_RES_CV2 144  // cv2
#define STR_RES_CV3 145  // cv3
#define STR_RES_CV4 146  // cv4
#define STR_RES_CCA 147  // ccA
#define STR_RES_CCB 148  // ccB
#define STR_RES_CCC 149  // ccC
#define STR_RES_CCD 150  // ccD
#define STR_RES__NOI 151  //  noi
#define STR_RES_EN1 152  // en1
#define STR_RES_EN2 153  // en2
#define STR_RES_VEL 154  // vel
#define STR_RES_RND 155  // rnd
#define STR_RES_NOT 156  // not
#define STR_RES_GAT 157  // gat
#define STR_RES_AUD 158  // aud
#define STR_RES_LFO_1 159  // lfo 1
#define STR_RES_LFO_2 160  // lfo 2
#define STR_RES_STPSEQ 161  // stpseq
#define STR_RES_STPSQ1 162  // stpsq1
#define STR_RES_STPSQ2 163  // stpsq2
#define STR_RES___ARP 164  //   arp
#define STR_RES_MWHEEL 165  // mwheel
#define STR_RES_AFTTCH 166  // afttch
#define STR_RES_BENDER 167  // bender
#define STR_RES_OFFSET 168  // offset
#define STR_RES_CV_1 169  // cv 1
#define STR_RES_CV_2 170  // cv 2
#define STR_RES_CV_3 171  // cv 3
#define STR_RES_CV_4 172  // cv 4
#define STR_RES_CC_A 173  // cc A
#define STR_RES_CC_B 174  // cc B
#define STR_RES_CC_C 175  // cc C
#define STR_RES_CC_D 176  // cc D
#define STR_RES___NOISE 177  //   noise
#define STR_RES_ENV_1 178  // env 1
#define STR_RES_ENV_2 179  // env 2
#define STR_RES_VELO 180  // velo
#define STR_RES_RANDOM 181  // random
#define STR_RES_NOTE 182  // note
#define STR_RES_GATE 183  // gate
#define STR_RES_AUDIO 184  // audio
#define STR_RES__OFF 185  //  off
#define STR_RES_THRU 186  // thru
#define STR_RES___SEQ 187  //   seq
#define STR_RES_FULL 188  // full
#define STR_RES_1__ 189  // 1>|
#define STR_RES_2_1 190  // 2>1
#define STR_RES_3_2 191  // 3>2
#define STR_RES_4_3 192  // 4>3
#define STR_RES_5_4 193  // 5>4
#define STR_RES_6_5 194  // 6>5
#define STR_RES_7_6 195  // 7>6
#define STR_RES_8_7 196  // 8>7
#define STR_RES_MODE 197  // mode
#define STR_RES_STP 198  // stp
#define STR_RES_ARP 199  // arp
#define STR_RES_ARPSLT 200  // arp+lt
#define STR_RES__SEQ 201  //  seq
#define STR_RES_SEQSLT 202  // seq+lt
#define STR_RES_IMPRO 203  // impro
#define STR_RES_FREE 204  // free
#define STR_RES_SLAVE 205  // slave
#define STR_RES_MASTER 206  // master
#define STR_RES_GROOVE 207  // groove
#define STR_RES_SWING 208  // swing
#define STR_RES_SHUFFLE 209  // shuffle
#define STR_RES_PUSH 210  // push
#define STR_RES_LAG 211  // lag
#define STR_RES_HUMAN 212  // human
#define STR_RES_START 213  // start
#define STR_RES_LENGTH 214  // length
#define STR_RES_FLOW 215  // flow
#define STR_RES_T 216  // ~
#define STR_RES___ 217  //  
#define STR_RES_T_ 218  // ~-
#define STR_RES__T_ 219  //  ~
#define STR_RES_KRAMA 220  // krama
#define STR_RES_JATA 221  // jata
#define STR_RES_SIKHA 222  // sikha
#define STR_RES_GHANA 223  // ghana
#define STR_RES_2KRAMA 224  // 2krama
#define STR_RES_2JATA 225  // 2jata
#define STR_RES_2SIKHA 226  // 2sikha
#define STR_RES_2GHANA 227  // 2ghana
#define STR_RES_4KRAMA 228  // 4krama
#define STR_RES_4JATA 229  // 4jata
#define STR_RES_4SIKHA 230  // 4sikha
#define STR_RES_4GHANA 231  // 4ghana
#define STR_RES_TOUCH_A_KNOB_TO 232  // touch a knob to
#define STR_RES_ASSIGN_PARAMETER 233  // assign parameter
#define STR_RES_PATCH 234  // patch
#define STR_RES_SEQUENCE 235  // sequence
#define STR_RES_SAVE_MIDI_KBD 236  // save midi/kbd
#define STR_RES_SETTINGS_ 237  // settings?
#define STR_RES_START_FULL_MIDI 238  // start full MIDI
#define STR_RES_BACKUP_ 239  // backup?
#define STR_RES_STEP_SEQUENCER 240  // step sequencer
#define STR_RES_LOAD 241  // load
#define STR_RES_SAVE 242  // save
#define STR_RES_COMPARE 243  // compare
#define STR_RES_ 244  // ----
#define STR_RES_V 245  // v
#define STR_RES_MUTABLE____V1_00 246  // mutable    v1.00
#define STR_RES_INSTRUMENTS_671 247  // instruments -1
#define STR_RES_EXTERN 248  // extern
#define STR_RES_EQUAL 249  // equal
#define STR_RES_JUST 250  // just
#define STR_RES_PYTHAG 251  // pythag
#define STR_RES_1_4_EB 252  // 1/4 eb
#define STR_RES_1_4_E 253  // 1/4 e
#define STR_RES_1_4_EA 254  // 1/4 ea
#define STR_RES_BHAIRA 255  // bhaira
#define STR_RES_GUNAKR 256  // gunakr
#define STR_RES_MARWA 257  // marwa
#define STR_RES_SHREE 258  // shree
#define STR_RES_PURVI 259  // purvi
#define STR_RES_BILAWA 260  // bilawa
#define STR_RES_YAMAN 261  // yaman
#define STR_RES_KAFI 262  // kafi
#define STR_RES_BHIMPA 263  // bhimpa
#define STR_RES_DARBAR 264  // darbar
#define STR_RES_BAGESH 265  // bagesh
#define STR_RES_RAGESH 266  // ragesh
#define STR_RES_KHAMAJ 267  // khamaj
#define STR_RES_MIMAL 268  // mi'mal
#define STR_RES_PARAME 269  // parame
#define STR_RES_RANGES 270  // ranges
#define STR_RES_GANGES 271  // ganges
#define STR_RES_KAMESH 272  // kamesh
#define STR_RES_PALAS_ 273  // palas 
#define STR_RES_NATBHA 274  // natbha
#define STR_RES_M_KAUN 275  // m.kaun
#define STR_RES_BAIRAG 276  // bairag
#define STR_RES_B_TODI 277  // b.todi
#define STR_RES_CHANDR 278  // chandr
#define STR_RES_KAUSHI 279  // kaushi
#define STR_RES_JOGESH 280  // jogesh
#define STR_RES_RASIA 281  // rasia
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
#define WAV_RES_LOW_RES_WAVETABLE_1 25
#define WAV_RES_LOW_RES_WAVETABLE_1_SIZE 2064
#define WAV_RES_LOW_RES_WAVETABLE_2 26
#define WAV_RES_LOW_RES_WAVETABLE_2_SIZE 2064
#define WAV_RES_LOW_RES_WAVETABLE_3 27
#define WAV_RES_LOW_RES_WAVETABLE_3_SIZE 2064
#define WAV_RES_LOW_RES_WAVETABLE_4 28
#define WAV_RES_LOW_RES_WAVETABLE_4_SIZE 2064
#define WAV_RES_LOW_RES_WAVETABLE_5 29
#define WAV_RES_LOW_RES_WAVETABLE_5_SIZE 2064
#define WAV_RES_LOW_RES_WAVETABLE_6 30
#define WAV_RES_LOW_RES_WAVETABLE_6_SIZE 2064
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
