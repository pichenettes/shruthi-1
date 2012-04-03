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

#ifndef SHRUTHI_SYNTHESIS_ENGINE_H_
#define SHRUTHI_SYNTHESIS_ENGINE_H_

#include "shruthi/shruthi.h"

#include "midi/midi.h"
#include "shruthi/envelope.h"
#include "shruthi/lfo.h"
#include "shruthi/patch.h"
#include "shruthi/sequencer_settings.h"
#include "shruthi/system_settings.h"
#include "shruthi/voice_allocator.h"
#include "shruthi/voice_controller.h"

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
  static void Trigger(uint8_t note, uint8_t velocity, uint8_t legato);
  static void TriggerSecondNote(uint8_t note);

  // Move this voice to the release stage.
  static void Release();

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

  static inline void set_unregistered_modulation_source(
      uint8_t i,
      uint8_t value) {
    unregistered_modulation_sources_[i] = value;
  }
  
  static Envelope* mutable_envelope(uint8_t i) { return &envelope_[i]; }
  static void TriggerEnvelope(uint8_t stage);
  static void TriggerEnvelope(uint8_t index, uint8_t stage);

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
  static int16_t aux_pitch_;

  // The voice-specific modulation sources are from MOD_SRC_ENV_1 to
  // MOD_SRC_GATE.
  static uint8_t modulation_sources_[kNumModulationSources];
  static uint8_t unregistered_modulation_sources_[1];

  // Value of all the stuff controlled by the modulators, scaled to the value
  // they will be used for. MOD_DST_FILTER_RESONANCE is the last entry
  // in the modulation destinations enum.
  static int8_t modulation_destinations_[kNumModulationDestinations];

  static uint8_t last_note_;
  static uint8_t osc1_phase_msb_;
  
  static uint8_t buffer_[kAudioBlockSize];
  static uint8_t osc2_buffer_[kAudioBlockSize];
  static uint8_t sync_state_[kAudioBlockSize];
  static uint8_t no_sync_[kAudioBlockSize];
  static uint8_t dummy_sync_state_[kAudioBlockSize];
  static uint8_t trigger_count_;

  DISALLOW_COPY_AND_ASSIGN(Voice);
};

class SynthesisEngine : public midi::MidiDevice {
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

  static void ProcessBlock();
  static void Trigger(uint8_t index, uint8_t value) {
    voice_.set_modulation_source(MOD_SRC_TRIG_1 + index, value);
  }

  // Patch manipulation stuff.
  static void SetParameter(
      uint8_t struct_parameter_index,
      uint8_t parameter_value,
      uint8_t user_initiated);
  static void SetScaledParameter(
      uint8_t ui_parameter_index,
      uint8_t value,
      uint8_t user_initiated);
  static inline uint8_t GetParameter(uint8_t parameter_index) {
    return data_access_byte_[parameter_index + 1];
  }
  static void set_modulation_source(uint8_t index, uint8_t value) {
    voice_.set_modulation_source(index, value);
  }
  static void set_unregistered_modulation_source(uint8_t index, uint8_t value) {
    voice_.set_unregistered_modulation_source(index, value);
  }
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
  static inline const ExtraSystemSettings& extra_system_settings() {
    return extra_system_settings_;
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
    return voice_.modulation_source(j);
  }

  static const Voice& voice() { return voice_; }
  
  static uint8_t dirty() {
    uint8_t value = dirty_;
    dirty_ = 0;
    return value;
  }
  
  static inline uint8_t fx_control_byte() {
    return (patch_.filter_1_mode_ << 4) | patch_.filter_2_mode_;
  }
  
  static inline uint8_t pvk_routing_byte() {
    uint8_t byte = 0;
    if (patch_.filter_1_mode_ == FILTER_MODE_LP) {
      byte |= 4;
    }
    if (!voice().cv_1()) {
      byte |= 2;
    }
    if (!voice().cv_2()) {
      byte |= 1;
    }
    return byte;
  }
  
  static uint8_t four_pole_routing_byte();
  
  static inline uint8_t svf_routing_byte() {
    uint8_t byte = 0;
    uint8_t filter_1_mode = patch_.filter_1_mode_;
    if (filter_1_mode >= 3) {
      filter_1_mode -= 3;
    }
    if (filter_1_mode == FILTER_MODE_BP) {
      byte = 2;
    } else if (filter_1_mode == FILTER_MODE_HP) {
      byte = 4;
    }
    if (patch_.filter_2_mode_ >= FILTER_MODE_SERIAL_LP && 
        patch_.filter_2_mode_ <= FILTER_MODE_SERIAL_HP) {
      byte |= 1;  // Do not mix filter 1 to the output.
    }
    
    uint8_t filter_2_mode = patch_.filter_2_mode_;
    if (filter_2_mode >= 3) {
      filter_2_mode -= 3;
    }
    if (filter_2_mode == FILTER_MODE_BP) {
      byte |= (2 << 3);
    } else if (filter_2_mode == FILTER_MODE_HP) {
      byte |= (4 << 3);
    }
    if (patch_.filter_2_mode_ < FILTER_MODE_SERIAL_LP) {
      byte |= (1 << 3);  // Do not mix filter 1 to the output.
    }
    return byte;
  }
  
 private:
  static uint8_t data_access_byte_[1];
  static Patch patch_;
  static SequencerSettings sequencer_settings_;
  static SystemSettings system_settings_;
  static ExtraSystemSettings extra_system_settings_;
  
  static Lfo lfo_[kNumLfos];
  static uint8_t previous_lfo_fm_[kNumLfos];

  static uint8_t num_lfo_reset_steps_;  // resync the LFO every n-th step.
  static uint8_t lfo_reset_counter_;
  static uint8_t lfo_to_reset_;
  static Voice voice_;
  static VoiceController controller_;
  static VoiceAllocator polychaining_allocator_;
  static VoiceAllocator duophonic_allocator_;
  static uint8_t nrpn_parameter_number_;
  static uint8_t nrpn_parameter_number_msb_;
  static uint8_t data_entry_msb_;
  static uint8_t dirty_;
  static uint8_t volume_;
  static uint8_t ignore_note_off_messages_;  // For hold pedal.

  // Called whenever a parameter related to LFOs/envelopes is modified (for now
  // everytime a parameter is modified by the user).
  static void UpdateModulationRates();
  static void UpdateLfoRate(uint8_t i);

  DISALLOW_COPY_AND_ASSIGN(SynthesisEngine);
};

extern SynthesisEngine engine;

}  // namespace shruthi

#endif // SHRUTHI_SYNTHESIS_ENGINE_H_
