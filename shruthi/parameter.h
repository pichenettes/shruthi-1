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
// Parameter definitions.

#ifndef SHRUTHI_PARAMETER_H_
#define SHRUTHI_PARAMETER_H_

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
  UNIT_SEQUENCER_DIVISION,
  UNIT_GROOVE_TEMPLATE,
  UNIT_ARPEGGIO_PATTERN,
  UNIT_LFO_RETRIGGER_MODE,
  UNIT_START_PAGE,
  UNIT_PAUSE,
  UNIT_FILTER_BOARD,
  UNIT_FILTER_1_MODE,
  UNIT_FILTER_2_MODE,
  UNIT_CV_OPERATOR,
  UNIT_FX_PROGRAM,
  UNIT_FILTER_FX_MODE,
  UNIT_FILTER_4P_MODE,
  UNIT_FILTER_4P_FLAVOUR,
  UNIT_FILTER_SP_MODE,
  UNIT_LAST
};

struct Parameter {
  uint8_t offset;
  uint8_t unit;
  uint8_t min_value;
  uint8_t max_value;
  uint8_t midi_cc[2];
  uint8_t short_name;
  uint8_t long_name;
  
  uint8_t Scale(uint8_t value_7bits) const;
  uint8_t Clamp(uint8_t value) const;
  uint8_t Increment(uint8_t value, int8_t increment) const;
  uint8_t RandomValue() const;
  
  uint8_t is_snapped(uint8_t current_value, uint8_t value_7bits) const;
  
  void PrintValue(uint8_t value, char* buffer, uint8_t width) const;
};

typedef Parameter PROGMEM prog_Parameter;
const uint8_t kNumParameters = 90;

class ParameterManager {
 public:
  ParameterManager() { }
  static void Init();
  
  static const Parameter& parameter(uint8_t index);
  static uint8_t for_cc(uint8_t cc) { return cc_to_id_[cc & 0x7f]; }
  static uint8_t at_offset(uint8_t offset) {
    return offset < 160 ? offset_to_id_[offset] : 0xff;
  }

 private:
  static Parameter cached_definition_;
  static Parameter dummy_parameter_;
  static uint8_t cached_index_;

  static uint8_t offset_to_id_[160];
  static uint8_t cc_to_id_[128];
  
  DISALLOW_COPY_AND_ASSIGN(ParameterManager);
};

extern ParameterManager parameter_manager;

}  // namespace shruthi

#endif // SHRUTHI_PARAMETER_H_
