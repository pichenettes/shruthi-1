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
// Patch data.

#include "shruthi/patch.h"
#include "shruthi/part.h"

#include <string.h>

namespace shruthi {

void Patch::PrepareForWrite() {
  version_ = '%';
  filter_topology_ = (filter_1_mode_ << 4) | filter_2_mode_;
  op_data_[0] = ops_[0].operands[0];
  op_data_[1] = (ops_[0].operands[1] << 3) | (ops_[0].op & 0x7);
  op_data_[2] = ops_[1].operands[0];
  op_data_[3] = (ops_[1].operands[1] << 3) | (ops_[1].op & 0x7);
  if (ops_[0].op & 0x8) {
    op_data_[0] |= 0x80;
  }
  if (ops_[1].op & 0x8) {
    op_data_[2] |= 0x80;
  }
  if (ops_[0].operands[1] & 0x20) {
    op_data_[0] |= 0x40;
  }
  if (ops_[1].operands[1] & 0x20) {
    op_data_[2] |= 0x40;
  }
  
  // Copy sequencer settings data into patch data.
  const SystemSettings system_settings = part.system_settings();
  const SequencerSettings sequencer_settings = part.sequencer_settings();
  
  extra_data_[0] = system_settings.legato ? 0x40 : 0x00;
  extra_data_[0] |= system_settings.portamento;
  
  extra_data_[1] = sequencer_settings.seq_mode;
  extra_data_[2] = sequencer_settings.seq_tempo;
  extra_data_[3] = sequencer_settings.seq_groove_template;
  extra_data_[4] = sequencer_settings.seq_groove_amount;
  extra_data_[5] = (sequencer_settings.arp_direction << 4) | \
      sequencer_settings.arp_range;
  extra_data_[6] = sequencer_settings.arp_pattern;
  extra_data_[7] = sequencer_settings.arp_clock_division;
}

uint8_t Patch::CheckBuffer(uint8_t* buffer) {
  for (uint8_t i = 8; i < 24; ++i) {
    if (buffer[i] >= 128) {
      memset(name, '-', 8);
      return 0;
    }
  }
  if (buffer[91] != '!' && buffer[91] != '%') {
    memset(name, '-', 8);
    return 0;
  }
  return 1;
}

void Patch::Update() {
  // Horrible hack to set the HPF to 0 on patches saved with previous
  // versions of the firmware.
  if (op_data_[2] == 'n' && op_data_[3] == 'g') {
    memset(saved_data() + 84, 0, 8);
  }
  ops_[0].operands[0] = op_data_[0] & 0x3f;
  ops_[0].operands[1] = op_data_[1] >> 3;
  ops_[0].op = op_data_[1] & 0x7;
  if (op_data_[0] & 0x80) {
    ops_[0].op |= 0x8;
  }
  if (op_data_[0] & 0x40) {
    ops_[0].operands[1] |= 0x20;
  }
  
  ops_[1].operands[0] = op_data_[2] & 0x3f;
  ops_[1].operands[1] = op_data_[3] >> 3;
  ops_[1].op = op_data_[3] & 0x7;
  if (op_data_[2] & 0x80) {
    ops_[1].op |= 0x8;
  }
  if (op_data_[2] & 0x40) {
    ops_[1].operands[1] |= 0x20;
  }
    
  filter_2_mode_ = filter_topology_ & 0xf;
  filter_1_mode_ = filter_topology_ >> 4;
  
  if (version_ == '%') {
    SystemSettings* system_settings = part.mutable_system_settings();
    SequencerSettings* sequencer_settings = part.mutable_sequencer_settings();
    
    system_settings->legato = extra_data_[0] & 0x40 ? 1 : 0;
    system_settings->portamento = extra_data_[0] & 0x3f;

    if (!part.running()) {
      sequencer_settings->seq_mode = extra_data_[1];
      sequencer_settings->seq_tempo = extra_data_[2];
      sequencer_settings->seq_groove_template = extra_data_[3];
      sequencer_settings->seq_groove_amount = extra_data_[4];
      sequencer_settings->arp_direction = extra_data_[5] >> 4;
      sequencer_settings->arp_range = extra_data_[5] & 0xf;
      sequencer_settings->arp_pattern = extra_data_[6];
      sequencer_settings->arp_clock_division = extra_data_[7];
    }
  }
}

}  // shruthi
