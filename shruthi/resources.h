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

extern const prog_char* const string_table[];

extern const prog_uint16_t* const lookup_table_table[];

extern const prog_uint32_t* const lookup_table32_table[];

extern const prog_uint8_t* const waveform_table[];

extern const prog_uint8_t* const character_table[];

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
extern const prog_uint16_t lut_res_groove_swing[] PROGMEM;
extern const prog_uint16_t lut_res_groove_shuffle[] PROGMEM;
extern const prog_uint16_t lut_res_groove_push[] PROGMEM;
extern const prog_uint16_t lut_res_groove_lag[] PROGMEM;
extern const prog_uint16_t lut_res_groove_human[] PROGMEM;
extern const prog_uint16_t lut_res_groove_monkey[] PROGMEM;
extern const prog_uint32_t lut_res_tempo_phase_increment[] PROGMEM;
extern const prog_uint8_t wav_res_formant_sine[] PROGMEM;
extern const prog_uint8_t wav_res_formant_square[] PROGMEM;
extern const prog_uint8_t wav_res_sine[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_square_0[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_square_1[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_square_2[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_square_3[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_square_4[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_square_5[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_saw_0[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_saw_1[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_saw_2[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_saw_3[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_saw_4[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_saw_5[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_triangle_0[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_triangle_3[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_triangle_4[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_triangle_5[] PROGMEM;
extern const prog_uint8_t wav_res_vowel_data[] PROGMEM;
extern const prog_uint8_t wav_res_distortion[] PROGMEM;
extern const prog_uint8_t wav_res_env_expo[] PROGMEM;
extern const prog_uint8_t wav_res_ssm2164_linearization[] PROGMEM;
extern const prog_uint8_t wav_res_waves[] PROGMEM;
extern const prog_uint8_t wav_res_wavetables[] PROGMEM;
extern const prog_uint8_t wav_res_version[] PROGMEM;
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
#define STR_RES_OVERDRIVE 29  // overdrive
#define STR_RES__FM 30  // fm
#define STR_RES_FLAVOUR 31  // flavour
#define STR_RES_TIME 32  // time
#define STR_RES_LEVEL 33  // level
#define STR_RES_FDB 34  // fdb
#define STR_RES_FEEDBACK 35  // feedback
#define STR_RES_EQ_ 36  // eq.
#define STR_RES_FDBCK_EQ_ 37  // fdbck eq.
#define STR_RES_TEMPO 38  // tempo
#define STR_RES_BPM 39  // bpm
#define STR_RES_GROOVE 40  // groove
#define STR_RES_DIRECTION 41  // direction
#define STR_RES_PATTERN 42  // pattern
#define STR_RES_DIVISION 43  // division
#define STR_RES_START 44  // start
#define STR_RES_LENGTH 45  // length
#define STR_RES_OCTAVE 46  // octave
#define STR_RES_RAGA 47  // raga
#define STR_RES_PORTA 48  // porta
#define STR_RES_PRT 49  // prt
#define STR_RES_LEGATO 50  // legato
#define STR_RES_TUNING 51  // tuning
#define STR_RES_MIDI_CHAN 52  // midi chan
#define STR_RES_CHN 53  // chn
#define STR_RES_MIDI_OUT 54  // midi out
#define STR_RES_PAUSE 55  // pause
#define STR_RES_STARTPAGE 56  // startpage
#define STR_RES_SNAP 57  // snap
#define STR_RES_PROGRAMMER 58  // programmer
#define STR_RES_OSCILLATOR_1 59  // oscillator 1
#define STR_RES_OSCILLATOR_2 60  // oscillator 2
#define STR_RES_MIXER 61  // mixer
#define STR_RES_FILTER 62  // filter
#define STR_RES_FILTERS 63  // filter+
#define STR_RES_MODE_1 64  // mode 1
#define STR_RES_MODE_2 65  // mode 2
#define STR_RES_MD1 66  // md1
#define STR_RES_MD2 67  // md2
#define STR_RES_ENVELOPE_1 68  // envelope 1
#define STR_RES_ENVELOPE_2 69  // envelope 2
#define STR_RES_SEQUENCER 70  // sequencer
#define STR_RES_ARPEGGIO 71  // arpeggio
#define STR_RES_CH1 72  // ch1
#define STR_RES_CH2 73  // ch2
#define STR_RES_11 74  // 1
#define STR_RES_12 75  // 2
#define STR_RES_STEP_SEQUENCER 76  // step sequencer
#define STR_RES_KEYBOARD 77  // keyboard
#define STR_RES_MIDI 78  // midi
#define STR_RES_SYSTEM 79  // system
#define STR_RES_PERFORMANCE 80  // performance
#define STR_RES_PARAM__1 81  // param. 1
#define STR_RES_PARAM__2 82  // param. 2
#define STR_RES_PR1 83  // pr1
#define STR_RES_PR2 84  // pr2
#define STR_RES_FX_ 85  // fx.
#define STR_RES_FX_PROG_ 86  // fx prog.
#define STR_RES_LPF 87  // lpf
#define STR_RES_BPF 88  // bpf
#define STR_RES_HPF 89  // hpf
#define STR_RES_LPL 90  // lp<
#define STR_RES_BPL 91  // bp<
#define STR_RES_HPL 92  // hp<
#define STR_RES_SLP 93  // +lp
#define STR_RES_SBP 94  // +bp
#define STR_RES_SHP 95  // +hp
#define STR_RES_GLP 96  // >lp
#define STR_RES_GBP 97  // >bp
#define STR_RES_GHP 98  // >hp
#define STR_RES_LP4 99  // lp4
#define STR_RES_LP3 100  // lp3
#define STR_RES_LP2 101  // lp2
#define STR_RES_LP1 102  // lp1
#define STR_RES_HP1 103  // hp1
#define STR_RES_HP2 104  // hp2
#define STR_RES_HP3 105  // hp3
#define STR_RES_BP2 106  // bp2
#define STR_RES_BP4 107  // bp4
#define STR_RES_NOTCH 108  // notch
#define STR_RES_PHASER 109  // phaser
#define STR_RES_H2LP 110  // h2lp
#define STR_RES_H3LP 111  // h3lp
#define STR_RES_NSLP 112  // n+lp
#define STR_RES_PSLP 113  // p+lp
#define STR_RES_LIQUID 114  // liquid
#define STR_RES_MS 115  // ms
#define STR_RES_WOBBLY 116  // wobbly
#define STR_RES_WHACKY 117  // whacky
#define STR_RES_PW1 118  // pw1
#define STR_RES_PW2 119  // pw2
#define STR_RES_51 120  // 1
#define STR_RES_52 121  // 2
#define STR_RES_5 122  // 
#define STR_RES_5F 123  // f
#define STR_RES_MIX 124  // mix
#define STR_RES_NOI 125  // noi
#define STR_RES_SUB 126  // sub
#define STR_RES_CUT 127  // cut
#define STR_RES_RES 128  // res
#define STR_RES_VCA 129  // vca
#define STR_RES_CV1 130  // cv1
#define STR_RES_CV2 131  // cv2
#define STR_RES_TR1 132  // tr1
#define STR_RES_A1 133  // a1
#define STR_RES_D1 134  // d1
#define STR_RES_S1 135  // s1
#define STR_RES_R1 136  // r1
#define STR_RES_TR2 137  // tr2
#define STR_RES_A2 138  // a2
#define STR_RES_D2 139  // d2
#define STR_RES_S2 140  // s2
#define STR_RES_R2 141  // r2
#define STR_RES__ATK 142  // atk
#define STR_RES__LF1 143  // lf1
#define STR_RES__LF2 144  // lf2
#define STR_RES_IN1 145  // in1
#define STR_RES_IN2 146  // in2
#define STR_RES_OUT 147  // out
#define STR_RES___OFF 148  // off
#define STR_RES_ADD 149  // add
#define STR_RES_PRD 150  // prd
#define STR_RES_MAX 151  // max
#define STR_RES_MIN 152  // min
#define STR_RES__XOR 153  // xor
#define STR_RES_GE 154  // >=
#define STR_RES_LE 155  // <=
#define STR_RES_QTZ 156  // qtz
#define STR_RES_LAG 157  // lag
#define STR_RES_PWM1 158  // pwm1
#define STR_RES_PWM2 159  // pwm2
#define STR_RES_OSC1 160  // osc1
#define STR_RES_OSC2 161  // osc2
#define STR_RES_OSC1S2 162  // osc1+2
#define STR_RES_FINE 163  // fine
#define STR_RES__MIX 164  // mix
#define STR_RES_NOISE 165  // noise
#define STR_RES_SUBOSC 166  // subosc
#define STR_RES_CUTOFF 167  // cutoff
#define STR_RES_RESO 168  // reso
#define STR_RES__VCA 169  // vca
#define STR_RES_CV_1 170  // cv 1
#define STR_RES_CV_2 171  // cv 2
#define STR_RES_TRG_E1 172  // trg e1
#define STR_RES_ATK__1 173  // atk. 1
#define STR_RES_DEC__1 174  // dec. 1
#define STR_RES_SUS__1 175  // sus. 1
#define STR_RES_REL__1 176  // rel. 1
#define STR_RES_TRG_E2 177  // trg e2
#define STR_RES_ATK__2 178  // atk. 2
#define STR_RES_DEC__2 179  // dec. 2
#define STR_RES_SUS__2 180  // sus. 2
#define STR_RES_REL__2 181  // rel. 2
#define STR_RES_ATK1S2 182  // atk1+2
#define STR_RES__LFO_1 183  // lfo 1
#define STR_RES__LFO_2 184  // lfo 2
#define STR_RES_DISTRT 185  // distrt
#define STR_RES_CRUSHR 186  // crushr
#define STR_RES_SCMBFL 187  // +cmbfl
#define STR_RES_CMBFL 188  // -cmbfl
#define STR_RES_RINGMD 189  // ringmd
#define STR_RES_DELAY 190  // delay
#define STR_RES_FB_DLY 191  // fb dly
#define STR_RES_DUBDLY 192  // dubdly
#define STR_RES__FBDLY 193  // !fbdly
#define STR_RES__DBDLY 194  // !dbdly
#define STR_RES__16_DL 195  // /16 dl
#define STR_RES__12_DL 196  // /12 dl
#define STR_RES__8_DLY 197  // /8 dly
#define STR_RES_3_16DL 198  // 3/16dl
#define STR_RES_LOOPER 199  // looper
#define STR_RES_PITCH 200  // pitch
#define STR_RES_LGF 201  // l>f
#define STR_RES_HGF 202  // h>f
#define STR_RES_FGL 203  // f>l
#define STR_RES_FGH 204  // f>h
#define STR_RES_GFX 205  // >fx
#define STR_RES_LF1 206  // lf1
#define STR_RES_LF2 207  // lf2
#define STR_RES_SEQ 208  // seq
#define STR_RES__SQ1 209  // sq1
#define STR_RES__SQ2 210  // sq2
#define STR_RES_ARP 211  // arp
#define STR_RES_WHL 212  // whl
#define STR_RES_AFT 213  // aft
#define STR_RES_BND 214  // bnd
#define STR_RES_OFS 215  // ofs
#define STR_RES__CV1 216  // cv1
#define STR_RES__CV2 217  // cv2
#define STR_RES_CV3 218  // cv3
#define STR_RES_CV4 219  // cv4
#define STR_RES_CCA 220  // ccA
#define STR_RES_CCB 221  // ccB
#define STR_RES_CCC 222  // ccC
#define STR_RES_CCD 223  // ccD
#define STR_RES__NOI 224  // noi
#define STR_RES_EN1 225  // en1
#define STR_RES_EN2 226  // en2
#define STR_RES_VEL 227  // vel
#define STR_RES_RND 228  // rnd
#define STR_RES_NOT 229  // not
#define STR_RES_GAT 230  // gat
#define STR_RES_AUD 231  // aud
#define STR_RES_OP1 232  // op1
#define STR_RES_OP2 233  // op2
#define STR_RES_E4 234  // =4
#define STR_RES_E8 235  // =8
#define STR_RES_E16 236  // =16
#define STR_RES_E32 237  // =32
#define STR_RES_LFO_1 238  // lfo 1
#define STR_RES_LFO_2 239  // lfo 2
#define STR_RES_STPSEQ 240  // stpseq
#define STR_RES_STPSQ1 241  // stpsq1
#define STR_RES_STPSQ2 242  // stpsq2
#define STR_RES__ARP 243  // arp
#define STR_RES_MWHEEL 244  // mwheel
#define STR_RES_AFTTCH 245  // afttch
#define STR_RES_BENDER 246  // bender
#define STR_RES_OFFSET 247  // offset
#define STR_RES__CV_1 248  // cv 1
#define STR_RES__CV_2 249  // cv 2
#define STR_RES_CV_3 250  // cv 3
#define STR_RES_CV_4 251  // cv 4
#define STR_RES_CC_A 252  // cc A
#define STR_RES_CC_B 253  // cc B
#define STR_RES_CC_C 254  // cc C
#define STR_RES_CC_D 255  // cc D
#define STR_RES__NOISE 256  // noise
#define STR_RES_ENV_1 257  // env 1
#define STR_RES_ENV_2 258  // env 2
#define STR_RES_VELO 259  // velo
#define STR_RES_RANDOM 260  // random
#define STR_RES_NOTE 261  // note
#define STR_RES_GATE 262  // gate
#define STR_RES_AUDIO 263  // audio
#define STR_RES_OP__1 264  // op. 1
#define STR_RES_OP__2 265  // op. 2
#define STR_RES_E_4 266  // = 4
#define STR_RES_E_8 267  // = 8
#define STR_RES_E_16 268  // = 16
#define STR_RES_E_32 269  // = 32
#define STR_RES_PATCH 270  // patch
#define STR_RES_SEQUENCE 271  // sequence
#define STR_RES_SAVE_MIDI_KBD 272  // save midi/kbd
#define STR_RES_SETTINGS_ 273  // settings?
#define STR_RES_START_FULL_MIDI 274  // start full midi
#define STR_RES_BACKUP_ 275  // backup?
#define STR_RES_BROWSE 276  // browse
#define STR_RES_SAVE 277  // save
#define STR_RES_COMPARE 278  // compare
#define STR_RES_ 279  // ----
#define STR_RES_V 280  // v
#define STR_RES_MUTABLE____V1_00 281  // mutable    v1.00
#define STR_RES_INSTRUMENTS_671 282  // instruments -1
#define STR_RES_LETS_JAM_ 283  // let's jam!
#define STR_RES_EXTERN 284  // extern
#define STR_RES_SUM 285  // sum
#define STR_RES_SYNC 286  // sync
#define STR_RES_RING 287  // ring
#define STR_RES_XOR 288  // xor
#define STR_RES_FUZZ 289  // fuzz
#define STR_RES_GG4 290  // >>4
#define STR_RES_GG8 291  // >>8
#define STR_RES_FOLD 292  // fold
#define STR_RES_BITS 293  // bits
#define STR_RES_DUO 294  // duo
#define STR_RES_2STEPS 295  // 2steps
#define STR_RES_4STEPS 296  // 4steps
#define STR_RES_8STEPS 297  // 8steps
#define STR_RES_SEQMIX 298  // seqmix
#define STR_RES_STP 299  // stp
#define STR_RES___ARP 300  // arp
#define STR_RES__SEQ 301  // seq
#define STR_RES_FREE 302  // free
#define STR_RES_SLAVE 303  // slave
#define STR_RES_MASTER 304  // master
#define STR_RES_1SHOT 305  // 1shot
#define STR_RES_1_1 306  // 1/1
#define STR_RES_1_2 307  // 1/2
#define STR_RES_1_3 308  // 1/3
#define STR_RES_1_4 309  // 1/4
#define STR_RES_1_6 310  // 1/6
#define STR_RES_1_8 311  // 1/8
#define STR_RES__12 312  // /12
#define STR_RES__16 313  // /16
#define STR_RES__24 314  // /24
#define STR_RES__32 315  // /32
#define STR_RES__48 316  // /48
#define STR_RES__96 317  // /96
#define STR_RES_SWING 318  // swing
#define STR_RES_SHUFFLE 319  // shuffle
#define STR_RES_PUSH 320  // push
#define STR_RES__LAG 321  // lag
#define STR_RES_HUMAN 322  // human
#define STR_RES_MONKEY 323  // monkey
#define STR_RES__OFF 324  // off
#define STR_RES_THRU 325  // thru
#define STR_RES___SEQ 326  // seq
#define STR_RES_CTRL 327  // ctrl
#define STR_RES_FULL 328  // full
#define STR_RES_1TV 329  // 1~|
#define STR_RES_2T1 330  // 2~1
#define STR_RES_3T2 331  // 3~2
#define STR_RES_4T3 332  // 4~3
#define STR_RES_5T4 333  // 5~4
#define STR_RES_6T5 334  // 6~5
#define STR_RES_7T6 335  // 7~6
#define STR_RES_8T7 336  // 8~7
#define STR_RES_TRI 337  // tri
#define STR_RES_SQR 338  // sqr
#define STR_RES_S_H 339  // s&h
#define STR_RES_RAMP 340  // ramp
#define STR_RES_STEP 341  // step
#define STR_RES_3 342  // 
#define STR_RES_4 343  // 
#define STR_RES_34 344  // 
#define STR_RES__ 345  // ?
#define STR_RES_PLAYED 346  // played
#define STR_RES_OFF 347  // off
#define STR_RES_ON 348  // on
#define STR_RES_SQ1 349  // sq1
#define STR_RES__TR1 350  // tr1
#define STR_RES_PL1 351  // pl1
#define STR_RES_SQ2 352  // sq2
#define STR_RES__TR2 353  // tr2
#define STR_RES_PL2 354  // pl2
#define STR_RES_CLICK 355  // click
#define STR_RES_GLITCH 356  // glitch
#define STR_RES_BLOW 357  // blow
#define STR_RES_METAL 358  // metal
#define STR_RES_POP 359  // pop
#define STR_RES_NONE 360  // none
#define STR_RES_SAW 361  // saw
#define STR_RES_SQUARE 362  // square
#define STR_RES_TRIANG 363  // triang
#define STR_RES_ZSAW 364  // zsaw
#define STR_RES_ZRESO 365  // zreso
#define STR_RES_ZTRI 366  // ztri
#define STR_RES_ZPULSE 367  // zpulse
#define STR_RES_ZSYNC 368  // zsync
#define STR_RES_PAD 369  // pad
#define STR_RES_FM 370  // fm
#define STR_RES_WAVES 371  // waves
#define STR_RES_TAMPUR 372  // tampur
#define STR_RES_DIGITL 373  // digitl
#define STR_RES_METALL 374  // metall
#define STR_RES_BOWED 375  // bowed
#define STR_RES_SLAP 376  // slap
#define STR_RES_ORGAN 377  // organ
#define STR_RES_MALE 378  // male
#define STR_RES_USER 379  // user
#define STR_RES_8BITS 380  // 8bits
#define STR_RES_CRUSH 381  // crush
#define STR_RES_PWM 382  // pwm
#define STR_RES___NOISE 383  // noise
#define STR_RES_VOWEL 384  // vowel
#define STR_RES_BELISH 385  // belish
#define STR_RES_POLATD 386  // polatd
#define STR_RES_CELLO 387  // cello
#define STR_RES_CLPSWP 388  // clpswp
#define STR_RES_FEMALE 389  // female
#define STR_RES_FMTVOC 390  // fmtvoc
#define STR_RES_FRMNT2 391  // frmnt2
#define STR_RES_RES3HP 392  // res3hp
#define STR_RES_ELECTP 393  // electp
#define STR_RES_VIBES 394  // vibes
#define STR_RES__LPF 395  // lpf
#define STR_RES_SSM 396  // ssm
#define STR_RES_SVF 397  // svf
#define STR_RES_DSP 398  // dsp
#define STR_RES_PVK 399  // pvk
#define STR_RES_4PM 400  // 4pm
#define STR_RES_DLY 401  // dly
#define STR_RES_SPLASH 402  // splash
#define STR_RES__FILTER 403  // filter
#define STR_RES_PRESET 404  // preset
#define STR_RES____OFF 405  // off
#define STR_RES_FCD 406  // fcd
#define STR_RES_XT 407  // xt
#define STR_RES_EQUAL 408  // equal
#define STR_RES_JUST 409  // just
#define STR_RES_PYTHAG 410  // pythag
#define STR_RES_1_4_EB 411  // 1/4 eb
#define STR_RES_1_4_E 412  // 1/4 e
#define STR_RES_1_4_EA 413  // 1/4 ea
#define STR_RES_BHAIRA 414  // bhaira
#define STR_RES_GUNAKR 415  // gunakr
#define STR_RES_MARWA 416  // marwa
#define STR_RES_SHREE 417  // shree
#define STR_RES_PURVI 418  // purvi
#define STR_RES_BILAWA 419  // bilawa
#define STR_RES_YAMAN 420  // yaman
#define STR_RES_KAFI 421  // kafi
#define STR_RES_BHIMPA 422  // bhimpa
#define STR_RES_DARBAR 423  // darbar
#define STR_RES_BAGESH 424  // bagesh
#define STR_RES_RAGESH 425  // ragesh
#define STR_RES_KHAMAJ 426  // khamaj
#define STR_RES_MIMAL 427  // mi'mal
#define STR_RES_PARAME 428  // parame
#define STR_RES_RANGES 429  // ranges
#define STR_RES_GANGES 430  // ganges
#define STR_RES_KAMESH 431  // kamesh
#define STR_RES_PALAS_ 432  // palas
#define STR_RES_NATBHA 433  // natbha
#define STR_RES_M_KAUN 434  // m.kaun
#define STR_RES_BAIRAG 435  // bairag
#define STR_RES_B_TODI 436  // b.todi
#define STR_RES_CHANDR 437  // chandr
#define STR_RES_KAUSHI 438  // kaushi
#define STR_RES_JOGESH 439  // jogesh
#define STR_RES_RASIA 440  // rasia
#define LUT_RES_LFO_INCREMENTS 0
#define LUT_RES_LFO_INCREMENTS_SIZE 128
#define LUT_RES_ENV_PORTAMENTO_INCREMENTS 1
#define LUT_RES_ENV_PORTAMENTO_INCREMENTS_SIZE 128
#define LUT_RES_OSCILLATOR_INCREMENTS 2
#define LUT_RES_OSCILLATOR_INCREMENTS_SIZE 97
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
#define LUT_RES_GROOVE_SWING 37
#define LUT_RES_GROOVE_SWING_SIZE 16
#define LUT_RES_GROOVE_SHUFFLE 38
#define LUT_RES_GROOVE_SHUFFLE_SIZE 16
#define LUT_RES_GROOVE_PUSH 39
#define LUT_RES_GROOVE_PUSH_SIZE 16
#define LUT_RES_GROOVE_LAG 40
#define LUT_RES_GROOVE_LAG_SIZE 16
#define LUT_RES_GROOVE_HUMAN 41
#define LUT_RES_GROOVE_HUMAN_SIZE 16
#define LUT_RES_GROOVE_MONKEY 42
#define LUT_RES_GROOVE_MONKEY_SIZE 16
#define LUT_RES_TEMPO_PHASE_INCREMENT 0
#define LUT_RES_TEMPO_PHASE_INCREMENT_SIZE 201
#define WAV_RES_FORMANT_SINE 0
#define WAV_RES_FORMANT_SINE_SIZE 256
#define WAV_RES_FORMANT_SQUARE 1
#define WAV_RES_FORMANT_SQUARE_SIZE 256
#define WAV_RES_SINE 2
#define WAV_RES_SINE_SIZE 257
#define WAV_RES_BANDLIMITED_SQUARE_0 3
#define WAV_RES_BANDLIMITED_SQUARE_0_SIZE 257
#define WAV_RES_BANDLIMITED_SQUARE_1 4
#define WAV_RES_BANDLIMITED_SQUARE_1_SIZE 257
#define WAV_RES_BANDLIMITED_SQUARE_2 5
#define WAV_RES_BANDLIMITED_SQUARE_2_SIZE 257
#define WAV_RES_BANDLIMITED_SQUARE_3 6
#define WAV_RES_BANDLIMITED_SQUARE_3_SIZE 257
#define WAV_RES_BANDLIMITED_SQUARE_4 7
#define WAV_RES_BANDLIMITED_SQUARE_4_SIZE 257
#define WAV_RES_BANDLIMITED_SQUARE_5 8
#define WAV_RES_BANDLIMITED_SQUARE_5_SIZE 257
#define WAV_RES_BANDLIMITED_SQUARE_6 9
#define WAV_RES_BANDLIMITED_SQUARE_6_SIZE 257
#define WAV_RES_BANDLIMITED_SAW_0 10
#define WAV_RES_BANDLIMITED_SAW_0_SIZE 257
#define WAV_RES_BANDLIMITED_SAW_1 11
#define WAV_RES_BANDLIMITED_SAW_1_SIZE 257
#define WAV_RES_BANDLIMITED_SAW_2 12
#define WAV_RES_BANDLIMITED_SAW_2_SIZE 257
#define WAV_RES_BANDLIMITED_SAW_3 13
#define WAV_RES_BANDLIMITED_SAW_3_SIZE 257
#define WAV_RES_BANDLIMITED_SAW_4 14
#define WAV_RES_BANDLIMITED_SAW_4_SIZE 257
#define WAV_RES_BANDLIMITED_SAW_5 15
#define WAV_RES_BANDLIMITED_SAW_5_SIZE 257
#define WAV_RES_BANDLIMITED_SAW_6 16
#define WAV_RES_BANDLIMITED_SAW_6_SIZE 257
#define WAV_RES_BANDLIMITED_TRIANGLE_0 17
#define WAV_RES_BANDLIMITED_TRIANGLE_0_SIZE 257
#define WAV_RES__BANDLIMITED_TRIANGLE_0 18
#define WAV_RES__BANDLIMITED_TRIANGLE_0_SIZE 257
#define WAV_RES___BANDLIMITED_TRIANGLE_0 19
#define WAV_RES___BANDLIMITED_TRIANGLE_0_SIZE 257
#define WAV_RES_BANDLIMITED_TRIANGLE_3 20
#define WAV_RES_BANDLIMITED_TRIANGLE_3_SIZE 257
#define WAV_RES_BANDLIMITED_TRIANGLE_4 21
#define WAV_RES_BANDLIMITED_TRIANGLE_4_SIZE 257
#define WAV_RES_BANDLIMITED_TRIANGLE_5 22
#define WAV_RES_BANDLIMITED_TRIANGLE_5_SIZE 257
#define WAV_RES_BANDLIMITED_TRIANGLE_6 23
#define WAV_RES_BANDLIMITED_TRIANGLE_6_SIZE 257
#define WAV_RES_VOWEL_DATA 24
#define WAV_RES_VOWEL_DATA_SIZE 63
#define WAV_RES_DISTORTION 25
#define WAV_RES_DISTORTION_SIZE 256
#define WAV_RES_ENV_EXPO 26
#define WAV_RES_ENV_EXPO_SIZE 257
#define WAV_RES_SSM2164_LINEARIZATION 27
#define WAV_RES_SSM2164_LINEARIZATION_SIZE 64
#define WAV_RES_WAVES 28
#define WAV_RES_WAVES_SIZE 16383
#define WAV_RES_WAVETABLES 29
#define WAV_RES_WAVETABLES_SIZE 324
#define WAV_RES_VERSION 30
#define WAV_RES_VERSION_SIZE 2
#define CHR_RES_SPECIAL_CHARACTERS 0
#define CHR_RES_SPECIAL_CHARACTERS_SIZE 56
typedef avrlib::ResourcesManager<
    ResourceId,
    avrlib::ResourcesTables<
        string_table,
        lookup_table_table> > ResourcesManager;

}  // namespace shruthi

#endif  // SHRUTHI_RESOURCES_H_
