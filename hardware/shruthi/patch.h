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
// Patch definition. The order of the fields must match the numbering of the
// parameters defined later. Contains methods for packing/unpacking to a
// buffer of bytes (the compression is not optimal, but a more optimal
// compression that would use, for example, the MSB of all parameters in the
// 0-127 range, would result in a high code size).
// Also includes code for checking whether a buffer looks like a reasonable
// patch.

#ifndef HARDWARE_SHRUTHI_PATCH_H_
#define HARDWARE_SHRUTHI_PATCH_H_

#include "hardware/base/base.h"

namespace hardware_shruthi {

const uint8_t kPatchNameSize = 8;
const uint8_t kModulationMatrixSize = 12;
const uint8_t kPatchBankSize = 20;

struct Modulation {
  uint8_t source;
  uint8_t destination;
  int8_t amount;
};

union ModulationMatrix {
  Modulation modulation[kModulationMatrixSize];
  uint8_t raw_modulation_data[kModulationMatrixSize * 3];
};

enum SysExReceptionState {
  RECEIVING_HEADER = 0,
  RECEIVING_DATA = 1,
  RECEIVING_FOOTER = 2,

  RECEPTION_OK = 3,
  RECEPTION_ERROR = 4,
};

enum MidiOutMode {
  MIDI_OUT_OFF,
  MIDI_OUT_SOFT_THRU,
  MIDI_OUT_CONTROLLER,
  MIDI_OUT_SEQUENCER,
  MIDI_OUT_DAISY_CHAIN,
};

struct OscillatorSettings {
  uint8_t shape;
  uint8_t parameter;
  int8_t range;
  uint8_t option;
};

struct EnvelopeSettings {
  uint8_t attack;
  uint8_t decay;
  uint8_t sustain;
  uint8_t release;
};

struct LfoSettings {
  uint8_t waveform;
  uint8_t rate;
  uint8_t attack;
  uint8_t retrigger_mode;
};

const uint8_t kPatchSize = 76;

class Patch {
 public:
  // Offset: 0-8
  OscillatorSettings osc[2];

  // Offset: 8-12
  uint8_t mix_balance;
  uint8_t mix_sub_osc;
  uint8_t mix_noise;
  uint8_t mix_sub_osc_shape;

  // Offset: 12-16
  uint8_t filter_cutoff;
  uint8_t filter_resonance;
  int8_t filter_env;
  int8_t filter_lfo;

  // Offset: 16-24
  EnvelopeSettings env[2];

  // Offset: 24-32
  LfoSettings lfo[2];

  // Offset: 32-68
  ModulationMatrix modulation_matrix;
  // Offset: 68-76
  uint8_t name[kPatchNameSize];

  void EepromSave(uint8_t slot) const;
  void EepromLoad(uint8_t slot);
  void SysExSend() const;
  void SysExReceive(uint8_t sysex_byte);
  void Backup() const;
  void Restore();

  inline uint8_t sysex_reception_state() const {
    return sysex_reception_state_;
  }

 private:
  static uint8_t CheckBuffer() __attribute__((noinline));
  void Pack(uint8_t* patch_buffer) const;
  void Unpack(const uint8_t* patch_buffer);

  // Buffer in which the patch is compressed for load/save operations. The last
  // byte is for the checksum added to the stream during sysex dumps.
  static uint8_t load_save_buffer_[kPatchSize + 1];
  // Buffer used to allow the user to undo the loading of a patch (similar to
  // the "compare" function on some synths).
  static uint8_t undo_buffer_[kPatchSize];

  static uint8_t sysex_bytes_received_;
  static uint8_t sysex_reception_state_;
  static uint8_t sysex_reception_checksum_;
};

static const uint8_t kNumModulationSources = 21;
static const uint8_t kNumGlobalModulationSources = 15;
static const uint8_t kNumVoiceModulationSources = kNumModulationSources -
    kNumGlobalModulationSources;

enum ModulationSource {
  /* First the modulation sources common to all notes. */
  MOD_SRC_LFO_1 = 0,
  MOD_SRC_LFO_2,
  MOD_SRC_SEQ,
  MOD_SRC_SEQ_1,
  MOD_SRC_SEQ_2,
  MOD_SRC_STEP,
  MOD_SRC_WHEEL,
  MOD_SRC_AFTERTOUCH,
  MOD_SRC_PITCH_BEND,
  MOD_SRC_OFFSET,
  MOD_SRC_CV_1,
  MOD_SRC_CV_2,
  MOD_SRC_CV_3,
  MOD_SRC_CV_4,
  MOD_SRC_NOISE,

