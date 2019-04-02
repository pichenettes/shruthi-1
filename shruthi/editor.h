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
// Parameter editor.

#ifndef SHRUTHI_EDITOR_H_
#define SHRUTHI_EDITOR_H_

#include "avrlib/base.h"
#include "shruthi/patch.h"
#include "shruthi/resources.h"
#include "shruthi/shruthi.h"

namespace avrlib {
  class Event;
}

namespace shruthi {

class ParameterDefinition;

// These 3 modes determine within which group of pages the switches navigate.
enum EditorMode {
  EDITOR_MODE_PATCH,
  EDITOR_MODE_SEQUENCE,
};

enum LoadSaveTarget {
  LOAD_SAVE_TARGET_PATCH = 1,
  LOAD_SAVE_TARGET_SEQUENCE = 2,
  LOAD_SAVE_TARGET_BOTH = 3
};

enum DisplayMode {
  // Show the parameter names.
  DISPLAY_MODE_OVERVIEW = 0,
  // Show a single parameter without pesky acronyms.
  DISPLAY_MODE_EDIT = 1,
  // Show a single parameter without pesky acronyms, and revert to overview
  // mode after a while
  DISPLAY_MODE_EDIT_TEMPORARY = 2,
};

enum Group {
  GROUP_OSC,
  GROUP_FILTER,
  GROUP_MOD_SOURCES,
  GROUP_MOD_MATRIX,
  
  GROUP_SEQUENCER_ARPEGGIATOR,
  GROUP_SEQUENCER_TRACKER,
  GROUP_SEQUENCER_STEPS,
  GROUP_SYS,

  GROUP_LOAD_SAVE,
  GROUP_CONFIRM,
  
  GROUP_JAM,
  GROUP_LAST
};

enum Page {
  PAGE_OSC_OSC_1,
  PAGE_OSC_OSC_2,
  PAGE_OSC_OSC_MIX,
  PAGE_FILTER_FILTER,
  PAGE_FILTER_MULTIMODE,
  PAGE_MOD_ENV_1,
  PAGE_MOD_ENV_2,
  PAGE_MOD_LFO_1,
  PAGE_MOD_LFO_2,
  PAGE_MOD_MATRIX,
  PAGE_MOD_OPERATORS,
  
  PAGE_SEQ_SEQUENCER,
  PAGE_SEQ_ARPEGGIATOR,
  PAGE_SEQ_TRACKER,
  PAGE_SEQ_RHYTHM,
  PAGE_SEQ_CONTROLLER,
  
  PAGE_SYS_KBD,
  PAGE_SYS_MIDI,
  PAGE_SYS_DISPLAY,
  
  PAGE_LOAD_SAVE,
  PAGE_CONFIRM,
  PAGE_JAM
};

enum Action {
  ACTION_LOAD,
  ACTION_SAVE,
  ACTION_COMPARE,
};

// We do not use enums here because they take 2 bytes, not 1.
typedef uint8_t ParameterGroup;
typedef uint8_t ParameterPage;

// Size (in char) of the display elements.
static const uint8_t kCaptionWidth = 10;
static const uint8_t kValueWidth = 6;
static const uint8_t kColumnWidth = 4;

enum PageUiType {
  PARAMETER_EDITOR,
  TRACKER_EDITOR,
  PAGE_R_EDITOR,
  STEP_SEQUENCER,
  LOAD_SAVE,
  CONFIRM,
  JAM,
};

struct PageDefinition {
  ParameterPage next;
  ParameterGroup group;

  // Previous and next page when cycling with encoder.
  ParameterPage overall_previous;
  ParameterPage overall_next;

  ResourceId name;
  uint8_t ui_type;
  uint8_t first_parameter_index;
  uint8_t leds_pattern;
};

// For each type of page (basic parameter editor, step sequencer, load/save
// dialog, 4 functions must be defined:
// - a function displaying the "overview" page.
// - a function displaying a specific parameter value ("details").
// - a function handling a change in one of the 4 editing pots.
// - a function handling presses on the increment/decrement buttons.
struct UiHandler {
  void (*overview_page)();
  void (*edit_page)();
  void (*input_handler)(uint8_t knob_index, uint8_t value);
  void (*increment_handler)(int8_t increment);
  void (*click_handler)();
};

struct ConfirmPageSettings {
  ResourceId text;
  ParameterPage return_group;
  void (*callback)();
};

class Editor {
 public:
  Editor() { }
  static void Init();

  // Ons a press on a switch.
  static void OnSwitch(const avrlib::Event& event);

  // Ons the modification of one of the editing pots.
  static void OnInput(uint8_t knob_index, uint8_t value);

  // Ons a rotation of the encoder.
  static void OnIncrement(int8_t increment);

  // Ons a click on the encoder.
  static void OnClick();
  // Ons a long click on the encoder.
  static void OnLongClick();
  
  // The editor can react to a note on. This is used for step-by-step
  // pattern programming. This function returns true when the note has been
  // recorded in the sequence. In this case, it is not processed!
  static uint8_t OnNoteOn(uint8_t note, uint16_t velocity);

