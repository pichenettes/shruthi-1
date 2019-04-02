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
// Patch editor.
//
// I really hate this code. Work on a "UI" framework to avoid such horrible
// things in progress...

#include "shruthi/editor.h"

#include "avrlib/deprecated/devices/switch_array.h"
#include "shruthi/display.h"
#include "shruthi/midi_dispatcher.h"
#include "shruthi/parameter.h"
#include "shruthi/storage.h"
#include "shruthi/part.h"
#include "shruthi/ui.h"
#include "avrlib/string.h"

using namespace avrlib;
using namespace avrlib;

using avrlib::kLcdNoCursor;

namespace shruthi {

/* extern */
Editor editor;

/* static */
const UiHandler Editor::ui_handler_[] = {
  { &Editor::DisplayEditOverviewPage, &Editor::DisplayEditDetailsPage,
    &Editor::OnEditInput, &Editor::OnEditIncrement, NULL },
  { &Editor::DisplayTrackerPage, &Editor::DisplayTrackerPage,
    &Editor::OnTrackerInput, &Editor::OnTrackerIncrement, NULL },
  { &Editor::DisplayPageRPage, &Editor::DisplayPageRPage,
    &Editor::OnPageRInput, &Editor::OnPageRIncrement, NULL },
  { &Editor::DisplayStepSequencerPage, &Editor::DisplayStepSequencerPage,
    &Editor::OnStepSequencerInput, &Editor::OnStepSequencerIncrement,
    NULL },
  { &Editor::DisplayLoadSavePage, &Editor::DisplayLoadSavePage,
    &Editor::OnEditInput, &Editor::OnLoadSaveIncrement,
    &Editor::OnLoadSaveClick },
  { &Editor::DisplayConfirmPage, &Editor::DisplayConfirmPage,
    &Editor::OnConfirmInput, &Editor::OnConfirmIncrement,
    &Editor::OnConfirmClick },
  { &Editor::DisplayJamPage, &Editor::DisplayEditDetailsPage,
    &Editor::OnJamPageInput, &Editor::OnJamPageIncrement,
    &Editor::OnJamPageClick },
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
    PAGE_SYS_DISPLAY, PAGE_SYS_MIDI,
    STR_RES_KEYBOARD, PARAMETER_EDITOR, 44, LED_6_MASK },

  /* PAGE_SYS_MIDI */ { PAGE_SYS_DISPLAY, GROUP_SYS,
    PAGE_SYS_KBD, PAGE_SYS_DISPLAY,
    STR_RES_MIDI, PARAMETER_EDITOR, 48, LED_6_MASK },

  /* PAGE_SYS_DISPLAY */ { PAGE_SYS_KBD, GROUP_SYS,
    PAGE_SYS_MIDI, PAGE_SYS_KBD,
    STR_RES_SYSTEM, PARAMETER_EDITOR, 52, LED_6_MASK },

  /* PAGE_LOAD_SAVE */ { PAGE_LOAD_SAVE, GROUP_LOAD_SAVE,
    PAGE_LOAD_SAVE, PAGE_LOAD_SAVE,
    STR_RES_PATCH, LOAD_SAVE, 0, LED_WRITE_MASK },

  /* PAGE_CONFIRM */ { PAGE_CONFIRM, GROUP_CONFIRM,
    PAGE_CONFIRM, PAGE_CONFIRM,
    STR_RES_PATCH, CONFIRM, 0, 0x55 },

  /* PAGE_JAM */ { PAGE_JAM, GROUP_JAM,
    PAGE_JAM, PAGE_JAM,
    STR_RES_PATCH, JAM, 0, 0x00 },
};

/* <static> */
ParameterPage Editor::current_page_ = PAGE_FILTER_FILTER;
ParameterPage Editor::last_visited_page_[] = {
    PAGE_OSC_OSC_1,
    PAGE_FILTER_FILTER,
    PAGE_MOD_ENV_1,
    PAGE_MOD_MATRIX,

    PAGE_SEQ_SEQUENCER,
    PAGE_SEQ_TRACKER,
    PAGE_SEQ_RHYTHM,
    PAGE_SYS_KBD,

    PAGE_LOAD_SAVE,
    PAGE_CONFIRM
};
uint8_t Editor::last_visited_subpage_ = 0;
uint8_t Editor::display_mode_ = DISPLAY_MODE_OVERVIEW;
uint8_t Editor::editor_mode_ = EDITOR_MODE_PATCH;
uint8_t Editor::last_visited_group_[] = {
    GROUP_FILTER,
    GROUP_SEQUENCER_ARPEGGIATOR,
};

char Editor::line_buffer_[kLcdWidth * kLcdHeight + 1];

uint8_t Editor::cursor_;
uint8_t Editor::last_knob_;
uint8_t Editor::subpage_;
uint8_t Editor::action_;
uint8_t Editor::programmer_parameter_;
uint16_t Editor::current_patch_number_ = 0;

