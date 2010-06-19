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
// Main synthesis engine. Everything is in static methods because this allows
// the compiler to compute in advance the address of all objects, and use direct
// addressing like:
// lds r18, 0x04e4
//
// instead of ugly indirect addressing like:
// subi r28, 0xf1
// sbci r29, 0xfD
// ld r18, Y
// ldd  r19, Y+1  ; 0x01
//
// This transformation from a class that would be used as a singleton anyway,
// to a "class" with only static methods/member variables yielded faster, leaner
// code in many places and has since been widely adopted in the code.
//
// Note that a polyphonic synth would need several voices object - in this case
// this transformation should not be applied to the Voice class. Since, for now
// only the monophonic mode is supported, Voice is also "static'ified".

#ifndef HARDWARE_SHRUTHI_SYNTHESIS_ENGINE_H_
#define HARDWARE_SHRUTHI_SYNTHESIS_ENGINE_H_

#include "hardware/shruthi/shruthi.h"

#include "hardware/midi/midi.h"
#include "hardware/shruthi/envelope.h"
#include "hardware/shruthi/lfo.h"
#include "hardware/shruthi/patch.h"
#include "hardware/shruthi/sequencer_settings.h"
#include "hardware/shruthi/system_settings.h"
#include "hardware/shruthi/voice_allocator.h"
#include "hardware/shruthi/voice_controller.h"

namespace hardware_shruthi {

// Used for MIDI -> oscillator increment conversion.
static const int16_t kLowestNote = 0 * 128;
static const int16_t kHighestNote = 108 * 128;
static const int16_t kOctave = 12 * 128;
static const int16_t kPitchTableStart = 96 * 128;

static const uint8_t kNumLfos = 2;
static const uint8_t kNumEnvelopes = 2;
static const uint8_t kNumOscillators = 2;

class Voice {
 public:
  Voice() { }
  static void Init();

  // Called whenever a new note is played, manually or through the arpeggiator.
  static void Trigger(uint8_t note, uint8_t velocity, uint8_t legato);

  // Move this voice to the release stage.
  static void Release();

  // Move this voice to the release stage.
  static void Kill() { TriggerEnvelope(DEAD); }

  static void Audio();
  static void Control();

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
    uint8_t value = modulation_destinations_[MOD_DST_2_BITS];
    return value == 0xff ?
        modulation_destinations_[MOD_DST_CV_1] :
        (value >= 32 ? 0xff : 0);
  }
  static inline uint8_t cv_2()  {
    uint8_t value = modulation_destinations_[MOD_DST_2_BITS];
    return value == 0xff ?
        modulation_destinations_[MOD_DST_CV_2] :
        ((value & 31) >= 16 ? 0xff : 0);
  }
  static inline uint8_t signal()  { return signal_; }

  static inline uint8_t dead()  { return dead_; }
  static inline uint8_t modulation_source(uint8_t i) {
    return modulation_sources_[i - kNumGlobalModulationSources];
  }
  static uint8_t modulation_destination(uint8_t i) {
    return modulation_destinations_[i];
  }
  static Envelope* mutable_envelope(uint8_t i) { return &envelope_[i]; }
  static void TriggerEnvelope(uint8_t stage);
  static void TriggerEnvelope(uint8_t index, uint8_t stage);

 private:
  // Envelope generators.
  static Envelope envelope_[kNumEnvelopes];
  static uint8_t dead_;

  // Counters/phases for the pitch envelope generator (portamento).
  // Pitches are stored on 14 bits, the 7 highest bits are the MIDI note value,
  // the 7 lowest bits are used for fine-tuning.
  static int16_t pitch_increment_;
  static int16_t pitch_target_;
  static int16_t pitch_value_;

  // The voice-specific modulation sources are from MOD_SRC_ENV_1 to
  // MOD_SRC_GATE.
  static uint8_t modulation_sources_[kNumVoiceModulationSources];

  // Value of all the stuff controlled by the modulators, scaled to the value
  // they will be used for. MOD_DST_FILTER_RESONANCE is the last entry
  // in the modulation destinations enum.
  static int8_t modulation_destinations_[kNumModulationDestinations];

  static uint8_t signal_;
  static uint8_t last_note_;
  static uint8_t osc1_phase_msb_;

  DISALLOW_COPY_AND_ASSIGN(Voice);
};

class SynthesisEngine : public hardware_midi::MidiDevice {
  friend class Voice;

 public:
  SynthesisEngine() { }
  static void Init();

  // Forwarded to the controller.
  static void NoteOn(uint8_t channel, uint8_t note, uint8_t velocity);
  static void NoteOff(uint8_t channel, uint8_t note, uint8_t velocity);