  static void OnProgrammerSwitch(const avrlib::Event& event);
  static void OnVolume(uint8_t value);

  // Displays variants of the current page.
  static void Refresh();
  static void ScreenSaver();
  
  // Notify the editor that the user has not provided any input for 2s.
  static bool Relax();
  
  // Displays two lines of text read from a resource.
  static void DisplaySplashScreen(ResourceId first_line);
  // Displays the programmer initialization screen.
  static void DisplayProgrammerSetting(uint8_t programmer);

  static inline ParameterPage current_page() { return current_page_; }
  static inline uint8_t current_mode() { return editor_mode_; }
  static inline uint8_t leds_pattern() {
    return page_definition_[current_page_].leds_pattern;
  }
  static inline uint8_t cursor() { return cursor_; }
  static inline uint8_t subpage() { return subpage_; }
  
  static void Confirm(ConfirmPageSettings confirm_page_settings);

  static void BootOnPatchBrowsePage(uint16_t patch_index);
  
  static void RandomizeParameter(uint8_t subpage, uint8_t parameter_index);
  static void RandomizePatch();
  static void RandomizeSequence();

  static inline uint16_t current_patch_number() {
    return current_patch_number_;
  }
  
  static inline void set_current_patch_number(uint16_t patch_number) {
    current_patch_number_ = patch_number;
  }
  
  static bool FinishLoadingPatch();
  
 private:
  // This hides or shows the second filter page, with settings for
  // upcoming multimode filters.
  static void ConfigureFilterMenu();
   
  // A bunch of hacks for special values/pages.
  static void SetParameterValue(uint8_t id, uint8_t offset, uint8_t value);
  static void IncrementParameterValue(uint8_t id, int8_t increment);
  static uint8_t GetParameterValue(uint8_t offset);

  // Returns the parameter id of the parameter that should be edited when
  // touching knob #knob_index.
  static uint8_t KnobIndexToParameterId(uint8_t knob_index);

  static void JumpToPageGroup(uint8_t id);
  static void PageChange();
  static void ShowEditCursor();

  // Output and Input handling for all the different category of pages.
  static void DisplayEditOverviewPage();
  static void DisplayEditDetailsPage();
  
  static void OnEditInput(uint8_t knob_index, uint8_t value);
  static void OnEditIncrement(int8_t increment);

  static void MoveSequencerCursor(int8_t increment);
  static void OnSequencerNavigation(uint8_t knob, uint8_t value);
  
  static void DisplayTrackerPage();
  static void OnTrackerInput(uint8_t knob_index, uint8_t value);
  static void OnTrackerIncrement(int8_t increment);

  static void DisplayPageRPage();
  static void OnPageRInput(uint8_t knob_index, uint8_t value);
  static void OnPageRIncrement(int8_t increment);

  static void DisplayStepSequencerPage();
  static void OnStepSequencerInput(uint8_t knob_index, uint8_t value);
  static void OnStepSequencerIncrement(int8_t increment);
  
  static void DisplayConfirmPage();
  static void OnConfirmInput(uint8_t knob_index, uint8_t value);
  static void OnConfirmIncrement(int8_t increment);
  static void OnConfirmClick();

  static void DisplayLoadSavePage();
  static void ToggleLoadSaveAction();
  static void OnLoadSaveIncrement(int8_t increment);
  static void OnLoadSaveClick();

  static void DisplayJamPage();
  static void OnJamPageInput(uint8_t knob_index, uint8_t value);
  static void OnJamPageIncrement(int8_t increment);
  static void OnJamPageClick();
  
  static void BackupEditBuffer();
  static void RestoreEditBuffer();
  static uint16_t edited_item_number();
  static void set_edited_item_number(int16_t value);
  static uint8_t is_cursor_at_valid_position();
  
  static void LoadPatch(uint8_t index);
  static void LoadSequence(uint8_t index);
  
  static void SaveSystemSettings();
  static void StartMidiBackup();
  
  static void UpdateJamNote();
  
  static PageDefinition page_definition_[];
  static const UiHandler ui_handler_[];

  static ParameterPage current_page_;
  static ParameterPage last_visited_page_[GROUP_LAST];
  
  static uint8_t last_visited_group_[2];
  static uint8_t display_mode_;
  static uint8_t editor_mode_;
  static uint8_t cursor_;
  static uint8_t programmer_parameter_;
  static uint8_t last_knob_;
  static uint8_t last_visited_subpage_;

  static char line_buffer_[kLcdWidth * kLcdHeight + 1];

  static uint8_t subpage_;
  static uint8_t action_;
  static uint16_t current_patch_number_;
  static uint16_t current_sequence_number_;
  static ConfirmPageSettings confirm_page_settings_;

  static bool empty_patch_;

  static int8_t jam_note_;
  static int8_t jam_note_root_;
  static uint8_t jam_mode_previous_page_;
  static int8_t jam_mode_shifts_[4];
  
  static bool snapped_[36];
  
  static uint16_t deferred_load_;

  DISALLOW_COPY_AND_ASSIGN(Editor);
};

extern Editor editor;

}  // namespace shruthi

#endif // SHRUTHI_EDITOR_H_
