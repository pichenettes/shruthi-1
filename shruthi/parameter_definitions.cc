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
// Parameter definitions.

#include "shruthi/parameter_definitions.h"

#include <avr/pgmspace.h>

#include "shruthi/patch.h"
#include "shruthi/sequencer_settings.h"
#include "shruthi/system_settings.h"

namespace shruthi {

static const prog_char raw_parameter_definition[
    74 * sizeof(ParameterDefinition)] PROGMEM = {
  // Osc 1.
  PRM_OSC_SHAPE_1,
  WAVEFORM_NONE, WAVEFORM_LAST - 1,
  UNIT_WAVEFORM,
  STR_RES_SHAPE, STR_RES_SHAPE,

  PRM_OSC_PARAMETER_1,
  0, 127,
  UNIT_RAW_UINT8,
  STR_RES_PRM, STR_RES_PARAMETER,

  PRM_OSC_RANGE_1,
  -24, 24,
  UNIT_INT8,
  STR_RES_RNG, STR_RES_RANGE,
  
  PRM_MIX_SUB_OSC_SHAPE,
  WAVEFORM_SUB_OSC_SQUARE_1, WAVEFORM_SUB_OSC_LAST - 1,
  UNIT_SUB_OSC_WAVEFORM,
  STR_RES_SUB, STR_RES_SUBOSC,

  // Osc 2.
  PRM_OSC_SHAPE_2,
  WAVEFORM_NONE, WAVEFORM_VOWEL - 1,
  UNIT_WAVEFORM,
  STR_RES_SHAPE, STR_RES_SHAPE,

  PRM_OSC_PARAMETER_2,
  0, 127,
  UNIT_RAW_UINT8,
  STR_RES_PRM, STR_RES_PARAMETER,

  PRM_OSC_RANGE_2,
  -24, 24,
  UNIT_INT8,
  STR_RES_RNG, STR_RES_RANGE,

  PRM_OSC_OPTION_2,
  0, 127,
  UNIT_RAW_UINT8,
  STR_RES_TUNING, STR_RES_DETUNE,

  // Mix balance.
  PRM_OSC_OPTION_1,
  0, OP_LAST - 1,
  UNIT_OPERATOR,
  STR_RES_OP_, STR_RES_OPERATOR,

  PRM_MIX_BALANCE,
  0, 63,
  UNIT_UINT8,
  STR_RES_MIX, STR_RES_OSC_MIX,

  PRM_MIX_SUB_OSC,
  0, 63,
  UNIT_UINT8,
  STR_RES_SUB, STR_RES_SUB_OSC_,

  PRM_MIX_NOISE,
  0, 63,
  UNIT_UINT8,
  STR_RES_NOI, STR_RES_NOISE,

  // Filter.
  PRM_FILTER_CUTOFF,
  0, 127,
  UNIT_RAW_UINT8,
  STR_RES_CUT, STR_RES_CUTOFF,

  PRM_FILTER_RESONANCE,
  0, 63,
  UNIT_UINT8,
  STR_RES_RESONANCE, STR_RES_RESONANCE,

  PRM_FILTER_ENV,
  0, 63,
  UNIT_INT8,
  STR_RES_ENV1TVCF, STR_RES_ENV1TVCF,

  PRM_FILTER_LFO,
  0, 63,
  UNIT_INT8,
  STR_RES_LFO2TVCF, STR_RES_LFO2TVCF,

  // Env 1.
  PRM_ENV_ATTACK_1,
  0, 127,
  UNIT_RAW_UINT8,
  STR_RES_ATK, STR_RES_ATTACK,

  PRM_ENV_DECAY_1,
  0, 127,
  UNIT_RAW_UINT8,
  STR_RES_DECAY, STR_RES_DECAY,

  PRM_ENV_SUSTAIN_1,
  0, 127,
  UNIT_RAW_UINT8,
  STR_RES_SUSTAIN, STR_RES_SUSTAIN,

  PRM_ENV_RELEASE_1,
  0, 127,
  UNIT_RAW_UINT8,
  STR_RES_RELEASE, STR_RES_RELEASE,

  // Env 2.
  PRM_ENV_ATTACK_2,
  0, 127,
  UNIT_RAW_UINT8,
  STR_RES_ATK, STR_RES_ATTACK,

  PRM_ENV_DECAY_2,
  0, 127,
  UNIT_RAW_UINT8,
  STR_RES_DECAY, STR_RES_DECAY,

  PRM_ENV_SUSTAIN_2,
  0, 127,
  UNIT_RAW_UINT8,
  STR_RES_SUSTAIN, STR_RES_SUSTAIN,

  PRM_ENV_RELEASE_2,
  0, 127,
  UNIT_RAW_UINT8,
  STR_RES_RELEASE, STR_RES_RELEASE,

  // Lfo 1.
  PRM_LFO_WAVE_1,
  LFO_WAVEFORM_TRIANGLE, LFO_WAVEFORM_LAST - 1,
  UNIT_LFO_WAVEFORM,
  STR_RES_SHAPE, STR_RES_SHAPE,

  PRM_LFO_RATE_1,
  0, 127 + 16,
  UNIT_LFO_RATE,
  STR_RES_RATE, STR_RES_RATE,

  PRM_LFO_ATTACK_1,
  0, 127,
  UNIT_RAW_UINT8,
  STR_RES_ATK, STR_RES_ATTACK,

  PRM_LFO_RETRIGGER_1,
  LFO_MODE_FREE, LFO_MOD_LAST - 1,
  UNIT_LFO_RETRIGGER_MODE,
  STR_RES_MODE, STR_RES_MODE,

  // Lfo 2.
  PRM_LFO_WAVE_2,
  LFO_WAVEFORM_TRIANGLE, LFO_WAVEFORM_WAVE_16,
  UNIT_LFO_WAVEFORM,
  STR_RES_SHAPE, STR_RES_SHAPE,

  PRM_LFO_RATE_2,
  0, 127 + 16,
  UNIT_LFO_RATE,
  STR_RES_RATE, STR_RES_RATE,

  PRM_LFO_ATTACK_2,
  0, 127,
  UNIT_RAW_UINT8,
  STR_RES_ATK, STR_RES_ATTACK,

  PRM_LFO_RETRIGGER_2,
  LFO_MODE_FREE, LFO_MOD_LAST - 1,
  UNIT_LFO_RETRIGGER_MODE,
  STR_RES_MODE, STR_RES_MODE,

  // Modulations.
  PRM_MOD_ROW,
  0, kModulationMatrixSize - 1,
  UNIT_INDEX,
  STR_RES_MOD_, STR_RES_MODULATION,

  PRM_MOD_SOURCE,
  0, kNumModulationSources - 1,
  UNIT_MODULATION_SOURCE,
  STR_RES_SRC, STR_RES_SOURCE,

  PRM_MOD_DESTINATION,
  0, kNumModulationDestinations - 1,
  UNIT_MODULATION_DESTINATION,
  STR_RES_DST, STR_RES_DEST_,

  PRM_MOD_AMOUNT,
  -63, 63,
  UNIT_INT8,
  STR_RES_AMT, STR_RES_AMOUNT,

  // Sequencer.
  PRM_SEQ_MODE,
  SEQUENCER_MODE_STEP, SEQUENCER_MODE_IMPROVISATION,
  UNIT_SEQUENCER_MODE,
  STR_RES_MODE, STR_RES_MODE,

  PRM_SEQ_TEMPO,
  35, 248,
  UNIT_TEMPO_WITH_EXTERNAL_CLOCK,
  STR_RES_BPM, STR_RES_TEMPO,

  PRM_SEQ_GROOVE_TEMPLATE,
  0, STR_RES_MONKEY - STR_RES_SWING,
  UNIT_GROOVE_TEMPLATE,
  STR_RES_GROOVE, STR_RES_GROOVE,

  PRM_SEQ_GROOVE_AMOUNT,
  0, 127,
  UNIT_RAW_UINT8,
  STR_RES_AMT, STR_RES_AMOUNT,

  // Arpeggiator.
  PRM_ARP_DIRECTION,
  ARPEGGIO_DIRECTION_UP, ARPEGGIO_DIRECTION_RANDOM,
  UNIT_ARPEGGIO_DIRECTION,
  STR_RES_DIRECTION, STR_RES_DIRECTION,

  PRM_ARP_RANGE,
  1, 4,
  UNIT_INT8,
  STR_RES_RNG, STR_RES_RANGE,

  PRM_ARP_PATTERN,
  0, kNumArpeggiatorPatterns,
  UNIT_ARPEGGIO_PATTERN,
  STR_RES_PATTERN, STR_RES_PATTERN,

  PRM_ARP_WARP,
  WARP_NORMAL, WARP_GHANA_4,
  UNIT_SEQUENCER_WARP,
  STR_RES_WRP, STR_RES_WARP,

  // Keyboard and system settings.
  PRM_SYS_OCTAVE,
  -2, +2,
  UNIT_INT8,
  STR_RES_OCTAVE, STR_RES_OCTAVE,

  PRM_SYS_RAGA,
  0, 32,
  UNIT_RAGA,
  STR_RES_RAGA, STR_RES_RAGA,

  PRM_SYS_PORTAMENTO,
  0, 63,
  UNIT_UINT8,
  STR_RES_PRT, STR_RES_PORTA,

  PRM_SYS_LEGATO,
  0, 1,
  UNIT_BOOLEAN,
  STR_RES_LEGATO, STR_RES_LEGATO,

  PRM_SYS_MASTER_TUNING,
  -127, 127,
  UNIT_INT8,
  STR_RES_TUNING, STR_RES_TUNING,

  PRM_SYS_MIDI_CHANNEL,
  0, 16,
  UNIT_UINT8,
  STR_RES_CHN, STR_RES_MIDI_CHAN,

  PRM_SYS_MIDI_OUT_MODE,
  MIDI_OUT_OFF, MIDI_OUT_8_7,
  UNIT_MIDI_MODE,
  STR_RES_MIDI_OUT, STR_RES_MIDI_OUT,

  PRM_SYS_MIDI_SPLIT_POINT,
  0, 7,
  UNIT_SPLIT_POINT,
  STR_RES_SPLIT, STR_RES_SPLIT,

  // More system settings
  PRM_SYS_DISPLAY_DELAY,
  0, 16,
  UNIT_UINT8,
  STR_RES_PAUSE, STR_RES_PAUSE,
  
  PRM_SYS_DISPLAY_SNAP,
  0, 1,
  UNIT_BOOLEAN,
  STR_RES_SNAP, STR_RES_SNAP,

  PRM_SYS_EXPANSION_FILTER_BOARD,
  FILTER_BOARD_LPF, FILTER_BOARD_DSP,
  UNIT_FILTER_BOARD,
  STR_RES_FILTER, STR_RES_FILTER,
  
  PRM_SYS_EXPANSION_CV_MODE,
  CV_MODE_4CV_IN, CV_MODE_PEDALS,
  UNIT_CV_MODE,
  STR_RES_CV_MODE, STR_RES_CV_MODE,
  
  PRM_SEQ_PATTERN_ROTATION,
  0, 15,
  UNIT_UINT8,
  STR_RES_START, STR_RES_START,

  PRM_SEQ_PATTERN_SIZE,
  1, 16,
  UNIT_UINT8,
  STR_RES_LENGTH, STR_RES_LENGTH,
  
  // Operators
  PRM_OP_ROW,
  0, 1,
  UNIT_INDEX,
  STR_RES_OP_, STR_RES_OPERATOR,

  PRM_OP_OP1,
  0, kNumModulationSources - 1,
  UNIT_MODULATION_SOURCE,
  STR_RES_IN1, STR_RES_IN1,

  PRM_OP_OP2,
  0, kNumModulationSources - 1,
  UNIT_MODULATION_SOURCE,
  STR_RES_IN2, STR_RES_IN2,

  PRM_OP_OPERATOR,
  OP_CV_NONE, OP_CV_LAST - 1,
  UNIT_CV_OPERATOR,
  STR_RES_OUT, STR_RES_OUT,
  
  // Settings for SSM2044 filter board.
  PRM_FILTER_CUTOFF_2,
  0, 127,
  UNIT_RAW_UINT8,
  STR_RES_HPF, STR_RES_HPF,

  PRM_FILTER_RESONANCE_2,
  0, 0,
  UNIT_UINT8,
  STR_RES_, STR_RES_,

  PRM_FILTER_RESONANCE_2,
  0, 0,
  UNIT_INT8,
  STR_RES_, STR_RES_,

  PRM_FILTER_RESONANCE_2,
  0, 0,
  UNIT_INT8,
  STR_RES_, STR_RES_,
  
  // Settings for dual SVF filter board.
  PRM_FILTER_CUTOFF_2,
  0, 127,
  UNIT_RAW_UINT8,
  STR_RES_CUTOFF, STR_RES_CUTOFF,

  PRM_FILTER_RESONANCE_2,
  0, 63,
  UNIT_UINT8,
  STR_RES_RESONANCE, STR_RES_RESONANCE,

  PRM_FILTER_MODE_1,
  FILTER_MODE_LP, FILTER_MODE_HP,
  UNIT_FILTER_1_MODE,
  STR_RES_MD1, STR_RES_MODE_1,

  PRM_FILTER_MODE_2,
  FILTER_MODE_PARALLEL_LP, FILTER_MODE_SERIAL_HP,
  UNIT_FILTER_2_MODE,
  STR_RES_MD2, STR_RES_MODE_2,
  
  // Settings for digital filter board.
  PRM_FILTER_MODE_1,
  FILTER_MODE_LP, FILTER_MODE_HP,
  UNIT_FILTER_1_MODE,
  STR_RES_MODE, STR_RES_MODE,
  
  PRM_FX_PROGRAM,
  0, 15,
  UNIT_FX_PROGRAM,
  STR_RES_FX_, STR_RES_FX_PROG_,
  
  PRM_FX_PARAM_1,
  0, 127,
  UNIT_RAW_UINT8,
  STR_RES_PR1, STR_RES_PARAM__1,

  PRM_FX_PARAM_2,
  0, 63,
  UNIT_UINT8,
  STR_RES_PR2, STR_RES_PARAM__2,
};

/* static */
ParameterDefinition ParameterDefinitions::parameter_definition_;

/* static */
uint8_t ParameterDefinitions::parameter_definition_index_ = 0xff;

/* static */
const ParameterDefinition& ParameterDefinitions::parameter_definition(
    uint8_t index) {
  if (index != parameter_definition_index_) {
    parameter_definition_index_ = index;
    ResourcesManager::Load(
        raw_parameter_definition,
        index,
        &parameter_definition_);
  }
  return parameter_definition_;
}

/* static */
uint8_t ParameterDefinitions::offset_to_id_map_[128];

/* static */
void ParameterDefinitions::Init() {
  uint8_t i = 0;
  memset(offset_to_id_map_, 0xff, 128);
  for (uint16_t offset = 0;
       offset < sizeof(raw_parameter_definition);
       offset += sizeof(ParameterDefinition), ++i) {
    uint8_t prm = ResourcesManager::Lookup<uint8_t, uint16_t>(
        raw_parameter_definition,
        offset);
    if (prm != PRM_MOD_ROW && prm != PRM_OP_ROW) {
      offset_to_id_map_[prm] = i;
    }
  }
}

/* static */
uint8_t ParameterDefinitions::MemoryOffsetToId(uint8_t i) {
  while (offset_to_id_map_[i] == 0xff && i <= 128) {
    i -= 3;
  }
  return offset_to_id_map_[i];
}

/* static */
uint8_t ParameterDefinitions::Scale(
    const ParameterDefinition& parameter,
    uint8_t value_7bits) {
  uint8_t scaled_value;
  if (parameter.unit == UNIT_RAW_UINT8) {
    scaled_value = value_7bits;
  } else {
    uint8_t range = parameter.max_value - parameter.min_value + 1;
    scaled_value = (value_7bits * range) >> 7;
    scaled_value += parameter.min_value;
  }
  return scaled_value;
}

/* static */
uint8_t ParameterDefinitions::Increment(
    const ParameterDefinition& parameter,
    uint8_t original_value,
    int8_t increment) {
  int16_t value = original_value;
  uint8_t new_value = original_value;
  if (parameter.unit == UNIT_INT8) {
    value = static_cast<int16_t>(static_cast<int8_t>(value));
    value += increment;
    if (value >= static_cast<int8_t>(parameter.min_value) &&
        value <= static_cast<int8_t>(parameter.max_value)) {
      new_value = static_cast<uint8_t>(value);
    }
  } else {
    value += increment;
    if (value >= parameter.min_value && value <= parameter.max_value) {
      new_value = static_cast<uint8_t>(value);
    }
  }
  return new_value;
}

}  // shruti
