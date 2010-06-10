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
  uint8_t midi_blank;
  
  uint8_t display_delay;
  uint8_t display_delimiter;
  uint8_t display_splash_screen;
  uint8_t display_blank_2;

  void EepromSave() const;
  uint8_t EepromLoad();
};

enum SystemParameter {
  PRM_SYS_OCTAVE = sizeof(Patch) + sizeof(SequencerSettings),
  PRM_SYS_RAGA,
  PRM_SYS_PORTAMENTO,
  PRM_SYS_LEGATO,

  PRM_SYS_MASTER_TUNING,
  PRM_SYS_MIDI_CHANNEL,
  PRM_SYS_MIDI_OUT_MODE,
  PRM_SYS_MIDI_BLANK,
  
  PRM_SYS_DISPLAY_DELAY,
  PRM_SYS_DISPLAY_DELIMITER,
  PRM_SYS_DISPLAY_SHOW_SPLASH_SCREEN,
  PRM_SYS_DISPLAY_BLANK
};

}  // namespace hardware_shruthi

#endif  // HARDWARE_SHRUTHI_SYSTEM_SETTINGS_H_
