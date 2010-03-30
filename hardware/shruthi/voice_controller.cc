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
const SequencerSettings* VoiceController::sequencer_settings_;

int16_t VoiceController::internal_clock_counter_;
uint8_t VoiceController::midi_clock_counter_;
int16_t VoiceController::step_duration_[2];

uint16_t VoiceController::pattern_;
uint16_t VoiceController::pattern_mask_;
uint8_t VoiceController::pattern_step_;
uint8_t VoiceController::expanded_pattern_step_;
uint8_t VoiceController::expanded_pattern_size_;

int8_t VoiceController::arp_step_;
int8_t VoiceController::arp_current_direction_;
int8_t VoiceController::arp_octave_step_;

NoteStack VoiceController::notes_;
Voice* VoiceController::voices_;
uint8_t VoiceController::num_voices_;

uint8_t VoiceController::active_;
uint8_t VoiceController::inactive_steps_;
uint8_t VoiceController::previous_mode_;

uint16_t VoiceController::step_duration_estimator_num_;
uint8_t VoiceController::step_duration_estimator_den_;
uint16_t VoiceController::estimated_beat_duration_;
/* </static> */

/* static */
void VoiceController::Init(
    const SequencerSettings* sequencer_settings,
    Voice* voices,
    uint8_t num_voices) {
  sequencer_settings_ = sequencer_settings;
  voices_ = voices;
  num_voices_ = num_voices;
  notes_.Clear();
  TouchSequence();
  inactive_steps_ = 0;
  active_ = 0;
  previous_mode_ = 0xff;
  Reset();
}

