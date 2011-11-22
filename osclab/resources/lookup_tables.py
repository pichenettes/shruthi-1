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
notes = numpy.arange(116 * 128.0, 128 * 128.0, 2)
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


"""----------------------------------------------------------------------------
MinBLEP
----------------------------------------------------------------------------"""

NUM_ZERO_CROSSINGS = 16
OVERSAMPLING = 256
THRESHOLD = 15

def minimum_phase_reconstruction(signal, fft_size=32768):
  Xf = numpy.fft.fft(signal, fft_size)
  real_cepstrum = numpy.fft.ifft(numpy.log(1e-50 + numpy.abs(Xf))).real
  real_cepstrum[1:fft_size / 2] *= 2
  real_cepstrum[fft_size / 2 + 1:] = 0
  min_phi = numpy.fft.ifft(numpy.exp(numpy.fft.fft(real_cepstrum))).real
  return min_phi


n = NUM_ZERO_CROSSINGS * OVERSAMPLING * 2 + 1
t = numpy.arange(0, n)
sinc = numpy.sinc(-NUM_ZERO_CROSSINGS + 2.0 * t / (n - 1) * NUM_ZERO_CROSSINGS)
windowed_sinc = sinc * numpy.blackman(n)
blep = minimum_phase_reconstruction(windowed_sinc)[:n]
blep = numpy.cumsum(blep)
blep = 1.0 - (blep / blep[-1])
blep_s2_14 = (blep * 16384).round().astype(numpy.int16)
last_sample = numpy.max(numpy.where(numpy.abs(blep_s2_14) > THRESHOLD)[0])
blep_s2_14 = blep_s2_14[:last_sample + 1]

lookup_tables.append(
    ('blep', blep_s2_14.astype(int))
)


"""----------------------------------------------------------------------------
Reciprocal
----------------------------------------------------------------------------"""

x = numpy.arange(0, 256)
x[0] = 1
x = 65535 / x

lookup_tables.append(
    ('reciprocal', x.astype(int))
)
