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
#define STR_RES___OFF 93  //   off
#define STR_RES_ADD 94  // add
#define STR_RES_PRD 95  // prd
#define STR_RES_MAX 96  // max
#define STR_RES_MIN 97  // min
#define STR_RES__XOR 98  //  xor
#define STR_RES_GE 99  // >=
#define STR_RES_LE 100  // <=
#define STR_RES_CUTOFF 101  // cutoff
#define STR_RES__VCA 102  //  vca
#define STR_RES_PWM1 103  // pwm1
#define STR_RES_PWM2 104  // pwm2
#define STR_RES_OSC1 105  // osc1
#define STR_RES_OSC2 106  // osc2
#define STR_RES_OSC1S2 107  // osc1+2
#define STR_RES_FINE 108  // fine
#define STR_RES__MIX 109  //  mix
#define STR_RES_NOISE 110  // noise
#define STR_RES_SUBOSC 111  // subosc
#define STR_RES_RESO 112  // reso
#define STR_RES__CV_1 113  //  cv 1
#define STR_RES__CV_2 114  //  cv 2
#define STR_RES__ATTACK 115  //  attack
#define STR_RES__LFO_1 116  //  lfo 1
#define STR_RES__LFO_2 117  //  lfo 2
#define STR_RES_LF1 118  // lf1
#define STR_RES_LF2 119  // lf2
#define STR_RES_SEQ 120  // seq
#define STR_RES__SQ1 121  //  sq1
#define STR_RES__SQ2 122  //  sq2
#define STR_RES__ARP 123  //  arp
#define STR_RES_WHL 124  // whl
#define STR_RES_AFT 125  // aft
#define STR_RES_BND 126  // bnd
#define STR_RES_OFS 127  // ofs
#define STR_RES_CV1 128  // cv1
#define STR_RES_CV2 129  // cv2
#define STR_RES_CV3 130  // cv3
#define STR_RES_CV4 131  // cv4
#define STR_RES_CCA 132  // ccA
#define STR_RES_CCB 133  // ccB
#define STR_RES_CCC 134  // ccC
#define STR_RES_CCD 135  // ccD
#define STR_RES__NOI 136  //  noi
#define STR_RES_EN1 137  // en1
#define STR_RES_EN2 138  // en2
#define STR_RES_VEL 139  // vel
#define STR_RES_RND 140  // rnd
#define STR_RES_NOT 141  // not
#define STR_RES_GAT 142  // gat
#define STR_RES_AUD 143  // aud
#define STR_RES_OP1 144  // op1
#define STR_RES_OP2 145  // op2
#define STR_RES_LFO_1 146  // lfo 1
#define STR_RES_LFO_2 147  // lfo 2
#define STR_RES_STPSEQ 148  // stpseq
#define STR_RES_STPSQ1 149  // stpsq1
#define STR_RES_STPSQ2 150  // stpsq2
#define STR_RES___ARP 151  //   arp
#define STR_RES_MWHEEL 152  // mwheel
#define STR_RES_AFTTCH 153  // afttch
#define STR_RES_BENDER 154  // bender
#define STR_RES_OFFSET 155  // offset
#define STR_RES_CV_1 156  // cv 1
#define STR_RES_CV_2 157  // cv 2
#define STR_RES_CV_3 158  // cv 3
#define STR_RES_CV_4 159  // cv 4
#define STR_RES_CC_A 160  // cc A
#define STR_RES_CC_B 161  // cc B
#define STR_RES_CC_C 162  // cc C
#define STR_RES_CC_D 163  // cc D
#define STR_RES___NOISE 164  //   noise
#define STR_RES_ENV_1 165  // env 1
#define STR_RES_ENV_2 166  // env 2
#define STR_RES_VELO 167  // velo
#define STR_RES_RANDOM 168  // random
#define STR_RES_NOTE 169  // note
#define STR_RES_GATE 170  // gate
#define STR_RES_AUDIO 171  // audio
#define STR_RES_OP__1 172  // op. 1
#define STR_RES_OP__2 173  // op. 2
#define STR_RES_TOUCH_A_KNOB_TO 174  // touch a knob to
#define STR_RES_ASSIGN_PARAMETER 175  // assign parameter
#define STR_RES_PATCH 176  // patch
#define STR_RES_SEQUENCE 177  // sequence
#define STR_RES_COMBO 178  // combo
#define STR_RES_SAVE_MIDI_KBD 179  // save midi/kbd
#define STR_RES_SETTINGS_ 180  // settings?
#define STR_RES_START_FULL_MIDI 181  // start full midi
#define STR_RES_BACKUP_ 182  // backup?
#define STR_RES_BROWSE 183  // browse
#define STR_RES_SAVE 184  // save
#define STR_RES_COMPARE 185  // compare
#define STR_RES_ 186  // ----
#define STR_RES_V 187  // v
#define STR_RES_MUTABLE____V0_92 188  // mutable    v0.92
#define STR_RES_INSTRUMENTS_671 189  // instruments -1
#define STR_RES_EXTERN 190  // extern
#define STR_RES_X2_EXT 191  // x2 ext
#define STR_RES__2_EXT 192  // /2 ext
#define STR_RES__4_EXT 193  // /4 ext
#define STR_RES__8_EXT 194  // /8 ext
#define STR_RES_SUM 195  // sum
#define STR_RES_SYNC 196  // sync
#define STR_RES_RING 197  // ring
#define STR_RES_XOR 198  // xor
#define STR_RES_FUZZ 199  // fuzz
#define STR_RES_GG4 200  // >>4
#define STR_RES_GG8 201  // >>8
#define STR_RES_STP 202  // stp
#define STR_RES_ARP 203  // arp
#define STR_RES_ARPSLT 204  // arp+lt
#define STR_RES__SEQ 205  //  seq
#define STR_RES_SEQSLT 206  // seq+lt
#define STR_RES_REC 207  // rec
#define STR_RES_IMPRO 208  // impro
#define STR_RES_FREE 209  // free
#define STR_RES_SLAVE 210  // slave
#define STR_RES_MASTER 211  // master
#define STR_RES_T 212  // ~
#define STR_RES___ 213  //  
#define STR_RES_T_ 214  // ~-
#define STR_RES__T_ 215  //  ~
#define STR_RES_GLASS 216  // glass
#define STR_RES_KRAMA 217  // krama
#define STR_RES_JATA 218  // jata
#define STR_RES_SIKHA 219  // sikha
#define STR_RES_GHANA 220  // ghana
#define STR_RES_2GLASS 221  // 2glass
#define STR_RES_2KRAMA 222  // 2krama
#define STR_RES_2JATA 223  // 2jata
#define STR_RES_2SIKHA 224  // 2sikha
#define STR_RES_2GHANA 225  // 2ghana
#define STR_RES_4GLASS 226  // 4glass
#define STR_RES_4KRAMA 227  // 4krama
#define STR_RES_4JATA 228  // 4jata
#define STR_RES_4SIKHA 229  // 4sikha
#define STR_RES_4GHANA 230  // 4ghana
#define STR_RES_SWING 231  // swing
#define STR_RES_SHUFFLE 232  // shuffle
#define STR_RES_PUSH 233  // push
#define STR_RES_LAG 234  // lag
#define STR_RES_HUMAN 235  // human
#define STR_RES_MONKEY 236  // monkey
#define STR_RES__OFF 237  //  off
#define STR_RES_THRU 238  // thru
#define STR_RES___SEQ 239  //   seq
#define STR_RES_CTRL 240  // ctrl
#define STR_RES_SPLIT 241  // split
#define STR_RES_FULL 242  // full
#define STR_RES_1TV 243  // 1~|
#define STR_RES_2T1 244  // 2~1
#define STR_RES_3T2 245  // 3~2
#define STR_RES_4T3 246  // 4~3
#define STR_RES_5T4 247  // 5~4
#define STR_RES_6T5 248  // 6~5
#define STR_RES_7T6 249  // 7~6
#define STR_RES_8T7 250  // 8~7
#define STR_RES_TRI 251  // tri
#define STR_RES_SQR 252  // sqr
#define STR_RES_S_H 253  // s&h
#define STR_RES_RAMP 254  // ramp
#define STR_RES_STEP 255  // step
#define STR_RES_3 256  // 
#define STR_RES_4 257  // 
#define STR_RES_34 258  // 
#define STR_RES__ 259  // ?
#define STR_RES_OFF 260  // off
#define STR_RES_ON 261  // on
#define STR_RES_SQ1 262  // sq1
#define STR_RES_TR1 263  // tr1
#define STR_RES_PL1 264  // pl1
#define STR_RES_SQ2 265  // sq2
#define STR_RES_TR2 266  // tr2
#define STR_RES_PL2 267  // pl2
#define STR_RES_CLICK 268  // click
#define STR_RES_GLITCH 269  // glitch
#define STR_RES_BLOW 270  // blow
#define STR_RES_METAL 271  // metal
#define STR_RES_POP 272  // pop
#define STR_RES_NONE 273  // none
#define STR_RES_SAW 274  // saw
#define STR_RES_SQUARE 275  // square
#define STR_RES_TRIANG 276  // triang
#define STR_RES_ZSAW 277  // zsaw
#define STR_RES_ZRESO 278  // zreso
#define STR_RES_ZTRI 279  // ztri
#define STR_RES_ZPULSE 280  // zpulse
#define STR_RES_ZSYNC 281  // zsync
#define STR_RES_PAD 282  // pad
#define STR_RES_FM 283  // fm
#define STR_RES_WAVES 284  // waves
#define STR_RES_TAMPUR 285  // tampur
#define STR_RES_DIGITL 286  // digitl
#define STR_RES_METALL 287  // metall
#define STR_RES_BOWED 288  // bowed
#define STR_RES_SLAP 289  // slap
#define STR_RES_ORGAN 290  // organ
#define STR_RES_MALE 291  // male
#define STR_RES_USER 292  // user
#define STR_RES_8BITS 293  // 8bits
#define STR_RES_CRUSH 294  // crush
#define STR_RES_PWM 295  // pwm
#define STR_RES__NOISE 296  //  noise
#define STR_RES_VOWEL 297  // vowel
#define STR_RES_BELISH 298  // belish
#define STR_RES_POLATD 299  // polatd
#define STR_RES_CELLO 300  // cello
#define STR_RES_CLPSWP 301  // clpswp
#define STR_RES_FEMALE 302  // female
#define STR_RES_FMTVOC 303  // fmtvoc
#define STR_RES_FRMNT2 304  // frmnt2
#define STR_RES_RES3HP 305  // res3hp
#define STR_RES_ELECTP 306  // electp
#define STR_RES_VIBES 307  // vibes
#define STR_RES__LPF 308  //  lpf
#define STR_RES_SSM 309  // ssm
#define STR_RES_SVF 310  // svf
#define STR_RES_4CV_IN 311  // 4cv in
#define STR_RES_PRGM 312  // prgm
#define STR_RES_PEDALS 313  // pedals
#define STR_RES_EQUAL 314  // equal
#define STR_RES_JUST 315  // just
#define STR_RES_PYTHAG 316  // pythag
#define STR_RES_1_4_EB 317  // 1/4 eb
#define STR_RES_1_4_E 318  // 1/4 e
#define STR_RES_1_4_EA 319  // 1/4 ea
#define STR_RES_BHAIRA 320  // bhaira
#define STR_RES_GUNAKR 321  // gunakr
#define STR_RES_MARWA 322  // marwa
#define STR_RES_SHREE 323  // shree
#define STR_RES_PURVI 324  // purvi
#define STR_RES_BILAWA 325  // bilawa
#define STR_RES_YAMAN 326  // yaman
#define STR_RES_KAFI 327  // kafi
#define STR_RES_BHIMPA 328  // bhimpa
#define STR_RES_DARBAR 329  // darbar
#define STR_RES_BAGESH 330  // bagesh
#define STR_RES_RAGESH 331  // ragesh
#define STR_RES_KHAMAJ 332  // khamaj
#define STR_RES_MIMAL 333  // mi'mal
#define STR_RES_PARAME 334  // parame
#define STR_RES_RANGES 335  // ranges
#define STR_RES_GANGES 336  // ganges
#define STR_RES_KAMESH 337  // kamesh
#define STR_RES_PALAS_ 338  // palas 
#define STR_RES_NATBHA 339  // natbha
#define STR_RES_M_KAUN 340  // m.kaun
#define STR_RES_BAIRAG 341  // bairag
#define STR_RES_B_TODI 342  // b.todi
#define STR_RES_CHANDR 343  // chandr
#define STR_RES_KAUSHI 344  // kaushi
#define STR_RES_JOGESH 345  // jogesh
#define STR_RES_RASIA 346  // rasia
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