int8_t Editor::jam_note_ = 0;
int8_t Editor::jam_note_root_ = 60;
int8_t Editor::jam_mode_shifts_[4] = { 2, 5, 7, 4 };
uint8_t Editor::jam_mode_previous_page_;

ConfirmPageSettings Editor::confirm_page_settings_;
bool Editor::snapped_[36];
bool Editor::empty_patch_;
uint16_t Editor::deferred_load_;
/* </static> */

/* static */
void Editor::Init() {
  parameter_manager.Init();
  
  line_buffer_[kLcdWidth] = '\0';
  ConfigureFilterMenu();
  deferred_load_ = 0xffff;
}

void Editor::ConfigureFilterMenu() {
  uint8_t n = part.system_settings().expansion_filter_board;
  if (n == 0) {
    page_definition_[PAGE_FILTER_FILTER].next = PAGE_FILTER_FILTER;
    page_definition_[PAGE_FILTER_FILTER].overall_next = PAGE_MOD_ENV_1;
    page_definition_[PAGE_MOD_ENV_1].overall_previous = PAGE_FILTER_FILTER;
  } else {
    page_definition_[PAGE_FILTER_FILTER].next = PAGE_FILTER_MULTIMODE;
    page_definition_[PAGE_FILTER_FILTER].overall_next = PAGE_FILTER_MULTIMODE;
    page_definition_[PAGE_MOD_ENV_1].overall_previous = PAGE_FILTER_MULTIMODE;
    page_definition_[PAGE_FILTER_MULTIMODE].first_parameter_index = 62;
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
    memset(snapped_, false, sizeof(snapped_));
  }
  display.set_cursor_position(kLcdNoCursor);
}

