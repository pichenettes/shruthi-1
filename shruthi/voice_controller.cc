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

#include "shruthi/voice_controller.h"
#include "shruthi/patch.h"
#include "shruthi/resources.h"
#include "shruthi/synthesis_engine.h"

#include "avrlib/random.h"

using avrlib::Random;

namespace shruthi {

static const uint8_t kNumNotesForExitingLatchMode = 8;

static const prog_uint8_t midi_clock_scale[5] PROGMEM = {
  6 /* normal */, 3 /* x2 */, 12, 24, 48 /* x2, x4, x8 */
};

/* <static> */
SequencerSettings* VoiceController::sequencer_settings_;

int16_t VoiceController::internal_clock_counter_;
uint8_t VoiceController::midi_clock_prescaler_;
int8_t VoiceController::midi_clock_counter_;
int16_t VoiceController::step_duration_[kNumSteps];
int16_t VoiceController::average_step_duration_;

uint16_t VoiceController::pattern_;
uint16_t VoiceController::pattern_mask_;
uint8_t VoiceController::pattern_step_;
uint8_t VoiceController::expanded_pattern_step_;
uint8_t VoiceController::expanded_pattern_size_;
uint8_t VoiceController::expanded_pattern_[256];

int8_t VoiceController::arp_step_;
int8_t VoiceController::arp_current_direction_;
int8_t VoiceController::arp_octave_step_;

NoteStack VoiceController::notes_;
Voice* VoiceController::voices_;
uint8_t VoiceController::num_voices_;

uint8_t VoiceController::active_;
uint8_t VoiceController::inactive_steps_;
uint8_t VoiceController::previous_mode_;
uint8_t VoiceController::recording_;
uint8_t VoiceController::recording_note_;
uint8_t VoiceController::recording_gate_;
uint8_t VoiceController::will_stop_at_step_;

uint16_t VoiceController::step_duration_estimator_num_;
uint8_t VoiceController::step_duration_estimator_den_;
uint16_t VoiceController::estimated_beat_duration_;
EventHandler VoiceController::handler_;
EventHandler VoiceController::handler_table_[] = {
  /* SEQUENCER_MODE_STEP */
  { NoteOnHandlerArpStep, NoteOffHandlerDefault, NULL, 0 },
  /* SEQUENCER_MODE_ARP */
  { NoteOnHandlerArpStep, NoteOffHandlerDefault, StepHandlerArp, 1 },
  /* SEQUENCER_MODE_ARP_LATCH */
  { NoteOnHandlerArpLatch, NoteOffHandlerLatch, StepHandlerArp, 2 },
  /* SEQUENCER_MODE_RPS */
  { NoteOnHandlerRps, NoteOffHandlerDefault, StepHandlerSequencer, 3 },
  /* SEQUENCER_MODE_RPS_LATCH */
  { NoteOnHandlerRpsLatch, NoteOffHandlerLatch, StepHandlerSequencer, 3 },
  /* SEQUENCER_MODE_REC */
  { NoteOnHandlerRpsRecording, NoteOffHandlerRpsRecording,
    StepHandlerSequencer, 3 },
  /* SEQUENCER_MODE_IMPROVISATION */
  { NoteOnHandlerRps, NoteOffHandlerDefault, StepHandlerImprovisation, 3 }
};
/* </static> */

/* static */
void VoiceController::Init(
    SequencerSettings* sequencer_settings,
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
void VoiceController::Reset() {
  // If 4 beats has elapsed without event, the sequencer will restart from
  // the first step when a key is pressed. Otherwise, the pattern will continue
  // moving on.
  // Note that all this active/reset stuff is only for internal clock. For
  // external clock there's little we can do as we don't know, for example,
  // if not receiving a clock event at t means "we're slowing down" or "we have
  // stopped".
  if (!active_) {
    if (midi_clock_prescaler_ == 0) {
      estimated_beat_duration_ = average_step_duration_ / (kControlRate / 4);
    }
    recording_ = 0;
    inactive_steps_ = 0;
    pattern_mask_ = 0xffff;
    internal_clock_counter_ = 0;
    midi_clock_counter_ = 1;  // We'll receive a clock message just afterwards.
    step_duration_estimator_num_ = 0xffff;
    step_duration_estimator_den_ = 0xff;
    expanded_pattern_step_ = expanded_pattern_size_ - 1;
    arp_current_direction_ = (
        sequencer_settings_->arp_direction == ARPEGGIO_DIRECTION_DOWN ? -1 : 1); 
    ArpeggioStart(1);
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
  uint8_t warp = sequencer_settings_->arp_warp;
  uint8_t pattern_size = sequencer_settings_->pattern_size;
  if (warp >= WARP_GLASS_2) {
    pattern_size >>= 1;
  }
  if (warp >= WARP_GLASS_4) {
    pattern_size >>= 1;
  }
  switch (warp) {
    case WARP_NORMAL:
      expanded_pattern_size_ = pattern_size;
      break;
    case WARP_REVERSE:
      expanded_pattern_size_ = pattern_size;
      break;
    case WARP_BACK_FORTH_1:
      expanded_pattern_size_ = 2 * pattern_size;
      break;
    case WARP_BACK_FORTH_2:
      expanded_pattern_size_ = 2 * (pattern_size - 1);
      break;
    default:
      {
        uint8_t warp_type = warp - WARP_GLASS;
        while (warp_type >= 5) {
          warp_type -= 5;
        }
        switch (warp_type) {
          case 0:
            // Compute a Philip Glass-like sequence expansion.
            expanded_pattern_size_ = 0;
            for (uint8_t i = 0; i < pattern_size; ++i) {
              for (uint8_t j = 0; j < i + 1; ++j) {
                expanded_pattern_[expanded_pattern_size_++] = j;
              }
            }
            for (uint8_t i = 0; i < pattern_size; ++i) {
              for (uint8_t j = i + 1; j < pattern_size; ++j) {
                expanded_pattern_[expanded_pattern_size_++] = j;
              }
            }
            break;
          
          case 1:
            expanded_pattern_size_ = 2 * (pattern_size - 1);
            break;
          
          case 2:
            expanded_pattern_size_ = 6 * (pattern_size - 1);
            break;
          
          case 3:
            expanded_pattern_size_ = 9 * (pattern_size - 2);
            break;
          
          case 4:
            expanded_pattern_size_ = 13 * (pattern_size - 2);
            break;
        }
    }
  }
  if (warp >= WARP_GLASS_2) {
    expanded_pattern_size_ <<= 1;
  }
  if (warp >= WARP_GLASS_4) {
    expanded_pattern_size_ <<= 1;
  }
}

/* static */
void VoiceController::TouchSequence() {
  if (sequencer_settings_->seq_mode != previous_mode_) {
    // When switching between the arpeggiator / sequencer / steps only mode,
    // reset everything, otherwise we might end up with stuck notes!
    if (handler_table_[sequencer_settings_->seq_mode].kind != \
        handler_table_[previous_mode_].kind) {
      StopAndKillNotes();
    } else {
      if (notes_.size()) {
        if (previous_mode_ == SEQUENCER_MODE_REC) {
          // When switching from the recording mode to the standard mode, we need
          // to forget which key was used to start/stop... otherwise it will be
          // interpreted as a transposition key.
          notes_.Clear();
          notes_.NoteOn(60, 80);
        }
        if (sequencer_settings_->seq_mode == SEQUENCER_MODE_REC) {
          will_stop_at_step_ = 0xff;
          recording_ = 1;
        }
      }
    }
    previous_mode_ = sequencer_settings_->seq_mode;
  }   
  pattern_ = ResourcesManager::Lookup<uint16_t, uint8_t>(
      lut_res_arpeggiator_patterns,
      sequencer_settings_->arp_pattern);
      
  arp_current_direction_ = (
      sequencer_settings_->arp_direction == ARPEGGIO_DIRECTION_DOWN ? -1 : 1);
  ComputeExpandedPatternSize();
  
  average_step_duration_ = (kSampleRate * 60L / 4) / static_cast<int32_t>(
      sequencer_settings_->seq_tempo <= 240
          ? sequencer_settings_->seq_tempo
          : ResourcesManager::Lookup<uint16_t, uint8_t>(
              lut_res_turbo_tempi, sequencer_settings_->seq_tempo - 240 - 1));
  if (sequencer_settings_->seq_tempo < 40) {
    midi_clock_prescaler_ = ResourcesManager::Lookup<uint8_t, uint8_t>(
        midi_clock_scale, sequencer_settings_->seq_tempo - 35);
  } else {
    midi_clock_prescaler_ = 0;
  }
  for (uint8_t i = 0; i < kNumSteps; ++i) {
    int32_t swing_direction = ResourcesManager::Lookup<int16_t, uint8_t>(
        LUT_RES_GROOVE_SWING + sequencer_settings_->seq_groove_template, i);
    swing_direction *= average_step_duration_;
    swing_direction *= sequencer_settings_->seq_groove_amount;
    int16_t swing = swing_direction >> 16;
    step_duration_[i] = average_step_duration_ + swing;
  }
  estimated_beat_duration_ = average_step_duration_ / (kControlRate / 4);
  if (sequencer_settings_->seq_mode > SEQUENCER_MODE_IMPROVISATION) {
    sequencer_settings_->seq_mode = SEQUENCER_MODE_IMPROVISATION;
  }
  handler_ = handler_table_[sequencer_settings_->seq_mode];
}

/* static */
void VoiceController::NoteOnHandlerArpStep(uint8_t note, uint8_t velocity) {
  notes_.NoteOn(note, velocity);
  // In case we haven't played something for a while, reset all the
  // sequencer/arpeggiator stuff.
  Start();
  // Trigger the note.
  if (sequencer_settings_->seq_mode == SEQUENCER_MODE_STEP) {
    voices_[0].Trigger(note, velocity, notes_.size() > 1);
    voices_[0].TriggerSecondNote(notes_.least_recent_note().note);
  }
}

/* static */
void VoiceController::NoteOnHandlerArpLatch(uint8_t note, uint8_t velocity) {
  if (!recording_) {
    notes_.Clear();
    recording_ = 1;
  }
  notes_.NoteOn(note, velocity);
  Start();
  if (notes_.size() == kNumNotesForExitingLatchMode) {
    StopAndKillNotes();
  }
}

/* static */
void VoiceController::NoteOnHandlerRpsLatch(uint8_t note, uint8_t velocity) {
  if (notes_.size() == 0) {
    Start();
    notes_.NoteOn(note, velocity);
  } else if (notes_.most_recent_note().note == note) {
    StopAndKillNotes();
  } else {
    notes_.Clear();
    notes_.NoteOn(note, velocity);
  }
}

/* static */
void VoiceController::NoteOnHandlerRps(uint8_t note, uint8_t velocity) {
  notes_.NoteOn(note, velocity);
  if (notes_.size() == 1) {
    Start();
  } else {
    if (sequencer_settings_->seq_mode == SEQUENCER_MODE_IMPROVISATION) {
      voices_[0].Trigger(note, velocity, notes_.size() > 2);
    }
  }
}

/* static */
void VoiceController::NoteOnHandlerRpsRecording(
    uint8_t note,
    uint8_t velocity) {
  if (notes_.size() == 0) {
    Start();
    notes_.NoteOn(note, velocity);
    will_stop_at_step_ = 0xff;
    recording_ = 1;
  } else if (notes_.most_recent_note().note == note) {
    StopAndKillNotes();
    recording_note_ = 0;
    recording_ = 0;
  } else {
    if (will_stop_at_step_ == 0xff) {
      will_stop_at_step_ = 0;
      pattern_step_ = 0;
      expanded_pattern_step_ = 0;
    }
    sequencer_settings_->steps[pattern_step_].set_note(note);
    sequencer_settings_->steps[pattern_step_].set_legato(0);
    sequencer_settings_->steps[pattern_step_].set_gate(1);
    sequencer_settings_->steps[pattern_step_].set_velocity(velocity);
    recording_note_ = note;
    recording_gate_ = 1;
    voices_[0].Trigger(note, velocity, 0);
  }
}

/* static */
void VoiceController::NoteOffHandlerLatch(uint8_t note) {
  if (note == notes_.most_recent_note().note) {
    recording_ = 0;
  }
}
  
/* static */
void VoiceController::NoteOffHandlerDefault(uint8_t note) {
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
        voices_[0].Trigger(
            notes_.most_recent_note().note,
            notes_.most_recent_note().velocity,
            1);
      }
    }
  }
  if (sequencer_settings_->seq_mode == SEQUENCER_MODE_IMPROVISATION) {
    if (notes_.size() == 1) {
      Step(0);
    }
  } 
}

