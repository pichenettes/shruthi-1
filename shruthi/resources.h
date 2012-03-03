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
#define STR_RES_TEMPO 31  // tempo
#define STR_RES_BPM 32  // bpm
#define STR_RES_GROOVE 33  // groove
#define STR_RES_DIRECTION 34  // direction
#define STR_RES_PATTERN 35  // pattern
#define STR_RES_WARP 36  // warp
#define STR_RES_WRP 37  // wrp
#define STR_RES_START 38  // start
#define STR_RES_SPLIT 39  // split
#define STR_RES_LENGTH 40  // length
#define STR_RES_OCTAVE 41  // octave
#define STR_RES_RAGA 42  // raga
#define STR_RES_PORTA 43  // porta
#define STR_RES_PRT 44  // prt
#define STR_RES_LEGATO 45  // legato
#define STR_RES_TUNING 46  // tuning
#define STR_RES_MIDI_CHAN 47  // midi chan
#define STR_RES_CHN 48  // chn
#define STR_RES_MIDI_OUT 49  // midi out
#define STR_RES_PAUSE 50  // pause
#define STR_RES_SNAP 51  // snap
#define STR_RES_CV_MODE 52  // cv.mode
#define STR_RES_OSCILLATOR_1 53  // oscillator 1
#define STR_RES_OSCILLATOR_2 54  // oscillator 2
#define STR_RES_MIXER 55  // mixer
#define STR_RES_FILTER 56  // filter
#define STR_RES_FILTERS 57  // filter+
#define STR_RES_MODE_1 58  // mode 1
#define STR_RES_MODE_2 59  // mode 2
#define STR_RES_MD1 60  // md1
#define STR_RES_MD2 61  // md2
#define STR_RES_ENVELOPE_1 62  // envelope 1
#define STR_RES_ENVELOPE_2 63  // envelope 2
#define STR_RES_SEQUENCER 64  // sequencer
#define STR_RES_ARPEGGIO 65  // arpeggio
#define STR_RES_CH1 66  // ch1
#define STR_RES_CH2 67  // ch2
#define STR_RES_11 68  // 1
#define STR_RES_12 69  // 2
#define STR_RES_STEP_SEQUENCER 70  // step sequencer
#define STR_RES_KEYBOARD 71  // keyboard
#define STR_RES_MIDI 72  // midi
#define STR_RES_SYSTEM 73  // system
#define STR_RES_TRIGGERS 74  // triggers
#define STR_RES_PERFORMANCE 75  // performance
#define STR_RES_PARAM__1 76  // param. 1
#define STR_RES_PARAM__2 77  // param. 2
#define STR_RES_PR1 78  // pr1
#define STR_RES_PR2 79  // pr2
#define STR_RES_FX_ 80  // fx.
#define STR_RES_FX_PROG_ 81  // fx prog.
#define STR_RES_LPF 82  // lpf
#define STR_RES_BPF 83  // bpf
#define STR_RES_HPF 84  // hpf
#define STR_RES_LPL 85  // lp<
#define STR_RES_BPL 86  // bp<
#define STR_RES_HPL 87  // hp<
#define STR_RES_SLP 88  // +lp
#define STR_RES_SBP 89  // +bp
#define STR_RES_SHP 90  // +hp
#define STR_RES_GLP 91  // >lp
#define STR_RES_GBP 92  // >bp
#define STR_RES_GHP 93  // >hp
#define STR_RES_CUT 94  // cut
#define STR_RES_VCA 95  // vca
#define STR_RES_PW1 96  // pw1
#define STR_RES_PW2 97  // pw2
#define STR_RES_51 98  // 1
#define STR_RES_52 99  // 2
#define STR_RES_5 100  // 
#define STR_RES_5F 101  // f
#define STR_RES_MIX 102  // mix
#define STR_RES_NOI 103  // noi
#define STR_RES_SUB 104  // sub
#define STR_RES_RES 105  // res
#define STR_RES_CV1 106  // cv1
#define STR_RES_CV2 107  // cv2
#define STR_RES__ATK 108  // atk
#define STR_RES__LF1 109  // lf1
#define STR_RES__LF2 110  // lf2
#define STR_RES_EN1 111  // en1
#define STR_RES_EN2 112  // en2
#define STR_RES_IN1 113  // in1
#define STR_RES_IN2 114  // in2
#define STR_RES_OUT 115  // out
#define STR_RES___OFF 116  // off
#define STR_RES_ADD 117  // add
#define STR_RES_PRD 118  // prd
#define STR_RES_MAX 119  // max
#define STR_RES_MIN 120  // min
#define STR_RES__XOR 121  // xor
#define STR_RES_GE 122  // >=
#define STR_RES_LE 123  // <=
#define STR_RES_QTZ 124  // qtz
#define STR_RES_LAG 125  // lag
#define STR_RES_CUTOFF 126  // cutoff
#define STR_RES__VCA 127  // vca
#define STR_RES_PWM1 128  // pwm1
#define STR_RES_PWM2 129  // pwm2
#define STR_RES_OSC1 130  // osc1
#define STR_RES_OSC2 131  // osc2
#define STR_RES_OSC1S2 132  // osc1+2
#define STR_RES_FINE 133  // fine
#define STR_RES__MIX 134  // mix
#define STR_RES_NOISE 135  // noise
#define STR_RES_SUBOSC 136  // subosc
#define STR_RES_RESO 137  // reso
#define STR_RES_CV_1 138  // cv 1
#define STR_RES_CV_2 139  // cv 2
#define STR_RES__ATTACK 140  // attack
#define STR_RES__LFO_1 141  // lfo 1
#define STR_RES__LFO_2 142  // lfo 2
#define STR_RES_ENV_1 143  // env 1
#define STR_RES_ENV_2 144  // env 2
#define STR_RES_DISTRT 145  // distrt
#define STR_RES_CRUSHR 146  // crushr
#define STR_RES_SCMBFL 147  // +cmbfl
#define STR_RES_CMBFL 148  // -cmbfl
#define STR_RES_RINGMD 149  // ringmd
#define STR_RES_DELAY 150  // delay
#define STR_RES_FB_DLY 151  // fb dly
#define STR_RES_DUBDLY 152  // dubdly
#define STR_RES__FBDLY 153  // !fbdly
#define STR_RES__DBDLY 154  // !dbdly
#define STR_RES__16_DL 155  // /16 dl
#define STR_RES__12_DL 156  // /12 dl
#define STR_RES__8_DLY 157  // /8 dly
#define STR_RES_3_16DL 158  // 3/16dl
#define STR_RES_LOOPER 159  // looper
#define STR_RES_PITCH 160  // pitch
#define STR_RES_LGF 161  // l>f
#define STR_RES_HGF 162  // h>f
#define STR_RES_FGL 163  // f>l
#define STR_RES_FGH 164  // f>h
#define STR_RES_GFX 165  // >fx
#define STR_RES_LF1 166  // lf1
#define STR_RES_LF2 167  // lf2
#define STR_RES_SEQ 168  // seq
#define STR_RES__SQ1 169  // sq1
#define STR_RES__SQ2 170  // sq2
#define STR_RES_ARP 171  // arp
#define STR_RES_WHL 172  // whl
#define STR_RES_AFT 173  // aft
#define STR_RES_BND 174  // bnd
#define STR_RES_OFS 175  // ofs
#define STR_RES__CV1 176  // cv1
#define STR_RES__CV2 177  // cv2
#define STR_RES_CV3 178  // cv3
#define STR_RES_CV4 179  // cv4
#define STR_RES_CCA 180  // ccA
#define STR_RES_CCB 181  // ccB
#define STR_RES_CCC 182  // ccC
#define STR_RES_CCD 183  // ccD
#define STR_RES__NOI 184  // noi
#define STR_RES__EN1 185  // en1
#define STR_RES__EN2 186  // en2
#define STR_RES_VEL 187  // vel
#define STR_RES_RND 188  // rnd
#define STR_RES_NOT 189  // not
#define STR_RES_GAT 190  // gat
#define STR_RES_AUD 191  // aud
#define STR_RES_OP1 192  // op1
#define STR_RES_OP2 193  // op2
#define STR_RES_TR1 194  // tr1
#define STR_RES_TR2 195  // tr2
#define STR_RES_E4 196  // =4
#define STR_RES_E8 197  // =8
#define STR_RES_E16 198  // =16
#define STR_RES_E32 199  // =32
#define STR_RES_LFO_1 200  // lfo 1
#define STR_RES_LFO_2 201  // lfo 2
#define STR_RES_STPSEQ 202  // stpseq
#define STR_RES_STPSQ1 203  // stpsq1
#define STR_RES_STPSQ2 204  // stpsq2
#define STR_RES__ARP 205  // arp
#define STR_RES_MWHEEL 206  // mwheel
#define STR_RES_AFTTCH 207  // afttch
#define STR_RES_BENDER 208  // bender
#define STR_RES_OFFSET 209  // offset
#define STR_RES__CV_1 210  // cv 1
#define STR_RES__CV_2 211  // cv 2
#define STR_RES_CV_3 212  // cv 3
#define STR_RES_CV_4 213  // cv 4
#define STR_RES_CC_A 214  // cc A
#define STR_RES_CC_B 215  // cc B
#define STR_RES_CC_C 216  // cc C
#define STR_RES_CC_D 217  // cc D
#define STR_RES__NOISE 218  // noise
#define STR_RES__ENV_1 219  // env 1
#define STR_RES__ENV_2 220  // env 2
#define STR_RES_VELO 221  // velo
#define STR_RES_RANDOM 222  // random
#define STR_RES_NOTE 223  // note
#define STR_RES_GATE 224  // gate
#define STR_RES_AUDIO 225  // audio
#define STR_RES_OP__1 226  // op. 1
#define STR_RES_OP__2 227  // op. 2
#define STR_RES_TRG_1 228  // trg 1
#define STR_RES_TRG_2 229  // trg 2
#define STR_RES_E_4 230  // = 4
#define STR_RES_E_8 231  // = 8
#define STR_RES_E_16 232  // = 16
#define STR_RES_E_32 233  // = 32
#define STR_RES_TOUCH_A_KNOB_TO 234  // touch a knob to
#define STR_RES_ASSIGN_PARAMETER 235  // assign parameter
#define STR_RES_PATCH 236  // patch
#define STR_RES_SEQUENCE 237  // sequence
#define STR_RES_COMBO 238  // combo
#define STR_RES_SAVE_MIDI_KBD 239  // save midi/kbd
#define STR_RES_SETTINGS_ 240  // settings?
#define STR_RES_START_FULL_MIDI 241  // start full midi
#define STR_RES_BACKUP_ 242  // backup?
#define STR_RES_BROWSE 243  // browse
#define STR_RES_SAVE 244  // save
#define STR_RES_COMPARE 245  // compare
#define STR_RES_ 246  // ----
#define STR_RES_V 247  // v
#define STR_RES_MUTABLE____V0_96 248  // mutable    v0.96
#define STR_RES_INSTRUMENTS_671 249  // instruments -1
#define STR_RES_EXTERN 250  // extern
#define STR_RES_X2_EXT 251  // x2 ext
#define STR_RES__2_EXT 252  // /2 ext
#define STR_RES__4_EXT 253  // /4 ext
#define STR_RES__8_EXT 254  // /8 ext
#define STR_RES_SUM 255  // sum
#define STR_RES_SYNC 256  // sync
#define STR_RES_RING 257  // ring
#define STR_RES_XOR 258  // xor
#define STR_RES_FUZZ 259  // fuzz
#define STR_RES_GG4 260  // >>4
#define STR_RES_GG8 261  // >>8
#define STR_RES_FOLD 262  // fold
#define STR_RES_BITS 263  // bits
#define STR_RES_STP 264  // stp
#define STR_RES___ARP 265  // arp
#define STR_RES_ARPSLT 266  // arp+lt
#define STR_RES__SEQ 267  // seq
#define STR_RES_SEQSLT 268  // seq+lt
#define STR_RES_REC 269  // rec
#define STR_RES_IMPRO 270  // impro
#define STR_RES_FREE 271  // free
#define STR_RES_SLAVE 272  // slave
#define STR_RES_MASTER 273  // master
#define STR_RES_ENVTRG 274  // envtrg
#define STR_RES_T 275  // ~
#define STR_RES__ 276  // 
#define STR_RES_T_ 277  // ~-
#define STR_RES__T_ 278  // ~
#define STR_RES_GLASS 279  // glass
#define STR_RES_KRAMA 280  // krama
#define STR_RES_JATA 281  // jata
#define STR_RES_SIKHA 282  // sikha
#define STR_RES_GHANA 283  // ghana
#define STR_RES_2GLASS 284  // 2glass
#define STR_RES_2KRAMA 285  // 2krama
#define STR_RES_2JATA 286  // 2jata
#define STR_RES_2SIKHA 287  // 2sikha
#define STR_RES_2GHANA 288  // 2ghana
#define STR_RES_4GLASS 289  // 4glass
#define STR_RES_4KRAMA 290  // 4krama
#define STR_RES_4JATA 291  // 4jata
#define STR_RES_4SIKHA 292  // 4sikha
#define STR_RES_4GHANA 293  // 4ghana
#define STR_RES_SWING 294  // swing
#define STR_RES_SHUFFLE 295  // shuffle
#define STR_RES_PUSH 296  // push
#define STR_RES__LAG 297  // lag
#define STR_RES_HUMAN 298  // human
#define STR_RES_MONKEY 299  // monkey
#define STR_RES__OFF 300  // off
#define STR_RES_THRU 301  // thru
#define STR_RES___SEQ 302  // seq
#define STR_RES_CTRL 303  // ctrl
#define STR_RES__SPLIT 304  // split
#define STR_RES_FULL 305  // full
#define STR_RES_1TV 306  // 1~|
#define STR_RES_2T1 307  // 2~1
#define STR_RES_3T2 308  // 3~2
#define STR_RES_4T3 309  // 4~3
#define STR_RES_5T4 310  // 5~4
#define STR_RES_6T5 311  // 6~5
#define STR_RES_7T6 312  // 7~6
#define STR_RES_8T7 313  // 8~7
#define STR_RES_TRI 314  // tri
#define STR_RES_SQR 315  // sqr
#define STR_RES_S_H 316  // s&h
#define STR_RES_RAMP 317  // ramp
#define STR_RES_STEP 318  // step
#define STR_RES_3 319  // 
#define STR_RES_4 320  // 
#define STR_RES_34 321  // 
#define STR_RES___ 322  // ?
#define STR_RES_OFF 323  // off
#define STR_RES_ON 324  // on
#define STR_RES_SQ1 325  // sq1
#define STR_RES__TR1 326  // tr1
#define STR_RES_PL1 327  // pl1
#define STR_RES_SQ2 328  // sq2
#define STR_RES__TR2 329  // tr2
#define STR_RES_PL2 330  // pl2
#define STR_RES_CLICK 331  // click
#define STR_RES_GLITCH 332  // glitch
#define STR_RES_BLOW 333  // blow
#define STR_RES_METAL 334  // metal
#define STR_RES_POP 335  // pop
#define STR_RES_NONE 336  // none
#define STR_RES_SAW 337  // saw
#define STR_RES_SQUARE 338  // square
#define STR_RES_TRIANG 339  // triang
#define STR_RES_ZSAW 340  // zsaw
#define STR_RES_ZRESO 341  // zreso
#define STR_RES_ZTRI 342  // ztri
#define STR_RES_ZPULSE 343  // zpulse
#define STR_RES_ZSYNC 344  // zsync
#define STR_RES_PAD 345  // pad
#define STR_RES_FM 346  // fm
#define STR_RES_WAVES 347  // waves
#define STR_RES_TAMPUR 348  // tampur
#define STR_RES_DIGITL 349  // digitl
#define STR_RES_METALL 350  // metall
#define STR_RES_BOWED 351  // bowed
#define STR_RES_SLAP 352  // slap
#define STR_RES_ORGAN 353  // organ
#define STR_RES_MALE 354  // male
#define STR_RES_USER 355  // user
#define STR_RES_8BITS 356  // 8bits
#define STR_RES_CRUSH 357  // crush
#define STR_RES_PWM 358  // pwm
#define STR_RES___NOISE 359  // noise
#define STR_RES_VOWEL 360  // vowel
#define STR_RES_BELISH 361  // belish
#define STR_RES_POLATD 362  // polatd
#define STR_RES_CELLO 363  // cello
#define STR_RES_CLPSWP 364  // clpswp
#define STR_RES_FEMALE 365  // female
#define STR_RES_FMTVOC 366  // fmtvoc
#define STR_RES_FRMNT2 367  // frmnt2
#define STR_RES_RES3HP 368  // res3hp
#define STR_RES_ELECTP 369  // electp
#define STR_RES_VIBES 370  // vibes
#define STR_RES__LPF 371  // lpf
#define STR_RES_SSM 372  // ssm
#define STR_RES_SVF 373  // svf
#define STR_RES_DSP 374  // dsp
#define STR_RES_PVK 375  // pvk
#define STR_RES_4CV_IN 376  // 4cv in
#define STR_RES_PRGM 377  // prgm
#define STR_RES_PEDALS 378  // pedals
#define STR_RES_EQUAL 379  // equal
#define STR_RES_JUST 380  // just
#define STR_RES_PYTHAG 381  // pythag
#define STR_RES_1_4_EB 382  // 1/4 eb
#define STR_RES_1_4_E 383  // 1/4 e
#define STR_RES_1_4_EA 384  // 1/4 ea
#define STR_RES_BHAIRA 385  // bhaira
#define STR_RES_GUNAKR 386  // gunakr
#define STR_RES_MARWA 387  // marwa
#define STR_RES_SHREE 388  // shree
#define STR_RES_PURVI 389  // purvi
#define STR_RES_BILAWA 390  // bilawa
#define STR_RES_YAMAN 391  // yaman
#define STR_RES_KAFI 392  // kafi
#define STR_RES_BHIMPA 393  // bhimpa
#define STR_RES_DARBAR 394  // darbar
#define STR_RES_BAGESH 395  // bagesh
#define STR_RES_RAGESH 396  // ragesh
#define STR_RES_KHAMAJ 397  // khamaj
#define STR_RES_MIMAL 398  // mi'mal
#define STR_RES_PARAME 399  // parame
#define STR_RES_RANGES 400  // ranges
#define STR_RES_GANGES 401  // ganges
#define STR_RES_KAMESH 402  // kamesh
#define STR_RES_PALAS_ 403  // palas
#define STR_RES_NATBHA 404  // natbha
#define STR_RES_M_KAUN 405  // m.kaun
#define STR_RES_BAIRAG 406  // bairag
#define STR_RES_B_TODI 407  // b.todi
#define STR_RES_CHANDR 408  // chandr
#define STR_RES_KAUSHI 409  // kaushi
#define STR_RES_JOGESH 410  // jogesh
#define STR_RES_RASIA 411  // rasia
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
