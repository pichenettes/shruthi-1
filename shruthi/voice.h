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

#ifndef SHRUTHI_VOICE_H_
#define SHRUTHI_VOICE_H_

#include "shruthi/shruthi.h"

#include "midi/midi.h"
#include "shruthi/envelope.h"
#include "shruthi/patch.h"
#include "shruthi/voice_allocator.h"

namespace shruthi {

// Used for MIDI -> oscillator increment conversion.
static const int16_t kLowestNote = 0 * 128;
static const int16_t kHighestNote = 128 * 128;
static const int16_t kOctave = 12 * 128;
static const int16_t kPitchTableStart = 116 * 128;

static const uint8_t kNumLfos = 2;
static const uint8_t kNumEnvelopes = 2;
static const uint8_t kNumOscillators = 2;

class Voice {
 public:
  Voice() { }
  static void Init();

  // Called whenever a new note is played, manually or through the arpeggiator.
  static void NoteOn(
      uint16_t note,
      uint8_t velocity,
      uint8_t portamento,
      bool trigger);

  // Move this voice to the release stage.
  static void NoteOff();

  // Move this voice to the release stage.
  static void Kill() { TriggerEnvelope(DEAD); }

  static void ProcessBlock();

  // Called whenever a write to the CV analog outputs has to be made.
  static inline uint8_t cutoff()  {
    return modulation_destinations_[MOD_DST_FILTER_CUTOFF];
  }
  static inline uint8_t vca()  {
    return modulation_destinations_[MOD_DST_VCA];
  }
  static inline uint8_t resonance()  {
    return modulation_destinations_[MOD_DST_FILTER_RESONANCE];
  }
  static inline uint8_t cv_1()  {
    return modulation_destinations_[MOD_DST_CV_1];
  }
  static inline uint8_t cv_2()  {
    return modulation_destinations_[MOD_DST_CV_2];
  }
  static inline uint8_t modulation_source(uint8_t i) {
    return modulation_sources_[i];
  }
  static uint8_t modulation_destination(uint8_t i) {
    return modulation_destinations_[i];
  }
  
  static inline void set_modulation_source(uint8_t i, uint8_t value) {
    modulation_sources_[i] = value;
  }

  static inline void set_volume(uint8_t volume) {
    volume_ = volume;
  }
  
  static inline void set_bass_note(int16_t bass_note) {
    pitch_bass_note_ = bass_note;
  }
  
  static Envelope* mutable_envelope(uint8_t i) { return &envelope_[i]; }
  static void TriggerEnvelope(uint8_t stage);
  static void TriggerEnvelope(uint8_t index, uint8_t stage);
  
  static void ControlChange(uint8_t controller, uint8_t value);
  static void Aftertouch(uint8_t value) {
    modulation_sources_[MOD_SRC_AFTERTOUCH] = value << 1;
  }
  static void PitchBend(uint16_t value);
  static void ResetAllControllers();
  
 private:
  static inline void LoadSources() __attribute__((always_inline));
  static inline void ProcessModulationMatrix() __attribute__((always_inline));
  static inline void UpdateDestinations() __attribute__((always_inline));
  static inline void RenderOscillators() __attribute__((always_inline));
  
  static uint16_t NoteToPitch(uint8_t note);
   
  // Envelope generators.
  static Envelope envelope_[kNumEnvelopes];
  static uint8_t disable_envelope_auto_retriggering_[kNumEnvelopes];
  static uint8_t gate_;
  static int16_t dst_[kNumModulationDestinations];

  // Counters/phases for the pitch envelope generator (portamento).
  // Pitches are stored on 14 bits, the 7 highest bits are the MIDI note value,
  // the 7 lowest bits are used for fine-tuning.
  static int16_t pitch_increment_;
  static int16_t pitch_target_;
  static int16_t pitch_value_;
  static int16_t pitch_bass_note_;

  // The voice-specific modulation sources are from MOD_SRC_ENV_1 to
  // MOD_SRC_GATE.
  static uint8_t modulation_sources_[kNumModulationSources];

  // Value of all the stuff controlled by the modulators, scaled to the value
  // they will be used for. MOD_DST_FILTER_RESONANCE is the last entry
  // in the modulation destinations enum.
  static int8_t modulation_destinations_[kNumModulationDestinations];

  static uint8_t buffer_[kAudioBlockSize];
  static uint8_t osc2_buffer_[kAudioBlockSize];
  static uint8_t sync_state_[kAudioBlockSize];
  static uint8_t no_sync_[kAudioBlockSize];
  static uint8_t dummy_sync_state_[kAudioBlockSize];
  static uint8_t trigger_count_;
  
  static uint8_t volume_;

  DISALLOW_COPY_AND_ASSIGN(Voice);
};

}  // namespace shruthi

#endif // SHRUTHI_VOICE_H_
