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
#define STR_RES_PRM 2  // prm
#define STR_RES_RANGE 3  // range
#define STR_RES_RNG 4  // rng
#define STR_RES_OP_ 5  // op.
#define STR_RES_OPERATOR 6  // operator
#define STR_RES_DETUNE 7  // detune
#define STR_RES_OSC_MIX 8  // osc mix
#define STR_RES_SUB_OSC_ 9  // sub osc.
#define STR_RES_ENV1TVCF 10  // env1~vcf
#define STR_RES_LFO2TVCF 11  // lfo2~vcf
#define STR_RES_ATTACK 12  // attack
#define STR_RES_ATK 13  // atk
#define STR_RES_DECAY 14  // decay
#define STR_RES_SUSTAIN 15  // sustain
#define STR_RES_RELEASE 16  // release
#define STR_RES_RATE 17  // rate
#define STR_RES_MODULATION 18  // modulation
#define STR_RES_MOD_ 19  // mod.
#define STR_RES_SOURCE 20  // source
#define STR_RES_SRC 21  // src
#define STR_RES_DEST_ 22  // dest.
#define STR_RES_DST 23  // dst
#define STR_RES_AMOUNT 24  // amount
#define STR_RES_AMT 25  // amt
#define STR_RES_MODE 26  // mode
#define STR_RES_TEMPO 27  // tempo
#define STR_RES_BPM 28  // bpm
#define STR_RES_GROOVE 29  // groove
#define STR_RES_DIRECTION 30  // direction
#define STR_RES_PATTERN 31  // pattern
#define STR_RES_WARP 32  // warp
#define STR_RES_WRP 33  // wrp
#define STR_RES_START 34  // start
#define STR_RES_LENGTH 35  // length
#define STR_RES_OCTAVE 36  // octave
#define STR_RES_RAGA 37  // raga
#define STR_RES_PORTA 38  // porta
#define STR_RES_PRT 39  // prt
#define STR_RES_LEGATO 40  // legato
#define STR_RES_TUNING 41  // tuning
#define STR_RES_MIDI_CHAN 42  // midi chan
#define STR_RES_CHN 43  // chn
#define STR_RES_MIDI_OUT 44  // midi out
#define STR_RES_PAUSE 45  // pause
#define STR_RES_SNAP 46  // snap
#define STR_RES_CV_MODE 47  // cv.mode
#define STR_RES_OSCILLATOR_1 48  // oscillator 1
#define STR_RES_OSCILLATOR_2 49  // oscillator 2
#define STR_RES_MIXER 50  // mixer
#define STR_RES_FILTER 51  // filter
#define STR_RES_FILTER_2 52  // filter 2
#define STR_RES_ENVELOPE_1 53  // envelope 1
#define STR_RES_ENVELOPE_2 54  // envelope 2
#define STR_RES_SEQUENCER 55  // sequencer
#define STR_RES_ARPEGGIO 56  // arpeggio
#define STR_RES_STEP_SEQUENCER 57  // step sequencer
#define STR_RES_KEYBOARD 58  // keyboard
#define STR_RES_MIDI 59  // midi
#define STR_RES_SYSTEM 60  // system
#define STR_RES_PERFORMANCE 61  // performance
#define STR_RES_LPF 62  // lpf
#define STR_RES_BPF 63  // bpf
#define STR_RES_HPF 64  // hpf
#define STR_RES__LP 65  // =lp
#define STR_RES__BP 66  // =bp
#define STR_RES__HP 67  // =hp
#define STR_RES_LP 68  // :lp
#define STR_RES_BP 69  // :bp
#define STR_RES_HP 70  // :hp
#define STR_RES_CUT 71  // cut
#define STR_RES_VCA 72  // vca
#define STR_RES_PW1 73  // pw1
#define STR_RES_PW2 74  // pw2
#define STR_RES_51 75  // 1
#define STR_RES_52 76  // 2
#define STR_RES_5 77  // 
#define STR_RES_5F 78  // f
#define STR_RES_MIX 79  // mix
#define STR_RES_NOI 80  // noi
#define STR_RES_SUB 81  // sub
#define STR_RES_RESONANCE 82  // resonance
#define STR_RES__CV1 83  //  cv1
#define STR_RES__CV2 84  //  cv2
#define STR_RES__ATK 85  //  atk
#define STR_RES__LF1 86  //  lf1
#define STR_RES__LF2 87  //  lf2
#define STR_RES_CUTOFF 88  // cutoff
#define STR_RES__VCA 89  //  vca
#define STR_RES_PWM1 90  // pwm1
#define STR_RES_PWM2 91  // pwm2
#define STR_RES_OSC1 92  // osc1
#define STR_RES_OSC2 93  // osc2
#define STR_RES_OSC1S2 94  // osc1+2
#define STR_RES_FINE 95  // fine
#define STR_RES__MIX 96  //  mix
#define STR_RES_NOISE 97  // noise
#define STR_RES_SUBOSC 98  // subosc
#define STR_RES_RESO 99  // reso
#define STR_RES__CV_1 100  //  cv 1
#define STR_RES__CV_2 101  //  cv 2
#define STR_RES__ATTACK 102  //  attack
#define STR_RES__LFO_1 103  //  lfo 1
#define STR_RES__LFO_2 104  //  lfo 2
#define STR_RES_LF1 105  // lf1
#define STR_RES_LF2 106  // lf2
#define STR_RES_SEQ 107  // seq
#define STR_RES__SQ1 108  //  sq1
#define STR_RES__SQ2 109  //  sq2
#define STR_RES__ARP 110  //  arp
#define STR_RES_WHL 111  // whl
#define STR_RES_AFT 112  // aft
#define STR_RES_BND 113  // bnd
#define STR_RES_OFS 114  // ofs
#define STR_RES_CV1 115  // cv1
#define STR_RES_CV2 116  // cv2
#define STR_RES_CV3 117  // cv3
#define STR_RES_CV4 118  // cv4
#define STR_RES_CCA 119  // ccA
#define STR_RES_CCB 120  // ccB
#define STR_RES_CCC 121  // ccC
#define STR_RES_CCD 122  // ccD
#define STR_RES__NOI 123  //  noi
#define STR_RES_EN1 124  // en1
#define STR_RES_EN2 125  // en2
#define STR_RES_VEL 126  // vel
#define STR_RES_RND 127  // rnd
#define STR_RES_NOT 128  // not
#define STR_RES_GAT 129  // gat
#define STR_RES_AUD 130  // aud
#define STR_RES_LFO_1 131  // lfo 1
#define STR_RES_LFO_2 132  // lfo 2
#define STR_RES_STPSEQ 133  // stpseq
#define STR_RES_STPSQ1 134  // stpsq1
#define STR_RES_STPSQ2 135  // stpsq2
#define STR_RES___ARP 136  //   arp
#define STR_RES_MWHEEL 137  // mwheel
#define STR_RES_AFTTCH 138  // afttch
#define STR_RES_BENDER 139  // bender
#define STR_RES_OFFSET 140  // offset
#define STR_RES_CV_1 141  // cv 1
#define STR_RES_CV_2 142  // cv 2
#define STR_RES_CV_3 143  // cv 3
#define STR_RES_CV_4 144  // cv 4
#define STR_RES_CC_A 145  // cc A
#define STR_RES_CC_B 146  // cc B
#define STR_RES_CC_C 147  // cc C
#define STR_RES_CC_D 148  // cc D
#define STR_RES___NOISE 149  //   noise
#define STR_RES_ENV_1 150  // env 1
#define STR_RES_ENV_2 151  // env 2
#define STR_RES_VELO 152  // velo
#define STR_RES_RANDOM 153  // random
#define STR_RES_NOTE 154  // note
#define STR_RES_GATE 155  // gate
#define STR_RES_AUDIO 156  // audio
#define STR_RES_TOUCH_A_KNOB_TO 157  // touch a knob to
#define STR_RES_ASSIGN_PARAMETER 158  // assign parameter
#define STR_RES_PATCH 159  // patch
#define STR_RES_SEQUENCE 160  // sequence
#define STR_RES_SAVE_MIDI_KBD 161  // save midi/kbd
#define STR_RES_SETTINGS_ 162  // settings?
#define STR_RES_START_FULL_MIDI 163  // start full midi
#define STR_RES_BACKUP_ 164  // backup?
#define STR_RES_BROWSE 165  // browse
#define STR_RES_SAVE 166  // save
#define STR_RES_COMPARE 167  // compare
#define STR_RES_ 168  // ----
#define STR_RES_V 169  // v
#define STR_RES_MUTABLE____V0_92 170  // mutable    v0.92
#define STR_RES_INSTRUMENTS_671 171  // instruments -1
#define STR_RES_EXTERN 172  // extern
#define STR_RES_X2_EXT 173  // x2 ext
#define STR_RES__2_EXT 174  // /2 ext
#define STR_RES__4_EXT 175  // /4 ext
#define STR_RES__8_EXT 176  // /8 ext
#define STR_RES_SUM 177  // sum
#define STR_RES_SYNC 178  // sync
#define STR_RES_RING 179  // ring
#define STR_RES_XOR 180  // xor
#define STR_RES_FUZZ 181  // fuzz
#define STR_RES___4 182  // >>4
#define STR_RES___8 183  // >>8
#define STR_RES_STP 184  // stp
#define STR_RES_ARP 185  // arp
#define STR_RES_ARPSLT 186  // arp+lt
#define STR_RES__SEQ 187  //  seq
#define STR_RES_SEQSLT 188  // seq+lt
#define STR_RES_REC 189  // rec
#define STR_RES_IMPRO 190  // impro
#define STR_RES_FREE 191  // free
#define STR_RES_SLAVE 192  // slave
#define STR_RES_MASTER 193  // master
#define STR_RES_T 194  // ~
#define STR_RES___ 195  //  
#define STR_RES_T_ 196  // ~-
#define STR_RES__T_ 197  //  ~
#define STR_RES_GLASS 198  // glass
#define STR_RES_KRAMA 199  // krama
#define STR_RES_JATA 200  // jata
#define STR_RES_SIKHA 201  // sikha
#define STR_RES_GHANA 202  // ghana
#define STR_RES_2GLASS 203  // 2glass
#define STR_RES_2KRAMA 204  // 2krama
#define STR_RES_2JATA 205  // 2jata
#define STR_RES_2SIKHA 206  // 2sikha
#define STR_RES_2GHANA 207  // 2ghana
#define STR_RES_4GLASS 208  // 4glass
#define STR_RES_4KRAMA 209  // 4krama
#define STR_RES_4JATA 210  // 4jata
#define STR_RES_4SIKHA 211  // 4sikha
#define STR_RES_4GHANA 212  // 4ghana
#define STR_RES_SWING 213  // swing
#define STR_RES_SHUFFLE 214  // shuffle
#define STR_RES_PUSH 215  // push
#define STR_RES_LAG 216  // lag
#define STR_RES_HUMAN 217  // human
#define STR_RES_MONKEY 218  // monkey
#define STR_RES__OFF 219  //  off
#define STR_RES_THRU 220  // thru
#define STR_RES___SEQ 221  //   seq
#define STR_RES_SPLIT 222  // split
#define STR_RES_FULL 223  // full
#define STR_RES_1T_ 224  // 1~|
#define STR_RES_2T1 225  // 2~1
#define STR_RES_3T2 226  // 3~2
#define STR_RES_4T3 227  // 4~3
#define STR_RES_5T4 228  // 5~4
#define STR_RES_6T5 229  // 6~5
#define STR_RES_7T6 230  // 7~6
#define STR_RES_8T7 231  // 8~7
#define STR_RES_TRI 232  // tri
#define STR_RES_SQR 233  // sqr
#define STR_RES_S_H 234  // s&h
#define STR_RES_RAMP 235  // ramp
#define STR_RES_STEP 236  // step
#define STR_RES_3 237  // 
#define STR_RES_4 238  // 
#define STR_RES_34 239  // 
#define STR_RES__ 240  // ?
#define STR_RES_OFF 241  // off
#define STR_RES_ON 242  // on
#define STR_RES_SQ1 243  // sq1
#define STR_RES_TR1 244  // tr1
#define STR_RES_PL1 245  // pl1
#define STR_RES_SQ2 246  // sq2
#define STR_RES_TR2 247  // tr2
#define STR_RES_PL2 248  // pl2
#define STR_RES_CLICK 249  // click
#define STR_RES_GLITCH 250  // glitch
#define STR_RES_BLOW 251  // blow
#define STR_RES_METAL 252  // metal
#define STR_RES_POP 253  // pop
#define STR_RES_NONE 254  // none
#define STR_RES_SAW 255  // saw
#define STR_RES_SQUARE 256  // square
#define STR_RES_TRIANG 257  // triang
#define STR_RES_ZSAW 258  // zsaw
#define STR_RES_ZRESO 259  // zreso
#define STR_RES_ZTRI 260  // ztri
#define STR_RES_ZPULSE 261  // zpulse
#define STR_RES_ZSYNC 262  // zsync
#define STR_RES_PAD 263  // pad
#define STR_RES_FM 264  // fm
#define STR_RES_WAVES 265  // waves
#define STR_RES_TAMPUR 266  // tampur
#define STR_RES_DIGITL 267  // digitl
#define STR_RES_METALL 268  // metall
#define STR_RES_BOWED 269  // bowed
#define STR_RES_SLAP 270  // slap
#define STR_RES_ORGAN 271  // organ
#define STR_RES_MALE 272  // male
#define STR_RES_USER 273  // user
#define STR_RES_8BITS 274  // 8bits
#define STR_RES_CRUSH 275  // crush
#define STR_RES_PWM 276  // pwm
#define STR_RES__NOISE 277  //  noise
#define STR_RES_VOWEL 278  // vowel
#define STR_RES__LPF 279  //  lpf
#define STR_RES_SSM 280  // ssm
#define STR_RES_SVF 281  // svf
#define STR_RES_4CV_IN 282  // 4cv in
#define STR_RES_PRGM 283  // prgm
#define STR_RES_PEDALS 284  // pedals
#define STR_RES_EQUAL 285  // equal
#define STR_RES_JUST 286  // just
#define STR_RES_PYTHAG 287  // pythag
#define STR_RES_1_4_EB 288  // 1/4 eb
#define STR_RES_1_4_E 289  // 1/4 e
#define STR_RES_1_4_EA 290  // 1/4 ea
#define STR_RES_BHAIRA 291  // bhaira
#define STR_RES_GUNAKR 292  // gunakr
#define STR_RES_MARWA 293  // marwa
#define STR_RES_SHREE 294  // shree
#define STR_RES_PURVI 295  // purvi
#define STR_RES_BILAWA 296  // bilawa
#define STR_RES_YAMAN 297  // yaman
#define STR_RES_KAFI 298  // kafi
#define STR_RES_BHIMPA 299  // bhimpa
#define STR_RES_DARBAR 300  // darbar
#define STR_RES_BAGESH 301  // bagesh
#define STR_RES_RAGESH 302  // ragesh
#define STR_RES_KHAMAJ 303  // khamaj
#define STR_RES_MIMAL 304  // mi'mal
#define STR_RES_PARAME 305  // parame
#define STR_RES_RANGES 306  // ranges
#define STR_RES_GANGES 307  // ganges
#define STR_RES_KAMESH 308  // kamesh
#define STR_RES_PALAS_ 309  // palas 
#define STR_RES_NATBHA 310  // natbha
#define STR_RES_M_KAUN 311  // m.kaun
#define STR_RES_BAIRAG 312  // bairag
#define STR_RES_B_TODI 313  // b.todi
#define STR_RES_CHANDR 314  // chandr
#define STR_RES_KAUSHI 315  // kaushi
#define STR_RES_JOGESH 316  // jogesh
#define STR_RES_RASIA 317  // rasia
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
