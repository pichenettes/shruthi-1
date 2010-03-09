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

"""----------------------------------------------------------------------------
LFO and envelope increments.
----------------------------------------------------------------------------"""

lookup_tables = []

sample_rate = 39062.0
control_rate = sample_rate / 32
min_frequency = 1.0 / 16.0  # Hertz
max_frequency = 100.0  # Hertz

excursion = 65536
num_values = 128
min_increment = excursion * min_frequency / control_rate
max_increment = excursion * max_frequency / control_rate

rates = numpy.linspace(numpy.log(min_increment),
                       numpy.log(max_increment), num_values)

lookup_tables.append(
    ('lfo_increments', numpy.exp(rates).astype(int))
)


# Create lookup table for envelope times (x^0.25).
max_time = 4.0  # seconds
min_time = 1.0 / control_rate  # seconds
excursion = 32767.0
gamma = 0.25
min_increment = excursion / (max_time * control_rate)
max_increment = excursion / (min_time * control_rate)
          
rates = numpy.linspace(numpy.power(max_increment, -gamma),
                       numpy.power(min_increment, -gamma), num_values)

lookup_tables.append(
    ('env_portamento_increments', numpy.power(rates, -1/gamma).astype(int))
)

# Create table for pitch.
a4_midi = 69
a4_pitch = 440.0
excursion = 65536.0
notes = numpy.arange(96 * 128.0, (96 + 12) * 128.0, 2)
pitches = a4_pitch * 2 ** ((notes - a4_midi * 128) / (128 * 12))
increments = excursion / sample_rate * pitches

lookup_tables.append(
    ('oscillator_increments', increments.astype(int))
)


"""----------------------------------------------------------------------------
Table with FM modulation frequency ratios. This is taken from the
DX21 manual (http://www.maths.abdn.ac.uk/~bensondj/dx7/manuals/dx21-man.pdf),
with less details in the highest frequencies. Added: slight variations in
pitch to create phasing/detune effects, low octaves, and 7/4, 9/4 that I really
like.
----------------------------------------------------------------------------"""

fm_frequency_ratios = numpy.array([
  0.125,
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
  8,
])

lookup_tables.append(
    ('fm_frequency_ratios', (fm_frequency_ratios * 256).astype(int))
)


"""----------------------------------------------------------------------------
List of 22 shrutis with different notation schemes.

The most common notation scheme is in the 3th column.
----------------------------------------------------------------------------"""

shrutis = [
  # Swara ref 1, Swara ref 2, Swara, Swara (carnatic, common), Just, Ratio
  ('S', 'sa', 's', 'C', 1),
  ('r1', 'ra', 'r1', '?', 256.0/243.0),
  ('r2', 'ri', 'r2', 'C#', 16.0/15.0),
  ('R1', 'ru', 'r3', '?', 10.0/9.0),
  ('R2', 're', 'r4', 'D', 9.0/8.0),
  ('g1', 'ga', 'g1', 'pD#', 32.0/27.0),
  ('g2', 'gi', 'g2', 'D#', 6.0/5.0),
  ('G1', 'gu', 'g3', 'E', 5.0/4.0),
  ('G2', 'ge', 'g4', 'pE', 81.0/64.0),
  ('m1', 'ma', 'm1', 'F', 4.0/3.0),
  ('m2', 'mi', 'm2', '?', 27.0/20.0),
  ('M1', 'mu', 'm3', 'F#', 45.0/32.0),
  ('M2', 'me', 'm4', '?', 729.0/512.0),
  ('P', 'pa', 'p', 'G', 3.0/2.0),
  ('d1', 'dha', 'd1', '?', 128.0/81.0),
  ('d2', 'dhi', 'd2', 'G#', 8.0/5.0),
  ('D1', 'dhu', 'd3', 'A', 5.0/3.0),
  ('D2', 'dhe', 'd4', '?', 27.0/16.0),
  ('n1', 'na', 'n1', 'A#', 16.0/9.0),
  ('n2', 'ni', 'n2', '?', 9.0/5.0),
  ('N1', 'nu', 'n3', 'B', 15.0/8.0),
  ('N2', 'ne', 'n4', 'pB', 243.0/128.0),
]


"""----------------------------------------------------------------------------
A recommended key on the keyboard for each of the swara.

From:
http://commons.wikimedia.org/wiki/Melakarta_ragams_(svg)
----------------------------------------------------------------------------"""
recommended_keys = {
  's': 0,
  'r1': 1,
  'r2': 2,
  'r3': 3,
  'g1': 2,
  'g2': 3,
  'g3': 4,
  'm1': 5,
  'm2': 6,
  'p': 7,
  'd1': 8,
  'd2': 9,
  'd3': 10,
  'n1': 9,
  'n2': 10,
  'n3': 11 
}

shruti_dictionary = {}
for entry in shrutis:
  for name in entry[:-1]:
    shruti_dictionary[name] = entry[-1]


