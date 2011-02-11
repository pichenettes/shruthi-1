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


#ifndef HARDWARE_SHRUTHI_RESOURCES_H_
#define HARDWARE_SHRUTHI_RESOURCES_H_


#include "hardware/base/base.h"

#include <avr/pgmspace.h>


#include "hardware/resources/resources_manager.h"
namespace hardware_shruthi {

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
extern const prog_uint8_t wav_res_wavetable_1[] PROGMEM;
extern const prog_uint8_t wav_res_wavetable_2[] PROGMEM;
extern const prog_uint8_t wav_res_wavetable_3[] PROGMEM;
extern const prog_uint8_t wav_res_wavetable_4[] PROGMEM;
extern const prog_uint8_t wav_res_wavetable_5[] PROGMEM;
extern const prog_uint8_t wav_res_wavetable_6[] PROGMEM;
extern const prog_uint8_t wav_res_wavetable_7[] PROGMEM;
extern const prog_uint8_t wav_res_wavetable_8[] PROGMEM;
extern const prog_uint8_t wav_res_vowel_data[] PROGMEM;
extern const prog_uint8_t wav_res_expansion_krama[] PROGMEM;
extern const prog_uint8_t wav_res_expansion_jata[] PROGMEM;
extern const prog_uint8_t wav_res_expansion_sikha[] PROGMEM;
extern const prog_uint8_t wav_res_expansion_ghana[] PROGMEM;
extern const prog_uint8_t wav_res_distortion[] PROGMEM;
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
#define STR_RES_MOD_ 20  // mod.
#define STR_RES_SOURCE 21  // source
#define STR_RES_SRC 22  // src
#define STR_RES_DEST_ 23  // dest.
#define STR_RES_DST 24  // dst
#define STR_RES_AMOUNT 25  // amount
#define STR_RES_AMT 26  // amt
#define STR_RES_MODE 27  // mode
#define STR_RES_TEMPO 28  // tempo
#define STR_RES_BPM 29  // bpm
#define STR_RES_GROOVE 30  // groove
#define STR_RES_DIRECTION 31  // direction
#define STR_RES_PATTERN 32  // pattern
#define STR_RES_WARP 33  // warp
#define STR_RES_WRP 34  // wrp
#define STR_RES_START 35  // start
#define STR_RES_LENGTH 36  // length
#define STR_RES_OCTAVE 37  // octave
#define STR_RES_RAGA 38  // raga
#define STR_RES_PORTA 39  // porta
#define STR_RES_PRT 40  // prt
#define STR_RES_LEGATO 41  // legato
#define STR_RES_TUNING 42  // tuning
#define STR_RES_MIDI_CHAN 43  // midi chan
#define STR_RES_CHN 44  // chn
#define STR_RES_MIDI_OUT 45  // midi out
#define STR_RES_PAUSE 46  // pause
#define STR_RES_SNAP 47  // snap
#define STR_RES_CV_MODE 48  // cv.mode
#define STR_RES_OSCILLATOR_1 49  // oscillator 1
#define STR_RES_OSCILLATOR_2 50  // oscillator 2
#define STR_RES_MIXER 51  // mixer
#define STR_RES_FILTER 52  // filter
#define STR_RES_FILTER_2 53  // filter 2
#define STR_RES_ENVELOPE_1 54  // envelope 1
#define STR_RES_ENVELOPE_2 55  // envelope 2
#define STR_RES_SEQUENCER 56  // sequencer
#define STR_RES_ARPEGGIO 57  // arpeggio
#define STR_RES_STEP_SEQUENCER 58  // step sequencer
#define STR_RES_KEYBOARD 59  // keyboard
#define STR_RES_MIDI 60  // midi
#define STR_RES_SYSTEM 61  // system
#define STR_RES_PERFORMANCE 62  // performance
#define STR_RES_LPF 63  // lpf
#define STR_RES_BPF 64  // bpf
#define STR_RES_HPF 65  // hpf
#define STR_RES__LP 66  // =lp
#define STR_RES__BP 67  // =bp
#define STR_RES__HP 68  // =hp
#define STR_RES_LP 69  // :lp
#define STR_RES_BP 70  // :bp
#define STR_RES_HP 71  // :hp
#define STR_RES_CUT 72  // cut
#define STR_RES_VCA 73  // vca
#define STR_RES_PW1 74  // pw1
#define STR_RES_PW2 75  // pw2
#define STR_RES_51 76  // 1
#define STR_RES_52 77  // 2
#define STR_RES_5 78  // 
#define STR_RES_5F 79  // f
#define STR_RES_MIX 80  // mix
#define STR_RES_NOI 81  // noi
#define STR_RES_SUB 82  // sub
#define STR_RES_RES 83  // res
#define STR_RES__CV1 84  //  cv1
#define STR_RES__CV2 85  //  cv2
#define STR_RES__ATK 86  //  atk
#define STR_RES__LF1 87  //  lf1
#define STR_RES__LF2 88  //  lf2
#define STR_RES_CUTOFF 89  // cutoff
#define STR_RES__VCA 90  //  vca
#define STR_RES_PWM1 91  // pwm1
#define STR_RES_PWM2 92  // pwm2
#define STR_RES_OSC1 93  // osc1
#define STR_RES_OSC2 94  // osc2
#define STR_RES_OSC1S2 95  // osc1+2
#define STR_RES_FINE 96  // fine
#define STR_RES__MIX 97  //  mix
#define STR_RES_NOISE 98  // noise
#define STR_RES_SUBOSC 99  // subosc
#define STR_RES_RESO 100  // reso
#define STR_RES__CV_1 101  //  cv 1
#define STR_RES__CV_2 102  //  cv 2
#define STR_RES__ATTACK 103  //  attack
#define STR_RES__LFO_1 104  //  lfo 1
#define STR_RES__LFO_2 105  //  lfo 2
#define STR_RES_LF1 106  // lf1
#define STR_RES_LF2 107  // lf2
#define STR_RES_SEQ 108  // seq
#define STR_RES__SQ1 109  //  sq1
#define STR_RES__SQ2 110  //  sq2
#define STR_RES__ARP 111  //  arp
#define STR_RES_WHL 112  // whl
#define STR_RES_AFT 113  // aft
#define STR_RES_BND 114  // bnd
#define STR_RES_OFS 115  // ofs
#define STR_RES_CV1 116  // cv1
#define STR_RES_CV2 117  // cv2
#define STR_RES_CV3 118  // cv3
#define STR_RES_CV4 119  // cv4
#define STR_RES_CCA 120  // ccA
#define STR_RES_CCB 121  // ccB
#define STR_RES_CCC 122  // ccC
#define STR_RES_CCD 123  // ccD
#define STR_RES__NOI 124  //  noi
#define STR_RES_EN1 125  // en1
#define STR_RES_EN2 126  // en2
#define STR_RES_VEL 127  // vel
#define STR_RES_RND 128  // rnd
#define STR_RES_NOT 129  // not
#define STR_RES_GAT 130  // gat
#define STR_RES_AUD 131  // aud
#define STR_RES_LFO_1 132  // lfo 1
#define STR_RES_LFO_2 133  // lfo 2
#define STR_RES_STPSEQ 134  // stpseq
#define STR_RES_STPSQ1 135  // stpsq1
#define STR_RES_STPSQ2 136  // stpsq2
#define STR_RES___ARP 137  //   arp
#define STR_RES_MWHEEL 138  // mwheel
#define STR_RES_AFTTCH 139  // afttch
#define STR_RES_BENDER 140  // bender
#define STR_RES_OFFSET 141  // offset
#define STR_RES_CV_1 142  // cv 1
#define STR_RES_CV_2 143  // cv 2
#define STR_RES_CV_3 144  // cv 3
#define STR_RES_CV_4 145  // cv 4
#define STR_RES_CC_A 146  // cc A
#define STR_RES_CC_B 147  // cc B
#define STR_RES_CC_C 148  // cc C
#define STR_RES_CC_D 149  // cc D
#define STR_RES___NOISE 150  //   noise
#define STR_RES_ENV_1 151  // env 1
#define STR_RES_ENV_2 152  // env 2
#define STR_RES_VELO 153  // velo
#define STR_RES_RANDOM 154  // random
#define STR_RES_NOTE 155  // note
#define STR_RES_GATE 156  // gate
#define STR_RES_AUDIO 157  // audio
#define STR_RES_TOUCH_A_KNOB_TO 158  // touch a knob to
#define STR_RES_ASSIGN_PARAMETER 159  // assign parameter
#define STR_RES_PATCH 160  // patch
#define STR_RES_SEQUENCE 161  // sequence
#define STR_RES_SAVE_MIDI_KBD 162  // save midi/kbd
#define STR_RES_SETTINGS_ 163  // settings?
#define STR_RES_START_FULL_MIDI 164  // start full midi
#define STR_RES_BACKUP_ 165  // backup?
#define STR_RES_BROWSE 166  // browse
#define STR_RES_SAVE 167  // save
#define STR_RES_COMPARE 168  // compare
#define STR_RES_ 169  // ----
#define STR_RES_V 170  // v
#define STR_RES_MUTABLE____V0_92 171  // mutable    v0.92
#define STR_RES_INSTRUMENTS_671 172  // instruments -1
#define STR_RES_EXTERN 173  // extern
#define STR_RES_X2_EXT 174  // x2 ext
#define STR_RES__2_EXT 175  // /2 ext
#define STR_RES__4_EXT 176  // /4 ext
#define STR_RES__8_EXT 177  // /8 ext
#define STR_RES_SUM 178  // sum
#define STR_RES_SYNC 179  // sync
#define STR_RES_RING 180  // ring
#define STR_RES_XOR 181  // xor
#define STR_RES_FUZZ 182  // fuzz
#define STR_RES___4 183  // >>4
#define STR_RES___8 184  // >>8
#define STR_RES_STP 185  // stp
#define STR_RES_ARP 186  // arp
#define STR_RES_ARPSLT 187  // arp+lt
#define STR_RES__SEQ 188  //  seq
#define STR_RES_SEQSLT 189  // seq+lt
#define STR_RES_REC 190  // rec
#define STR_RES_IMPRO 191  // impro
#define STR_RES_FREE 192  // free
#define STR_RES_SLAVE 193  // slave
#define STR_RES_MASTER 194  // master
#define STR_RES_T 195  // ~
#define STR_RES___ 196  //  
#define STR_RES_T_ 197  // ~-
#define STR_RES__T_ 198  //  ~
#define STR_RES_GLASS 199  // glass
#define STR_RES_KRAMA 200  // krama
#define STR_RES_JATA 201  // jata
#define STR_RES_SIKHA 202  // sikha
#define STR_RES_GHANA 203  // ghana
#define STR_RES_2GLASS 204  // 2glass
#define STR_RES_2KRAMA 205  // 2krama
#define STR_RES_2JATA 206  // 2jata
#define STR_RES_2SIKHA 207  // 2sikha
#define STR_RES_2GHANA 208  // 2ghana
#define STR_RES_4GLASS 209  // 4glass
#define STR_RES_4KRAMA 210  // 4krama
#define STR_RES_4JATA 211  // 4jata
#define STR_RES_4SIKHA 212  // 4sikha
#define STR_RES_4GHANA 213  // 4ghana
#define STR_RES_SWING 214  // swing
#define STR_RES_SHUFFLE 215  // shuffle
#define STR_RES_PUSH 216  // push
#define STR_RES_LAG 217  // lag
#define STR_RES_HUMAN 218  // human
#define STR_RES_MONKEY 219  // monkey
#define STR_RES__OFF 220  //  off
#define STR_RES_THRU 221  // thru
#define STR_RES___SEQ 222  //   seq
#define STR_RES_SPLIT 223  // split
#define STR_RES_FULL 224  // full
#define STR_RES_1T_ 225  // 1~|
#define STR_RES_2T1 226  // 2~1
#define STR_RES_3T2 227  // 3~2
#define STR_RES_4T3 228  // 4~3
#define STR_RES_5T4 229  // 5~4
#define STR_RES_6T5 230  // 6~5
#define STR_RES_7T6 231  // 7~6
#define STR_RES_8T7 232  // 8~7
#define STR_RES_TRI 233  // tri
#define STR_RES_SQR 234  // sqr
#define STR_RES_S_H 235  // s&h
#define STR_RES_RAMP 236  // ramp
#define STR_RES_STEP 237  // step
#define STR_RES_3 238  // 
#define STR_RES_4 239  // 
#define STR_RES_34 240  // 
#define STR_RES__ 241  // ?
#define STR_RES_OFF 242  // off
#define STR_RES_ON 243  // on
#define STR_RES_SQ1 244  // sq1
#define STR_RES_TR1 245  // tr1
#define STR_RES_PL1 246  // pl1
#define STR_RES_SQ2 247  // sq2
#define STR_RES_TR2 248  // tr2
#define STR_RES_PL2 249  // pl2
#define STR_RES_CLICK 250  // click
#define STR_RES_GLITCH 251  // glitch
#define STR_RES_BLOW 252  // blow
#define STR_RES_METAL 253  // metal
#define STR_RES_POP 254  // pop
#define STR_RES_NONE 255  // none
#define STR_RES_SAW 256  // saw
#define STR_RES_SQUARE 257  // square
#define STR_RES_TRIANG 258  // triang
#define STR_RES_ZSAW 259  // zsaw
#define STR_RES_ZRESO 260  // zreso
#define STR_RES_ZTRI 261  // ztri
#define STR_RES_ZPULSE 262  // zpulse
#define STR_RES_ZSYNC 263  // zsync
#define STR_RES_PAD 264  // pad
#define STR_RES_FM 265  // fm
#define STR_RES_WAVES 266  // waves
#define STR_RES_TAMPUR 267  // tampur
#define STR_RES_DIGITL 268  // digitl
#define STR_RES_METALL 269  // metall
#define STR_RES_BOWED 270  // bowed
#define STR_RES_SLAP 271  // slap
#define STR_RES_ORGAN 272  // organ
#define STR_RES_MALE 273  // male
#define STR_RES_USER 274  // user
#define STR_RES_8BITS 275  // 8bits
#define STR_RES_CRUSH 276  // crush
#define STR_RES_PWM 277  // pwm
#define STR_RES__NOISE 278  //  noise
#define STR_RES_VOWEL 279  // vowel
#define STR_RES__LPF 280  //  lpf
#define STR_RES_SSM 281  // ssm
#define STR_RES_SVF 282  // svf
#define STR_RES_4CV_IN 283  // 4cv in
#define STR_RES_PRGM 284  // prgm
#define STR_RES_PEDALS 285  // pedals
#define STR_RES_EQUAL 286  // equal
#define STR_RES_JUST 287  // just
#define STR_RES_PYTHAG 288  // pythag
#define STR_RES_1_4_EB 289  // 1/4 eb
#define STR_RES_1_4_E 290  // 1/4 e
#define STR_RES_1_4_EA 291  // 1/4 ea
#define STR_RES_BHAIRA 292  // bhaira
#define STR_RES_GUNAKR 293  // gunakr
#define STR_RES_MARWA 294  // marwa
#define STR_RES_SHREE 295  // shree
#define STR_RES_PURVI 296  // purvi
#define STR_RES_BILAWA 297  // bilawa
#define STR_RES_YAMAN 298  // yaman
#define STR_RES_KAFI 299  // kafi
#define STR_RES_BHIMPA 300  // bhimpa
#define STR_RES_DARBAR 301  // darbar
#define STR_RES_BAGESH 302  // bagesh
#define STR_RES_RAGESH 303  // ragesh
#define STR_RES_KHAMAJ 304  // khamaj
#define STR_RES_MIMAL 305  // mi'mal
#define STR_RES_PARAME 306  // parame
#define STR_RES_RANGES 307  // ranges
#define STR_RES_GANGES 308  // ganges
#define STR_RES_KAMESH 309  // kamesh
#define STR_RES_PALAS_ 310  // palas 
#define STR_RES_NATBHA 311  // natbha
#define STR_RES_M_KAUN 312  // m.kaun
#define STR_RES_BAIRAG 313  // bairag
#define STR_RES_B_TODI 314  // b.todi
#define STR_RES_CHANDR 315  // chandr
#define STR_RES_KAUSHI 316  // kaushi
#define STR_RES_JOGESH 317  // jogesh
#define STR_RES_RASIA 318  // rasia
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
#define WAV_RES_WAVETABLE_1 23
#define WAV_RES_WAVETABLE_1_SIZE 2064
#define WAV_RES_WAVETABLE_2 24
#define WAV_RES_WAVETABLE_2_SIZE 2064
#define WAV_RES_WAVETABLE_3 25
#define WAV_RES_WAVETABLE_3_SIZE 2064
#define WAV_RES_WAVETABLE_4 26
#define WAV_RES_WAVETABLE_4_SIZE 2064
#define WAV_RES_WAVETABLE_5 27
#define WAV_RES_WAVETABLE_5_SIZE 2064
#define WAV_RES_WAVETABLE_6 28
#define WAV_RES_WAVETABLE_6_SIZE 2064
#define WAV_RES_WAVETABLE_7 29
#define WAV_RES_WAVETABLE_7_SIZE 2064
#define WAV_RES_WAVETABLE_8 30
#define WAV_RES_WAVETABLE_8_SIZE 2064
#define WAV_RES_VOWEL_DATA 31
#define WAV_RES_VOWEL_DATA_SIZE 45
#define WAV_RES_EXPANSION_KRAMA 32
#define WAV_RES_EXPANSION_KRAMA_SIZE 30
#define WAV_RES_EXPANSION_JATA 33
#define WAV_RES_EXPANSION_JATA_SIZE 90
#define WAV_RES_EXPANSION_SIKHA 34
#define WAV_RES_EXPANSION_SIKHA_SIZE 126
#define WAV_RES_EXPANSION_GHANA 35
#define WAV_RES_EXPANSION_GHANA_SIZE 182
#define WAV_RES_DISTORTION 36
#define WAV_RES_DISTORTION_SIZE 256
#define CHR_RES_SPECIAL_CHARACTERS 0
#define CHR_RES_SPECIAL_CHARACTERS_SIZE 56
typedef hardware_resources::ResourcesManager<
    ResourceId,
    hardware_resources::ResourcesTables<
        string_table,
        lookup_table_table> > ResourcesManager; 

}  // namespace hardware_shruthi

#endif  // HARDWARE_SHRUTHI_RESOURCES_H_