/* static */
void VoiceController::NoteOffHandlerRpsRecording(uint8_t note) {
  recording_gate_ = 0;
  voices_[0].Release();
}

/* static */
void VoiceController::NoteOn(uint8_t note, uint8_t velocity) {
  if (velocity == 0) {
    NoteOff(note);
  } else {
    (*handler_.handle_note_on)(note, velocity);
  }
}

void VoiceController::NoteOff(uint8_t note) {
  if (handler_.handle_note_off) {
    (*handler_.handle_note_off)(note);
  }
}

/* static */
int8_t VoiceController::FoldPattern() {
  int8_t before = pattern_step_;
  uint8_t step = expanded_pattern_step_;
  uint8_t warp = sequencer_settings_->arp_warp;
  uint8_t pattern_size = sequencer_settings_->pattern_size;
  if (warp >= WARP_GLASS_2) {
    step >>= 1;
  }
  if (warp >= WARP_GLASS_4) {
    step >>= 1;
  }
  switch (warp) {
    case WARP_NORMAL:
      pattern_step_ = step;
      break;

    case WARP_REVERSE:
      pattern_step_ = pattern_size - step - 1;
      break;

    case WARP_BACK_FORTH_1:
      pattern_step_ = step < pattern_size ? step : 2 * pattern_size - step - 1;
      break;

    case WARP_BACK_FORTH_2:
      pattern_step_ = step < pattern_size ? step : 2 * pattern_size - step - 2;
      break;

    default:
      {
        uint8_t warp_type = warp - WARP_GLASS;
        while (warp_type >= 5) {
          warp_type -= 5;
        }
        if (warp_type == 0) {
          pattern_step_ = expanded_pattern_[step];
        } else {
          pattern_step_ = ResourcesManager::Lookup<uint8_t, uint8_t>(
              waveform_table[WAV_RES_EXPANSION_KRAMA + warp_type - 1],
              step);
        }
      }
      break;
  }
  if (warp >= WARP_GLASS_4) {
    pattern_step_ <<= 2;
    pattern_step_ += (expanded_pattern_step_ & 0x3);
  } else if (warp >= WARP_GLASS_2) {
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
  internal_clock_counter_ -= kControlRate;
  ++step_duration_estimator_num_;
  if ((!midi_clock_prescaler_ && internal_clock_counter_ > 0) ||
      (midi_clock_prescaler_ && midi_clock_counter_ > 0)) {
    return 0;
  }
  ++step_duration_estimator_den_;

  // Advance to the next step.
  ++expanded_pattern_step_;
  if (expanded_pattern_size_ &&
      expanded_pattern_step_ >= expanded_pattern_size_) {
    expanded_pattern_step_ = 0;
  }

  // Start counting inactive steps when no key is currently pressed.
  if (notes_.size() == 0 && !midi_clock_prescaler_ &&
      sequencer_settings_->seq_mode != SEQUENCER_MODE_RPS_LATCH &&
      sequencer_settings_->seq_mode != SEQUENCER_MODE_ARP_LATCH &&
      active_) {
    ++inactive_steps_;
    if (inactive_steps_ >= sequencer_settings_->pattern_size) {
      StopAndKillNotes();
    }
  }

  // Update the value of the counter depending on which steps we are on.
  // Steps 1, 2 are longer than steps 3, 4 if swing is enabled.
  if (!midi_clock_prescaler_) {
    internal_clock_counter_ += step_duration_[expanded_pattern_step_ & 0x0f];
  } else {
    midi_clock_counter_ += midi_clock_prescaler_;
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
void VoiceController::StopAndKillNotes() {
  active_ = 0;
  notes_.Clear();
  voices_[0].Release();
  recording_ = 0;
}

/* static */
void VoiceController::ArpeggioStart(int8_t delta) {
  int8_t sign = delta > 0 ? arp_current_direction_ : -arp_current_direction_;
  if (sign == 1) {
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
          ArpeggioStart(delta);
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
void VoiceController::StepHandlerArp(int8_t delta) {
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
      uint8_t velocity = (notes_.sorted_note(arp_step_).velocity + \
          sequencer_settings_->steps[pattern_step_].velocity()) >> 1;
      voices_[0].Trigger(note, velocity, false);
    }
  } else {
    voices_[0].Release();
  }
}

/* static */
void VoiceController::StepHandlerSequencer(int8_t delta) {
  if (notes_.size()) {
    if (pattern_step_ == will_stop_at_step_) {
      will_stop_at_step_ = 0xff;
    }
    if (will_stop_at_step_ != 0xff) {
      if (recording_gate_) {
        sequencer_settings_->steps[pattern_step_].set_note(recording_note_);
        sequencer_settings_->steps[pattern_step_].set_velocity(4);
        sequencer_settings_->steps[pattern_step_].set_legato(1);
        sequencer_settings_->steps[pattern_step_].set_gate(1);
      } else {
        sequencer_settings_->steps[pattern_step_].set_note(recording_note_);
        sequencer_settings_->steps[pattern_step_].set_velocity(4);
        sequencer_settings_->steps[pattern_step_].set_legato(0);
        sequencer_settings_->steps[pattern_step_].set_gate(0);
      }
    } else {
      int8_t transpose = recording_ ? 0 : notes_.most_recent_note().note - 60;
      const SequenceStep& step = sequencer_settings_->steps[pattern_step_];
      if (step.gate()) {
        voices_[0].Trigger(
            step.note() + transpose,
            step.velocity(),
            step.legato() ? 255 : 0);
      } else {
        voices_[0].Release();
      }
    }
  }
}

/* static */
void VoiceController::StepHandlerImprovisation(int8_t delta) {
  if (notes_.size() == 1) {
    const SequenceStep& step = sequencer_settings_->steps[pattern_step_];
    if (step.gate()) {
      voices_[0].Trigger(
          step.note() + notes_.most_recent_note().note - 60,
          step.velocity(),
          step.legato() ? 255 : 0);
    }
  }
}

/* static */
void VoiceController::Step(int8_t delta) {
  if (handler_.handle_step) {
    (*handler_.handle_step)(delta);
  }
}

}  // namespace shruthi
