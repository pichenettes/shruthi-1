// Copyright 2009 Emilie Gillet.
//
// Author: Emilie Gillet (emilie.o.gillet@gmail.com)
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

extern const prog_char* const string_table[];

extern const prog_uint16_t* const lookup_table_table[];

extern const prog_uint32_t* const lookup_table32_table[];

extern const prog_uint8_t* const waveform_table[];

extern const prog_uint8_t* const character_table[];

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
extern const prog_uint16_t lut_res_groove_swing[] PROGMEM;
extern const prog_uint16_t lut_res_groove_shuffle[] PROGMEM;
extern const prog_uint16_t lut_res_groove_push[] PROGMEM;
extern const prog_uint16_t lut_res_groove_lag[] PROGMEM;
extern const prog_uint16_t lut_res_groove_human[] PROGMEM;
extern const prog_uint16_t lut_res_groove_monkey[] PROGMEM;
extern const prog_uint32_t lut_res_tempo_phase_increment[] PROGMEM;
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
extern const prog_uint8_t wav_res_distortion[] PROGMEM;
extern const prog_uint8_t wav_res_env_expo[] PROGMEM;
extern const prog_uint8_t wav_res_ssm2164_linearization[] PROGMEM;
extern const prog_uint8_t wav_res_waves[] PROGMEM;
extern const prog_uint8_t wav_res_wavetables[] PROGMEM;
extern const prog_uint8_t wav_res_version[] PROGMEM;
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
#define STR_RES_DIVISION 43  // division
#define STR_RES_START 44  // start
#define STR_RES_LENGTH 45  // length
#define STR_RES_OCTAVE 46  // octave
#define STR_RES_RAGA 47  // raga
#define STR_RES_PORTA 48  // porta
#define STR_RES_PRT 49  // prt
#define STR_RES_LEGATO 50  // legato
#define STR_RES_TUNING 51  // tuning
#define STR_RES_MIDI_CHAN 52  // midi chan
#define STR_RES_CHN 53  // chn
#define STR_RES_MIDI_OUT 54  // midi out
#define STR_RES_PAUSE 55  // pause
#define STR_RES_STARTPAGE 56  // startpage
#define STR_RES_SNAP 57  // snap
#define STR_RES_OSCILLATOR_1 58  // oscillator 1
#define STR_RES_OSCILLATOR_2 59  // oscillator 2
#define STR_RES_MIXER 60  // mixer
#define STR_RES_FILTER 61  // filter
#define STR_RES_FILTERS 62  // filter+
#define STR_RES_MODE_1 63  // mode 1
#define STR_RES_MODE_2 64  // mode 2
#define STR_RES_MD1 65  // md1
#define STR_RES_MD2 66  // md2
#define STR_RES_ENVELOPE_1 67  // envelope 1
#define STR_RES_ENVELOPE_2 68  // envelope 2
#define STR_RES_SEQUENCER 69  // sequencer
#define STR_RES_ARPEGGIO 70  // arpeggio
#define STR_RES_CH1 71  // ch1
#define STR_RES_CH2 72  // ch2
#define STR_RES_11 73  // 1
#define STR_RES_12 74  // 2
#define STR_RES_STEP_SEQUENCER 75  // step sequencer
#define STR_RES_KEYBOARD 76  // keyboard
#define STR_RES_MIDI 77  // midi
#define STR_RES_SYSTEM 78  // system
#define STR_RES_PERFORMANCE 79  // performance
#define STR_RES_PARAM__1 80  // param. 1
#define STR_RES_PARAM__2 81  // param. 2
#define STR_RES_PR1 82  // pr1
#define STR_RES_PR2 83  // pr2
#define STR_RES_FX_ 84  // fx.
#define STR_RES_FX_PROG_ 85  // fx prog.
#define STR_RES_LPF 86  // lpf
#define STR_RES_BPF 87  // bpf
#define STR_RES_HPF 88  // hpf
#define STR_RES_LPL 89  // lp<
#define STR_RES_BPL 90  // bp<
#define STR_RES_HPL 91  // hp<
#define STR_RES_SLP 92  // +lp
#define STR_RES_SBP 93  // +bp
#define STR_RES_SHP 94  // +hp
#define STR_RES_GLP 95  // >lp
#define STR_RES_GBP 96  // >bp
#define STR_RES_GHP 97  // >hp
#define STR_RES_LP4 98  // lp4
#define STR_RES_LP3 99  // lp3
#define STR_RES_LP2 100  // lp2
#define STR_RES_LP1 101  // lp1
#define STR_RES_HP1 102  // hp1
#define STR_RES_HP2 103  // hp2
#define STR_RES_HP3 104  // hp3
#define STR_RES_BP2 105  // bp2
#define STR_RES_BP4 106  // bp4
#define STR_RES_NOTCH 107  // notch
#define STR_RES_PHASER 108  // phaser
#define STR_RES_H2LP 109  // h2lp
#define STR_RES_H3LP 110  // h3lp
#define STR_RES_NSLP 111  // n+lp
#define STR_RES_PSLP 112  // p+lp
#define STR_RES_LP 113  // lp
#define STR_RES_BP 114  // bp
#define STR_RES_HP 115  // hp
#define STR_RES_AP 116  // ap
#define STR_RES_LIQUID 117  // liquid
#define STR_RES_MS 118  // ms
#define STR_RES_WOBBLY 119  // wobbly
#define STR_RES_WHACKY 120  // whacky
#define STR_RES_PW1 121  // pw1
#define STR_RES_PW2 122  // pw2
#define STR_RES_51 123  // 1
#define STR_RES_52 124  // 2
#define STR_RES_5 125  // 
#define STR_RES_5F 126  // f
#define STR_RES_MIX 127  // mix
#define STR_RES_NOI 128  // noi
#define STR_RES_SUB 129  // sub
#define STR_RES_CUT 130  // cut
#define STR_RES_RES 131  // res
#define STR_RES_VCA 132  // vca
#define STR_RES_CV1 133  // cv1
#define STR_RES_CV2 134  // cv2
#define STR_RES_TR1 135  // tr1
#define STR_RES_A1 136  // a1
#define STR_RES_D1 137  // d1
#define STR_RES_S1 138  // s1
#define STR_RES_R1 139  // r1
#define STR_RES_TR2 140  // tr2
#define STR_RES_A2 141  // a2
#define STR_RES_D2 142  // d2
#define STR_RES_S2 143  // s2
#define STR_RES_R2 144  // r2
#define STR_RES__ATK 145  // atk
#define STR_RES__LF1 146  // lf1
#define STR_RES__LF2 147  // lf2
#define STR_RES_IN1 148  // in1
#define STR_RES_IN2 149  // in2
#define STR_RES_OUT 150  // out
#define STR_RES___OFF 151  // off
#define STR_RES_ADD 152  // add
#define STR_RES_PRD 153  // prd
#define STR_RES_MAX 154  // max
#define STR_RES_MIN 155  // min
#define STR_RES__XOR 156  // xor
#define STR_RES_GE 157  // >=
#define STR_RES_LE 158  // <=
#define STR_RES_QTZ 159  // qtz
#define STR_RES_LAG 160  // lag
#define STR_RES_PWM1 161  // pwm1
#define STR_RES_PWM2 162  // pwm2
#define STR_RES_OSC1 163  // osc1
#define STR_RES_OSC2 164  // osc2
#define STR_RES_OSC1S2 165  // osc1+2
#define STR_RES_FINE 166  // fine
#define STR_RES__MIX 167  // mix
#define STR_RES_NOISE 168  // noise
#define STR_RES_SUBOSC 169  // subosc
#define STR_RES_CUTOFF 170  // cutoff
#define STR_RES_RESO 171  // reso
#define STR_RES__VCA 172  // vca
#define STR_RES_CV_1 173  // cv 1
#define STR_RES_CV_2 174  // cv 2
#define STR_RES_TRG_E1 175  // trg e1
#define STR_RES_ATK__1 176  // atk. 1
#define STR_RES_DEC__1 177  // dec. 1
#define STR_RES_SUS__1 178  // sus. 1
#define STR_RES_REL__1 179  // rel. 1
#define STR_RES_TRG_E2 180  // trg e2
#define STR_RES_ATK__2 181  // atk. 2
#define STR_RES_DEC__2 182  // dec. 2
#define STR_RES_SUS__2 183  // sus. 2
#define STR_RES_REL__2 184  // rel. 2
#define STR_RES_ATK1S2 185  // atk1+2
#define STR_RES__LFO_1 186  // lfo 1
#define STR_RES__LFO_2 187  // lfo 2
#define STR_RES_DISTRT 188  // distrt
#define STR_RES_CRUSHR 189  // crushr
#define STR_RES_SCMBFL 190  // +cmbfl
#define STR_RES_CMBFL 191  // -cmbfl
#define STR_RES_RINGMD 192  // ringmd
#define STR_RES_DELAY 193  // delay
#define STR_RES_FB_DLY 194  // fb dly
#define STR_RES_DUBDLY 195  // dubdly
#define STR_RES__FBDLY 196  // !fbdly
#define STR_RES__DBDLY 197  // !dbdly
#define STR_RES__16_DL 198  // /16 dl
#define STR_RES__12_DL 199  // /12 dl
#define STR_RES__8_DLY 200  // /8 dly
#define STR_RES_3_16DL 201  // 3/16dl
#define STR_RES_LOOPER 202  // looper
#define STR_RES_PITCH 203  // pitch
#define STR_RES_LGF 204  // l>f
#define STR_RES_HGF 205  // h>f
#define STR_RES_FGL 206  // f>l
#define STR_RES_FGH 207  // f>h
#define STR_RES_GFX 208  // >fx
#define STR_RES_LF1 209  // lf1
#define STR_RES_LF2 210  // lf2
#define STR_RES_SEQ 211  // seq
#define STR_RES__SQ1 212  // sq1
#define STR_RES__SQ2 213  // sq2
#define STR_RES_ARP 214  // arp
#define STR_RES_WHL 215  // whl
#define STR_RES_AFT 216  // aft
#define STR_RES_BND 217  // bnd
#define STR_RES_OFS 218  // ofs
#define STR_RES__CV1 219  // cv1
#define STR_RES__CV2 220  // cv2
#define STR_RES_CV3 221  // cv3
#define STR_RES_CV4 222  // cv4
#define STR_RES_CCA 223  // ccA
#define STR_RES_CCB 224  // ccB
#define STR_RES_BRE 225  // bre
#define STR_RES_PED 226  // ped
#define STR_RES__NOI 227  // noi
#define STR_RES_EN1 228  // en1
#define STR_RES_EN2 229  // en2
#define STR_RES_VEL 230  // vel
#define STR_RES_RND 231  // rnd
#define STR_RES_NOT 232  // not
#define STR_RES_GAT 233  // gat
#define STR_RES_AUD 234  // aud
#define STR_RES_OP1 235  // op1
#define STR_RES_OP2 236  // op2
#define STR_RES_E4 237  // =4
#define STR_RES_E8 238  // =8
#define STR_RES_E16 239  // =16
#define STR_RES_E32 240  // =32
#define STR_RES_LFO_1 241  // lfo 1
#define STR_RES_LFO_2 242  // lfo 2
#define STR_RES_STPSEQ 243  // stpseq
#define STR_RES_STPSQ1 244  // stpsq1
#define STR_RES_STPSQ2 245  // stpsq2
#define STR_RES__ARP 246  // arp
#define STR_RES_MWHEEL 247  // mwheel
#define STR_RES_AFTTCH 248  // afttch
#define STR_RES_BENDER 249  // bender
#define STR_RES_OFFSET 250  // offset
#define STR_RES__CV_1 251  // cv 1
#define STR_RES__CV_2 252  // cv 2
#define STR_RES_CV_3 253  // cv 3
#define STR_RES_CV_4 254  // cv 4
#define STR_RES_CC_A 255  // cc A
#define STR_RES_CC_B 256  // cc B
#define STR_RES_BREATH 257  // breath
#define STR_RES_PEDAL 258  // pedal
#define STR_RES__NOISE 259  // noise
#define STR_RES_ENV_1 260  // env 1
#define STR_RES_ENV_2 261  // env 2
#define STR_RES_VELO 262  // velo
#define STR_RES_RANDOM 263  // random
#define STR_RES_NOTE 264  // note
#define STR_RES_GATE 265  // gate
#define STR_RES_AUDIO 266  // audio
#define STR_RES_OP__1 267  // op. 1
#define STR_RES_OP__2 268  // op. 2
#define STR_RES_E_4 269  // = 4
#define STR_RES_E_8 270  // = 8
#define STR_RES_E_16 271  // = 16
#define STR_RES_E_32 272  // = 32
#define STR_RES_PATCH 273  // patch
#define STR_RES_SEQUENCE 274  // sequence
#define STR_RES_SAVE_MIDI_KBD 275  // save midi/kbd
#define STR_RES_SETTINGS_ 276  // settings?
#define STR_RES_START_FULL_MIDI 277  // start full midi
#define STR_RES_BACKUP_ 278  // backup?
#define STR_RES_BROWSE 279  // browse
#define STR_RES_SAVE 280  // save
#define STR_RES_COMPARE 281  // compare
#define STR_RES_ 282  // ----
#define STR_RES_V 283  // v
#define STR_RES_671____SN__4370 284  // -1    SN #4370
#define STR_RES_V1_03 285  // v1.03
#define STR_RES_SHRUTHI_CLASSIC 286  // shruthi classic
#define STR_RES_4_KNOBS 287  // (4 knobs)
#define STR_RES_SHRUTHI_XT 288  // shruthi xt
#define STR_RES_CLASSIC_FCD72 289  // classic (fcd72)
#define STR_RES__SHRUTHI_XT 290  // shruthi xt
#define STR_RES_FULL_CONTROL 291  // (full control)
#define STR_RES_LETS_JAM_ 292  // let's jam!
#define STR_RES_EXTERN 293  // extern
#define STR_RES_SUM 294  // sum
#define STR_RES_SYNC 295  // sync
#define STR_RES_RING 296  // ring
#define STR_RES_XOR 297  // xor
#define STR_RES_FUZZ 298  // fuzz
#define STR_RES_GG4 299  // >>4
#define STR_RES_GG8 300  // >>8
#define STR_RES_FOLD 301  // fold
#define STR_RES_BITS 302  // bits
#define STR_RES_DUO 303  // duo
#define STR_RES_2STEPS 304  // 2steps
#define STR_RES_4STEPS 305  // 4steps
#define STR_RES_8STEPS 306  // 8steps
#define STR_RES_SEQMIX 307  // seqmix
#define STR_RES_STP 308  // stp
#define STR_RES___ARP 309  // arp
#define STR_RES__SEQ 310  // seq
#define STR_RES_FREE 311  // free
#define STR_RES_SLAVE 312  // slave
#define STR_RES_MASTER 313  // master
#define STR_RES_1SHOT 314  // 1shot
#define STR_RES_1_1 315  // 1/1
#define STR_RES_1_2 316  // 1/2
#define STR_RES_1_3 317  // 1/3
#define STR_RES_1_4 318  // 1/4
#define STR_RES_1_6 319  // 1/6
#define STR_RES_1_8 320  // 1/8
#define STR_RES__12 321  // /12
#define STR_RES__16 322  // /16
#define STR_RES__24 323  // /24
#define STR_RES__32 324  // /32
#define STR_RES__48 325  // /48
#define STR_RES__96 326  // /96
#define STR_RES_SWING 327  // swing
#define STR_RES_SHUFFLE 328  // shuffle
#define STR_RES_PUSH 329  // push
#define STR_RES__LAG 330  // lag
#define STR_RES_HUMAN 331  // human
#define STR_RES_MONKEY 332  // monkey
#define STR_RES__OFF 333  // off
#define STR_RES_THRU 334  // thru
#define STR_RES___SEQ 335  // seq
#define STR_RES_CTRL 336  // ctrl
#define STR_RES_FULL 337  // full
#define STR_RES_1TV 338  // 1~|
#define STR_RES_2T1 339  // 2~1
#define STR_RES_3T2 340  // 3~2
#define STR_RES_4T3 341  // 4~3
#define STR_RES_5T4 342  // 5~4
#define STR_RES_6T5 343  // 6~5
#define STR_RES_7T6 344  // 7~6
#define STR_RES_8T7 345  // 8~7
#define STR_RES_TRI 346  // tri
#define STR_RES_SQR 347  // sqr
#define STR_RES_S_H 348  // s&h
#define STR_RES_RAMP 349  // ramp
#define STR_RES_STEP 350  // step
#define STR_RES_3 351  // 
#define STR_RES_4 352  // 
#define STR_RES_34 353  // 
#define STR_RES__ 354  // ?
#define STR_RES_PLAYED 355  // played
#define STR_RES_OFF 356  // off
#define STR_RES_ON 357  // on
#define STR_RES_SQ1 358  // sq1
#define STR_RES__TR1 359  // tr1
#define STR_RES_PL1 360  // pl1
#define STR_RES_SQ2 361  // sq2
#define STR_RES__TR2 362  // tr2
#define STR_RES_PL2 363  // pl2
#define STR_RES_CLICK 364  // click
#define STR_RES_GLITCH 365  // glitch
#define STR_RES_BLOW 366  // blow
#define STR_RES_METAL 367  // metal
#define STR_RES_POP 368  // pop
#define STR_RES_NONE 369  // none
#define STR_RES_SAW 370  // saw
#define STR_RES_SQUARE 371  // square
#define STR_RES_TRIANG 372  // triang
#define STR_RES_ZSAW 373  // zsaw
#define STR_RES_ZRESO 374  // zreso
#define STR_RES_ZTRI 375  // ztri
#define STR_RES_ZPULSE 376  // zpulse
#define STR_RES_ZSYNC 377  // zsync
#define STR_RES_PAD 378  // pad
#define STR_RES_FM 379  // fm
#define STR_RES_WAVES 380  // waves
#define STR_RES_TAMPUR 381  // tampur
#define STR_RES_DIGITL 382  // digitl
#define STR_RES_METALL 383  // metall
#define STR_RES_BOWED 384  // bowed
#define STR_RES_SLAP 385  // slap
#define STR_RES_ORGAN 386  // organ
#define STR_RES_MALE 387  // male
#define STR_RES_USER 388  // user
#define STR_RES_8BITS 389  // 8bits
#define STR_RES_CRUSH 390  // crush
#define STR_RES_PWM 391  // pwm
#define STR_RES___NOISE 392  // noise
#define STR_RES_VOWEL 393  // vowel
#define STR_RES_BELISH 394  // belish
#define STR_RES_POLATD 395  // polatd
#define STR_RES_CELLO 396  // cello
#define STR_RES_CLPSWP 397  // clpswp
#define STR_RES_FEMALE 398  // female
#define STR_RES_FMTVOC 399  // fmtvoc
#define STR_RES_FRMNT2 400  // frmnt2
#define STR_RES_RES3HP 401  // res3hp
#define STR_RES_ELECTP 402  // electp
#define STR_RES_VIBES 403  // vibes
#define STR_RES__LPF 404  // lpf
#define STR_RES_SSM 405  // ssm
#define STR_RES_SVF 406  // svf
#define STR_RES_DSP 407  // dsp
#define STR_RES_PVK 408  // pvk
#define STR_RES_4PM 409  // 4pm
#define STR_RES_DLY 410  // dly
#define STR_RES_SP 411  // sp
#define STR_RES_SPLASH 412  // splash
#define STR_RES__FILTER 413  // filter
#define STR_RES_PRESET 414  // preset
#define STR_RES_EQUAL 415  // equal
#define STR_RES_JUST 416  // just
#define STR_RES_PYTHAG 417  // pythag
#define STR_RES_1_4_EB 418  // 1/4 eb
#define STR_RES_1_4_E 419  // 1/4 e
#define STR_RES_1_4_EA 420  // 1/4 ea
#define STR_RES_BHAIRA 421  // bhaira
#define STR_RES_GUNAKR 422  // gunakr
#define STR_RES_MARWA 423  // marwa
#define STR_RES_SHREE 424  // shree
#define STR_RES_PURVI 425  // purvi
#define STR_RES_BILAWA 426  // bilawa
#define STR_RES_YAMAN 427  // yaman
#define STR_RES_KAFI 428  // kafi
#define STR_RES_BHIMPA 429  // bhimpa
#define STR_RES_DARBAR 430  // darbar
#define STR_RES_BAGESH 431  // bagesh
#define STR_RES_RAGESH 432  // ragesh
#define STR_RES_KHAMAJ 433  // khamaj
#define STR_RES_MIMAL 434  // mi'mal
#define STR_RES_PARAME 435  // parame
#define STR_RES_RANGES 436  // ranges
#define STR_RES_GANGES 437  // ganges
#define STR_RES_KAMESH 438  // kamesh
#define STR_RES_PALAS_ 439  // palas
#define STR_RES_NATBHA 440  // natbha
#define STR_RES_M_KAUN 441  // m.kaun
#define STR_RES_BAIRAG 442  // bairag
#define STR_RES_B_TODI 443  // b.todi
#define STR_RES_CHANDR 444  // chandr
#define STR_RES_KAUSHI 445  // kaushi
#define STR_RES_JOGESH 446  // jogesh
#define STR_RES_RASIA 447  // rasia
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
#define LUT_RES_GROOVE_SWING 37
#define LUT_RES_GROOVE_SWING_SIZE 16
#define LUT_RES_GROOVE_SHUFFLE 38
#define LUT_RES_GROOVE_SHUFFLE_SIZE 16
#define LUT_RES_GROOVE_PUSH 39
#define LUT_RES_GROOVE_PUSH_SIZE 16
#define LUT_RES_GROOVE_LAG 40
#define LUT_RES_GROOVE_LAG_SIZE 16
#define LUT_RES_GROOVE_HUMAN 41
#define LUT_RES_GROOVE_HUMAN_SIZE 16
#define LUT_RES_GROOVE_MONKEY 42
#define LUT_RES_GROOVE_MONKEY_SIZE 16
#define LUT_RES_TEMPO_PHASE_INCREMENT 0
#define LUT_RES_TEMPO_PHASE_INCREMENT_SIZE 201
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
#define WAV_RES_DISTORTION 25
#define WAV_RES_DISTORTION_SIZE 256
#define WAV_RES_ENV_EXPO 26
#define WAV_RES_ENV_EXPO_SIZE 257
#define WAV_RES_SSM2164_LINEARIZATION 27
#define WAV_RES_SSM2164_LINEARIZATION_SIZE 64
#define WAV_RES_WAVES 28
#define WAV_RES_WAVES_SIZE 16383
#define WAV_RES_WAVETABLES 29
#define WAV_RES_WAVETABLES_SIZE 324
#define WAV_RES_VERSION 30
#define WAV_RES_VERSION_SIZE 2
#define CHR_RES_SPECIAL_CHARACTERS 0
#define CHR_RES_SPECIAL_CHARACTERS_SIZE 56
typedef avrlib::ResourcesManager<
    ResourceId,
    avrlib::ResourcesTables<
        string_table,
        lookup_table_table> > ResourcesManager; 

}  // namespace shruthi

#endif  // SHRUTHI_RESOURCES_H_
