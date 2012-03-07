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
#define STR_RES_MS_REZ 31  // ms rez
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
#define STR_RES_ALLPASS 105  // allpass
#define STR_RES_H2LP 106  // h2lp
#define STR_RES_H3LP 107  // h3lp
#define STR_RES_NSLP 108  // n+lp
#define STR_RES_ASLP 109  // a+lp
#define STR_RES_CUT 110  // cut
#define STR_RES_VCA 111  // vca
#define STR_RES_PW1 112  // pw1
#define STR_RES_PW2 113  // pw2
#define STR_RES_51 114  // 1
#define STR_RES_52 115  // 2
#define STR_RES_5 116  // 
#define STR_RES_5F 117  // f
#define STR_RES_MIX 118  // mix
#define STR_RES_NOI 119  // noi
#define STR_RES_SUB 120  // sub
#define STR_RES_RES 121  // res
#define STR_RES_CV1 122  // cv1
#define STR_RES_CV2 123  // cv2
#define STR_RES__ATK 124  // atk
#define STR_RES__LF1 125  // lf1
#define STR_RES__LF2 126  // lf2
#define STR_RES_EN1 127  // en1
#define STR_RES_EN2 128  // en2
#define STR_RES_IN1 129  // in1
#define STR_RES_IN2 130  // in2
#define STR_RES_OUT 131  // out
#define STR_RES___OFF 132  // off
#define STR_RES_ADD 133  // add
#define STR_RES_PRD 134  // prd
#define STR_RES_MAX 135  // max
#define STR_RES_MIN 136  // min
#define STR_RES__XOR 137  // xor
#define STR_RES_GE 138  // >=
#define STR_RES_LE 139  // <=
#define STR_RES_QTZ 140  // qtz
#define STR_RES_LAG 141  // lag
#define STR_RES_CUTOFF 142  // cutoff
#define STR_RES__VCA 143  // vca
#define STR_RES_PWM1 144  // pwm1
#define STR_RES_PWM2 145  // pwm2
#define STR_RES_OSC1 146  // osc1
#define STR_RES_OSC2 147  // osc2
#define STR_RES_OSC1S2 148  // osc1+2
#define STR_RES_FINE 149  // fine
#define STR_RES__MIX 150  // mix
#define STR_RES_NOISE 151  // noise
#define STR_RES_SUBOSC 152  // subosc
#define STR_RES_RESO 153  // reso
#define STR_RES_CV_1 154  // cv 1
#define STR_RES_CV_2 155  // cv 2
#define STR_RES__ATTACK 156  // attack
#define STR_RES__LFO_1 157  // lfo 1
#define STR_RES__LFO_2 158  // lfo 2
#define STR_RES_ENV_1 159  // env 1
#define STR_RES_ENV_2 160  // env 2
#define STR_RES_DISTRT 161  // distrt
#define STR_RES_CRUSHR 162  // crushr
#define STR_RES_SCMBFL 163  // +cmbfl
#define STR_RES_CMBFL 164  // -cmbfl
#define STR_RES_RINGMD 165  // ringmd
#define STR_RES_DELAY 166  // delay
#define STR_RES_FB_DLY 167  // fb dly
#define STR_RES_DUBDLY 168  // dubdly
#define STR_RES__FBDLY 169  // !fbdly
#define STR_RES__DBDLY 170  // !dbdly
#define STR_RES__16_DL 171  // /16 dl
#define STR_RES__12_DL 172  // /12 dl
#define STR_RES__8_DLY 173  // /8 dly
#define STR_RES_3_16DL 174  // 3/16dl
#define STR_RES_LOOPER 175  // looper
#define STR_RES_PITCH 176  // pitch
#define STR_RES_LGF 177  // l>f
#define STR_RES_HGF 178  // h>f
#define STR_RES_FGL 179  // f>l
#define STR_RES_FGH 180  // f>h
#define STR_RES_GFX 181  // >fx
#define STR_RES_LF1 182  // lf1
#define STR_RES_LF2 183  // lf2
#define STR_RES_SEQ 184  // seq
#define STR_RES__SQ1 185  // sq1
#define STR_RES__SQ2 186  // sq2
#define STR_RES_ARP 187  // arp
#define STR_RES_WHL 188  // whl
#define STR_RES_AFT 189  // aft
#define STR_RES_BND 190  // bnd
#define STR_RES_OFS 191  // ofs
#define STR_RES__CV1 192  // cv1
#define STR_RES__CV2 193  // cv2
#define STR_RES_CV3 194  // cv3
#define STR_RES_CV4 195  // cv4
#define STR_RES_CCA 196  // ccA
#define STR_RES_CCB 197  // ccB
#define STR_RES_CCC 198  // ccC
#define STR_RES_CCD 199  // ccD
#define STR_RES__NOI 200  // noi
#define STR_RES__EN1 201  // en1
#define STR_RES__EN2 202  // en2
#define STR_RES_VEL 203  // vel
#define STR_RES_RND 204  // rnd
#define STR_RES_NOT 205  // not
#define STR_RES_GAT 206  // gat
#define STR_RES_AUD 207  // aud
#define STR_RES_OP1 208  // op1
#define STR_RES_OP2 209  // op2
#define STR_RES_TR1 210  // tr1
#define STR_RES_TR2 211  // tr2
#define STR_RES_E4 212  // =4
#define STR_RES_E8 213  // =8
#define STR_RES_E16 214  // =16
#define STR_RES_E32 215  // =32
#define STR_RES_LFO_1 216  // lfo 1
#define STR_RES_LFO_2 217  // lfo 2
#define STR_RES_STPSEQ 218  // stpseq
#define STR_RES_STPSQ1 219  // stpsq1
#define STR_RES_STPSQ2 220  // stpsq2
#define STR_RES__ARP 221  // arp
#define STR_RES_MWHEEL 222  // mwheel
#define STR_RES_AFTTCH 223  // afttch
#define STR_RES_BENDER 224  // bender
#define STR_RES_OFFSET 225  // offset
#define STR_RES__CV_1 226  // cv 1
#define STR_RES__CV_2 227  // cv 2
#define STR_RES_CV_3 228  // cv 3
#define STR_RES_CV_4 229  // cv 4
#define STR_RES_CC_A 230  // cc A
#define STR_RES_CC_B 231  // cc B
#define STR_RES_CC_C 232  // cc C
#define STR_RES_CC_D 233  // cc D
#define STR_RES__NOISE 234  // noise
#define STR_RES__ENV_1 235  // env 1
#define STR_RES__ENV_2 236  // env 2
#define STR_RES_VELO 237  // velo
#define STR_RES_RANDOM 238  // random
#define STR_RES_NOTE 239  // note
#define STR_RES_GATE 240  // gate
#define STR_RES_AUDIO 241  // audio
#define STR_RES_OP__1 242  // op. 1
#define STR_RES_OP__2 243  // op. 2
#define STR_RES_TRG_1 244  // trg 1
#define STR_RES_TRG_2 245  // trg 2
#define STR_RES_E_4 246  // = 4
#define STR_RES_E_8 247  // = 8
#define STR_RES_E_16 248  // = 16
#define STR_RES_E_32 249  // = 32
#define STR_RES_TOUCH_A_KNOB_TO 250  // touch a knob to
#define STR_RES_ASSIGN_PARAMETER 251  // assign parameter
#define STR_RES_PATCH 252  // patch
#define STR_RES_SEQUENCE 253  // sequence
#define STR_RES_COMBO 254  // combo
#define STR_RES_SAVE_MIDI_KBD 255  // save midi/kbd
#define STR_RES_SETTINGS_ 256  // settings?
#define STR_RES_START_FULL_MIDI 257  // start full midi
#define STR_RES_BACKUP_ 258  // backup?
#define STR_RES_BROWSE 259  // browse
#define STR_RES_SAVE 260  // save
#define STR_RES_COMPARE 261  // compare
#define STR_RES_ 262  // ----
#define STR_RES_V 263  // v
#define STR_RES_MUTABLE____V0_96 264  // mutable    v0.96
#define STR_RES_INSTRUMENTS_671 265  // instruments -1
#define STR_RES_EXTERN 266  // extern
#define STR_RES_X2_EXT 267  // x2 ext
#define STR_RES__2_EXT 268  // /2 ext
#define STR_RES__4_EXT 269  // /4 ext
#define STR_RES__8_EXT 270  // /8 ext
#define STR_RES_SUM 271  // sum
#define STR_RES_SYNC 272  // sync
#define STR_RES_RING 273  // ring
#define STR_RES_XOR 274  // xor
#define STR_RES_FUZZ 275  // fuzz
#define STR_RES_GG4 276  // >>4
#define STR_RES_GG8 277  // >>8
#define STR_RES_FOLD 278  // fold
#define STR_RES_BITS 279  // bits
#define STR_RES_STP 280  // stp
#define STR_RES___ARP 281  // arp
#define STR_RES_ARPSLT 282  // arp+lt
#define STR_RES__SEQ 283  // seq
#define STR_RES_SEQSLT 284  // seq+lt
#define STR_RES_REC 285  // rec
#define STR_RES_IMPRO 286  // impro
#define STR_RES_FREE 287  // free
#define STR_RES_SLAVE 288  // slave
#define STR_RES_MASTER 289  // master
#define STR_RES_T 290  // ~
#define STR_RES__ 291  // 
#define STR_RES_T_ 292  // ~-
#define STR_RES__T_ 293  // ~
#define STR_RES_GLASS 294  // glass
#define STR_RES_KRAMA 295  // krama
#define STR_RES_JATA 296  // jata
#define STR_RES_SIKHA 297  // sikha
#define STR_RES_GHANA 298  // ghana
#define STR_RES_2GLASS 299  // 2glass
#define STR_RES_2KRAMA 300  // 2krama
#define STR_RES_2JATA 301  // 2jata
#define STR_RES_2SIKHA 302  // 2sikha
#define STR_RES_2GHANA 303  // 2ghana
#define STR_RES_4GLASS 304  // 4glass
#define STR_RES_4KRAMA 305  // 4krama
#define STR_RES_4JATA 306  // 4jata
#define STR_RES_4SIKHA 307  // 4sikha
#define STR_RES_4GHANA 308  // 4ghana
#define STR_RES_SWING 309  // swing
#define STR_RES_SHUFFLE 310  // shuffle
#define STR_RES_PUSH 311  // push
#define STR_RES__LAG 312  // lag
#define STR_RES_HUMAN 313  // human
#define STR_RES_MONKEY 314  // monkey
#define STR_RES__OFF 315  // off
#define STR_RES_THRU 316  // thru
#define STR_RES___SEQ 317  // seq
#define STR_RES_CTRL 318  // ctrl
#define STR_RES__SPLIT 319  // split
#define STR_RES_FULL 320  // full
#define STR_RES_1TV 321  // 1~|
#define STR_RES_2T1 322  // 2~1
#define STR_RES_3T2 323  // 3~2
#define STR_RES_4T3 324  // 4~3
#define STR_RES_5T4 325  // 5~4
#define STR_RES_6T5 326  // 6~5
#define STR_RES_7T6 327  // 7~6
#define STR_RES_8T7 328  // 8~7
#define STR_RES_TRI 329  // tri
#define STR_RES_SQR 330  // sqr
#define STR_RES_S_H 331  // s&h
#define STR_RES_RAMP 332  // ramp
#define STR_RES_STEP 333  // step
#define STR_RES_3 334  // 
#define STR_RES_4 335  // 
#define STR_RES_34 336  // 
#define STR_RES___ 337  // ?
#define STR_RES_OFF 338  // off
#define STR_RES_ON 339  // on
#define STR_RES_SQ1 340  // sq1
#define STR_RES__TR1 341  // tr1
#define STR_RES_PL1 342  // pl1
#define STR_RES_SQ2 343  // sq2
#define STR_RES__TR2 344  // tr2
#define STR_RES_PL2 345  // pl2
#define STR_RES_CLICK 346  // click
#define STR_RES_GLITCH 347  // glitch
#define STR_RES_BLOW 348  // blow
#define STR_RES_METAL 349  // metal
#define STR_RES_POP 350  // pop
#define STR_RES_NONE 351  // none
#define STR_RES_SAW 352  // saw
#define STR_RES_SQUARE 353  // square
#define STR_RES_TRIANG 354  // triang
#define STR_RES_ZSAW 355  // zsaw
#define STR_RES_ZRESO 356  // zreso
#define STR_RES_ZTRI 357  // ztri
#define STR_RES_ZPULSE 358  // zpulse
#define STR_RES_ZSYNC 359  // zsync
#define STR_RES_PAD 360  // pad
#define STR_RES_FM 361  // fm
#define STR_RES_WAVES 362  // waves
#define STR_RES_TAMPUR 363  // tampur
#define STR_RES_DIGITL 364  // digitl
#define STR_RES_METALL 365  // metall
#define STR_RES_BOWED 366  // bowed
#define STR_RES_SLAP 367  // slap
#define STR_RES_ORGAN 368  // organ
#define STR_RES_MALE 369  // male
#define STR_RES_USER 370  // user
#define STR_RES_8BITS 371  // 8bits
#define STR_RES_CRUSH 372  // crush
#define STR_RES_PWM 373  // pwm
#define STR_RES___NOISE 374  // noise
#define STR_RES_VOWEL 375  // vowel
#define STR_RES_BELISH 376  // belish
#define STR_RES_POLATD 377  // polatd
#define STR_RES_CELLO 378  // cello
#define STR_RES_CLPSWP 379  // clpswp
#define STR_RES_FEMALE 380  // female
#define STR_RES_FMTVOC 381  // fmtvoc
#define STR_RES_FRMNT2 382  // frmnt2
#define STR_RES_RES3HP 383  // res3hp
#define STR_RES_ELECTP 384  // electp
#define STR_RES_VIBES 385  // vibes
#define STR_RES__LPF 386  // lpf
#define STR_RES_SSM 387  // ssm
#define STR_RES_SVF 388  // svf
#define STR_RES_DSP 389  // dsp
#define STR_RES_PVK 390  // pvk
#define STR_RES_4PM 391  // 4pm
#define STR_RES_4CV_IN 392  // 4cv in
#define STR_RES_PRGM 393  // prgm
#define STR_RES_PEDALS 394  // pedals
#define STR_RES_EQUAL 395  // equal
#define STR_RES_JUST 396  // just
#define STR_RES_PYTHAG 397  // pythag
#define STR_RES_1_4_EB 398  // 1/4 eb
#define STR_RES_1_4_E 399  // 1/4 e
#define STR_RES_1_4_EA 400  // 1/4 ea
#define STR_RES_BHAIRA 401  // bhaira
#define STR_RES_GUNAKR 402  // gunakr
#define STR_RES_MARWA 403  // marwa
#define STR_RES_SHREE 404  // shree
#define STR_RES_PURVI 405  // purvi
#define STR_RES_BILAWA 406  // bilawa
#define STR_RES_YAMAN 407  // yaman
#define STR_RES_KAFI 408  // kafi
#define STR_RES_BHIMPA 409  // bhimpa
#define STR_RES_DARBAR 410  // darbar
#define STR_RES_BAGESH 411  // bagesh
#define STR_RES_RAGESH 412  // ragesh
#define STR_RES_KHAMAJ 413  // khamaj
#define STR_RES_MIMAL 414  // mi'mal
#define STR_RES_PARAME 415  // parame
#define STR_RES_RANGES 416  // ranges
#define STR_RES_GANGES 417  // ganges
#define STR_RES_KAMESH 418  // kamesh
#define STR_RES_PALAS_ 419  // palas
#define STR_RES_NATBHA 420  // natbha
#define STR_RES_M_KAUN 421  // m.kaun
#define STR_RES_BAIRAG 422  // bairag
#define STR_RES_B_TODI 423  // b.todi
#define STR_RES_CHANDR 424  // chandr
#define STR_RES_KAUSHI 425  // kaushi
#define STR_RES_JOGESH 426  // jogesh
#define STR_RES_RASIA 427  // rasia
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
