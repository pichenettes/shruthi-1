#!/usr/bin/python2.5
#
# Copyright 2009 Olivier Gillet.
#
# Author: Olivier Gillet (ol.gillet@gmail.com)
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
# -----------------------------------------------------------------------------
#
# Lookup table definitions.

import numpy

sample_rate = 20000000.0 / 510
control_rate = sample_rate / 40.0

# Create table for pitch.
a4_midi = 69
a4_pitch = 440.0
excursion = 65536.0
pitch_table_start = 108
notes = numpy.arange(
    pitch_table_start * 128.0, (pitch_table_start + 12) * 128.0, 2)
pitches = a4_pitch * 2 ** ((notes - a4_midi * 128) / (128 * 12))
increments = excursion / sample_rate * pitches

lookup_tables = [
    ('oscillator_increments', increments.astype(int))
]


"""----------------------------------------------------------------------------
Table with FM modulation frequency ratios. This is taken from the
DX21 manual (http://www.maths.abdn.ac.uk/~bensondj/dx7/manuals/dx21-man.pdf),
with less details in the highest frequencies. Added: slight variations in
pitch to create phasing/detune effects, low octaves, and 7/4, 9/4 that I really
like.
----------------------------------------------------------------------------"""

fm_frequency_ratios = numpy.array(
[ 0.125,
  0.25,
  0.5,
  0.5 * 2 ** (16 / 1200.0),
  numpy.sqrt(2) / 2,
  numpy.pi / 4,
  1.0,
  1.0 * 2 ** (8 / 1200.0),
  numpy.sqrt(2),
  numpy.pi / 2,
  7.0 / 4,
  2,
  2 * 2 ** (8 / 1200.0),
  9.0 / 4,
  11.0 / 4,
  2 * numpy.sqrt(2),
  3,
  numpy.pi,
  numpy.sqrt(3) * 2,
  4,
  numpy.sqrt(2) * 3,
  numpy.pi * 3 / 2,
  5,
  numpy.sqrt(2) * 4,
  8]
)

lookup_tables.append(
    ('fm_frequency_ratios', (fm_frequency_ratios * 256).astype(int))
)
