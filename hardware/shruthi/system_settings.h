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

#ifndef HARDWARE_SHRUTHI_SYSTEM_SETTINGS_H_
#define HARDWARE_SHRUTHI_SYSTEM_SETTINGS_H_

#include "hardware/base/base.h"
#include "hardware/shruthi/patch.h"
#include "hardware/shruthi/sequencer_settings.h"

namespace hardware_shruthi {

class SystemSettings {
 public:
  int8_t octave;
  uint8_t raga;
  uint8_t portamento;
  uint8_t legato;

  int8_t master_tuning;
  uint8_t midi_channel;
  uint8_t midi_out_mode;
  uint8_t midi_split_point;
  
  uint8_t display_delay;
  uint8_t expansion_filter_board;
  uint8_t expansion_cv_mode;
  uint8_t display_snap;

  uint8_t padding[2];
  uint8_t patch_restore_on_boot;

  void EepromSave() const;
  uint8_t EepromLoad();
};

enum FilterBoard {
  FILTER_BOARD_LPF,
  FILTER_BOARD_SSM,
  FILTER_BOARD_SVF,
};

enum CvMode {
  CV_MODE_4CV_IN,
  CV_MODE_PROGRAMMER,
  CV_MODE_PEDALS
};

enum MidiOutMode {
  MIDI_OUT_OFF,
  MIDI_OUT_SOFT_THRU,
  MIDI_OUT_SEQUENCER,
  MIDI_OUT_CTRL,
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

enum SystemParameter {
  PRM_SYS_OCTAVE = sizeof(Patch) + sizeof(SequencerSettings),
  PRM_SYS_RAGA,
  PRM_SYS_PORTAMENTO,
  PRM_SYS_LEGATO,

  PRM_SYS_MASTER_TUNING,
  PRM_SYS_MIDI_CHANNEL,
  PRM_SYS_MIDI_OUT_MODE,
  PRM_SYS_MIDI_SPLIT_POINT,
  
  PRM_SYS_DISPLAY_DELAY,
  PRM_SYS_EXPANSION_FILTER_BOARD,
  PRM_SYS_EXPANSION_CV_MODE,
  PRM_SYS_DISPLAY_SNAP
};

}  // namespace hardware_shruthi

#endif  // HARDWARE_SHRUTHI_SYSTEM_SETTINGS_H_
