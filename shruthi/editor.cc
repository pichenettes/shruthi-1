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

#include "shruthi/editor.h"

#include "avrlib/deprecated/devices/switch_array.h"
#include "shruthi/display.h"
#include "shruthi/midi_dispatcher.h"
#include "shruthi/parameter_definitions.h"
#include "shruthi/storage.h"
#include "shruthi/synthesis_engine.h"
#include "avrlib/string.h"

using namespace avrlib;
using namespace avrlib;

using avrlib::kLcdNoCursor;

namespace shruthi {

/* extern */
Editor editor;

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
  STR_RES_CUTOFF,  // UNIT_MODULATION_DESTINATION
  STR_RES_3,       // UNIT_ARPEGGIO_DIRECTION
  STR_RES_EQUAL,   // UNIT_RAGA
  0,               // UNIT_TEMPO_WITH_EXTERNAL_CLOCK
  STR_RES__OFF,    // UNIT_MIDI_MODE
  STR_RES_STP,     // UNIT_SEQUENCER_MODE
  STR_RES_T,       // UNIT_SEQUENCER_WARP
  STR_RES_SWING,   // UNIT_GROOVE_TEMPLATE
  0,               // UNIT_ARPEGGIO_PATTERN
  STR_RES_FREE,    // UNIT_LFO_RETRIGGER_MODE
  0,               // UNIT_SPLIT_POINT
  STR_RES__LPF,    // UNIT_FILTER_BOARD
  STR_RES_4CV_IN,  // UNIT_CV_MODE
  STR_RES_LPF,     // UNIT_FILTER_1_MODE
  STR_RES_SLP,     // UNIT_FILTER_2_MODE
  STR_RES___OFF,   // UNIT_CV_OPERATOR
  STR_RES_DISTRT,  // UNIT_FX_PROGRAM
  STR_RES_LGF,     // UNIT_FILTER_FX_MODE
  STR_RES_LP4,     // UNIT_FILTER_4P_MODE
  STR_RES_LIQUID,   // UNIT_FILTER_4P_FLAVOUR
};  // UNIT_LAST

static const prog_char arp_pattern_prefix[4] PROGMEM = {
  0x03, 0x04, 0x05, '?'  // Up, Down, UpDown, Random
};

/* static */
const UiHandler Editor::ui_handler_[] = {
  { &Editor::DisplayEditOverviewPage, &Editor::DisplayEditDetailsPage,
    &Editor::HandleEditInput, &Editor::HandleEditIncrement, NULL },
  { &Editor::DisplayTrackerPage, &Editor::DisplayTrackerPage,
    &Editor::HandleTrackerInput, &Editor::HandleTrackerIncrement, NULL },
  { &Editor::DisplayPageRPage, &Editor::DisplayPageRPage,
    &Editor::HandlePageRInput, &Editor::HandlePageRIncrement, NULL },
  { &Editor::DisplayStepSequencerPage, &Editor::DisplayStepSequencerPage,
    &Editor::HandleStepSequencerInput, &Editor::HandleStepSequencerIncrement,
    NULL },
  { &Editor::DisplayLoadSavePage, &Editor::DisplayLoadSavePage,
    &Editor::HandleEditInput, &Editor::HandleLoadSaveIncrement,
    &Editor::HandleLoadSaveClick },
  { &Editor::DisplayConfirmPage, &Editor::DisplayConfirmPage,
    &Editor::HandleConfirmInput, &Editor::HandleConfirmIncrement,
    &Editor::HandleConfirmClick },
};

