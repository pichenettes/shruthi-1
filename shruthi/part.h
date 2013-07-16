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

#ifndef SHRUTHI_PART_H_
#define SHRUTHI_PART_H_

#include "shruthi/shruthi.h"

#include "midi/midi.h"
#include "shruthi/envelope.h"
#include "shruthi/lfo.h"
#include "shruthi/part.h"
#include "shruthi/patch.h"
#include "shruthi/sequencer_settings.h"
#include "shruthi/system_settings.h"
#include "shruthi/voice.h"
#include "shruthi/voice_allocator.h"

namespace shruthi {

class Part : public midi::MidiDevice {
  friend class Voice;

 public:
  Part() { }
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
  static void SetName(uint8_t* name);
  static void SetSequenceStep(uint8_t index, uint8_t data_a, uint8_t data_b);
  static void SetPatternRotation(uint8_t rotation);
  static void SetPatternLength(uint8_t length);

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
  static void TouchPatch(bool cascade);
  static void TouchSequence(bool cascade) { }
  static void TriggerLfos() {
    for (uint8_t i = 0; i < kNumLfos; ++i) {
      lfo_[i].Trigger();
    }
  }
  
  static inline bool running() { return false; }
  static inline uint8_t step() { return 0; }
  
  static inline const Patch& patch() { return patch_; }
  static inline const SequencerSettings& sequencer_settings() {
    return sequencer_settings_;
  }
  static inline const SystemSettings& system_settings() {
    return system_settings_;
  }
  static inline Patch* mutable_patch() { return &patch_; }
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
  
  static Lfo lfo_[kNumLfos];
  static uint8_t previous_lfo_fm_[kNumLfos];

  static uint8_t num_lfo_reset_steps_;  // resync the LFO every n-th step.
  static uint8_t lfo_reset_counter_;
  static uint8_t lfo_to_reset_;
  static Voice voice_;
  static VoiceAllocator polychaining_allocator_;
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

  DISALLOW_COPY_AND_ASSIGN(Part);
};

extern Part part;

}  // namespace shruthi

#endif // SHRUTHI_PART_H_
