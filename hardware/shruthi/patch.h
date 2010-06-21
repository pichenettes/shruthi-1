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

#ifndef HARDWARE_SHRUTHI_PATCH_H_
#define HARDWARE_SHRUTHI_PATCH_H_

#include "hardware/base/base.h"

namespace hardware_shruthi {

const uint8_t kPatchNameSize = 8;
const uint8_t kModulationMatrixSize = 12;

struct Modulation {
  uint8_t source;
  uint8_t destination;
  int8_t amount;
};

union ModulationMatrix {
  Modulation modulation[kModulationMatrixSize];
  uint8_t raw_modulation_data[kModulationMatrixSize * 3];
};

enum MidiOutMode {
  MIDI_OUT_OFF,
  MIDI_OUT_SOFT_THRU,
  MIDI_OUT_SEQUENCER,
  MIDI_OUT_SPLIT,
  MIDI_OUT_FULL,
  MIDI_OUT_1_0,
  MIDI_OUT_2_1,
  MIDI_OUT_3_4,
  MIDI_OUT_4_3,
  MIDI_OUT_5_4,
  MIDI_OUT_6_5,
  MIDI_OUT_7_6,
  MIDI_OUT_8_7,
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
  
  // Offset: 76-84
  ParameterAssignment assigned_parameters[4];
  
  // Offset: 84-92
  uint8_t padding[8];
  
  uint8_t* saved_data() { return (uint8_t*)(this); }
  void PrepareForWrite() { return; }
  uint8_t CheckBuffer(uint8_t* buffer) {
    for (uint8_t i = 8; i < 24; ++i) {
      if (buffer[i] >= 128) {
        name[0] = '?';
        return 0;
      }
    }
    if (buffer[91] != '!') {
      name[0] = '?';
      return 0;
    }
    return 1;
  }
  void Update() { }
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
};

static const uint8_t kNumModulationSources = MOD_SRC_AUDIO + 1;
static const uint8_t kNumGlobalModulationSources = MOD_SRC_NOISE + 1;
static const uint8_t kNumVoiceModulationSources = kNumModulationSources -
    kNumGlobalModulationSources;

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
  MOD_DST_2_BITS,
  MOD_DST_LFO_1,
  MOD_DST_LFO_2
};

static const uint8_t kNumModulationDestinations = MOD_DST_LFO_2 + 1;

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
};

static const uint8_t kNumHiResWavetables = 1;

enum SubOscillatorAlgorithm {
  WAVEFORM_SUB_OSC_SQUARE,
  WAVEFORM_SUB_OSC_TRIANGLE,
  WAVEFORM_SUB_OSC_CLICK,
  WAVEFORM_SUB_OSC_GLITCH,
  WAVEFORM_SUB_OSC_BLOW,
  WAVEFORM_SUB_OSC_METALLIC,
  WAVEFORM_SUB_OSC_POP
};

enum LfoWave {
  // For oscillators.
  LFO_WAVEFORM_TRIANGLE,
  LFO_WAVEFORM_SQUARE,
  LFO_WAVEFORM_S_H,
  LFO_WAVEFORM_RAMP,
  LFO_WAVEFORM_STEP_SEQUENCER,
};

enum LfoMode {
  // For oscillators.
  LFO_MODE_FREE,
  LFO_MODE_SLAVE,
  LFO_MODE_MASTER
};

enum Status {
  OFF = 0,
  ON
};

enum OPERATOR {
  OP_SUM = 0,
  OP_SYNC = 1,
  OP_RING_MOD = 2,
  OP_XOR = 3,
  OP_WAVESHAPPER = 4,
};

}  // namespace hardware_shruthi

#endif  // HARDWARE_SHRUTHI_PATCH_H_
