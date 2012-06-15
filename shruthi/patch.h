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
// Patch definition. The order of the fields must match the numbering of the
// parameters defined later. Contains methods for packing/unpacking to a
// buffer of bytes (the compression is not optimal, but a more optimal
// compression that would use, for example, the MSB of all parameters in the
// 0-127 range, would result in a high code size).
// Also includes code for checking whether a buffer looks like a reasonable
// patch.

#ifndef SHRUTHI_PATCH_H_
#define SHRUTHI_PATCH_H_

#include "avrlib/base.h"

namespace shruthi {

#ifdef PORTAMENTO_SAVE_HACK
const uint8_t kPatchNameSize = 7;
#else
const uint8_t kPatchNameSize = 8;
#endif  // PORTAMENTO_SAVE_HACK
const uint8_t kModulationMatrixSize = 12;

struct Modulation {
  uint8_t source;
  uint8_t destination;
  int8_t amount;
};

struct Operation {
  uint8_t operands[2];
  uint8_t op;
};

union ModulationMatrix {
  Modulation modulation[kModulationMatrixSize];
  uint8_t raw_modulation_data[kModulationMatrixSize * 3];
};

struct OscillatorSettings {
  uint8_t shape;
  uint8_t parameter;
  int8_t range;
  uint8_t option;
};

struct EnvelopeSettings {
  uint8_t attack;
  uint8_t decay;
  uint8_t sustain;
  uint8_t release;
};

struct LfoSettings {
  uint8_t waveform;
  uint8_t rate;
  uint8_t attack;
  uint8_t retrigger_mode;
};

struct ParameterAssignment {
  uint8_t id;
  uint8_t subpage;
};

#define PATCH_SIZE (sizeof(Patch) - 8)

class Patch {
 public:
  // Offset: 0-8
  OscillatorSettings osc[2];

  // Offset: 8-12
  uint8_t mix_balance;
  uint8_t mix_sub_osc;
  uint8_t mix_noise;
  uint8_t mix_sub_osc_shape;

  // Offset: 12-16
  uint8_t filter_cutoff;
  uint8_t filter_resonance;
  int8_t filter_env;
  int8_t filter_lfo;

  // Offset: 16-24
  EnvelopeSettings env[2];

  // Offset: 24-32
  LfoSettings lfo[2];

  // Offset: 32-68
  ModulationMatrix modulation_matrix;
  // Offset: 68-76
  uint8_t name[kPatchNameSize];

#ifdef PORTAMENTO_SAVE_HACK
  uint8_t portamento_data;
#endif

  // Offset: 76-84
  ParameterAssignment assigned_parameters[4];
  
  // Offset: 84-92
  uint8_t filter_cutoff_2;
  uint8_t filter_resonance_2;
  uint8_t filter_topology_;
  uint8_t op_data_[4];
  uint8_t exclamation_mark_;
  
  // 8 bytes of decompressed patch data.
  uint8_t filter_1_mode_;
  uint8_t filter_2_mode_;
  Operation ops_[2];
  
  uint8_t* saved_data() { return (uint8_t*)(this); }
  void PrepareForWrite();
  uint8_t CheckBuffer(uint8_t* buffer);
  void Update();
};

enum ModulationSource {
  /* First the modulation sources common to all notes. */
  MOD_SRC_LFO_1 = 0,
  MOD_SRC_LFO_2,
  MOD_SRC_SEQ,
  MOD_SRC_SEQ_1,
  MOD_SRC_SEQ_2,
  MOD_SRC_STEP,
  MOD_SRC_WHEEL,
  MOD_SRC_AFTERTOUCH,
  MOD_SRC_PITCH_BEND,
  MOD_SRC_OFFSET,
  MOD_SRC_CV_1,
  MOD_SRC_CV_2,
  MOD_SRC_CV_3,
  MOD_SRC_CV_4,
  MOD_SRC_CC_A,
  MOD_SRC_CC_B,
  MOD_SRC_CC_C,
  MOD_SRC_CC_D,
  MOD_SRC_NOISE,

  /* Then those which are different for each note. */
  MOD_SRC_ENV_1,
  MOD_SRC_ENV_2,
  MOD_SRC_VELOCITY,
  MOD_SRC_RANDOM,
  MOD_SRC_NOTE,
  MOD_SRC_GATE,
  MOD_SRC_AUDIO,
  MOD_SRC_OP_1,
  MOD_SRC_OP_2,
  
  /* Some newly added modulations */
  MOD_SRC_TRIG_1,
  MOD_SRC_TRIG_2,
  MOD_SRC_VALUE_4,
  MOD_SRC_VALUE_8,
  MOD_SRC_VALUE_16,
  MOD_SRC_VALUE_32,
  
