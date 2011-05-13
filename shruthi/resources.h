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
extern const prog_uint8_t wav_res_bandlimited_square_0[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_square_1[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_square_2[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_square_3[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_square_4[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_square_5[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_square_6[] PROGMEM;
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
#define STR_RES_LENGTH 37  // length
#define STR_RES_OCTAVE 38  // octave
#define STR_RES_RAGA 39  // raga
#define STR_RES_PORTA 40  // porta
#define STR_RES_PRT 41  // prt
#define STR_RES_LEGATO 42  // legato
#define STR_RES_TUNING 43  // tuning
#define STR_RES_MIDI_CHAN 44  // midi chan
#define STR_RES_CHN 45  // chn
#define STR_RES_MIDI_OUT 46  // midi out
#define STR_RES_PAUSE 47  // pause
#define STR_RES_SNAP 48  // snap
#define STR_RES_CV_MODE 49  // cv.mode
#define STR_RES_OSCILLATOR_1 50  // oscillator 1
#define STR_RES_OSCILLATOR_2 51  // oscillator 2
#define STR_RES_MIXER 52  // mixer
#define STR_RES_FILTER 53  // filter
#define STR_RES_FILTERS 54  // filter+
#define STR_RES_MODE_1 55  // mode 1
#define STR_RES_MODE_2 56  // mode 2
#define STR_RES_MD1 57  // md1
#define STR_RES_MD2 58  // md2
#define STR_RES_ENVELOPE_1 59  // envelope 1
#define STR_RES_ENVELOPE_2 60  // envelope 2
#define STR_RES_SEQUENCER 61  // sequencer
#define STR_RES_ARPEGGIO 62  // arpeggio
#define STR_RES_STEP_SEQUENCER 63  // step sequencer
#define STR_RES_KEYBOARD 64  // keyboard
#define STR_RES_MIDI 65  // midi
#define STR_RES_SYSTEM 66  // system
#define STR_RES_PERFORMANCE 67  // performance
#define STR_RES_PARAM__1 68  // param. 1
#define STR_RES_PARAM__2 69  // param. 2
#define STR_RES_PR1 70  // pr1
#define STR_RES_PR2 71  // pr2
#define STR_RES_FX_ 72  // fx.
#define STR_RES_FX_PROG_ 73  // fx prog.
#define STR_RES_LPF 74  // lpf
#define STR_RES_BPF 75  // bpf
#define STR_RES_HPF 76  // hpf
#define STR_RES_SLP 77  // +lp
#define STR_RES_SBP 78  // +bp
#define STR_RES_SHP 79  // +hp
#define STR_RES_GLP 80  // >lp
#define STR_RES_GBP 81  // >bp
#define STR_RES_GHP 82  // >hp
#define STR_RES_CUT 83  // cut
#define STR_RES_VCA 84  // vca
#define STR_RES_PW1 85  // pw1
#define STR_RES_PW2 86  // pw2
#define STR_RES_51 87  // 1
#define STR_RES_52 88  // 2
#define STR_RES_5 89  // 
#define STR_RES_5F 90  // f
#define STR_RES_MIX 91  // mix
#define STR_RES_NOI 92  // noi
#define STR_RES_SUB 93  // sub
#define STR_RES_RES 94  // res
#define STR_RES__CV1 95  //  cv1
#define STR_RES__CV2 96  //  cv2
#define STR_RES__ATK 97  //  atk
#define STR_RES__LF1 98  //  lf1
#define STR_RES__LF2 99  //  lf2
#define STR_RES_IN1 100  // in1
#define STR_RES_IN2 101  // in2
#define STR_RES_OUT 102  // out
#define STR_RES___OFF 103  //   off
#define STR_RES_ADD 104  // add
#define STR_RES_PRD 105  // prd
#define STR_RES_MAX 106  // max
#define STR_RES_MIN 107  // min
#define STR_RES__XOR 108  //  xor
#define STR_RES_GE 109  // >=
#define STR_RES_LE 110  // <=
#define STR_RES_CUTOFF 111  // cutoff
#define STR_RES__VCA 112  //  vca
#define STR_RES_PWM1 113  // pwm1
#define STR_RES_PWM2 114  // pwm2
#define STR_RES_OSC1 115  // osc1
#define STR_RES_OSC2 116  // osc2
#define STR_RES_OSC1S2 117  // osc1+2
#define STR_RES_FINE 118  // fine
#define STR_RES__MIX 119  //  mix
#define STR_RES_NOISE 120  // noise
#define STR_RES_SUBOSC 121  // subosc
#define STR_RES_RESO 122  // reso
#define STR_RES__CV_1 123  //  cv 1
#define STR_RES__CV_2 124  //  cv 2
#define STR_RES__ATTACK 125  //  attack
#define STR_RES__LFO_1 126  //  lfo 1
#define STR_RES__LFO_2 127  //  lfo 2
#define STR_RES__NONE 128  //  none
#define STR_RES_DISTRT 129  // distrt
#define STR_RES_CRUSHR 130  // crushr
#define STR_RES_COMBFL 131  // combfl
#define STR_RES_RINGMD 132  // ringmd
#define STR_RES_DELAY 133  // delay
#define STR_RES_FB_DLY 134  // fb dly
#define STR_RES_DUBDLY 135  // dubdly
#define STR_RES_1_4_DL 136  // 1/4 dl
#define STR_RES_1_3_DL 137  // 1/3 dl
#define STR_RES_1_2_DL 138  // 1/2 dl
#define STR_RES_3_4_DL 139  // 3/4 dl
#define STR_RES_1_1_DL 140  // 1/1 dl
#define STR_RES_FLANGE 141  // flange
#define STR_RES_SPACER 142  // spacer
#define STR_RES_WEIRDO 143  // weirdo
#define STR_RES_LF1 144  // lf1
#define STR_RES_LF2 145  // lf2
#define STR_RES_SEQ 146  // seq
#define STR_RES__SQ1 147  //  sq1
#define STR_RES__SQ2 148  //  sq2
#define STR_RES__ARP 149  //  arp
#define STR_RES_WHL 150  // whl
#define STR_RES_AFT 151  // aft
#define STR_RES_BND 152  // bnd
#define STR_RES_OFS 153  // ofs
#define STR_RES_CV1 154  // cv1
#define STR_RES_CV2 155  // cv2
#define STR_RES_CV3 156  // cv3
#define STR_RES_CV4 157  // cv4
#define STR_RES_CCA 158  // ccA
#define STR_RES_CCB 159  // ccB
#define STR_RES_CCC 160  // ccC
#define STR_RES_CCD 161  // ccD
#define STR_RES__NOI 162  //  noi
#define STR_RES_EN1 163  // en1
#define STR_RES_EN2 164  // en2
#define STR_RES_VEL 165  // vel
#define STR_RES_RND 166  // rnd
#define STR_RES_NOT 167  // not
#define STR_RES_GAT 168  // gat
#define STR_RES_AUD 169  // aud
#define STR_RES_OP1 170  // op1
#define STR_RES_OP2 171  // op2
#define STR_RES_LFO_1 172  // lfo 1
#define STR_RES_LFO_2 173  // lfo 2
#define STR_RES_STPSEQ 174  // stpseq
#define STR_RES_STPSQ1 175  // stpsq1
#define STR_RES_STPSQ2 176  // stpsq2
#define STR_RES___ARP 177  //   arp
#define STR_RES_MWHEEL 178  // mwheel
#define STR_RES_AFTTCH 179  // afttch
#define STR_RES_BENDER 180  // bender
#define STR_RES_OFFSET 181  // offset
#define STR_RES_CV_1 182  // cv 1
#define STR_RES_CV_2 183  // cv 2
#define STR_RES_CV_3 184  // cv 3
#define STR_RES_CV_4 185  // cv 4
#define STR_RES_CC_A 186  // cc A
#define STR_RES_CC_B 187  // cc B
#define STR_RES_CC_C 188  // cc C
#define STR_RES_CC_D 189  // cc D
#define STR_RES___NOISE 190  //   noise
#define STR_RES_ENV_1 191  // env 1
#define STR_RES_ENV_2 192  // env 2
#define STR_RES_VELO 193  // velo
#define STR_RES_RANDOM 194  // random
#define STR_RES_NOTE 195  // note
#define STR_RES_GATE 196  // gate
#define STR_RES_AUDIO 197  // audio
#define STR_RES_OP__1 198  // op. 1
#define STR_RES_OP__2 199  // op. 2
#define STR_RES_TOUCH_A_KNOB_TO 200  // touch a knob to
#define STR_RES_ASSIGN_PARAMETER 201  // assign parameter
#define STR_RES_PATCH 202  // patch
#define STR_RES_SEQUENCE 203  // sequence
#define STR_RES_COMBO 204  // combo
#define STR_RES_SAVE_MIDI_KBD 205  // save midi/kbd
#define STR_RES_SETTINGS_ 206  // settings?
#define STR_RES_START_FULL_MIDI 207  // start full midi
#define STR_RES_BACKUP_ 208  // backup?
#define STR_RES_BROWSE 209  // browse
#define STR_RES_SAVE 210  // save
#define STR_RES_COMPARE 211  // compare
#define STR_RES_ 212  // ----
#define STR_RES_V 213  // v
#define STR_RES_MUTABLE____V0_93 214  // mutable    v0.93
#define STR_RES_INSTRUMENTS_671 215  // instruments -1
#define STR_RES_EXTERN 216  // extern
#define STR_RES_X2_EXT 217  // x2 ext
#define STR_RES__2_EXT 218  // /2 ext
#define STR_RES__4_EXT 219  // /4 ext
#define STR_RES__8_EXT 220  // /8 ext
#define STR_RES_SUM 221  // sum
#define STR_RES_SYNC 222  // sync
#define STR_RES_RING 223  // ring
#define STR_RES_XOR 224  // xor
#define STR_RES_FUZZ 225  // fuzz
#define STR_RES_GG4 226  // >>4
#define STR_RES_GG8 227  // >>8
#define STR_RES_STP 228  // stp
#define STR_RES_ARP 229  // arp
#define STR_RES_ARPSLT 230  // arp+lt
#define STR_RES__SEQ 231  //  seq
#define STR_RES_SEQSLT 232  // seq+lt
#define STR_RES_REC 233  // rec
#define STR_RES_IMPRO 234  // impro
#define STR_RES_FREE 235  // free
#define STR_RES_SLAVE 236  // slave
#define STR_RES_MASTER 237  // master
#define STR_RES_T 238  // ~
#define STR_RES___ 239  //  
#define STR_RES_T_ 240  // ~-
#define STR_RES__T_ 241  //  ~
#define STR_RES_GLASS 242  // glass
#define STR_RES_KRAMA 243  // krama
#define STR_RES_JATA 244  // jata
#define STR_RES_SIKHA 245  // sikha
#define STR_RES_GHANA 246  // ghana
#define STR_RES_2GLASS 247  // 2glass
#define STR_RES_2KRAMA 248  // 2krama
#define STR_RES_2JATA 249  // 2jata
#define STR_RES_2SIKHA 250  // 2sikha
#define STR_RES_2GHANA 251  // 2ghana
#define STR_RES_4GLASS 252  // 4glass
#define STR_RES_4KRAMA 253  // 4krama
#define STR_RES_4JATA 254  // 4jata
#define STR_RES_4SIKHA 255  // 4sikha
#define STR_RES_4GHANA 256  // 4ghana
#define STR_RES_SWING 257  // swing
#define STR_RES_SHUFFLE 258  // shuffle
#define STR_RES_PUSH 259  // push
#define STR_RES_LAG 260  // lag
#define STR_RES_HUMAN 261  // human
#define STR_RES_MONKEY 262  // monkey
#define STR_RES__OFF 263  //  off
#define STR_RES_THRU 264  // thru
#define STR_RES___SEQ 265  //   seq
#define STR_RES_CTRL 266  // ctrl
#define STR_RES_SPLIT 267  // split
#define STR_RES_FULL 268  // full
#define STR_RES_1TV 269  // 1~|
#define STR_RES_2T1 270  // 2~1
#define STR_RES_3T2 271  // 3~2
#define STR_RES_4T3 272  // 4~3
#define STR_RES_5T4 273  // 5~4
#define STR_RES_6T5 274  // 6~5
#define STR_RES_7T6 275  // 7~6
#define STR_RES_8T7 276  // 8~7
#define STR_RES_TRI 277  // tri
#define STR_RES_SQR 278  // sqr
#define STR_RES_S_H 279  // s&h
#define STR_RES_RAMP 280  // ramp
#define STR_RES_STEP 281  // step
#define STR_RES_3 282  // 
#define STR_RES_4 283  // 
#define STR_RES_34 284  // 
#define STR_RES__ 285  // ?
#define STR_RES_OFF 286  // off
#define STR_RES_ON 287  // on
#define STR_RES_SQ1 288  // sq1
#define STR_RES_TR1 289  // tr1
#define STR_RES_PL1 290  // pl1
#define STR_RES_SQ2 291  // sq2
#define STR_RES_TR2 292  // tr2
#define STR_RES_PL2 293  // pl2
#define STR_RES_CLICK 294  // click
#define STR_RES_GLITCH 295  // glitch
#define STR_RES_BLOW 296  // blow
#define STR_RES_METAL 297  // metal
#define STR_RES_POP 298  // pop
#define STR_RES_NONE 299  // none
#define STR_RES_SAW 300  // saw
#define STR_RES_SQUARE 301  // square
#define STR_RES_TRIANG 302  // triang
#define STR_RES_ZSAW 303  // zsaw
#define STR_RES_ZRESO 304  // zreso
#define STR_RES_ZTRI 305  // ztri
#define STR_RES_ZPULSE 306  // zpulse
#define STR_RES_ZSYNC 307  // zsync
#define STR_RES_PAD 308  // pad
#define STR_RES_FM 309  // fm
#define STR_RES_WAVES 310  // waves
#define STR_RES_TAMPUR 311  // tampur
#define STR_RES_DIGITL 312  // digitl
#define STR_RES_METALL 313  // metall
#define STR_RES_BOWED 314  // bowed
#define STR_RES_SLAP 315  // slap
#define STR_RES_ORGAN 316  // organ
#define STR_RES_MALE 317  // male
#define STR_RES_USER 318  // user
#define STR_RES_8BITS 319  // 8bits
#define STR_RES_CRUSH 320  // crush
#define STR_RES_PWM 321  // pwm
#define STR_RES__NOISE 322  //  noise
#define STR_RES_VOWEL 323  // vowel
#define STR_RES_BELISH 324  // belish
#define STR_RES_POLATD 325  // polatd
#define STR_RES_CELLO 326  // cello
#define STR_RES_CLPSWP 327  // clpswp
#define STR_RES_FEMALE 328  // female
#define STR_RES_FMTVOC 329  // fmtvoc
#define STR_RES_FRMNT2 330  // frmnt2
#define STR_RES_RES3HP 331  // res3hp
#define STR_RES_ELECTP 332  // electp
#define STR_RES_VIBES 333  // vibes
#define STR_RES__LPF 334  //  lpf
#define STR_RES_SSM 335  // ssm
#define STR_RES_SVF 336  // svf
#define STR_RES_DSP 337  // dsp
#define STR_RES_4CV_IN 338  // 4cv in
#define STR_RES_PRGM 339  // prgm
#define STR_RES_PEDALS 340  // pedals
#define STR_RES_EQUAL 341  // equal
#define STR_RES_JUST 342  // just
#define STR_RES_PYTHAG 343  // pythag
#define STR_RES_1_4_EB 344  // 1/4 eb
#define STR_RES_1_4_E 345  // 1/4 e
#define STR_RES_1_4_EA 346  // 1/4 ea
#define STR_RES_BHAIRA 347  // bhaira
#define STR_RES_GUNAKR 348  // gunakr
#define STR_RES_MARWA 349  // marwa
#define STR_RES_SHREE 350  // shree
#define STR_RES_PURVI 351  // purvi
#define STR_RES_BILAWA 352  // bilawa
#define STR_RES_YAMAN 353  // yaman
#define STR_RES_KAFI 354  // kafi
#define STR_RES_BHIMPA 355  // bhimpa
#define STR_RES_DARBAR 356  // darbar
#define STR_RES_BAGESH 357  // bagesh
#define STR_RES_RAGESH 358  // ragesh
#define STR_RES_KHAMAJ 359  // khamaj
#define STR_RES_MIMAL 360  // mi'mal
#define STR_RES_PARAME 361  // parame
#define STR_RES_RANGES 362  // ranges
#define STR_RES_GANGES 363  // ganges
#define STR_RES_KAMESH 364  // kamesh
#define STR_RES_PALAS_ 365  // palas 
#define STR_RES_NATBHA 366  // natbha
#define STR_RES_M_KAUN 367  // m.kaun
#define STR_RES_BAIRAG 368  // bairag
#define STR_RES_B_TODI 369  // b.todi
#define STR_RES_CHANDR 370  // chandr
#define STR_RES_KAUSHI 371  // kaushi
#define STR_RES_JOGESH 372  // jogesh
#define STR_RES_RASIA 373  // rasia
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
#define WAV_RES_BANDLIMITED_SQUARE_0 2
#define WAV_RES_BANDLIMITED_SQUARE_0_SIZE 257
#define WAV_RES_BANDLIMITED_SQUARE_1 3
#define WAV_RES_BANDLIMITED_SQUARE_1_SIZE 257
#define WAV_RES_BANDLIMITED_SQUARE_2 4
#define WAV_RES_BANDLIMITED_SQUARE_2_SIZE 257
#define WAV_RES_BANDLIMITED_SQUARE_3 5
#define WAV_RES_BANDLIMITED_SQUARE_3_SIZE 257
#define WAV_RES_BANDLIMITED_SQUARE_4 6
#define WAV_RES_BANDLIMITED_SQUARE_4_SIZE 257
#define WAV_RES_BANDLIMITED_SQUARE_5 7
#define WAV_RES_BANDLIMITED_SQUARE_5_SIZE 257
#define WAV_RES_BANDLIMITED_SQUARE_6 8
#define WAV_RES_BANDLIMITED_SQUARE_6_SIZE 257
#define WAV_RES_BANDLIMITED_SAW_0 9
#define WAV_RES_BANDLIMITED_SAW_0_SIZE 257
#define WAV_RES_BANDLIMITED_SAW_1 10
#define WAV_RES_BANDLIMITED_SAW_1_SIZE 257
#define WAV_RES_BANDLIMITED_SAW_2 11
#define WAV_RES_BANDLIMITED_SAW_2_SIZE 257
#define WAV_RES_BANDLIMITED_SAW_3 12
#define WAV_RES_BANDLIMITED_SAW_3_SIZE 257
#define WAV_RES_BANDLIMITED_SAW_4 13
#define WAV_RES_BANDLIMITED_SAW_4_SIZE 257
#define WAV_RES_BANDLIMITED_SAW_5 14
#define WAV_RES_BANDLIMITED_SAW_5_SIZE 257
#define WAV_RES_BANDLIMITED_SAW_6 15
#define WAV_RES_BANDLIMITED_SAW_6_SIZE 257
#define WAV_RES_BANDLIMITED_TRIANGLE_0 16
#define WAV_RES_BANDLIMITED_TRIANGLE_0_SIZE 257
#define WAV_RES_BANDLIMITED_TRIANGLE_1 17
#define WAV_RES_BANDLIMITED_TRIANGLE_1_SIZE 257
#define WAV_RES_BANDLIMITED_TRIANGLE_2 18
#define WAV_RES_BANDLIMITED_TRIANGLE_2_SIZE 257
#define WAV_RES_BANDLIMITED_TRIANGLE_3 19
#define WAV_RES_BANDLIMITED_TRIANGLE_3_SIZE 257
#define WAV_RES_BANDLIMITED_TRIANGLE_4 20
#define WAV_RES_BANDLIMITED_TRIANGLE_4_SIZE 257
#define WAV_RES_BANDLIMITED_TRIANGLE_5 21
#define WAV_RES_BANDLIMITED_TRIANGLE_5_SIZE 257
#define WAV_RES_BANDLIMITED_TRIANGLE_6 22
#define WAV_RES_BANDLIMITED_TRIANGLE_6_SIZE 257
#define WAV_RES_VOWEL_DATA 23
#define WAV_RES_VOWEL_DATA_SIZE 45
#define WAV_RES_EXPANSION_KRAMA 24
#define WAV_RES_EXPANSION_KRAMA_SIZE 30
#define WAV_RES_EXPANSION_JATA 25
#define WAV_RES_EXPANSION_JATA_SIZE 90
#define WAV_RES_EXPANSION_SIKHA 26
#define WAV_RES_EXPANSION_SIKHA_SIZE 126
#define WAV_RES_EXPANSION_GHANA 27
#define WAV_RES_EXPANSION_GHANA_SIZE 182
#define WAV_RES_DISTORTION 28
#define WAV_RES_DISTORTION_SIZE 256
#define WAV_RES_WAVES 29
#define WAV_RES_WAVES_SIZE 16512
#define WAV_RES_WAVETABLES 30
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
