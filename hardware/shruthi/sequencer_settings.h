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

#ifndef HARDWARE_SHRUTHI_SYSTEM_SEQUENCER_SETTINGS_H_
#define HARDWARE_SHRUTHI_SYSTEM_SEQUENCER_SETTINGS_H_

#include "hardware/base/base.h"
#include "hardware/shruthi/patch.h"

namespace hardware_shruthi {

const uint8_t kSequenceBankSize = 16;

enum SequencerMode {
  SEQUENCER_MODE_STEP,
  SEQUENCER_MODE_ARP,
  SEQUENCER_MODE_ARP_LATCH,
  SEQUENCER_MODE_RPS,
  SEQUENCER_MODE_RPS_LATCH,
  SEQUENCER_MODE_IMPROVISATION,
};

enum ArpeggioVelocitySource {
  ARPEGGIO_VELOCITY_SOURCE_KEYBOARD,
  ARPEGGIO_VELOCITY_SOURCE_SEQUENCE
};

enum Flow {
  FLOW_NORMAL,
  FLOW_REVERSE,
  FLOW_BACK_FORTH_1,
  FLOW_BACK_FORTH_2,
  
  FLOW_KRAMA,
  FLOW_JATA,
  FLOW_SIKHA,
  FLOW_GHANA,

  FLOW_KRAMA_2,
  FLOW_JATA_2,
  FLOW_SIKHA_2,
  FLOW_GHANA_2,

  FLOW_KRAMA_4,
  FLOW_JATA_4,
  FLOW_SIKHA_4,
  FLOW_GHANA_4,
};

enum ArpeggioDirection {
  ARPEGGIO_DIRECTION_UP = 0,
  ARPEGGIO_DIRECTION_DOWN,
  ARPEGGIO_DIRECTION_UP_DOWN,
  ARPEGGIO_DIRECTION_RANDOM,
};

class SequenceStep {
 public:
  void set_gate(uint8_t gate) {
    if (gate) {
      data_[0] |= 0x80;
    } else {
      data_[0] &= ~0x80;
    }
  }
  void set_note(uint8_t note) {
    data_[0] = (data_[0] & 0x80) | (note & 0x7f);
  } 
  void set_legato(uint8_t legato) {
    if (legato) {
      data_[1] |= 0x80;
    } else {
      data_[1] &= ~0x80;
    }
  }
  void set_velocity(uint8_t velocity) {
    data_[1] = (data_[1] & 0x8f) | (velocity & 0x70);
  }
  void set_controller(uint8_t controller) {
    data_[1] = (data_[1] & 0xf0) | (controller & 0x0f);
  }
  void set_flags(uint8_t flags) {
    if (flags == 0) {
      set_gate(0);
      set_legato(0);
      set_velocity(0);
    } else {
      --flags;
      set_gate(1);
      set_velocity(flags << 4);
      if (flags >= 8) {
        set_legato(1);
      } else {
        set_legato(0);
      }
    }
  }
  
  uint8_t gate() const {
    return data_[0] & 0x80;
  }
  uint8_t note() const {
    return data_[0] & 0x7f;
  }
  uint8_t legato() const {
    return data_[1] & 0x80;
  }
  uint8_t velocity() const {
    return data_[1] & 0x70;
  }
  uint8_t controller() const {
    return data_[1] & 0x0f;
  }
  uint8_t flags() const {
    uint8_t flags = 0;
    if (gate()) {
      ++flags;
      flags += velocity() >> 4;
      if (legato()) {
        flags += 8;
      }
    }
    return flags;
  }
  char character() const {
    return gate() ? (legato() ? '-' : '\x01') : ' ';
  }
  
  void clear() {
    data_[0] = 0;
    data_[1] = 0;
  }
  uint8_t blank() {
    return (data_[0] == 0) && (data_[1] == 0);
  }

 private:
  uint8_t data_[2];
};

static const uint8_t kNumSteps = 16;

struct SequencerSettings {
 public:
  uint8_t seq_mode;
  uint8_t seq_tempo;
  uint8_t seq_swing;
  uint8_t seq_flow;
  
  uint8_t arp_direction;
  uint8_t arp_range;
  uint8_t arp_pattern;
  uint8_t arp_velocity_source;
  
  uint8_t pattern_size;
  SequenceStep steps[kNumSteps];
  
  
  void EepromSave(uint8_t slot);
  void EepromLoad(uint8_t slot);
  void Backup() const;
  void Restore();
  void PrintStep(uint8_t step, char* buffer) const;
  
 private:
  static uint8_t undo_buffer_[sizeof(SequenceStep) * kNumSteps];
};

static const uint8_t kSequenceSize = sizeof(SequenceStep) * kNumSteps;

enum SequencerParameter {
  PRM_SEQ_MODE = sizeof(Patch),
  PRM_SEQ_TEMPO,
  PRM_SEQ_SWING,
  PRM_SEQ_FLOW,

  PRM_ARP_DIRECTION,
  PRM_ARP_RANGE,
  PRM_ARP_PATTERN,
  PRM_ARP_VELOCITY_SOURCE,
  
  PRM_SEQ_PATTERN_SIZE,
};

static const uint8_t kNumArpeggiatorPatterns = 15;

}  // namespace hardware_shruthi

#endif  // HARDWARE_SHRUTHI_SYSTEM_SEQUENCER_SETTINGS_H_
