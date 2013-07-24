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

#ifndef SHRUTHI_SYSTEM_SEQUENCER_SETTINGS_H_
#define SHRUTHI_SYSTEM_SEQUENCER_SETTINGS_H_

#include "avrlib/base.h"
#include "shruthi/patch.h"

namespace shruthi {

enum SequencerMode {
  SEQUENCER_MODE_STEP,
  SEQUENCER_MODE_ARP,
  SEQUENCER_MODE_SEQ
};

enum ArpeggioDirection {
  ARPEGGIO_DIRECTION_UP = 0,
  ARPEGGIO_DIRECTION_DOWN,
  ARPEGGIO_DIRECTION_UP_DOWN,
  ARPEGGIO_DIRECTION_RANDOM,
  ARPEGGIO_DIRECTION_PLAYED,
};

struct SequenceStep {
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
  void set_raw(uint8_t a, uint8_t b) {
    data_[0] = a;
    data_[1] = b;
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

  uint8_t data_[2];
};

static const uint8_t kNumSteps = 16;

struct SequencerSettings {
 public:
  uint8_t seq_mode;
  uint8_t seq_tempo;
  uint8_t seq_groove_template;
  uint8_t seq_groove_amount;
  
  uint8_t arp_direction;
  uint8_t arp_range;
  uint8_t arp_pattern;
  uint8_t arp_clock_division;
  
  uint8_t pattern_size;
  uint8_t pattern_rotation;
  SequenceStep steps[kNumSteps];
  
  uint8_t mode() {
    return seq_mode;
  }
  bool internal_clock() {
    return seq_tempo >= 40;
  }
  
  static void PrintNote(uint8_t note, char* buffer);
  void PrintStep(uint8_t step, char* buffer) const;
  
  uint8_t* saved_data() { return (uint8_t*)(&steps[0]); }
  void PrepareForWrite();
  uint8_t CheckBuffer(uint8_t* buffer) { return 1; }
  void Update() {
    pattern_size = kNumSteps;
    for (uint8_t i = 0; i < kNumSteps; ++i) {
      if (steps[i].blank()) {
        pattern_size = i;
        break;
      }
    }
  }
};

enum SequencerParameter {
  PRM_SEQ_MODE = sizeof(Patch),
  PRM_SEQ_TEMPO,
  PRM_SEQ_GROOVE_TEMPLATE,
  PRM_SEQ_GROOVE_AMOUNT,

  PRM_ARP_DIRECTION,
  PRM_ARP_RANGE,
  PRM_ARP_PATTERN,
  PRM_ARP_DIVISION,
  
  PRM_SEQ_PATTERN_SIZE,
  PRM_SEQ_PATTERN_ROTATION,
};

static const uint8_t kNumArpeggiatorPatterns = 15;

}  // namespace shruthi

#endif // SHRUTHI_SYSTEM_SEQUENCER_SETTINGS_H_
