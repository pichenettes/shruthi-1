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
#define STR_RES_SHAPE 0  // shape
#define STR_RES_PARAMETER 1  // parameter
#define STR_RES_RESONANCE 2  // resonance
#define STR_RES_PRM 3  // prm
#define STR_RES_RANGE 4  // range
#define STR_RES_RNG 5  // rng
#define STR_RES_OP_ 6  // op.
#define STR_RES_OPERATOR 7  // operator
#define STR_RES_DETUNE 8  // detune
#define STR_RES_OSC_MIX 9  // osc mix
#define STR_RES_SUB_OSC_ 10  // sub osc.
#define STR_RES_ENV1TVCF 11  // env1~vcf
#define STR_RES_LFO2TVCF 12  // lfo2~vcf
#define STR_RES_ATTACK 13  // attack
#define STR_RES_ATK 14  // atk
#define STR_RES_DECAY 15  // decay
#define STR_RES_SUSTAIN 16  // sustain
#define STR_RES_RELEASE 17  // release
#define STR_RES_RATE 18  // rate
#define STR_RES_MODULATION 19  // modulation
#define STR_RES_OPERATORS 20  // operators
#define STR_RES_MOD_ 21  // mod.
#define STR_RES_SOURCE 22  // source
#define STR_RES_SRC 23  // src
#define STR_RES_DEST_ 24  // dest.
#define STR_RES_DST 25  // dst
#define STR_RES_AMOUNT 26  // amount
#define STR_RES_AMT 27  // amt
#define STR_RES_MODE 28  // mode
#define STR_RES_TEMPO 29  // tempo
#define STR_RES_BPM 30  // bpm
#define STR_RES_GROOVE 31  // groove
#define STR_RES_DIRECTION 32  // direction
#define STR_RES_PATTERN 33  // pattern
#define STR_RES_WARP 34  // warp
#define STR_RES_WRP 35  // wrp
#define STR_RES_START 36  // start
#define STR_RES_LENGTH 37  // length
#define STR_RES_OCTAVE 38  // octave
#define STR_RES_RAGA 39  // raga
#define STR_RES_PORTA 40  // porta
#define STR_RES_PRT 41  // prt
#define STR_RES_LEGATO 42  // legato
#define STR_RES_TUNING 43  // tuning
#define STR_RES_MIDI_CHAN 44  // midi chan
#define STR_RES_CHN 45  // chn
#define STR_RES_MIDI_OUT 46  // midi out
#define STR_RES_PAUSE 47  // pause
#define STR_RES_SNAP 48  // snap
#define STR_RES_CV_MODE 49  // cv.mode
#define STR_RES_OSCILLATOR_1 50  // oscillator 1
#define STR_RES_OSCILLATOR_2 51  // oscillator 2
#define STR_RES_MIXER 52  // mixer
#define STR_RES_FILTER 53  // filter
#define STR_RES_FILTER_2 54  // filter 2
#define STR_RES_ENVELOPE_1 55  // envelope 1
#define STR_RES_ENVELOPE_2 56  // envelope 2
#define STR_RES_SEQUENCER 57  // sequencer
#define STR_RES_ARPEGGIO 58  // arpeggio
#define STR_RES_STEP_SEQUENCER 59  // step sequencer
#define STR_RES_KEYBOARD 60  // keyboard
#define STR_RES_MIDI 61  // midi
#define STR_RES_SYSTEM 62  // system
#define STR_RES_PERFORMANCE 63  // performance
#define STR_RES_LPF 64  // lpf
#define STR_RES_BPF 65  // bpf
#define STR_RES_HPF 66  // hpf
#define STR_RES_ELP 67  // =lp
#define STR_RES_EBP 68  // =bp
#define STR_RES_EHP 69  // =hp
#define STR_RES_LP 70  // :lp
#define STR_RES_BP 71  // :bp
#define STR_RES_HP 72  // :hp
#define STR_RES_CUT 73  // cut
#define STR_RES_VCA 74  // vca
#define STR_RES_PW1 75  // pw1
#define STR_RES_PW2 76  // pw2
#define STR_RES_51 77  // 1
#define STR_RES_52 78  // 2
#define STR_RES_5 79  // 
#define STR_RES_5F 80  // f
#define STR_RES_MIX 81  // mix
#define STR_RES_NOI 82  // noi
#define STR_RES_SUB 83  // sub
#define STR_RES_RES 84  // res
#define STR_RES__CV1 85  //  cv1
#define STR_RES__CV2 86  //  cv2
#define STR_RES__ATK 87  //  atk
#define STR_RES__LF1 88  //  lf1
#define STR_RES__LF2 89  //  lf2
#define STR_RES_IN1 90  // in1
#define STR_RES_IN2 91  // in2
#define STR_RES_OUT 92  // out
#define STR_RES_ADD 93  // add
#define STR_RES_PRD 94  // prd
#define STR_RES_MAX 95  // max
#define STR_RES_MIN 96  // min
#define STR_RES__XOR 97  //  xor
#define STR_RES_GE 98  // >=
#define STR_RES_LE 99  // <=
#define STR_RES_CUTOFF 100  // cutoff
#define STR_RES__VCA 101  //  vca
#define STR_RES_PWM1 102  // pwm1
#define STR_RES_PWM2 103  // pwm2
#define STR_RES_OSC1 104  // osc1
#define STR_RES_OSC2 105  // osc2
#define STR_RES_OSC1S2 106  // osc1+2
#define STR_RES_FINE 107  // fine
#define STR_RES__MIX 108  //  mix
#define STR_RES_NOISE 109  // noise
#define STR_RES_SUBOSC 110  // subosc
#define STR_RES_RESO 111  // reso
#define STR_RES__CV_1 112  //  cv 1
#define STR_RES__CV_2 113  //  cv 2
#define STR_RES__ATTACK 114  //  attack
#define STR_RES__LFO_1 115  //  lfo 1
#define STR_RES__LFO_2 116  //  lfo 2
#define STR_RES_LF1 117  // lf1
#define STR_RES_LF2 118  // lf2
#define STR_RES_SEQ 119  // seq
#define STR_RES__SQ1 120  //  sq1
#define STR_RES__SQ2 121  //  sq2
#define STR_RES__ARP 122  //  arp
#define STR_RES_WHL 123  // whl
#define STR_RES_AFT 124  // aft
#define STR_RES_BND 125  // bnd
#define STR_RES_OFS 126  // ofs
#define STR_RES_CV1 127  // cv1
#define STR_RES_CV2 128  // cv2
#define STR_RES_CV3 129  // cv3
#define STR_RES_CV4 130  // cv4
#define STR_RES_CCA 131  // ccA
#define STR_RES_CCB 132  // ccB
#define STR_RES_CCC 133  // ccC
#define STR_RES_CCD 134  // ccD
#define STR_RES__NOI 135  //  noi
#define STR_RES_EN1 136  // en1
#define STR_RES_EN2 137  // en2
#define STR_RES_VEL 138  // vel
#define STR_RES_RND 139  // rnd
#define STR_RES_NOT 140  // not
#define STR_RES_GAT 141  // gat
#define STR_RES_AUD 142  // aud
#define STR_RES_OP1 143  // op1
#define STR_RES_OP2 144  // op2
#define STR_RES_LFO_1 145  // lfo 1
#define STR_RES_LFO_2 146  // lfo 2
#define STR_RES_STPSEQ 147  // stpseq
#define STR_RES_STPSQ1 148  // stpsq1
#define STR_RES_STPSQ2 149  // stpsq2
#define STR_RES___ARP 150  //   arp
#define STR_RES_MWHEEL 151  // mwheel
#define STR_RES_AFTTCH 152  // afttch
#define STR_RES_BENDER 153  // bender
#define STR_RES_OFFSET 154  // offset
#define STR_RES_CV_1 155  // cv 1
#define STR_RES_CV_2 156  // cv 2
#define STR_RES_CV_3 157  // cv 3
#define STR_RES_CV_4 158  // cv 4
#define STR_RES_CC_A 159  // cc A
#define STR_RES_CC_B 160  // cc B
#define STR_RES_CC_C 161  // cc C
#define STR_RES_CC_D 162  // cc D
#define STR_RES___NOISE 163  //   noise
#define STR_RES_ENV_1 164  // env 1
#define STR_RES_ENV_2 165  // env 2
#define STR_RES_VELO 166  // velo
#define STR_RES_RANDOM 167  // random
#define STR_RES_NOTE 168  // note
#define STR_RES_GATE 169  // gate
#define STR_RES_AUDIO 170  // audio
#define STR_RES_OP__1 171  // op. 1
#define STR_RES_OP__2 172  // op. 2
#define STR_RES_TOUCH_A_KNOB_TO 173  // touch a knob to
#define STR_RES_ASSIGN_PARAMETER 174  // assign parameter
#define STR_RES_PATCH 175  // patch
#define STR_RES_SEQUENCE 176  // sequence
#define STR_RES_SAVE_MIDI_KBD 177  // save midi/kbd
#define STR_RES_SETTINGS_ 178  // settings?
#define STR_RES_START_FULL_MIDI 179  // start full midi
#define STR_RES_BACKUP_ 180  // backup?
#define STR_RES_BROWSE 181  // browse
#define STR_RES_SAVE 182  // save
#define STR_RES_COMPARE 183  // compare
#define STR_RES_ 184  // ----
#define STR_RES_V 185  // v
#define STR_RES_MUTABLE____V0_92 186  // mutable    v0.92
#define STR_RES_INSTRUMENTS_671 187  // instruments -1
#define STR_RES_EXTERN 188  // extern
#define STR_RES_X2_EXT 189  // x2 ext
#define STR_RES__2_EXT 190  // /2 ext
#define STR_RES__4_EXT 191  // /4 ext
#define STR_RES__8_EXT 192  // /8 ext
#define STR_RES_SUM 193  // sum
#define STR_RES_SYNC 194  // sync
#define STR_RES_RING 195  // ring
#define STR_RES_XOR 196  // xor
#define STR_RES_FUZZ 197  // fuzz
#define STR_RES_GG4 198  // >>4
#define STR_RES_GG8 199  // >>8
#define STR_RES_STP 200  // stp
#define STR_RES_ARP 201  // arp
#define STR_RES_ARPSLT 202  // arp+lt
#define STR_RES__SEQ 203  //  seq
#define STR_RES_SEQSLT 204  // seq+lt
#define STR_RES_REC 205  // rec
#define STR_RES_IMPRO 206  // impro
#define STR_RES_FREE 207  // free
#define STR_RES_SLAVE 208  // slave
#define STR_RES_MASTER 209  // master
#define STR_RES_T 210  // ~
#define STR_RES___ 211  //  
#define STR_RES_T_ 212  // ~-
#define STR_RES__T_ 213  //  ~
#define STR_RES_GLASS 214  // glass
#define STR_RES_KRAMA 215  // krama
#define STR_RES_JATA 216  // jata
#define STR_RES_SIKHA 217  // sikha
#define STR_RES_GHANA 218  // ghana
#define STR_RES_2GLASS 219  // 2glass
#define STR_RES_2KRAMA 220  // 2krama
#define STR_RES_2JATA 221  // 2jata
#define STR_RES_2SIKHA 222  // 2sikha
#define STR_RES_2GHANA 223  // 2ghana
#define STR_RES_4GLASS 224  // 4glass
#define STR_RES_4KRAMA 225  // 4krama
#define STR_RES_4JATA 226  // 4jata
#define STR_RES_4SIKHA 227  // 4sikha
#define STR_RES_4GHANA 228  // 4ghana
#define STR_RES_SWING 229  // swing
#define STR_RES_SHUFFLE 230  // shuffle
#define STR_RES_PUSH 231  // push
#define STR_RES_LAG 232  // lag
#define STR_RES_HUMAN 233  // human
#define STR_RES_MONKEY 234  // monkey
#define STR_RES__OFF 235  //  off
#define STR_RES_THRU 236  // thru
#define STR_RES___SEQ 237  //   seq
#define STR_RES_SPLIT 238  // split
#define STR_RES_FULL 239  // full
#define STR_RES_1T_ 240  // 1~|
#define STR_RES_2T1 241  // 2~1
#define STR_RES_3T2 242  // 3~2
#define STR_RES_4T3 243  // 4~3
#define STR_RES_5T4 244  // 5~4
#define STR_RES_6T5 245  // 6~5
#define STR_RES_7T6 246  // 7~6
#define STR_RES_8T7 247  // 8~7
#define STR_RES_TRI 248  // tri
#define STR_RES_SQR 249  // sqr
#define STR_RES_S_H 250  // s&h
#define STR_RES_RAMP 251  // ramp
#define STR_RES_STEP 252  // step
#define STR_RES_3 253  // 
#define STR_RES_4 254  // 
#define STR_RES_34 255  // 
#define STR_RES__ 256  // ?
#define STR_RES_OFF 257  // off
#define STR_RES_ON 258  // on
#define STR_RES_SQ1 259  // sq1
#define STR_RES_TR1 260  // tr1
#define STR_RES_PL1 261  // pl1
#define STR_RES_SQ2 262  // sq2
#define STR_RES_TR2 263  // tr2
#define STR_RES_PL2 264  // pl2
#define STR_RES_CLICK 265  // click
#define STR_RES_GLITCH 266  // glitch
#define STR_RES_BLOW 267  // blow
#define STR_RES_METAL 268  // metal
#define STR_RES_POP 269  // pop
#define STR_RES_NONE 270  // none
#define STR_RES_SAW 271  // saw
#define STR_RES_SQUARE 272  // square
#define STR_RES_TRIANG 273  // triang
#define STR_RES_ZSAW 274  // zsaw
#define STR_RES_ZRESO 275  // zreso
#define STR_RES_ZTRI 276  // ztri
#define STR_RES_ZPULSE 277  // zpulse
#define STR_RES_ZSYNC 278  // zsync
#define STR_RES_PAD 279  // pad
#define STR_RES_FM 280  // fm
#define STR_RES_WAVES 281  // waves
#define STR_RES_TAMPUR 282  // tampur
#define STR_RES_DIGITL 283  // digitl
#define STR_RES_METALL 284  // metall
#define STR_RES_BOWED 285  // bowed
#define STR_RES_SLAP 286  // slap
#define STR_RES_ORGAN 287  // organ
#define STR_RES_MALE 288  // male
#define STR_RES_USER 289  // user
#define STR_RES_8BITS 290  // 8bits
#define STR_RES_CRUSH 291  // crush
#define STR_RES_PWM 292  // pwm
#define STR_RES__NOISE 293  //  noise
#define STR_RES_VOWEL 294  // vowel
#define STR_RES__LPF 295  //  lpf
#define STR_RES_SSM 296  // ssm
#define STR_RES_SVF 297  // svf
#define STR_RES_4CV_IN 298  // 4cv in
#define STR_RES_PRGM 299  // prgm
#define STR_RES_PEDALS 300  // pedals
#define STR_RES_EQUAL 301  // equal
#define STR_RES_JUST 302  // just
#define STR_RES_PYTHAG 303  // pythag
#define STR_RES_1_4_EB 304  // 1/4 eb
#define STR_RES_1_4_E 305  // 1/4 e
#define STR_RES_1_4_EA 306  // 1/4 ea
#define STR_RES_BHAIRA 307  // bhaira
#define STR_RES_GUNAKR 308  // gunakr
#define STR_RES_MARWA 309  // marwa
#define STR_RES_SHREE 310  // shree
#define STR_RES_PURVI 311  // purvi
#define STR_RES_BILAWA 312  // bilawa
#define STR_RES_YAMAN 313  // yaman
#define STR_RES_KAFI 314  // kafi
#define STR_RES_BHIMPA 315  // bhimpa
#define STR_RES_DARBAR 316  // darbar
#define STR_RES_BAGESH 317  // bagesh
#define STR_RES_RAGESH 318  // ragesh
#define STR_RES_KHAMAJ 319  // khamaj
#define STR_RES_MIMAL 320  // mi'mal
#define STR_RES_PARAME 321  // parame
#define STR_RES_RANGES 322  // ranges
#define STR_RES_GANGES 323  // ganges
#define STR_RES_KAMESH 324  // kamesh
#define STR_RES_PALAS_ 325  // palas 
#define STR_RES_NATBHA 326  // natbha
#define STR_RES_M_KAUN 327  // m.kaun
#define STR_RES_BAIRAG 328  // bairag
#define STR_RES_B_TODI 329  // b.todi
#define STR_RES_CHANDR 330  // chandr
#define STR_RES_KAUSHI 331  // kaushi
#define STR_RES_JOGESH 332  // jogesh
#define STR_RES_RASIA 333  // rasia
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
#define WAV_RES_WAVETABLE_1_SIZE 2064
#define WAV_RES_WAVETABLE_2 24
#define WAV_RES_WAVETABLE_2_SIZE 2064
#define WAV_RES_WAVETABLE_3 25
#define WAV_RES_WAVETABLE_3_SIZE 2064
#define WAV_RES_WAVETABLE_4 26
#define WAV_RES_WAVETABLE_4_SIZE 2064
#define WAV_RES_WAVETABLE_5 27
#define WAV_RES_WAVETABLE_5_SIZE 2064
#define WAV_RES_WAVETABLE_6 28
#define WAV_RES_WAVETABLE_6_SIZE 2064
#define WAV_RES_WAVETABLE_7 29
#define WAV_RES_WAVETABLE_7_SIZE 2064
#define WAV_RES_WAVETABLE_8 30
#define WAV_RES_WAVETABLE_8_SIZE 2064
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
