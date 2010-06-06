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
#define STR_RES_SHAPE 0  // shape
#define STR_RES_PARAMETER 1  // parameter
#define STR_RES_PRM 2  // prm
#define STR_RES_RANGE 3  // range
#define STR_RES_RNG 4  // rng
#define STR_RES_OP_ 5  // op.
#define STR_RES_OPERATOR 6  // operator
#define STR_RES_DETUNE 7  // detune
#define STR_RES_OSC_BAL 8  // osc bal
#define STR_RES_SUB_OSC_ 9  // sub osc.
#define STR_RES_RESONANCE 10  // resonance
#define STR_RES_ENV1TVCF 11  // env1~vcf
#define STR_RES_LFO2TVCF 12  // lfo2~vcf
#define STR_RES_ATTACK 13  // attack
#define STR_RES_ATK 14  // atk
#define STR_RES_DECAY 15  // decay
#define STR_RES_SUSTAIN 16  // sustain
#define STR_RES_RELEASE 17  // release
#define STR_RES_RATE 18  // rate
#define STR_RES_MODULATION 19  // modulation
#define STR_RES_MOD_ 20  // mod.
#define STR_RES_SOURCE 21  // source
#define STR_RES_SRC 22  // src
#define STR_RES_DEST_ 23  // dest.
#define STR_RES_DST 24  // dst
#define STR_RES_AMOUNT 25  // amount
#define STR_RES_AMT 26  // amt
#define STR_RES_MODE 27  // mode
#define STR_RES_TEMPO 28  // tempo
#define STR_RES_BPM 29  // bpm
#define STR_RES_GROOVE 30  // groove
#define STR_RES_DIRECTION 31  // direction
#define STR_RES_PATTERN 32  // pattern
#define STR_RES_FLOW 33  // flow
#define STR_RES_START 34  // start
#define STR_RES_LENGTH 35  // length
#define STR_RES_OCTAVE 36  // octave
#define STR_RES_RAGA 37  // raga
#define STR_RES_PORTA 38  // porta
#define STR_RES_PRT 39  // prt
#define STR_RES_LEGATO 40  // legato
#define STR_RES_TUNING 41  // tuning
#define STR_RES_MIDI_CHAN 42  // midi chan
#define STR_RES_CHN 43  // chn
#define STR_RES_MIDI_OUT 44  // midi out
#define STR_RES_OSCILLATOR_1 45  // oscillator 1
#define STR_RES_OSCILLATOR_2 46  // oscillator 2
#define STR_RES_MIXER 47  // mixer
#define STR_RES_FILTER 48  // filter
#define STR_RES_ENVELOPE_1 49  // envelope 1
#define STR_RES_ENVELOPE_2 50  // envelope 2
#define STR_RES_SEQUENCER 51  // sequencer
#define STR_RES_ARPEGGIO 52  // arpeggio
#define STR_RES_STEP_SEQUENCER 53  // step sequencer
#define STR_RES_KEYBOARD 54  // keyboard
#define STR_RES_MIDI 55  // midi
#define STR_RES_PERFORMANCE 56  // performance
#define STR_RES_CUT 57  // cut
#define STR_RES_VCA 58  // vca
#define STR_RES_PW1 59  // pw1
#define STR_RES_PW2 60  // pw2
#define STR_RES_51 61  // 1
#define STR_RES_52 62  // 2
#define STR_RES_5 63  // 
#define STR_RES_5F 64  // f
#define STR_RES_MIX 65  // mix
#define STR_RES_NOI 66  // noi
#define STR_RES_SUB 67  // sub
#define STR_RES_RES 68  // res
#define STR_RES__CV1 69  //  cv1
#define STR_RES__CV2 70  //  cv2
#define STR_RES_2BT 71  // 2bt
#define STR_RES__LF1 72  //  lf1
#define STR_RES__LF2 73  //  lf2
#define STR_RES_CUTOFF 74  // cutoff
#define STR_RES__VCA 75  //  vca
#define STR_RES_PWM1 76  // pwm1
#define STR_RES_PWM2 77  // pwm2
#define STR_RES_OSC1 78  // osc1
#define STR_RES_OSC2 79  // osc2
#define STR_RES_OSC1S2 80  // osc1+2
#define STR_RES_FINE 81  // fine
#define STR_RES__MIX 82  //  mix
#define STR_RES_NOISE 83  // noise
#define STR_RES_SUBOSC 84  // subosc
#define STR_RES_RESO 85  // reso
#define STR_RES__CV_1 86  //  cv 1
#define STR_RES__CV_2 87  //  cv 2
#define STR_RES_2_BITS 88  // 2 bits
#define STR_RES__LFO_1 89  //  lfo 1
#define STR_RES__LFO_2 90  //  lfo 2
#define STR_RES_LF1 91  // lf1
#define STR_RES_LF2 92  // lf2
#define STR_RES_SEQ 93  // seq
#define STR_RES_SQ1 94  // sq1
#define STR_RES_SQ2 95  // sq2
#define STR_RES__ARP 96  //  arp
#define STR_RES_WHL 97  // whl
#define STR_RES_AFT 98  // aft
#define STR_RES_BND 99  // bnd
#define STR_RES_OFS 100  // ofs
#define STR_RES_CV1 101  // cv1
#define STR_RES_CV2 102  // cv2
#define STR_RES_CV3 103  // cv3
#define STR_RES_CV4 104  // cv4
#define STR_RES_CCA 105  // ccA
#define STR_RES_CCB 106  // ccB
#define STR_RES_CCC 107  // ccC
#define STR_RES_CCD 108  // ccD
#define STR_RES__NOI 109  //  noi
#define STR_RES_EN1 110  // en1
#define STR_RES_EN2 111  // en2
#define STR_RES_VEL 112  // vel
#define STR_RES_RND 113  // rnd
#define STR_RES_NOT 114  // not
#define STR_RES_GAT 115  // gat
#define STR_RES_AUD 116  // aud
#define STR_RES_LFO_1 117  // lfo 1
#define STR_RES_LFO_2 118  // lfo 2
#define STR_RES_STPSEQ 119  // stpseq
#define STR_RES_STPSQ1 120  // stpsq1
#define STR_RES_STPSQ2 121  // stpsq2
#define STR_RES___ARP 122  //   arp
#define STR_RES_MWHEEL 123  // mwheel
#define STR_RES_AFTTCH 124  // afttch
#define STR_RES_BENDER 125  // bender
#define STR_RES_OFFSET 126  // offset
#define STR_RES_CV_1 127  // cv 1
#define STR_RES_CV_2 128  // cv 2
#define STR_RES_CV_3 129  // cv 3
#define STR_RES_CV_4 130  // cv 4
#define STR_RES_CC_A 131  // cc A
#define STR_RES_CC_B 132  // cc B
#define STR_RES_CC_C 133  // cc C
#define STR_RES_CC_D 134  // cc D
#define STR_RES___NOISE 135  //   noise
#define STR_RES_ENV_1 136  // env 1
#define STR_RES_ENV_2 137  // env 2
#define STR_RES_VELO 138  // velo
#define STR_RES_RANDOM 139  // random
#define STR_RES_NOTE 140  // note
#define STR_RES_GATE 141  // gate
#define STR_RES_AUDIO 142  // audio
#define STR_RES_TOUCH_A_KNOB_TO 143  // touch a knob to
#define STR_RES_ASSIGN_PARAMETER 144  // assign parameter
#define STR_RES_PATCH 145  // patch
#define STR_RES_SEQUENCE 146  // sequence
#define STR_RES_SAVE_MIDI_KBD 147  // save midi/kbd
#define STR_RES_SETTINGS_ 148  // settings?
#define STR_RES_START_FULL_MIDI 149  // start full MIDI
#define STR_RES_BACKUP_ 150  // backup?
#define STR_RES_LOAD 151  // load
#define STR_RES_SAVE 152  // save
#define STR_RES_COMPARE 153  // compare
#define STR_RES_ 154  // ----
#define STR_RES_V 155  // v
#define STR_RES_MUTABLE____V1_00 156  // mutable    v1.00
#define STR_RES_INSTRUMENTS_671 157  // instruments -1
#define STR_RES_EXTERN 158  // extern
#define STR_RES_SUM 159  // sum
#define STR_RES_SYNC 160  // sync
#define STR_RES_RING 161  // ring
#define STR_RES_XOR 162  // xor
#define STR_RES_FUZZ 163  // fuzz
#define STR_RES_STP 164  // stp
#define STR_RES_ARP 165  // arp
#define STR_RES_ARPSLT 166  // arp+lt
#define STR_RES__SEQ 167  //  seq
#define STR_RES_SEQSLT 168  // seq+lt
#define STR_RES_IMPRO 169  // impro
#define STR_RES_FREE 170  // free
#define STR_RES_SLAVE 171  // slave
#define STR_RES_MASTER 172  // master
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
#define STR_RES_SWING 189  // swing
#define STR_RES_SHUFFLE 190  // shuffle
#define STR_RES_PUSH 191  // push
#define STR_RES_LAG 192  // lag
#define STR_RES_HUMAN 193  // human
#define STR_RES__OFF 194  //  off
#define STR_RES_THRU 195  // thru
#define STR_RES___SEQ 196  //   seq
#define STR_RES_FULL 197  // full
#define STR_RES_1__ 198  // 1>|
#define STR_RES_2_1 199  // 2>1
#define STR_RES_3_2 200  // 3>2
#define STR_RES_4_3 201  // 4>3
#define STR_RES_5_4 202  // 5>4
#define STR_RES_6_5 203  // 6>5
#define STR_RES_7_6 204  // 7>6
#define STR_RES_8_7 205  // 8>7
#define STR_RES_TRI 206  // tri
#define STR_RES_SQR 207  // sqr
#define STR_RES_S_H 208  // s&h
#define STR_RES_RAMP 209  // ramp
#define STR_RES_STEP 210  // step
#define STR_RES_3 211  // 
#define STR_RES_4 212  // 
#define STR_RES_34 213  // 
#define STR_RES__ 214  // ?
#define STR_RES_OFF 215  // off
#define STR_RES_ON 216  // on
#define STR_RES_NONE 217  // none
#define STR_RES_SAW 218  // saw
#define STR_RES_SQUARE 219  // square
#define STR_RES_TRIANG 220  // triang
#define STR_RES_ZSAW 221  // zsaw
#define STR_RES_ZRESO 222  // zreso
#define STR_RES_ZTRI 223  // ztri
#define STR_RES_ZPULSE 224  // zpulse
#define STR_RES_ZSYNC 225  // zsync
#define STR_RES_PAD 226  // pad
#define STR_RES_FM 227  // fm
#define STR_RES_WAVES 228  // waves
#define STR_RES_TAMPUR 229  // tampur
#define STR_RES_DIGITL 230  // digitl
#define STR_RES_METALL 231  // metall
#define STR_RES_BOWED 232  // bowed
#define STR_RES_SLAP 233  // slap
#define STR_RES_ORGAN 234  // organ
#define STR_RES_MALE 235  // male
#define STR_RES_8BITS 236  // 8bits
#define STR_RES_CRUSH 237  // crush
#define STR_RES_PWM 238  // pwm
#define STR_RES__NOISE 239  //  noise
#define STR_RES_VOWEL 240  // vowel
#define STR_RES__SQUARE 241  //  square
#define STR_RES__TRIANG 242  //  triang
#define STR_RES_CLICK 243  // click
#define STR_RES_GLITCH 244  // glitch
#define STR_RES_BLOW 245  // blow
#define STR_RES_METAL 246  // metal
#define STR_RES_POP 247  // pop
#define STR_RES_EQUAL 248  // equal
#define STR_RES_JUST 249  // just
#define STR_RES_PYTHAG 250  // pythag
#define STR_RES_1_4_EB 251  // 1/4 eb
#define STR_RES_1_4_E 252  // 1/4 e
#define STR_RES_1_4_EA 253  // 1/4 ea
#define STR_RES_BHAIRA 254  // bhaira
#define STR_RES_GUNAKR 255  // gunakr
#define STR_RES_MARWA 256  // marwa
#define STR_RES_SHREE 257  // shree
#define STR_RES_PURVI 258  // purvi
#define STR_RES_BILAWA 259  // bilawa
#define STR_RES_YAMAN 260  // yaman
#define STR_RES_KAFI 261  // kafi
#define STR_RES_BHIMPA 262  // bhimpa
#define STR_RES_DARBAR 263  // darbar
#define STR_RES_BAGESH 264  // bagesh
#define STR_RES_RAGESH 265  // ragesh
#define STR_RES_KHAMAJ 266  // khamaj
#define STR_RES_MIMAL 267  // mi'mal
#define STR_RES_PARAME 268  // parame
#define STR_RES_RANGES 269  // ranges
#define STR_RES_GANGES 270  // ganges
#define STR_RES_KAMESH 271  // kamesh
#define STR_RES_PALAS_ 272  // palas 
#define STR_RES_NATBHA 273  // natbha
#define STR_RES_M_KAUN 274  // m.kaun
#define STR_RES_BAIRAG 275  // bairag
#define STR_RES_B_TODI 276  // b.todi
#define STR_RES_CHANDR 277  // chandr
#define STR_RES_KAUSHI 278  // kaushi
#define STR_RES_JOGESH 279  // jogesh
#define STR_RES_RASIA 280  // rasia
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