def Compute(scale):
  """Translate a list of 12 note/swaras names into pitch corrections."""
  values = [shruti_dictionary.get(x) for x in scale.split(' ')]
  equal = 2 ** (numpy.arange(12.0) / 12.0)
  return (numpy.log2(values / equal) * 12 * 128).astype(int)


def LayoutRaga(raga):
  """Find a good assignments of swaras to keys for a raga."""
  raga = raga.lower()
  scale = numpy.zeros((12,))
  mapping = ['' for i in range(12)]
  for swara in raga.split(' '):
    key = recommended_keys.get(swara)
    mapping[key] = swara

  # Fill unassigned notes
  for i, n in enumerate(mapping):
    if n == '':
      candidates = []
      for swara, key in recommended_keys.items():
        if key == i:
          candidates.append(swara)
      for candidate in candidates:
        if candidate[0] != mapping[i - 1]:
          mapping[i] = candidate
          break
      else:
        mapping[i] = candidates[0]
  
  scale = [shruti_dictionary.get(swara) for swara in mapping]
  return Compute(' '.join(mapping))


altered_e_b = [0, 0, 0, 0, -64, 0, 0, 0, 0, 0, 0, -64]
altered_e = [0, 0, 0, 0, -64, 0, 0, 0, 0, 0, 0, 0]
altered_e_a = [0, 0, 0, 0, -64, 0, 0, 0, 0, -64, 0, 0]