PageDefinition Editor::page_definition_[] = {
  /* PAGE_OSC_OSC_1 */ { PAGE_OSC_OSC_2, GROUP_OSC,
    PAGE_MOD_MATRIX, PAGE_OSC_OSC_2,
    STR_RES_OSCILLATOR_1, PARAMETER_EDITOR, 0, LED_1_MASK },

  /* PAGE_OSC_OSC_2 */ { PAGE_OSC_OSC_MIX, GROUP_OSC,
    PAGE_OSC_OSC_1, PAGE_OSC_OSC_MIX,
    STR_RES_OSCILLATOR_2, PARAMETER_EDITOR, 4, LED_2_MASK },

  /* PAGE_OSC_OSC_MIX */ { PAGE_OSC_OSC_1, GROUP_OSC,
    PAGE_OSC_OSC_2, PAGE_FILTER_FILTER,
    STR_RES_MIXER, PARAMETER_EDITOR, 8, LED_1_MASK | LED_2_MASK },

  /* PAGE_FILTER_FILTER */ { PAGE_FILTER_MULTIMODE, GROUP_FILTER,
    PAGE_OSC_OSC_MIX, PAGE_FILTER_MULTIMODE,
    STR_RES_FILTER, PARAMETER_EDITOR, 12, LED_3_MASK },

  /* PAGE_FILTER_MULTIMODE */ { PAGE_FILTER_FILTER, GROUP_FILTER,
    PAGE_FILTER_FILTER, PAGE_MOD_ENV_1,
    STR_RES_FILTERS, PARAMETER_EDITOR, 66, LED_3_MASK },

  /* PAGE_MOD_ENV_1 */ { PAGE_MOD_ENV_2, GROUP_MOD_SOURCES,
    PAGE_FILTER_MULTIMODE, PAGE_MOD_ENV_2,
    STR_RES_ENVELOPE_1, PARAMETER_EDITOR, 16, LED_4_MASK },

  /* PAGE_MOD_ENV_2 */ { PAGE_MOD_LFO_1, GROUP_MOD_SOURCES,
    PAGE_MOD_ENV_1, PAGE_MOD_LFO_1,
    STR_RES_ENVELOPE_2, PARAMETER_EDITOR, 20, LED_5_MASK },

  /* PAGE_MOD_LFO_1 */ { PAGE_MOD_LFO_2, GROUP_MOD_SOURCES,
    PAGE_MOD_ENV_2, PAGE_MOD_LFO_2,
    STR_RES_LFO_1, PARAMETER_EDITOR, 24, LED_4_MASK },

  /* PAGE_MOD_LFO_2 */ { PAGE_MOD_ENV_1, GROUP_MOD_SOURCES,
    PAGE_MOD_LFO_1, PAGE_MOD_MATRIX,
    STR_RES_LFO_2, PARAMETER_EDITOR, 28, LED_5_MASK },

  /* PAGE_MOD_MATRIX */ { PAGE_MOD_OPERATORS, GROUP_MOD_MATRIX,
    PAGE_MOD_LFO_2, PAGE_MOD_OPERATORS,
    STR_RES_MOD_, PARAMETER_EDITOR, 32, 0 },

  /* PAGE_MOD_OPERATORS */ { PAGE_MOD_MATRIX, GROUP_MOD_MATRIX,
    PAGE_MOD_MATRIX, PAGE_OSC_OSC_1,
    STR_RES_OPERATORS, PARAMETER_EDITOR, 58, 0 },
    
  /* PAGE_SEQ_SEQUENCER */ { PAGE_SEQ_ARPEGGIATOR, GROUP_SEQUENCER_ARPEGGIATOR,
    PAGE_SEQ_CONTROLLER, PAGE_SEQ_ARPEGGIATOR,
    STR_RES_SEQUENCER, PARAMETER_EDITOR, 36, LED_1_MASK },

  /* PAGE_SEQ_ARPEGGIATOR */ { PAGE_SEQ_SEQUENCER, GROUP_SEQUENCER_ARPEGGIATOR,
    PAGE_SEQ_SEQUENCER, PAGE_SEQ_TRACKER,
    STR_RES_ARPEGGIO, PARAMETER_EDITOR, 40, LED_2_MASK },

  /* PAGE_SEQ_TRACKER */ { PAGE_SEQ_TRACKER, GROUP_SEQUENCER_TRACKER,
    PAGE_SEQ_ARPEGGIATOR, PAGE_SEQ_RHYTHM,
    STR_RES_STEP_SEQUENCER, TRACKER_EDITOR, 0, LED_3_MASK },

  /* PAGE_SEQ_RHYTHM */ { PAGE_SEQ_CONTROLLER, GROUP_SEQUENCER_STEPS,
    PAGE_SEQ_TRACKER, PAGE_SEQ_CONTROLLER,
    STR_RES_STEP_SEQUENCER, PAGE_R_EDITOR, 0, LED_4_MASK },

  /* PAGE_SEQ_CONTROLLER */ { PAGE_SEQ_RHYTHM, GROUP_SEQUENCER_STEPS,
    PAGE_SEQ_RHYTHM, PAGE_SEQ_SEQUENCER,
    STR_RES_STEP_SEQUENCER, STEP_SEQUENCER, 52, LED_5_MASK },

  /* PAGE_SYS_KBD */ { PAGE_SYS_MIDI, GROUP_SYS,
    PAGE_SYS_TRIGGERS, PAGE_SYS_MIDI,
    STR_RES_KEYBOARD, PARAMETER_EDITOR, 44, LED_6_MASK },

  /* PAGE_SYS_MIDI */ { PAGE_SYS_DISPLAY, GROUP_SYS,
    PAGE_SYS_KBD, PAGE_SYS_DISPLAY,
    STR_RES_MIDI, PARAMETER_EDITOR, 48, LED_6_MASK },

  /* PAGE_SYS_DISPLAY */ { PAGE_SYS_TRIGGERS, GROUP_SYS,
    PAGE_SYS_MIDI, PAGE_SYS_TRIGGERS,
    STR_RES_SYSTEM, PARAMETER_EDITOR, 52, LED_6_MASK },

  /* PAGE_SYS_TRIGGERS */ { PAGE_SYS_KBD, GROUP_SYS,
    PAGE_SYS_DISPLAY, PAGE_SYS_KBD,
    STR_RES_TRIGGERS, PARAMETER_EDITOR, 62, LED_6_MASK },
    
  /* PAGE_LOAD_SAVE */ { PAGE_LOAD_SAVE, GROUP_LOAD_SAVE,
    PAGE_LOAD_SAVE, PAGE_LOAD_SAVE,
    STR_RES_PATCH, LOAD_SAVE, 0, LED_WRITE_MASK },

  /* PAGE_PERFORMANCE */ { PAGE_PERFORMANCE, GROUP_PERFORMANCE,
    PAGE_PERFORMANCE, PAGE_PERFORMANCE,
    STR_RES_PERFORMANCE, PARAMETER_EDITOR, 0, 0 },
    
  /* PAGE_CONFIRM */ { PAGE_CONFIRM, GROUP_CONFIRM,
    PAGE_CONFIRM, PAGE_CONFIRM,
    STR_RES_PATCH, CONFIRM, 0, 0x55 },
};

/* <static> */
ParameterPage Editor::current_page_ = PAGE_FILTER_FILTER;
ParameterPage Editor::last_visited_page_[kNumGroups] = {
    PAGE_OSC_OSC_1,
    PAGE_FILTER_FILTER,
    PAGE_MOD_ENV_1,
    PAGE_MOD_MATRIX,

    PAGE_SEQ_SEQUENCER,
    PAGE_SEQ_TRACKER,
    PAGE_SEQ_RHYTHM,
    PAGE_SYS_KBD,

    PAGE_LOAD_SAVE,
    PAGE_PERFORMANCE
};
uint8_t Editor::last_visited_subpage_ = 0;
uint8_t Editor::display_mode_ = DISPLAY_MODE_OVERVIEW;
uint8_t Editor::editor_mode_ = EDITOR_MODE_PATCH;
uint8_t Editor::last_visited_group_[3] = {
    GROUP_FILTER,
    GROUP_SEQUENCER_ARPEGGIATOR,
    GROUP_PERFORMANCE
};

