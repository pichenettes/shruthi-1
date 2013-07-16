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
extern const prog_uint8_t wav_res_expansion_krama[] PROGMEM;
extern const prog_uint8_t wav_res_expansion_jata[] PROGMEM;
extern const prog_uint8_t wav_res_expansion_sikha[] PROGMEM;
extern const prog_uint8_t wav_res_expansion_ghana[] PROGMEM;
extern const prog_uint8_t wav_res_distortion[] PROGMEM;
extern const prog_uint8_t wav_res_env_expo[] PROGMEM;
extern const prog_uint8_t wav_res_ssm2164_linearization[] PROGMEM;
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
#define STR_RES_WARP 43  // warp
#define STR_RES_WRP 44  // wrp
#define STR_RES_START 45  // start
#define STR_RES_SPLIT 46  // split
#define STR_RES_LENGTH 47  // length
#define STR_RES_OCTAVE 48  // octave
#define STR_RES_RAGA 49  // raga
#define STR_RES_PORTA 50  // porta
#define STR_RES_PRT 51  // prt
#define STR_RES_LEGATO 52  // legato
#define STR_RES_TUNING 53  // tuning
#define STR_RES_MIDI_CHAN 54  // midi chan
#define STR_RES_CHN 55  // chn
#define STR_RES_MIDI_OUT 56  // midi out
#define STR_RES_PAUSE 57  // pause
#define STR_RES_SNAP 58  // snap
#define STR_RES_PROGRAMMER 59  // programmer
#define STR_RES_OSCILLATOR_1 60  // oscillator 1
#define STR_RES_OSCILLATOR_2 61  // oscillator 2
#define STR_RES_MIXER 62  // mixer
#define STR_RES_FILTER 63  // filter
#define STR_RES_FILTERS 64  // filter+
#define STR_RES_MODE_1 65  // mode 1
#define STR_RES_MODE_2 66  // mode 2
#define STR_RES_MD1 67  // md1
#define STR_RES_MD2 68  // md2
#define STR_RES_ENVELOPE_1 69  // envelope 1
#define STR_RES_ENVELOPE_2 70  // envelope 2
#define STR_RES_SEQUENCER 71  // sequencer
#define STR_RES_ARPEGGIO 72  // arpeggio
#define STR_RES_CH1 73  // ch1
#define STR_RES_CH2 74  // ch2
#define STR_RES_11 75  // 1
#define STR_RES_12 76  // 2
#define STR_RES_STEP_SEQUENCER 77  // step sequencer
#define STR_RES_KEYBOARD 78  // keyboard
#define STR_RES_MIDI 79  // midi
#define STR_RES_SYSTEM 80  // system
#define STR_RES_PERFORMANCE 81  // performance
#define STR_RES_PARAM__1 82  // param. 1
#define STR_RES_PARAM__2 83  // param. 2
#define STR_RES_PR1 84  // pr1
#define STR_RES_PR2 85  // pr2
#define STR_RES_FX_ 86  // fx.
#define STR_RES_FX_PROG_ 87  // fx prog.
#define STR_RES_LPF 88  // lpf
#define STR_RES_BPF 89  // bpf
#define STR_RES_HPF 90  // hpf
#define STR_RES_LPL 91  // lp<
#define STR_RES_BPL 92  // bp<
#define STR_RES_HPL 93  // hp<
#define STR_RES_SLP 94  // +lp
#define STR_RES_SBP 95  // +bp
#define STR_RES_SHP 96  // +hp
#define STR_RES_GLP 97  // >lp
#define STR_RES_GBP 98  // >bp
#define STR_RES_GHP 99  // >hp
#define STR_RES_LP4 100  // lp4
#define STR_RES_LP3 101  // lp3
#define STR_RES_LP2 102  // lp2
#define STR_RES_LP1 103  // lp1
#define STR_RES_HP1 104  // hp1
#define STR_RES_HP2 105  // hp2
#define STR_RES_HP3 106  // hp3
#define STR_RES_BP2 107  // bp2
#define STR_RES_BP4 108  // bp4
#define STR_RES_NOTCH 109  // notch
#define STR_RES_PHASER 110  // phaser
#define STR_RES_H2LP 111  // h2lp
#define STR_RES_H3LP 112  // h3lp
#define STR_RES_NSLP 113  // n+lp
#define STR_RES_PSLP 114  // p+lp
#define STR_RES_LIQUID 115  // liquid
#define STR_RES_MS 116  // ms
#define STR_RES_WOBBLY 117  // wobbly
#define STR_RES_WHACKY 118  // whacky
#define STR_RES_CUT 119  // cut
#define STR_RES_VCA 120  // vca
#define STR_RES_PW1 121  // pw1
#define STR_RES_PW2 122  // pw2
#define STR_RES_51 123  // 1
#define STR_RES_52 124  // 2
#define STR_RES_5 125  // 
#define STR_RES_5F 126  // f
#define STR_RES_MIX 127  // mix
#define STR_RES_NOI 128  // noi
#define STR_RES_SUB 129  // sub
#define STR_RES_RES 130  // res
#define STR_RES_CV1 131  // cv1
#define STR_RES_CV2 132  // cv2
#define STR_RES__ATK 133  // atk
#define STR_RES__LF1 134  // lf1
#define STR_RES__LF2 135  // lf2
#define STR_RES_EN1 136  // en1
#define STR_RES_EN2 137  // en2
#define STR_RES_IN1 138  // in1
#define STR_RES_IN2 139  // in2
#define STR_RES_OUT 140  // out
#define STR_RES___OFF 141  // off
#define STR_RES_ADD 142  // add
#define STR_RES_PRD 143  // prd
#define STR_RES_MAX 144  // max
#define STR_RES_MIN 145  // min
#define STR_RES__XOR 146  // xor
#define STR_RES_GE 147  // >=
#define STR_RES_LE 148  // <=
#define STR_RES_QTZ 149  // qtz
#define STR_RES_LAG 150  // lag
#define STR_RES_CUTOFF 151  // cutoff
#define STR_RES__VCA 152  // vca
#define STR_RES_PWM1 153  // pwm1
#define STR_RES_PWM2 154  // pwm2
#define STR_RES_OSC1 155  // osc1
#define STR_RES_OSC2 156  // osc2
#define STR_RES_OSC1S2 157  // osc1+2
#define STR_RES_FINE 158  // fine
#define STR_RES__MIX 159  // mix
#define STR_RES_NOISE 160  // noise
#define STR_RES_SUBOSC 161  // subosc
#define STR_RES_RESO 162  // reso
#define STR_RES_CV_1 163  // cv 1
#define STR_RES_CV_2 164  // cv 2
#define STR_RES__ATTACK 165  // attack
#define STR_RES__LFO_1 166  // lfo 1
#define STR_RES__LFO_2 167  // lfo 2
#define STR_RES_ENV_1 168  // env 1
#define STR_RES_ENV_2 169  // env 2
#define STR_RES_DISTRT 170  // distrt
#define STR_RES_CRUSHR 171  // crushr
#define STR_RES_SCMBFL 172  // +cmbfl
#define STR_RES_CMBFL 173  // -cmbfl
#define STR_RES_RINGMD 174  // ringmd
#define STR_RES_DELAY 175  // delay
#define STR_RES_FB_DLY 176  // fb dly
#define STR_RES_DUBDLY 177  // dubdly
#define STR_RES__FBDLY 178  // !fbdly
#define STR_RES__DBDLY 179  // !dbdly
#define STR_RES__16_DL 180  // /16 dl
#define STR_RES__12_DL 181  // /12 dl
#define STR_RES__8_DLY 182  // /8 dly
#define STR_RES_3_16DL 183  // 3/16dl
#define STR_RES_LOOPER 184  // looper
#define STR_RES_PITCH 185  // pitch
#define STR_RES_LGF 186  // l>f
#define STR_RES_HGF 187  // h>f
#define STR_RES_FGL 188  // f>l
#define STR_RES_FGH 189  // f>h
#define STR_RES_GFX 190  // >fx
#define STR_RES_LF1 191  // lf1
#define STR_RES_LF2 192  // lf2
#define STR_RES_SEQ 193  // seq
#define STR_RES__SQ1 194  // sq1
#define STR_RES__SQ2 195  // sq2
#define STR_RES_ARP 196  // arp
#define STR_RES_WHL 197  // whl
#define STR_RES_AFT 198  // aft
#define STR_RES_BND 199  // bnd
#define STR_RES_OFS 200  // ofs
#define STR_RES__CV1 201  // cv1
#define STR_RES__CV2 202  // cv2
#define STR_RES_CV3 203  // cv3
#define STR_RES_CV4 204  // cv4
#define STR_RES_CCA 205  // ccA
#define STR_RES_CCB 206  // ccB
#define STR_RES_CCC 207  // ccC
#define STR_RES_CCD 208  // ccD
#define STR_RES__NOI 209  // noi
#define STR_RES__EN1 210  // en1
#define STR_RES__EN2 211  // en2
#define STR_RES_VEL 212  // vel
#define STR_RES_RND 213  // rnd
#define STR_RES_NOT 214  // not
#define STR_RES_GAT 215  // gat
#define STR_RES_AUD 216  // aud
#define STR_RES_OP1 217  // op1
#define STR_RES_OP2 218  // op2
#define STR_RES_E4 219  // =4
#define STR_RES_E8 220  // =8
#define STR_RES_E16 221  // =16
#define STR_RES_E32 222  // =32
#define STR_RES_LFO_1 223  // lfo 1
#define STR_RES_LFO_2 224  // lfo 2
#define STR_RES_STPSEQ 225  // stpseq
#define STR_RES_STPSQ1 226  // stpsq1
#define STR_RES_STPSQ2 227  // stpsq2
#define STR_RES__ARP 228  // arp
#define STR_RES_MWHEEL 229  // mwheel
#define STR_RES_AFTTCH 230  // afttch
#define STR_RES_BENDER 231  // bender
#define STR_RES_OFFSET 232  // offset
#define STR_RES__CV_1 233  // cv 1
#define STR_RES__CV_2 234  // cv 2
#define STR_RES_CV_3 235  // cv 3
#define STR_RES_CV_4 236  // cv 4
#define STR_RES_CC_A 237  // cc A
#define STR_RES_CC_B 238  // cc B
#define STR_RES_CC_C 239  // cc C
#define STR_RES_CC_D 240  // cc D
#define STR_RES__NOISE 241  // noise
#define STR_RES__ENV_1 242  // env 1
#define STR_RES__ENV_2 243  // env 2
#define STR_RES_VELO 244  // velo
#define STR_RES_RANDOM 245  // random
#define STR_RES_NOTE 246  // note
#define STR_RES_GATE 247  // gate
#define STR_RES_AUDIO 248  // audio
#define STR_RES_OP__1 249  // op. 1
#define STR_RES_OP__2 250  // op. 2
#define STR_RES_E_4 251  // = 4
#define STR_RES_E_8 252  // = 8
#define STR_RES_E_16 253  // = 16
#define STR_RES_E_32 254  // = 32
#define STR_RES_PATCH 255  // patch
#define STR_RES_SEQUENCE 256  // sequence
#define STR_RES_SAVE_MIDI_KBD 257  // save midi/kbd
#define STR_RES_SETTINGS_ 258  // settings?
#define STR_RES_START_FULL_MIDI 259  // start full midi
#define STR_RES_BACKUP_ 260  // backup?
#define STR_RES_BROWSE 261  // browse
#define STR_RES_SAVE 262  // save
#define STR_RES_COMPARE 263  // compare
#define STR_RES_ 264  // ----
#define STR_RES_V 265  // v
#define STR_RES_MUTABLE____V1_00 266  // mutable    v1.00
#define STR_RES_INSTRUMENTS_671 267  // instruments -1
#define STR_RES_EXTERN 268  // extern
#define STR_RES_X2_EXT 269  // x2 ext
#define STR_RES__2_EXT 270  // /2 ext
#define STR_RES__4_EXT 271  // /4 ext
#define STR_RES__8_EXT 272  // /8 ext
#define STR_RES_SUM 273  // sum
#define STR_RES_SYNC 274  // sync
#define STR_RES_RING 275  // ring
#define STR_RES_XOR 276  // xor
#define STR_RES_FUZZ 277  // fuzz
#define STR_RES_GG4 278  // >>4
#define STR_RES_GG8 279  // >>8
#define STR_RES_FOLD 280  // fold
#define STR_RES_BITS 281  // bits
#define STR_RES_DUO 282  // duo
#define STR_RES_2STEPS 283  // 2steps
#define STR_RES_4STEPS 284  // 4steps
#define STR_RES_8STEPS 285  // 8steps
#define STR_RES_SEQMIX 286  // seqmix
#define STR_RES_STP 287  // stp
#define STR_RES___ARP 288  // arp
#define STR_RES_ARPSLT 289  // arp+lt
#define STR_RES__SEQ 290  // seq
#define STR_RES_SEQSLT 291  // seq+lt
#define STR_RES_REC 292  // rec
#define STR_RES_IMPRO 293  // impro
#define STR_RES_FREE 294  // free
#define STR_RES_SLAVE 295  // slave
#define STR_RES_MASTER 296  // master
#define STR_RES_T 297  // ~
#define STR_RES__ 298  // 
#define STR_RES_T_ 299  // ~-
#define STR_RES__T_ 300  // ~
#define STR_RES_GLASS 301  // glass
#define STR_RES_KRAMA 302  // krama
#define STR_RES_JATA 303  // jata
#define STR_RES_SIKHA 304  // sikha
#define STR_RES_GHANA 305  // ghana
#define STR_RES_2GLASS 306  // 2glass
#define STR_RES_2KRAMA 307  // 2krama
#define STR_RES_2JATA 308  // 2jata
#define STR_RES_2SIKHA 309  // 2sikha
#define STR_RES_2GHANA 310  // 2ghana
#define STR_RES_4GLASS 311  // 4glass
#define STR_RES_4KRAMA 312  // 4krama
#define STR_RES_4JATA 313  // 4jata
#define STR_RES_4SIKHA 314  // 4sikha
#define STR_RES_4GHANA 315  // 4ghana
#define STR_RES_SWING 316  // swing
#define STR_RES_SHUFFLE 317  // shuffle
#define STR_RES_PUSH 318  // push
#define STR_RES__LAG 319  // lag
#define STR_RES_HUMAN 320  // human
#define STR_RES_MONKEY 321  // monkey
#define STR_RES__OFF 322  // off
#define STR_RES_THRU 323  // thru
#define STR_RES___SEQ 324  // seq
#define STR_RES_CTRL 325  // ctrl
#define STR_RES__SPLIT 326  // split
#define STR_RES_FULL 327  // full
#define STR_RES_1TV 328  // 1~|
#define STR_RES_2T1 329  // 2~1
#define STR_RES_3T2 330  // 3~2
#define STR_RES_4T3 331  // 4~3
#define STR_RES_5T4 332  // 5~4
#define STR_RES_6T5 333  // 6~5
#define STR_RES_7T6 334  // 7~6
#define STR_RES_8T7 335  // 8~7
#define STR_RES_TRI 336  // tri
#define STR_RES_SQR 337  // sqr
#define STR_RES_S_H 338  // s&h
#define STR_RES_RAMP 339  // ramp
#define STR_RES_STEP 340  // step
#define STR_RES_3 341  // 
#define STR_RES_4 342  // 
#define STR_RES_34 343  // 
#define STR_RES___ 344  // ?
#define STR_RES_OFF 345  // off
#define STR_RES_ON 346  // on
#define STR_RES_SQ1 347  // sq1
#define STR_RES_TR1 348  // tr1
#define STR_RES_PL1 349  // pl1
#define STR_RES_SQ2 350  // sq2
#define STR_RES_TR2 351  // tr2
#define STR_RES_PL2 352  // pl2
#define STR_RES_CLICK 353  // click
#define STR_RES_GLITCH 354  // glitch
#define STR_RES_BLOW 355  // blow
#define STR_RES_METAL 356  // metal
#define STR_RES_POP 357  // pop
#define STR_RES_NONE 358  // none
#define STR_RES_SAW 359  // saw
#define STR_RES_SQUARE 360  // square
#define STR_RES_TRIANG 361  // triang
#define STR_RES_ZSAW 362  // zsaw
#define STR_RES_ZRESO 363  // zreso
#define STR_RES_ZTRI 364  // ztri
#define STR_RES_ZPULSE 365  // zpulse
#define STR_RES_ZSYNC 366  // zsync
#define STR_RES_PAD 367  // pad
#define STR_RES_FM 368  // fm
#define STR_RES_WAVES 369  // waves
#define STR_RES_TAMPUR 370  // tampur
#define STR_RES_DIGITL 371  // digitl
#define STR_RES_METALL 372  // metall
#define STR_RES_BOWED 373  // bowed
#define STR_RES_SLAP 374  // slap
#define STR_RES_ORGAN 375  // organ
#define STR_RES_MALE 376  // male
#define STR_RES_USER 377  // user
#define STR_RES_8BITS 378  // 8bits
#define STR_RES_CRUSH 379  // crush
#define STR_RES_PWM 380  // pwm
#define STR_RES___NOISE 381  // noise
#define STR_RES_VOWEL 382  // vowel
#define STR_RES_BELISH 383  // belish
#define STR_RES_POLATD 384  // polatd
#define STR_RES_CELLO 385  // cello
#define STR_RES_CLPSWP 386  // clpswp
#define STR_RES_FEMALE 387  // female
#define STR_RES_FMTVOC 388  // fmtvoc
#define STR_RES_FRMNT2 389  // frmnt2
#define STR_RES_RES3HP 390  // res3hp
#define STR_RES_ELECTP 391  // electp
#define STR_RES_VIBES 392  // vibes
#define STR_RES__LPF 393  // lpf
#define STR_RES_SSM 394  // ssm
#define STR_RES_SVF 395  // svf
#define STR_RES_DSP 396  // dsp
#define STR_RES_PVK 397  // pvk
#define STR_RES_4PM 398  // 4pm
#define STR_RES_DLY 399  // dly
#define STR_RES____OFF 400  // off
#define STR_RES_FCD 401  // fcd
#define STR_RES_XT 402  // xt
#define STR_RES_EQUAL 403  // equal
#define STR_RES_JUST 404  // just
#define STR_RES_PYTHAG 405  // pythag
#define STR_RES_1_4_EB 406  // 1/4 eb
#define STR_RES_1_4_E 407  // 1/4 e
#define STR_RES_1_4_EA 408  // 1/4 ea
#define STR_RES_BHAIRA 409  // bhaira
#define STR_RES_GUNAKR 410  // gunakr
#define STR_RES_MARWA 411  // marwa
#define STR_RES_SHREE 412  // shree
#define STR_RES_PURVI 413  // purvi
#define STR_RES_BILAWA 414  // bilawa
#define STR_RES_YAMAN 415  // yaman
#define STR_RES_KAFI 416  // kafi
#define STR_RES_BHIMPA 417  // bhimpa
#define STR_RES_DARBAR 418  // darbar
#define STR_RES_BAGESH 419  // bagesh
#define STR_RES_RAGESH 420  // ragesh
#define STR_RES_KHAMAJ 421  // khamaj
#define STR_RES_MIMAL 422  // mi'mal
#define STR_RES_PARAME 423  // parame
#define STR_RES_RANGES 424  // ranges
#define STR_RES_GANGES 425  // ganges
#define STR_RES_KAMESH 426  // kamesh
#define STR_RES_PALAS_ 427  // palas
#define STR_RES_NATBHA 428  // natbha
#define STR_RES_M_KAUN 429  // m.kaun
#define STR_RES_BAIRAG 430  // bairag
#define STR_RES_B_TODI 431  // b.todi
#define STR_RES_CHANDR 432  // chandr
#define STR_RES_KAUSHI 433  // kaushi
#define STR_RES_JOGESH 434  // jogesh
#define STR_RES_RASIA 435  // rasia
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
#define WAV_RES_EXPANSION_KRAMA 25
#define WAV_RES_EXPANSION_KRAMA_SIZE 30
#define WAV_RES_EXPANSION_JATA 26
#define WAV_RES_EXPANSION_JATA_SIZE 90
#define WAV_RES_EXPANSION_SIKHA 27
#define WAV_RES_EXPANSION_SIKHA_SIZE 126
#define WAV_RES_EXPANSION_GHANA 28
#define WAV_RES_EXPANSION_GHANA_SIZE 182
#define WAV_RES_DISTORTION 29
#define WAV_RES_DISTORTION_SIZE 256
#define WAV_RES_ENV_EXPO 30
#define WAV_RES_ENV_EXPO_SIZE 257
#define WAV_RES_SSM2164_LINEARIZATION 31
#define WAV_RES_SSM2164_LINEARIZATION_SIZE 64
#define WAV_RES_WAVES 32
#define WAV_RES_WAVES_SIZE 16383
#define WAV_RES_WAVETABLES 33
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
