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
// Voice manager / arpeggiator.

#include "hardware/shruthi/voice_controller.h"
#include "hardware/shruthi/patch.h"
#include "hardware/shruthi/resources.h"
#include "hardware/shruthi/synthesis_engine.h"

#include "hardware/utils/random.h"

using hardware_utils::Random;

namespace hardware_shruthi {
  
/* <static> */
int16_t VoiceController::internal_clock_counter_;
uint8_t VoiceController::midi_clock_counter_;
int16_t VoiceController::step_duration_[2];

uint16_t VoiceController::pattern_;
uint16_t VoiceController::pattern_mask_;
uint8_t VoiceController::pattern_step_;
  
int8_t VoiceController::arpeggio_step_;
int8_t VoiceController::direction_;
int8_t VoiceController::octave_step_;
int8_t VoiceController::octaves_;
uint8_t VoiceController::mode_;

NoteStack VoiceController::notes_;
Voice* VoiceController::voices_;
uint8_t VoiceController::num_voices_;
  
uint8_t VoiceController::tempo_;
uint8_t VoiceController::pattern_size_;
uint8_t VoiceController::active_;
uint8_t VoiceController::inactive_steps_;

uint16_t VoiceController::step_duration_estimator_num_;
uint8_t VoiceController::step_duration_estimator_den_;
uint16_t VoiceController::estimated_beat_duration_;
/* </static> */

/* static */
void VoiceController::Init(Voice* voices, uint8_t num_voices) {
  voices_ = voices;
  num_voices_ = num_voices;
  notes_.Clear();
  tempo_ = 120;
  step_duration_[0] = step_duration_[1] = (kSampleRate * 60L / 4) / 120;
  octaves_ = 0;
  pattern_size_ = 16;
  pattern_ = 0x5555;
  mode_ = 0;
  inactive_steps_ = 0;
  active_ = 0;
  Reset();
}

/* static */
void VoiceController::Reset() {
  // If 4 beats has elapsed without event, the sequencer will restart from
  // the first step when a key is pressed. Otherwise, the pattern will continue
  // moving on.
  // Note that all this active/reset stuff is only for internal clock. For
  // external clock there's little we can do as we don't know, for example,
  // if not receiving a clock event at t means "we're slowing down" or "we have
  // stopped".
  if (!active_) {
    midi_clock_counter_ = kMidiClockPrescaler;
    if (tempo_) {
      estimated_beat_duration_ = step_duration_[0] / (kControlRate / 4);
    }
    pattern_mask_ = 255;
    internal_clock_counter_ = 0;
    step_duration_estimator_num_ = 0xffff;
    step_duration_estimator_den_ = 0xff;
    pattern_step_ = pattern_size_ - 1;
    direction_ = mode_ == ARPEGGIO_DIRECTION_DOWN ? -1 : 1; 
    ArpeggioStart();
  }
}

/* static */
void VoiceController::AllSoundOff() {
  notes_.Clear();
  for (uint8_t i = 0; i < num_voices_; ++i) {
    voices_[i].Kill();
  }
}

/* static */
void VoiceController::AllNotesOff() {
  notes_.Clear();
  for (uint8_t i = 0; i < num_voices_; ++i) {
    voices_[i].Release();
  }
}

/* static */
void VoiceController::UpdateArpeggiatorParameters(const Patch& patch) {
  tempo_ = patch.arp_tempo;
  pattern_ = ResourcesManager::Lookup<uint16_t, uint8_t>(
      lut_res_arpeggiator_patterns, patch.arp_pattern >> 2);
  mode_ = patch.arp_pattern & 0x03;
  direction_ = mode_ == ARPEGGIO_DIRECTION_DOWN ? -1 : 1;
  octaves_ = patch.arp_octave;
  pattern_size_ = patch.pattern_size;
  step_duration_[0] = (kSampleRate * 60L / 4) / static_cast<int32_t>(tempo_);
  step_duration_[1] = step_duration_[0];
  estimated_beat_duration_ = step_duration_[0] / (kControlRate / 4);
  int16_t swing = (step_duration_[0] * static_cast<int32_t>(patch.arp_swing)) >> 9;
  step_duration_[0] += swing;
  step_duration_[1] -= swing;
}

/* static */
void VoiceController::NoteOn(uint8_t note, uint8_t velocity) {
  if (velocity == 0) {
    NoteOff(note);
  } else {
    notes_.NoteOn(note, velocity);
    // In case we haven't played something for a while, reset all the
    // sequencer/arpeggiator stuff.
    Start();
    // Trigger the note.
    if (octaves_ == 0) {
      voices_[0].Trigger(note, velocity, notes_.size() > 1);
    }
  }
}

/* static */
void VoiceController::NoteOff(uint8_t note) {
  notes_.NoteOff(note);

  // If no note is remaining, play the release phase of the envelope.
  if (notes_.size() == 0) {
    voices_[0].Release();
  } else {
    // Otherwise retrigger the previously played note, or let the arpeggiator
    // do it. No need to retrigger if we just removed notes different from
    // the one currently played.
    if (octaves_ == 0) {
      uint8_t retriggered_note = notes_.most_recent_note().note;
      if (retriggered_note != note) {
        voices_[0].Trigger(retriggered_note, 0, true);
      }
    }
  }
}

/* static */
uint8_t VoiceController::Control() {
  ++step_duration_estimator_num_;
  if ((tempo_ && internal_clock_counter_ > 0) ||
      (!tempo_ && midi_clock_counter_ > 0)) {
    return 0;
  }
  ++step_duration_estimator_den_;
  
  // Move to the next step in the x-o-x pattern.
  pattern_mask_ <<= 1;
  pattern_step_ += 1;
  if (pattern_step_ >= pattern_size_) {
    pattern_mask_ = 1;
    pattern_step_ = 0;
  }
  if (notes_.size() == 0 && tempo_) {
    ++inactive_steps_;
    if (inactive_steps_ >= pattern_size_) {
      Stop();
      inactive_steps_ = 0;
    }
  }
  
  // Update the value of the counter depending on which steps we are on.
  // Steps 1, 2 are longer than steps 3, 4 if swing is enabled.
  if (tempo_) {
    if (pattern_step_ & 2) {
      internal_clock_counter_ += step_duration_[1];
    } else {
      internal_clock_counter_ += step_duration_[0];
    }
  } else {
    midi_clock_counter_ += kMidiClockPrescaler;
  }
  if (step_duration_estimator_den_ == 4) {
    estimated_beat_duration_ = step_duration_estimator_num_;
    step_duration_estimator_den_ = 0;
    step_duration_estimator_num_ = 0;
  }

  if (notes_.size() == 0 || octaves_ == 0) {
    return 1;
  }
  
  // If the bit is set in the x-o-x pattern, move to the next note.
  if (has_arpeggiator_note()) {
    Step();
  }
  return 2;
}

/* static */
void VoiceController::ArpeggioStart() {
  if (direction_ == 1) {
    octave_step_ = 0;
    arpeggio_step_ = 0; 
  } else {
    octave_step_ = octaves_ - 1;
    arpeggio_step_ = notes_.size() - 1;
  }
}

/* static */
void VoiceController::ArpeggioStep() {
  uint8_t num_notes = notes_.size();
  arpeggio_step_ += direction_;
  uint8_t next_octave = 0;
  if (arpeggio_step_ >= num_notes) {
    arpeggio_step_ = 0;
    next_octave = 1;
  } else if (arpeggio_step_ < 0) {
    arpeggio_step_ = num_notes - 1;
    next_octave = 1;
  }
  if (next_octave) {
    octave_step_ += direction_;
    if (octave_step_ >= octaves_ || octave_step_ < 0) {
      if (mode_ == ARPEGGIO_DIRECTION_UP_DOWN) {
        direction_ = -direction_;
        ArpeggioStart();
        if (num_notes > 1 || octaves_ > 1) {
          ArpeggioStep();
        }
      } else {
        ArpeggioStart();
      }
    }
  }
}

/* static */
void VoiceController::Step() {
  uint8_t num_notes = notes_.size();
  if (mode_ == ARPEGGIO_DIRECTION_RANDOM) {
    uint8_t random_byte = Random::state_msb();
    octave_step_ = random_byte & 0xf;
    arpeggio_step_ = (random_byte & 0xf0) >> 4;
    while (octave_step_ >= octaves_) {
      octave_step_ -= octaves_;
    }
    while (arpeggio_step_ >= num_notes) {
      arpeggio_step_ -= num_notes;
    }
  } else {
    ArpeggioStep();
  }
  uint8_t note = notes_.sorted_note(arpeggio_step_).note;
  note += 12 * octave_step_;
  while (note > 127) {
    note -= 12;
  }
  voices_[0].Trigger(note, notes_.sorted_note(arpeggio_step_).velocity, false);
}    

}  // namespace hardware_shruthi
