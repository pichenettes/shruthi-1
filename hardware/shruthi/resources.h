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
extern const prog_uint16_t lut_res_groove_monkey[] PROGMEM;
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
extern const prog_uint8_t wav_res_low_res_wavetable_1[] PROGMEM;
extern const prog_uint8_t wav_res_low_res_wavetable_2[] PROGMEM;
extern const prog_uint8_t wav_res_low_res_wavetable_3[] PROGMEM;
extern const prog_uint8_t wav_res_low_res_wavetable_4[] PROGMEM;
extern const prog_uint8_t wav_res_low_res_wavetable_5[] PROGMEM;
extern const prog_uint8_t wav_res_low_res_wavetable_6[] PROGMEM;
extern const prog_uint8_t wav_res_low_res_wavetable_7[] PROGMEM;
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
#define STR_RES_WARP 33  // warp
#define STR_RES_WRP 34  // wrp
#define STR_RES_START 35  // start
#define STR_RES_LENGTH 36  // length
#define STR_RES_OCTAVE 37  // octave
#define STR_RES_RAGA 38  // raga
#define STR_RES_PORTA 39  // porta
#define STR_RES_PRT 40  // prt
#define STR_RES_LEGATO 41  // legato
#define STR_RES_TUNING 42  // tuning
#define STR_RES_MIDI_CHAN 43  // midi chan
#define STR_RES_CHN 44  // chn
#define STR_RES_MIDI_OUT 45  // midi out
#define STR_RES_PAUSE 46  // pause
#define STR_RES_SNAP 47  // snap
#define STR_RES_CV_MODE 48  // cv.mode
#define STR_RES_OSCILLATOR_1 49  // oscillator 1
#define STR_RES_OSCILLATOR_2 50  // oscillator 2
#define STR_RES_MIXER 51  // mixer
#define STR_RES_FILTER 52  // filter
#define STR_RES_ENVELOPE_1 53  // envelope 1
#define STR_RES_ENVELOPE_2 54  // envelope 2
#define STR_RES_SEQUENCER 55  // sequencer
#define STR_RES_ARPEGGIO 56  // arpeggio
#define STR_RES_STEP_SEQUENCER 57  // step sequencer
#define STR_RES_KEYBOARD 58  // keyboard
#define STR_RES_MIDI 59  // midi
#define STR_RES_SYSTEM 60  // system
#define STR_RES_PERFORMANCE 61  // performance
#define STR_RES_CUT 62  // cut
#define STR_RES_VCA 63  // vca
#define STR_RES_PW1 64  // pw1
#define STR_RES_PW2 65  // pw2
#define STR_RES_51 66  // 1
#define STR_RES_52 67  // 2
#define STR_RES_5 68  // 
#define STR_RES_5F 69  // f
#define STR_RES_MIX 70  // mix
#define STR_RES_NOI 71  // noi
#define STR_RES_SUB 72  // sub
#define STR_RES_RES 73  // res
#define STR_RES__CV1 74  //  cv1
#define STR_RES__CV2 75  //  cv2
#define STR_RES_2BT 76  // 2bt
#define STR_RES__LF1 77  //  lf1
#define STR_RES__LF2 78  //  lf2
#define STR_RES_CUTOFF 79  // cutoff
#define STR_RES__VCA 80  //  vca
#define STR_RES_PWM1 81  // pwm1
#define STR_RES_PWM2 82  // pwm2
#define STR_RES_OSC1 83  // osc1
#define STR_RES_OSC2 84  // osc2
#define STR_RES_OSC1S2 85  // osc1+2
#define STR_RES_FINE 86  // fine
#define STR_RES__MIX 87  //  mix
#define STR_RES_NOISE 88  // noise
#define STR_RES_SUBOSC 89  // subosc
#define STR_RES_RESO 90  // reso
#define STR_RES__CV_1 91  //  cv 1
#define STR_RES__CV_2 92  //  cv 2
#define STR_RES_2_BITS 93  // 2 bits
#define STR_RES__LFO_1 94  //  lfo 1
#define STR_RES__LFO_2 95  //  lfo 2
#define STR_RES_LF1 96  // lf1
#define STR_RES_LF2 97  // lf2
#define STR_RES_SEQ 98  // seq
#define STR_RES__SQ1 99  //  sq1
#define STR_RES__SQ2 100  //  sq2
#define STR_RES__ARP 101  //  arp
#define STR_RES_WHL 102  // whl
#define STR_RES_AFT 103  // aft
#define STR_RES_BND 104  // bnd
#define STR_RES_OFS 105  // ofs
#define STR_RES_CV1 106  // cv1
#define STR_RES_CV2 107  // cv2
#define STR_RES_CV3 108  // cv3
#define STR_RES_CV4 109  // cv4
#define STR_RES_CCA 110  // ccA
#define STR_RES_CCB 111  // ccB
#define STR_RES_CCC 112  // ccC
#define STR_RES_CCD 113  // ccD
#define STR_RES__NOI 114  //  noi
#define STR_RES_EN1 115  // en1
#define STR_RES_EN2 116  // en2
#define STR_RES_VEL 117  // vel
#define STR_RES_RND 118  // rnd
#define STR_RES_NOT 119  // not
#define STR_RES_GAT 120  // gat
#define STR_RES_AUD 121  // aud
#define STR_RES_LFO_1 122  // lfo 1
#define STR_RES_LFO_2 123  // lfo 2
#define STR_RES_STPSEQ 124  // stpseq
#define STR_RES_STPSQ1 125  // stpsq1
#define STR_RES_STPSQ2 126  // stpsq2
#define STR_RES___ARP 127  //   arp
#define STR_RES_MWHEEL 128  // mwheel
#define STR_RES_AFTTCH 129  // afttch
#define STR_RES_BENDER 130  // bender
#define STR_RES_OFFSET 131  // offset
#define STR_RES_CV_1 132  // cv 1
#define STR_RES_CV_2 133  // cv 2
#define STR_RES_CV_3 134  // cv 3
#define STR_RES_CV_4 135  // cv 4
#define STR_RES_CC_A 136  // cc A
#define STR_RES_CC_B 137  // cc B
#define STR_RES_CC_C 138  // cc C
#define STR_RES_CC_D 139  // cc D
#define STR_RES___NOISE 140  //   noise
#define STR_RES_ENV_1 141  // env 1
#define STR_RES_ENV_2 142  // env 2
#define STR_RES_VELO 143  // velo
#define STR_RES_RANDOM 144  // random
#define STR_RES_NOTE 145  // note
#define STR_RES_GATE 146  // gate
#define STR_RES_AUDIO 147  // audio
#define STR_RES_TOUCH_A_KNOB_TO 148  // touch a knob to
#define STR_RES_ASSIGN_PARAMETER 149  // assign parameter
#define STR_RES_PATCH 150  // patch
#define STR_RES_SEQUENCE 151  // sequence
#define STR_RES_SAVE_MIDI_KBD 152  // save midi/kbd
#define STR_RES_SETTINGS_ 153  // settings?
#define STR_RES_START_FULL_MIDI 154  // start full midi
#define STR_RES_BACKUP_ 155  // backup?
#define STR_RES_BROWSE 156  // browse
#define STR_RES_SAVE 157  // save
#define STR_RES_COMPARE 158  // compare
#define STR_RES_ 159  // ----
#define STR_RES_V 160  // v
#define STR_RES_MUTABLE____V0_92 161  // mutable    v0.92
#define STR_RES_INSTRUMENTS_671 162  // instruments -1
#define STR_RES_EXTERN 163  // extern
#define STR_RES_X2_EXT 164  // x2 ext
#define STR_RES__2_EXT 165  // /2 ext
#define STR_RES__4_EXT 166  // /4 ext
#define STR_RES__8_EXT 167  // /8 ext
#define STR_RES_SUM 168  // sum
#define STR_RES_SYNC 169  // sync
#define STR_RES_RING 170  // ring
#define STR_RES_XOR 171  // xor
#define STR_RES_FUZZ 172  // fuzz
#define STR_RES_STP 173  // stp
#define STR_RES_ARP 174  // arp
#define STR_RES_ARPSLT 175  // arp+lt
#define STR_RES__SEQ 176  //  seq
#define STR_RES_SEQSLT 177  // seq+lt
#define STR_RES_REC 178  // rec
#define STR_RES_IMPRO 179  // impro
#define STR_RES_FREE 180  // free
#define STR_RES_SLAVE 181  // slave
#define STR_RES_MASTER 182  // master
#define STR_RES_T 183  // ~
#define STR_RES___ 184  //  
#define STR_RES_T_ 185  // ~-
#define STR_RES__T_ 186  //  ~
#define STR_RES_GLASS 187  // glass
#define STR_RES_KRAMA 188  // krama
#define STR_RES_JATA 189  // jata
#define STR_RES_SIKHA 190  // sikha
#define STR_RES_GHANA 191  // ghana
#define STR_RES_2GLASS 192  // 2glass
#define STR_RES_2KRAMA 193  // 2krama
#define STR_RES_2JATA 194  // 2jata
#define STR_RES_2SIKHA 195  // 2sikha
#define STR_RES_2GHANA 196  // 2ghana
#define STR_RES_4GLASS 197  // 4glass
#define STR_RES_4KRAMA 198  // 4krama
#define STR_RES_4JATA 199  // 4jata
#define STR_RES_4SIKHA 200  // 4sikha
#define STR_RES_4GHANA 201  // 4ghana
#define STR_RES_SWING 202  // swing
#define STR_RES_SHUFFLE 203  // shuffle
#define STR_RES_PUSH 204  // push
#define STR_RES_LAG 205  // lag
#define STR_RES_HUMAN 206  // human
#define STR_RES_MONKEY 207  // monkey
#define STR_RES__OFF 208  //  off
#define STR_RES_THRU 209  // thru
#define STR_RES___SEQ 210  //   seq
#define STR_RES_SPLIT 211  // split
#define STR_RES_FULL 212  // full
#define STR_RES_1T_ 213  // 1~|
#define STR_RES_2T1 214  // 2~1
#define STR_RES_3T2 215  // 3~2
#define STR_RES_4T3 216  // 4~3
#define STR_RES_5T4 217  // 5~4
#define STR_RES_6T5 218  // 6~5
#define STR_RES_7T6 219  // 7~6
#define STR_RES_8T7 220  // 8~7
#define STR_RES_TRI 221  // tri
#define STR_RES_SQR 222  // sqr
#define STR_RES_S_H 223  // s&h
#define STR_RES_RAMP 224  // ramp
#define STR_RES_STEP 225  // step
#define STR_RES_3 226  // 
#define STR_RES_4 227  // 
#define STR_RES_34 228  // 
#define STR_RES__ 229  // ?
#define STR_RES_OFF 230  // off
#define STR_RES_ON 231  // on
#define STR_RES_SQ1 232  // sq1
#define STR_RES_TR1 233  // tr1
#define STR_RES_PL1 234  // pl1
#define STR_RES_SQ2 235  // sq2
#define STR_RES_TR2 236  // tr2
#define STR_RES_PL2 237  // pl2
#define STR_RES_CLICK 238  // click
#define STR_RES_GLITCH 239  // glitch
#define STR_RES_BLOW 240  // blow
#define STR_RES_METAL 241  // metal
#define STR_RES_POP 242  // pop
#define STR_RES_NONE 243  // none
#define STR_RES_SAW 244  // saw
#define STR_RES_SQUARE 245  // square
#define STR_RES_TRIANG 246  // triang
#define STR_RES_ZSAW 247  // zsaw
#define STR_RES_ZRESO 248  // zreso
#define STR_RES_ZTRI 249  // ztri
#define STR_RES_ZPULSE 250  // zpulse
#define STR_RES_ZSYNC 251  // zsync
#define STR_RES_PAD 252  // pad
#define STR_RES_FM 253  // fm
#define STR_RES_WAVES 254  // waves
#define STR_RES_TAMPUR 255  // tampur
#define STR_RES_DIGITL 256  // digitl
#define STR_RES_METALL 257  // metall
#define STR_RES_BOWED 258  // bowed
#define STR_RES_SLAP 259  // slap
#define STR_RES_ORGAN 260  // organ
#define STR_RES_MALE 261  // male
#define STR_RES_USER 262  // user
#define STR_RES_8BITS 263  // 8bits
#define STR_RES_CRUSH 264  // crush
#define STR_RES_PWM 265  // pwm
#define STR_RES__NOISE 266  //  noise
#define STR_RES_VOWEL 267  // vowel
#define STR_RES_SMR 268  // smr
#define STR_RES_CEM 269  // cem
#define STR_RES_SSM 270  // ssm
#define STR_RES_4CV_IN 271  // 4cv in
#define STR_RES_PRGM 272  // prgm
#define STR_RES_PEDALS 273  // pedals
#define STR_RES_EQUAL 274  // equal
#define STR_RES_JUST 275  // just
#define STR_RES_PYTHAG 276  // pythag
#define STR_RES_1_4_EB 277  // 1/4 eb
#define STR_RES_1_4_E 278  // 1/4 e
#define STR_RES_1_4_EA 279  // 1/4 ea
#define STR_RES_BHAIRA 280  // bhaira
#define STR_RES_GUNAKR 281  // gunakr
#define STR_RES_MARWA 282  // marwa
#define STR_RES_SHREE 283  // shree
#define STR_RES_PURVI 284  // purvi
#define STR_RES_BILAWA 285  // bilawa
#define STR_RES_YAMAN 286  // yaman
#define STR_RES_KAFI 287  // kafi
#define STR_RES_BHIMPA 288  // bhimpa
#define STR_RES_DARBAR 289  // darbar
#define STR_RES_BAGESH 290  // bagesh
#define STR_RES_RAGESH 291  // ragesh
#define STR_RES_KHAMAJ 292  // khamaj
#define STR_RES_MIMAL 293  // mi'mal
#define STR_RES_PARAME 294  // parame
#define STR_RES_RANGES 295  // ranges
#define STR_RES_GANGES 296  // ganges
#define STR_RES_KAMESH 297  // kamesh
#define STR_RES_PALAS_ 298  // palas 
#define STR_RES_NATBHA 299  // natbha
#define STR_RES_M_KAUN 300  // m.kaun
#define STR_RES_BAIRAG 301  // bairag
#define STR_RES_B_TODI 302  // b.todi
#define STR_RES_CHANDR 303  // chandr
#define STR_RES_KAUSHI 304  // kaushi
#define STR_RES_JOGESH 305  // jogesh
#define STR_RES_RASIA 306  // rasia
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
#define LUT_RES_GROOVE_MONKEY 43
#define LUT_RES_GROOVE_MONKEY_SIZE 16
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
#define WAV_RES_LOW_RES_WAVETABLE_1 24
#define WAV_RES_LOW_RES_WAVETABLE_1_SIZE 2064
#define WAV_RES_LOW_RES_WAVETABLE_2 25
#define WAV_RES_LOW_RES_WAVETABLE_2_SIZE 2064
#define WAV_RES_LOW_RES_WAVETABLE_3 26
#define WAV_RES_LOW_RES_WAVETABLE_3_SIZE 2064
#define WAV_RES_LOW_RES_WAVETABLE_4 27
#define WAV_RES_LOW_RES_WAVETABLE_4_SIZE 2064
#define WAV_RES_LOW_RES_WAVETABLE_5 28
#define WAV_RES_LOW_RES_WAVETABLE_5_SIZE 2064
#define WAV_RES_LOW_RES_WAVETABLE_6 29
#define WAV_RES_LOW_RES_WAVETABLE_6_SIZE 2064
#define WAV_RES_LOW_RES_WAVETABLE_7 30
#define WAV_RES_LOW_RES_WAVETABLE_7_SIZE 2064
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
#define CHR_RES_SPECIAL_CHARACTERS_SIZE 56
typedef hardware_resources::ResourcesManager<
    ResourceId,
    hardware_resources::ResourcesTables<
        string_table,
        lookup_table_table> > ResourcesManager; 

}  // namespace hardware_shruthi

#endif  // HARDWARE_SHRUTHI_RESOURCES_H_
