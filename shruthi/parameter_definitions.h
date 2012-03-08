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

#ifndef SHRUTHI_PARAMETER_DEFINITIONS_H_
#define SHRUTHI_PARAMETER_DEFINITIONS_H_

#include "avrlib/base.h"
#include "shruthi/resources.h"
#include "shruthi/shruthi.h"

namespace shruthi {

enum Unit {
  UNIT_RAW_UINT8,
  UNIT_UINT8,
  UNIT_INT8,
  UNIT_BOOLEAN,
  UNIT_WAVEFORM,
  UNIT_SUB_OSC_WAVEFORM,
  UNIT_OPERATOR,
  UNIT_LFO_WAVEFORM,
  UNIT_LFO_RATE,
  UNIT_INDEX,
  UNIT_MODULATION_SOURCE,
  UNIT_MODULATION_DESTINATION,
  UNIT_ARPEGGIO_DIRECTION,
  UNIT_RAGA,
  UNIT_TEMPO_WITH_EXTERNAL_CLOCK,
  UNIT_MIDI_MODE,
  UNIT_SEQUENCER_MODE,
  UNIT_SEQUENCER_WARP,
  UNIT_GROOVE_TEMPLATE,
  UNIT_ARPEGGIO_PATTERN,
  UNIT_LFO_RETRIGGER_MODE,
  UNIT_SPLIT_POINT,
  UNIT_FILTER_BOARD,
  UNIT_CV_MODE,
  UNIT_FILTER_1_MODE,
  UNIT_FILTER_2_MODE,
  UNIT_CV_OPERATOR,
  UNIT_FX_PROGRAM,
  UNIT_FILTER_FX_MODE,
  UNIT_FILTER_4P_MODE,
  UNIT_FILTER_4P_FLAVOUR,
  UNIT_LAST
};

typedef uint8_t ParameterUnit;

struct ParameterDefinition {
  uint8_t id;
  uint8_t min_value;
  uint8_t max_value;
  ParameterUnit unit;
  uint8_t short_name;
  uint8_t long_name;
};

class ParameterDefinitions {
 public:
  ParameterDefinitions() { }
  static void Init();
  static const ParameterDefinition& parameter_definition(uint8_t index);
  static uint8_t Scale(const ParameterDefinition& parameter, uint8_t value);
  static uint8_t Increment(
      const ParameterDefinition& parameter,
      uint8_t value,
      int8_t increment);
  static uint8_t MemoryOffsetToId(uint8_t i);
 private:
  static ParameterDefinition parameter_definition_;
  static uint8_t parameter_definition_index_;
  static uint8_t offset_to_id_map_[128];
  
  DISALLOW_COPY_AND_ASSIGN(ParameterDefinitions);
};

}  // namespace shruthi

#endif // SHRUTHI_PARAMETER_DEFINITIONS_H_