  MOD_SRC_LAST
};

static const uint8_t kNumModulationSources = MOD_SRC_LAST;

enum ModulationDestination {
  MOD_DST_FILTER_CUTOFF = 0,
  MOD_DST_VCA,
  MOD_DST_PWM_1,
  MOD_DST_PWM_2,
  MOD_DST_VCO_1,
  MOD_DST_VCO_2,
  MOD_DST_VCO_1_2_COARSE,
  MOD_DST_VCO_1_2_FINE,
  MOD_DST_MIX_BALANCE,
  MOD_DST_MIX_NOISE,
  MOD_DST_MIX_SUB_OSC,
  MOD_DST_FILTER_RESONANCE,
  MOD_DST_CV_1,
  MOD_DST_CV_2,
  MOD_DST_ATTACK,
  MOD_DST_LFO_1,
  MOD_DST_LFO_2,
  MOD_DST_TRIGGER_ENV_1,
  MOD_DST_TRIGGER_ENV_2,
  MOD_DST_LAST
};

static const uint8_t kNumModulationDestinations = MOD_DST_LAST;

enum PatchParameter {
  PRM_OSC_SHAPE_1,
  PRM_OSC_PARAMETER_1,
  PRM_OSC_RANGE_1,
  PRM_OSC_OPTION_1,

  PRM_OSC_SHAPE_2,
  PRM_OSC_PARAMETER_2,
  PRM_OSC_RANGE_2,
  PRM_OSC_OPTION_2,

  PRM_MIX_BALANCE,
  PRM_MIX_SUB_OSC,
  PRM_MIX_NOISE,
  PRM_MIX_SUB_OSC_SHAPE,

  PRM_FILTER_CUTOFF,
  PRM_FILTER_RESONANCE,
  PRM_FILTER_ENV,
  PRM_FILTER_LFO,

  PRM_ENV_ATTACK_1,
  PRM_ENV_DECAY_1,
  PRM_ENV_SUSTAIN_1,
  PRM_ENV_RELEASE_1,

  PRM_ENV_ATTACK_2,
  PRM_ENV_DECAY_2,
  PRM_ENV_SUSTAIN_2,
  PRM_ENV_RELEASE_2,

  PRM_LFO_WAVE_1,
  PRM_LFO_RATE_1,
  PRM_LFO_ATTACK_1,
  PRM_LFO_RETRIGGER_1,

  PRM_LFO_WAVE_2,
  PRM_LFO_RATE_2,
  PRM_LFO_ATTACK_2,
  PRM_LFO_RETRIGGER_2,

  PRM_MOD_SOURCE,
  PRM_MOD_DESTINATION,
  PRM_MOD_AMOUNT,
  PRM_MOD_ROW,
  
  PRM_FILTER_CUTOFF_2 = 84,
  PRM_FILTER_RESONANCE_2 = 85,
  PRM_FILTER_MODE_1 = 92,
  PRM_FILTER_MODE_2 = 93,
  
  PRM_OP_OP1 = 94,
  PRM_OP_OP2 = 95,
  PRM_OP_OPERATOR = 96,
  PRM_OP_ROW = 97,
  
  PRM_FX_PROGRAM = PRM_FILTER_MODE_2,
  PRM_FX_PARAM_1 = PRM_FILTER_CUTOFF_2,
  PRM_FX_PARAM_2 = PRM_FILTER_RESONANCE_2,
  
  PRM_PV_MODE = PRM_FILTER_MODE_1,
  PRM_PV_OVERDRIVE = PRM_FILTER_CUTOFF_2,
  PRM_PV_FM_FEEDBACK = PRM_FILTER_RESONANCE_2,
  
  PRM_4P_MODE = PRM_FILTER_MODE_1,
  PRM_4P_FLAVOUR = PRM_FILTER_MODE_2,
  
