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
// Patch data.

#include "shruthi/patch.h"
#include "shruthi/synthesis_engine.h"

#include <string.h>

namespace shruthi {

void Patch::PrepareForWrite() {
  exclamation_mark_ = '!';
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
  
  
#ifdef PORTAMENTO_SAVE_HACK
  portamento_data = \
      0x80 | \
      (engine.system_settings().legato ? 0x40 : 0x00) | \
      (engine.system_settings().portamento);
#endif  // PORTAMENTO_SAVE_HACK
}

uint8_t Patch::CheckBuffer(uint8_t* buffer) {
  for (uint8_t i = 8; i < 24; ++i) {
    if (buffer[i] >= 128) {
      memset(name, '-', 8);
      return 0;
    }
  }
  if (buffer[91] != '!') {
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
#ifdef PORTAMENTO_SAVE_HACK
  if (!(portamento_data & 0x80)) {
    portamento_data = 0;
  }
  engine.mutable_system_settings()->legato = (portamento_data & 0x40) ? 1 : 0;
  engine.mutable_system_settings()->portamento = portamento_data & 0x3f;
#else
  // Yuck. This is to provide some compatibility with the patches saved with the
  // portamento hack.
  if (name[kPatchNameSize - 1] & 0x80) {
    name[kPatchNameSize - 1] = ' ';
  }
#endif  // PORTAMENTO_SAVE_HACK
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
}

}  // shruthi
