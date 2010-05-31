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
#include "hardware/shruthi/parameter_definitions.h"
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
  STR_RES__SQUARE,
  STR_RES_SUM,
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
  STR_RES_SWING,
  0,
  STR_RES_FREE
};

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
    &Editor::HandleLoadSaveInput, &Editor::HandleLoadSaveIncrement,
    &Editor::HandleLoadSaveClick },
  { &Editor::DisplayConfirmPage, &Editor::DisplayConfirmPage,
    &Editor::HandleConfirmInput, &Editor::HandleConfirmIncrement,
    &Editor::HandleConfirmClick },
};

const PageDefinition Editor::page_definition_[] = {
  /* PAGE_OSC_OSC_1 */ { PAGE_OSC_OSC_2, GROUP_OSC,
    PAGE_MOD_MATRIX, PAGE_OSC_OSC_2,
    STR_RES_OSCILLATOR_1, PARAMETER_EDITOR, 0, LED_1_MASK },

  /* PAGE_OSC_OSC_2 */ { PAGE_OSC_OSC_MIX, GROUP_OSC,
    PAGE_OSC_OSC_1, PAGE_OSC_OSC_MIX,
    STR_RES_OSCILLATOR_2, PARAMETER_EDITOR, 4, LED_2_MASK },

  /* PAGE_OSC_OSC_MIX */ { PAGE_OSC_OSC_1, GROUP_OSC,
    PAGE_OSC_OSC_2, PAGE_FILTER_FILTER,
    STR_RES_MIXER, PARAMETER_EDITOR, 8, LED_1_MASK | LED_2_MASK },

  /* PAGE_FILTER_FILTER */ { PAGE_FILTER_FILTER, GROUP_FILTER,
    PAGE_OSC_OSC_MIX, PAGE_MOD_ENV_1,
    STR_RES_FILTER, PARAMETER_EDITOR, 12, LED_3_MASK },

  /* PAGE_MOD_ENV_1 */ { PAGE_MOD_ENV_2, GROUP_MOD_SOURCES,
    PAGE_FILTER_FILTER, PAGE_MOD_ENV_2,
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

  /* PAGE_MOD_MATRIX */ { PAGE_MOD_MATRIX, GROUP_MOD_MATRIX,
    PAGE_MOD_LFO_2, PAGE_OSC_OSC_1,
    STR_RES_MODULATION, PARAMETER_EDITOR, 32, 0 },

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
    PAGE_SYS_MIDI, PAGE_SYS_MIDI,
    STR_RES_KEYBOARD, PARAMETER_EDITOR, 44, LED_6_MASK },

  /* PAGE_SYS_MIDI */ { PAGE_SYS_KBD, GROUP_SYS,
    PAGE_SYS_KBD, PAGE_SYS_KBD,
    STR_RES_MIDI, PARAMETER_EDITOR, 48, LED_6_MASK },

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
uint8_t Editor::current_patch_number_ = 0;
uint8_t Editor::current_sequence_number_ = 0;

uint8_t Editor::test_note_playing_ = 0;
uint8_t Editor::assign_in_progress_ = 0;
ParameterAssignment Editor::parameter_to_assign_;
ConfirmPageSettings Editor::confirm_page_settings_;
/* </static> */

/* static */
void Editor::Init() {
  line_buffer_[kLcdWidth] = '\0';
}

/* static */
void Editor::JumpToPageGroup(uint8_t group) {
  cursor_ = 0;
  assign_in_progress_ = 0;
  display.set_cursor_position(kLcdNoCursor);
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
  if (current_page_ == PAGE_MOD_MATRIX) {
    subpage_ = last_visited_subpage_;
  }
  last_visited_group_[editor_mode_] = page_definition_[current_page_].group;
  last_visited_page_[group] = current_page_;
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
void Editor::RandomizeParameter(uint8_t subpage, uint8_t parameter_index) {
  const ParameterDefinition& parameter = (
      ParameterDefinitions::parameter_definition(parameter_index));
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
        if (editor_mode_ == EDITOR_MODE_PATCH) {
          engine.ResetPatch();
        } else {
          engine.ResetSequence();
        }
        break;

      case KEY_2:
        display.set_status('?');
        if (editor_mode_ == EDITOR_MODE_PATCH) {
          RandomizePatch();
        } else {
          RandomizeSequence();
        }
        break;

      case KEY_3:
        display.set_status('>');
        if (editor_mode_ == EDITOR_MODE_PATCH) {
          Storage::SysExDump(engine.mutable_patch());
        } else {
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
    }
  } else if (event.hold_time >= 6) {
    switch (event.id) {
      case KEY_1:
        engine.NoteOn(0, 48, test_note_playing_ ? 0 : 100);
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
    if (current_page_ >= PAGE_SYS_KBD && current_page_ <= PAGE_SYS_MIDI) {
      ConfirmPageSettings confirm_save_system_settings;
      confirm_save_system_settings.text = STR_RES_SAVE_MIDI_KBD;
      confirm_save_system_settings.return_group = GROUP_SYS;
      confirm_save_system_settings.callback = &SaveSystemSettings;
      Confirm(confirm_save_system_settings);
    } else if (current_page_ != PAGE_PERFORMANCE) {
      ToggleLoadSaveAction();
    }
  } else {
    uint8_t id = event.id;
    if (editor_mode_ == EDITOR_MODE_SEQUENCE) {
      JumpToPageGroup(id + GROUP_SEQUENCER_ARPEGGIATOR);
    } else {
      JumpToPageGroup(id + GROUP_OSC);
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
void Editor::HandleIncrement(int8_t direction) {
  (*ui_handler_[page_definition_[current_page_].ui_type].increment_handler)(
      direction);
  Refresh();
}

/* static */
void Editor::HandleClick() {
  if (display_mode_ == DISPLAY_MODE_OVERVIEW) {
    display_mode_ = DISPLAY_MODE_EDIT;
    display.set_cursor_character(' ');
  } else {
    display_mode_ = DISPLAY_MODE_OVERVIEW;
    display.set_cursor_character(kLcdNoCursor);
  }
  if (ui_handler_[page_definition_[current_page_].ui_type].click_handler) {
    (*ui_handler_[page_definition_[current_page_].ui_type].click_handler)();
  }
  Refresh();
}

/* static */
void Editor::Refresh() {
  if (display_mode_ == DISPLAY_MODE_OVERVIEW) {
    (*ui_handler_[page_definition_[current_page_].ui_type].overview_page)();
  } else {
    (*ui_handler_[page_definition_[current_page_].ui_type].edit_page)();
  }
}

/* static */
void Editor::RestoreEditBuffer() {
  if (editor_mode_ == EDITOR_MODE_PATCH) {
    Storage::Restore(engine.mutable_patch());
    engine.TouchPatch(1);
  } else {
    Storage::Restore(engine.mutable_sequencer_settings());
    engine.TouchSequence();
  }
}

/* static */
void Editor::ToggleLoadSaveAction() {
  if (current_page_ != PAGE_LOAD_SAVE) {
    if (editor_mode_ == EDITOR_MODE_PATCH) {
      Storage::Backup(engine.mutable_patch());
    } else {
      Storage::Backup(engine.mutable_sequencer_settings());
    }
    action_ = ACTION_LOAD;
  } else {
    if (action_ != ACTION_SAVE) {
      RestoreEditBuffer();
      action_ = ACTION_SAVE;
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
int8_t Editor::edited_item_number() {
  if (editor_mode_ == EDITOR_MODE_PATCH) {
    return current_patch_number_;
  } else {
    return current_sequence_number_;
  }
}

/* static */
void Editor::set_edited_item_number(int8_t value) {
  if (editor_mode_ == EDITOR_MODE_PATCH) {
    if (value >= 0 && value < Storage::size<Patch>()) {
      current_patch_number_ = value;
    }
  } else {
    if (value >= 0 && value < Storage::size<SequencerSettings>()) {
      current_sequence_number_ = value;
    }
  }
}

/* static */
uint8_t Editor::is_cursor_at_valid_position() {
  uint16_t allowed_cursor_positions = editor_mode_ == EDITOR_MODE_PATCH
      ? 0x07fb : 0x0003;
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
      if (editor_mode_ == EDITOR_MODE_PATCH) {
        Storage::Write(engine.mutable_patch(), current_patch_number_);
      } else {
        Storage::Write(engine.mutable_sequencer_settings(),
                       current_sequence_number_);
      }
      action_ = ACTION_LOAD;
    }
  }
}

/* static */
void Editor::HandleLoadSaveIncrement(int8_t direction) {
  if (action_ == ACTION_SAVE) {
    if (display_mode_ == DISPLAY_MODE_OVERVIEW) {
      int8_t new_cursor = static_cast<int8_t>(cursor_) + direction;
      if (new_cursor >= 0 && new_cursor < kLcdWidth) {
        cursor_ = new_cursor;
      }
    } else {
      if (cursor_ <= 1) {
        set_edited_item_number(edited_item_number() + direction);      
      } else if (cursor_ >= 3 && cursor_ < 3 + kPatchNameSize &&
                 editor_mode_ == EDITOR_MODE_PATCH) {
        uint8_t value = engine.patch().name[cursor_ - 3];
        value += direction;
        if (value >= 32 && value <= 128) {
          engine.mutable_patch()->name[cursor_ - 3] = value;
        }
      }
    }
  } else {
    set_edited_item_number(edited_item_number() + direction);
    if (action_ == ACTION_LOAD) {
      if (editor_mode_ == EDITOR_MODE_PATCH) {
        Storage::Load(engine.mutable_patch(), edited_item_number());
        engine.TouchPatch(1);
      } else {
        Storage::Load(engine.mutable_sequencer_settings(),
                      edited_item_number());
        engine.TouchSequence();
      }
    }
  }
}

/* static */
void Editor::HandleLoadSaveInput(uint8_t knob_index, uint16_t value) { }

/* static */
void Editor::DisplayLoadSavePage() {
  ResourcesManager::LoadStringResource(
      STR_RES_LOAD + action_,
      line_buffer_,
      8);
  ResourcesManager::LoadStringResource(
      STR_RES_PATCH + editor_mode_,
      line_buffer_ + 8,
      kLcdWidth - 8);
  AlignLeft(line_buffer_, 8);
  AlignLeft(line_buffer_ + 8, kLcdWidth - 8);
  line_buffer_[7] = ':';
  display.Print(0, line_buffer_);

  if (editor_mode_ == EDITOR_MODE_PATCH) {
    UnsafeItoa<int16_t>(edited_item_number() + 1, 2, line_buffer_);
    AlignRight(line_buffer_, 2);
    memcpy(line_buffer_ + 3, engine.patch().name, kPatchNameSize);
  } else {
    UnsafeItoa<int16_t>(edited_item_number() + 1, 2, line_buffer_);
    AlignRight(line_buffer_, 2);
    for (uint8_t i = 0; i < 8; ++i) {
      line_buffer_[i + 3] = engine.sequencer_settings().steps[i].character();
    }
  }
  line_buffer_[2] = ' ';
  memset(line_buffer_ + 11, ' ', kLcdWidth - 11);
  if (action_ == ACTION_SAVE) {
    line_buffer_[kLcdWidth - 2] = 'k';
    line_buffer_[kLcdWidth - 3] = 'o';
    if (cursor_ >= kLcdWidth - 4) {
      line_buffer_[kLcdWidth - 4] = '[';
      line_buffer_[kLcdWidth - 1] = ']';
    }
  }
  if (action_ == ACTION_SAVE && is_cursor_at_valid_position()) {
    display.set_cursor_position(kLcdWidth + cursor_);
  } else {
    display.set_cursor_position(kLcdNoCursor);
  }
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
  last_visited_page_[page_definition_[current_page_].group] = current_page_;
  last_visited_group_[editor_mode_] = page_definition_[current_page_].group;
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
  display.set_cursor_position(kLcdWidth + cursor_);
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
          last_knob_ = 1;
          engine.SetParameter(PRM_SEQ_PATTERN_SIZE, new_size);
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
    engine.SetParameter(PRM_SEQ_PATTERN_ROTATION, value >> 6);
    last_knob_ = 0;
  }
}

/* static */
void Editor::HandleStepSequencerIncrement(int8_t direction) {
  if (display_mode_ == DISPLAY_MODE_OVERVIEW) {
    MoveSequencerCursor(direction);
  } else {
    SequencerSettings* seq = engine.mutable_sequencer_settings();
    uint8_t position = (cursor_ + seq->pattern_rotation) & 0x0f;
    seq->steps[position].set_controller(
        seq->steps[position].controller() + \
        direction);
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
  if (display_mode_ == DISPLAY_MODE_OVERVIEW) {
    display.set_cursor_position(0xff);
  } else {
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
  if (display_mode_ == DISPLAY_MODE_OVERVIEW) {
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
  if (display_mode_ == DISPLAY_MODE_OVERVIEW) {
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
    const ParameterDefinition& parameter = (
        ParameterDefinitions::parameter_definition(index));
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
  const ParameterDefinition& parameter = (
      ParameterDefinitions::parameter_definition(index));
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
    display_mode_ = DISPLAY_MODE_EDIT_TEMPORARY;
    uint8_t value_7bits = value >> 3;
    uint8_t index = KnobIndexToParameterId(knob_index);
    const ParameterDefinition& parameter = (
        ParameterDefinitions::parameter_definition(index));
    SetParameterValue(
        parameter.id,
        ParameterDefinitions::Scale(parameter, value_7bits));
    cursor_ = knob_index;
  }
}

/* static */
void Editor::HandleEditIncrement(int8_t direction) {
  if (display_mode_ == DISPLAY_MODE_OVERVIEW) {
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
    last_visited_group_[editor_mode_] = page_definition_[current_page_].group;
  } else {
    uint8_t index = KnobIndexToParameterId(cursor_);
    const ParameterDefinition& parameter = (
        ParameterDefinitions::parameter_definition(index));

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
void Editor::HandleConfirmClick() {
  if (cursor_) {
    (*confirm_page_settings_.callback)();
  }
  JumpToPageGroup(confirm_page_settings_.return_group);
  Refresh();
}

/* static */
void Editor::HandleConfirmIncrement(int8_t direction) {
  cursor_ = !cursor_;
}

/* static */
void Editor::HandleConfirmInput(uint8_t knob_index, uint16_t value) {
}

/* static */
void Editor::DisplayConfirmPage() {
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

}  // namespace hardware_shruthi
