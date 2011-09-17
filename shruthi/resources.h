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
#define STR_RES_TEMPO 29  // tempo
#define STR_RES_BPM 30  // bpm
#define STR_RES_GROOVE 31  // groove
#define STR_RES_DIRECTION 32  // direction
#define STR_RES_PATTERN 33  // pattern
#define STR_RES_WARP 34  // warp
#define STR_RES_WRP 35  // wrp
#define STR_RES_START 36  // start
#define STR_RES_SPLIT 37  // split
#define STR_RES_LENGTH 38  // length
#define STR_RES_OCTAVE 39  // octave
#define STR_RES_RAGA 40  // raga
#define STR_RES_PORTA 41  // porta
#define STR_RES_PRT 42  // prt
#define STR_RES_LEGATO 43  // legato
#define STR_RES_TUNING 44  // tuning
#define STR_RES_MIDI_CHAN 45  // midi chan
#define STR_RES_CHN 46  // chn
#define STR_RES_MIDI_OUT 47  // midi out
#define STR_RES_PAUSE 48  // pause
#define STR_RES_SNAP 49  // snap
#define STR_RES_CV_MODE 50  // cv.mode
#define STR_RES_OSCILLATOR_1 51  // oscillator 1
#define STR_RES_OSCILLATOR_2 52  // oscillator 2
#define STR_RES_MIXER 53  // mixer
#define STR_RES_FILTER 54  // filter
#define STR_RES_FILTERS 55  // filter+
#define STR_RES_MODE_1 56  // mode 1
#define STR_RES_MODE_2 57  // mode 2
#define STR_RES_MD1 58  // md1
#define STR_RES_MD2 59  // md2
#define STR_RES_ENVELOPE_1 60  // envelope 1
#define STR_RES_ENVELOPE_2 61  // envelope 2
#define STR_RES_SEQUENCER 62  // sequencer
#define STR_RES_ARPEGGIO 63  // arpeggio
#define STR_RES_STEP_SEQUENCER 64  // step sequencer
#define STR_RES_KEYBOARD 65  // keyboard
#define STR_RES_MIDI 66  // midi
#define STR_RES_SYSTEM 67  // system
#define STR_RES_PERFORMANCE 68  // performance
#define STR_RES_PARAM__1 69  // param. 1
#define STR_RES_PARAM__2 70  // param. 2
#define STR_RES_PR1 71  // pr1
#define STR_RES_PR2 72  // pr2
#define STR_RES_FX_ 73  // fx.
#define STR_RES_FX_PROG_ 74  // fx prog.
#define STR_RES_LPF 75  // lpf
#define STR_RES_BPF 76  // bpf
#define STR_RES_HPF 77  // hpf
#define STR_RES_SLP 78  // +lp
#define STR_RES_SBP 79  // +bp
#define STR_RES_SHP 80  // +hp
#define STR_RES_GLP 81  // >lp
#define STR_RES_GBP 82  // >bp
#define STR_RES_GHP 83  // >hp
#define STR_RES_CUT 84  // cut
#define STR_RES_VCA 85  // vca
#define STR_RES_PW1 86  // pw1
#define STR_RES_PW2 87  // pw2
#define STR_RES_51 88  // 1
#define STR_RES_52 89  // 2
#define STR_RES_5 90  // 
#define STR_RES_5F 91  // f
#define STR_RES_MIX 92  // mix
#define STR_RES_NOI 93  // noi
#define STR_RES_SUB 94  // sub
#define STR_RES_RES 95  // res
#define STR_RES_CV1 96  // cv1
#define STR_RES_CV2 97  // cv2
#define STR_RES__ATK 98  // atk
#define STR_RES__LF1 99  // lf1
#define STR_RES__LF2 100  // lf2
#define STR_RES_IN1 101  // in1
#define STR_RES_IN2 102  // in2
#define STR_RES_OUT 103  // out
#define STR_RES___OFF 104  // off
#define STR_RES_ADD 105  // add
#define STR_RES_PRD 106  // prd
#define STR_RES_MAX 107  // max
#define STR_RES_MIN 108  // min
#define STR_RES__XOR 109  // xor
#define STR_RES_GE 110  // >=
#define STR_RES_LE 111  // <=
#define STR_RES_CUTOFF 112  // cutoff
#define STR_RES__VCA 113  // vca
#define STR_RES_PWM1 114  // pwm1
#define STR_RES_PWM2 115  // pwm2
#define STR_RES_OSC1 116  // osc1
#define STR_RES_OSC2 117  // osc2
#define STR_RES_OSC1S2 118  // osc1+2
#define STR_RES_FINE 119  // fine
#define STR_RES__MIX 120  // mix
#define STR_RES_NOISE 121  // noise
#define STR_RES_SUBOSC 122  // subosc
#define STR_RES_RESO 123  // reso
#define STR_RES_CV_1 124  // cv 1
#define STR_RES_CV_2 125  // cv 2
#define STR_RES__ATTACK 126  // attack
#define STR_RES__LFO_1 127  // lfo 1
#define STR_RES__LFO_2 128  // lfo 2
#define STR_RES_DISTRT 129  // distrt
#define STR_RES_CRUSHR 130  // crushr
#define STR_RES_SCMBFL 131  // +cmbfl
#define STR_RES_CMBFL 132  // -cmbfl
#define STR_RES_RINGMD 133  // ringmd
#define STR_RES_DELAY 134  // delay
#define STR_RES_FB_DLY 135  // fb dly
#define STR_RES_DUBDLY 136  // dubdly
#define STR_RES__FBDLY 137  // !fbdly
#define STR_RES__DBDLY 138  // !dbdly
#define STR_RES__16_DL 139  // /16 dl
#define STR_RES__12_DL 140  // /12 dl
#define STR_RES__8_DLY 141  // /8 dly
#define STR_RES_3_16DL 142  // 3/16dl
#define STR_RES_LOOPER 143  // looper
#define STR_RES_PITCH 144  // pitch
#define STR_RES_LGF 145  // l>f
#define STR_RES_HGF 146  // h>f
#define STR_RES_FGL 147  // f>l
#define STR_RES_FGH 148  // f>h
#define STR_RES_GFX 149  // >fx
#define STR_RES_LF1 150  // lf1
#define STR_RES_LF2 151  // lf2
#define STR_RES_SEQ 152  // seq
#define STR_RES__SQ1 153  // sq1
#define STR_RES__SQ2 154  // sq2
#define STR_RES_ARP 155  // arp
#define STR_RES_WHL 156  // whl
#define STR_RES_AFT 157  // aft
#define STR_RES_BND 158  // bnd
#define STR_RES_OFS 159  // ofs
#define STR_RES__CV1 160  // cv1
#define STR_RES__CV2 161  // cv2
#define STR_RES_CV3 162  // cv3
#define STR_RES_CV4 163  // cv4
#define STR_RES_CCA 164  // ccA
#define STR_RES_CCB 165  // ccB
#define STR_RES_CCC 166  // ccC
#define STR_RES_CCD 167  // ccD
#define STR_RES__NOI 168  // noi
#define STR_RES_EN1 169  // en1
#define STR_RES_EN2 170  // en2
#define STR_RES_VEL 171  // vel
#define STR_RES_RND 172  // rnd
#define STR_RES_NOT 173  // not
#define STR_RES_GAT 174  // gat
#define STR_RES_AUD 175  // aud
#define STR_RES_OP1 176  // op1
#define STR_RES_OP2 177  // op2
#define STR_RES_LFO_1 178  // lfo 1
#define STR_RES_LFO_2 179  // lfo 2
#define STR_RES_STPSEQ 180  // stpseq
#define STR_RES_STPSQ1 181  // stpsq1
#define STR_RES_STPSQ2 182  // stpsq2
#define STR_RES__ARP 183  // arp
#define STR_RES_MWHEEL 184  // mwheel
#define STR_RES_AFTTCH 185  // afttch
#define STR_RES_BENDER 186  // bender
#define STR_RES_OFFSET 187  // offset
#define STR_RES__CV_1 188  // cv 1
#define STR_RES__CV_2 189  // cv 2
#define STR_RES_CV_3 190  // cv 3
#define STR_RES_CV_4 191  // cv 4
#define STR_RES_CC_A 192  // cc A
#define STR_RES_CC_B 193  // cc B
#define STR_RES_CC_C 194  // cc C
#define STR_RES_CC_D 195  // cc D
#define STR_RES__NOISE 196  // noise
#define STR_RES_ENV_1 197  // env 1
#define STR_RES_ENV_2 198  // env 2
#define STR_RES_VELO 199  // velo
#define STR_RES_RANDOM 200  // random
#define STR_RES_NOTE 201  // note
#define STR_RES_GATE 202  // gate
#define STR_RES_AUDIO 203  // audio
#define STR_RES_OP__1 204  // op. 1
#define STR_RES_OP__2 205  // op. 2
#define STR_RES_TOUCH_A_KNOB_TO 206  // touch a knob to
#define STR_RES_ASSIGN_PARAMETER 207  // assign parameter
#define STR_RES_PATCH 208  // patch
#define STR_RES_SEQUENCE 209  // sequence
#define STR_RES_COMBO 210  // combo
#define STR_RES_SAVE_MIDI_KBD 211  // save midi/kbd
#define STR_RES_SETTINGS_ 212  // settings?
#define STR_RES_START_FULL_MIDI 213  // start full midi
#define STR_RES_BACKUP_ 214  // backup?
#define STR_RES_BROWSE 215  // browse
#define STR_RES_SAVE 216  // save
#define STR_RES_COMPARE 217  // compare
#define STR_RES_ 218  // ----
#define STR_RES_V 219  // v
#define STR_RES_MUTABLE____V0_94 220  // mutable    v0.94
#define STR_RES_INSTRUMENTS_671 221  // instruments -1
#define STR_RES_EXTERN 222  // extern
#define STR_RES_X2_EXT 223  // x2 ext
#define STR_RES__2_EXT 224  // /2 ext
#define STR_RES__4_EXT 225  // /4 ext
#define STR_RES__8_EXT 226  // /8 ext
#define STR_RES_SUM 227  // sum
#define STR_RES_SYNC 228  // sync
#define STR_RES_RING 229  // ring
#define STR_RES_XOR 230  // xor
#define STR_RES_FUZZ 231  // fuzz
#define STR_RES_GG4 232  // >>4
#define STR_RES_GG8 233  // >>8
#define STR_RES_STP 234  // stp
#define STR_RES___ARP 235  // arp
#define STR_RES_ARPSLT 236  // arp+lt
#define STR_RES__SEQ 237  // seq
#define STR_RES_SEQSLT 238  // seq+lt
#define STR_RES_REC 239  // rec
#define STR_RES_IMPRO 240  // impro
#define STR_RES_FREE 241  // free
#define STR_RES_SLAVE 242  // slave
#define STR_RES_MASTER 243  // master
#define STR_RES_T 244  // ~
#define STR_RES__ 245  // 
#define STR_RES_T_ 246  // ~-
#define STR_RES__T_ 247  // ~
#define STR_RES_GLASS 248  // glass
#define STR_RES_KRAMA 249  // krama
#define STR_RES_JATA 250  // jata
#define STR_RES_SIKHA 251  // sikha
#define STR_RES_GHANA 252  // ghana
#define STR_RES_2GLASS 253  // 2glass
#define STR_RES_2KRAMA 254  // 2krama
#define STR_RES_2JATA 255  // 2jata
#define STR_RES_2SIKHA 256  // 2sikha
#define STR_RES_2GHANA 257  // 2ghana
#define STR_RES_4GLASS 258  // 4glass
#define STR_RES_4KRAMA 259  // 4krama
#define STR_RES_4JATA 260  // 4jata
#define STR_RES_4SIKHA 261  // 4sikha
#define STR_RES_4GHANA 262  // 4ghana
#define STR_RES_SWING 263  // swing
#define STR_RES_SHUFFLE 264  // shuffle
#define STR_RES_PUSH 265  // push
#define STR_RES_LAG 266  // lag
#define STR_RES_HUMAN 267  // human
#define STR_RES_MONKEY 268  // monkey
#define STR_RES__OFF 269  // off
#define STR_RES_THRU 270  // thru
#define STR_RES___SEQ 271  // seq
#define STR_RES_CTRL 272  // ctrl
#define STR_RES__SPLIT 273  // split
#define STR_RES_FULL 274  // full
#define STR_RES_1TV 275  // 1~|
#define STR_RES_2T1 276  // 2~1
#define STR_RES_3T2 277  // 3~2
#define STR_RES_4T3 278  // 4~3
#define STR_RES_5T4 279  // 5~4
#define STR_RES_6T5 280  // 6~5
#define STR_RES_7T6 281  // 7~6
#define STR_RES_8T7 282  // 8~7
#define STR_RES_TRI 283  // tri
#define STR_RES_SQR 284  // sqr
#define STR_RES_S_H 285  // s&h
#define STR_RES_RAMP 286  // ramp
#define STR_RES_STEP 287  // step
#define STR_RES_3 288  // 
#define STR_RES_4 289  // 
#define STR_RES_34 290  // 
#define STR_RES___ 291  // ?
#define STR_RES_OFF 292  // off
#define STR_RES_ON 293  // on
#define STR_RES_SQ1 294  // sq1
#define STR_RES_TR1 295  // tr1
#define STR_RES_PL1 296  // pl1
#define STR_RES_SQ2 297  // sq2
#define STR_RES_TR2 298  // tr2
#define STR_RES_PL2 299  // pl2
#define STR_RES_CLICK 300  // click
#define STR_RES_GLITCH 301  // glitch
#define STR_RES_BLOW 302  // blow
#define STR_RES_METAL 303  // metal
#define STR_RES_POP 304  // pop
#define STR_RES_NONE 305  // none
#define STR_RES_SAW 306  // saw
#define STR_RES_SQUARE 307  // square
#define STR_RES_TRIANG 308  // triang
#define STR_RES_ZSAW 309  // zsaw
#define STR_RES_ZRESO 310  // zreso
#define STR_RES_ZTRI 311  // ztri
#define STR_RES_ZPULSE 312  // zpulse
#define STR_RES_ZSYNC 313  // zsync
#define STR_RES_PAD 314  // pad
#define STR_RES_FM 315  // fm
#define STR_RES_WAVES 316  // waves
#define STR_RES_TAMPUR 317  // tampur
#define STR_RES_DIGITL 318  // digitl
#define STR_RES_METALL 319  // metall
#define STR_RES_BOWED 320  // bowed
#define STR_RES_SLAP 321  // slap
#define STR_RES_ORGAN 322  // organ
#define STR_RES_MALE 323  // male
#define STR_RES_USER 324  // user
#define STR_RES_8BITS 325  // 8bits
#define STR_RES_CRUSH 326  // crush
#define STR_RES_PWM 327  // pwm
#define STR_RES___NOISE 328  // noise
#define STR_RES_VOWEL 329  // vowel
#define STR_RES_BELISH 330  // belish
#define STR_RES_POLATD 331  // polatd
#define STR_RES_CELLO 332  // cello
#define STR_RES_CLPSWP 333  // clpswp
#define STR_RES_FEMALE 334  // female
#define STR_RES_FMTVOC 335  // fmtvoc
#define STR_RES_FRMNT2 336  // frmnt2
#define STR_RES_RES3HP 337  // res3hp
#define STR_RES_ELECTP 338  // electp
#define STR_RES_VIBES 339  // vibes
#define STR_RES__LPF 340  // lpf
#define STR_RES_SSM 341  // ssm
#define STR_RES_SVF 342  // svf
#define STR_RES_DSP 343  // dsp
#define STR_RES_4CV_IN 344  // 4cv in
#define STR_RES_PRGM 345  // prgm
#define STR_RES_PEDALS 346  // pedals
#define STR_RES_EQUAL 347  // equal
#define STR_RES_JUST 348  // just
#define STR_RES_PYTHAG 349  // pythag
#define STR_RES_1_4_EB 350  // 1/4 eb
#define STR_RES_1_4_E 351  // 1/4 e
#define STR_RES_1_4_EA 352  // 1/4 ea
#define STR_RES_BHAIRA 353  // bhaira
#define STR_RES_GUNAKR 354  // gunakr
#define STR_RES_MARWA 355  // marwa
#define STR_RES_SHREE 356  // shree
#define STR_RES_PURVI 357  // purvi
#define STR_RES_BILAWA 358  // bilawa
#define STR_RES_YAMAN 359  // yaman
#define STR_RES_KAFI 360  // kafi
#define STR_RES_BHIMPA 361  // bhimpa
#define STR_RES_DARBAR 362  // darbar
#define STR_RES_BAGESH 363  // bagesh
#define STR_RES_RAGESH 364  // ragesh
#define STR_RES_KHAMAJ 365  // khamaj
#define STR_RES_MIMAL 366  // mi'mal
#define STR_RES_PARAME 367  // parame
#define STR_RES_RANGES 368  // ranges
#define STR_RES_GANGES 369  // ganges
#define STR_RES_KAMESH 370  // kamesh
#define STR_RES_PALAS_ 371  // palas
#define STR_RES_NATBHA 372  // natbha
#define STR_RES_M_KAUN 373  // m.kaun
#define STR_RES_BAIRAG 374  // bairag
#define STR_RES_B_TODI 375  // b.todi
#define STR_RES_CHANDR 376  // chandr
#define STR_RES_KAUSHI 377  // kaushi
#define STR_RES_JOGESH 378  // jogesh
#define STR_RES_RASIA 379  // rasia
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
#define WAV_RES_BANDLIMITED_TRIANGLE_1 18
#define WAV_RES_BANDLIMITED_TRIANGLE_1_SIZE 257
#define WAV_RES_BANDLIMITED_TRIANGLE_2 19
#define WAV_RES_BANDLIMITED_TRIANGLE_2_SIZE 257
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
