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
// Envelopes.

#ifndef SHRUTHI_ENVELOPE_H_
#define SHRUTHI_ENVELOPE_H_

#include "avrlib/base.h"
#include "shruthi/patch.h"
#include "shruthi/resources.h"
#include "shruthi/shruthi.h"
#include "avrlib/op.h"

using namespace avrlib;

namespace shruthi {

enum EnvelopeStage {
  ATTACK = 0,
  DECAY = 1,
  SUSTAIN = 2,
  RELEASE = 3,
  DEAD = 4,
  NUM_SEGMENTS,
};


class Envelope {
 public:
  Envelope() { }

  void Init() {
    stage_target_[ATTACK] = 255;
    stage_target_[RELEASE] = 0;
    stage_target_[DEAD] = 0;
    stage_phase_increment_[SUSTAIN] = 0;
    stage_phase_increment_[DEAD] = 0;
  }

  uint8_t stage() { return stage_; }
  uint16_t value() { return value_; }

  void Trigger(uint8_t stage) {
    if (stage == DEAD) {
      value_ = 0;
    }
    a_ = value_ >> 8;
    b_ = stage_target_[stage];
    stage_ = stage;
    phase_ = 0;
    phase_increment_ = stage_phase_increment_[stage];
  }

  inline void UpdateAttack(uint8_t attack) {
    stage_phase_increment_[ATTACK] = ResourcesManager::Lookup<
        uint16_t, uint8_t>(lut_res_env_portamento_increments, attack);
    phase_increment_ = stage_phase_increment_[stage_];
  }

  inline void Update(
      uint8_t attack,
      uint8_t decay,
      uint8_t sustain,
      uint8_t release) {
    stage_phase_increment_[ATTACK] = ResourcesManager::Lookup<
        uint16_t, uint8_t>(lut_res_env_portamento_increments, attack);
    stage_phase_increment_[DECAY] = ResourcesManager::Lookup<
        uint16_t, uint8_t>(lut_res_env_portamento_increments, decay);
    stage_phase_increment_[RELEASE] = ResourcesManager::Lookup<
        uint16_t, uint8_t>(lut_res_env_portamento_increments, release);
    stage_target_[DECAY] = sustain << 1;
    stage_target_[SUSTAIN] = stage_target_[DECAY];
  }

  uint8_t Render() {
    phase_ += phase_increment_;
    if (phase_ < phase_increment_) {
      value_ = U8MixU16(a_, b_, 255);
      Trigger(++stage_);
    }
    if (phase_increment_) {
      uint8_t step = InterpolateSample(wav_res_env_expo, phase_);
      value_ = U8MixU16(a_, b_, step);
    }
    return value_ >> 8;
  }

 private:
  // Phase increments for each stage.
  uint16_t stage_phase_increment_[NUM_SEGMENTS];
  // Value that needs to be reached at the end of each stage.
  uint8_t stage_target_[NUM_SEGMENTS];
  // Current stage.
  uint8_t stage_;

  // Start and end value of the current segment.
  uint8_t a_;
  uint8_t b_;

  // Phase and phase increment.
  uint16_t phase_increment_;
  uint16_t phase_;

  // Current value of the envelope.
  uint16_t value_;

  DISALLOW_COPY_AND_ASSIGN(Envelope);
};

}  // namespace shruthi

#endif // SHRUTHI_ENVELOPE_H_
