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
#define STR_RES_IN1 111  // in1
#define STR_RES_IN2 112  // in2
#define STR_RES_OUT 113  // out
#define STR_RES___OFF 114  // off
#define STR_RES_ADD 115  // add
#define STR_RES_PRD 116  // prd
#define STR_RES_MAX 117  // max
#define STR_RES_MIN 118  // min
#define STR_RES__XOR 119  // xor
#define STR_RES_GE 120  // >=
#define STR_RES_LE 121  // <=
#define STR_RES_QTZ 122  // qtz
#define STR_RES_LAG 123  // lag
#define STR_RES_CUTOFF 124  // cutoff
#define STR_RES__VCA 125  // vca
#define STR_RES_PWM1 126  // pwm1
#define STR_RES_PWM2 127  // pwm2
#define STR_RES_OSC1 128  // osc1
#define STR_RES_OSC2 129  // osc2
#define STR_RES_OSC1S2 130  // osc1+2
#define STR_RES_FINE 131  // fine
#define STR_RES__MIX 132  // mix
#define STR_RES_NOISE 133  // noise
#define STR_RES_SUBOSC 134  // subosc
#define STR_RES_RESO 135  // reso
#define STR_RES_CV_1 136  // cv 1
#define STR_RES_CV_2 137  // cv 2
#define STR_RES__ATTACK 138  // attack
#define STR_RES__LFO_1 139  // lfo 1
#define STR_RES__LFO_2 140  // lfo 2
#define STR_RES_DISTRT 141  // distrt
#define STR_RES_CRUSHR 142  // crushr
#define STR_RES_SCMBFL 143  // +cmbfl
#define STR_RES_CMBFL 144  // -cmbfl
#define STR_RES_RINGMD 145  // ringmd
#define STR_RES_DELAY 146  // delay
#define STR_RES_FB_DLY 147  // fb dly
#define STR_RES_DUBDLY 148  // dubdly
#define STR_RES__FBDLY 149  // !fbdly
#define STR_RES__DBDLY 150  // !dbdly
#define STR_RES__16_DL 151  // /16 dl
#define STR_RES__12_DL 152  // /12 dl
#define STR_RES__8_DLY 153  // /8 dly
#define STR_RES_3_16DL 154  // 3/16dl
#define STR_RES_LOOPER 155  // looper
#define STR_RES_PITCH 156  // pitch
#define STR_RES_LGF 157  // l>f
#define STR_RES_HGF 158  // h>f
#define STR_RES_FGL 159  // f>l
#define STR_RES_FGH 160  // f>h
#define STR_RES_GFX 161  // >fx
#define STR_RES_LF1 162  // lf1
#define STR_RES_LF2 163  // lf2
#define STR_RES_SEQ 164  // seq
#define STR_RES__SQ1 165  // sq1
#define STR_RES__SQ2 166  // sq2
#define STR_RES_ARP 167  // arp
#define STR_RES_WHL 168  // whl
#define STR_RES_AFT 169  // aft
#define STR_RES_BND 170  // bnd
#define STR_RES_OFS 171  // ofs
#define STR_RES__CV1 172  // cv1
#define STR_RES__CV2 173  // cv2
#define STR_RES_CV3 174  // cv3
#define STR_RES_CV4 175  // cv4
#define STR_RES_CCA 176  // ccA
#define STR_RES_CCB 177  // ccB
#define STR_RES_CCC 178  // ccC
#define STR_RES_CCD 179  // ccD
#define STR_RES__NOI 180  // noi
#define STR_RES_EN1 181  // en1
#define STR_RES_EN2 182  // en2
#define STR_RES_VEL 183  // vel
#define STR_RES_RND 184  // rnd
#define STR_RES_NOT 185  // not
#define STR_RES_GAT 186  // gat
#define STR_RES_AUD 187  // aud
#define STR_RES_OP1 188  // op1
#define STR_RES_OP2 189  // op2
#define STR_RES_TR1 190  // tr1
#define STR_RES_TR2 191  // tr2
#define STR_RES_E4 192  // =4
#define STR_RES_E8 193  // =8
#define STR_RES_E16 194  // =16
#define STR_RES_E32 195  // =32
#define STR_RES_LFO_1 196  // lfo 1
#define STR_RES_LFO_2 197  // lfo 2
#define STR_RES_STPSEQ 198  // stpseq
#define STR_RES_STPSQ1 199  // stpsq1
#define STR_RES_STPSQ2 200  // stpsq2
#define STR_RES__ARP 201  // arp
#define STR_RES_MWHEEL 202  // mwheel
#define STR_RES_AFTTCH 203  // afttch
#define STR_RES_BENDER 204  // bender
#define STR_RES_OFFSET 205  // offset
#define STR_RES__CV_1 206  // cv 1
#define STR_RES__CV_2 207  // cv 2
#define STR_RES_CV_3 208  // cv 3
#define STR_RES_CV_4 209  // cv 4
#define STR_RES_CC_A 210  // cc A
#define STR_RES_CC_B 211  // cc B
#define STR_RES_CC_C 212  // cc C
#define STR_RES_CC_D 213  // cc D
#define STR_RES__NOISE 214  // noise
#define STR_RES_ENV_1 215  // env 1
#define STR_RES_ENV_2 216  // env 2
#define STR_RES_VELO 217  // velo
#define STR_RES_RANDOM 218  // random
#define STR_RES_NOTE 219  // note
#define STR_RES_GATE 220  // gate
#define STR_RES_AUDIO 221  // audio
#define STR_RES_OP__1 222  // op. 1
#define STR_RES_OP__2 223  // op. 2
#define STR_RES_TRG_1 224  // trg 1
#define STR_RES_TRG_2 225  // trg 2
#define STR_RES_E_4 226  // = 4
#define STR_RES_E_8 227  // = 8
#define STR_RES_E_16 228  // = 16
#define STR_RES_E_32 229  // = 32
#define STR_RES_TOUCH_A_KNOB_TO 230  // touch a knob to
#define STR_RES_ASSIGN_PARAMETER 231  // assign parameter
#define STR_RES_PATCH 232  // patch
#define STR_RES_SEQUENCE 233  // sequence
#define STR_RES_COMBO 234  // combo
#define STR_RES_SAVE_MIDI_KBD 235  // save midi/kbd
#define STR_RES_SETTINGS_ 236  // settings?
#define STR_RES_START_FULL_MIDI 237  // start full midi
#define STR_RES_BACKUP_ 238  // backup?
#define STR_RES_BROWSE 239  // browse
#define STR_RES_SAVE 240  // save
#define STR_RES_COMPARE 241  // compare
#define STR_RES_ 242  // ----
#define STR_RES_V 243  // v
#define STR_RES_MUTABLE____V0_96 244  // mutable    v0.96
#define STR_RES_INSTRUMENTS_671 245  // instruments -1
#define STR_RES_EXTERN 246  // extern
#define STR_RES_X2_EXT 247  // x2 ext
#define STR_RES__2_EXT 248  // /2 ext
#define STR_RES__4_EXT 249  // /4 ext
#define STR_RES__8_EXT 250  // /8 ext
#define STR_RES_SUM 251  // sum
#define STR_RES_SYNC 252  // sync
#define STR_RES_RING 253  // ring
#define STR_RES_XOR 254  // xor
#define STR_RES_FUZZ 255  // fuzz
#define STR_RES_GG4 256  // >>4
#define STR_RES_GG8 257  // >>8
#define STR_RES_FOLD 258  // fold
#define STR_RES_BITS 259  // bits
#define STR_RES_STP 260  // stp
#define STR_RES___ARP 261  // arp
#define STR_RES_ARPSLT 262  // arp+lt
#define STR_RES__SEQ 263  // seq
#define STR_RES_SEQSLT 264  // seq+lt
#define STR_RES_REC 265  // rec
#define STR_RES_IMPRO 266  // impro
#define STR_RES_FREE 267  // free
#define STR_RES_SLAVE 268  // slave
#define STR_RES_MASTER 269  // master
#define STR_RES_T 270  // ~
#define STR_RES__ 271  // 
#define STR_RES_T_ 272  // ~-
#define STR_RES__T_ 273  // ~
#define STR_RES_GLASS 274  // glass
#define STR_RES_KRAMA 275  // krama
#define STR_RES_JATA 276  // jata
#define STR_RES_SIKHA 277  // sikha
#define STR_RES_GHANA 278  // ghana
#define STR_RES_2GLASS 279  // 2glass
#define STR_RES_2KRAMA 280  // 2krama
#define STR_RES_2JATA 281  // 2jata
#define STR_RES_2SIKHA 282  // 2sikha
#define STR_RES_2GHANA 283  // 2ghana
#define STR_RES_4GLASS 284  // 4glass
#define STR_RES_4KRAMA 285  // 4krama
#define STR_RES_4JATA 286  // 4jata
#define STR_RES_4SIKHA 287  // 4sikha
#define STR_RES_4GHANA 288  // 4ghana
#define STR_RES_SWING 289  // swing
#define STR_RES_SHUFFLE 290  // shuffle
#define STR_RES_PUSH 291  // push
#define STR_RES__LAG 292  // lag
#define STR_RES_HUMAN 293  // human
#define STR_RES_MONKEY 294  // monkey
#define STR_RES__OFF 295  // off
#define STR_RES_THRU 296  // thru
#define STR_RES___SEQ 297  // seq
#define STR_RES_CTRL 298  // ctrl
#define STR_RES__SPLIT 299  // split
#define STR_RES_FULL 300  // full
#define STR_RES_1TV 301  // 1~|
#define STR_RES_2T1 302  // 2~1
#define STR_RES_3T2 303  // 3~2
#define STR_RES_4T3 304  // 4~3
#define STR_RES_5T4 305  // 5~4
#define STR_RES_6T5 306  // 6~5
#define STR_RES_7T6 307  // 7~6
#define STR_RES_8T7 308  // 8~7
#define STR_RES_TRI 309  // tri
#define STR_RES_SQR 310  // sqr
#define STR_RES_S_H 311  // s&h
#define STR_RES_RAMP 312  // ramp
#define STR_RES_STEP 313  // step
#define STR_RES_3 314  // 
#define STR_RES_4 315  // 
#define STR_RES_34 316  // 
#define STR_RES___ 317  // ?
#define STR_RES_OFF 318  // off
#define STR_RES_ON 319  // on
#define STR_RES_SQ1 320  // sq1
#define STR_RES__TR1 321  // tr1
#define STR_RES_PL1 322  // pl1
#define STR_RES_SQ2 323  // sq2
#define STR_RES__TR2 324  // tr2
#define STR_RES_PL2 325  // pl2
#define STR_RES_CLICK 326  // click
#define STR_RES_GLITCH 327  // glitch
#define STR_RES_BLOW 328  // blow
#define STR_RES_METAL 329  // metal
#define STR_RES_POP 330  // pop
#define STR_RES_NONE 331  // none
#define STR_RES_SAW 332  // saw
#define STR_RES_SQUARE 333  // square
#define STR_RES_TRIANG 334  // triang
#define STR_RES_ZSAW 335  // zsaw
#define STR_RES_ZRESO 336  // zreso
#define STR_RES_ZTRI 337  // ztri
#define STR_RES_ZPULSE 338  // zpulse
#define STR_RES_ZSYNC 339  // zsync
#define STR_RES_PAD 340  // pad
#define STR_RES_FM 341  // fm
#define STR_RES_WAVES 342  // waves
#define STR_RES_TAMPUR 343  // tampur
#define STR_RES_DIGITL 344  // digitl
#define STR_RES_METALL 345  // metall
#define STR_RES_BOWED 346  // bowed
#define STR_RES_SLAP 347  // slap
#define STR_RES_ORGAN 348  // organ
#define STR_RES_MALE 349  // male
#define STR_RES_USER 350  // user
#define STR_RES_8BITS 351  // 8bits
#define STR_RES_CRUSH 352  // crush
#define STR_RES_PWM 353  // pwm
#define STR_RES___NOISE 354  // noise
#define STR_RES_VOWEL 355  // vowel
#define STR_RES_BELISH 356  // belish
#define STR_RES_POLATD 357  // polatd
#define STR_RES_CELLO 358  // cello
#define STR_RES_CLPSWP 359  // clpswp
#define STR_RES_FEMALE 360  // female
#define STR_RES_FMTVOC 361  // fmtvoc
#define STR_RES_FRMNT2 362  // frmnt2
#define STR_RES_RES3HP 363  // res3hp
#define STR_RES_ELECTP 364  // electp
#define STR_RES_VIBES 365  // vibes
#define STR_RES__LPF 366  // lpf
#define STR_RES_SSM 367  // ssm
#define STR_RES_SVF 368  // svf
#define STR_RES_DSP 369  // dsp
#define STR_RES_PVK 370  // pvk
#define STR_RES_4CV_IN 371  // 4cv in
#define STR_RES_PRGM 372  // prgm
#define STR_RES_PEDALS 373  // pedals
#define STR_RES_EQUAL 374  // equal
#define STR_RES_JUST 375  // just
#define STR_RES_PYTHAG 376  // pythag
#define STR_RES_1_4_EB 377  // 1/4 eb
#define STR_RES_1_4_E 378  // 1/4 e
#define STR_RES_1_4_EA 379  // 1/4 ea
#define STR_RES_BHAIRA 380  // bhaira
#define STR_RES_GUNAKR 381  // gunakr
#define STR_RES_MARWA 382  // marwa
#define STR_RES_SHREE 383  // shree
#define STR_RES_PURVI 384  // purvi
#define STR_RES_BILAWA 385  // bilawa
#define STR_RES_YAMAN 386  // yaman
#define STR_RES_KAFI 387  // kafi
#define STR_RES_BHIMPA 388  // bhimpa
#define STR_RES_DARBAR 389  // darbar
#define STR_RES_BAGESH 390  // bagesh
#define STR_RES_RAGESH 391  // ragesh
#define STR_RES_KHAMAJ 392  // khamaj
#define STR_RES_MIMAL 393  // mi'mal
#define STR_RES_PARAME 394  // parame
#define STR_RES_RANGES 395  // ranges
#define STR_RES_GANGES 396  // ganges
#define STR_RES_KAMESH 397  // kamesh
#define STR_RES_PALAS_ 398  // palas
#define STR_RES_NATBHA 399  // natbha
#define STR_RES_M_KAUN 400  // m.kaun
#define STR_RES_BAIRAG 401  // bairag
#define STR_RES_B_TODI 402  // b.todi
#define STR_RES_CHANDR 403  // chandr
#define STR_RES_KAUSHI 404  // kaushi
#define STR_RES_JOGESH 405  // jogesh
#define STR_RES_RASIA 406  // rasia
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