/* static */
uint16_t VoiceController::has_arpeggiator_note() {
  if (sequencer_settings_->arp_pattern != kNumArpeggiatorPatterns) {
    return pattern_mask_ & pattern_;
  } else {
    return sequencer_settings_->steps[pattern_step_].gate();
  }
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
    if (sequencer_settings_->seq_tempo) {
      estimated_beat_duration_ = step_duration_[0] / (kControlRate / 4);
    }
    pattern_mask_ = 0xffff;
    internal_clock_counter_ = 0;
    step_duration_estimator_num_ = 0xffff;
    step_duration_estimator_den_ = 0xff;
    expanded_pattern_step_ = expanded_pattern_size_ - 1;
    arp_current_direction_ = (
        sequencer_settings_->arp_direction == ARPEGGIO_DIRECTION_DOWN ? -1 : 1); 
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
void VoiceController::ComputeExpandedPatternSize() {
  uint8_t flow = sequencer_settings_->seq_flow;
  uint8_t pattern_size = sequencer_settings_->pattern_size;
  if (flow >= FLOW_KRAMA_2) {
    pattern_size >>= 1;
  }
  if (flow >= FLOW_KRAMA_4) {
    pattern_size >>= 1;
  }
  switch (flow & 0x3) {
    case FLOW_NORMAL:  // and 
      expanded_pattern_size_ = flow < 4
          ? pattern_size
          : 2 * (pattern_size - 1);
      break;
    case FLOW_REVERSE:
      expanded_pattern_size_ = flow < 4
          ? pattern_size
          : 6 * (pattern_size - 1);
      break;
    case FLOW_BACK_FORTH_1:
      expanded_pattern_size_ = flow < 4
          ? 2 * pattern_size
          : 9 * (pattern_size - 2);
      break;
    case FLOW_BACK_FORTH_2:
      expanded_pattern_size_ = flow < 4
          ? 2 * (pattern_size - 1)
          : 13 * (pattern_size - 2);
      break;
  }
  if (flow >= FLOW_KRAMA_2) {
    expanded_pattern_size_ <<= 1;
  }
  if (flow >= FLOW_KRAMA_4) {
    expanded_pattern_size_ <<= 1;
  }
}

/* static */
void VoiceController::TouchSequence() {
  // When switching from one mode to another, it is safe to stop the sequencer
  // Otherwise we might end up with stuck notes, for example (switching from
  // sequencer to arpeggiator), or from the sequencer starting unexpectedly
  // (switching from latched arpeggiator to sequencer).
  if (sequencer_settings_->seq_mode != previous_mode_) {
    previous_mode_ = sequencer_settings_->seq_mode;
    notes_.Clear();
    voices_[0].Release();
    Stop();
    inactive_steps_ = 0;
  }
  pattern_ = ResourcesManager::Lookup<uint16_t, uint8_t>(
      lut_res_arpeggiator_patterns,
      sequencer_settings_->arp_pattern);
      
  arp_current_direction_ = (
      sequencer_settings_->arp_direction == ARPEGGIO_DIRECTION_DOWN ? -1 : 1);
  ComputeExpandedPatternSize();
  
  step_duration_[0] = (kSampleRate * 60L / 4) / static_cast<int32_t>(sequencer_settings_->seq_tempo);
  step_duration_[1] = step_duration_[0];
  estimated_beat_duration_ = step_duration_[0] / (kControlRate / 4);
  int16_t swing = (step_duration_[0] * static_cast<int32_t>(sequencer_settings_->seq_swing)) >> 9;
  step_duration_[0] += swing;
  step_duration_[1] -= swing;
}

/* static */
void VoiceController::NoteOn(uint8_t note, uint8_t velocity) {
  if (velocity == 0) {
    NoteOff(note);
  } else {
    switch (sequencer_settings_->seq_mode) {
      case SEQUENCER_MODE_STEP:
      case SEQUENCER_MODE_ARP:
        notes_.NoteOn(note, velocity);
        // In case we haven't played something for a while, reset all the
        // sequencer/arpeggiator stuff.
        Start();
        // Trigger the note.
        if (sequencer_settings_->seq_mode == SEQUENCER_MODE_STEP) {
          voices_[0].Trigger(note, velocity, notes_.size() > 1);
        }
        break;
      case SEQUENCER_MODE_SEQUENCER:
        if (!active_) {
          Start();
        } else {
          Stop();
        }
        break;
      case SEQUENCER_MODE_RPS:
        notes_.NoteOn(note, velocity);
        Start();
        break;
    }
  }
}

/* static */
void VoiceController::NoteOff(uint8_t note) {
  // Get the currently playing note.
  uint8_t top_note = notes_.most_recent_note().note;
  notes_.NoteOff(note);

  // If no note is remaining, play the release phase of the envelope.
  if (notes_.size() == 0) {
    voices_[0].Release();
  } else {
    // Otherwise retrigger the previously played note, or let the arpeggiator
    // do it. No need to retrigger if we just removed notes different from
    // the one currently played.
    if (sequencer_settings_->seq_mode == SEQUENCER_MODE_STEP) {
      if (top_note == note) {
        voices_[0].Trigger(notes_.most_recent_note().note, 0, true);
      }
    }
  }
}

/* static */
int8_t VoiceController::FoldPattern() {
  int8_t before = pattern_step_;
  uint8_t step = expanded_pattern_step_;
  uint8_t flow = sequencer_settings_->seq_flow;
  uint8_t pattern_size = sequencer_settings_->pattern_size;
  if (flow >= FLOW_KRAMA_2) {
    step >>= 1;
  }
  if (flow >= FLOW_KRAMA_4) {
    step >>= 1;
  }
  switch (flow) {
    case FLOW_NORMAL:  // and 
      pattern_step_ = step;
      break;

    case FLOW_REVERSE:
      pattern_step_ = pattern_size - step - 1;
      break;

    case FLOW_BACK_FORTH_1:
      pattern_step_ = step < pattern_size ? step : 2 * pattern_size - step - 1;
      break;

    case FLOW_BACK_FORTH_2:
      pattern_step_ = step < pattern_size ? step : 2 * pattern_size - step - 2;
      break;
      
    default:
      pattern_step_ = ResourcesManager::Lookup<uint8_t, uint8_t>(
          waveform_table[WAV_RES_EXPANSION_KRAMA + (flow & 0x3)],
          step);
      break;
  }
  if (flow >= FLOW_KRAMA_4) {
    pattern_step_ <<= 2;
    pattern_step_ += (expanded_pattern_step_ & 0x3);
  } else if (flow >= FLOW_KRAMA_2) {
    pattern_step_ <<= 1;
    pattern_step_ += (expanded_pattern_step_ & 0x1);
  }
  pattern_mask_ = 1 << pattern_step_;
  int8_t delta = pattern_step_ - before;
  if (delta > 1) {
    delta = 1;
  } else if (delta < -1) {
    delta = 1;
  }
  return delta;
}

/* static */
uint8_t VoiceController::Control() {
  ++step_duration_estimator_num_;
  if ((sequencer_settings_->seq_tempo && internal_clock_counter_ > 0) ||
      (!sequencer_settings_->seq_tempo && midi_clock_counter_ > 0)) {
    return 0;
  }
  ++step_duration_estimator_den_;

  // Advance to the next step.
  ++expanded_pattern_step_;
  if (expanded_pattern_step_ >= expanded_pattern_size_) {
    expanded_pattern_step_ = 0;
  }

  // Start counting inactive steps when no key is currently pressed.
  if (notes_.size() == 0 && sequencer_settings_->seq_tempo && 
      sequencer_settings_->seq_mode != SEQUENCER_MODE_SEQUENCER) {
    ++inactive_steps_;
    if (inactive_steps_ >= sequencer_settings_->pattern_size) {
      Stop();
      inactive_steps_ = 0;
      voices_[0].Release();
    }
  }

  // Update the value of the counter depending on which steps we are on.
  // Steps 1, 2 are longer than steps 3, 4 if swing is enabled.
  if (sequencer_settings_->seq_tempo) {
    if (expanded_pattern_step_ & 2) {
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
  
  Step(FoldPattern());
  return 1;
}

/* static */
void VoiceController::ArpeggioStart() {
  if (arp_current_direction_ == 1) {
    arp_octave_step_ = 0;
    arp_step_ = 0; 
  } else {
    arp_octave_step_ = sequencer_settings_->arp_range - 1;
    arp_step_ = notes_.size() - 1;
  }
}

/* static */
void VoiceController::ArpeggioStep(int8_t delta) {
  uint8_t num_notes = notes_.size();
  if (delta == 0) {
    return;
  }
  if (sequencer_settings_->arp_direction == ARPEGGIO_DIRECTION_RANDOM) {
    uint8_t random_byte = Random::state_msb();
    arp_octave_step_ = random_byte & 0xf;
    arp_step_ = (random_byte & 0xf0) >> 4;
    while (arp_octave_step_ >= sequencer_settings_->arp_range) {
      arp_octave_step_ -= sequencer_settings_->arp_range;
    }
    while (arp_step_ >= num_notes) {
      arp_step_ -= num_notes;
    }
  } else {
    arp_step_ += delta < 0 ? -arp_current_direction_ : arp_current_direction_;
    uint8_t next_octave = 0;
    if (arp_step_ >= num_notes) {
      arp_step_ = 0;
      next_octave = 1;
    } else if (arp_step_ < 0) {
      arp_step_ = num_notes - 1;
      next_octave = 1;
    }
    if (next_octave) {
      arp_octave_step_ += delta < 0 ? -arp_current_direction_ : arp_current_direction_;
      if (arp_octave_step_ >= sequencer_settings_->arp_range ||
          arp_octave_step_ < 0) {
        if (sequencer_settings_->arp_direction == ARPEGGIO_DIRECTION_UP_DOWN) {
          arp_current_direction_ = -arp_current_direction_;
          ArpeggioStart();
          if (num_notes > 1 || sequencer_settings_->arp_range > 1) {
            ArpeggioStep(delta);
          }
        } else {
          if (arp_current_direction_ * delta == 1) {
            arp_octave_step_ = 0;
            arp_step_ = 0; 
          } else {
            arp_octave_step_ = sequencer_settings_->arp_range - 1;
            arp_step_ = notes_.size() - 1;
          }
        }
      }
    }
  }
}

/* static */
void VoiceController::Step(int8_t delta) {
  switch (sequencer_settings_->seq_mode) {
    case SEQUENCER_MODE_ARP:
      if (notes_.size() == 0) {
        return;
      }
      if (has_arpeggiator_note()) {
        // Do not move the arpeggiator to the next note when there's a legato
        // in the sequence (for the arpeggiator, legato behaves more like "tie")
        if (sequencer_settings_->arp_pattern != kNumArpeggiatorPatterns ||
            !sequencer_settings_->steps[pattern_step_].legato()) {
          ArpeggioStep(delta);
          uint8_t note = notes_.sorted_note(arp_step_).note;
          note += 12 * arp_octave_step_;
          while (note > 127) {
            note -= 12;
          }
          uint8_t velocity = (sequencer_settings_->arp_velocity_source == \
                              ARPEGGIO_VELOCITY_SOURCE_KEYBOARD)
              ? notes_.sorted_note(arp_step_).velocity
              : sequencer_settings_->steps[pattern_step_].velocity();
          voices_[0].Trigger(note, velocity, false);
        }
      } else {
        voices_[0].Release();
      }
      break;
      
    case SEQUENCER_MODE_SEQUENCER:
      if (active_) {
        const SequenceStep& step = sequencer_settings_->steps[pattern_step_];
        if (step.gate()) {
          voices_[0].Trigger(step.note(), step.velocity(), step.legato());
        } else {
          voices_[0].Release();
        }
      }
      break;
    case SEQUENCER_MODE_RPS:
      if (notes_.size()) {
        const SequenceStep& step = sequencer_settings_->steps[pattern_step_];
        if (step.gate()) {
          voices_[0].Trigger(
              step.note() + notes_.most_recent_note().note - 60,
              step.velocity(),
              step.legato());
        } else {
          voices_[0].Release();
        }
      }
      break;
  }
}

}  // namespace hardware_shruthi
