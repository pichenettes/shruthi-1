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
// Patch editor.
//
// I really hate this code. Work on a "UI" framework to avoid such horrible
// things in progress...

#include "hardware/shruthi/editor.h"

#include "hardware/hal/devices/switch_array.h"
#include "hardware/hal/watchdog_timer.h"
#include "hardware/shruthi/display.h"
#include "hardware/shruthi/storage.h"
#include "hardware/shruthi/synthesis_engine.h"
#include "hardware/utils/string.h"

using namespace hardware_hal;
using namespace hardware_utils;

using hardware_hal::kLcdNoCursor;

namespace hardware_shruthi {

/* extern */
Editor editor;

static const prog_char units_definitions[UNIT_LFO_RETRIGGER_MODE + 1]
    PROGMEM = {
  0,
  0,
  0,
  STR_RES_OFF,
  STR_RES_NONE,
  STR_RES_1S2,
  STR_RES_TRI,
  0,
  0,
  STR_RES_LFO_1,
  STR_RES_CUTOFF,
  STR_RES_3,
  STR_RES_EQUAL,
  0,
  STR_RES__OFF,
  STR_RES_STP,
  STR_RES_T,
  STR_RES_KBD,
  0,
  STR_RES_FREE
};

static const prog_char arp_pattern_prefix[4] PROGMEM = {
  0x03, 0x04, 0x05, '?'  // Up, Down, UpDown, Random
};

static const prog_char raw_parameter_definition[
    52 * sizeof(ParameterDefinition)] PROGMEM = {
  // Osc 1.
  PRM_OSC_SHAPE_1,
  WAVEFORM_NONE, WAVEFORM_VOWEL,
  UNIT_WAVEFORM,
  STR_RES_SHAPE, STR_RES_SHAPE,

  PRM_OSC_PARAMETER_1,
  0, 127,
  UNIT_RAW_UINT8,
  STR_RES_PRM, STR_RES_PARAMETER,

  PRM_OSC_RANGE_1,
  -12, 12,
  UNIT_INT8,
  STR_RES_RNG, STR_RES_RANGE,

  PRM_OSC_OPTION_1,
  SUM, XOR,
  UNIT_OPERATOR,
  STR_RES_OP_, STR_RES_OPERATOR,

  // Osc 2.
  PRM_OSC_SHAPE_2,
  WAVEFORM_NONE, WAVEFORM_FILTERED_NOISE,
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
  PRM_MIX_BALANCE,
  0, 63,
  UNIT_UINT8,
  STR_RES_MIX, STR_RES_OSC_BAL,

  PRM_MIX_SUB_OSC,
  0, 63,
  UNIT_UINT8,
  STR_RES_SUB, STR_RES_SUB_OSC_,

  PRM_MIX_NOISE,
  0, 63,
  UNIT_UINT8,
  STR_RES_NOI, STR_RES_NOISE,

  PRM_MIX_SUB_OSC_SHAPE,
  WAVEFORM_SQUARE, WAVEFORM_TRIANGLE,
  UNIT_WAVEFORM, 
  STR_RES_SHAPE, STR_RES_SHAPE,

  // Filter.
  PRM_FILTER_CUTOFF,
  0, 127,
  UNIT_RAW_UINT8,
  STR_RES_CUT, STR_RES_CUTOFF,

  PRM_FILTER_RESONANCE,
  0, 63,
  UNIT_UINT8,
  STR_RES_RES, STR_RES_RESONANCE,

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
  LFO_WAVEFORM_TRIANGLE, LFO_WAVEFORM_STEP_SEQUENCER,
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
  LFO_MODE_FREE, LFO_MODE_MASTER,
  UNIT_LFO_RETRIGGER_MODE,
  STR_RES_MODE, STR_RES_MODE,

  // Lfo 2.
  PRM_LFO_WAVE_2,
  LFO_WAVEFORM_TRIANGLE, LFO_WAVEFORM_STEP_SEQUENCER,
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
  LFO_MODE_FREE, LFO_MODE_MASTER,
  UNIT_LFO_RETRIGGER_MODE,
  STR_RES_MODE, STR_RES_MODE,

  // Modulations.
  PRM_MOD_ROW,
  0, kModulationMatrixSize - 1,
  UNIT_INDEX,
  STR_RES_MOD_, STR_RES_MOD_,

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
  24, 240 + STR_RES_960 - STR_RES_270 + 1,
  UNIT_TEMPO_WITH_EXTERNAL_CLOCK,
  STR_RES_BPM, STR_RES_TEMPO,
  
  PRM_SEQ_SWING,
  0, 127, 
  UNIT_RAW_UINT8,
  STR_RES_SWG, STR_RES_SWING,
  
  PRM_SEQ_FLOW,
  FLOW_NORMAL, FLOW_GHANA_4,
  UNIT_SEQUENCER_FLOW,
  STR_RES_FLOW, STR_RES_FLOW,
  
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
  
  PRM_ARP_VELOCITY_SOURCE,
  ARPEGGIO_VELOCITY_SOURCE_KEYBOARD, ARPEGGIO_VELOCITY_SOURCE_SEQUENCE,
  UNIT_ARPEGGIO_VELOCITY_SOURCE,
  STR_RES_VELO, STR_RES_VELO,

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
  MIDI_OUT_OFF, MIDI_OUT_DAISY_CHAIN,
  UNIT_MIDI_MODE,
  STR_RES_MIDI_OUT, STR_RES_MIDI_OUT,

  PRM_SYS_MIDI_OUT_CHAIN,
  1, 8,
  UNIT_UINT8,
  STR_RES_POLY, STR_RES_POLY
};

/* static */
const UiHandler Editor::ui_handler_[] = {
  { &Editor::DisplayEditOverviewPage, &Editor::DisplayEditDetailsPage,
    &Editor::HandleEditInput, &Editor::HandleEditIncrement },
  { &Editor::DisplayTrackerPage, &Editor::DisplayTrackerPage,
    &Editor::HandleTrackerInput, &Editor::HandleTrackerIncrement },
  { &Editor::DisplayPageRPage, &Editor::DisplayPageRPage,
    &Editor::HandlePageRInput, &Editor::HandlePageRIncrement },
  { &Editor::DisplayStepSequencerPage, &Editor::DisplayStepSequencerPage,
    &Editor::HandleStepSequencerInput, &Editor::HandleStepSequencerIncrement },
  { &Editor::DisplayLoadSavePage, &Editor::DisplayLoadSavePage,
    &Editor::HandleLoadSaveInput, &Editor::HandleLoadSaveIncrement },
};

const PageDefinition Editor::page_definition_[] = {
  /* PAGE_OSC_OSC_1 */ { PAGE_OSC_OSC_2, GROUP_OSC,
    PAGE_MOD_MATRIX, PAGE_OSC_OSC_2,
    STR_RES_OSCILLATOR_1, PARAMETER_EDITOR, 0, LED_OSC_1_MASK },

  /* PAGE_OSC_OSC_2 */ { PAGE_OSC_OSC_MIX, GROUP_OSC,
    PAGE_OSC_OSC_1, PAGE_OSC_OSC_MIX,
    STR_RES_OSCILLATOR_2, PARAMETER_EDITOR, 4, LED_OSC_2_MASK },

  /* PAGE_OSC_OSC_MIX */ { PAGE_OSC_OSC_1, GROUP_OSC,
    PAGE_OSC_OSC_2, PAGE_FILTER_FILTER,
    STR_RES_MIXER, PARAMETER_EDITOR, 8, LED_OSC_1_MASK | LED_OSC_2_MASK },

  /* PAGE_FILTER_FILTER */ { PAGE_FILTER_FILTER, GROUP_FILTER,
    PAGE_OSC_OSC_MIX, PAGE_MOD_ENV_1,
    STR_RES_FILTER, PARAMETER_EDITOR, 12, LED_FILTER_MASK },

  /* PAGE_MOD_ENV_1 */ { PAGE_MOD_ENV_2, GROUP_MOD,
    PAGE_FILTER_FILTER, PAGE_MOD_ENV_2,
    STR_RES_ENVELOPE_1, PARAMETER_EDITOR, 16, LED_MOD_1_MASK },

  /* PAGE_MOD_ENV_2 */ { PAGE_MOD_LFO_1, GROUP_MOD,
    PAGE_MOD_ENV_1, PAGE_MOD_LFO_1,
    STR_RES_ENVELOPE_2, PARAMETER_EDITOR, 20, LED_MOD_2_MASK },

  /* PAGE_MOD_LFO_1 */ { PAGE_MOD_LFO_2, GROUP_MOD,
    PAGE_MOD_ENV_2, PAGE_MOD_LFO_2,
    STR_RES_LFO_1, PARAMETER_EDITOR, 24, LED_MOD_1_MASK },

  /* PAGE_MOD_LFO_2 */ { PAGE_MOD_MATRIX, GROUP_MOD,
    PAGE_MOD_LFO_1, PAGE_MOD_MATRIX,
    STR_RES_LFO_2, PARAMETER_EDITOR, 28, LED_MOD_2_MASK },

  /* PAGE_MOD_MATRIX */ { PAGE_MOD_ENV_1, GROUP_MOD,
    PAGE_MOD_LFO_2, PAGE_OSC_OSC_1,
    STR_RES_MODULATION, PARAMETER_EDITOR, 32, LED_MOD_1_MASK | LED_MOD_2_MASK },

  /* PAGE_SEQ_SEQUENCER */ { PAGE_SEQ_ARPEGGIATOR, GROUP_SEQUENCER,
    PAGE_SEQ_CONTROLLER, PAGE_SEQ_ARPEGGIATOR,
    STR_RES_SEQUENCER, PARAMETER_EDITOR, 36, LED_SEQUENCER_MASK },

  /* PAGE_SEQ_ARPEGGIATOR */ { PAGE_SEQ_TRACKER, GROUP_SEQUENCER,
    PAGE_SEQ_SEQUENCER, PAGE_SEQ_TRACKER,
    STR_RES_ARPEGGIO, PARAMETER_EDITOR, 40, LED_SEQUENCER_MASK },

  /* PAGE_SEQ_TRACKER */ { PAGE_SEQ_RHYTHM, GROUP_SEQUENCER,
    PAGE_SEQ_ARPEGGIATOR, PAGE_SEQ_RHYTHM,
    STR_RES_STEP_SEQUENCER, TRACKER_EDITOR, 0, LED_SEQUENCER_MASK },

  /* PAGE_SEQ_RHYTHM */ { PAGE_SEQ_CONTROLLER, GROUP_SEQUENCER,
    PAGE_SEQ_TRACKER, PAGE_SEQ_CONTROLLER,
    STR_RES_STEP_SEQUENCER, PAGE_R_EDITOR, 0, LED_SEQUENCER_MASK },

  /* PAGE_SEQ_CONTROLLER */ { PAGE_SEQ_SEQUENCER, GROUP_SEQUENCER,
    PAGE_SEQ_RHYTHM, PAGE_SEQ_SEQUENCER,
    STR_RES_STEP_SEQUENCER, STEP_SEQUENCER, 0, LED_SEQUENCER_MASK },

  /* PAGE_SYS_KBD */ { PAGE_SYS_MIDI, GROUP_SYS,
    PAGE_SYS_MIDI, PAGE_SYS_MIDI,
    STR_RES_KEYBOARD, PARAMETER_EDITOR, 44, LED_SYS_MASK },

  /* PAGE_SYS_MIDI */ { PAGE_SYS_KBD, GROUP_SYS,
    PAGE_SYS_KBD, PAGE_SYS_KBD,
    STR_RES_MIDI, PARAMETER_EDITOR, 48, LED_SYS_MASK },

  /* PAGE_LOAD_SAVE */ { PAGE_LOAD_SAVE, GROUP_LOAD_SAVE,
    PAGE_LOAD_SAVE, PAGE_LOAD_SAVE,
    STR_RES_PATCHES, LOAD_SAVE, 0, LED_WRITE_MASK },

  /* PAGE_PERFORMANCE */ { PAGE_PERFORMANCE, GROUP_PERFORMANCE,
    PAGE_PERFORMANCE, PAGE_PERFORMANCE,
    STR_RES_PERFORMANCE, PARAMETER_EDITOR, 0, 0x0 }
};

/* <static> */
ParameterDefinition Editor::parameter_definition_;
uint8_t Editor::parameter_definition_index_ = 0xff;

ParameterPage Editor::current_page_ = PAGE_FILTER_FILTER;
ParameterPage Editor::last_visited_page_[kNumGroups] = {
    PAGE_LOAD_SAVE,
    PAGE_SYS_KBD,
    PAGE_SEQ_SEQUENCER,
    PAGE_MOD_ENV_1,
    PAGE_FILTER_FILTER,
    PAGE_OSC_OSC_1,
    PAGE_PERFORMANCE
};
uint8_t Editor::last_visited_subpage_ = 0;
uint8_t Editor::mode_ = EDITOR_MODE_OVERVIEW;

char Editor::line_buffer_[kLcdWidth * kLcdHeight + 1];

uint8_t Editor::cursor_;
uint8_t Editor::subpage_;
uint8_t Editor::action_;
uint8_t Editor::current_patch_number_ = 0;
uint8_t Editor::previous_patch_number_ = 0;
uint8_t Editor::current_sequence_number_ = 0;
uint8_t Editor::previous_sequence_number_ = 0;

uint8_t Editor::test_note_playing_ = 0;
uint8_t Editor::assign_in_progress_ = 0;
ParameterAssignment Editor::assigned_parameters_[kNumEditingPots] = {
  { 1, 0 },
  { PRM_FILTER_CUTOFF, 0 },
  { PRM_FILTER_ENV, 0 },
  { 25, 0 },
};
ParameterAssignment Editor::parameter_to_assign_;
/* </static> */

/* static */
void Editor::Init() {
  line_buffer_[kLcdWidth] = '\0';
}

/* static */
void Editor::ToggleGroup(uint8_t group) {
  cursor_ = 0;
  assign_in_progress_ = 0;
  display.set_cursor_position(kLcdNoCursor);

  mode_ = EDITOR_MODE_OVERVIEW;

  // Special case for the load/save page.
  if (group == GROUP_LOAD_SAVE) {
    EnterLoadSaveMode();
    current_page_ = PAGE_LOAD_SAVE;
  } else {
    subpage_ = 0;
    // Make sure that we won't confirm a save when moving back to the
    // Load/save page.
    action_ = ACTION_EXIT;
    // If we move to another group, go to the last visited page in this group.
    if (group != page_definition_[current_page_].group) {
      current_page_ = last_visited_page_[group];
    } else {
      current_page_ = page_definition_[current_page_].next;
    }
    // When switching to the modulation matrix page, go back to the previously
    // edited modulation.
    if (current_page_ == PAGE_MOD_MATRIX) {
      subpage_ = last_visited_subpage_;
    }
    last_visited_page_[group] = current_page_;
  }
}

/* static */
void Editor::Relax() {
  // Disable the "get back to overview page" thing in the sequencer pages or
  // Load/save pages - in short, all pages where there's a moving cursor.
  if (mode_ != EDITOR_MODE_OVERVIEW &&
      display.cursor_position() == kLcdNoCursor) {
    mode_ = EDITOR_MODE_OVERVIEW;
    Refresh();
  }
}

/* static */
void Editor::RandomizeParameter(uint8_t subpage, uint8_t parameter_index) {
  const ParameterDefinition& parameter = parameter_definition(parameter_index);
  uint8_t range = parameter.max_value - parameter.min_value + 1;
  uint8_t value = Random::GetByte();
  while (value >= range) {
    value -= range;
  }
  value += parameter.min_value;
  engine.SetParameter(parameter.id + subpage * 3, value);
}

/* static */
void Editor::RandomizePatch() {
  // Randomize all the main parameters
  for (uint8_t parameter = 0; parameter < 32; ++parameter) {
    RandomizeParameter(0, parameter);
  }
  for (uint8_t slot = 0; slot < kModulationMatrixSize; ++slot) {
    for (uint8_t parameter = 33; parameter < 36; ++parameter) {
      RandomizeParameter(slot, parameter);
    }
  }
}

/* static */
void Editor::RandomizeSequence() {
  for (uint8_t i = 0; i < kNumSteps; ++i) {
    SequencerSettings* settings = engine.mutable_sequencer_settings();
    settings->steps[i].set_raw(
        Random::GetByte(),
        Random::GetByte());
    settings->steps[i].set_note(
        (settings->steps[i].note() & 0x3f) + 0x20);
  }
}

/* static */
void Editor::HandleKeyEvent(const KeyEvent& event) {
  if (event.shifted) {
    switch (event.id) {
      case GROUP_OSC:
        display.set_status('x');
        if (subpage_ == LOAD_SAVE_PATCH) {
          engine.ResetPatch();
        } else if (subpage_ == LOAD_SAVE_SEQUENCE) {
          engine.ResetSequencerSettings();
        } else if (subpage_ == LOAD_SAVE_SYSTEM_SETTINGS) {
          engine.ResetSystemSettings();
        }
        break;

      case GROUP_FILTER:
        display.set_status('?');
        if (subpage_ == LOAD_SAVE_PATCH) {
          RandomizePatch();
        } else if (subpage_ == LOAD_SAVE_SEQUENCE) {
          RandomizeSequence();
        }
        break;

      case GROUP_MOD:
        display.set_status('>');
        if (subpage_ == LOAD_SAVE_PATCH) {
          Storage::SysExDump(engine.mutable_patch());
        } else if (subpage_ == LOAD_SAVE_SEQUENCE) {
          Storage::SysExDump(engine.mutable_sequencer_settings());
        }
        break;

      case GROUP_SEQUENCER:
        // TODO(pichenettes): BIG DUMP
        break;
    }
  } else if (event.hold_time >= 3) {
    switch (event.id) {
      case GROUP_SEQUENCER:
        engine.NoteOn(0, 48, test_note_playing_ ? 0 : 100);
        test_note_playing_ ^= 1;
        break;

      case GROUP_OSC:
        ToggleGroup(GROUP_PERFORMANCE);
        break;

      case GROUP_FILTER:
        if (current_page_ <= PAGE_MOD_MATRIX) {
          parameter_to_assign_.id = page_definition_[
              current_page_].first_parameter_index + cursor_;
          parameter_to_assign_.subpage = subpage_;
          DisplaySplashScreen(STR_RES_TOUCH_A_KNOB_TO);
          assign_in_progress_ = 1;
          return;  // To avoid refresh
        }
        break;
    }
  } else {
    ToggleGroup(event.id);
  }
  Refresh();
}

/* static */
void Editor::HandleInput(uint8_t knob_index, uint16_t value) {
  (*ui_handler_[page_definition_[current_page_].ui_type].input_handler)(
      knob_index, value);
  Refresh();
}

/* static */
void Editor::HandleIncrement(int8_t direction) {
  (*ui_handler_[page_definition_[current_page_].ui_type].increment_handler)(
      direction);
  Refresh();
}

/* static */
void Editor::HandleClick() {
  if (mode_ == EDITOR_MODE_OVERVIEW) {
    mode_ = EDITOR_MODE_EDIT;
    display.set_cursor_character(' ');
  } else {
    mode_ = EDITOR_MODE_OVERVIEW;
    display.set_cursor_character(kLcdNoCursor);
  }
  Refresh();
}

/* static */
void Editor::Refresh() {
  if (mode_ == EDITOR_MODE_OVERVIEW) {
    (*ui_handler_[page_definition_[current_page_].ui_type].overview_page)();
  } else {
    (*ui_handler_[page_definition_[current_page_].ui_type].edit_page)();
  }
}

/* static */
void Editor::EnterLoadSaveMode() {
  // We've just confirmed a save.
  if (current_page_ == PAGE_LOAD_SAVE) {
    if (action_ == ACTION_SAVE) {
      display.set_status('w');
      switch (subpage_) {
        case LOAD_SAVE_PATCH:
          Storage::Write(engine.mutable_patch(), current_patch_number_);
          break;
      
        case LOAD_SAVE_SEQUENCE:
          Storage::Write(engine.mutable_sequencer_settings(),
                         current_sequence_number_);
          break;
        
        case LOAD_SAVE_SYSTEM_SETTINGS:
          engine.mutable_system_settings()->EepromSave();
          break;
      }
    }
  } else {
    // From which page are we coming from? Depending on the answer, show the
    // patch library, sequence library, or system settings write pages.
    if (current_page_ <= PAGE_MOD_MATRIX) {
      subpage_ = LOAD_SAVE_PATCH;
      previous_patch_number_ = current_patch_number_;
      Storage::Backup(engine.mutable_patch());
    } else if (current_page_ >= PAGE_SYS_KBD) {
      subpage_ = LOAD_SAVE_SYSTEM_SETTINGS;
    } else {
      subpage_ = LOAD_SAVE_SEQUENCE;
      previous_sequence_number_ = current_sequence_number_;
      Storage::Backup(engine.mutable_sequencer_settings());      
    }
  }
  current_page_ = PAGE_LOAD_SAVE;
  action_ = ACTION_EXIT;
}

/* static */
void Editor::LoadPatch(uint8_t index) {
  if (index != current_patch_number_ && action_ == ACTION_LOAD) {
    Storage::Load(engine.mutable_patch(), index);
    engine.TouchPatch();
  }
  if (action_ != ACTION_EXIT) {
    current_patch_number_ = index;
  }
}

/* static */
void Editor::LoadSequence(uint8_t index) {
  if (index != current_sequence_number_ && action_ == ACTION_LOAD) {
    Storage::Load(engine.mutable_sequencer_settings(), index);
    engine.TouchSequence();
  }
  if (action_ != ACTION_EXIT) {
    current_sequence_number_ = index;
  }
}

/* static */
void Editor::HandleLoadSaveInput(uint8_t knob_index, uint16_t value) {
  switch (knob_index) {
    case 0:
      if (subpage_ == LOAD_SAVE_PATCH) {
        LoadPatch(value * Storage::size<Patch>() / 1024);
      } else if (subpage_ == LOAD_SAVE_SEQUENCE) {
        LoadSequence(value * Storage::size<SequencerSettings>() / 1024);
      }
      break;
    case 1:
      if (action_ == ACTION_SAVE && subpage_ == LOAD_SAVE_PATCH) {
        cursor_ = value * kPatchNameSize / 1024;
      }
      break;
    case 2:
      if (action_ == ACTION_SAVE && subpage_ == LOAD_SAVE_PATCH) {
        value += (value << 1);
        engine.mutable_patch()->name[cursor_] = 32 + (value >> 5);
      }
      break;
    case 3:
      if (value < 64 && subpage_ != LOAD_SAVE_SYSTEM_SETTINGS) {
        action_ = ACTION_LOAD;
      } else {
        if (action_ == ACTION_LOAD) {
          if (subpage_ == LOAD_SAVE_PATCH) {
            current_patch_number_ = previous_patch_number_;
            Storage::Restore(engine.mutable_patch());
            engine.TouchPatch();
          } else if (subpage_ == LOAD_SAVE_SEQUENCE) {
            current_sequence_number_ = previous_sequence_number_;
            Storage::Restore(engine.mutable_sequencer_settings());
            engine.TouchSequence();
          }
        }
        action_ = value >= 960 ? ACTION_SAVE : ACTION_EXIT;
      }
      break;
  }
}

/* static */
void Editor::HandleLoadSaveIncrement(int8_t direction) {
  if (action_ == ACTION_SAVE && subpage_ == LOAD_SAVE_PATCH) {
    if (mode_ == EDITOR_MODE_OVERVIEW) {
      int8_t new_cursor = static_cast<int8_t>(cursor_) + direction;
      if (new_cursor >= 0 & new_cursor < kPatchNameSize) {
        cursor_ = static_cast<uint8_t>(new_cursor);
      }
    } else {
      uint8_t value = engine.patch().name[cursor_];
      value += direction;
      if (value >= 32 && value <= 128) {
        engine.mutable_patch()->name[cursor_] = value;
      }
    }
  } else {
    if (subpage_ == LOAD_SAVE_PATCH) {
      int8_t patch_number = static_cast<int8_t>(current_patch_number_) + direction;
      if (patch_number >= 0 &&
          patch_number < Storage::size<Patch>()) {
        LoadPatch(patch_number);
      }
    } else if (subpage_ == LOAD_SAVE_SEQUENCE) {
      int8_t sequence_number = static_cast<int8_t>(current_sequence_number_) + direction;
      if (sequence_number >= 0 &&
          sequence_number < Storage::size<SequencerSettings>()) {
        LoadSequence(sequence_number);
      }
    }
  }
}

/* static */
void Editor::DisplayLoadSavePage() {
  // 0123456789abcdef
  // load/save patch
  // 32 barbpapa save
  if (cursor_ >= 7) {
    cursor_ = 7;
  }
  ResourcesManager::LoadStringResource(
      STR_RES_PATCHES + subpage_,
      line_buffer_,
      kLcdWidth);
  AlignLeft(line_buffer_, kLcdWidth);
  display.Print(0, line_buffer_);

  if (subpage_ == LOAD_SAVE_PATCH) {
    UnsafeItoa<int16_t>(current_patch_number_ + 1, 2, line_buffer_);
    AlignRight(line_buffer_, 2);
    memcpy(line_buffer_ + 3, engine.patch().name, kPatchNameSize);
    if (action_ == ACTION_SAVE) {
      display.set_cursor_position(kLcdWidth + 3 + cursor_);
    } else {
      display.set_cursor_position(kLcdNoCursor);
    }
  } else if (subpage_ == LOAD_SAVE_SEQUENCE) {
    UnsafeItoa<int16_t>(current_sequence_number_ + 1, 2, line_buffer_);
    AlignRight(line_buffer_, 2);
    for (uint8_t i = 0; i < 8; ++i) {
      line_buffer_[i + 3] = engine.sequencer_settings().steps[i].character();
    }
  } else {
    memset(line_buffer_, ' ', 12);
  }
  line_buffer_[2] = ' ';
  line_buffer_[11] = ' ';
  ResourcesManager::LoadStringResource(
      action_ + STR_RES_LOAD,
      line_buffer_ + 12,
      kColumnWidth);
  display.Print(1, line_buffer_);
}

/* static */
void Editor::MoveSequencerCursor(int8_t direction) {
  int8_t new_cursor = cursor_;
  new_cursor += direction;
  if (new_cursor < 0) {
    cursor_ = 0xff;
    current_page_ = page_definition_[current_page_].overall_previous;
    display.set_cursor_position(kLcdNoCursor);
  } else if (new_cursor >= engine.GetParameter(PRM_SEQ_PATTERN_SIZE)) {
    cursor_ = 0;
    current_page_ = page_definition_[current_page_].overall_next;
    display.set_cursor_position(kLcdNoCursor);
  } else {
    cursor_ = new_cursor;
  }
}

/* static */
void Editor::DisplayStepSequencerPage() {
  // 0123456789abcdef
  // step sequencer
  // 0000ffff44449999
  if (cursor_ > engine.sequencer_settings().pattern_size - 1) {
    cursor_ = engine.sequencer_settings().pattern_size - 1;
  }
  ResourcesManager::LoadStringResource(
      STR_RES_STEP_SEQUENCER,
      line_buffer_,
      kLcdWidth);
  AlignLeft(line_buffer_, kLcdWidth);
  display.Print(0, line_buffer_);
  memset(line_buffer_, ' ', kLcdWidth);
  for (uint8_t i = 0; i < engine.sequencer_settings().pattern_size; ++i) {
    line_buffer_[i] = NibbleToAscii(
        engine.sequencer_settings().steps[i].controller());
  }
  if (engine.sequencer_settings().pattern_size != kLcdWidth) {
    line_buffer_[engine.sequencer_settings().pattern_size] = '|';
  }
  display.Print(1, line_buffer_);
  display.set_cursor_position(kLcdWidth + cursor_);
}

/* static */
void Editor::HandleSequencerNavigation(
    uint8_t knob_index,
    uint16_t value) {
  switch (knob_index) {
    case 1:
      {
        cursor_ = value >> 6;
        uint8_t max_position = engine.GetParameter(PRM_SEQ_PATTERN_SIZE) - 1;
        if (cursor_ > max_position) {
          cursor_ = max_position;
        }
      }
      break;
    case 3:
      {
        uint8_t new_size = (value >> 6) + 1;
        if (cursor_ >= new_size) {
          cursor_ = new_size - 1;
        }
        engine.SetParameter(PRM_SEQ_PATTERN_SIZE, new_size);
      }
      break;
  }
}

/* static */
void Editor::HandleStepSequencerInput(
    uint8_t knob_index,
    uint16_t value) {
  HandleSequencerNavigation(knob_index, value);
  if (knob_index == 2) {
    HandleTrackerInput(3, value);
  }
}

/* static */
void Editor::HandleStepSequencerIncrement(int8_t direction) {
  if (mode_ == EDITOR_MODE_OVERVIEW) {
    MoveSequencerCursor(direction);
  } else {
    engine.mutable_sequencer_settings()->steps[cursor_].set_controller(
        engine.mutable_sequencer_settings()->steps[cursor_].controller() + \
        direction
    );
  }
}

/* static */
void Editor::DisplayTrackerPage() {
  memset(line_buffer_, ' ', kLcdWidth);
  if (cursor_ > engine.sequencer_settings().pattern_size - 1) {
    cursor_ = engine.sequencer_settings().pattern_size - 1;
  }
  if (cursor_ > 0) {
    engine.sequencer_settings().PrintStep(cursor_ - 1, line_buffer_);
  }
  display.Print(0, line_buffer_);
  engine.sequencer_settings().PrintStep(cursor_, line_buffer_);
  line_buffer_[0] = 0x7e;
  display.Print(1, line_buffer_);
  if (mode_ == EDITOR_MODE_EDIT) {
    display.set_cursor_position(kLcdWidth + 7);
  } else {
    display.set_cursor_position(0xff);
  }
}

/* static */
void Editor::HandleTrackerInput(
    uint8_t knob_index,
    uint16_t value) {
  switch (knob_index) {
    case 0:
      {
        cursor_ = value >> 6;
        uint8_t max_position = engine.GetParameter(PRM_SEQ_PATTERN_SIZE) - 1;
        if (cursor_ > max_position) {
          cursor_ = max_position;
        }
      }
      break;
    case 1:
      engine.mutable_sequencer_settings()->steps[cursor_].set_note(
          24 + (value >> 4));
      break;
    case 2:
      value *= 10;
      value >>= 5;
      if (value < 64) {
        engine.mutable_sequencer_settings()->steps[cursor_].set_velocity(0);
        engine.mutable_sequencer_settings()->steps[cursor_].set_gate(0);
        engine.mutable_sequencer_settings()->steps[cursor_].set_legato(0);
      } else {
        value -= 64;
        engine.mutable_sequencer_settings()->steps[cursor_].set_velocity(value);
        engine.mutable_sequencer_settings()->steps[cursor_].set_gate(1);
        engine.mutable_sequencer_settings()->steps[cursor_].set_legato(
            value >= 0x80);
      }
      break;
    case 3:
      engine.mutable_sequencer_settings()->steps[cursor_].set_controller(
          value >> 6);
      break;
  }
}

/* static */
void Editor::HandleTrackerIncrement(int8_t direction) {
  if (mode_ == EDITOR_MODE_OVERVIEW) {
    MoveSequencerCursor(direction);
  } else {
    int8_t note = engine.mutable_sequencer_settings()->steps[cursor_].note();
    note += direction;
    if (note >= 12 && note < 108) {
      engine.mutable_sequencer_settings()->steps[cursor_].set_note(note);
    }
  }
}

/* static */
void Editor::DisplayPageRPage() {
  if (cursor_ > engine.sequencer_settings().pattern_size - 1) {
    cursor_ = engine.sequencer_settings().pattern_size - 1;
  }
  memset(line_buffer_, ' ', kLcdWidth);
  memset(line_buffer_, ' ', kLcdWidth);
  for (uint8_t i = 0; i < engine.sequencer_settings().pattern_size; ++i) {
    line_buffer_[i] = engine.mutable_sequencer_settings()->steps[i].character();
  }
  if (engine.sequencer_settings().pattern_size != kLcdWidth) {
    line_buffer_[engine.sequencer_settings().pattern_size] = '|';
  }
  display.Print(0, line_buffer_);

  for (uint8_t i = 0; i < engine.sequencer_settings().pattern_size; ++i) {
    if (engine.mutable_sequencer_settings()->steps[i].gate()) {
      line_buffer_[i] = NibbleToAscii(
          engine.mutable_sequencer_settings()->steps[i].velocity() >> 4);
    }
  }
  if (engine.sequencer_settings().pattern_size != kLcdWidth) {
    line_buffer_[engine.sequencer_settings().pattern_size] = '|';
  }
  display.Print(1, line_buffer_);
  display.set_cursor_position(kLcdWidth + cursor_);
}

/* static */
void Editor::HandlePageRInput(
    uint8_t knob_index,
    uint16_t value) {
  HandleSequencerNavigation(knob_index, value);
  if (knob_index == 2) {
    HandleTrackerInput(2, value);
  }
}

/* static */
void Editor::HandlePageRIncrement(int8_t direction) {
  if (mode_ == EDITOR_MODE_OVERVIEW) {
    MoveSequencerCursor(direction);
  } else {
    int8_t flags = engine.mutable_sequencer_settings()->steps[cursor_].flags();
    flags += direction;
    if (flags >= 0 && flags <= 16) {
      engine.mutable_sequencer_settings()->steps[cursor_].set_flags(flags);
    }
  }
}

/* static */
void Editor::DisplayEditOverviewPage() {
  // 0123456789abcdef
  // foo bar baz bad
  //  63 127   0   0
  if (cursor_ >= 3) {
    cursor_ = 3;
  }
  for (uint8_t i = 0; i < kNumEditingPots; ++i) {
    uint8_t index = KnobIndexToParameterId(i);
    const ParameterDefinition& parameter = parameter_definition(index);
    ResourcesManager::LoadStringResource(
        parameter.short_name,
        line_buffer_ + i * kColumnWidth,
        kColumnWidth - 1);
    line_buffer_[i * kColumnWidth + kColumnWidth - 1] = '\0';
    AlignRight(line_buffer_ + i * kColumnWidth, kColumnWidth);
    PrettyPrintParameterValue(
        parameter,
        line_buffer_ + i * kColumnWidth + kLcdWidth + 1,
        kColumnWidth - 1);
    line_buffer_[i * kColumnWidth + kColumnWidth + kLcdWidth] = '\0';
    AlignRight(line_buffer_ + i * kColumnWidth + kLcdWidth + 1, kColumnWidth);
  }

  // Change the case of the current parameter accessible by the rotary encoder.
  uint8_t pos = cursor_ * kColumnWidth + 1;
  if (line_buffer_[pos] > 96 && line_buffer_[pos] <= 122) {
    line_buffer_[pos] -= 32;
  }

  display.Print(0, line_buffer_);
  display.Print(1, line_buffer_ + kLcdWidth + 1);
}

/* static */
void Editor::DisplayEditDetailsPage() {
  // 0123456789abcdef
  // filter
  // cutoff       127
  //
  // OR
  //
  // mod src>dst
  // amount        63
  if (current_page_ == PAGE_MOD_MATRIX) {
    const ParameterDefinition& current_source = parameter_definition(
        page_definition_[PAGE_MOD_MATRIX].first_parameter_index + 1);
    PrettyPrintParameterValue(
        current_source,
        line_buffer_ + 4,
        kColumnWidth - 1);
    const ParameterDefinition& current_destination = parameter_definition(
        page_definition_[PAGE_MOD_MATRIX].first_parameter_index + 2);
    PrettyPrintParameterValue(
        current_destination,
        line_buffer_ + kColumnWidth + 4,
        kColumnWidth);
    line_buffer_[0] = 'm';
    line_buffer_[1] = 'o';
    line_buffer_[2] = 'd';
    line_buffer_[3] = ' ';
    line_buffer_[kColumnWidth + 3] = '>';
    AlignLeft(line_buffer_ + kColumnWidth + 4, kLcdWidth - kColumnWidth - 4);
    display.Print(0, line_buffer_);
  }
  uint8_t index = KnobIndexToParameterId(cursor_);
  const ParameterDefinition& parameter = parameter_definition(index);
  const PageDefinition& page = page_definition_[current_page_];

  if (current_page_ != PAGE_MOD_MATRIX) {
    ResourcesManager::LoadStringResource(
        page.name,
        line_buffer_,
        kLcdWidth);
    AlignLeft(line_buffer_, kLcdWidth);
    display.Print(0, line_buffer_);
  }

  ResourcesManager::LoadStringResource(
      parameter.long_name,
      line_buffer_,
      kCaptionWidth);
  AlignLeft(line_buffer_, kCaptionWidth);

  PrettyPrintParameterValue(
      parameter,
      line_buffer_ + kCaptionWidth,
      kValueWidth);
  AlignRight(line_buffer_ + kCaptionWidth, kValueWidth);
  display.Print(1, line_buffer_);
}

/* static */
uint8_t Editor::KnobIndexToParameterId(uint8_t knob_index) {
  if (current_page_ == PAGE_PERFORMANCE) {
    subpage_ = assigned_parameters_[knob_index].subpage;
    return assigned_parameters_[knob_index].id;
  } else {
    return page_definition_[current_page_].first_parameter_index + \
        knob_index;
  }
}

/* static */
void Editor::HandleEditInput(uint8_t knob_index, uint16_t value) {
  if (assign_in_progress_) {
    assigned_parameters_[knob_index] = parameter_to_assign_;
    assign_in_progress_ = 0;
    ToggleGroup(GROUP_PERFORMANCE);
  } else {
    mode_ = EDITOR_MODE_EDIT;
    uint8_t new_value;
    uint8_t index = KnobIndexToParameterId(knob_index);
    const ParameterDefinition& parameter = parameter_definition(index);

    if (parameter.unit == UNIT_RAW_UINT8) {
      new_value = (value >> 3);
    } else {
      uint8_t range = parameter.max_value - parameter.min_value + 1;
      new_value = ((value >> 3) * range) >> 7;
      new_value += parameter.min_value;
    }
    SetParameterValue(parameter.id, new_value);
    cursor_ = knob_index;
  }
}

/* static */
void Editor::HandleEditIncrement(int8_t direction) {
  if (mode_ == EDITOR_MODE_OVERVIEW) {
    int8_t new_cursor = static_cast<int8_t>(cursor_) + direction;
    if (current_page_ == PAGE_MOD_MATRIX) {
      last_visited_subpage_ = subpage_;
    }
    if (new_cursor < 0) {
      subpage_ = 0;
      cursor_ = 0xff;
      current_page_ = page_definition_[current_page_].overall_previous;
    } else if (new_cursor >= 4) {
      subpage_ = 0;
      cursor_ = 0;
      current_page_ = page_definition_[current_page_].overall_next;
    } else {
      cursor_ = new_cursor;
    }
    if (current_page_ == PAGE_MOD_MATRIX) {
      subpage_ = last_visited_subpage_;
      last_visited_subpage_ = subpage_;
    }
    last_visited_page_[page_definition_[current_page_].group] = current_page_;
  } else {
    uint8_t index = KnobIndexToParameterId(cursor_);
    const ParameterDefinition& parameter = parameter_definition(index);

    int16_t value = GetParameterValue(parameter.id);
    if (parameter.unit == UNIT_INT8) {
      value = static_cast<int16_t>(static_cast<int8_t>(value));
      value += direction;
      if (value >= static_cast<int8_t>(parameter.min_value) &&
          value <= static_cast<int8_t>(parameter.max_value)) {
        SetParameterValue(parameter.id, value);
      }
    } else {
      value += direction;
      if (value >= parameter.min_value && value <= parameter.max_value) {
        SetParameterValue(parameter.id, value);
      }
    }
  }
}

/* static */
void Editor::SetParameterValue(uint8_t id, uint8_t value) {
  // Set the tempo to 0 for external clock.
  if (id == PRM_SEQ_TEMPO) {
    if (value < 40) {
      value = 0;
    }
  }

  // Dirty hack for the modulation page.
  if (current_page_ == PAGE_MOD_MATRIX && id == PRM_MOD_ROW) {
    subpage_ = value;
    last_visited_subpage_ = value;
  } else {
    engine.SetParameter(id + subpage_ * 3, value);
  }
}

/* static */
uint8_t Editor::GetParameterValue(uint8_t id) {
  uint8_t value;
  if (current_page_ == PAGE_MOD_MATRIX && id == PRM_MOD_ROW) {
    value = subpage_;
  } else {
    value = engine.GetParameter(id + subpage_ * 3);
  }
  if (id == PRM_SEQ_TEMPO && value == 0) {
    value = 39;
  }
  return value;
}

/* static */
void Editor::DisplaySplashScreen(ResourceId first_line) {
  // 0123456789abcdef
  // mutable 
  // instruments sh-1
  for (uint8_t i = 0; i < 2; ++i) {
    ResourcesManager::LoadStringResource(
        first_line + i,
        line_buffer_,
        kLcdWidth);
    AlignLeft(line_buffer_, kLcdWidth);
    display.Print(i, line_buffer_);
  }
}

/* static */
void Editor::PrettyPrintParameterValue(const ParameterDefinition& parameter,
                                       char* buffer, uint8_t width) {
  int16_t value = GetParameterValue(parameter.id);
  ResourceId text = ResourcesManager::Lookup<uint8_t, uint8_t>(
      units_definitions,
      parameter.unit);
  char prefix = '\0';
  switch (parameter.unit) {
    case UNIT_INT8:
      value = int16_t(int8_t(value));
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
        text = STR_RES_CUT;
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
    case UNIT_TEMPO_WITH_EXTERNAL_CLOCK:
      if (value == 39) {
        value = 0;
        text = STR_RES_EXTERN;
      } else if (value > 240) {
        text = STR_RES_270 + value - 240 - 1;
        value = 0;
      }
      break;
    case UNIT_ARPEGGIO_PATTERN:
      if (value == kNumArpeggiatorPatterns) {
        value = 0;
        text = STR_RES_SEQUENCER;
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
    UnsafeItoa<int16_t>(value, width, buffer);
  }
}

/* static */
const ParameterDefinition& Editor::parameter_definition(uint8_t index) {
  if (index != parameter_definition_index_) {
    parameter_definition_index_ = index;
    ResourcesManager::Load(
        raw_parameter_definition,
        index,
        &parameter_definition_);
  }
  return parameter_definition_;
}

}  // namespace hardware_shruthi
