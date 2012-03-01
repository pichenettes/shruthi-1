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
#define STR_RES_STEP_SEQUENCER 66  // step sequencer
#define STR_RES_KEYBOARD 67  // keyboard
#define STR_RES_MIDI 68  // midi
#define STR_RES_SYSTEM 69  // system
#define STR_RES_PERFORMANCE 70  // performance
#define STR_RES_PARAM__1 71  // param. 1
#define STR_RES_PARAM__2 72  // param. 2
#define STR_RES_PR1 73  // pr1
#define STR_RES_PR2 74  // pr2
#define STR_RES_FX_ 75  // fx.
#define STR_RES_FX_PROG_ 76  // fx prog.
#define STR_RES_LPF 77  // lpf
#define STR_RES_BPF 78  // bpf
#define STR_RES_HPF 79  // hpf
#define STR_RES_LPL 80  // lp<
#define STR_RES_BPL 81  // bp<
#define STR_RES_HPL 82  // hp<
#define STR_RES_SLP 83  // +lp
#define STR_RES_SBP 84  // +bp
#define STR_RES_SHP 85  // +hp
#define STR_RES_GLP 86  // >lp
#define STR_RES_GBP 87  // >bp
#define STR_RES_GHP 88  // >hp
#define STR_RES_CUT 89  // cut
#define STR_RES_VCA 90  // vca
#define STR_RES_PW1 91  // pw1
#define STR_RES_PW2 92  // pw2
#define STR_RES_51 93  // 1
#define STR_RES_52 94  // 2
#define STR_RES_5 95  // 
#define STR_RES_5F 96  // f
#define STR_RES_MIX 97  // mix
#define STR_RES_NOI 98  // noi
#define STR_RES_SUB 99  // sub
#define STR_RES_RES 100  // res
#define STR_RES_CV1 101  // cv1
#define STR_RES_CV2 102  // cv2
#define STR_RES__ATK 103  // atk
#define STR_RES__LF1 104  // lf1
#define STR_RES__LF2 105  // lf2
#define STR_RES_IN1 106  // in1
#define STR_RES_IN2 107  // in2
#define STR_RES_OUT 108  // out
#define STR_RES___OFF 109  // off
#define STR_RES_ADD 110  // add
#define STR_RES_PRD 111  // prd
#define STR_RES_MAX 112  // max
#define STR_RES_MIN 113  // min
#define STR_RES__XOR 114  // xor
#define STR_RES_GE 115  // >=
#define STR_RES_LE 116  // <=
#define STR_RES_QTZ 117  // qtz
#define STR_RES_LAG 118  // lag
#define STR_RES_CUTOFF 119  // cutoff
#define STR_RES__VCA 120  // vca
#define STR_RES_PWM1 121  // pwm1
#define STR_RES_PWM2 122  // pwm2
#define STR_RES_OSC1 123  // osc1
#define STR_RES_OSC2 124  // osc2
#define STR_RES_OSC1S2 125  // osc1+2
#define STR_RES_FINE 126  // fine
#define STR_RES__MIX 127  // mix
#define STR_RES_NOISE 128  // noise
#define STR_RES_SUBOSC 129  // subosc
#define STR_RES_RESO 130  // reso
#define STR_RES_CV_1 131  // cv 1
#define STR_RES_CV_2 132  // cv 2
#define STR_RES__ATTACK 133  // attack
#define STR_RES__LFO_1 134  // lfo 1
#define STR_RES__LFO_2 135  // lfo 2
#define STR_RES_DISTRT 136  // distrt
#define STR_RES_CRUSHR 137  // crushr
#define STR_RES_SCMBFL 138  // +cmbfl
#define STR_RES_CMBFL 139  // -cmbfl
#define STR_RES_RINGMD 140  // ringmd
#define STR_RES_DELAY 141  // delay
#define STR_RES_FB_DLY 142  // fb dly
#define STR_RES_DUBDLY 143  // dubdly
#define STR_RES__FBDLY 144  // !fbdly
#define STR_RES__DBDLY 145  // !dbdly
#define STR_RES__16_DL 146  // /16 dl
#define STR_RES__12_DL 147  // /12 dl
#define STR_RES__8_DLY 148  // /8 dly
#define STR_RES_3_16DL 149  // 3/16dl
#define STR_RES_LOOPER 150  // looper
#define STR_RES_PITCH 151  // pitch
#define STR_RES_LGF 152  // l>f
#define STR_RES_HGF 153  // h>f
#define STR_RES_FGL 154  // f>l
#define STR_RES_FGH 155  // f>h
#define STR_RES_GFX 156  // >fx
#define STR_RES_LF1 157  // lf1
#define STR_RES_LF2 158  // lf2
#define STR_RES_SEQ 159  // seq
#define STR_RES__SQ1 160  // sq1
#define STR_RES__SQ2 161  // sq2
#define STR_RES_ARP 162  // arp
#define STR_RES_WHL 163  // whl
#define STR_RES_AFT 164  // aft
#define STR_RES_BND 165  // bnd
#define STR_RES_OFS 166  // ofs
#define STR_RES__CV1 167  // cv1
#define STR_RES__CV2 168  // cv2
#define STR_RES_CV3 169  // cv3
#define STR_RES_CV4 170  // cv4
#define STR_RES_CCA 171  // ccA
#define STR_RES_CCB 172  // ccB
#define STR_RES_CCC 173  // ccC
#define STR_RES_CCD 174  // ccD
#define STR_RES__NOI 175  // noi
#define STR_RES_EN1 176  // en1
#define STR_RES_EN2 177  // en2
#define STR_RES_VEL 178  // vel
#define STR_RES_RND 179  // rnd
#define STR_RES_NOT 180  // not
#define STR_RES_GAT 181  // gat
#define STR_RES_AUD 182  // aud
#define STR_RES_OP1 183  // op1
#define STR_RES_OP2 184  // op2
#define STR_RES_TR1 185  // tr1
#define STR_RES_TR2 186  // tr2
#define STR_RES_E4 187  // =4
#define STR_RES_E8 188  // =8
#define STR_RES_E16 189  // =16
#define STR_RES_E32 190  // =32
#define STR_RES_LFO_1 191  // lfo 1
#define STR_RES_LFO_2 192  // lfo 2
#define STR_RES_STPSEQ 193  // stpseq
#define STR_RES_STPSQ1 194  // stpsq1
#define STR_RES_STPSQ2 195  // stpsq2
#define STR_RES__ARP 196  // arp
#define STR_RES_MWHEEL 197  // mwheel
#define STR_RES_AFTTCH 198  // afttch
#define STR_RES_BENDER 199  // bender
#define STR_RES_OFFSET 200  // offset
#define STR_RES__CV_1 201  // cv 1
#define STR_RES__CV_2 202  // cv 2
#define STR_RES_CV_3 203  // cv 3
#define STR_RES_CV_4 204  // cv 4
#define STR_RES_CC_A 205  // cc A
#define STR_RES_CC_B 206  // cc B
#define STR_RES_CC_C 207  // cc C
#define STR_RES_CC_D 208  // cc D
#define STR_RES__NOISE 209  // noise
#define STR_RES_ENV_1 210  // env 1
#define STR_RES_ENV_2 211  // env 2
#define STR_RES_VELO 212  // velo
#define STR_RES_RANDOM 213  // random
#define STR_RES_NOTE 214  // note
#define STR_RES_GATE 215  // gate
#define STR_RES_AUDIO 216  // audio
#define STR_RES_OP__1 217  // op. 1
#define STR_RES_OP__2 218  // op. 2
#define STR_RES_TRG_1 219  // trg 1
#define STR_RES_TRG_2 220  // trg 2
#define STR_RES_E_4 221  // = 4
#define STR_RES_E_8 222  // = 8
#define STR_RES_E_16 223  // = 16
#define STR_RES_E_32 224  // = 32
#define STR_RES_TOUCH_A_KNOB_TO 225  // touch a knob to
#define STR_RES_ASSIGN_PARAMETER 226  // assign parameter
#define STR_RES_PATCH 227  // patch
#define STR_RES_SEQUENCE 228  // sequence
#define STR_RES_COMBO 229  // combo
#define STR_RES_SAVE_MIDI_KBD 230  // save midi/kbd
#define STR_RES_SETTINGS_ 231  // settings?
#define STR_RES_START_FULL_MIDI 232  // start full midi
#define STR_RES_BACKUP_ 233  // backup?
#define STR_RES_BROWSE 234  // browse
#define STR_RES_SAVE 235  // save
#define STR_RES_COMPARE 236  // compare
#define STR_RES_ 237  // ----
#define STR_RES_V 238  // v
#define STR_RES_MUTABLE____V0_96 239  // mutable    v0.96
#define STR_RES_INSTRUMENTS_671 240  // instruments -1
#define STR_RES_EXTERN 241  // extern
#define STR_RES_X2_EXT 242  // x2 ext
#define STR_RES__2_EXT 243  // /2 ext
#define STR_RES__4_EXT 244  // /4 ext
#define STR_RES__8_EXT 245  // /8 ext
#define STR_RES_SUM 246  // sum
#define STR_RES_SYNC 247  // sync
#define STR_RES_RING 248  // ring
#define STR_RES_XOR 249  // xor
#define STR_RES_FUZZ 250  // fuzz
#define STR_RES_GG4 251  // >>4
#define STR_RES_GG8 252  // >>8
#define STR_RES_FOLD 253  // fold
#define STR_RES_BITS 254  // bits
#define STR_RES_STP 255  // stp
#define STR_RES___ARP 256  // arp
#define STR_RES_ARPSLT 257  // arp+lt
#define STR_RES__SEQ 258  // seq
#define STR_RES_SEQSLT 259  // seq+lt
#define STR_RES_REC 260  // rec
#define STR_RES_IMPRO 261  // impro
#define STR_RES_FREE 262  // free
#define STR_RES_SLAVE 263  // slave
#define STR_RES_MASTER 264  // master
#define STR_RES_T 265  // ~
#define STR_RES__ 266  // 
#define STR_RES_T_ 267  // ~-
#define STR_RES__T_ 268  // ~
#define STR_RES_GLASS 269  // glass
#define STR_RES_KRAMA 270  // krama
#define STR_RES_JATA 271  // jata
#define STR_RES_SIKHA 272  // sikha
#define STR_RES_GHANA 273  // ghana
#define STR_RES_2GLASS 274  // 2glass
#define STR_RES_2KRAMA 275  // 2krama
#define STR_RES_2JATA 276  // 2jata
#define STR_RES_2SIKHA 277  // 2sikha
#define STR_RES_2GHANA 278  // 2ghana
#define STR_RES_4GLASS 279  // 4glass
#define STR_RES_4KRAMA 280  // 4krama
#define STR_RES_4JATA 281  // 4jata
#define STR_RES_4SIKHA 282  // 4sikha
#define STR_RES_4GHANA 283  // 4ghana
#define STR_RES_SWING 284  // swing
#define STR_RES_SHUFFLE 285  // shuffle
#define STR_RES_PUSH 286  // push
#define STR_RES__LAG 287  // lag
#define STR_RES_HUMAN 288  // human
#define STR_RES_MONKEY 289  // monkey
#define STR_RES__OFF 290  // off
#define STR_RES_THRU 291  // thru
#define STR_RES___SEQ 292  // seq
#define STR_RES_CTRL 293  // ctrl
#define STR_RES__SPLIT 294  // split
#define STR_RES_FULL 295  // full
#define STR_RES_1TV 296  // 1~|
#define STR_RES_2T1 297  // 2~1
#define STR_RES_3T2 298  // 3~2
#define STR_RES_4T3 299  // 4~3
#define STR_RES_5T4 300  // 5~4
#define STR_RES_6T5 301  // 6~5
#define STR_RES_7T6 302  // 7~6
#define STR_RES_8T7 303  // 8~7
#define STR_RES_TRI 304  // tri
#define STR_RES_SQR 305  // sqr
#define STR_RES_S_H 306  // s&h
#define STR_RES_RAMP 307  // ramp
#define STR_RES_STEP 308  // step
#define STR_RES_3 309  // 
#define STR_RES_4 310  // 
#define STR_RES_34 311  // 
#define STR_RES___ 312  // ?
#define STR_RES_OFF 313  // off
#define STR_RES_ON 314  // on
#define STR_RES_SQ1 315  // sq1
#define STR_RES__TR1 316  // tr1
#define STR_RES_PL1 317  // pl1
#define STR_RES_SQ2 318  // sq2
#define STR_RES__TR2 319  // tr2
#define STR_RES_PL2 320  // pl2
#define STR_RES_CLICK 321  // click
#define STR_RES_GLITCH 322  // glitch
#define STR_RES_BLOW 323  // blow
#define STR_RES_METAL 324  // metal
#define STR_RES_POP 325  // pop
#define STR_RES_NONE 326  // none
#define STR_RES_SAW 327  // saw
#define STR_RES_SQUARE 328  // square
#define STR_RES_TRIANG 329  // triang
#define STR_RES_ZSAW 330  // zsaw
#define STR_RES_ZRESO 331  // zreso
#define STR_RES_ZTRI 332  // ztri
#define STR_RES_ZPULSE 333  // zpulse
#define STR_RES_ZSYNC 334  // zsync
#define STR_RES_PAD 335  // pad
#define STR_RES_FM 336  // fm
#define STR_RES_WAVES 337  // waves
#define STR_RES_TAMPUR 338  // tampur
#define STR_RES_DIGITL 339  // digitl
#define STR_RES_METALL 340  // metall
#define STR_RES_BOWED 341  // bowed
#define STR_RES_SLAP 342  // slap
#define STR_RES_ORGAN 343  // organ
#define STR_RES_MALE 344  // male
#define STR_RES_USER 345  // user
#define STR_RES_8BITS 346  // 8bits
#define STR_RES_CRUSH 347  // crush
#define STR_RES_PWM 348  // pwm
#define STR_RES___NOISE 349  // noise
#define STR_RES_VOWEL 350  // vowel
#define STR_RES_BELISH 351  // belish
#define STR_RES_POLATD 352  // polatd
#define STR_RES_CELLO 353  // cello
#define STR_RES_CLPSWP 354  // clpswp
#define STR_RES_FEMALE 355  // female
#define STR_RES_FMTVOC 356  // fmtvoc
#define STR_RES_FRMNT2 357  // frmnt2
#define STR_RES_RES3HP 358  // res3hp
#define STR_RES_ELECTP 359  // electp
#define STR_RES_VIBES 360  // vibes
#define STR_RES__LPF 361  // lpf
#define STR_RES_SSM 362  // ssm
#define STR_RES_SVF 363  // svf
#define STR_RES_DSP 364  // dsp
#define STR_RES_PVK 365  // pvk
#define STR_RES_4CV_IN 366  // 4cv in
#define STR_RES_PRGM 367  // prgm
#define STR_RES_PEDALS 368  // pedals
#define STR_RES_EQUAL 369  // equal
#define STR_RES_JUST 370  // just
#define STR_RES_PYTHAG 371  // pythag
#define STR_RES_1_4_EB 372  // 1/4 eb
#define STR_RES_1_4_E 373  // 1/4 e
#define STR_RES_1_4_EA 374  // 1/4 ea
#define STR_RES_BHAIRA 375  // bhaira
#define STR_RES_GUNAKR 376  // gunakr
#define STR_RES_MARWA 377  // marwa
#define STR_RES_SHREE 378  // shree
#define STR_RES_PURVI 379  // purvi
#define STR_RES_BILAWA 380  // bilawa
#define STR_RES_YAMAN 381  // yaman
#define STR_RES_KAFI 382  // kafi
#define STR_RES_BHIMPA 383  // bhimpa
#define STR_RES_DARBAR 384  // darbar
#define STR_RES_BAGESH 385  // bagesh
#define STR_RES_RAGESH 386  // ragesh
#define STR_RES_KHAMAJ 387  // khamaj
#define STR_RES_MIMAL 388  // mi'mal
#define STR_RES_PARAME 389  // parame
#define STR_RES_RANGES 390  // ranges
#define STR_RES_GANGES 391  // ganges
#define STR_RES_KAMESH 392  // kamesh
#define STR_RES_PALAS_ 393  // palas
#define STR_RES_NATBHA 394  // natbha
#define STR_RES_M_KAUN 395  // m.kaun
#define STR_RES_BAIRAG 396  // bairag
#define STR_RES_B_TODI 397  // b.todi
#define STR_RES_CHANDR 398  // chandr
#define STR_RES_KAUSHI 399  // kaushi
#define STR_RES_JOGESH 400  // jogesh
#define STR_RES_RASIA 401  // rasia
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