char Editor::line_buffer_[kLcdWidth * kLcdHeight + 1];

uint8_t Editor::cursor_;
uint8_t Editor::last_knob_;
uint8_t Editor::subpage_;
uint8_t Editor::action_;
uint8_t Editor::load_save_target_;
uint8_t Editor::last_external_input_;
uint16_t Editor::current_patch_number_ = 0;
uint16_t Editor::current_sequence_number_ = 0;

uint8_t Editor::test_note_playing_ = 0;
uint8_t Editor::assign_in_progress_ = 0;
ParameterAssignment Editor::parameter_to_assign_;
ConfirmPageSettings Editor::confirm_page_settings_;
uint8_t Editor::locked_value_[kNumEditingPots];
uint8_t Editor::locked_[kNumEditingPots];
bool Editor::empty_patch_;
/* </static> */

/* static */
void Editor::Init() {
  ParameterDefinitions::Init();
  
  line_buffer_[kLcdWidth] = '\0';
  ConfigureFilterMenu();
}

void Editor::ConfigureFilterMenu() {
  uint8_t n = engine.system_settings().expansion_filter_board;
  if (n == 0) {
    page_definition_[PAGE_FILTER_FILTER].next = PAGE_FILTER_FILTER;
    page_definition_[PAGE_FILTER_FILTER].overall_next = PAGE_MOD_ENV_1;
    page_definition_[PAGE_MOD_ENV_1].overall_previous = PAGE_FILTER_FILTER;
  } else {
    page_definition_[PAGE_FILTER_FILTER].next = PAGE_FILTER_MULTIMODE;
    page_definition_[PAGE_FILTER_FILTER].overall_next = PAGE_FILTER_MULTIMODE;
    page_definition_[PAGE_MOD_ENV_1].overall_previous = PAGE_FILTER_MULTIMODE;
    page_definition_[PAGE_FILTER_MULTIMODE].first_parameter_index = 66;
    page_definition_[PAGE_FILTER_MULTIMODE].name = (n == FILTER_BOARD_DSP) ? \
        STR_RES_DSP : STR_RES_FILTERS;
    while (--n) {
      page_definition_[PAGE_FILTER_MULTIMODE].first_parameter_index += 4;
    }
  }
}

/* static */
void Editor::PageChange() {
  if (current_page_ == PAGE_MOD_MATRIX) {
    subpage_ = last_visited_subpage_;
  }
  last_visited_page_[page_definition_[current_page_].group] = current_page_;
  last_visited_group_[editor_mode_] = page_definition_[current_page_].group;
  
  if (page_definition_[current_page_].ui_type == PARAMETER_EDITOR) {
    if (engine.system_settings().display_snap) {
      for (uint8_t i = 0; i < kNumEditingPots; ++i) {
        locked_[i] = 1;
        uint8_t index = KnobIndexToParameterId(i);
        const ParameterDefinition& parameter = (
            ParameterDefinitions::parameter_definition(index));
        if (parameter.unit == UNIT_INT8) {
          int16_t value = GetParameterValue(parameter.id);
          value -= static_cast<int8_t>(parameter.min_value);
          value <<= 8;
          value /= (static_cast<int8_t>(parameter.max_value) - 
                    static_cast<int8_t>(parameter.min_value));
          locked_value_[i] = value >> 1;
        } else {
          uint16_t value = GetParameterValue(parameter.id);
          value -= parameter.min_value;
          value <<= 8;
          value /= (parameter.max_value - parameter.min_value);
          locked_value_[i] = value >> 1;
        }
      }
    } else {
      memset(locked_, 0, kNumEditingPots);
    }
  }
  display.set_cursor_position(kLcdNoCursor);
}

/* static */
void Editor::JumpToPageGroup(uint8_t group) {
  cursor_ = 0;
  assign_in_progress_ = 0;
  display_mode_ = DISPLAY_MODE_OVERVIEW;
  subpage_ = 0;
  // If we move to another group, go to the last visited page in this group.
  if (group != page_definition_[current_page_].group) {
    current_page_ = last_visited_page_[group];
  } else {
    current_page_ = page_definition_[current_page_].next;
  }
  // When switching to the modulation matrix page, go back to the previously
  // edited modulation.
  PageChange();
}

/* static */
void Editor::Relax() {
  // Disable the "get back to overview page" thing in the sequencer pages or
  // Load/save pages - in short, all pages where there's a moving cursor.
  if (display_mode_ == DISPLAY_MODE_EDIT_TEMPORARY &&
      display.cursor_position() == kLcdNoCursor) {
    display_mode_ = DISPLAY_MODE_OVERVIEW;
    Refresh();
  }
}

/* static */
void Editor::ShowEditCursor() {
  display.set_cursor_position(kLcdWidth + cursor_);
  display.set_cursor_character(
      display_mode_ == DISPLAY_MODE_EDIT ? kLcdEditCursor : kLcdCursor);
}

/* static */
void Editor::RandomizeParameter(uint8_t subpage, uint8_t parameter_index) {
  const ParameterDefinition& parameter = (
      ParameterDefinitions::parameter_definition(parameter_index));
  uint8_t range = parameter.max_value - parameter.min_value + 1;
  uint8_t value = Random::GetByte();
  while (value >= range) {
    value -= range;
  }
  value += parameter.min_value;
  engine.SetParameter(parameter.id + subpage * 3, value, 0);
}

