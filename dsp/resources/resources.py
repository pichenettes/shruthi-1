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

"""----------------------------------------------------------------------------
Waveshaper/distorsion
-----------------------------------------------------------------------------"""

waveshapers = []

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


def Scale(array, min=1, max=254, center=True, dither=2):
  if center:
    array -= array.mean()
  mx = numpy.abs(array).max()
  array = (array + mx) / (2 * mx)
  array = array * (max - min) + min
  return Dither(array, order=dither)


signal_range = ((numpy.arange(0, 256) / 128.0 - 1.0))
fuzz = numpy.tanh(6.0 * signal_range) * 128.0 + 128.0
waveshapers.append(('distortion', Scale(fuzz, dither=0)))

"""----------------------------------------------------------------------------
Lookup tables for SVF
-----------------------------------------------------------------------------"""

luts = []

sr = 20000000 / 512.0
resolution = 15  # bits

cv = numpy.arange(0, 256.0)
cutoff = sr / 2 * 2 ** (-(128 - cv / 2.0) /12.0)
step = 2.0 * numpy.sin(numpy.pi * cutoff / (2 * sr))
integrator_step = numpy.round(step * (1 << resolution))
integrator_step = numpy.minimum(integrator_step, 65535)

resonance = numpy.maximum(numpy.minimum((cv - 8) / 240.0, 1.0), 0.0)
damp_factor = numpy.round(2.0 * (1.0 - resonance ** 0.25) * (1 << resolution))
damp_factor = numpy.minimum(damp_factor, 65535)

damp_stability_bound = numpy.round(
    numpy.minimum(2.0, 2.0 / step - step * 0.5) * (1 << resolution))
damp_stability_bound[damp_stability_bound == 65536] = 65535
damp_stability_bound = numpy.minimum(damp_stability_bound, 65535)

luts.append(('integrator_step', integrator_step))
luts.append(('damp_factor', damp_factor))
luts.append(('damp_stability_bound', damp_stability_bound))

resources = [
  (waveshapers, 'waveshaper', 'WAVESHAPER_RES', 'prog_uint8_t', int, True),
  (luts, 'lut', 'LUT_RES', 'prog_uint16_t', int, True)
]
