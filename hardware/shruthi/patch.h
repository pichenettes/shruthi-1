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
const uint8_t kSerializedPatchSize = 64;
const uint8_t kModulationMatrixSize = 14;
const uint8_t kSavedModulationMatrixSize = 10;

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
};

class Patch {
 public:
  uint8_t keep_me_at_the_top[1];

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

  // Offset: 24-28
  LfoSettings lfo[2];

  // Offset: 28-58, 58-70
  ModulationMatrix modulation_matrix;

  // Offset: 70-74, not saved

  uint8_t arp_tempo;
  uint8_t arp_octave;
  uint8_t arp_pattern;
  uint8_t arp_swing;

  // Offset: 74-82
  uint8_t sequence[8];

  // Offset: 82-86, not saved
  int8_t sys_octave;
  uint8_t sys_raga;
  uint8_t sys_portamento;
  uint8_t sys_legato;

  int8_t sys_master_tuning;
  uint8_t sys_midi_channel;
  uint8_t sys_midi_out_mode;
  uint8_t sys_midi_out_chain;

  // Offset: 86-94
  uint8_t name[kPatchNameSize];

  // Offset: 94, not saved
  uint8_t pattern_size;

  // Get the value of a step in the sequence.
  uint8_t sequence_step(uint8_t step) const {
    return (step & 1) ? sequence[step >> 1] << 4 : sequence[step >> 1] & 0xf0;
  }
  // Set the value of a step in the sequence.
  void set_sequence_step(uint8_t step, uint8_t value) {
    if (step & 1) {
      sequence[step >> 1] = (sequence[step >> 1] & 0xf0) | (value >> 4);
    } else {
      sequence[step >> 1] = (sequence[step >> 1] & 0x0f) | (value & 0xf0);
    }
  }

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
  static uint8_t load_save_buffer_[kSerializedPatchSize + 1];
  // Buffer used to allow the user to undo the loading of a patch (similar to
  // the "compare" function on some synths).
  static uint8_t undo_buffer_[kSerializedPatchSize];

  static uint8_t sysex_bytes_received_;
  static uint8_t sysex_reception_state_;
  static uint8_t sysex_reception_checksum_;
};

static const uint8_t kNumModulationSources = 16;
static const uint8_t kNumGlobalModulationSources = 11;
static const uint8_t kNumVoiceModulationSources = kNumModulationSources -
    kNumGlobalModulationSources;

enum ModulationSource {
  /* First the modulation sources common to all notes. */
  MOD_SRC_LFO_1 = 0,
  MOD_SRC_LFO_2,
  MOD_SRC_SEQ,
  MOD_SRC_STEP,
  MOD_SRC_WHEEL,
  MOD_SRC_PITCH_BEND,
  MOD_SRC_OFFSET,
  MOD_SRC_CV_1,
  MOD_SRC_CV_2,
  MOD_SRC_CV_3,
  MOD_SRC_RANDOM,

  /* Then those which are different for each note. */
  MOD_SRC_ENV_1 = kNumGlobalModulationSources,
  MOD_SRC_ENV_2,
  MOD_SRC_VELOCITY,
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

enum Parameter {
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
  PRM_LFO_WAVE_2,
  PRM_LFO_RATE_2,

  PRM_MOD_SOURCE = 28,
  PRM_MOD_DESTINATION = 29,
  PRM_MOD_AMOUNT = 30,
  PRM_MOD_ROW = 31,

  PRM_ARP_TEMPO = 3 * kModulationMatrixSize + 28,
  PRM_ARP_OCTAVE,
  PRM_ARP_PATTERN,
  PRM_ARP_SWING,

  PRM_SEQUENCE = 3 * kModulationMatrixSize + 28 + 4,

  PRM_SYS_OCTAVE = 3 * kModulationMatrixSize + 28 + 12,
  PRM_SYS_RAGA,
  PRM_SYS_PORTAMENTO,
  PRM_SYS_LEGATO,

  PRM_SYS_MASTER_TUNING,
  PRM_SYS_MIDI_CHANNEL,
  PRM_SYS_MIDI_OUT_MODE,
  PRM_SYS_MIDI_OUT_CHAIN,

  PRM_NAME = 3 * kModulationMatrixSize + 28 + 16,

  PRM_ARP_PATTERN_SIZE = 94
};

enum OscillatorAlgorithm {
  WAVEFORM_NONE,
  WAVEFORM_IMPULSE_TRAIN,
  WAVEFORM_SAW,
  WAVEFORM_SQUARE,
  WAVEFORM_TRIANGLE,
  WAVEFORM_CZ,
  WAVEFORM_FM,
  WAVEFORM_8BITLAND,
  WAVEFORM_DIRTY_PWM,
  WAVEFORM_FILTERED_NOISE,
  WAVEFORM_VOWEL,
  WAVEFORM_WAVETABLE,
  WAVEFORM_ANALOG_WAVETABLE,
};

enum LfoWave {
  // For oscillators.
  LFO_WAVEFORM_TRIANGLE,
  LFO_WAVEFORM_SQUARE,
  LFO_WAVEFORM_S_H,
  LFO_WAVEFORM_RAMP,
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

static const uint8_t kNumEditableParameters = 44;

static const uint8_t kNumArpeggiatorPatterns = 15;

}  // namespace hardware_shruthi

#endif  // HARDWARE_SHRUTHI_PATCH_H_
