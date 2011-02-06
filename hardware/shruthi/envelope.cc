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

#include "hardware/shruthi/envelope.h"

#include "hardware/shruthi/resources.h"

namespace hardware_shruthi {

// A decay of 40 will be played as a fast segment with a decay of 52, then a
// slow section with a decay of 28, to give a logarithmic feel.
const uint8_t kEnvelopeKnee = 16;

void Envelope::Init() {
  stage_target_[PRE_ATTACK] = 0;
  stage_target_[ATTACK] = 16383;
  stage_increment_[SUSTAIN] = 0;
  stage_target_[RELEASE_3] = 0;
  stage_target_[DEAD] = -1;
  stage_increment_[DEAD] = 0;
  Trigger(DEAD);
}

void Envelope::Trigger(uint8_t stage) {
  // When the envelope has reached the end of its cycle, it can only be
  // retriggered as an attack. This ensures that a sequencer-initiated request
  // for a release only releases legit triggered notes, and do not resurect dead
  // notes -- which would otherwise result in annoying Zombie clicks.
  if (stage_ == DEAD && stage == RELEASE_1) {
    return;
  }
  stage_ = stage;
  // The note might be released at any moment, so we need to figure out
  // the right slope to make it reach 0 within the release time.
  if (stage == RELEASE_1) {
    int16_t middle = (value_ >> 1);
    stage_target_[RELEASE_1] = (value_ + middle) >> 1;
    stage_target_[RELEASE_2] = middle >> 1;
    int16_t v = value_ >> 7;
    stage_increment_[RELEASE_1] = -ScaleEnvelopeIncrement(
        release_ > kEnvelopeKnee ? release_ - kEnvelopeKnee : 0,
        v);
    stage_increment_[RELEASE_2] = -ScaleEnvelopeIncrement(
        release_,
        v);
    stage_increment_[RELEASE_3] = -ScaleEnvelopeIncrement(
        release_ < (127 - kEnvelopeKnee) ? release_ + kEnvelopeKnee : 127,
        v);
  }
  increment_ = stage_increment_[stage];
  target_ = stage_target_[stage];
  velocity_increment_ = 0;
}

void Envelope::Update(
  uint8_t attack, uint8_t decay, uint8_t sustain, uint8_t release) {
  // Update the envelope increments and targets.
  stage_increment_[ATTACK] = ScaleEnvelopeIncrement(
      attack, 127);
  stage_increment_[PRE_ATTACK] = -ScaleEnvelopeIncrement(
      attack >> 3, 127);
  stage_increment_[DECAY_1] = -ScaleEnvelopeIncrement(
        decay > kEnvelopeKnee ? decay - kEnvelopeKnee : 0,
        127 - sustain);
  stage_increment_[DECAY_2] = -ScaleEnvelopeIncrement(
        decay,
        127 - sustain);
  stage_increment_[DECAY_3] = -ScaleEnvelopeIncrement(
        decay < (127 - kEnvelopeKnee) ? decay + kEnvelopeKnee : 127,
        127 - sustain);
  int16_t middle = static_cast<int16_t>(127 + sustain) << 6;
  stage_target_[DECAY_1] = (middle + 16383) >> 1;
  stage_target_[DECAY_3] = static_cast<int16_t>(sustain) << 7;
  stage_target_[DECAY_2] = (middle + stage_target_[DECAY_3]) >> 1;
  release_ = release;
}

/* static */
uint16_t Envelope::ScaleEnvelopeIncrement(uint8_t time, uint8_t scale) {
  uint16_t increment = ResourcesManager::Lookup<uint16_t, uint8_t>(
      lut_res_env_portamento_increments, time);
  increment = (uint32_t(increment) * scale) >> 8;
  if (increment == 0) {
    increment = 1;
  }
  return increment;
};

}  // namespace hardware_shruthi