  /* Then those which are different for each note. */
  MOD_SRC_ENV_1 = kNumGlobalModulationSources,
  MOD_SRC_ENV_2,
  MOD_SRC_VELOCITY,
  MOD_SRC_RANDOM,
  MOD_SRC_NOTE,
  MOD_SRC_GATE,
};

enum ModulationDestination {
  MOD_DST_FILTER_CUTOFF = 0,
  MOD_DST_VCA,
  MOD_DST_PWM_1,
  MOD_DST_PWM_2,
  MOD_DST_VCO_1,
  MOD_DST_VCO_2,
  MOD_DST_VCO_1_2_FINE,
  MOD_DST_MIX_BALANCE,
  MOD_DST_MIX_NOISE,
  MOD_DST_MIX_SUB_OSC,
  MOD_DST_FILTER_RESONANCE,
  MOD_DST_CV_1,
  MOD_DST_CV_2,
  MOD_DST_2_BITS,
};

static const uint8_t kNumModulationDestinations = 14;

enum PatchParameter {
  PRM_OSC_SHAPE_1,
  PRM_OSC_PARAMETER_1,
  PRM_OSC_RANGE_1,
  PRM_OSC_OPTION_1,

  PRM_OSC_SHAPE_2,
  PRM_OSC_PARAMETER_2,
  PRM_OSC_RANGE_2,
  PRM_OSC_OPTION_2,

  PRM_MIX_BALANCE,
  PRM_MIX_SUB_OSC,
  PRM_MIX_NOISE,
  PRM_MIX_SUB_OSC_SHAPE,

  PRM_FILTER_CUTOFF,
  PRM_FILTER_RESONANCE,
  PRM_FILTER_ENV,
  PRM_FILTER_LFO,

  PRM_ENV_ATTACK_1,
  PRM_ENV_DECAY_1,
  PRM_ENV_SUSTAIN_1,
  PRM_ENV_RELEASE_1,

  PRM_ENV_ATTACK_2,
  PRM_ENV_DECAY_2,
  PRM_ENV_SUSTAIN_2,
  PRM_ENV_RELEASE_2,

  PRM_LFO_WAVE_1,
  PRM_LFO_RATE_1,
  PRM_LFO_ATTACK_1,
  PRM_LFO_RETRIGGER_1,

  PRM_LFO_WAVE_2,
  PRM_LFO_RATE_2,
  PRM_LFO_ATTACK_2,
  PRM_LFO_RETRIGGER_2,

  PRM_MOD_SOURCE,
  PRM_MOD_DESTINATION,
  PRM_MOD_AMOUNT,
  PRM_MOD_ROW,
};

enum OscillatorAlgorithm {
  WAVEFORM_NONE,
  WAVEFORM_SAW,
  WAVEFORM_SQUARE,
  WAVEFORM_TRIANGLE,
  WAVEFORM_CZ_SAW,
  WAVEFORM_CZ_RESO,
  WAVEFORM_CZ_TRIANGLE,
  WAVEFORM_CZ_PULSE,
  WAVEFORM_CZ_SYNC,
  WAVEFORM_FM,
  WAVEFORM_WAVETABLE_1,
  WAVEFORM_WAVETABLE_2,
  WAVEFORM_WAVETABLE_3,
  WAVEFORM_WAVETABLE_4,
  WAVEFORM_WAVETABLE_5,
  WAVEFORM_WAVETABLE_6,
  WAVEFORM_8BITLAND,
  WAVEFORM_DIRTY_PWM,
  WAVEFORM_FILTERED_NOISE,
  WAVEFORM_VOWEL,
};

enum LfoWave {
  // For oscillators.
  LFO_WAVEFORM_TRIANGLE,
  LFO_WAVEFORM_SQUARE,
  LFO_WAVEFORM_S_H,
  LFO_WAVEFORM_RAMP,
};

enum LfoMode {
  // For oscillators.
  LFO_MODE_FREE,
  LFO_MODE_SLAVE,
  LFO_MODE_MASTER
};

enum Status {
  OFF = 0,
  ON
};

enum OPERATOR {
  SUM = 0,
  SYNC = 1,
  RING_MOD = 2,
  XOR = 3
};

}  // namespace hardware_shruthi

#endif  // HARDWARE_SHRUTHI_PATCH_H_