  // Handled.
  static void ControlChange(uint8_t channel, uint8_t controller, uint8_t value);
  static void PitchBend(uint8_t channel, uint16_t pitch_bend);
  static void Aftertouch(uint8_t channel, uint8_t note, uint8_t velocity);
  static void Aftertouch(uint8_t channel, uint8_t velocity);
  static void AllSoundOff(uint8_t channel);
  static void ResetAllControllers(uint8_t channel);
  static void AllNotesOff(uint8_t channel);
  static void OmniModeOff(uint8_t channel);
  static void OmniModeOn(uint8_t channel);
  static void Reset();
  static void Clock();
  static void Start();
  static void Stop();

  static void Audio();
  static void Control();

  // Patch manipulation stuff.
  static void SetParameter(uint8_t parameter_index, uint8_t parameter_value);
  static inline uint8_t GetParameter(uint8_t parameter_index) {
    return data_access_byte_[parameter_index + 1];
  }
  static void set_cv(uint8_t cv, uint8_t value) {
    modulation_sources_[MOD_SRC_CV_1 + cv] = value;
  }
  static uint8_t oscillator_decimation() { return oscillator_decimation_; }
  static void ResetPatch();
  static void ResetSequencerSettings();
  static void ResetSequence();
  static void ResetSystemSettings();
  // Variables dependent on parameters (increments) are recomputed in
  // SetParameter when the related parameter is modified. Sometimes, the patch
  // is modified all at once without any call to SetParameter (for example when
  // loading a patch from the EEPROM)... so in this case we need to recompute
  // all the related variables. This is also a good occasion to dump by SysEx
  // the patch to polychained units.
  static void TouchPatch(uint8_t cascade);
  static inline void TouchSequence() {
    controller_.TouchSequence();
  }
  static void TriggerLfos() {
    for (uint8_t i = 0; i < kNumLfos; ++i) {
      lfo_[i].Trigger();
    }
  }
  static inline const Patch& patch() { return patch_; }
  static inline const VoiceController& voice_controller() {
    return controller_;
  }
  static inline const SequencerSettings& sequencer_settings() {
    return sequencer_settings_;
  }
  static inline const SystemSettings& system_settings() {
    return system_settings_;
  }
  static inline Patch* mutable_patch() { return &patch_; }
  static inline VoiceController* mutable_voice_controller() {
    return &controller_;
  }
  static inline SequencerSettings* mutable_sequencer_settings() {
    return &sequencer_settings_;
  }
  static inline SystemSettings* mutable_system_settings() {
    return &system_settings_;
  }

  // These variables are sent to I/O pins, and are made accessible here.
  static inline uint8_t modulation_source(uint8_t i, uint8_t j) {
    if (j < kNumGlobalModulationSources) {
      return modulation_sources_[j];
    } else {
      return voice_[i].modulation_source(j);
    }
  }
  static const Voice& voice(uint8_t i) { return voice_[i]; }
  
  static uint8_t dirty() {
    uint8_t value = dirty_;
    dirty_ = 0;
    return value;
  }
  
 private:
  // Value of global modulation parameters, scaled to 0-255;
  static uint8_t modulation_sources_[kNumGlobalModulationSources];

  static uint8_t data_access_byte_[1];
  static Patch patch_;
  static SequencerSettings sequencer_settings_;
  static SystemSettings system_settings_;
  
  static Lfo lfo_[kNumLfos];
  static uint8_t previous_lfo_fm_[kNumLfos];

  static uint8_t num_lfo_reset_steps_;  // resync the LFO every n-th step.
  static uint8_t lfo_reset_counter_;
  static uint8_t lfo_to_reset_;
  static Voice voice_[kNumVoices];
  static VoiceController controller_;
  static VoiceAllocator polychaining_allocator_;
  static uint8_t oscillator_decimation_;
  static uint8_t nrpn_parameter_number_;
  static uint8_t nrpn_parameter_number_msb_;
  static uint8_t data_entry_msb_;
  static uint8_t dirty_;

  // Called whenever a parameter related to LFOs/envelopes is modified (for now
  // everytime a parameter is modified by the user).
  static void UpdateModulationRates();
  static void UpdateLfoRate(uint8_t i);

  // Called whenever a parameter related to oscillators is called.
  static void UpdateOscillatorAlgorithms();

  DISALLOW_COPY_AND_ASSIGN(SynthesisEngine);
};

extern SynthesisEngine engine;

}  // namespace hardware_shruthi

#endif  // HARDWARE_SHRUTHI_SYNTHESIS_ENGINE_H_
