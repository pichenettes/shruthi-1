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


#ifndef SHRUTHI_RESOURCES_H_
#define SHRUTHI_RESOURCES_H_


#include "avrlib/base.h"

#include <avr/pgmspace.h>


#include "avrlib/resources_manager.h"
namespace shruthi {

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
extern const prog_uint8_t wav_res_vowel_data[] PROGMEM;
extern const prog_uint8_t wav_res_expansion_krama[] PROGMEM;
extern const prog_uint8_t wav_res_expansion_jata[] PROGMEM;
extern const prog_uint8_t wav_res_expansion_sikha[] PROGMEM;
extern const prog_uint8_t wav_res_expansion_ghana[] PROGMEM;
extern const prog_uint8_t wav_res_distortion[] PROGMEM;
extern const prog_uint8_t wav_res_waves[] PROGMEM;
extern const prog_uint8_t wav_res_wavetables[] PROGMEM;
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
#define STR_RES_FILTERS 54  // filter+
#define STR_RES_MODE_1 55  // mode 1
#define STR_RES_MODE_2 56  // mode 2
#define STR_RES_MD1 57  // md1
#define STR_RES_MD2 58  // md2
#define STR_RES_ENVELOPE_1 59  // envelope 1
#define STR_RES_ENVELOPE_2 60  // envelope 2
#define STR_RES_SEQUENCER 61  // sequencer
#define STR_RES_ARPEGGIO 62  // arpeggio
#define STR_RES_STEP_SEQUENCER 63  // step sequencer
#define STR_RES_KEYBOARD 64  // keyboard
#define STR_RES_MIDI 65  // midi
#define STR_RES_SYSTEM 66  // system
#define STR_RES_PERFORMANCE 67  // performance
#define STR_RES_LPF 68  // lpf
#define STR_RES_BPF 69  // bpf
#define STR_RES_HPF 70  // hpf
#define STR_RES_SLP 71  // +lp
#define STR_RES_SBP 72  // +bp
#define STR_RES_SHP 73  // +hp
#define STR_RES_GLP 74  // >lp
#define STR_RES_GBP 75  // >bp
#define STR_RES_GHP 76  // >hp
#define STR_RES_CUT 77  // cut
#define STR_RES_VCA 78  // vca
#define STR_RES_PW1 79  // pw1
#define STR_RES_PW2 80  // pw2
#define STR_RES_51 81  // 1
#define STR_RES_52 82  // 2
#define STR_RES_5 83  // 
#define STR_RES_5F 84  // f
#define STR_RES_MIX 85  // mix
#define STR_RES_NOI 86  // noi
#define STR_RES_SUB 87  // sub
#define STR_RES_RES 88  // res
#define STR_RES__CV1 89  //  cv1
#define STR_RES__CV2 90  //  cv2
#define STR_RES__ATK 91  //  atk
#define STR_RES__LF1 92  //  lf1
#define STR_RES__LF2 93  //  lf2
#define STR_RES_IN1 94  // in1
#define STR_RES_IN2 95  // in2
#define STR_RES_OUT 96  // out
#define STR_RES___OFF 97  //   off
#define STR_RES_ADD 98  // add
#define STR_RES_PRD 99  // prd
#define STR_RES_MAX 100  // max
#define STR_RES_MIN 101  // min
#define STR_RES__XOR 102  //  xor
#define STR_RES_GE 103  // >=
#define STR_RES_LE 104  // <=
#define STR_RES_CUTOFF 105  // cutoff
#define STR_RES__VCA 106  //  vca
#define STR_RES_PWM1 107  // pwm1
#define STR_RES_PWM2 108  // pwm2
#define STR_RES_OSC1 109  // osc1
#define STR_RES_OSC2 110  // osc2
#define STR_RES_OSC1S2 111  // osc1+2
#define STR_RES_FINE 112  // fine
#define STR_RES__MIX 113  //  mix
#define STR_RES_NOISE 114  // noise
#define STR_RES_SUBOSC 115  // subosc
#define STR_RES_RESO 116  // reso
#define STR_RES__CV_1 117  //  cv 1
#define STR_RES__CV_2 118  //  cv 2
#define STR_RES__ATTACK 119  //  attack
#define STR_RES__LFO_1 120  //  lfo 1
#define STR_RES__LFO_2 121  //  lfo 2
#define STR_RES_LF1 122  // lf1
#define STR_RES_LF2 123  // lf2
#define STR_RES_SEQ 124  // seq
#define STR_RES__SQ1 125  //  sq1
#define STR_RES__SQ2 126  //  sq2
#define STR_RES__ARP 127  //  arp
#define STR_RES_WHL 128  // whl
#define STR_RES_AFT 129  // aft
#define STR_RES_BND 130  // bnd
#define STR_RES_OFS 131  // ofs
#define STR_RES_CV1 132  // cv1
#define STR_RES_CV2 133  // cv2
#define STR_RES_CV3 134  // cv3
#define STR_RES_CV4 135  // cv4
#define STR_RES_CCA 136  // ccA
#define STR_RES_CCB 137  // ccB
#define STR_RES_CCC 138  // ccC
#define STR_RES_CCD 139  // ccD
#define STR_RES__NOI 140  //  noi
#define STR_RES_EN1 141  // en1
#define STR_RES_EN2 142  // en2
#define STR_RES_VEL 143  // vel
#define STR_RES_RND 144  // rnd
#define STR_RES_NOT 145  // not
#define STR_RES_GAT 146  // gat
#define STR_RES_AUD 147  // aud
#define STR_RES_OP1 148  // op1
#define STR_RES_OP2 149  // op2
#define STR_RES_LFO_1 150  // lfo 1
#define STR_RES_LFO_2 151  // lfo 2
#define STR_RES_STPSEQ 152  // stpseq
#define STR_RES_STPSQ1 153  // stpsq1
#define STR_RES_STPSQ2 154  // stpsq2
#define STR_RES___ARP 155  //   arp
#define STR_RES_MWHEEL 156  // mwheel
#define STR_RES_AFTTCH 157  // afttch
#define STR_RES_BENDER 158  // bender
#define STR_RES_OFFSET 159  // offset
#define STR_RES_CV_1 160  // cv 1
#define STR_RES_CV_2 161  // cv 2
#define STR_RES_CV_3 162  // cv 3
#define STR_RES_CV_4 163  // cv 4
#define STR_RES_CC_A 164  // cc A
#define STR_RES_CC_B 165  // cc B
#define STR_RES_CC_C 166  // cc C
#define STR_RES_CC_D 167  // cc D
#define STR_RES___NOISE 168  //   noise
#define STR_RES_ENV_1 169  // env 1
#define STR_RES_ENV_2 170  // env 2
#define STR_RES_VELO 171  // velo
#define STR_RES_RANDOM 172  // random
#define STR_RES_NOTE 173  // note
#define STR_RES_GATE 174  // gate
#define STR_RES_AUDIO 175  // audio
#define STR_RES_OP__1 176  // op. 1
#define STR_RES_OP__2 177  // op. 2
#define STR_RES_TOUCH_A_KNOB_TO 178  // touch a knob to
#define STR_RES_ASSIGN_PARAMETER 179  // assign parameter
#define STR_RES_PATCH 180  // patch
#define STR_RES_SEQUENCE 181  // sequence
#define STR_RES_COMBO 182  // combo
#define STR_RES_SAVE_MIDI_KBD 183  // save midi/kbd
#define STR_RES_SETTINGS_ 184  // settings?
#define STR_RES_START_FULL_MIDI 185  // start full midi
#define STR_RES_BACKUP_ 186  // backup?
#define STR_RES_BROWSE 187  // browse
#define STR_RES_SAVE 188  // save
#define STR_RES_COMPARE 189  // compare
#define STR_RES_ 190  // ----
#define STR_RES_V 191  // v
#define STR_RES_MUTABLE____V0_93 192  // mutable    v0.93
#define STR_RES_INSTRUMENTS_671 193  // instruments -1
#define STR_RES_EXTERN 194  // extern
#define STR_RES_X2_EXT 195  // x2 ext
#define STR_RES__2_EXT 196  // /2 ext
#define STR_RES__4_EXT 197  // /4 ext
#define STR_RES__8_EXT 198  // /8 ext
#define STR_RES_SUM 199  // sum
#define STR_RES_SYNC 200  // sync
#define STR_RES_RING 201  // ring
#define STR_RES_XOR 202  // xor
#define STR_RES_FUZZ 203  // fuzz
#define STR_RES_GG4 204  // >>4
#define STR_RES_GG8 205  // >>8
#define STR_RES_STP 206  // stp
#define STR_RES_ARP 207  // arp
#define STR_RES_ARPSLT 208  // arp+lt
#define STR_RES__SEQ 209  //  seq
#define STR_RES_SEQSLT 210  // seq+lt
#define STR_RES_REC 211  // rec
#define STR_RES_IMPRO 212  // impro
#define STR_RES_FREE 213  // free
#define STR_RES_SLAVE 214  // slave
#define STR_RES_MASTER 215  // master
#define STR_RES_T 216  // ~
#define STR_RES___ 217  //  
#define STR_RES_T_ 218  // ~-
#define STR_RES__T_ 219  //  ~
#define STR_RES_GLASS 220  // glass
#define STR_RES_KRAMA 221  // krama
#define STR_RES_JATA 222  // jata
#define STR_RES_SIKHA 223  // sikha
#define STR_RES_GHANA 224  // ghana
#define STR_RES_2GLASS 225  // 2glass
#define STR_RES_2KRAMA 226  // 2krama
#define STR_RES_2JATA 227  // 2jata
#define STR_RES_2SIKHA 228  // 2sikha
#define STR_RES_2GHANA 229  // 2ghana
#define STR_RES_4GLASS 230  // 4glass
#define STR_RES_4KRAMA 231  // 4krama
#define STR_RES_4JATA 232  // 4jata
#define STR_RES_4SIKHA 233  // 4sikha
#define STR_RES_4GHANA 234  // 4ghana
#define STR_RES_SWING 235  // swing
#define STR_RES_SHUFFLE 236  // shuffle
#define STR_RES_PUSH 237  // push
#define STR_RES_LAG 238  // lag
#define STR_RES_HUMAN 239  // human
#define STR_RES_MONKEY 240  // monkey
#define STR_RES__OFF 241  //  off
#define STR_RES_THRU 242  // thru
#define STR_RES___SEQ 243  //   seq
#define STR_RES_CTRL 244  // ctrl
#define STR_RES_SPLIT 245  // split
#define STR_RES_FULL 246  // full
#define STR_RES_1TV 247  // 1~|
#define STR_RES_2T1 248  // 2~1
#define STR_RES_3T2 249  // 3~2
#define STR_RES_4T3 250  // 4~3
#define STR_RES_5T4 251  // 5~4
#define STR_RES_6T5 252  // 6~5
#define STR_RES_7T6 253  // 7~6
#define STR_RES_8T7 254  // 8~7
#define STR_RES_TRI 255  // tri
#define STR_RES_SQR 256  // sqr
#define STR_RES_S_H 257  // s&h
#define STR_RES_RAMP 258  // ramp
#define STR_RES_STEP 259  // step
#define STR_RES_3 260  // 
#define STR_RES_4 261  // 
#define STR_RES_34 262  // 
#define STR_RES__ 263  // ?
#define STR_RES_OFF 264  // off
#define STR_RES_ON 265  // on
#define STR_RES_SQ1 266  // sq1
#define STR_RES_TR1 267  // tr1
#define STR_RES_PL1 268  // pl1
#define STR_RES_SQ2 269  // sq2
#define STR_RES_TR2 270  // tr2
#define STR_RES_PL2 271  // pl2
#define STR_RES_CLICK 272  // click
#define STR_RES_GLITCH 273  // glitch
#define STR_RES_BLOW 274  // blow
#define STR_RES_METAL 275  // metal
#define STR_RES_POP 276  // pop
#define STR_RES_NONE 277  // none
#define STR_RES_SAW 278  // saw
#define STR_RES_SQUARE 279  // square
#define STR_RES_TRIANG 280  // triang
#define STR_RES_ZSAW 281  // zsaw
#define STR_RES_ZRESO 282  // zreso
#define STR_RES_ZTRI 283  // ztri
#define STR_RES_ZPULSE 284  // zpulse
#define STR_RES_ZSYNC 285  // zsync
#define STR_RES_PAD 286  // pad
#define STR_RES_FM 287  // fm
#define STR_RES_WAVES 288  // waves
#define STR_RES_TAMPUR 289  // tampur
#define STR_RES_DIGITL 290  // digitl
#define STR_RES_METALL 291  // metall
#define STR_RES_BOWED 292  // bowed
#define STR_RES_SLAP 293  // slap
#define STR_RES_ORGAN 294  // organ
#define STR_RES_MALE 295  // male
#define STR_RES_USER 296  // user
#define STR_RES_8BITS 297  // 8bits
#define STR_RES_CRUSH 298  // crush
#define STR_RES_PWM 299  // pwm
#define STR_RES__NOISE 300  //  noise
#define STR_RES_VOWEL 301  // vowel
#define STR_RES_BELISH 302  // belish
#define STR_RES_POLATD 303  // polatd
#define STR_RES_CELLO 304  // cello
#define STR_RES_CLPSWP 305  // clpswp
#define STR_RES_FEMALE 306  // female
#define STR_RES_FMTVOC 307  // fmtvoc
#define STR_RES_FRMNT2 308  // frmnt2
#define STR_RES_RES3HP 309  // res3hp
#define STR_RES_ELECTP 310  // electp
#define STR_RES_VIBES 311  // vibes
#define STR_RES__LPF 312  //  lpf
#define STR_RES_SSM 313  // ssm
#define STR_RES_SVF 314  // svf
#define STR_RES_4CV_IN 315  // 4cv in
#define STR_RES_PRGM 316  // prgm
#define STR_RES_PEDALS 317  // pedals
#define STR_RES_EQUAL 318  // equal
#define STR_RES_JUST 319  // just
#define STR_RES_PYTHAG 320  // pythag
#define STR_RES_1_4_EB 321  // 1/4 eb
#define STR_RES_1_4_E 322  // 1/4 e
#define STR_RES_1_4_EA 323  // 1/4 ea
#define STR_RES_BHAIRA 324  // bhaira
#define STR_RES_GUNAKR 325  // gunakr
#define STR_RES_MARWA 326  // marwa
#define STR_RES_SHREE 327  // shree
#define STR_RES_PURVI 328  // purvi
#define STR_RES_BILAWA 329  // bilawa
#define STR_RES_YAMAN 330  // yaman
#define STR_RES_KAFI 331  // kafi
#define STR_RES_BHIMPA 332  // bhimpa
#define STR_RES_DARBAR 333  // darbar
#define STR_RES_BAGESH 334  // bagesh
#define STR_RES_RAGESH 335  // ragesh
#define STR_RES_KHAMAJ 336  // khamaj
#define STR_RES_MIMAL 337  // mi'mal
#define STR_RES_PARAME 338  // parame
#define STR_RES_RANGES 339  // ranges
#define STR_RES_GANGES 340  // ganges
#define STR_RES_KAMESH 341  // kamesh
#define STR_RES_PALAS_ 342  // palas 
#define STR_RES_NATBHA 343  // natbha
#define STR_RES_M_KAUN 344  // m.kaun
#define STR_RES_BAIRAG 345  // bairag
#define STR_RES_B_TODI 346  // b.todi
#define STR_RES_CHANDR 347  // chandr
#define STR_RES_KAUSHI 348  // kaushi
#define STR_RES_JOGESH 349  // jogesh
#define STR_RES_RASIA 350  // rasia
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
#define WAV_RES_VOWEL_DATA 23
#define WAV_RES_VOWEL_DATA_SIZE 45
#define WAV_RES_EXPANSION_KRAMA 24
#define WAV_RES_EXPANSION_KRAMA_SIZE 30
#define WAV_RES_EXPANSION_JATA 25
#define WAV_RES_EXPANSION_JATA_SIZE 90
#define WAV_RES_EXPANSION_SIKHA 26
#define WAV_RES_EXPANSION_SIKHA_SIZE 126
#define WAV_RES_EXPANSION_GHANA 27
#define WAV_RES_EXPANSION_GHANA_SIZE 182
#define WAV_RES_DISTORTION 28
#define WAV_RES_DISTORTION_SIZE 256
#define WAV_RES_WAVES 29
#define WAV_RES_WAVES_SIZE 16512
#define WAV_RES_WAVETABLES 30
#define WAV_RES_WAVETABLES_SIZE 324
#define CHR_RES_SPECIAL_CHARACTERS 0
#define CHR_RES_SPECIAL_CHARACTERS_SIZE 56
typedef avrlib::ResourcesManager<
    ResourceId,
    avrlib::ResourcesTables<
        string_table,
        lookup_table_table> > ResourcesManager; 

}  // namespace shruthi

#endif  // SHRUTHI_RESOURCES_H_