scales = [
    ('just', Compute('C C# D D# E F F# G G# A A# B')),
    ('pythagorean', Compute('C C# D pD# pE F F# G G# A A# pB')),
    ('1/4 eb', numpy.array(altered_e_b, dtype=int)),
    ('1/4 e', numpy.array(altered_e, dtype=int)),
    ('1/4 ea', numpy.array(altered_e_a, dtype=int)),
    ('kanakangi', LayoutRaga('S R1 G1 M1 P D1 N1')),
    ('ratnangi', LayoutRaga('S R1 G1 M1 P D1 N2')),
    ('ganamurti', LayoutRaga('S R1 G1 M1 P D1 N3')),
    ('vanaspati', LayoutRaga('S R1 G1 M1 P D2 N2')),
    ('manavati', LayoutRaga('S R1 G1 M1 P D2 N3')),
    ('tanarupi', LayoutRaga('S R1 G1 M1 P D3 N3')),
    ('senavati', LayoutRaga('S R1 G2 M1 P D1 N1')),
    ('hanumatodi', LayoutRaga('S R1 G2 M1 P D1 N2')),
    ('dhenuka', LayoutRaga('S R1 G2 M1 P D1 N3')),
    ('natakapriya', LayoutRaga('S R1 G2 M1 P D2 N2')),
    ('kokilapriya', LayoutRaga('S R1 G2 M1 P D2 N3')),
    ('rupavati', LayoutRaga('S R1 G2 M1 P D3 N3')),
    ('gayakapriya', LayoutRaga('S R1 G3 M1 P D1 N1')),
    ('vakulabharanam', LayoutRaga('S R1 G3 M1 P D1 N2')),
    ('mayamalavagowla', LayoutRaga('S R1 G3 M1 P D1 N3')),
    ('chakravakam', LayoutRaga('S R1 G3 M1 P D2 N2')),
    ('suryakantam', LayoutRaga('S R1 G3 M1 P D2 N3')),
    ('hatakambari', LayoutRaga('S R1 G3 M1 P D3 N3')),
    ('jhankaradhwani', LayoutRaga('S R2 G2 M1 P D1 N1')),
    ('natabhairavi', LayoutRaga('S R2 G2 M1 P D1 N2')),
    ('keeravani', LayoutRaga('S R2 G2 M1 P D1 N3')),
    ('kharaharapriya', LayoutRaga('S R2 G2 M1 P D2 N2')),
    ('gourimanohari', LayoutRaga('S R2 G2 M1 P D2 N3')),
    ('varunapriya', LayoutRaga('S R2 G2 M1 P D3 N3')),
    ('mararanjani', LayoutRaga('S R2 G3 M1 P D1 N1')),
    ('charukesi', LayoutRaga('S R2 G3 M1 P D1 N2')),
    ('sarasangi', LayoutRaga('S R2 G3 M1 P D1 N3')),
    ('harikambhoji', LayoutRaga('S R2 G3 M1 P D2 N2')),
    ('dheerasankarabharanam', LayoutRaga('S R2 G3 M1 P D2 N3')),
    ('naganandini', LayoutRaga('S R2 G3 M1 P D3 N3')),
    ('yagapriya', LayoutRaga('S R3 G3 M1 P D1 N1')),
    ('ragavardhini', LayoutRaga('S R3 G3 M1 P D1 N2')),
    ('gangeyabhushani', LayoutRaga('S R3 G3 M1 P D1 N3')),
    ('vagadheeswari', LayoutRaga('S R3 G3 M1 P D2 N2')),
    ('shulini', LayoutRaga('S R3 G3 M1 P D2 N3')),
    ('chalanata', LayoutRaga('S R3 G3 M1 P D3 N3')),
    ('salagam', LayoutRaga('S R1 G1 M2 P D1 N1')),
    ('jalarnavam', LayoutRaga('S R1 G1 M2 P D1 N2')),
    ('jhalavarali', LayoutRaga('S R1 G1 M2 P D1 N3')),
    ('navaneetam', LayoutRaga('S R1 G1 M2 P D2 N2')),
    ('pavani', LayoutRaga('S R1 G1 M2 P D2 N3')),
    ('raghupriya', LayoutRaga('S R1 G1 M2 P D3 N3')),
    ('gavambhodi', LayoutRaga('S R1 G2 M2 P D1 N1')),
    ('bhavapriya', LayoutRaga('S R1 G2 M2 P D1 N2')),
    ('shubhapantuvarali', LayoutRaga('S R1 G2 M2 P D1 N3')),
    ('shadvidamargini', LayoutRaga('S R1 G2 M2 P D2 N2')),
    ('suvarnangi', LayoutRaga('S R1 G2 M2 P D2 N3')),
    ('divyamani', LayoutRaga('S R1 G2 M2 P D3 N3')),
    ('dhavalambari', LayoutRaga('S R1 G3 M2 P D1 N1')),
    ('namanarayani', LayoutRaga('S R1 G3 M2 P D1 N2')),
    ('kamavardani', LayoutRaga('S R1 G3 M2 P D1 N3')),
    ('ramapriya', LayoutRaga('S R1 G3 M2 P D2 N2')),
    ('gamanashrama', LayoutRaga('S R1 G3 M2 P D2 N3')),
    ('vishwambari', LayoutRaga('S R1 G3 M2 P D3 N3')),
    ('shamalangi', LayoutRaga('S R2 G2 M2 P D1 N1')),
    ('shanmukhapriya', LayoutRaga('S R2 G2 M2 P D1 N2')),
    ('simhendramadhyamam', LayoutRaga('S R2 G2 M2 P D1 N3')),
    ('hemavati', LayoutRaga('S R2 G2 M2 P D2 N2')),
    ('dharmavati', LayoutRaga('S R2 G2 M2 P D2 N3')),
    ('neetimati', LayoutRaga('S R2 G2 M2 P D3 N3')),
    ('kantamani', LayoutRaga('S R2 G3 M2 P D1 N1')),
    ('rishabhapriya', LayoutRaga('S R2 G3 M2 P D1 N2')),
    ('latangi', LayoutRaga('S R2 G3 M2 P D1 N3')),
    ('vachaspati', LayoutRaga('S R2 G3 M2 P D2 N2')),
    ('mechakalyani', LayoutRaga('S R2 G3 M2 P D2 N3')),
    ('chitrambari', LayoutRaga('S R2 G3 M2 P D3 N3')),
    ('sucharitra', LayoutRaga('S R3 G3 M2 P D1 N1')),
    ('jyotiswarupini', LayoutRaga('S R3 G3 M2 P D1 N2')),
    ('dhatuvardani', LayoutRaga('S R3 G3 M2 P D1 N3')),
    ('nasikabhushani', LayoutRaga('S R3 G3 M2 P D2 N2')),
    ('kosalam', LayoutRaga('S R3 G3 M2 P D2 N3')),
    ('rasikapriya', LayoutRaga('S R3 G3 M2 P D3 N3')),
]

strings = ''
for scale, values in scales:
  strings += '\n' + scale[:6]
  lookup_tables.append(('scale_%s' % scale, values))


"""----------------------------------------------------------------------------
Arpeggiator patterns
----------------------------------------------------------------------------"""

def XoxTo16BitInt(pattern):
  uint16 = 0
  i = 0
  for char in pattern:
    if char == 'o':
      uint16 += (2 ** i)
      i += 1
    elif char == '-':
      i += 1
  assert i == 16
  return uint16


def ConvertPatterns(patterns):
  return [XoxTo16BitInt(pattern) for pattern in patterns]


lookup_tables.append(
  ('arpeggiator_patterns', ConvertPatterns([
      'o-o- o-o- o-o- o-o-',
      'ooo- ooo- ooo- ooo-',
      'o-o- oooo o-o- oooo',
      'o-o- oo-o o-o- oo-o',
      'oooo -oo- oooo -oo-',

      'o--o ---- o--o ----',
      'o--o --o- o--o --o-',
      'o--o --o- -o-- o-o-',
      'o-o- -o-- o--o --o-',
      'oo-o o-oo oo-o o-oo',
      
      'oooo o-oo -oo- ooo-',
      'o--- o--- o--o -o-o',
      'o--o o--- o-o- o-oo',
      'o--- --oo oooo -oo-',
      'o--- ---- o--- o-oo',
      ])))