/* static */
void Editor::RandomizePatch() {
  // Randomize all the main parameters
  for (uint8_t parameter = 0; parameter < 32; ++parameter) {
    RandomizeParameter(0, parameter);
  }
  // Randomize the first 8th modulation slots. Keep the last one to avoid
  // silent patches in which a bogus modulation source is routed to the VCA.
  for (uint8_t slot = 0; slot < kModulationMatrixSize - 4; ++slot) {
    for (uint8_t parameter = 33; parameter < 36; ++parameter) {
      RandomizeParameter(slot, parameter);
    }
  }
  engine.TouchPatch(1);
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
void Editor::SaveSystemSettings() {
  engine.mutable_system_settings()->EepromSave();
  engine.extra_system_settings().EepromSave();
}

/* static */
void Editor::StartMidiBackup() {
  Storage::SysExBulkDump();
}

/* static */
void Editor::Confirm(ConfirmPageSettings confirm_page_settings) {
  confirm_page_settings_ = confirm_page_settings;
  current_page_ = PAGE_CONFIRM;
  display_mode_ = DISPLAY_MODE_OVERVIEW;
  Refresh();
}

/* static */
void Editor::HandleKeyEvent(const KeyEvent& event) {
  if (event.shifted) {
    if (current_page_ != PAGE_LOAD_SAVE) {
      return;
    }
    switch (event.id) {
      case KEY_1:
        display.set_status('x');
        if (load_save_target_ & LOAD_SAVE_TARGET_PATCH) {
          engine.ResetPatch();
        }
        if (load_save_target_ & LOAD_SAVE_TARGET_SEQUENCE) {
          engine.ResetSequence();
        }
        break;

      case KEY_2:
        display.set_status('?');
        if (load_save_target_ & LOAD_SAVE_TARGET_PATCH) {
          RandomizePatch();
        }
        if (load_save_target_ & LOAD_SAVE_TARGET_SEQUENCE) {
          RandomizeSequence();
        }
        break;

      case KEY_3:
        display.set_status('>');
        if (load_save_target_ & LOAD_SAVE_TARGET_PATCH) {
          Storage::SysExDump(engine.mutable_patch());
        }
        if (load_save_target_ & LOAD_SAVE_TARGET_SEQUENCE) {
          Storage::SysExDump(engine.mutable_sequencer_settings());
        }
        break;
        
      case KEY_4:
        {
          ConfirmPageSettings confirm_midi_backup;
          confirm_midi_backup.text = STR_RES_START_FULL_MIDI;
          confirm_midi_backup.return_group = GROUP_OSC;
          confirm_midi_backup.callback = &StartMidiBackup;
          Confirm(confirm_midi_backup);
        }
        break;

      case KEY_MODE:
        {
          engine.mutable_system_settings()->sequence_patch_coupling ^= 1;
          current_page_ = 0;
          ToggleLoadSaveAction();
        }
        break;
    }
  } else if (event.hold_time >= 6) {
    switch (event.id) {
      case KEY_1:
        engine.NoteOn(0, 60, test_note_playing_ * 100);
        test_note_playing_ ^= 1;
        break;

      case KEY_2:
        if (current_page_ <= PAGE_MOD_MATRIX ||
            current_page_ == PAGE_SEQ_CONTROLLER) {
          parameter_to_assign_.id = page_definition_[
              current_page_].first_parameter_index;
          parameter_to_assign_.id += (current_page_ == PAGE_SEQ_CONTROLLER)
              ? last_knob_
              : cursor_;
          parameter_to_assign_.subpage = subpage_;
          DisplaySplashScreen(STR_RES_TOUCH_A_KNOB_TO);
          assign_in_progress_ = 1;
          return;  // To avoid refresh
        }
        break;
        
      case KEY_MODE:
        editor_mode_ = EDITOR_MODE_PERFORMANCE;
        JumpToPageGroup(GROUP_PERFORMANCE);
        break;
    }
  } else if (event.id == KEY_MODE) {
    editor_mode_ = (editor_mode_ != EDITOR_MODE_PATCH)
      ? EDITOR_MODE_PATCH
      : EDITOR_MODE_SEQUENCE;
    JumpToPageGroup(last_visited_group_[editor_mode_]);
  } else if (event.id == KEY_LOAD_SAVE) {
    if (current_page_ >= PAGE_SYS_KBD && current_page_ <= PAGE_SYS_TRIGGERS) {
      ConfirmPageSettings confirm_save_system_settings;
      confirm_save_system_settings.text = STR_RES_SAVE_MIDI_KBD;
      confirm_save_system_settings.return_group = GROUP_SYS;
      confirm_save_system_settings.callback = &SaveSystemSettings;
      Confirm(confirm_save_system_settings);
    } else {
      ToggleLoadSaveAction();
    }
  } else {
    uint8_t id = event.id;
    if (editor_mode_ == EDITOR_MODE_SEQUENCE) {
      JumpToPageGroup(id + GROUP_SEQUENCER_ARPEGGIATOR);
    } else if (editor_mode_ == EDITOR_MODE_PATCH) {
      JumpToPageGroup(id + GROUP_OSC);
    } else {
      JumpToPageGroup(GROUP_PERFORMANCE);
    }
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
void Editor::HandleIncrement(int8_t increment) {
  (*ui_handler_[page_definition_[current_page_].ui_type].increment_handler)(
      increment);
  Refresh();
}

/* static */
void Editor::HandleClick() {
  if (display_mode_ == DISPLAY_MODE_OVERVIEW) {
    display_mode_ = DISPLAY_MODE_EDIT;
    last_external_input_ = 0xff;
  } else {
    display_mode_ = DISPLAY_MODE_OVERVIEW;
  }
  if (ui_handler_[page_definition_[current_page_].ui_type].click_handler) {
    (*ui_handler_[page_definition_[current_page_].ui_type].click_handler)();
  }
  Refresh();
}

/* static */
uint8_t Editor::HandleNoteOn(uint8_t note, uint16_t velocity) {
  uint8_t handled = 0;
  if (current_page_ == PAGE_SEQ_TRACKER && display_mode_ == DISPLAY_MODE_EDIT) {
    engine.mutable_sequencer_settings()->steps[cursor_].set_note(note);
    engine.mutable_sequencer_settings()->steps[cursor_].set_velocity(velocity);
    ++cursor_;
    if (cursor_ >= engine.sequencer_settings().pattern_size) {
      cursor_ = 0;
    }
    Refresh();
    handled = 1;
  }
  return handled;
}

/* static */
void Editor::Refresh() {
  ConfigureFilterMenu();
  if (display_mode_ == DISPLAY_MODE_OVERVIEW) {
    (*ui_handler_[page_definition_[current_page_].ui_type].overview_page)();
  } else {
    (*ui_handler_[page_definition_[current_page_].ui_type].edit_page)();
  }
}

/* static */
void Editor::RestoreEditBuffer() {
  if (load_save_target_ & LOAD_SAVE_TARGET_PATCH) {
    Storage::Restore(engine.mutable_patch());
    engine.TouchPatch(1);
  }
  if (load_save_target_ & LOAD_SAVE_TARGET_SEQUENCE) {
    Storage::Restore(engine.mutable_sequencer_settings());
    engine.TouchSequence();
  }
}

/* static */
void Editor::BackupEditBuffer() {
  if (load_save_target_ & LOAD_SAVE_TARGET_PATCH) {
    Storage::Backup(engine.mutable_patch());
  }
  if (load_save_target_ & LOAD_SAVE_TARGET_SEQUENCE) {
    Storage::Backup(engine.mutable_sequencer_settings());
  }
}

/* static */
void Editor::ToggleLoadSaveAction() {
  if (editor_mode_ == EDITOR_MODE_SEQUENCE) {
    load_save_target_ = LOAD_SAVE_TARGET_SEQUENCE;
  } else {
    load_save_target_ = LOAD_SAVE_TARGET_PATCH;
  }
  if (engine.system_settings().sequence_patch_coupling) {
    load_save_target_ = LOAD_SAVE_TARGET_BOTH;
  }
  empty_patch_ = false;
  if (current_page_ != PAGE_LOAD_SAVE) {
    BackupEditBuffer();
    action_ = ACTION_LOAD;
  } else {
    if (action_ != ACTION_SAVE) {
      action_ = ACTION_SAVE;
      set_edited_item_number(edited_item_number());
    } else {
      action_ = ACTION_COMPARE;
    }
  }
  cursor_ = 0;
  assign_in_progress_ = 0;
  display.set_cursor_position(kLcdNoCursor);
  display_mode_ = DISPLAY_MODE_OVERVIEW;
  current_page_ = PAGE_LOAD_SAVE;
}

/* static */
uint16_t Editor::edited_item_number() {
  if (load_save_target_ & LOAD_SAVE_TARGET_PATCH) {
    return current_patch_number_;
  } else {
    return current_sequence_number_;
  }
}

const prog_uint8_t default_name[] PROGMEM = "user    ";

/* static */
void Editor::set_edited_item_number(int16_t value) {
  if (load_save_target_ & LOAD_SAVE_TARGET_PATCH) {
    if (value >= Storage::size<Patch>()) {
      value = 0;
    } else if (value < 0) {
      value = Storage::size<Patch>() - 1;
    }
    current_patch_number_ = value;
  } else {
    if (value >= Storage::size<SequencerSettings>()) {
      value = 0;
    } else if (value < 0) {
      value = Storage::size<SequencerSettings>() - 1;
    }
    current_sequence_number_ = value;
  }
  
  if (load_save_target_ == LOAD_SAVE_TARGET_PATCH && action_ == ACTION_SAVE) {
    uint8_t name[8];
    Storage::LoadPatchName(name, edited_item_number());
    empty_patch_ = true;
    for (uint8_t i = 0; i < 8; ++i) {
      if (name[i] != pgm_read_byte(default_name + i)) {
        empty_patch_ = false;
      }
    }
  } else {
    empty_patch_ = false;
  }
}

/* static */
uint8_t Editor::is_cursor_at_valid_position() {
#ifdef PORTAMENTO_SAVE_HACK
  uint16_t allowed_cursor_positions = load_save_target_ & LOAD_SAVE_TARGET_PATCH
      ? 0x07f7 : 0x0007;
#else
  uint16_t allowed_cursor_positions = load_save_target_ & LOAD_SAVE_TARGET_PATCH
      ? 0x0ff7 : 0x0007;
#endif
  return ((1 << cursor_) & allowed_cursor_positions) != 0;
}

/* static */
void Editor::HandleLoadSaveClick() {
  if (action_ == ACTION_LOAD) {
    action_ = ACTION_COMPARE;
    RestoreEditBuffer();
  } else if (action_ == ACTION_COMPARE) {
    action_ = ACTION_LOAD;
    HandleLoadSaveIncrement(0);
  } else {
    if (!is_cursor_at_valid_position()) {
      display_mode_ = DISPLAY_MODE_OVERVIEW;
    }
    if (cursor_ >= kLcdWidth - 4) {
      if (load_save_target_ & LOAD_SAVE_TARGET_PATCH) {
        Storage::WritePatch(edited_item_number());
      }
      if (load_save_target_ & LOAD_SAVE_TARGET_SEQUENCE) {
        Storage::WriteSequence(edited_item_number());
      }
      action_ = ACTION_LOAD;
    }
  }
}

/* static */
void Editor::HandleLoadSaveIncrement(int8_t increment) {
  if (action_ == ACTION_SAVE) {
    if (display_mode_ == DISPLAY_MODE_OVERVIEW) {
      int8_t new_cursor = static_cast<int8_t>(cursor_) + increment;
      if (new_cursor >= 0 && new_cursor < kLcdWidth) {
        cursor_ = new_cursor;
      }
    } else {
      if (cursor_ <= 2) {
        set_edited_item_number(edited_item_number() + increment);
      } else if (cursor_ >= 4 && cursor_ < 4 + kPatchNameSize &&
                 load_save_target_ & LOAD_SAVE_TARGET_PATCH) {
        uint8_t value = engine.patch().name[cursor_ - 4];
        value += increment;
        if (value >= 32 && value <= 128) {
          engine.mutable_patch()->name[cursor_ - 4] = value;
        }
      }
    }
  } else {
    set_edited_item_number(edited_item_number() + increment);
    if (action_ == ACTION_LOAD) {
      if (load_save_target_ & LOAD_SAVE_TARGET_PATCH) {
        uint16_t n = edited_item_number();
        Storage::LoadPatch(n);
        midi_dispatcher.ProgramChange(n);
        engine.TouchPatch(1);
        if (engine.system_settings().patch_restore_on_boot & 0x8000) {
          engine.mutable_system_settings()->patch_restore_on_boot = n | 0x8000;
          engine.system_settings().EepromSave();
        } 
      }
      if (load_save_target_ & LOAD_SAVE_TARGET_SEQUENCE) {
        Storage::LoadSequence(edited_item_number());
        engine.TouchSequence();
      }
    }
  }
}

/* static */
void Editor::DisplayLoadSavePage() {
  if (display_mode_ == DISPLAY_MODE_EDIT_TEMPORARY
      && action_ != ACTION_SAVE
      && engine.system_settings().display_delay) {
    DisplayEditDetailsPage();
    return;
  }
  ResourcesManager::LoadStringResource(
      STR_RES_BROWSE + action_,
      line_buffer_,
      8);
  ResourcesManager::LoadStringResource(
      STR_RES_PATCH + load_save_target_ - 1,
      line_buffer_ + 8,
      kLcdWidth - 8);
  AlignLeft(line_buffer_, 8);
  AlignLeft(line_buffer_ + 8, kLcdWidth - 8);
  line_buffer_[7] = ':';
  display.Print(0, line_buffer_);

  if (load_save_target_ & LOAD_SAVE_TARGET_PATCH) {
    UnsafeItoa<int16_t>(edited_item_number() + 1, 3, line_buffer_);
    AlignRight(line_buffer_, 3);
    memcpy(line_buffer_ + 4, engine.patch().name, kPatchNameSize);
    memset(
        line_buffer_ + 4 + kPatchNameSize,
        ' ',
        kLcdWidth - kPatchNameSize - 4);
  } else {
    UnsafeItoa<int16_t>(edited_item_number() + 1, 3, line_buffer_);
    AlignRight(line_buffer_, 3);
    for (uint8_t i = 0; i < 8; ++i) {
      line_buffer_[i + 4] = engine.sequencer_settings().steps[i].character();
    }
    memset(line_buffer_ + 12, ' ', kLcdWidth - 12);
  }
  line_buffer_[3] = empty_patch_ ? '*' : ' ';
  if (action_ == ACTION_SAVE) {
    line_buffer_[kLcdWidth - 3] = 'o';
    line_buffer_[kLcdWidth - 2] = 'k';
    if (cursor_ >= kLcdWidth - 4) {
      line_buffer_[kLcdWidth - 4] = '[';
      line_buffer_[kLcdWidth - 1] = ']';
    }
  }
  if (action_ == ACTION_SAVE && is_cursor_at_valid_position()) {
    ShowEditCursor();
  } else {
    display.set_cursor_position(kLcdNoCursor);
  }
  display.Print(1, line_buffer_);
}

/* static */
void Editor::MoveSequencerCursor(int8_t increment) {
  int8_t new_cursor = cursor_;
  new_cursor += increment;
  const SequencerSettings& seq = engine.sequencer_settings();
  if (new_cursor < 0) {
    cursor_ = 0xff;
    current_page_ = page_definition_[current_page_].overall_previous;
    PageChange();
  } else if (new_cursor >= seq.pattern_size) {
    cursor_ = 0;
    current_page_ = page_definition_[current_page_].overall_next;
    PageChange();
  } else {
    cursor_ = new_cursor;
  }
}

/* static */
void Editor::DisplayStepSequencerPage() {
  // 0123456789abcdef
  // step sequencer
  // 0000ffff44449999
  const SequencerSettings& seq = engine.sequencer_settings();
  if (cursor_ > seq.pattern_size - 1) {
    cursor_ = seq.pattern_size - 1;
  }
  ResourcesManager::LoadStringResource(
      STR_RES_STEP_SEQUENCER,
      line_buffer_,
      kLcdWidth);
  AlignLeft(line_buffer_, kLcdWidth);
  display.Print(0, line_buffer_);
  memset(line_buffer_, ' ', kLcdWidth);
  for (uint8_t i = 0; i < seq.pattern_size; ++i) {
    line_buffer_[i] = NibbleToAscii(
        seq.steps[(i + seq.pattern_rotation) & 0x0f].controller());
  }
  if (seq.pattern_size != kLcdWidth) {
    line_buffer_[seq.pattern_size] = '|';
  }
  display.Print(1, line_buffer_);
  ShowEditCursor();
}

/* static */
uint8_t Editor::HandleKnobAssignment(uint8_t knob_index) {
  if (assign_in_progress_) {
    engine.mutable_patch()->assigned_parameters[knob_index] = \
        parameter_to_assign_;
    assign_in_progress_ = 0;
    editor_mode_ = EDITOR_MODE_PERFORMANCE;
    JumpToPageGroup(GROUP_PERFORMANCE);
    return 1;
  }
  return 0;
}

/* static */
void Editor::HandleSequencerNavigation(
    uint8_t knob_index,
    uint16_t value) {
  if (!HandleKnobAssignment(knob_index)) {
    switch (knob_index) {
      case 1:
        {
          cursor_ = value >> 6;
          uint8_t max_position = engine.sequencer_settings().pattern_size - 1;
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
          last_knob_ = 1;
          engine.SetParameter(PRM_SEQ_PATTERN_SIZE, new_size, 0);
        }
        break;
    }
  }
}

/* static */
void Editor::HandleStepSequencerInput(
    uint8_t knob_index,
    uint16_t value) {
  HandleSequencerNavigation(knob_index, value);
  if (knob_index == 2) {
    SequencerSettings* seq = engine.mutable_sequencer_settings();
    seq->steps[(cursor_ + seq->pattern_rotation) & 0x0f].set_controller(
        value >> 6);
  } else if (knob_index == 0) {
    engine.SetParameter(PRM_SEQ_PATTERN_ROTATION, value >> 6, 0);
    last_knob_ = 0;
  }
}

/* static */
void Editor::HandleStepSequencerIncrement(int8_t increment) {
  if (display_mode_ == DISPLAY_MODE_OVERVIEW) {
    MoveSequencerCursor(increment);
  } else {
    SequencerSettings* seq = engine.mutable_sequencer_settings();
    uint8_t position = (cursor_ + seq->pattern_rotation) & 0x0f;
    seq->steps[position].set_controller(
        seq->steps[position].controller() + \
        increment);
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
  } else {
    // This is an invisible character. It is just there to prevent the status
    // indicator to be printed on the last column instead of the first.
    line_buffer_[kLcdWidth - 1] = 0xfe;
  }
  display.Print(0, line_buffer_);

  engine.sequencer_settings().PrintStep(cursor_, line_buffer_);
  line_buffer_[0] = 0x7e;
  display.Print(1, line_buffer_);
  if (display_mode_ == DISPLAY_MODE_OVERVIEW) {
    display.set_cursor_position(0xff);
  } else {
    display.set_cursor_character(kLcdEditCursor);
    display.set_cursor_position(kLcdWidth + 7);
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
        uint8_t max_position = engine.sequencer_settings().pattern_size - 1;
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
void Editor::HandleTrackerIncrement(int8_t increment) {
  if (display_mode_ == DISPLAY_MODE_OVERVIEW) {
    MoveSequencerCursor(increment);
  } else {
    int8_t note = engine.mutable_sequencer_settings()->steps[cursor_].note();
    note += increment;
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
  ShowEditCursor();
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
void Editor::HandlePageRIncrement(int8_t increment) {
  if (display_mode_ == DISPLAY_MODE_OVERVIEW) {
    MoveSequencerCursor(increment);
  } else {
    int8_t flags = engine.mutable_sequencer_settings()->steps[cursor_].flags();
    flags += increment;
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
    const ParameterDefinition& parameter = (
        ParameterDefinitions::parameter_definition(index));
    uint8_t caption_position = i * kColumnWidth;
    uint8_t text_position = i * kColumnWidth + kLcdWidth + 1;
    ResourcesManager::LoadStringResource(
        parameter.short_name,
        line_buffer_ + caption_position,
        kColumnWidth - 1);
    line_buffer_[caption_position + kColumnWidth - 1] = '\0';
    line_buffer_[text_position + kColumnWidth - 1] = '\0';
    AlignRight(line_buffer_ + caption_position, kColumnWidth);
    PrettyPrintParameterValue(
        parameter,
        line_buffer_ + text_position,
        kColumnWidth - 1);
    AlignRight(line_buffer_ + text_position, kColumnWidth);
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
  if (engine.system_settings().display_delay == 0) {
    DisplayEditOverviewPage();
    return;
  }
  // 0123456789abcdef
  // programmer
  // cutoff        42
  //
  // OR
  //
  // filter
  // cutoff       127
  //
  // OR
  //
  // mod src>dst
  // amount        63
  if (current_page_ == PAGE_MOD_MATRIX) {
    const ParameterDefinition& current_source = (
        ParameterDefinitions::parameter_definition(
            page_definition_[PAGE_MOD_MATRIX].first_parameter_index + 1));
    PrettyPrintParameterValue(
        current_source,
        line_buffer_ + 4,
        kColumnWidth - 1);
    const ParameterDefinition& current_destination = (
        ParameterDefinitions::parameter_definition(
          page_definition_[PAGE_MOD_MATRIX].first_parameter_index + 2));
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
  if (last_external_input_ != 0xff) {
    index = last_external_input_;
  }
  const ParameterDefinition& parameter = (
      ParameterDefinitions::parameter_definition(index));
  const PageDefinition& page = page_definition_[current_page_];

  if (current_page_ != PAGE_MOD_MATRIX && last_external_input_ == 0xff) {
    ResourcesManager::LoadStringResource(
        page.name,
        line_buffer_,
        kLcdWidth);
    AlignLeft(line_buffer_, kLcdWidth);
    display.Print(0, line_buffer_);
  }
  if (last_external_input_ != 0xff) {
    strcpy_P(line_buffer_, PSTR("programmer"));
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
  if (current_page_ == PAGE_LOAD_SAVE
      && (action_ == ACTION_SAVE || action_ == ACTION_COMPARE)) {
    return 0xff;
  }
  if (current_page_ == PAGE_PERFORMANCE || current_page_ == PAGE_LOAD_SAVE) {
    subpage_ = engine.mutable_patch()->assigned_parameters[knob_index].subpage;
    return engine.mutable_patch()->assigned_parameters[knob_index].id;
  } else {
    return page_definition_[current_page_].first_parameter_index + \
        knob_index;
  }
}

/* static */
void Editor::HandleEditInput(uint8_t knob_index, uint16_t value) {
  if (!HandleKnobAssignment(knob_index)) {
    uint8_t value_7bits = value >> 3;
    
    // In "snap" mode, the knob is locked until we reached the value the
    // parameter is supposed to have.
    if (locked_[knob_index]) {
      int8_t delta = value_7bits - locked_value_[knob_index];
      if (delta < -4 || delta > 4) {
        return;
      }
      locked_[knob_index] = 0;
    }

    display_mode_ = DISPLAY_MODE_EDIT_TEMPORARY;
    uint8_t index = KnobIndexToParameterId(knob_index);
    if (index == 0xff) {
      return;
    }
    const ParameterDefinition& parameter = (
        ParameterDefinitions::parameter_definition(index));
    SetParameterValue(
        parameter.id,
        ParameterDefinitions::Scale(parameter, value_7bits));
    cursor_ = knob_index;

    last_external_input_ = 0xff;
  }
}

/* static */
void Editor::HandleProgrammerInput(uint8_t ui_parameter_index, uint16_t value) {
  display_mode_ = DISPLAY_MODE_EDIT_TEMPORARY;
  last_external_input_ = ui_parameter_index;
}

/* static */
void Editor::HandleEditIncrement(int8_t increment) {
  if (display_mode_ == DISPLAY_MODE_OVERVIEW) {
    int8_t new_cursor = static_cast<int8_t>(cursor_) + increment;
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
    PageChange();
  } else {
    uint8_t index = KnobIndexToParameterId(cursor_);
    locked_[cursor_] = 0;
    const ParameterDefinition& parameter = (
        ParameterDefinitions::parameter_definition(index));
    uint8_t old_value = GetParameterValue(parameter.id);
    uint8_t new_value = ParameterDefinitions::Increment(
        parameter,
        old_value,
        increment);
    if (new_value != old_value) {
      SetParameterValue(parameter.id, new_value);
    }
  }
}

/* static */
void Editor::SetParameterValue(uint8_t id, uint8_t value) {
  // Dirty hack for the modulation page.
  if (current_page_ == PAGE_MOD_MATRIX && id == PRM_MOD_ROW) {
    subpage_ = value;
    last_visited_subpage_ = value;
  } else if (current_page_ == PAGE_MOD_OPERATORS && id == PRM_OP_ROW ) {
    subpage_ = value;
  } else {
    engine.SetParameter(id + subpage_ * 3, value, 1);
  }
}

/* static */
uint8_t Editor::GetParameterValue(uint8_t id) {
  uint8_t value;
  if (current_page_ == PAGE_MOD_MATRIX && id == PRM_MOD_ROW) {
    value = subpage_;
  } else if (current_page_ == PAGE_MOD_OPERATORS && id == PRM_OP_ROW ) {
    value = subpage_;
  } else {
    value = engine.GetParameter(id + subpage_ * 3);
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
  ResourceId text = ResourcesManager::Lookup<uint16_t, uint8_t>(
      units_definitions,
      parameter.unit);
  char prefix = '\0';
  switch (parameter.unit) {
    case UNIT_INT8:
      value = int16_t(int8_t(value));
      break;
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
    case UNIT_LFO_WAVEFORM:
      if (value >= LFO_WAVEFORM_WAVE_1) {
        text = NULL;
        value = value - LFO_WAVEFORM_WAVE_1 + 1;
        prefix = '\x05';
      }
      break;
    case UNIT_TEMPO_WITH_EXTERNAL_CLOCK:
      if (value < 40) {
        value = value - 35;
        text = STR_RES_EXTERN;
      } else if (value > 240) {
        value = ResourcesManager::Lookup<uint16_t, uint8_t>(
            lut_res_turbo_tempi, value - 240 - 1);
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
    case UNIT_SPLIT_POINT:
      --value;
      prefix = 'C';
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
void Editor::HandleConfirmClick() {
  if (cursor_) {
    (*confirm_page_settings_.callback)();
  }
  JumpToPageGroup(confirm_page_settings_.return_group);
  Refresh();
}

/* static */
void Editor::HandleConfirmIncrement(int8_t increment) {
  cursor_ = !cursor_;
}

/* static */
void Editor::HandleConfirmInput(uint8_t knob_index, uint16_t value) {
}

/* static */
void Editor::DisplayConfirmPage() {
  display.set_cursor_position(kLcdNoCursor);
  for (uint8_t i = 0; i < 2; ++i) {
    ResourcesManager::LoadStringResource(
        confirm_page_settings_.text + i,
        line_buffer_,
        kLcdWidth);
    AlignLeft(line_buffer_, kLcdWidth);
    if (i == 1) {
      if (cursor_) {
        line_buffer_[kLcdWidth - 2] = 'o';
        line_buffer_[kLcdWidth - 1] = 'k';
      } else {
        line_buffer_[kLcdWidth - 2] = 'n';
        line_buffer_[kLcdWidth - 1] = 'o';
      }
    }
    display.Print(i, line_buffer_);
  }
}

/* static */
void Editor::BootOnPatchBrowsePage(uint8_t index) {
  if (index >= Storage::size<Patch>()) {
    index = Storage::size<Patch>() - 1;
  } 
  current_patch_number_ = index;
  current_page_ = 0;
  ToggleLoadSaveAction();
  HandleLoadSaveIncrement(0);
  Refresh();
}

}  // namespace shruthi
