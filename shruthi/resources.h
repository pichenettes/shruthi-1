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
#define STR_RES_SLP 80  // +lp
#define STR_RES_SBP 81  // +bp
#define STR_RES_SHP 82  // +hp
#define STR_RES_GLP 83  // >lp
#define STR_RES_GBP 84  // >bp
#define STR_RES_GHP 85  // >hp
#define STR_RES_CUT 86  // cut
#define STR_RES_VCA 87  // vca
#define STR_RES_PW1 88  // pw1
#define STR_RES_PW2 89  // pw2
#define STR_RES_51 90  // 1
#define STR_RES_52 91  // 2
#define STR_RES_5 92  // 
#define STR_RES_5F 93  // f
#define STR_RES_MIX 94  // mix
#define STR_RES_NOI 95  // noi
#define STR_RES_SUB 96  // sub
#define STR_RES_RES 97  // res
#define STR_RES_CV1 98  // cv1
#define STR_RES_CV2 99  // cv2
#define STR_RES__ATK 100  // atk
#define STR_RES__LF1 101  // lf1
#define STR_RES__LF2 102  // lf2
#define STR_RES_IN1 103  // in1
#define STR_RES_IN2 104  // in2
#define STR_RES_OUT 105  // out
#define STR_RES___OFF 106  // off
#define STR_RES_ADD 107  // add
#define STR_RES_PRD 108  // prd
#define STR_RES_MAX 109  // max
#define STR_RES_MIN 110  // min
#define STR_RES__XOR 111  // xor
#define STR_RES_GE 112  // >=
#define STR_RES_LE 113  // <=
#define STR_RES_CUTOFF 114  // cutoff
#define STR_RES__VCA 115  // vca
#define STR_RES_PWM1 116  // pwm1
#define STR_RES_PWM2 117  // pwm2
#define STR_RES_OSC1 118  // osc1
#define STR_RES_OSC2 119  // osc2
#define STR_RES_OSC1S2 120  // osc1+2
#define STR_RES_FINE 121  // fine
#define STR_RES__MIX 122  // mix
#define STR_RES_NOISE 123  // noise
#define STR_RES_SUBOSC 124  // subosc
#define STR_RES_RESO 125  // reso
#define STR_RES_CV_1 126  // cv 1
#define STR_RES_CV_2 127  // cv 2
#define STR_RES__ATTACK 128  // attack
#define STR_RES__LFO_1 129  // lfo 1
#define STR_RES__LFO_2 130  // lfo 2
#define STR_RES_DISTRT 131  // distrt
#define STR_RES_CRUSHR 132  // crushr
#define STR_RES_SCMBFL 133  // +cmbfl
#define STR_RES_CMBFL 134  // -cmbfl
#define STR_RES_RINGMD 135  // ringmd
#define STR_RES_DELAY 136  // delay
#define STR_RES_FB_DLY 137  // fb dly
#define STR_RES_DUBDLY 138  // dubdly
#define STR_RES__FBDLY 139  // !fbdly
#define STR_RES__DBDLY 140  // !dbdly
#define STR_RES__16_DL 141  // /16 dl
#define STR_RES__12_DL 142  // /12 dl
#define STR_RES__8_DLY 143  // /8 dly
#define STR_RES_3_16DL 144  // 3/16dl
#define STR_RES_LOOPER 145  // looper
#define STR_RES_PITCH 146  // pitch
#define STR_RES_LGF 147  // l>f
#define STR_RES_HGF 148  // h>f
#define STR_RES_FGL 149  // f>l
#define STR_RES_FGH 150  // f>h
#define STR_RES_GFX 151  // >fx
#define STR_RES_LF1 152  // lf1
#define STR_RES_LF2 153  // lf2
#define STR_RES_SEQ 154  // seq
#define STR_RES__SQ1 155  // sq1
#define STR_RES__SQ2 156  // sq2
#define STR_RES_ARP 157  // arp
#define STR_RES_WHL 158  // whl
#define STR_RES_AFT 159  // aft
#define STR_RES_BND 160  // bnd
#define STR_RES_OFS 161  // ofs
#define STR_RES__CV1 162  // cv1
#define STR_RES__CV2 163  // cv2
#define STR_RES_CV3 164  // cv3
#define STR_RES_CV4 165  // cv4
#define STR_RES_CCA 166  // ccA
#define STR_RES_CCB 167  // ccB
#define STR_RES_CCC 168  // ccC
#define STR_RES_CCD 169  // ccD
#define STR_RES__NOI 170  // noi
#define STR_RES_EN1 171  // en1
#define STR_RES_EN2 172  // en2
#define STR_RES_VEL 173  // vel
#define STR_RES_RND 174  // rnd
#define STR_RES_NOT 175  // not
#define STR_RES_GAT 176  // gat
#define STR_RES_AUD 177  // aud
#define STR_RES_OP1 178  // op1
#define STR_RES_OP2 179  // op2
#define STR_RES_LFO_1 180  // lfo 1
#define STR_RES_LFO_2 181  // lfo 2
#define STR_RES_STPSEQ 182  // stpseq
#define STR_RES_STPSQ1 183  // stpsq1
#define STR_RES_STPSQ2 184  // stpsq2
#define STR_RES__ARP 185  // arp
#define STR_RES_MWHEEL 186  // mwheel
#define STR_RES_AFTTCH 187  // afttch
#define STR_RES_BENDER 188  // bender
#define STR_RES_OFFSET 189  // offset
#define STR_RES__CV_1 190  // cv 1
#define STR_RES__CV_2 191  // cv 2
#define STR_RES_CV_3 192  // cv 3
#define STR_RES_CV_4 193  // cv 4
#define STR_RES_CC_A 194  // cc A
#define STR_RES_CC_B 195  // cc B
#define STR_RES_CC_C 196  // cc C
#define STR_RES_CC_D 197  // cc D
#define STR_RES__NOISE 198  // noise
#define STR_RES_ENV_1 199  // env 1
#define STR_RES_ENV_2 200  // env 2
#define STR_RES_VELO 201  // velo
#define STR_RES_RANDOM 202  // random
#define STR_RES_NOTE 203  // note
#define STR_RES_GATE 204  // gate
#define STR_RES_AUDIO 205  // audio
#define STR_RES_OP__1 206  // op. 1
#define STR_RES_OP__2 207  // op. 2
#define STR_RES_TOUCH_A_KNOB_TO 208  // touch a knob to
#define STR_RES_ASSIGN_PARAMETER 209  // assign parameter
#define STR_RES_PATCH 210  // patch
#define STR_RES_SEQUENCE 211  // sequence
#define STR_RES_COMBO 212  // combo
#define STR_RES_SAVE_MIDI_KBD 213  // save midi/kbd
#define STR_RES_SETTINGS_ 214  // settings?
#define STR_RES_START_FULL_MIDI 215  // start full midi
#define STR_RES_BACKUP_ 216  // backup?
#define STR_RES_BROWSE 217  // browse
#define STR_RES_SAVE 218  // save
#define STR_RES_COMPARE 219  // compare
#define STR_RES_ 220  // ----
#define STR_RES_V 221  // v
#define STR_RES_MUTABLE____V0_95 222  // mutable    v0.95
#define STR_RES_INSTRUMENTS_671 223  // instruments -1
#define STR_RES_EXTERN 224  // extern
#define STR_RES_X2_EXT 225  // x2 ext
#define STR_RES__2_EXT 226  // /2 ext
#define STR_RES__4_EXT 227  // /4 ext
#define STR_RES__8_EXT 228  // /8 ext
#define STR_RES_SUM 229  // sum
#define STR_RES_SYNC 230  // sync
#define STR_RES_RING 231  // ring
#define STR_RES_XOR 232  // xor
#define STR_RES_FUZZ 233  // fuzz
#define STR_RES_GG4 234  // >>4
#define STR_RES_GG8 235  // >>8
#define STR_RES_STP 236  // stp
#define STR_RES___ARP 237  // arp
#define STR_RES_ARPSLT 238  // arp+lt
#define STR_RES__SEQ 239  // seq
#define STR_RES_SEQSLT 240  // seq+lt
#define STR_RES_REC 241  // rec
#define STR_RES_IMPRO 242  // impro
#define STR_RES_FREE 243  // free
#define STR_RES_SLAVE 244  // slave
#define STR_RES_MASTER 245  // master
#define STR_RES_T 246  // ~
#define STR_RES__ 247  // 
#define STR_RES_T_ 248  // ~-
#define STR_RES__T_ 249  // ~
#define STR_RES_GLASS 250  // glass
#define STR_RES_KRAMA 251  // krama
#define STR_RES_JATA 252  // jata
#define STR_RES_SIKHA 253  // sikha
#define STR_RES_GHANA 254  // ghana
#define STR_RES_2GLASS 255  // 2glass
#define STR_RES_2KRAMA 256  // 2krama
#define STR_RES_2JATA 257  // 2jata
#define STR_RES_2SIKHA 258  // 2sikha
#define STR_RES_2GHANA 259  // 2ghana
#define STR_RES_4GLASS 260  // 4glass
#define STR_RES_4KRAMA 261  // 4krama
#define STR_RES_4JATA 262  // 4jata
#define STR_RES_4SIKHA 263  // 4sikha
#define STR_RES_4GHANA 264  // 4ghana
#define STR_RES_SWING 265  // swing
#define STR_RES_SHUFFLE 266  // shuffle
#define STR_RES_PUSH 267  // push
#define STR_RES_LAG 268  // lag
#define STR_RES_HUMAN 269  // human
#define STR_RES_MONKEY 270  // monkey
#define STR_RES__OFF 271  // off
#define STR_RES_THRU 272  // thru
#define STR_RES___SEQ 273  // seq
#define STR_RES_CTRL 274  // ctrl
#define STR_RES__SPLIT 275  // split
#define STR_RES_FULL 276  // full
#define STR_RES_1TV 277  // 1~|
#define STR_RES_2T1 278  // 2~1
#define STR_RES_3T2 279  // 3~2
#define STR_RES_4T3 280  // 4~3
#define STR_RES_5T4 281  // 5~4
#define STR_RES_6T5 282  // 6~5
#define STR_RES_7T6 283  // 7~6
#define STR_RES_8T7 284  // 8~7
#define STR_RES_TRI 285  // tri
#define STR_RES_SQR 286  // sqr
#define STR_RES_S_H 287  // s&h
#define STR_RES_RAMP 288  // ramp
#define STR_RES_STEP 289  // step
#define STR_RES_3 290  // 
#define STR_RES_4 291  // 
#define STR_RES_34 292  // 
#define STR_RES___ 293  // ?
#define STR_RES_OFF 294  // off
#define STR_RES_ON 295  // on
#define STR_RES_SQ1 296  // sq1
#define STR_RES_TR1 297  // tr1
#define STR_RES_PL1 298  // pl1
#define STR_RES_SQ2 299  // sq2
#define STR_RES_TR2 300  // tr2
#define STR_RES_PL2 301  // pl2
#define STR_RES_CLICK 302  // click
#define STR_RES_GLITCH 303  // glitch
#define STR_RES_BLOW 304  // blow
#define STR_RES_METAL 305  // metal
#define STR_RES_POP 306  // pop
#define STR_RES_NONE 307  // none
#define STR_RES_SAW 308  // saw
#define STR_RES_SQUARE 309  // square
#define STR_RES_TRIANG 310  // triang
#define STR_RES_ZSAW 311  // zsaw
#define STR_RES_ZRESO 312  // zreso
#define STR_RES_ZTRI 313  // ztri
#define STR_RES_ZPULSE 314  // zpulse
#define STR_RES_ZSYNC 315  // zsync
#define STR_RES_PAD 316  // pad
#define STR_RES_FM 317  // fm
#define STR_RES_WAVES 318  // waves
#define STR_RES_TAMPUR 319  // tampur
#define STR_RES_DIGITL 320  // digitl
#define STR_RES_METALL 321  // metall
#define STR_RES_BOWED 322  // bowed
#define STR_RES_SLAP 323  // slap
#define STR_RES_ORGAN 324  // organ
#define STR_RES_MALE 325  // male
#define STR_RES_USER 326  // user
#define STR_RES_8BITS 327  // 8bits
#define STR_RES_CRUSH 328  // crush
#define STR_RES_PWM 329  // pwm
#define STR_RES___NOISE 330  // noise
#define STR_RES_VOWEL 331  // vowel
#define STR_RES_BELISH 332  // belish
#define STR_RES_POLATD 333  // polatd
#define STR_RES_CELLO 334  // cello
#define STR_RES_CLPSWP 335  // clpswp
#define STR_RES_FEMALE 336  // female
#define STR_RES_FMTVOC 337  // fmtvoc
#define STR_RES_FRMNT2 338  // frmnt2
#define STR_RES_RES3HP 339  // res3hp
#define STR_RES_ELECTP 340  // electp
#define STR_RES_VIBES 341  // vibes
#define STR_RES__LPF 342  // lpf
#define STR_RES_SSM 343  // ssm
#define STR_RES_SVF 344  // svf
#define STR_RES_DSP 345  // dsp
#define STR_RES_PVK 346  // pvk
#define STR_RES_4CV_IN 347  // 4cv in
#define STR_RES_PRGM 348  // prgm
#define STR_RES_PEDALS 349  // pedals
#define STR_RES_EQUAL 350  // equal
#define STR_RES_JUST 351  // just
#define STR_RES_PYTHAG 352  // pythag
#define STR_RES_1_4_EB 353  // 1/4 eb
#define STR_RES_1_4_E 354  // 1/4 e
#define STR_RES_1_4_EA 355  // 1/4 ea
#define STR_RES_BHAIRA 356  // bhaira
#define STR_RES_GUNAKR 357  // gunakr
#define STR_RES_MARWA 358  // marwa
#define STR_RES_SHREE 359  // shree
#define STR_RES_PURVI 360  // purvi
#define STR_RES_BILAWA 361  // bilawa
#define STR_RES_YAMAN 362  // yaman
#define STR_RES_KAFI 363  // kafi
#define STR_RES_BHIMPA 364  // bhimpa
#define STR_RES_DARBAR 365  // darbar
#define STR_RES_BAGESH 366  // bagesh
#define STR_RES_RAGESH 367  // ragesh
#define STR_RES_KHAMAJ 368  // khamaj
#define STR_RES_MIMAL 369  // mi'mal
#define STR_RES_PARAME 370  // parame
#define STR_RES_RANGES 371  // ranges
#define STR_RES_GANGES 372  // ganges
#define STR_RES_KAMESH 373  // kamesh
#define STR_RES_PALAS_ 374  // palas
#define STR_RES_NATBHA 375  // natbha
#define STR_RES_M_KAUN 376  // m.kaun
#define STR_RES_BAIRAG 377  // bairag
#define STR_RES_B_TODI 378  // b.todi
#define STR_RES_CHANDR 379  // chandr
#define STR_RES_KAUSHI 380  // kaushi
#define STR_RES_JOGESH 381  // jogesh
#define STR_RES_RASIA 382  // rasia
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
