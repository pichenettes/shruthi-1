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
#define STR_RES_CUTOFF 117  // cutoff
#define STR_RES__VCA 118  // vca
#define STR_RES_PWM1 119  // pwm1
#define STR_RES_PWM2 120  // pwm2
#define STR_RES_OSC1 121  // osc1
#define STR_RES_OSC2 122  // osc2
#define STR_RES_OSC1S2 123  // osc1+2
#define STR_RES_FINE 124  // fine
#define STR_RES__MIX 125  // mix
#define STR_RES_NOISE 126  // noise
#define STR_RES_SUBOSC 127  // subosc
#define STR_RES_RESO 128  // reso
#define STR_RES_CV_1 129  // cv 1
#define STR_RES_CV_2 130  // cv 2
#define STR_RES__ATTACK 131  // attack
#define STR_RES__LFO_1 132  // lfo 1
#define STR_RES__LFO_2 133  // lfo 2
#define STR_RES_DISTRT 134  // distrt
#define STR_RES_CRUSHR 135  // crushr
#define STR_RES_SCMBFL 136  // +cmbfl
#define STR_RES_CMBFL 137  // -cmbfl
#define STR_RES_RINGMD 138  // ringmd
#define STR_RES_DELAY 139  // delay
#define STR_RES_FB_DLY 140  // fb dly
#define STR_RES_DUBDLY 141  // dubdly
#define STR_RES__FBDLY 142  // !fbdly
#define STR_RES__DBDLY 143  // !dbdly
#define STR_RES__16_DL 144  // /16 dl
#define STR_RES__12_DL 145  // /12 dl
#define STR_RES__8_DLY 146  // /8 dly
#define STR_RES_3_16DL 147  // 3/16dl
#define STR_RES_LOOPER 148  // looper
#define STR_RES_PITCH 149  // pitch
#define STR_RES_LGF 150  // l>f
#define STR_RES_HGF 151  // h>f
#define STR_RES_FGL 152  // f>l
#define STR_RES_FGH 153  // f>h
#define STR_RES_GFX 154  // >fx
#define STR_RES_LF1 155  // lf1
#define STR_RES_LF2 156  // lf2
#define STR_RES_SEQ 157  // seq
#define STR_RES__SQ1 158  // sq1
#define STR_RES__SQ2 159  // sq2
#define STR_RES_ARP 160  // arp
#define STR_RES_WHL 161  // whl
#define STR_RES_AFT 162  // aft
#define STR_RES_BND 163  // bnd
#define STR_RES_OFS 164  // ofs
#define STR_RES__CV1 165  // cv1
#define STR_RES__CV2 166  // cv2
#define STR_RES_CV3 167  // cv3
#define STR_RES_CV4 168  // cv4
#define STR_RES_CCA 169  // ccA
#define STR_RES_CCB 170  // ccB
#define STR_RES_CCC 171  // ccC
#define STR_RES_CCD 172  // ccD
#define STR_RES__NOI 173  // noi
#define STR_RES_EN1 174  // en1
#define STR_RES_EN2 175  // en2
#define STR_RES_VEL 176  // vel
#define STR_RES_RND 177  // rnd
#define STR_RES_NOT 178  // not
#define STR_RES_GAT 179  // gat
#define STR_RES_AUD 180  // aud
#define STR_RES_OP1 181  // op1
#define STR_RES_OP2 182  // op2
#define STR_RES_LFO_1 183  // lfo 1
#define STR_RES_LFO_2 184  // lfo 2
#define STR_RES_STPSEQ 185  // stpseq
#define STR_RES_STPSQ1 186  // stpsq1
#define STR_RES_STPSQ2 187  // stpsq2
#define STR_RES__ARP 188  // arp
#define STR_RES_MWHEEL 189  // mwheel
#define STR_RES_AFTTCH 190  // afttch
#define STR_RES_BENDER 191  // bender
#define STR_RES_OFFSET 192  // offset
#define STR_RES__CV_1 193  // cv 1
#define STR_RES__CV_2 194  // cv 2
#define STR_RES_CV_3 195  // cv 3
#define STR_RES_CV_4 196  // cv 4
#define STR_RES_CC_A 197  // cc A
#define STR_RES_CC_B 198  // cc B
#define STR_RES_CC_C 199  // cc C
#define STR_RES_CC_D 200  // cc D
#define STR_RES__NOISE 201  // noise
#define STR_RES_ENV_1 202  // env 1
#define STR_RES_ENV_2 203  // env 2
#define STR_RES_VELO 204  // velo
#define STR_RES_RANDOM 205  // random
#define STR_RES_NOTE 206  // note
#define STR_RES_GATE 207  // gate
#define STR_RES_AUDIO 208  // audio
#define STR_RES_OP__1 209  // op. 1
#define STR_RES_OP__2 210  // op. 2
#define STR_RES_TOUCH_A_KNOB_TO 211  // touch a knob to
#define STR_RES_ASSIGN_PARAMETER 212  // assign parameter
#define STR_RES_PATCH 213  // patch
#define STR_RES_SEQUENCE 214  // sequence
#define STR_RES_COMBO 215  // combo
#define STR_RES_SAVE_MIDI_KBD 216  // save midi/kbd
#define STR_RES_SETTINGS_ 217  // settings?
#define STR_RES_START_FULL_MIDI 218  // start full midi
#define STR_RES_BACKUP_ 219  // backup?
#define STR_RES_BROWSE 220  // browse
#define STR_RES_SAVE 221  // save
#define STR_RES_COMPARE 222  // compare
#define STR_RES_ 223  // ----
#define STR_RES_V 224  // v
#define STR_RES_MUTABLE____V0_96 225  // mutable    v0.96
#define STR_RES_INSTRUMENTS_671 226  // instruments -1
#define STR_RES_EXTERN 227  // extern
#define STR_RES_X2_EXT 228  // x2 ext
#define STR_RES__2_EXT 229  // /2 ext
#define STR_RES__4_EXT 230  // /4 ext
#define STR_RES__8_EXT 231  // /8 ext
#define STR_RES_SUM 232  // sum
#define STR_RES_SYNC 233  // sync
#define STR_RES_RING 234  // ring
#define STR_RES_XOR 235  // xor
#define STR_RES_FUZZ 236  // fuzz
#define STR_RES_GG4 237  // >>4
#define STR_RES_GG8 238  // >>8
#define STR_RES_FOLD 239  // fold
#define STR_RES_BITS 240  // bits
#define STR_RES_STP 241  // stp
#define STR_RES___ARP 242  // arp
#define STR_RES_ARPSLT 243  // arp+lt
#define STR_RES__SEQ 244  // seq
#define STR_RES_SEQSLT 245  // seq+lt
#define STR_RES_REC 246  // rec
#define STR_RES_IMPRO 247  // impro
#define STR_RES_FREE 248  // free
#define STR_RES_SLAVE 249  // slave
#define STR_RES_MASTER 250  // master
#define STR_RES_T 251  // ~
#define STR_RES__ 252  // 
#define STR_RES_T_ 253  // ~-
#define STR_RES__T_ 254  // ~
#define STR_RES_GLASS 255  // glass
#define STR_RES_KRAMA 256  // krama
#define STR_RES_JATA 257  // jata
#define STR_RES_SIKHA 258  // sikha
#define STR_RES_GHANA 259  // ghana
#define STR_RES_2GLASS 260  // 2glass
#define STR_RES_2KRAMA 261  // 2krama
#define STR_RES_2JATA 262  // 2jata
#define STR_RES_2SIKHA 263  // 2sikha
#define STR_RES_2GHANA 264  // 2ghana
#define STR_RES_4GLASS 265  // 4glass
#define STR_RES_4KRAMA 266  // 4krama
#define STR_RES_4JATA 267  // 4jata
#define STR_RES_4SIKHA 268  // 4sikha
#define STR_RES_4GHANA 269  // 4ghana
#define STR_RES_SWING 270  // swing
#define STR_RES_SHUFFLE 271  // shuffle
#define STR_RES_PUSH 272  // push
#define STR_RES_LAG 273  // lag
#define STR_RES_HUMAN 274  // human
#define STR_RES_MONKEY 275  // monkey
#define STR_RES__OFF 276  // off
#define STR_RES_THRU 277  // thru
#define STR_RES___SEQ 278  // seq
#define STR_RES_CTRL 279  // ctrl
#define STR_RES__SPLIT 280  // split
#define STR_RES_FULL 281  // full
#define STR_RES_1TV 282  // 1~|
#define STR_RES_2T1 283  // 2~1
#define STR_RES_3T2 284  // 3~2
#define STR_RES_4T3 285  // 4~3
#define STR_RES_5T4 286  // 5~4
#define STR_RES_6T5 287  // 6~5
#define STR_RES_7T6 288  // 7~6
#define STR_RES_8T7 289  // 8~7
#define STR_RES_TRI 290  // tri
#define STR_RES_SQR 291  // sqr
#define STR_RES_S_H 292  // s&h
#define STR_RES_RAMP 293  // ramp
#define STR_RES_STEP 294  // step
#define STR_RES_3 295  // 
#define STR_RES_4 296  // 
#define STR_RES_34 297  // 
#define STR_RES___ 298  // ?
#define STR_RES_OFF 299  // off
#define STR_RES_ON 300  // on
#define STR_RES_SQ1 301  // sq1
#define STR_RES_TR1 302  // tr1
#define STR_RES_PL1 303  // pl1
#define STR_RES_SQ2 304  // sq2
#define STR_RES_TR2 305  // tr2
#define STR_RES_PL2 306  // pl2
#define STR_RES_CLICK 307  // click
#define STR_RES_GLITCH 308  // glitch
#define STR_RES_BLOW 309  // blow
#define STR_RES_METAL 310  // metal
#define STR_RES_POP 311  // pop
#define STR_RES_NONE 312  // none
#define STR_RES_SAW 313  // saw
#define STR_RES_SQUARE 314  // square
#define STR_RES_TRIANG 315  // triang
#define STR_RES_ZSAW 316  // zsaw
#define STR_RES_ZRESO 317  // zreso
#define STR_RES_ZTRI 318  // ztri
#define STR_RES_ZPULSE 319  // zpulse
#define STR_RES_ZSYNC 320  // zsync
#define STR_RES_PAD 321  // pad
#define STR_RES_FM 322  // fm
#define STR_RES_WAVES 323  // waves
#define STR_RES_TAMPUR 324  // tampur
#define STR_RES_DIGITL 325  // digitl
#define STR_RES_METALL 326  // metall
#define STR_RES_BOWED 327  // bowed
#define STR_RES_SLAP 328  // slap
#define STR_RES_ORGAN 329  // organ
#define STR_RES_MALE 330  // male
#define STR_RES_USER 331  // user
#define STR_RES_8BITS 332  // 8bits
#define STR_RES_CRUSH 333  // crush
#define STR_RES_PWM 334  // pwm
#define STR_RES___NOISE 335  // noise
#define STR_RES_VOWEL 336  // vowel
#define STR_RES_BELISH 337  // belish
#define STR_RES_POLATD 338  // polatd
#define STR_RES_CELLO 339  // cello
#define STR_RES_CLPSWP 340  // clpswp
#define STR_RES_FEMALE 341  // female
#define STR_RES_FMTVOC 342  // fmtvoc
#define STR_RES_FRMNT2 343  // frmnt2
#define STR_RES_RES3HP 344  // res3hp
#define STR_RES_ELECTP 345  // electp
#define STR_RES_VIBES 346  // vibes
#define STR_RES__LPF 347  // lpf
#define STR_RES_SSM 348  // ssm
#define STR_RES_SVF 349  // svf
#define STR_RES_DSP 350  // dsp
#define STR_RES_PVK 351  // pvk
#define STR_RES_4CV_IN 352  // 4cv in
#define STR_RES_PRGM 353  // prgm
#define STR_RES_PEDALS 354  // pedals
#define STR_RES_EQUAL 355  // equal
#define STR_RES_JUST 356  // just
#define STR_RES_PYTHAG 357  // pythag
#define STR_RES_1_4_EB 358  // 1/4 eb
#define STR_RES_1_4_E 359  // 1/4 e
#define STR_RES_1_4_EA 360  // 1/4 ea
#define STR_RES_BHAIRA 361  // bhaira
#define STR_RES_GUNAKR 362  // gunakr
#define STR_RES_MARWA 363  // marwa
#define STR_RES_SHREE 364  // shree
#define STR_RES_PURVI 365  // purvi
#define STR_RES_BILAWA 366  // bilawa
#define STR_RES_YAMAN 367  // yaman
#define STR_RES_KAFI 368  // kafi
#define STR_RES_BHIMPA 369  // bhimpa
#define STR_RES_DARBAR 370  // darbar
#define STR_RES_BAGESH 371  // bagesh
#define STR_RES_RAGESH 372  // ragesh
#define STR_RES_KHAMAJ 373  // khamaj
#define STR_RES_MIMAL 374  // mi'mal
#define STR_RES_PARAME 375  // parame
#define STR_RES_RANGES 376  // ranges
#define STR_RES_GANGES 377  // ganges
#define STR_RES_KAMESH 378  // kamesh
#define STR_RES_PALAS_ 379  // palas
#define STR_RES_NATBHA 380  // natbha
#define STR_RES_M_KAUN 381  // m.kaun
#define STR_RES_BAIRAG 382  // bairag
#define STR_RES_B_TODI 383  // b.todi
#define STR_RES_CHANDR 384  // chandr
#define STR_RES_KAUSHI 385  // kaushi
#define STR_RES_JOGESH 386  // jogesh
#define STR_RES_RASIA 387  // rasia
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
#define WAV_RES____BANDLIMITED_TRIANGLE_0 20
#define WAV_RES____BANDLIMITED_TRIANGLE_0_SIZE 257
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
#define WAV_RES_WAVES_SIZE 16512
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
