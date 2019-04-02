// Copyright 2009 Emilie Gillet.
//
// Author: Emilie Gillet (emilie.o.gillet@gmail.com)
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

#include "shruthi/envelope.h"
#include "shruthi/lfo.h"
#include "shruthi/note_stack.h"
#include "shruthi/part.h"
#include "shruthi/patch.h"
#include "shruthi/sequencer_settings.h"
#include "shruthi/system_settings.h"
#include "shruthi/voice.h"
#include "shruthi/voice_allocator.h"

namespace shruthi {

class Part {
  friend class Voice;

 public:
  Part() { }
  static void Init();

  // Forwarded to the controller.
  static void NoteOn(uint8_t channel, uint8_t note, uint8_t velocity);
  static void NoteOff(uint8_t channel, uint8_t note);

  // Handled.
  static void ControlChange(uint8_t controller, uint8_t value);
  static void PitchBend(uint16_t pitch_bend) {
    voice_.PitchBend(pitch_bend);
  }
  static void Aftertouch(uint8_t note, uint8_t velocity) {
    voice_.Aftertouch(velocity);
  }
  static void Aftertouch(uint8_t velocity) {
    voice_.Aftertouch(velocity);
  }
  static void AllSoundOff();
  static void ResetAllControllers();
  static void AllNotesOff();
  static void OmniModeOff(uint8_t channel);
  static void OmniModeOn();
  static void Reset();
  static void Clock(bool internal);
  static void Start(bool internal);
  static void Stop(bool internal);

  static void ProcessBlock();  
  static void SetName(uint8_t* name);
  static void SetSequenceStep(uint8_t index, uint8_t data_a, uint8_t data_b);
  static void SetPatternRotation(uint8_t rotation);
  static void SetPatternLength(uint8_t length);

  // Patch manipulation stuff.
  static void SetParameter(uint8_t index, uint8_t offset, uint8_t value,
      bool user_initiated);
  static void SetScaledParameter(uint8_t index, uint8_t value,
      bool user_initiated);
  static inline uint8_t GetParameter(uint8_t offset) {
    return data_access_byte_[offset + 1];
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
  static void Touch(bool cascade);
  static void TriggerLfos() {
    for (uint8_t i = 0; i < kNumLfos; ++i) {
      lfo_[i].Trigger();
    }
  }
  
  static inline bool running() { return arp_seq_running_; }
  static inline uint8_t step() { return arp_seq_step_; }
  
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
  static Voice* mutable_voice() { return &voice_; }
  
  static inline bool dirty() {
    bool value = dirty_;
    dirty_ = false;
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
  
  static inline uint8_t sp_routing_byte() {
    return patch_.filter_1_mode_;
  }
  
  static uint8_t four_pole_routing_byte();
  static uint8_t blinky_eyes();
  
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
    return byte | blinky_eyes();
  }
  
  inline bool internal_clock() { return sequencer_settings_.internal_clock(); }
  inline bool latched() { return ignore_note_off_messages_; }
  inline static void Latch() {
    ignore_note_off_messages_ = true;
    release_latched_keys_on_next_note_on_ = true;
  }
  static inline uint8_t num_notes() {
    return pressed_keys_.size();
  }
  
  inline static void Unlatch() {
    ignore_note_off_messages_ = false;
    release_latched_keys_on_next_note_on_ = true;
  }
  
 private:
  // Called whenever a parameter related to LFOs/envelopes is modified (for now
  // everytime a parameter is modified by the user).
  static void UpdateModulationRates();
  static void UpdateLfoRate(uint8_t i);
  static void StopSequencerArpeggiatorNotes();
  static void ReleaseLatchedNotes();
  static void InternalNoteOn(uint8_t note, uint8_t velocity);
  static void InternalNoteOff(uint8_t note);
  static void ClockArpeggiator();
  static void ClockSequencer();
  static void NextStep();
  
  static uint16_t Tune(uint8_t note);
  static uint8_t step_duration();
   
  static uint8_t data_access_byte_[1];
  static Patch patch_;
  static SequencerSettings sequencer_settings_;
  static SystemSettings system_settings_;
  static bool dirty_;
  
  static uint8_t nrpn_parameter_number_;
  static uint8_t nrpn_parameter_number_msb_;
  static uint8_t data_entry_msb_;
  
  static Voice voice_;
  static NoteStack mono_allocator_;
  static NoteStack pressed_keys_;
  static NoteStack generated_notes_;
  static VoiceAllocator poly_allocator_;
  static bool release_latched_keys_on_next_note_on_;
  static bool ignore_note_off_messages_;

  static Lfo lfo_[kNumLfos];
  static uint8_t previous_lfo_fm_[kNumLfos];
  static uint16_t lfo_step_[kNumLfos];
  static uint16_t lfo_limit_[kNumLfos];
  static uint16_t lfo_increment_[kNumLfos];

  // Sequencer stuff
  static bool arp_seq_running_;
  static uint8_t arp_seq_prescaler_;
  static uint8_t arp_seq_step_;
  static int8_t arp_note_;
  static int8_t arp_octave_;
  static int8_t arp_direction_;
  static int8_t arp_previous_note_;
  static uint16_t arp_seq_gate_length_counter_;
  static int8_t swing_amount_;
  static uint8_t internal_clock_blank_ticks_;
  static int8_t seq_transposition_;

  DISALLOW_COPY_AND_ASSIGN(Part);
};

extern Part part;

}  // namespace shruthi

#endif // SHRUTHI_PART_H_
