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
#define STR_RES_TEMPO 32  // tempo
#define STR_RES_BPM 33  // bpm
#define STR_RES_GROOVE 34  // groove
#define STR_RES_DIRECTION 35  // direction
#define STR_RES_PATTERN 36  // pattern
#define STR_RES_WARP 37  // warp
#define STR_RES_WRP 38  // wrp
#define STR_RES_START 39  // start
#define STR_RES_SPLIT 40  // split
#define STR_RES_LENGTH 41  // length
#define STR_RES_OCTAVE 42  // octave
#define STR_RES_RAGA 43  // raga
#define STR_RES_PORTA 44  // porta
#define STR_RES_PRT 45  // prt
#define STR_RES_LEGATO 46  // legato
#define STR_RES_TUNING 47  // tuning
#define STR_RES_MIDI_CHAN 48  // midi chan
#define STR_RES_CHN 49  // chn
#define STR_RES_MIDI_OUT 50  // midi out
#define STR_RES_PAUSE 51  // pause
#define STR_RES_SNAP 52  // snap
#define STR_RES_CV_MODE 53  // cv.mode
#define STR_RES_OSCILLATOR_1 54  // oscillator 1
#define STR_RES_OSCILLATOR_2 55  // oscillator 2
#define STR_RES_MIXER 56  // mixer
#define STR_RES_FILTER 57  // filter
#define STR_RES_FILTERS 58  // filter+
#define STR_RES_MODE_1 59  // mode 1
#define STR_RES_MODE_2 60  // mode 2
#define STR_RES_MD1 61  // md1
#define STR_RES_MD2 62  // md2
#define STR_RES_ENVELOPE_1 63  // envelope 1
#define STR_RES_ENVELOPE_2 64  // envelope 2
#define STR_RES_SEQUENCER 65  // sequencer
#define STR_RES_ARPEGGIO 66  // arpeggio
#define STR_RES_CH1 67  // ch1
#define STR_RES_CH2 68  // ch2
#define STR_RES_11 69  // 1
#define STR_RES_12 70  // 2
#define STR_RES_STEP_SEQUENCER 71  // step sequencer
#define STR_RES_KEYBOARD 72  // keyboard
#define STR_RES_MIDI 73  // midi
#define STR_RES_SYSTEM 74  // system
#define STR_RES_TRIGGERS 75  // triggers
#define STR_RES_PERFORMANCE 76  // performance
#define STR_RES_PARAM__1 77  // param. 1
#define STR_RES_PARAM__2 78  // param. 2
#define STR_RES_PR1 79  // pr1
#define STR_RES_PR2 80  // pr2
#define STR_RES_FX_ 81  // fx.
#define STR_RES_FX_PROG_ 82  // fx prog.
#define STR_RES_LPF 83  // lpf
#define STR_RES_BPF 84  // bpf
#define STR_RES_HPF 85  // hpf
#define STR_RES_LPL 86  // lp<
#define STR_RES_BPL 87  // bp<
#define STR_RES_HPL 88  // hp<
#define STR_RES_SLP 89  // +lp
#define STR_RES_SBP 90  // +bp
#define STR_RES_SHP 91  // +hp
#define STR_RES_GLP 92  // >lp
#define STR_RES_GBP 93  // >bp
#define STR_RES_GHP 94  // >hp
#define STR_RES_LP4 95  // lp4
#define STR_RES_LP3 96  // lp3
#define STR_RES_LP2 97  // lp2
#define STR_RES_LP1 98  // lp1
#define STR_RES_HP1 99  // hp1
#define STR_RES_HP2 100  // hp2
#define STR_RES_HP3 101  // hp3
#define STR_RES_BP2 102  // bp2
#define STR_RES_BP4 103  // bp4
#define STR_RES_NOTCH 104  // notch
#define STR_RES_PHASER 105  // phaser
#define STR_RES_H2LP 106  // h2lp
#define STR_RES_H3LP 107  // h3lp
#define STR_RES_NSLP 108  // n+lp
#define STR_RES_PSLP 109  // p+lp
#define STR_RES_LIQUID 110  // liquid
#define STR_RES_MS 111  // ms
#define STR_RES_WOBBLY 112  // wobbly
#define STR_RES_WHACKY 113  // whacky
#define STR_RES_CUT 114  // cut
#define STR_RES_VCA 115  // vca
#define STR_RES_PW1 116  // pw1
#define STR_RES_PW2 117  // pw2
#define STR_RES_51 118  // 1
#define STR_RES_52 119  // 2
#define STR_RES_5 120  // 
#define STR_RES_5F 121  // f
#define STR_RES_MIX 122  // mix
#define STR_RES_NOI 123  // noi
#define STR_RES_SUB 124  // sub
#define STR_RES_RES 125  // res
#define STR_RES_CV1 126  // cv1
#define STR_RES_CV2 127  // cv2
#define STR_RES__ATK 128  // atk
#define STR_RES__LF1 129  // lf1
#define STR_RES__LF2 130  // lf2
#define STR_RES_EN1 131  // en1
#define STR_RES_EN2 132  // en2
#define STR_RES_IN1 133  // in1
#define STR_RES_IN2 134  // in2
#define STR_RES_OUT 135  // out
#define STR_RES___OFF 136  // off
#define STR_RES_ADD 137  // add
#define STR_RES_PRD 138  // prd
#define STR_RES_MAX 139  // max
#define STR_RES_MIN 140  // min
#define STR_RES__XOR 141  // xor
#define STR_RES_GE 142  // >=
#define STR_RES_LE 143  // <=
#define STR_RES_QTZ 144  // qtz
#define STR_RES_LAG 145  // lag
#define STR_RES_CUTOFF 146  // cutoff
#define STR_RES__VCA 147  // vca
#define STR_RES_PWM1 148  // pwm1
#define STR_RES_PWM2 149  // pwm2
#define STR_RES_OSC1 150  // osc1
#define STR_RES_OSC2 151  // osc2
#define STR_RES_OSC1S2 152  // osc1+2
#define STR_RES_FINE 153  // fine
#define STR_RES__MIX 154  // mix
#define STR_RES_NOISE 155  // noise
#define STR_RES_SUBOSC 156  // subosc
#define STR_RES_RESO 157  // reso
#define STR_RES_CV_1 158  // cv 1
#define STR_RES_CV_2 159  // cv 2
#define STR_RES__ATTACK 160  // attack
#define STR_RES__LFO_1 161  // lfo 1
#define STR_RES__LFO_2 162  // lfo 2
#define STR_RES_ENV_1 163  // env 1
#define STR_RES_ENV_2 164  // env 2
#define STR_RES_DISTRT 165  // distrt
#define STR_RES_CRUSHR 166  // crushr
#define STR_RES_SCMBFL 167  // +cmbfl
#define STR_RES_CMBFL 168  // -cmbfl
#define STR_RES_RINGMD 169  // ringmd
#define STR_RES_DELAY 170  // delay
#define STR_RES_FB_DLY 171  // fb dly
#define STR_RES_DUBDLY 172  // dubdly
#define STR_RES__FBDLY 173  // !fbdly
#define STR_RES__DBDLY 174  // !dbdly
#define STR_RES__16_DL 175  // /16 dl
#define STR_RES__12_DL 176  // /12 dl
#define STR_RES__8_DLY 177  // /8 dly
#define STR_RES_3_16DL 178  // 3/16dl
#define STR_RES_LOOPER 179  // looper
#define STR_RES_PITCH 180  // pitch
#define STR_RES_LGF 181  // l>f
#define STR_RES_HGF 182  // h>f
#define STR_RES_FGL 183  // f>l
#define STR_RES_FGH 184  // f>h
#define STR_RES_GFX 185  // >fx
#define STR_RES_LF1 186  // lf1
#define STR_RES_LF2 187  // lf2
#define STR_RES_SEQ 188  // seq
#define STR_RES__SQ1 189  // sq1
#define STR_RES__SQ2 190  // sq2
#define STR_RES_ARP 191  // arp
#define STR_RES_WHL 192  // whl
#define STR_RES_AFT 193  // aft
#define STR_RES_BND 194  // bnd
#define STR_RES_OFS 195  // ofs
#define STR_RES__CV1 196  // cv1
#define STR_RES__CV2 197  // cv2
#define STR_RES_CV3 198  // cv3
#define STR_RES_CV4 199  // cv4
#define STR_RES_CCA 200  // ccA
#define STR_RES_CCB 201  // ccB
#define STR_RES_CCC 202  // ccC
#define STR_RES_CCD 203  // ccD
#define STR_RES__NOI 204  // noi
#define STR_RES__EN1 205  // en1
#define STR_RES__EN2 206  // en2
#define STR_RES_VEL 207  // vel
#define STR_RES_RND 208  // rnd
#define STR_RES_NOT 209  // not
#define STR_RES_GAT 210  // gat
#define STR_RES_AUD 211  // aud
#define STR_RES_OP1 212  // op1
#define STR_RES_OP2 213  // op2
#define STR_RES_TR1 214  // tr1
#define STR_RES_TR2 215  // tr2
#define STR_RES_E4 216  // =4
#define STR_RES_E8 217  // =8
#define STR_RES_E16 218  // =16
#define STR_RES_E32 219  // =32
#define STR_RES_LFO_1 220  // lfo 1
#define STR_RES_LFO_2 221  // lfo 2
#define STR_RES_STPSEQ 222  // stpseq
#define STR_RES_STPSQ1 223  // stpsq1
#define STR_RES_STPSQ2 224  // stpsq2
#define STR_RES__ARP 225  // arp
#define STR_RES_MWHEEL 226  // mwheel
#define STR_RES_AFTTCH 227  // afttch
#define STR_RES_BENDER 228  // bender
#define STR_RES_OFFSET 229  // offset
#define STR_RES__CV_1 230  // cv 1
#define STR_RES__CV_2 231  // cv 2
#define STR_RES_CV_3 232  // cv 3
#define STR_RES_CV_4 233  // cv 4
#define STR_RES_CC_A 234  // cc A
#define STR_RES_CC_B 235  // cc B
#define STR_RES_CC_C 236  // cc C
#define STR_RES_CC_D 237  // cc D
#define STR_RES__NOISE 238  // noise
#define STR_RES__ENV_1 239  // env 1
#define STR_RES__ENV_2 240  // env 2
#define STR_RES_VELO 241  // velo
#define STR_RES_RANDOM 242  // random
#define STR_RES_NOTE 243  // note
#define STR_RES_GATE 244  // gate
#define STR_RES_AUDIO 245  // audio
#define STR_RES_OP__1 246  // op. 1
#define STR_RES_OP__2 247  // op. 2
#define STR_RES_TRG_1 248  // trg 1
#define STR_RES_TRG_2 249  // trg 2
#define STR_RES_E_4 250  // = 4
#define STR_RES_E_8 251  // = 8
#define STR_RES_E_16 252  // = 16
#define STR_RES_E_32 253  // = 32
#define STR_RES_TOUCH_A_KNOB_TO 254  // touch a knob to
#define STR_RES_ASSIGN_PARAMETER 255  // assign parameter
#define STR_RES_PATCH 256  // patch
#define STR_RES_SEQUENCE 257  // sequence
#define STR_RES_COMBO 258  // combo
#define STR_RES_SAVE_MIDI_KBD 259  // save midi/kbd
#define STR_RES_SETTINGS_ 260  // settings?
#define STR_RES_START_FULL_MIDI 261  // start full midi
#define STR_RES_BACKUP_ 262  // backup?
#define STR_RES_BROWSE 263  // browse
#define STR_RES_SAVE 264  // save
#define STR_RES_COMPARE 265  // compare
#define STR_RES_ 266  // ----
#define STR_RES_V 267  // v
#define STR_RES_MUTABLE____V0_96 268  // mutable    v0.96
#define STR_RES_INSTRUMENTS_671 269  // instruments -1
#define STR_RES_EXTERN 270  // extern
#define STR_RES_X2_EXT 271  // x2 ext
#define STR_RES__2_EXT 272  // /2 ext
#define STR_RES__4_EXT 273  // /4 ext
#define STR_RES__8_EXT 274  // /8 ext
#define STR_RES_SUM 275  // sum
#define STR_RES_SYNC 276  // sync
#define STR_RES_RING 277  // ring
#define STR_RES_XOR 278  // xor
#define STR_RES_FUZZ 279  // fuzz
#define STR_RES_GG4 280  // >>4
#define STR_RES_GG8 281  // >>8
#define STR_RES_FOLD 282  // fold
#define STR_RES_BITS 283  // bits
#define STR_RES_2STEPS 284  // 2steps
#define STR_RES_4STEPS 285  // 4steps
#define STR_RES_8STEPS 286  // 8steps
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
#define STR_RES__TR1 348  // tr1
#define STR_RES_PL1 349  // pl1
#define STR_RES_SQ2 350  // sq2
#define STR_RES__TR2 351  // tr2
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
#define STR_RES_4CV_IN 399  // 4cv in
#define STR_RES_PRGM 400  // prgm
#define STR_RES_PEDALS 401  // pedals
#define STR_RES_EQUAL 402  // equal
#define STR_RES_JUST 403  // just
#define STR_RES_PYTHAG 404  // pythag
#define STR_RES_1_4_EB 405  // 1/4 eb
#define STR_RES_1_4_E 406  // 1/4 e
#define STR_RES_1_4_EA 407  // 1/4 ea
#define STR_RES_BHAIRA 408  // bhaira
#define STR_RES_GUNAKR 409  // gunakr
#define STR_RES_MARWA 410  // marwa
#define STR_RES_SHREE 411  // shree
#define STR_RES_PURVI 412  // purvi
#define STR_RES_BILAWA 413  // bilawa
#define STR_RES_YAMAN 414  // yaman
#define STR_RES_KAFI 415  // kafi
#define STR_RES_BHIMPA 416  // bhimpa
#define STR_RES_DARBAR 417  // darbar
#define STR_RES_BAGESH 418  // bagesh
#define STR_RES_RAGESH 419  // ragesh
#define STR_RES_KHAMAJ 420  // khamaj
#define STR_RES_MIMAL 421  // mi'mal
#define STR_RES_PARAME 422  // parame
#define STR_RES_RANGES 423  // ranges
#define STR_RES_GANGES 424  // ganges
#define STR_RES_KAMESH 425  // kamesh
#define STR_RES_PALAS_ 426  // palas
#define STR_RES_NATBHA 427  // natbha
#define STR_RES_M_KAUN 428  // m.kaun
#define STR_RES_BAIRAG 429  // bairag
#define STR_RES_B_TODI 430  // b.todi
#define STR_RES_CHANDR 431  // chandr
#define STR_RES_KAUSHI 432  // kaushi
#define STR_RES_JOGESH 433  // jogesh
#define STR_RES_RASIA 434  // rasia
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
#define WAV_RES_WAVES 31
#define WAV_RES_WAVES_SIZE 16383
#define WAV_RES_WAVETABLES 32
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