  PRM_DELAY_TIME = PRM_FILTER_CUTOFF_2,
  PRM_DELAY_LEVEL = PRM_FILTER_RESONANCE_2,
  PRM_DELAY_FEEDBACK = PRM_FILTER_MODE_1,
  PRM_DELAY_FLAVOUR = PRM_FILTER_MODE_2
};

enum OscillatorAlgorithm {
  WAVEFORM_NONE,
  WAVEFORM_SAW,
  WAVEFORM_SQUARE,
  WAVEFORM_TRIANGLE,
  WAVEFORM_CZ_SAW,
  WAVEFORM_CZ_RESO,
  WAVEFORM_CZ_TRIANGLE,
  WAVEFORM_CZ_PULSE,
  WAVEFORM_CZ_SYNC,
  WAVEFORM_QUAD_SAW_PAD,
  WAVEFORM_FM,
  WAVEFORM_WAVETABLE_1,
  WAVEFORM_WAVETABLE_2,
  WAVEFORM_WAVETABLE_3,
  WAVEFORM_WAVETABLE_4,
  WAVEFORM_WAVETABLE_5,
  WAVEFORM_WAVETABLE_6,
  WAVEFORM_WAVETABLE_7,
  WAVEFORM_WAVETABLE_8,
  WAVEFORM_WAVETABLE_USER,
  WAVEFORM_8BITLAND,
  WAVEFORM_CRUSHED_SINE,
  WAVEFORM_DIRTY_PWM,
  WAVEFORM_FILTERED_NOISE,
  WAVEFORM_VOWEL,
  WAVEFORM_WAVETABLE_9,
  WAVEFORM_WAVETABLE_18 = WAVEFORM_WAVETABLE_9 - 1 + 10,
  WAVEFORM_LAST
};

static const uint8_t kNumHiResWavetables = 1;

enum SubOscillatorAlgorithm {
  WAVEFORM_SUB_OSC_SQUARE_1,
  WAVEFORM_SUB_OSC_TRIANGLE_1,
  WAVEFORM_SUB_OSC_PULSE_1,
  WAVEFORM_SUB_OSC_SQUARE_2,
  WAVEFORM_SUB_OSC_TRIANGLE_2,
  WAVEFORM_SUB_OSC_PULSE_2,
  WAVEFORM_SUB_OSC_CLICK,
  WAVEFORM_SUB_OSC_GLITCH,
  WAVEFORM_SUB_OSC_BLOW,
  WAVEFORM_SUB_OSC_METALLIC,
  WAVEFORM_SUB_OSC_POP,
  WAVEFORM_SUB_OSC_LAST
};

enum LfoWave {
  // For oscillators.
  LFO_WAVEFORM_TRIANGLE,
  LFO_WAVEFORM_SQUARE,
  LFO_WAVEFORM_S_H,
  LFO_WAVEFORM_RAMP,
  LFO_WAVEFORM_STEP_SEQUENCER,
  LFO_WAVEFORM_WAVE_1,
  LFO_WAVEFORM_WAVE_2,
  LFO_WAVEFORM_WAVE_3,
  LFO_WAVEFORM_WAVE_4,
  LFO_WAVEFORM_WAVE_5,
  LFO_WAVEFORM_WAVE_6,
  LFO_WAVEFORM_WAVE_7,
  LFO_WAVEFORM_WAVE_8,
  LFO_WAVEFORM_WAVE_9,
  LFO_WAVEFORM_WAVE_10,
  LFO_WAVEFORM_WAVE_11,
  LFO_WAVEFORM_WAVE_12,
  LFO_WAVEFORM_WAVE_13,
  LFO_WAVEFORM_WAVE_14,
  LFO_WAVEFORM_WAVE_15,
  LFO_WAVEFORM_WAVE_16,
  LFO_WAVEFORM_LAST
};

enum LfoMode {
  // For oscillators.
  LFO_MODE_FREE,
  LFO_MODE_SLAVE,
  LFO_MODE_MASTER,
  LFO_MODE_LAST
};

enum Status {
  OFF = 0,
  ON
};

enum Operator {
  OP_SUM,
  OP_SYNC,
  OP_RING_MOD,
  OP_XOR,
  OP_FUZZ,
  OP_CRUSH_4,
  OP_CRUSH_8,
  OP_FOLD,
  OP_BITS,
  OP_DUO,
  OP_PING_PONG_2,
  OP_PING_PONG_4,
  OP_PING_PONG_8,
  OP_PING_PONG_SEQ,
  OP_LAST
};

enum CvOperator {
  OP_CV_NONE,
  OP_CV_SUM,
  OP_CV_PRODUCT,
  OP_CV_MAX,
  OP_CV_MIN,
  OP_CV_XOR,
  OP_CV_GE,
  OP_CV_LE,
  OP_CV_QUANTIZE,
  OP_CV_LAG_PROCESSOR,
  OP_CV_LAST
};

enum MainFilterMode {
  FILTER_MODE_LP,
  FILTER_MODE_BP,
  FILTER_MODE_HP,
  
  FILTER_MODE_LP_COUPLED,
  FILTER_MODE_BP_COUPLED,
  FILTER_MODE_HP_COUPLED
};

enum SecondaryFilterMode {
  FILTER_MODE_PARALLEL_LP,
  FILTER_MODE_PARALLEL_BP,
  FILTER_MODE_PARALLEL_HP,
  FILTER_MODE_SERIAL_LP,
  FILTER_MODE_SERIAL_BP,
  FILTER_MODE_SERIAL_HP,
};

}  // namespace shruthi

#endif // SHRUTHI_PATCH_H_
