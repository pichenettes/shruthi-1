#!/usr/bin/python2.5
#
# Copyright 2011 Olivier Gillet.
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
# Master resources file.

header = """// Copyright 2011 Olivier Gillet.
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
// Resources definitions.
//
// Automatically generated with:
// make resources
"""

namespace = 'dsp'
target = 'dsp'
modifier = 'PROGMEM'
types = ['uint8_t', 'uint16_t']
includes = """
#include "avrlib/base.h"

#include <avr/pgmspace.h>
"""
create_specialized_manager = False


import numpy

luts = []
waveforms = []

"""----------------------------------------------------------------------------
Waveshaper/distortion
-----------------------------------------------------------------------------"""
def Dither(x, order=0, type=numpy.uint8):
  for i in xrange(order):
    x = numpy.hstack((numpy.zeros(1,), numpy.cumsum(x)))
  x = numpy.round(x)
  for i in xrange(order):
    x = numpy.diff(x)
  if any(x < numpy.iinfo(type).min) or any(x > numpy.iinfo(type).max):
    print 'Clipping occurred!'
  x[x < numpy.iinfo(type).min] = numpy.iinfo(type).min
  x[x > numpy.iinfo(type).max] = numpy.iinfo(type).max
  return x.astype(type)


def Scale(array, min=1, max=254, center=True, dither=2, type=numpy.uint16):
  if center:
    array -= array.mean()
  mx = numpy.abs(array).max()
  array = (array + mx) / (2 * mx)
  array = array * (max - min) + min
  return Dither(array, order=dither, type=type)


signal_range = ((numpy.arange(0, 4096) / 2047.0 - 1.0))
fuzz = numpy.tanh(9.0 * signal_range)
fold = numpy.sin(numpy.pi * fuzz)
luts.append(('distortion', Scale(fuzz, min=1, max=4094, type=numpy.uint16, dither=0)))
luts.append(('fold', Scale(fold, min=1, max=4094, type=numpy.uint16, dither=0)))

"""----------------------------------------------------------------------------
Lookup tables for LPF
-----------------------------------------------------------------------------"""
sr = 20000000 / 510.0
cv = numpy.arange(0, 256.0)
cutoff = numpy.minimum(sr / 2, 1.5 * sr / 2 * 2 ** (-(128 - cv / 2.0) / 12.0))
# The correct scale for cutoff is the following:
# omega = 2 * numpy.pi * cutoff / sr
# s = numpy.sin(omega)
# c = numpy.cos(omega)
# t = numpy.tan((omega - numpy.pi) / 4)
# alpha = 1 + t / (s - c * t)
# integrator_gain = numpy.round(65535 * alpha)

# However, we use the lazier scale here because it has two nice properties:
# - The self-oscillation sine wave is correctly tuned
# - With cutoff set to its maximum the filter behaves as the identity operator,
#   rather than a low-pass with fc at nyquist.
integrator_gain = numpy.round(65535 * cutoff / sr * 2)
luts.append(('integrator_gain', integrator_gain))

resonance_curve = 256.0 * ((cv / 256.0) ** 0.4)
waveforms.append(('resonance_response', resonance_curve))

"""----------------------------------------------------------------------------
Lookup tables for comb filter
-----------------------------------------------------------------------------"""
sr = 20000000 / 510.0
cutoff = sr / 2 * 2 ** (-(128 - cv / 2.0) / 12.0)

delays = numpy.round(numpy.minimum(1024, sr / cutoff))
luts.append(('comb_delays', delays))

"""----------------------------------------------------------------------------
Lookup tables for ring modulator
-----------------------------------------------------------------------------"""
sine = -numpy.sin(numpy.arange(257) / float(256) * 2 * numpy.pi) * 127.5 + 127.5
waveforms.append(('sine', Scale(sine)))
increments = 65536 * (cutoff / 2) / sr
luts.append(('phase_increment', increments))

"""----------------------------------------------------------------------------
Lookup tables for delays
-----------------------------------------------------------------------------"""
minimum_delay = 0.05 ** 0.5
durations = sr * (minimum_delay + (1 - minimum_delay) * (cv / 256.0)) ** 2
decimation = numpy.ceil(durations / 1279)
filter_gain = numpy.ceil(255 / decimation)
delay_line_size = numpy.round(durations / decimation)
luts.append(('delay_duration', delay_line_size))
luts.append(('delay_decimation', decimation))
luts.append(('delay_filter_gain', filter_gain))
luts.append(('delay_phase_scaling', 65536.0 / decimation))

tempo = numpy.arange(40.0, 721.0)
whole_note_duration = 240.0 / tempo
durations = sr * 3.0 * whole_note_duration / 16.0
decimation = numpy.ceil(durations / 1279)
delay_line_size = numpy.round(durations / decimation)
filter_gain = numpy.ceil(255 / decimation)
luts.append(('tap_delay_duration', delay_line_size))
luts.append(('tap_delay_decimation', decimation))
luts.append(('tap_delay_filter_gain', filter_gain))
  
"""----------------------------------------------------------------------------
Lookup tables for looper pitch shifting ratio
-----------------------------------------------------------------------------"""
ratio = numpy.round(256.0 * 2 ** ((cv - 128.0) / 48.0))
luts.append(('pitch_ratio', ratio))

resources = [
  (waveforms, 'waveform', 'WAVEFORM_RES', 'prog_uint8_t', int, True),
  (luts, 'lut', 'LUT_RES', 'prog_uint16_t', int, True)
]