/* static */
void Editor::JumpToPageGroup(uint8_t group) {
  cursor_ = 0;
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
bool Editor::Relax() {
  // Disable the "get back to overview page" thing in the sequencer pages or
  // Load/save pages - in short, all pages where there's a moving cursor.
  if (display_mode_ == DISPLAY_MODE_EDIT_TEMPORARY &&
      display.cursor_position() == kLcdNoCursor) {
    display_mode_ = DISPLAY_MODE_OVERVIEW;
    return true;
  } else {
    return false;
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
  const Parameter& parameter = parameter_manager.parameter(parameter_index);
  uint8_t value = parameter.RandomValue();
  part.SetParameter(
      parameter_index,
      parameter.offset + subpage * 3,
      value,
      true);
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
  part.Touch(true);
}

/* static */
void Editor::RandomizeSequence() {
  for (uint8_t i = 0; i < kNumSteps; ++i) {
    SequencerSettings* settings = part.mutable_sequencer_settings();
    settings->steps[i].set_raw(
        Random::GetByte(),
        Random::GetByte());
    settings->steps[i].set_note(
        (settings->steps[i].note() & 0x3f) + 0x20);
  }
}

/* static */
void Editor::SaveSystemSettings() {
  part.mutable_system_settings()->EepromSave();
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

const prog_uint8_t programmer_switch_mapping[] PROGMEM = {
  3,
  3 | 0x80,
  8 | 0x80,
  8,
  0 | 0x80,
  0,
  4 | 0x80,
  4,
  
  28 | 0x80,
  28,
  24 | 0x80,
  24,
  
  0xff
};

/* static */
void Editor::OnProgrammerSwitch(const Event& event) {
  uint8_t id = event.control_id - SWITCH_OSC_2_MINUS;
  uint8_t parameter_index = pgm_read_byte(programmer_switch_mapping + id);
  if (parameter_index != 0xff) {
    int8_t increment = parameter_index & 0x80 ? -1 : 1;
    parameter_index = parameter_index & 0x7f;

    display_mode_ = DISPLAY_MODE_EDIT_TEMPORARY;
    programmer_parameter_ = parameter_index;
    IncrementParameterValue(parameter_index, increment);
  } else {
    OnLongClick();
  }
};

/* static */
void Editor::OnSwitch(const Event& event) {
  uint8_t id = event.control_id;
  if (event.value == 0xff) {
    if (current_page_ != PAGE_LOAD_SAVE) {
      return;
    }
    switch (id) {
      case SWITCH_1:
        display.set_status('x');
        part.ResetPatch();
        part.ResetSequence();
        break;

      case SWITCH_2:
        display.set_status('?');
        RandomizePatch();
        RandomizeSequence();
        break;

      case SWITCH_3:
        display.set_status('>');
        Storage::SysExDump(part.mutable_patch());
        Storage::SysExDump(part.mutable_sequencer_settings());
        break;
        
      case SWITCH_4:
        {
          ConfirmPageSettings confirm_midi_backup;
          confirm_midi_backup.text = STR_RES_START_FULL_MIDI;
          confirm_midi_backup.return_group = GROUP_OSC;
          confirm_midi_backup.callback = &StartMidiBackup;
          Confirm(confirm_midi_backup);
        }
        break;
    }
  } else if (id == SWITCH_MODE) {
    editor_mode_ = (editor_mode_ != EDITOR_MODE_PATCH)
      ? EDITOR_MODE_PATCH
      : EDITOR_MODE_SEQUENCE;
    JumpToPageGroup(last_visited_group_[editor_mode_]);
  } else if (id == SWITCH_LOAD_SAVE) {
    if (current_page_ >= PAGE_SYS_KBD && current_page_ <= PAGE_SYS_DISPLAY) {
      ConfirmPageSettings confirm_save_system_settings;
      confirm_save_system_settings.text = STR_RES_SAVE_MIDI_KBD;
      confirm_save_system_settings.return_group = GROUP_SYS;
      confirm_save_system_settings.callback = &SaveSystemSettings;
      Confirm(confirm_save_system_settings);
    } else {
      ToggleLoadSaveAction();
    }
  } else {
    if (editor_mode_ == EDITOR_MODE_SEQUENCE) {
      JumpToPageGroup(id + GROUP_SEQUENCER_ARPEGGIATOR);
    } else if (editor_mode_ == EDITOR_MODE_PATCH) {
      JumpToPageGroup(id + GROUP_OSC);
    }
  }
}

/* static */
void Editor::OnInput(uint8_t knob_index, uint8_t value) {
  if (knob_index < 4) {
    (*ui_handler_[page_definition_[current_page_].ui_type].input_handler)(
        knob_index, value);
  } else {
    OnEditInput(knob_index, value);
  }
}

/* static */
void Editor::OnIncrement(int8_t increment) {
  (*ui_handler_[page_definition_[current_page_].ui_type].increment_handler)(
      increment);
}

/* static */
void Editor::OnLongClick() {
  if (!part.latched()) {
    if (part.num_notes() == 0) {
      UpdateJamNote();
      jam_mode_previous_page_ = current_page_;
      display_mode_ = DISPLAY_MODE_OVERVIEW;
      current_page_ = PAGE_JAM;
    }
    part.Latch();
  } else {
    if (jam_note_ && current_page_ != PAGE_JAM) {
      display_mode_ = DISPLAY_MODE_OVERVIEW;
      current_page_ = PAGE_JAM;
    } else {
      part.Unlatch();
      if (jam_note_) {
        part.NoteOn(0, jam_note_, 0);
        jam_note_ = 0;
        if (current_page_ == PAGE_JAM) {
          current_page_ = jam_mode_previous_page_;
        }
      }
    }
  }
}

/* static */
void Editor::OnClick() {
  if (display_mode_ == DISPLAY_MODE_OVERVIEW) {
    display_mode_ = DISPLAY_MODE_EDIT;
    programmer_parameter_ = 0xff;
  } else {
    display_mode_ = DISPLAY_MODE_OVERVIEW;
  }
  if (ui_handler_[page_definition_[current_page_].ui_type].click_handler) {
    (*ui_handler_[page_definition_[current_page_].ui_type].click_handler)();
  }
}

/* static */
uint8_t Editor::OnNoteOn(uint8_t note, uint16_t velocity) {
  uint8_t handled = 0;
  if (current_page_ == PAGE_SEQ_TRACKER && display_mode_ == DISPLAY_MODE_EDIT) {
    part.mutable_sequencer_settings()->steps[cursor_].set_note(note);
    part.mutable_sequencer_settings()->steps[cursor_].set_velocity(velocity);
    ++cursor_;
    if (cursor_ >= part.sequencer_settings().pattern_size) {
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
void Editor::ScreenSaver() {
  memset(line_buffer_, ' ', kLcdWidth);
  display.Print(0, line_buffer_);
  display.Print(1, line_buffer_);
}

/* static */
void Editor::RestoreEditBuffer() {
  Storage::Restore(part.mutable_patch());
  part.Touch(true);
  Storage::Restore(part.mutable_sequencer_settings());
}

/* static */
void Editor::BackupEditBuffer() {
  Storage::Backup(part.mutable_patch());
  Storage::Backup(part.mutable_sequencer_settings());
}

/* static */
void Editor::ToggleLoadSaveAction() {
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
  display.set_cursor_position(kLcdNoCursor);
  display_mode_ = DISPLAY_MODE_OVERVIEW;
  current_page_ = PAGE_LOAD_SAVE;
}

/* static */
uint16_t Editor::edited_item_number() {
  return current_patch_number_;
}

const prog_uint8_t default_name[] PROGMEM = "user    ";

/* static */
void Editor::set_edited_item_number(int16_t value) {
  if (value >= static_cast<int16_t>(Storage::size<Patch>())) {
    value = 0;
  } else if (value < 0) {
    value = Storage::size<Patch>() - 1;
  }
  current_patch_number_ = value;
  
  uint8_t name[8];
  Storage::LoadPatchName(name, edited_item_number());
  empty_patch_ = true;
  for (uint8_t i = 0; i < 8; ++i) {
    if (name[i] != pgm_read_byte(default_name + i)) {
      empty_patch_ = false;
    }
  }
}

/* static */
uint8_t Editor::is_cursor_at_valid_position() {
  uint16_t allowed_cursor_positions = 0x0ff7;
  return ((1 << cursor_) & allowed_cursor_positions) != 0;
}

/* static */
void Editor::OnLoadSaveClick() {
  if (action_ == ACTION_LOAD) {
    action_ = ACTION_COMPARE;
    RestoreEditBuffer();
  } else if (action_ == ACTION_COMPARE) {
    action_ = ACTION_LOAD;
    OnLoadSaveIncrement(0);
  } else {
    if (!is_cursor_at_valid_position()) {
      display_mode_ = DISPLAY_MODE_OVERVIEW;
    }
    if (cursor_ >= kLcdWidth - 4) {
      Storage::WritePatch(edited_item_number());
      Storage::WriteSequence(edited_item_number());
      action_ = ACTION_LOAD;
    }
  }
}

/* static */
bool Editor::FinishLoadingPatch() {
  if (deferred_load_ == 0xffff) {
    return false;
  }
  uint16_t n = deferred_load_;
  Storage::LoadPatch(n);
  midi_dispatcher.OnProgramChange(n);
  part.Touch(true);
  if (part.system_settings().start_page == START_PAGE_LAST_PATCH) {
    part.mutable_system_settings()->last_patch = n;
    part.system_settings().EepromSave();
  }
  // When we are not playing, load the sequence parameters.
  if (!part.running()) {
    Storage::LoadSequence(edited_item_number());
  }
  // Reset the snap position of all pots.
  memset(snapped_, false, sizeof(snapped_));
  deferred_load_ = 0xffff;
  return true;
}

/* static */
void Editor::OnLoadSaveIncrement(int8_t increment) {
  if (action_ == ACTION_SAVE) {
    if (display_mode_ == DISPLAY_MODE_OVERVIEW) {
      int8_t new_cursor = static_cast<int8_t>(cursor_) + increment;
      if (new_cursor >= 0 && new_cursor < kLcdWidth) {
        cursor_ = new_cursor;
      }
    } else {
      if (cursor_ <= 2) {
        set_edited_item_number(edited_item_number() + increment);
      } else if (cursor_ >= 4 && cursor_ < 4 + kPatchNameSize) {
        uint8_t value = part.patch().name[cursor_ - 4];
        value += increment;
        if (value >= 32 && value <= 128) {
          part.mutable_patch()->name[cursor_ - 4] = value;
        }
      }
    }
  } else {
    set_edited_item_number(edited_item_number() + increment);
    if (action_ == ACTION_LOAD) {
      deferred_load_ = edited_item_number();
    }
  }
}

/* static */
void Editor::DisplayLoadSavePage() {
  if (display_mode_ == DISPLAY_MODE_EDIT_TEMPORARY
      && action_ != ACTION_SAVE
      && (part.system_settings().display_delay & 0xf)) {
    DisplayEditDetailsPage();
    return;
  }
  ResourcesManager::LoadStringResource(
      STR_RES_BROWSE + action_,
      line_buffer_,
      8);
  ResourcesManager::LoadStringResource(
      STR_RES_PATCH,
      line_buffer_ + 8,
      kLcdWidth - 8);
  AlignLeft(line_buffer_, 8);
  AlignLeft(line_buffer_ + 8, kLcdWidth - 8);
  line_buffer_[7] = ':';
  display.Print(0, line_buffer_);

  UnsafeItoa<int16_t>(edited_item_number() + 1, 3, line_buffer_);
  AlignRight(line_buffer_, 3);
  memcpy(line_buffer_ + 4, part.patch().name, kPatchNameSize);
  memset(
        line_buffer_ + 4 + kPatchNameSize,
        ' ',
        kLcdWidth - kPatchNameSize - 4);
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
  const SequencerSettings& seq = part.sequencer_settings();
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
  const SequencerSettings& seq = part.sequencer_settings();
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
void Editor::OnSequencerNavigation(uint8_t knob_index, uint8_t value) {
  switch (knob_index) {
    case 1:
      {
        cursor_ = value >> 3;
        uint8_t max_position = part.sequencer_settings().pattern_size - 1;
        if (cursor_ > max_position) {
          cursor_ = max_position;
        }
      }
      break;
    case 3:
      {
        uint8_t new_size = (value >> 3) + 1;
        if (cursor_ >= new_size) {
          cursor_ = new_size - 1;
        }
        last_knob_ = 1;
        part.SetParameter(57, PRM_SEQ_PATTERN_SIZE, new_size, true);
      }
      break;
  }
}

/* static */
void Editor::OnStepSequencerInput(uint8_t knob_index, uint8_t value) {
  OnSequencerNavigation(knob_index, value);
  if (knob_index == 2) {
    SequencerSettings* seq = part.mutable_sequencer_settings();
    seq->steps[(cursor_ + seq->pattern_rotation) & 0x0f].set_controller(
        value >> 3);
  } else if (knob_index == 0) {
    part.SetParameter(56, PRM_SEQ_PATTERN_ROTATION, value >> 3, true);
    last_knob_ = 0;
  }
}

/* static */
void Editor::OnStepSequencerIncrement(int8_t increment) {
  if (display_mode_ == DISPLAY_MODE_OVERVIEW) {
    MoveSequencerCursor(increment);
  } else {
    SequencerSettings* seq = part.mutable_sequencer_settings();
    uint8_t position = (cursor_ + seq->pattern_rotation) & 0x0f;
    seq->steps[position].set_controller(
        seq->steps[position].controller() + \
        increment);
  }
}

/* static */
void Editor::DisplayTrackerPage() {
  memset(line_buffer_, ' ', kLcdWidth);
  if (cursor_ > part.sequencer_settings().pattern_size - 1) {
    cursor_ = part.sequencer_settings().pattern_size - 1;
  }
  if (cursor_ > 0) {
    part.sequencer_settings().PrintStep(cursor_ - 1, line_buffer_);
  } else {
    // This is an invisible character. It is just there to prevent the status
    // indicator to be printed on the last column instead of the first.
    line_buffer_[kLcdWidth - 1] = 0xfe;
  }
  display.Print(0, line_buffer_);

  part.sequencer_settings().PrintStep(cursor_, line_buffer_);
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
void Editor::OnTrackerInput(uint8_t knob_index, uint8_t value) {
  uint16_t value_16_bits = 0;
  switch (knob_index) {
    case 0:
      {
        cursor_ = value >> 3;
        uint8_t max_position = part.sequencer_settings().pattern_size - 1;
        if (cursor_ > max_position) {
          cursor_ = max_position;
        }
      }
      break;
    case 1:
      part.mutable_sequencer_settings()->steps[cursor_].set_note(
          24 + (value >> 1));
      break;
    case 2:
      value_16_bits = value << 3;
      value_16_bits *= 10;
      value_16_bits >>= 5;
      if (value_16_bits < 64) {
        part.mutable_sequencer_settings()->steps[cursor_].set_velocity(0);
        part.mutable_sequencer_settings()->steps[cursor_].set_gate(0);
        part.mutable_sequencer_settings()->steps[cursor_].set_legato(0);
      } else {
        value_16_bits -= 64;
        part.mutable_sequencer_settings()->steps[cursor_].set_velocity(
            value_16_bits);
        part.mutable_sequencer_settings()->steps[cursor_].set_gate(1);
        part.mutable_sequencer_settings()->steps[cursor_].set_legato(
            value_16_bits >= 0x80);
      }
      break;
    case 3:
      part.mutable_sequencer_settings()->steps[cursor_].set_controller(
          value >> 3);
      break;
  }
}

/* static */
void Editor::OnTrackerIncrement(int8_t increment) {
  if (display_mode_ == DISPLAY_MODE_OVERVIEW) {
    MoveSequencerCursor(increment);
  } else {
    int8_t note = part.mutable_sequencer_settings()->steps[cursor_].note();
    note += increment;
    if (note >= 12 && note < 108) {
      part.mutable_sequencer_settings()->steps[cursor_].set_note(note);
    }
  }
}

/* static */
void Editor::DisplayPageRPage() {
  if (cursor_ > part.sequencer_settings().pattern_size - 1) {
    cursor_ = part.sequencer_settings().pattern_size - 1;
  }
  memset(line_buffer_, ' ', kLcdWidth);
  memset(line_buffer_, ' ', kLcdWidth);
  for (uint8_t i = 0; i < part.sequencer_settings().pattern_size; ++i) {
    line_buffer_[i] = part.mutable_sequencer_settings()->steps[i].character();
  }
  if (part.sequencer_settings().pattern_size != kLcdWidth) {
    line_buffer_[part.sequencer_settings().pattern_size] = '|';
  }
  display.Print(0, line_buffer_);

  for (uint8_t i = 0; i < part.sequencer_settings().pattern_size; ++i) {
    if (part.mutable_sequencer_settings()->steps[i].gate()) {
      line_buffer_[i] = NibbleToAscii(
          part.mutable_sequencer_settings()->steps[i].velocity() >> 4);
    }
  }
  if (part.sequencer_settings().pattern_size != kLcdWidth) {
    line_buffer_[part.sequencer_settings().pattern_size] = '|';
  }
  display.Print(1, line_buffer_);
  ShowEditCursor();
}

/* static */
void Editor::OnPageRInput(
    uint8_t knob_index,
    uint8_t value) {
  OnSequencerNavigation(knob_index, value);
  if (knob_index == 2) {
    OnTrackerInput(2, value);
  }
}

/* static */
void Editor::OnPageRIncrement(int8_t increment) {
  if (display_mode_ == DISPLAY_MODE_OVERVIEW) {
    MoveSequencerCursor(increment);
  } else {
    int8_t flags = part.mutable_sequencer_settings()->steps[cursor_].flags();
    flags += increment;
    if (flags >= 0 && flags <= 16) {
      part.mutable_sequencer_settings()->steps[cursor_].set_flags(flags);
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
  uint8_t previous = 0xff;
  for (uint8_t i = 0; i < kNumEditingPots; ++i) {
    uint8_t index = KnobIndexToParameterId(i);
    const Parameter& parameter = parameter_manager.parameter(index);
    uint8_t caption_position = i * kColumnWidth;
    uint8_t text_position = i * kColumnWidth + kLcdWidth + 1;
    if (parameter.offset == previous) {
      memset(line_buffer_ + caption_position, ' ', kColumnWidth);
      memset(line_buffer_ + text_position, ' ', kColumnWidth);
    } else {
      ResourcesManager::LoadStringResource(
          parameter.short_name,
          line_buffer_ + caption_position,
          kColumnWidth - 1);
      line_buffer_[caption_position + kColumnWidth - 1] = '\0';
      line_buffer_[text_position + kColumnWidth - 1] = '\0';
      AlignRight(line_buffer_ + caption_position, kColumnWidth);
      uint8_t value = GetParameterValue(parameter.offset);
      parameter.PrintValue(value, line_buffer_ + text_position, kColumnWidth - 1);
      AlignRight(line_buffer_ + text_position, kColumnWidth);
    }
    previous = parameter.offset;
  }

  // Change the case of the current parameter accessible by the rotary encoder.
  uint8_t pos = cursor_ * kColumnWidth + 1;
  if (line_buffer_[pos] > 96 && line_buffer_[pos] <= 122) {
    line_buffer_[pos] -= 32;
  }
  
  // If we are in latched mode, show it.
  if (part.latched()) {
    for (uint8_t i = 1; i < kLcdWidth; ++i) {
      if (line_buffer_[i] == ' ') {
        line_buffer_[i] = '-';
      }
    }
  }

  display.Print(0, line_buffer_);
  display.Print(1, line_buffer_ + kLcdWidth + 1);
}

/* static */
void Editor::DisplayEditDetailsPage() {
  if ((part.system_settings().display_delay & 0xf) == 0) {
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
  if (current_page_ == PAGE_MOD_MATRIX && programmer_parameter_ == 0xff) {
    const Parameter& current_source = parameter_manager.parameter(
            page_definition_[PAGE_MOD_MATRIX].first_parameter_index + 1);
    uint8_t value = GetParameterValue(current_source.offset);
    current_source.PrintValue(value, line_buffer_ + 4, kColumnWidth - 1);
    const Parameter& current_destination = parameter_manager.parameter(
          page_definition_[PAGE_MOD_MATRIX].first_parameter_index + 2);
    value = GetParameterValue(current_destination.offset);
    current_destination.PrintValue(value, line_buffer_ + kColumnWidth + 4, kColumnWidth);
    line_buffer_[0] = 'm';
    line_buffer_[1] = 'o';
    line_buffer_[2] = 'd';
    line_buffer_[3] = ' ';
    line_buffer_[kColumnWidth + 3] = '>';
    AlignLeft(line_buffer_ + kColumnWidth + 4, kLcdWidth - kColumnWidth - 4);
    display.Print(0, line_buffer_);
  }
  uint8_t index = KnobIndexToParameterId(cursor_);
  if (programmer_parameter_ != 0xff) {
    index = programmer_parameter_;
  }
  const Parameter& parameter = parameter_manager.parameter(index);
  uint8_t page_index = current_page_;
  
  if (programmer_parameter_ != 0xff) {
    page_index = programmer_parameter_ >> 2;
    if (page_index >= PAGE_FILTER_MULTIMODE) {
      ++page_index;
    }
  }
  const PageDefinition& page = page_definition_[page_index];
  if (current_page_ != PAGE_MOD_MATRIX || programmer_parameter_ != 0xff) {
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
  
  uint8_t value = GetParameterValue(parameter.offset);
  parameter.PrintValue(value, line_buffer_ + kCaptionWidth, kValueWidth);
  AlignRight(line_buffer_ + kCaptionWidth, kValueWidth);
  display.Print(1, line_buffer_);
}

/* static */
uint8_t Editor::KnobIndexToParameterId(uint8_t knob_index) {
  if (current_page_ == PAGE_LOAD_SAVE
      && (action_ == ACTION_SAVE || action_ == ACTION_COMPARE)) {
    return 0xff;
  }
  if (current_page_ == PAGE_LOAD_SAVE) {
    switch (knob_index) {
      case 0:
        return PRM_OSC_PARAMETER_1;
      case 1:
        return PRM_FILTER_CUTOFF;
      case 2:
        return PRM_FILTER_RESONANCE;
      case 3:
        return PRM_FILTER_ENV;
    }
    subpage_ = 0;
  } else {
    return page_definition_[current_page_].first_parameter_index + \
        knob_index;
  }
}

/* static */
void Editor::OnEditInput(uint8_t knob_index, uint8_t value) {
  uint8_t index;
  if (knob_index < 4) {
    index = KnobIndexToParameterId(knob_index);
    if (index == 0xff) {
      return;
    }
    programmer_parameter_ = 0xff;
    cursor_ = knob_index;
  } else {
    index = knob_index - 4;
    programmer_parameter_ = index;
  }
  const Parameter& parameter = parameter_manager.parameter(index);
  
  if (part.system_settings().display_snap) {
    if (!snapped_[knob_index]) {
      uint8_t current_value = GetParameterValue(parameter.offset);
      if (parameter.is_snapped(current_value, value)) {
        snapped_[knob_index] = true;
      } else {
        return;
      }
    }
  }
  display_mode_ = DISPLAY_MODE_EDIT_TEMPORARY;
  SetParameterValue(index, parameter.offset, parameter.Scale(value));
}

/* static */
void Editor::OnVolume(uint8_t value) {
  if (value >= 120) {
    part.mutable_voice()->set_volume(255);
  } else {
    part.mutable_voice()->set_volume(16 + (value << 1));
  }
}

/* static */
void Editor::OnEditIncrement(int8_t increment) {
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
    uint8_t parameter_index = programmer_parameter_ != 0xff
        ? programmer_parameter_
        : KnobIndexToParameterId(cursor_);
    IncrementParameterValue(parameter_index, increment);
  }
}

/* static */
void Editor::IncrementParameterValue(uint8_t index, int8_t increment) {
  const Parameter& parameter = parameter_manager.parameter(index);
  uint8_t old_value = GetParameterValue(parameter.offset);
  uint8_t new_value = parameter.Increment(old_value, increment);
  if (new_value != old_value) {
    SetParameterValue(index, parameter.offset, new_value);
  }
}

const prog_uint8_t modulation_destination_map[] PROGMEM = {
  MOD_DST_PWM_1,
  MOD_DST_PWM_2,
  MOD_DST_VCO_1,
  MOD_DST_VCO_2,
  MOD_DST_VCO_1_2_COARSE,
  MOD_DST_VCO_1_2_FINE,
  MOD_DST_MIX_BALANCE,
  MOD_DST_MIX_NOISE,
  MOD_DST_MIX_SUB_OSC,
  MOD_DST_FILTER_CUTOFF,
  MOD_DST_FILTER_RESONANCE,
  MOD_DST_VCA,
  MOD_DST_CV_1,
  MOD_DST_CV_2,
  MOD_DST_TRIGGER_ENV_1,
  MOD_DST_ATTACK_1,
  MOD_DST_DECAY_1,
  MOD_DST_SUSTAIN_1,
  MOD_DST_RELEASE_1,
  MOD_DST_TRIGGER_ENV_2,
  MOD_DST_ATTACK_2,
  MOD_DST_DECAY_2,
  MOD_DST_SUSTAIN_2,
  MOD_DST_RELEASE_2,
  MOD_DST_ATTACK,
  MOD_DST_LFO_1,
  MOD_DST_LFO_2,
};

/* static */
void Editor::SetParameterValue(
    uint8_t index,
    uint8_t offset,
    uint8_t value) {
  // Dirty hack for the modulation page.
  if (current_page_ == PAGE_MOD_MATRIX && offset == PRM_MOD_ROW) {
    subpage_ = value;
    last_visited_subpage_ = value;
  } else if (current_page_ == PAGE_MOD_OPERATORS && offset == PRM_OP_ROW ) {
    subpage_ = value;
  } else {
    if (offset == PRM_MOD_DESTINATION) {
      value = pgm_read_byte(modulation_destination_map + value);
    }
    if ((offset >= PRM_OP_OP1 && offset <= PRM_OP_OPERATOR) ||
        (offset >= PRM_MOD_SOURCE && offset <= PRM_MOD_AMOUNT)) {
      offset += subpage_ * 3;
    }
    part.SetParameter(index, offset, value, true);
  }
}

/* static */
uint8_t Editor::GetParameterValue(uint8_t offset) {
  uint8_t value;
  if (current_page_ == PAGE_MOD_MATRIX && offset == PRM_MOD_ROW) {
    value = subpage_;
  } else if (current_page_ == PAGE_MOD_OPERATORS && offset == PRM_OP_ROW ) {
    value = subpage_;
  } else {
    uint8_t actual_offset = offset;
    if ((actual_offset >= PRM_OP_OP1 && actual_offset <= PRM_OP_OPERATOR) ||
        (actual_offset >= PRM_MOD_SOURCE && actual_offset <= PRM_MOD_AMOUNT)) {
      actual_offset += subpage_ * 3;
    }
    value = part.GetParameter(actual_offset);
    if (offset == PRM_MOD_DESTINATION) {
      for (uint8_t i = 0; i < MOD_DST_LAST; ++i) {
        if (pgm_read_byte(modulation_destination_map + i) == value) {
          value = i;
          break;
        }
      }
    }
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
void Editor::OnConfirmClick() {
  if (cursor_) {
    (*confirm_page_settings_.callback)();
  }
  JumpToPageGroup(confirm_page_settings_.return_group);
  Refresh();
}

/* static */
void Editor::OnConfirmIncrement(int8_t increment) {
  cursor_ = !cursor_;
}

/* static */
void Editor::OnConfirmInput(uint8_t knob_index, uint8_t value) {
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
void Editor::DisplayJamPage() {
  ResourcesManager::LoadStringResource(
      STR_RES_LETS_JAM_,
      line_buffer_,
      kLcdWidth);
  AlignLeft(line_buffer_, kLcdWidth);
  display.Print(0, line_buffer_);
  line_buffer_[0] = 'r';
  line_buffer_[1] = 'o';
  line_buffer_[2] = 'o';
  line_buffer_[3] = 't';
  line_buffer_[4] = ' ';
  SequencerSettings::PrintNote(jam_note_, &line_buffer_[5]);
  line_buffer_[8] = '\0';
  AlignLeft(line_buffer_, kLcdWidth);
  display.Print(1, line_buffer_);
}


const prog_uint8_t octave_shift[] PROGMEM = {
  -24, -12, 0, 12, 24
};

const prog_uint8_t pentatonic_shift[] PROGMEM = {
  -12, -10, -8, -5, -3, 0, 2, 4, 7, 9, 12
};

const prog_uint8_t bhairav_shift[] PROGMEM = {
  -12, -11, -8, -7, -5, -4, -1, 0, 1, 4, 5, 7, 8, 11, 12
};

const prog_uint8_t chromatic_shift[] PROGMEM = {
  -12, -5 , -2, -1, 0, 1, 2, 7, 12
};

const prog_uint8_t ranges[] PROGMEM = {
  5,
  sizeof(pentatonic_shift),
  sizeof(bhairav_shift),
  sizeof(chromatic_shift)
};

void Editor::OnJamPageInput(uint8_t knob_index, uint8_t value) {
  value = U8U8MulShift8(pgm_read_byte(ranges + knob_index), value << 1);
  jam_mode_shifts_[knob_index] = value;
  UpdateJamNote();
}

void Editor::UpdateJamNote() {
  int16_t note = jam_note_root_;
  note += static_cast<int8_t>(pgm_read_byte(octave_shift + jam_mode_shifts_[0]));
  note += static_cast<int8_t>(pgm_read_byte(pentatonic_shift + jam_mode_shifts_[1]));
  note += static_cast<int8_t>(pgm_read_byte(bhairav_shift + jam_mode_shifts_[2]));
  note += static_cast<int8_t>(pgm_read_byte(chromatic_shift + jam_mode_shifts_[3]));
  while (note < 12) {
    note += 12;
  }
  while (note > 96) {
    note -= 12;
  }
  if (note != jam_note_) {
    if (jam_note_) {
      part.NoteOn(0, jam_note_, 0);
    }
    part.NoteOn(0, note, 100);
    jam_note_ = note;
  }
}

void Editor::OnJamPageIncrement(int8_t increment) {
  int16_t new_root = jam_note_root_ + increment;
  if (new_root < 0) {
    new_root = 0;
  } else if (new_root > 127) {
    new_root = 127;
  }
  jam_note_root_ = new_root;
  UpdateJamNote();
}

void Editor::OnJamPageClick() {
  OnLongClick();
}

/* static */
void Editor::BootOnPatchBrowsePage(uint16_t index) {
  if (index >= Storage::size<Patch>()) {
    index = Storage::size<Patch>() - 1;
  } 
  current_patch_number_ = index;
  current_page_ = 0;
  ToggleLoadSaveAction();
  OnLoadSaveIncrement(0);
  Refresh();
}

}  // namespace shruthi
