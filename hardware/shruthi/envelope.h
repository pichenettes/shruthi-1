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
//
// This implements a piece-wise ADSR envelope, with an inflection point in the
// decay and release segments to make it sound logarithmitc-y:
//
// 
// 
// < P ><-- A --><-- D -->           <-- R -->
//               1  2  3             4  5  6
//              /\
//             /  \
//            /    \
//           /       \
//          /          \ ____________
//  _      /                         \
//    -   /                           \
//      \/                              \

#ifndef HARDWARE_SHRUTHI_ENVELOPE_H_
#define HARDWARE_SHRUTHI_ENVELOPE_H_

#include "hardware/base/base.h"
#include "hardware/shruthi/patch.h"
#include "hardware/shruthi/shruthi.h"
#include "hardware/utils/op.h"

using namespace hardware_utils_op;

namespace hardware_shruthi {

enum EnvelopeStage {
  // What to do when two notes of a sound with a very long attack time are
  // played in sequence?
  // - Should we reset the envelope to 0 and restart the attack? This creates
  // a nasty click because of the sharp reset.
  // - Should we start the attack from the current value of the envelope? This
  // creates a very weird effect on pads or flutes - if notes are played very
  // fast they end up colliding into each other.
  //
  // The solution is to have a very short "pre-attack" phase in which the
  // envelope quickly goes to 0 to avoid a click, and then restart at the
  // attack.
  PRE_ATTACK = 0,
  ATTACK = 1,
  DECAY_1 = 2,
  DECAY_2 = 3,
  DECAY_3 = 4,
  SUSTAIN = 5,
  RELEASE_1 = 6,
  RELEASE_2 = 7,
  RELEASE_3 = 8,
  DEAD = 9,
};


class Envelope {
 public:
  Envelope() { }
 
  void Init();

  uint8_t stage() { return stage_; }
  int16_t value() { return value_; }

  void Trigger(uint8_t stage);

  void Update(uint8_t attack, uint8_t decay, uint8_t sustain, uint8_t release);

  void Render() {
    value_ += increment_;
    value_ += velocity_increment_;
    // This code makes the assumption that only the ATTACK stage has a positive
    // slope. This is true for the classical ADSR envelope. To support more
    // complex multistage envelopes, the correct code is:
    //
    // if ((increment_ > 0) ^ (value_ < target_)) {
    //
    // but the first test is more expensive on AVR...
    if ((stage_ == ATTACK) ^ (value_ < target_)) {
      value_ = target_;
      ++stage_;
      Trigger(stage_);
    }
  }
  
  void SetVelocity(uint8_t velocity) {
    velocity_increment_ = 0;
    if (increment_ > 0 && velocity) {
      velocity = 80 - velocity;
      if (velocity > 128) {
        velocity = 0;
      }
      velocity_increment_ = ScaleEnvelopeIncrement(velocity, 127);
    }
  }

  static uint16_t ScaleEnvelopeIncrement(uint8_t time, uint8_t scale) 
      __attribute__((noinline));

 private:
  uint8_t release_;  // release time.
  uint8_t stage_;  // current envelope stage.
  int16_t increment_;  // envelope value increment.
  int16_t velocity_increment_;  // envelope value increment.
  int16_t target_;  // target value (moves to next stage once reached).
  int16_t value_;  // envelope value, 0-16384.
  // Increment and target for each stage of the envelope.
  int16_t stage_increment_[DEAD + 1];
  int16_t stage_target_[DEAD + 1];
 
  DISALLOW_COPY_AND_ASSIGN(Envelope);
};

}  // namespace hardware_shruthi

#endif  // HARDWARE_SHRUTHI_OSCILLATOR_H_
