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
#define STR_RES_CUTOFF 72  // cutoff
#define STR_RES__VCA 73  //  vca
#define STR_RES_PWM1 74  // pwm1
#define STR_RES_PWM2 75  // pwm2
#define STR_RES_OSC1 76  // osc1
#define STR_RES_OSC2 77  // osc2
#define STR_RES_OSC1S2 78  // osc1+2
#define STR_RES_FINE 79  // fine
#define STR_RES__MIX 80  //  mix
#define STR_RES_NOISE 81  // noise
#define STR_RES_SUBOSC 82  // subosc
#define STR_RES_RESO 83  // reso
#define STR_RES__CV_1 84  //  cv 1
#define STR_RES__CV_2 85  //  cv 2
#define STR_RES_2_BITS 86  // 2 bits
#define STR_RES_LF1 87  // lf1
#define STR_RES_LF2 88  // lf2
#define STR_RES_SEQ 89  // seq
#define STR_RES_SQ1 90  // sq1
#define STR_RES_SQ2 91  // sq2
#define STR_RES__ARP 92  //  arp
#define STR_RES_WHL 93  // whl
#define STR_RES_AFT 94  // aft
#define STR_RES_BND 95  // bnd
#define STR_RES_OFS 96  // ofs
#define STR_RES_CV1 97  // cv1
#define STR_RES_CV2 98  // cv2
#define STR_RES_CV3 99  // cv3
#define STR_RES_CV4 100  // cv4
#define STR_RES_CCA 101  // ccA
#define STR_RES_CCB 102  // ccB
#define STR_RES_CCC 103  // ccC
#define STR_RES_CCD 104  // ccD
#define STR_RES__NOI 105  //  noi
#define STR_RES_EN1 106  // en1
#define STR_RES_EN2 107  // en2
#define STR_RES_VEL 108  // vel
#define STR_RES_RND 109  // rnd
#define STR_RES_NOT 110  // not
#define STR_RES_GAT 111  // gat
#define STR_RES_AUD 112  // aud
#define STR_RES_LFO_1 113  // lfo 1
#define STR_RES_LFO_2 114  // lfo 2
#define STR_RES_STPSEQ 115  // stpseq
#define STR_RES_STPSQ1 116  // stpsq1
#define STR_RES_STPSQ2 117  // stpsq2
#define STR_RES___ARP 118  //   arp
#define STR_RES_MWHEEL 119  // mwheel
#define STR_RES_AFTTCH 120  // afttch
#define STR_RES_BENDER 121  // bender
#define STR_RES_OFFSET 122  // offset
#define STR_RES_CV_1 123  // cv 1
#define STR_RES_CV_2 124  // cv 2
#define STR_RES_CV_3 125  // cv 3
#define STR_RES_CV_4 126  // cv 4
#define STR_RES_CC_A 127  // cc A
#define STR_RES_CC_B 128  // cc B
#define STR_RES_CC_C 129  // cc C
#define STR_RES_CC_D 130  // cc D
#define STR_RES___NOISE 131  //   noise
#define STR_RES_ENV_1 132  // env 1
#define STR_RES_ENV_2 133  // env 2
#define STR_RES_VELO 134  // velo
#define STR_RES_RANDOM 135  // random
#define STR_RES_NOTE 136  // note
#define STR_RES_GATE 137  // gate
#define STR_RES_AUDIO 138  // audio
#define STR_RES_TOUCH_A_KNOB_TO 139  // touch a knob to
#define STR_RES_ASSIGN_PARAMETER 140  // assign parameter
#define STR_RES_PATCH 141  // patch
#define STR_RES_SEQUENCE 142  // sequence
#define STR_RES_SAVE_MIDI_KBD 143  // save midi/kbd
#define STR_RES_SETTINGS_ 144  // settings?
#define STR_RES_START_FULL_MIDI 145  // start full MIDI
#define STR_RES_BACKUP_ 146  // backup?
#define STR_RES_LOAD 147  // load
#define STR_RES_SAVE 148  // save
#define STR_RES_COMPARE 149  // compare
#define STR_RES_ 150  // ----
#define STR_RES_V 151  // v
#define STR_RES_MUTABLE____V1_00 152  // mutable    v1.00
#define STR_RES_INSTRUMENTS_671 153  // instruments -1
#define STR_RES_EXTERN 154  // extern
#define STR_RES_SUM 155  // sum
#define STR_RES_SYNC 156  // sync
#define STR_RES_RING 157  // ring
#define STR_RES_XOR 158  // xor
#define STR_RES_FUZZ 159  // fuzz
#define STR_RES_STP 160  // stp
#define STR_RES_ARP 161  // arp
#define STR_RES_ARPSLT 162  // arp+lt
#define STR_RES__SEQ 163  //  seq
#define STR_RES_SEQSLT 164  // seq+lt
#define STR_RES_IMPRO 165  // impro
#define STR_RES_FREE 166  // free
#define STR_RES_SLAVE 167  // slave
#define STR_RES_MASTER 168  // master
#define STR_RES_T 169  // ~
#define STR_RES___ 170  //  
#define STR_RES_T_ 171  // ~-
#define STR_RES__T_ 172  //  ~
#define STR_RES_KRAMA 173  // krama
#define STR_RES_JATA 174  // jata
#define STR_RES_SIKHA 175  // sikha
#define STR_RES_GHANA 176  // ghana
#define STR_RES_2KRAMA 177  // 2krama
#define STR_RES_2JATA 178  // 2jata
#define STR_RES_2SIKHA 179  // 2sikha
#define STR_RES_2GHANA 180  // 2ghana
#define STR_RES_4KRAMA 181  // 4krama
#define STR_RES_4JATA 182  // 4jata
#define STR_RES_4SIKHA 183  // 4sikha
#define STR_RES_4GHANA 184  // 4ghana
#define STR_RES_SWING 185  // swing
#define STR_RES_SHUFFLE 186  // shuffle
#define STR_RES_PUSH 187  // push
#define STR_RES_LAG 188  // lag
#define STR_RES_HUMAN 189  // human
#define STR_RES__OFF 190  //  off
#define STR_RES_THRU 191  // thru
#define STR_RES___SEQ 192  //   seq
#define STR_RES_FULL 193  // full
#define STR_RES_1__ 194  // 1>|
#define STR_RES_2_1 195  // 2>1
#define STR_RES_3_2 196  // 3>2
#define STR_RES_4_3 197  // 4>3
#define STR_RES_5_4 198  // 5>4
#define STR_RES_6_5 199  // 6>5
#define STR_RES_7_6 200  // 7>6
#define STR_RES_8_7 201  // 8>7
#define STR_RES_TRI 202  // tri
#define STR_RES_SQR 203  // sqr
#define STR_RES_S_H 204  // s&h
#define STR_RES_RAMP 205  // ramp
#define STR_RES_STEP 206  // step
#define STR_RES_3 207  // 
#define STR_RES_4 208  // 
#define STR_RES_34 209  // 
#define STR_RES__ 210  // ?
#define STR_RES_OFF 211  // off
#define STR_RES_ON 212  // on
#define STR_RES_NONE 213  // none
#define STR_RES_SAW 214  // saw
#define STR_RES_SQUARE 215  // square
#define STR_RES_TRIANG 216  // triang
#define STR_RES_ZSAW 217  // zsaw
#define STR_RES_ZRESO 218  // zreso
#define STR_RES_ZTRI 219  // ztri
#define STR_RES_ZPULSE 220  // zpulse
#define STR_RES_ZSYNC 221  // zsync
#define STR_RES_PAD 222  // pad
#define STR_RES_FM 223  // fm
#define STR_RES_WAVES 224  // waves
#define STR_RES_TAMPUR 225  // tampur
#define STR_RES_DIGITL 226  // digitl
#define STR_RES_METALL 227  // metall
#define STR_RES_BOWED 228  // bowed
#define STR_RES_SLAP 229  // slap
#define STR_RES_ORGAN 230  // organ
#define STR_RES_MALE 231  // male
#define STR_RES_8BITS 232  // 8bits
#define STR_RES_CRUSH 233  // crush
#define STR_RES_PWM 234  // pwm
#define STR_RES__NOISE 235  //  noise
#define STR_RES_VOWEL 236  // vowel
#define STR_RES__SQUARE 237  //  square
#define STR_RES__TRIANG 238  //  triang
#define STR_RES_CLICK 239  // click
#define STR_RES_GLITCH 240  // glitch
#define STR_RES_BLOW 241  // blow
#define STR_RES_METAL 242  // metal
#define STR_RES_POP 243  // pop
#define STR_RES_EQUAL 244  // equal
#define STR_RES_JUST 245  // just
#define STR_RES_PYTHAG 246  // pythag
#define STR_RES_1_4_EB 247  // 1/4 eb
#define STR_RES_1_4_E 248  // 1/4 e
#define STR_RES_1_4_EA 249  // 1/4 ea
#define STR_RES_BHAIRA 250  // bhaira
#define STR_RES_GUNAKR 251  // gunakr
#define STR_RES_MARWA 252  // marwa
#define STR_RES_SHREE 253  // shree
#define STR_RES_PURVI 254  // purvi
#define STR_RES_BILAWA 255  // bilawa
#define STR_RES_YAMAN 256  // yaman
#define STR_RES_KAFI 257  // kafi
#define STR_RES_BHIMPA 258  // bhimpa
#define STR_RES_DARBAR 259  // darbar
#define STR_RES_BAGESH 260  // bagesh
#define STR_RES_RAGESH 261  // ragesh
#define STR_RES_KHAMAJ 262  // khamaj
#define STR_RES_MIMAL 263  // mi'mal
#define STR_RES_PARAME 264  // parame
#define STR_RES_RANGES 265  // ranges
#define STR_RES_GANGES 266  // ganges
#define STR_RES_KAMESH 267  // kamesh
#define STR_RES_PALAS_ 268  // palas 
#define STR_RES_NATBHA 269  // natbha
#define STR_RES_M_KAUN 270  // m.kaun
#define STR_RES_BAIRAG 271  // bairag
#define STR_RES_B_TODI 272  // b.todi
#define STR_RES_CHANDR 273  // chandr
#define STR_RES_KAUSHI 274  // kaushi
#define STR_RES_JOGESH 275  // jogesh
#define STR_RES_RASIA 276  // rasia
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
