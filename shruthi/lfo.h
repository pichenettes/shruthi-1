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
//
// -----------------------------------------------------------------------------
//
// LFO (cheap oscillator).
//
// Contrary to oscillators which are templatized "static singletons", to
// generate the fastest, most specialized code, LFOs are less
// performance-sensitive and are thus implemented as a traditional class.

#ifndef SHRUTHI_LFO_H_
#define SHRUTHI_LFO_H_

#include "avrlib/base.h"
#include "shruthi/envelope.h"
#include "shruthi/patch.h"
#include "shruthi/resources.h"
#include "shruthi/sequencer_settings.h"
#include "shruthi/shruthi.h"
#include "avrlib/random.h"
#include "avrlib/op.h"

using avrlib::Random;

namespace shruthi {

class Lfo {
 public:
  Lfo() { }

  uint8_t Render(const SequencerSettings& sequence) {
    uint8_t value;

    // Ramp up the intensity envelope.
    uint16_t i = intensity_;
    if (static_cast<uint8_t>(i >> 8) != 0x3f) {
      i += intensity_increment_;
      if (static_cast<uint8_t>(i >> 8) >= 0x40) {
        i = 16383;
      }
      intensity_ = i;
    }
    
    cycle_complete_ = phase_ < phase_increment_;
    
    // Compute the LFO value.
    switch (shape_) {
      case LFO_WAVEFORM_RAMP:
        value = phase_ >> 8;
        break;
        
      case LFO_WAVEFORM_S_H:
        if (cycle_complete_) {
          value_ = Random::GetByte();
        }
        value = value_;
        break;

      case LFO_WAVEFORM_TRIANGLE:
        value = (phase_ & 0x8000) ?
            phase_ >> 7 :
            ~static_cast<uint8_t>(phase_ >> 7);
        break;

      case LFO_WAVEFORM_SQUARE:
        value = (phase_ & 0x8000) ? 255 : 0;
        break;
        
      case LFO_WAVEFORM_STEP_SEQUENCER:
        {
          uint8_t phase_to_step = phase_ >> 8;
          phase_to_step = U8U8MulShift8(phase_to_step, sequence.pattern_size);
          value = sequence.steps[phase_to_step].controller() << 4;
        }
        break;
        
      default:
        {
          uint8_t shape_offset = shape_ - LFO_WAVEFORM_WAVE_1;
          if (shape_offset == 0) {
            shape_offset = 3;
          } else {
            shape_offset += 16;
          }
          value = ResourcesManager::Lookup<uint8_t, uint8_t>(
              wav_res_waves + U8U8Mul(shape_offset, 129),
              phase_ >> 9);
        }
        break;
    }
    phase_ += phase_increment_;
    if (retrigger_mode_ == LFO_MODE_ONE_SHOT) {
      // The one-shot mode is implemented as follow: we continue running
      // the phase accumulator in the background; but the value is sampled
      // and held at the end of the first cycle.
      if (running_) {
        if (phase_ < phase_increment_) {
          running_ = false;
          // End of cycle adjustments.
          if (shape_ == LFO_WAVEFORM_RAMP ||
              shape_ == LFO_WAVEFORM_TRIANGLE ||
              shape_ == LFO_WAVEFORM_SQUARE) {
            value = 255;
          } else if (shape_ == LFO_WAVEFORM_STEP_SEQUENCER) {
            value = 0;
          }
          one_shot_value_ = value;
        }
      } else {
        value = one_shot_value_;
      }
      
      // Only positive values are generated.
      value = shape_ == LFO_WAVEFORM_STEP_SEQUENCER
          ? 128 + (value >> 1)
          : 255 - (value >> 1);
    }

    // Apply the intensity envelope.
    return S8U8MulShift8(
        static_cast<int8_t>(value) - 128,
        avrlib::U14ShiftRight6(intensity_)
    ) + 128;
  }
  
  inline void set_target_phase(uint16_t step, uint16_t increment) {
    // PLL for aligning the LFO to the phase dictated by the MIDI sync.
    uint16_t phi = phase_;
    int16_t d_error = increment - (phi - previous_phase_);
    int16_t p_error = (step * increment) - phi;
    int32_t error = 0;
    error += d_error;
    error += p_error;
    int32_t new_increment = phase_increment_ + (error >> 8);
    // The tracking range is 15 BPM .. 960 BPM.
    if (new_increment < 6) {
      new_increment = 6;
    } else if (new_increment > 1040) {
      new_increment = 1040;
    }
    phase_increment_ = new_increment;
    previous_phase_ = phi;
  }
  
  inline void set_target_increment(uint16_t increment) {
    phase_increment_ = increment;
  }

  void Reset() {
    ResetPhase();
    Trigger();
  }

  void ResetPhase() {
    phase_ = 0;
    cycle_complete_ = true;
    running_ = true;
  }

  void Trigger() {
    if (retrigger_mode_) {
      ResetPhase();
    }
    intensity_ = 0;
  }

  void Update(uint8_t shape, uint16_t phase_increment,
              uint8_t attack, uint8_t retrigger_mode) {
    shape_ = shape;
    if (phase_increment) {
      phase_increment_ = phase_increment;
    }
    intensity_increment_ = ResourcesManager::Lookup<
        uint16_t, uint8_t>(lut_res_env_portamento_increments, attack) >> 1;
    retrigger_mode_ = retrigger_mode;
  }
  
  bool triggered() const { return cycle_complete_; }

 private:
  // Phase increment.
  uint16_t phase_increment_;
  uint16_t previous_phase_;
  uint16_t intensity_increment_;
  uint16_t target_increment_;
  uint16_t intensity_;

  // Current phase of the lfo.
  uint16_t phase_;

  // Copy of the shape used by this lfo.
  uint8_t shape_;
  uint8_t retrigger_mode_;
  bool cycle_complete_;
  bool running_;
  
  // Current value of S&H.
  uint8_t value_;
  uint8_t one_shot_value_;
  uint8_t step_;
  
  DISALLOW_COPY_AND_ASSIGN(Lfo);
};

}  // namespace shruthi

#endif // SHRUTHI_LFO_H_
