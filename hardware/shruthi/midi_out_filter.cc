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
// Instance of the midi out filter class.

#include "hardware/shruthi/midi_out_filter.h"

namespace hardware_shruthi {

/* static */
uint8_t MidiOutFilter::mode_;

/* static */
uint8_t MidiOutFilter::channel_;

/* static */
uint8_t MidiOutFilter::current_parameter_index_;

MidiOutFilter midi_out_filter;

}  // namespace hardware_shruthi
