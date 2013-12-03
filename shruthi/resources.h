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
#define STR_RES_OSCILLATOR_1 58  // oscillator 1
#define STR_RES_OSCILLATOR_2 59  // oscillator 2
#define STR_RES_MIXER 60  // mixer
#define STR_RES_FILTER 61  // filter
#define STR_RES_FILTERS 62  // filter+
#define STR_RES_MODE_1 63  // mode 1
#define STR_RES_MODE_2 64  // mode 2
#define STR_RES_MD1 65  // md1
#define STR_RES_MD2 66  // md2
#define STR_RES_ENVELOPE_1 67  // envelope 1
#define STR_RES_ENVELOPE_2 68  // envelope 2
#define STR_RES_SEQUENCER 69  // sequencer
#define STR_RES_ARPEGGIO 70  // arpeggio
#define STR_RES_CH1 71  // ch1
#define STR_RES_CH2 72  // ch2
#define STR_RES_11 73  // 1
#define STR_RES_12 74  // 2
#define STR_RES_STEP_SEQUENCER 75  // step sequencer
#define STR_RES_KEYBOARD 76  // keyboard
#define STR_RES_MIDI 77  // midi
#define STR_RES_SYSTEM 78  // system
#define STR_RES_PERFORMANCE 79  // performance
#define STR_RES_PARAM__1 80  // param. 1
#define STR_RES_PARAM__2 81  // param. 2
#define STR_RES_PR1 82  // pr1
#define STR_RES_PR2 83  // pr2
#define STR_RES_FX_ 84  // fx.
#define STR_RES_FX_PROG_ 85  // fx prog.
#define STR_RES_LPF 86  // lpf
#define STR_RES_BPF 87  // bpf
#define STR_RES_HPF 88  // hpf
#define STR_RES_LPL 89  // lp<
#define STR_RES_BPL 90  // bp<
#define STR_RES_HPL 91  // hp<
#define STR_RES_SLP 92  // +lp
#define STR_RES_SBP 93  // +bp
#define STR_RES_SHP 94  // +hp
#define STR_RES_GLP 95  // >lp
#define STR_RES_GBP 96  // >bp
#define STR_RES_GHP 97  // >hp
#define STR_RES_LP4 98  // lp4
#define STR_RES_LP3 99  // lp3
#define STR_RES_LP2 100  // lp2
#define STR_RES_LP1 101  // lp1
#define STR_RES_HP1 102  // hp1
#define STR_RES_HP2 103  // hp2
#define STR_RES_HP3 104  // hp3
#define STR_RES_BP2 105  // bp2
#define STR_RES_BP4 106  // bp4
#define STR_RES_NOTCH 107  // notch
#define STR_RES_PHASER 108  // phaser
#define STR_RES_H2LP 109  // h2lp
#define STR_RES_H3LP 110  // h3lp
#define STR_RES_NSLP 111  // n+lp
#define STR_RES_PSLP 112  // p+lp
#define STR_RES_LIQUID 113  // liquid
#define STR_RES_MS 114  // ms
#define STR_RES_WOBBLY 115  // wobbly
#define STR_RES_WHACKY 116  // whacky
#define STR_RES_PW1 117  // pw1
#define STR_RES_PW2 118  // pw2
#define STR_RES_51 119  // 1
#define STR_RES_52 120  // 2
#define STR_RES_5 121  // 
#define STR_RES_5F 122  // f
#define STR_RES_MIX 123  // mix
#define STR_RES_NOI 124  // noi
#define STR_RES_SUB 125  // sub
#define STR_RES_CUT 126  // cut
#define STR_RES_RES 127  // res
#define STR_RES_VCA 128  // vca
#define STR_RES_CV1 129  // cv1
#define STR_RES_CV2 130  // cv2
#define STR_RES_TR1 131  // tr1
#define STR_RES_A1 132  // a1
#define STR_RES_D1 133  // d1
#define STR_RES_S1 134  // s1
#define STR_RES_R1 135  // r1
#define STR_RES_TR2 136  // tr2
#define STR_RES_A2 137  // a2
#define STR_RES_D2 138  // d2
#define STR_RES_S2 139  // s2
#define STR_RES_R2 140  // r2
#define STR_RES__ATK 141  // atk
#define STR_RES__LF1 142  // lf1
#define STR_RES__LF2 143  // lf2
#define STR_RES_IN1 144  // in1
#define STR_RES_IN2 145  // in2
#define STR_RES_OUT 146  // out
#define STR_RES___OFF 147  // off
#define STR_RES_ADD 148  // add
#define STR_RES_PRD 149  // prd
#define STR_RES_MAX 150  // max
#define STR_RES_MIN 151  // min
#define STR_RES__XOR 152  // xor
#define STR_RES_GE 153  // >=
#define STR_RES_LE 154  // <=
#define STR_RES_QTZ 155  // qtz
#define STR_RES_LAG 156  // lag
#define STR_RES_PWM1 157  // pwm1
#define STR_RES_PWM2 158  // pwm2
#define STR_RES_OSC1 159  // osc1
#define STR_RES_OSC2 160  // osc2
#define STR_RES_OSC1S2 161  // osc1+2
#define STR_RES_FINE 162  // fine
#define STR_RES__MIX 163  // mix
#define STR_RES_NOISE 164  // noise
#define STR_RES_SUBOSC 165  // subosc
#define STR_RES_CUTOFF 166  // cutoff
#define STR_RES_RESO 167  // reso
#define STR_RES__VCA 168  // vca
#define STR_RES_CV_1 169  // cv 1
#define STR_RES_CV_2 170  // cv 2
#define STR_RES_TRG_E1 171  // trg e1
#define STR_RES_ATK__1 172  // atk. 1
#define STR_RES_DEC__1 173  // dec. 1
#define STR_RES_SUS__1 174  // sus. 1
#define STR_RES_REL__1 175  // rel. 1
#define STR_RES_TRG_E2 176  // trg e2
#define STR_RES_ATK__2 177  // atk. 2
#define STR_RES_DEC__2 178  // dec. 2
#define STR_RES_SUS__2 179  // sus. 2
#define STR_RES_REL__2 180  // rel. 2
#define STR_RES_ATK1S2 181  // atk1+2
#define STR_RES__LFO_1 182  // lfo 1
#define STR_RES__LFO_2 183  // lfo 2
#define STR_RES_DISTRT 184  // distrt
#define STR_RES_CRUSHR 185  // crushr
#define STR_RES_SCMBFL 186  // +cmbfl
#define STR_RES_CMBFL 187  // -cmbfl
#define STR_RES_RINGMD 188  // ringmd
#define STR_RES_DELAY 189  // delay
#define STR_RES_FB_DLY 190  // fb dly
#define STR_RES_DUBDLY 191  // dubdly
#define STR_RES__FBDLY 192  // !fbdly
#define STR_RES__DBDLY 193  // !dbdly
#define STR_RES__16_DL 194  // /16 dl
#define STR_RES__12_DL 195  // /12 dl
#define STR_RES__8_DLY 196  // /8 dly
#define STR_RES_3_16DL 197  // 3/16dl
#define STR_RES_LOOPER 198  // looper
#define STR_RES_PITCH 199  // pitch
#define STR_RES_LGF 200  // l>f
#define STR_RES_HGF 201  // h>f
#define STR_RES_FGL 202  // f>l
#define STR_RES_FGH 203  // f>h
#define STR_RES_GFX 204  // >fx
#define STR_RES_LF1 205  // lf1
#define STR_RES_LF2 206  // lf2
#define STR_RES_SEQ 207  // seq
#define STR_RES__SQ1 208  // sq1
#define STR_RES__SQ2 209  // sq2
#define STR_RES_ARP 210  // arp
#define STR_RES_WHL 211  // whl
#define STR_RES_AFT 212  // aft
#define STR_RES_BND 213  // bnd
#define STR_RES_OFS 214  // ofs
#define STR_RES__CV1 215  // cv1
#define STR_RES__CV2 216  // cv2
#define STR_RES_CV3 217  // cv3
#define STR_RES_CV4 218  // cv4
#define STR_RES_CCA 219  // ccA
#define STR_RES_CCB 220  // ccB
#define STR_RES_CCC 221  // ccC
#define STR_RES_CCD 222  // ccD
#define STR_RES__NOI 223  // noi
#define STR_RES_EN1 224  // en1
#define STR_RES_EN2 225  // en2
#define STR_RES_VEL 226  // vel
#define STR_RES_RND 227  // rnd
#define STR_RES_NOT 228  // not
#define STR_RES_GAT 229  // gat
#define STR_RES_AUD 230  // aud
#define STR_RES_OP1 231  // op1
#define STR_RES_OP2 232  // op2
#define STR_RES_E4 233  // =4
#define STR_RES_E8 234  // =8
#define STR_RES_E16 235  // =16
#define STR_RES_E32 236  // =32
#define STR_RES_LFO_1 237  // lfo 1
#define STR_RES_LFO_2 238  // lfo 2
#define STR_RES_STPSEQ 239  // stpseq
#define STR_RES_STPSQ1 240  // stpsq1
#define STR_RES_STPSQ2 241  // stpsq2
#define STR_RES__ARP 242  // arp
#define STR_RES_MWHEEL 243  // mwheel
#define STR_RES_AFTTCH 244  // afttch
#define STR_RES_BENDER 245  // bender
#define STR_RES_OFFSET 246  // offset
#define STR_RES__CV_1 247  // cv 1
#define STR_RES__CV_2 248  // cv 2
#define STR_RES_CV_3 249  // cv 3
#define STR_RES_CV_4 250  // cv 4
#define STR_RES_CC_A 251  // cc A
#define STR_RES_CC_B 252  // cc B
#define STR_RES_CC_C 253  // cc C
#define STR_RES_CC_D 254  // cc D
#define STR_RES__NOISE 255  // noise
#define STR_RES_ENV_1 256  // env 1
#define STR_RES_ENV_2 257  // env 2
#define STR_RES_VELO 258  // velo
#define STR_RES_RANDOM 259  // random
#define STR_RES_NOTE 260  // note
#define STR_RES_GATE 261  // gate
#define STR_RES_AUDIO 262  // audio
#define STR_RES_OP__1 263  // op. 1
#define STR_RES_OP__2 264  // op. 2
#define STR_RES_E_4 265  // = 4
#define STR_RES_E_8 266  // = 8
#define STR_RES_E_16 267  // = 16
#define STR_RES_E_32 268  // = 32
#define STR_RES_PATCH 269  // patch
#define STR_RES_SEQUENCE 270  // sequence
#define STR_RES_SAVE_MIDI_KBD 271  // save midi/kbd
#define STR_RES_SETTINGS_ 272  // settings?
#define STR_RES_START_FULL_MIDI 273  // start full midi
#define STR_RES_BACKUP_ 274  // backup?
#define STR_RES_BROWSE 275  // browse
#define STR_RES_SAVE 276  // save
#define STR_RES_COMPARE 277  // compare
#define STR_RES_ 278  // ----
#define STR_RES_V 279  // v
#define STR_RES_MUTABLE____V1_00 280  // mutable    v1.00
#define STR_RES_INSTRUMENTS_671 281  // instruments -1
#define STR_RES_SHRUTHI_CLASSIC 282  // shruthi classic
#define STR_RES_4_KNOBS 283  // (4 knobs)
#define STR_RES_SHRUTHI_XT 284  // shruthi xt
#define STR_RES_CLASSIC_FCD72 285  // classic (fcd72)
#define STR_RES__SHRUTHI_XT 286  // shruthi xt
#define STR_RES_FULL_CONTROL 287  // (full control)
#define STR_RES_LETS_JAM_ 288  // let's jam!
#define STR_RES_EXTERN 289  // extern
#define STR_RES_SUM 290  // sum
#define STR_RES_SYNC 291  // sync
#define STR_RES_RING 292  // ring
#define STR_RES_XOR 293  // xor
#define STR_RES_FUZZ 294  // fuzz
#define STR_RES_GG4 295  // >>4
#define STR_RES_GG8 296  // >>8
#define STR_RES_FOLD 297  // fold
#define STR_RES_BITS 298  // bits
#define STR_RES_DUO 299  // duo
#define STR_RES_2STEPS 300  // 2steps
#define STR_RES_4STEPS 301  // 4steps
#define STR_RES_8STEPS 302  // 8steps
#define STR_RES_SEQMIX 303  // seqmix
#define STR_RES_STP 304  // stp
#define STR_RES___ARP 305  // arp
#define STR_RES__SEQ 306  // seq
#define STR_RES_FREE 307  // free
#define STR_RES_SLAVE 308  // slave
#define STR_RES_MASTER 309  // master
#define STR_RES_1SHOT 310  // 1shot
#define STR_RES_1_1 311  // 1/1
#define STR_RES_1_2 312  // 1/2
#define STR_RES_1_3 313  // 1/3
#define STR_RES_1_4 314  // 1/4
#define STR_RES_1_6 315  // 1/6
#define STR_RES_1_8 316  // 1/8
#define STR_RES__12 317  // /12
#define STR_RES__16 318  // /16
#define STR_RES__24 319  // /24
#define STR_RES__32 320  // /32
#define STR_RES__48 321  // /48
#define STR_RES__96 322  // /96
#define STR_RES_SWING 323  // swing
#define STR_RES_SHUFFLE 324  // shuffle
#define STR_RES_PUSH 325  // push
#define STR_RES__LAG 326  // lag
#define STR_RES_HUMAN 327  // human
#define STR_RES_MONKEY 328  // monkey
#define STR_RES__OFF 329  // off
#define STR_RES_THRU 330  // thru
#define STR_RES___SEQ 331  // seq
#define STR_RES_CTRL 332  // ctrl
#define STR_RES_FULL 333  // full
#define STR_RES_1TV 334  // 1~|
#define STR_RES_2T1 335  // 2~1
#define STR_RES_3T2 336  // 3~2
#define STR_RES_4T3 337  // 4~3
#define STR_RES_5T4 338  // 5~4
#define STR_RES_6T5 339  // 6~5
#define STR_RES_7T6 340  // 7~6
#define STR_RES_8T7 341  // 8~7
#define STR_RES_TRI 342  // tri
#define STR_RES_SQR 343  // sqr
#define STR_RES_S_H 344  // s&h
#define STR_RES_RAMP 345  // ramp
#define STR_RES_STEP 346  // step
#define STR_RES_3 347  // 
#define STR_RES_4 348  // 
#define STR_RES_34 349  // 
#define STR_RES__ 350  // ?
#define STR_RES_PLAYED 351  // played
#define STR_RES_OFF 352  // off
#define STR_RES_ON 353  // on
#define STR_RES_SQ1 354  // sq1
#define STR_RES__TR1 355  // tr1
#define STR_RES_PL1 356  // pl1
#define STR_RES_SQ2 357  // sq2
#define STR_RES__TR2 358  // tr2
#define STR_RES_PL2 359  // pl2
#define STR_RES_CLICK 360  // click
#define STR_RES_GLITCH 361  // glitch
#define STR_RES_BLOW 362  // blow
#define STR_RES_METAL 363  // metal
#define STR_RES_POP 364  // pop
#define STR_RES_NONE 365  // none
#define STR_RES_SAW 366  // saw
#define STR_RES_SQUARE 367  // square
#define STR_RES_TRIANG 368  // triang
#define STR_RES_ZSAW 369  // zsaw
#define STR_RES_ZRESO 370  // zreso
#define STR_RES_ZTRI 371  // ztri
#define STR_RES_ZPULSE 372  // zpulse
#define STR_RES_ZSYNC 373  // zsync
#define STR_RES_PAD 374  // pad
#define STR_RES_FM 375  // fm
#define STR_RES_WAVES 376  // waves
#define STR_RES_TAMPUR 377  // tampur
#define STR_RES_DIGITL 378  // digitl
#define STR_RES_METALL 379  // metall
#define STR_RES_BOWED 380  // bowed
#define STR_RES_SLAP 381  // slap
#define STR_RES_ORGAN 382  // organ
#define STR_RES_MALE 383  // male
#define STR_RES_USER 384  // user
#define STR_RES_8BITS 385  // 8bits
#define STR_RES_CRUSH 386  // crush
#define STR_RES_PWM 387  // pwm
#define STR_RES___NOISE 388  // noise
#define STR_RES_VOWEL 389  // vowel
#define STR_RES_BELISH 390  // belish
#define STR_RES_POLATD 391  // polatd
#define STR_RES_CELLO 392  // cello
#define STR_RES_CLPSWP 393  // clpswp
#define STR_RES_FEMALE 394  // female
#define STR_RES_FMTVOC 395  // fmtvoc
#define STR_RES_FRMNT2 396  // frmnt2
#define STR_RES_RES3HP 397  // res3hp
#define STR_RES_ELECTP 398  // electp
#define STR_RES_VIBES 399  // vibes
#define STR_RES__LPF 400  // lpf
#define STR_RES_SSM 401  // ssm
#define STR_RES_SVF 402  // svf
#define STR_RES_DSP 403  // dsp
#define STR_RES_PVK 404  // pvk
#define STR_RES_4PM 405  // 4pm
#define STR_RES_DLY 406  // dly
#define STR_RES_SPLASH 407  // splash
#define STR_RES__FILTER 408  // filter
#define STR_RES_PRESET 409  // preset
#define STR_RES_EQUAL 410  // equal
#define STR_RES_JUST 411  // just
#define STR_RES_PYTHAG 412  // pythag
#define STR_RES_1_4_EB 413  // 1/4 eb
#define STR_RES_1_4_E 414  // 1/4 e
#define STR_RES_1_4_EA 415  // 1/4 ea
#define STR_RES_BHAIRA 416  // bhaira
#define STR_RES_GUNAKR 417  // gunakr
#define STR_RES_MARWA 418  // marwa
#define STR_RES_SHREE 419  // shree
#define STR_RES_PURVI 420  // purvi
#define STR_RES_BILAWA 421  // bilawa
#define STR_RES_YAMAN 422  // yaman
#define STR_RES_KAFI 423  // kafi
#define STR_RES_BHIMPA 424  // bhimpa
#define STR_RES_DARBAR 425  // darbar
#define STR_RES_BAGESH 426  // bagesh
#define STR_RES_RAGESH 427  // ragesh
#define STR_RES_KHAMAJ 428  // khamaj
#define STR_RES_MIMAL 429  // mi'mal
#define STR_RES_PARAME 430  // parame
#define STR_RES_RANGES 431  // ranges
#define STR_RES_GANGES 432  // ganges
#define STR_RES_KAMESH 433  // kamesh
#define STR_RES_PALAS_ 434  // palas
#define STR_RES_NATBHA 435  // natbha
#define STR_RES_M_KAUN 436  // m.kaun
#define STR_RES_BAIRAG 437  // bairag
#define STR_RES_B_TODI 438  // b.todi
#define STR_RES_CHANDR 439  // chandr
#define STR_RES_KAUSHI 440  // kaushi
#define STR_RES_JOGESH 441  // jogesh
#define STR_RES_RASIA 442  // rasia
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
