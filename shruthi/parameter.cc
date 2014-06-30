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

#include "shruthi/parameter.h"

#include <avr/pgmspace.h>

#include "avrlib/op.h"
#include "avrlib/random.h"
#include "avrlib/string.h"

#include "shruthi/patch.h"
#include "shruthi/sequencer_settings.h"
#include "shruthi/system_settings.h"

namespace shruthi {

using namespace avrlib;

uint8_t Parameter::Scale(uint8_t value_7bits) const {
  uint8_t scaled_value;
  if (unit == UNIT_RAW_UINT8) {
    scaled_value = value_7bits;
  } else {
    uint8_t range = max_value - min_value + 1;
    scaled_value = U8U8MulShift8(range, value_7bits << 1);
    scaled_value += min_value;
    if (unit == UNIT_TEMPO_WITH_EXTERNAL_CLOCK) {
      if (scaled_value >= 239) {
        scaled_value = 240;
      }
      scaled_value &= 0xfe;
    }
  }
  return scaled_value;
}

uint8_t Parameter::is_snapped(
    uint8_t current_value,
    uint8_t value_7bits) const {
  uint8_t scaled_value = Scale(value_7bits);
  int16_t delta;
  if (unit == UNIT_INT8) {
    delta = static_cast<int16_t>(static_cast<int8_t>(current_value)) - \
        static_cast<int8_t>(scaled_value);
  } else {
    delta = static_cast<int16_t>(static_cast<uint8_t>(current_value)) - \
        static_cast<uint8_t>(scaled_value);
  }
  if (delta < 0) {
    delta = -delta;
  }
  return delta <= static_cast<uint8_t>(max_value - min_value) >> 5;
}

uint8_t Parameter::Clamp(uint8_t value) const {
  if (unit == UNIT_INT8) {
    int8_t signed_value = static_cast<int8_t>(value);
    if (signed_value < static_cast<int8_t>(min_value)) {
      value = min_value;
    } else if (signed_value > static_cast<int8_t>(max_value)) {
      value = max_value;
    }
  } else {
    if (value < min_value) {
      value = min_value;
    } else if (value > max_value) {
      value = max_value;
    }
  }
  return value;
}

uint8_t Parameter::Increment(
    uint8_t current_value,
    int8_t increment) const {
  int16_t value = current_value;
  uint8_t new_value = current_value;
  if (unit == UNIT_INT8) {
    value = static_cast<int16_t>(static_cast<int8_t>(value));
    value += increment;
    if (value >= static_cast<int8_t>(min_value) &&
        value <= static_cast<int8_t>(max_value)) {
      new_value = static_cast<uint8_t>(value);
    }
  } else {
    value += increment;
    if (value >= min_value && value <= max_value) {
      new_value = static_cast<uint8_t>(value);
    }
  }
  return new_value;
}

uint8_t Parameter::RandomValue() const {
  uint8_t range = max_value - min_value + 1;
  uint8_t value = Random::GetByte();
  // Handle two special cases: min = max ; and range = 256.
  if (range == 0) {
    if (max_value == min_value) {
      return min_value;
    } else {
      return value;
    }
  }
  while (value >= range) {
    value -= range;
  }
  return value + min_value;
}

static const prog_uint16_t units_definitions[UNIT_LAST]
    PROGMEM = {
  0,               // UNIT_RAW_UINT8
  0,               // UNIT_UINT8
  0,               // UNIT_INT8
  STR_RES_OFF,     // UNIT_BOOLEAN
  STR_RES_NONE,    // UNIT_WAVEFORM
  STR_RES_SQ1,     // UNIT_SUB_OSC_WAVEFORM
  STR_RES_SUM,     // UNIT_OPERATOR
  STR_RES_TRI,     // UNIT_LFO_WAVEFORM
  0,               // UNIT_LFO_RATE
  0,               // UNIT_INDEX
  STR_RES_LFO_1,   // UNIT_MODULATION_SOURCE
  STR_RES_PWM1,  // UNIT_MODULATION_DESTINATION
  STR_RES_3,       // UNIT_ARPEGGIO_DIRECTION
  STR_RES_EQUAL,   // UNIT_RAGA
  0,               // UNIT_TEMPO_WITH_EXTERNAL_CLOCK
  STR_RES__OFF,    // UNIT_MIDI_MODE
  STR_RES_STP,     // UNIT_SEQUENCER_MODE
  STR_RES_1_1,     // UNIT_SEQUENCER_DIVISION
  STR_RES_SWING,   // UNIT_GROOVE_TEMPLATE
  0,               // UNIT_ARPEGGIO_PATTERN
  STR_RES_FREE,    // UNIT_LFO_RETRIGGER_MODE
  STR_RES_SPLASH,  // UNIT_START_PAGE
  0,               // UNIT_PAUSE
  STR_RES__LPF,    // UNIT_FILTER_BOARD
  STR_RES_LPF,     // UNIT_FILTER_1_MODE
  STR_RES_SLP,     // UNIT_FILTER_2_MODE
  STR_RES___OFF,   // UNIT_CV_OPERATOR
  STR_RES_DISTRT,  // UNIT_FX_PROGRAM
  STR_RES_LGF,     // UNIT_FILTER_FX_MODE
  STR_RES_LP4,     // UNIT_FILTER_4P_MODE
  STR_RES_LIQUID,  // UNIT_FILTER_4P_FLAVOUR
  STR_RES_LP,      // UNIT_FILTER_SP_MODE
};  // UNIT_LAST

static const prog_char arp_pattern_prefix[4] PROGMEM = {
  0x03, 0x04, 0x05, '?'  // Up, Down, UpDown, Random
};

void Parameter::PrintValue(uint8_t value, char* buffer, uint8_t width) const {
  ResourceId text = ResourcesManager::Lookup<uint16_t, uint8_t>(
      units_definitions,
      unit);
  char prefix = '\0';
  switch (unit) {
    case UNIT_BOOLEAN:
      if (value > 0) {
        value = 1;
      }
      break;
    case UNIT_INDEX:
      value++;
      break;
    case UNIT_MODULATION_SOURCE:
      if (width <= 4) {
        text = STR_RES_LF1;
      }
      break;
    case UNIT_MODULATION_DESTINATION:
      if (width <= 4) {
        text = STR_RES_PW1;
      }
      break;
    case UNIT_LFO_RATE:
      if (value >= 16) {
        value = value - 16;
      } else {
        ++value;
        prefix = 'x';
      }
      break;
    case UNIT_LFO_WAVEFORM:
      if (value >= LFO_WAVEFORM_WAVE_1) {
        text = NULL;
        value = value - LFO_WAVEFORM_WAVE_1 + 1;
        prefix = '\x05';
      }
      break;
    case UNIT_TEMPO_WITH_EXTERNAL_CLOCK:
      if (value < 40) {
        value = 0;
        text = STR_RES_EXTERN;
      }
      break;
    case UNIT_PAUSE:
      if (value >= 16) {
        value = value - 16;
        prefix = 's';
      }
      break;
    case UNIT_ARPEGGIO_PATTERN:
      if (value == kNumArpeggiatorPatterns) {
        value = 0;
        text = STR_RES_SEQUENCER;
      } else {
        ++value;
      }
      break;
  }
  if (prefix) {
    *buffer++ = prefix;
    --width;
  }
  if (text) {
    ResourcesManager::LoadStringResource(text + value, buffer, width);
  } else {
    int16_t v = (unit == UNIT_INT8) ? static_cast<int8_t>(value) : value;
    UnsafeItoa<int16_t>(v, width, buffer);
  }
}

static const prog_Parameter parameters[kNumParameters] PROGMEM = {
  // 0
  { PRM_OSC_SHAPE_1,
    UNIT_WAVEFORM,
    WAVEFORM_NONE, WAVEFORM_LAST - 1,
    { 20, 0 },
    STR_RES_SHAPE, STR_RES_SHAPE },
  
  // 1
  { PRM_OSC_PARAMETER_1,
    UNIT_RAW_UINT8,
    0, 127,
    { 21, 0 },
    STR_RES_PRM, STR_RES_PARAMETER },

  // 2
  { PRM_OSC_RANGE_1,
    UNIT_INT8,
    -24, 24,
    { 22, 0 },
    STR_RES_RNG, STR_RES_RANGE },

  // 3
  { PRM_MIX_SUB_OSC_SHAPE,
    UNIT_SUB_OSC_WAVEFORM,
    WAVEFORM_SUB_OSC_SQUARE_1, WAVEFORM_SUB_OSC_LAST - 1,
    { 23, 0 },
    STR_RES_SUB, STR_RES_SUBOSC },
    
  // 4
  { PRM_OSC_SHAPE_2,
    UNIT_WAVEFORM,
    WAVEFORM_NONE, WAVEFORM_LAST - 1,
    { 24, 0 },
    STR_RES_SHAPE, STR_RES_SHAPE },

  // 5
  { PRM_OSC_PARAMETER_2,
    UNIT_RAW_UINT8,
    0, 127,
    { 25, 0 },
    STR_RES_PRM, STR_RES_PARAMETER }, 

  // 6
  { PRM_OSC_RANGE_2,
    UNIT_INT8,
    -24, 24,
    { 26, 0 },
    STR_RES_RNG, STR_RES_RANGE }, 

  // 7
  { PRM_OSC_OPTION_2,
    UNIT_RAW_UINT8,
    0, 127,
    { 27, 0 },
    STR_RES_TUNING, STR_RES_DETUNE }, 

  // 8
  { PRM_OSC_OPTION_1,
    UNIT_OPERATOR,
    0, OP_LAST - 1,
    { 28, 0 },
    STR_RES_OP_, STR_RES_OPERATOR }, 

  // 9
  { PRM_MIX_BALANCE,
    UNIT_UINT8,
    0, 63,
    { 29, 0 },
    STR_RES_MIX, STR_RES_OSC_MIX }, 

  // 10
  { PRM_MIX_SUB_OSC,
    UNIT_UINT8,
    0, 63,
    { 30, 0 },
    STR_RES_SUB, STR_RES_SUB_OSC_ }, 

  // 11
  { PRM_MIX_NOISE,
    UNIT_UINT8,
    0, 63,
    { 31, 0 },
    STR_RES_NOI, STR_RES_NOISE }, 

  // 12
  { PRM_FILTER_CUTOFF,
    UNIT_RAW_UINT8,
    0, 127,
    { 14, 74 },
    STR_RES_CUT, STR_RES_CUTOFF }, 

  // 13
  { PRM_FILTER_RESONANCE,
    UNIT_UINT8,
    0, 63,
    { 15, 71 },
    STR_RES_RESONANCE, STR_RES_RESONANCE }, 

  // 14
  { PRM_FILTER_ENV,
    UNIT_INT8,
    0, 63,
    { 102, 0 },
    STR_RES_ENV1TVCF, STR_RES_ENV1TVCF }, 

  // 15
  { PRM_FILTER_LFO,
    UNIT_INT8,
    0, 63,
    { 103, 0 },
    STR_RES_LFO2TVCF, STR_RES_LFO2TVCF }, 

  // 16
  { PRM_ENV_ATTACK_1,
    UNIT_RAW_UINT8,
    0, 127,
    { 104, 0 },
    STR_RES_ATK, STR_RES_ATTACK }, 

  // 17
  { PRM_ENV_DECAY_1,
    UNIT_RAW_UINT8,
    0, 127,
    { 105, 0 },
    STR_RES_DECAY, STR_RES_DECAY }, 

  // 18
  { PRM_ENV_SUSTAIN_1,
    UNIT_RAW_UINT8,
    0, 127,
    { 106, 0 },
    STR_RES_SUSTAIN, STR_RES_SUSTAIN }, 

  // 19
  { PRM_ENV_RELEASE_1,
    UNIT_RAW_UINT8,
    0, 127,
    { 107, 0 },
    STR_RES_RELEASE, STR_RES_RELEASE }, 

  // 20
  { PRM_ENV_ATTACK_2,
    UNIT_RAW_UINT8,
    0, 127,
    { 108, 73 },
    STR_RES_ATK, STR_RES_ATTACK }, 

  // 21
  { PRM_ENV_DECAY_2,
    UNIT_RAW_UINT8,
    0, 127,
    { 109, 0 },
    STR_RES_DECAY, STR_RES_DECAY }, 

  // 22
  { PRM_ENV_SUSTAIN_2,
    UNIT_RAW_UINT8,
    0, 127,
    { 110, 0 },
    STR_RES_SUSTAIN, STR_RES_SUSTAIN }, 

  // 23
  { PRM_ENV_RELEASE_2,
    UNIT_RAW_UINT8,
    0, 127,
    { 111, 72 },
    STR_RES_RELEASE, STR_RES_RELEASE }, 

  // 24
  { PRM_LFO_WAVE_1,
    UNIT_LFO_WAVEFORM,
    LFO_WAVEFORM_TRIANGLE, LFO_WAVEFORM_LAST - 1,
    { 112, 0 },
    STR_RES_SHAPE, STR_RES_SHAPE }, 

  // 25
  { PRM_LFO_RATE_1,
    UNIT_LFO_RATE,
    0, 127 + 16,
    { 113, 0 },
    STR_RES_RATE, STR_RES_RATE }, 

  // 26
  { PRM_LFO_ATTACK_1,
    UNIT_RAW_UINT8,
    0, 127,
    { 114, 0 },
    STR_RES_ATK, STR_RES_ATTACK }, 

  // 27
  { PRM_LFO_RETRIGGER_1,
    UNIT_LFO_RETRIGGER_MODE,
    LFO_MODE_FREE, LFO_MODE_LAST - 1,
    { 115, 0 },
    STR_RES_MODE, STR_RES_MODE }, 

  // 28
  { PRM_LFO_WAVE_2,
    UNIT_LFO_WAVEFORM,
    LFO_WAVEFORM_TRIANGLE, LFO_WAVEFORM_WAVE_16,
    { 116, 0 },
    STR_RES_SHAPE, STR_RES_SHAPE }, 

  // 29
  { PRM_LFO_RATE_2,
    UNIT_LFO_RATE,
    0, 127 + 16,
    { 117, 0 },
    STR_RES_RATE, STR_RES_RATE }, 

  // 30
  { PRM_LFO_ATTACK_2,
    UNIT_RAW_UINT8,
    0, 127,
    { 118, 0 },
    STR_RES_ATK, STR_RES_ATTACK }, 

  // 31
  { PRM_LFO_RETRIGGER_2,
    UNIT_LFO_RETRIGGER_MODE,
    LFO_MODE_FREE, LFO_MODE_LAST - 1,
    { 119, 0 },
    STR_RES_MODE, STR_RES_MODE }, 

  // 32
  { PRM_MOD_ROW,
    UNIT_INDEX,
    0, kModulationMatrixSize - 1,
    { 0, 0 },
    STR_RES_MOD_, STR_RES_MODULATION }, 

  // 33
  { PRM_MOD_SOURCE,
    UNIT_MODULATION_SOURCE,
    0, MOD_SRC_OP_2,
    { 0, 0 },
    STR_RES_SRC, STR_RES_SOURCE }, 

  // 34
  { PRM_MOD_DESTINATION,
    UNIT_MODULATION_DESTINATION,
    0, kNumModulationDestinations - 1,
    { 0, 0 },
    STR_RES_DST, STR_RES_DEST_ }, 

  // 35
  { PRM_MOD_AMOUNT,
    UNIT_INT8,
    -63, 63,
    { 0, 0 },
    STR_RES_AMT, STR_RES_AMOUNT }, 

  // 36
  { PRM_SEQ_MODE,
    UNIT_SEQUENCER_MODE,
    SEQUENCER_MODE_STEP, SEQUENCER_MODE_SEQ,
    { 75, 0 },
    STR_RES_MODE, STR_RES_MODE }, 

  // 37
  { PRM_SEQ_TEMPO,
    UNIT_TEMPO_WITH_EXTERNAL_CLOCK,
    39, 240,
    { 0, 0 },
    STR_RES_BPM, STR_RES_TEMPO }, 

  // 38
  { PRM_SEQ_GROOVE_TEMPLATE,
    UNIT_GROOVE_TEMPLATE,
    0, STR_RES_MONKEY - STR_RES_SWING,
    { 76, 0 },
    STR_RES_GROOVE, STR_RES_GROOVE }, 

  // 39
  { PRM_SEQ_GROOVE_AMOUNT,
    UNIT_RAW_UINT8,
    0, 127,
    { 77, 0 },
    STR_RES_AMT, STR_RES_AMOUNT }, 

  // 40
  { PRM_ARP_DIRECTION,
    UNIT_ARPEGGIO_DIRECTION,
    ARPEGGIO_DIRECTION_UP, ARPEGGIO_DIRECTION_PLAYED,
    { 78, 0 },
    STR_RES_DIRECTION, STR_RES_DIRECTION }, 

  // 41
  { PRM_ARP_RANGE,
    UNIT_INT8,
    1, 4,
    { 79, 0 },
    STR_RES_RNG, STR_RES_RANGE }, 

  // 42
  { PRM_ARP_PATTERN,
    UNIT_ARPEGGIO_PATTERN,
    0, kNumArpeggiatorPatterns,
    { 80, 0 },
    STR_RES_PATTERN, STR_RES_PATTERN }, 

  // 43
  { PRM_ARP_DIVISION,
    UNIT_SEQUENCER_DIVISION,
    0, 11,
    { 81, 0 },
    STR_RES_DIVISION, STR_RES_DIVISION }, 

  // 44
  { PRM_SYS_OCTAVE,
    UNIT_INT8,
    -2, +2,
    { 82, 0 },
    STR_RES_OCTAVE, STR_RES_OCTAVE }, 

  // 45
  { PRM_SYS_RAGA,
    UNIT_RAGA,
    0, 32,
    { 83, 0 },
    STR_RES_RAGA, STR_RES_RAGA }, 

  // 46
  { PRM_SYS_PORTAMENTO,
    UNIT_UINT8,
    0, 63,
    { 84, 5 },
    STR_RES_PRT, STR_RES_PORTA }, 

  // 47
  { PRM_SYS_LEGATO,
    UNIT_BOOLEAN,
    0, 1,
    { 68, 0 },
    STR_RES_LEGATO, STR_RES_LEGATO }, 

  // 48
  { PRM_SYS_MASTER_TUNING,
    UNIT_INT8,
    -127, 127,
    { 0, 0 },
    STR_RES_TUNING, STR_RES_TUNING }, 

  // 49
  { PRM_SYS_MIDI_CHANNEL,
    UNIT_UINT8,
    0, 16,
    { 0, 0 },
    STR_RES_CHN, STR_RES_MIDI_CHAN }, 

  // 50
  { PRM_SYS_MIDI_OUT_MODE,
    UNIT_MIDI_MODE,
    MIDI_OUT_OFF, MIDI_OUT_8_7,
    { 0, 0 },
    STR_RES_MIDI_OUT, STR_RES_MIDI_OUT }, 

  // 51
  { PRM_SYS_MIDI_OUT_MODE,
    UNIT_MIDI_MODE,
    MIDI_OUT_OFF, MIDI_OUT_8_7,
    { 0, 0 },
    STR_RES_MIDI_OUT, STR_RES_MIDI_OUT },

  // 52
  { PRM_SYS_DISPLAY_DELAY,
    UNIT_PAUSE,
    0, 31,
    { 0, 0 },
    STR_RES_PAUSE, STR_RES_PAUSE }, 

  // 53
  { PRM_SYS_DISPLAY_SNAP,
    UNIT_BOOLEAN,
    0, 1,
    { 0, 0 },
    STR_RES_SNAP, STR_RES_SNAP }, 

  // 54
  { PRM_SYS_EXPANSION_FILTER_BOARD,
    UNIT_FILTER_BOARD,
    FILTER_BOARD_LPF, FILTER_BOARD_LAST - 1,
    { 0, 0 },
    STR_RES_FILTER, STR_RES_FILTER }, 

  // 55
  { PRM_SYS_START_PAGE,
    UNIT_START_PAGE,
    0, 2,
    { 0, 0 },
    STR_RES_STARTPAGE, STR_RES_STARTPAGE }, 

  // 56
  { PRM_SEQ_PATTERN_ROTATION,
    UNIT_UINT8,
    0, 15,
    { 0, 0 },
    STR_RES_START, STR_RES_START }, 

  // 57
  { PRM_SEQ_PATTERN_SIZE,
    UNIT_UINT8,
    1, 16,
    { 0, 0 },
    STR_RES_LENGTH, STR_RES_LENGTH }, 

  // 58
  { PRM_OP_ROW,
    UNIT_INDEX,
    0, 1,
    { 0, 0 },
    STR_RES_OP_, STR_RES_OPERATOR }, 

  // 59
  { PRM_OP_OP1,
    UNIT_MODULATION_SOURCE,
    0, kNumModulationSources - 1,
    { 0, 0 },
    STR_RES_IN1, STR_RES_IN1 }, 

  // 60,
  { PRM_OP_OP2,
    UNIT_MODULATION_SOURCE,
    0, kNumModulationSources - 1,
    { 0, 0 },
    STR_RES_IN2, STR_RES_IN2 }, 

  // 61
  { PRM_OP_OPERATOR,
    UNIT_CV_OPERATOR,
    OP_CV_NONE, OP_CV_LAST - 1,
    { 0, 0 },
    STR_RES_OUT, STR_RES_OUT }, 

  // 62
  { PRM_FILTER_CUTOFF,
    UNIT_RAW_UINT8,
    0, 127,
    { 14, 0 },
    STR_RES_CUT, STR_RES_CUTOFF }, 

  // 63
  { PRM_FILTER_RESONANCE,
    UNIT_UINT8,
    0, 63,
    { 15, 0 },
    STR_RES_RESONANCE, STR_RES_RESONANCE }, 

  // 64
  { PRM_FILTER_ENV,
    UNIT_INT8,
    0, 63,
    { 102, 0 },
    STR_RES_ENV1TVCF, STR_RES_ENV1TVCF }, 

  // 65
  { PRM_FILTER_CUTOFF_2,
    UNIT_RAW_UINT8,
    0, 127,
    { 12, 0 },
    STR_RES_HPF, STR_RES_HPF }, 

  // 66
  { PRM_FILTER_CUTOFF_2,
    UNIT_RAW_UINT8,
    0, 127,
    { 12, 0 },
    STR_RES_CUTOFF, STR_RES_CUTOFF }, 

  // 67
  { PRM_FILTER_RESONANCE_2,
    UNIT_UINT8,
    0, 63,
    { 13, 0 },
    STR_RES_RESONANCE, STR_RES_RESONANCE }, 

  // 68
  { PRM_FILTER_MODE_1,
    UNIT_FILTER_1_MODE,
    FILTER_MODE_LP, FILTER_MODE_HP_COUPLED,
    { 85, 0 },
    STR_RES_MD1, STR_RES_MODE_1 }, 

  // 69
  { PRM_FILTER_MODE_2,
    UNIT_FILTER_2_MODE,
    FILTER_MODE_PARALLEL_LP, FILTER_MODE_SERIAL_HP,
    { 86, 0 },
    STR_RES_MD2, STR_RES_MODE_2 }, 

  // 70
  { PRM_FILTER_MODE_1,
    UNIT_FILTER_FX_MODE,
    0, 4,
    { 87, 0 },
    STR_RES_MODE, STR_RES_MODE }, 

  // 71
  { PRM_FX_PROGRAM,
    UNIT_FX_PROGRAM,
    0, 15,
    { 88, 0 },
    STR_RES_FX_, STR_RES_FX_PROG_ }, 

  // 72
  { PRM_FX_PARAM_1,
    UNIT_RAW_UINT8,
    0, 127,
    { 12, 0 },
    STR_RES_PR1, STR_RES_PARAM__1 }, 

  // 73
  { PRM_FX_PARAM_2,
    UNIT_UINT8,
    0, 63,
    { 13, 0 },
    STR_RES_PR2, STR_RES_PARAM__2 }, 

  // 74
  { PRM_FILTER_CUTOFF,
    UNIT_RAW_UINT8,
    0, 127,
    { 14, 0 },
    STR_RES_CUT, STR_RES_CUTOFF }, 

  // 75
  { PRM_PV_MODE,
    UNIT_FILTER_1_MODE,
    FILTER_MODE_LP, FILTER_MODE_BP,
    { 89, 0 },
    STR_RES_MODE, STR_RES_MODE }, 

  // 76
  { PRM_PV_OVERDRIVE,
    UNIT_BOOLEAN,
    0, 1,
    { 90, 0 },
    STR_RES_OVERDRIVE, STR_RES_OVERDRIVE }, 

  // 77
  { PRM_PV_FM_FEEDBACK,
    UNIT_BOOLEAN,
    0, 1,
    { 91, 0 },
    STR_RES__FM, STR_RES__FM }, 

  // 78
  { PRM_FILTER_CUTOFF,
    UNIT_RAW_UINT8,
    0, 127,
    { 14, 0 },
    STR_RES_CUT, STR_RES_CUTOFF }, 

  // 79
  { PRM_FILTER_RESONANCE,
    UNIT_UINT8,
    0, 63,
    { 15, 0 },
    STR_RES_RESONANCE, STR_RES_RESONANCE }, 

  // 80
  { PRM_4P_MODE,
    UNIT_FILTER_4P_MODE,
    0, 14,
    { 92, 0 },
    STR_RES_MODE, STR_RES_MODE }, 

  // 81
  { PRM_4P_FLAVOUR,
    UNIT_FILTER_4P_FLAVOUR,
    0, 3,
    { 93, 0 },
    STR_RES_FLAVOUR, STR_RES_FLAVOUR }, 

  // 82
  { PRM_DELAY_TIME,
    UNIT_RAW_UINT8,
    0, 127,
    { 12, 0 },
    STR_RES_TIME, STR_RES_TIME }, 

  // 83
  { PRM_DELAY_LEVEL,
    UNIT_UINT8,
    0, 63,
    { 13, 0 },
    STR_RES_LEVEL, STR_RES_LEVEL }, 

  // 84
  { PRM_DELAY_FEEDBACK,
    UNIT_UINT8,
    0, 15,
    { 94, 0 },
    STR_RES_FDB, STR_RES_FEEDBACK }, 

  // 85
  { PRM_DELAY_FLAVOUR,
    UNIT_UINT8,
    0, 15,
    { 95, 0 },
    STR_RES_EQ_, STR_RES_FDBCK_EQ_ },
    
  // 86
  { PRM_FILTER_CUTOFF,
    UNIT_RAW_UINT8,
    0, 127,
    { 14, 0 },
    STR_RES_CUT, STR_RES_CUTOFF }, 

  // 87
  { PRM_FILTER_RESONANCE,
    UNIT_UINT8,
    0, 63,
    { 15, 0 },
    STR_RES_RESONANCE, STR_RES_RESONANCE }, 

  // 88
  { PRM_SP_MODE,
    UNIT_FILTER_SP_MODE,
    0, 3,
    { 96, 0 },
    STR_RES_MODE, STR_RES_MODE }, 

  // 89
  { PRM_SP_FEEDBACK,
    UNIT_RAW_UINT8,
    0, 127,
    { 12, 0 },
    STR_RES_FDB, STR_RES_FEEDBACK }, 
};

/* static */
Parameter ParameterManager::cached_definition_;

/* static */
Parameter ParameterManager::dummy_parameter_ = {
  0xff, UNIT_UINT8, 0, 255, { 0, 0 }, 0, 0,
};

/* static */
uint8_t ParameterManager::cached_index_ = 0xff;

/* static */
uint8_t ParameterManager::offset_to_id_[160];

/* static */
uint8_t ParameterManager::cc_to_id_[128];

/* static */
void ParameterManager::Init() {
  memset(offset_to_id_, 0xff, 192);
  memset(cc_to_id_, 0xff, 128);
  for (uint8_t i = 0; i < kNumParameters; ++i) {
    const Parameter& p = parameter(i);
    if (p.offset < 160) {
      offset_to_id_[p.offset] = i;
    }
    if (p.midi_cc[0]) {
      cc_to_id_[p.midi_cc[0]] = i;
    }
    if (p.midi_cc[1]) {
      cc_to_id_[p.midi_cc[1]] = i;
    }
  }
  
  // Hack for NRPN ranges of the filter mode 1 & 2 parameters.
  offset_to_id_[92] = 84;
  offset_to_id_[93] = 85;
  
  // Fill modulation matrix gaps
  for (uint8_t i = 0; i < kModulationMatrixSize; ++i) {
    offset_to_id_[PRM_MOD_SOURCE + i * 3] = 33;
    offset_to_id_[PRM_MOD_SOURCE + i * 3 + 1] = 34;
    offset_to_id_[PRM_MOD_SOURCE + i * 3 + 2] = 35;
  }
  for (uint8_t i = 0; i < 2; ++i) {
    offset_to_id_[PRM_OP_OP1 + i * 3] = 59;
    offset_to_id_[PRM_OP_OP1 + i * 3 + 1] = 60;
    offset_to_id_[PRM_OP_OP1 + i * 3 + 2] = 61;
  }
  
}

/* static */
const Parameter& ParameterManager::parameter(
    uint8_t index) {
  if (index == 0xfe) {
    return dummy_parameter_;
  }
  if (index != cached_index_) {
    ResourcesManager::Load(
        parameters,
        index,
        &cached_definition_);
    cached_index_ = index;
  }
  return cached_definition_;
}

/* extern */
ParameterManager parameter_manager;

}  // shruti
