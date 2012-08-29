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

sample_rate = 20000000.0 / 510
control_rate = sample_rate / 40.0
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
max_time = 12.0  # seconds
min_time = 3.0 / control_rate  # seconds
excursion = 65535.0
gamma = 0.175
min_increment = excursion / (max_time * control_rate)
max_increment = excursion / (min_time * control_rate)

rates = numpy.linspace(numpy.power(max_increment, -gamma),
                       numpy.power(min_increment, -gamma), num_values)

values = numpy.power(rates, -1/gamma).astype(int)
slow_values = numpy.arange(num_values + 2, 2, -1) / 2
i = num_values - 1
while slow_values[i] != values[i]:
  values[i] = slow_values[i]
  i -= 1
values[0] = 65535
lookup_tables.append(
    ('env_portamento_increments', values)
)

# Create table for pitch.
a4_midi = 69
a4_pitch = 440.0
excursion = 65536.0
notes = numpy.arange(116 * 128.0, 128 * 128.0 + 16, 16)
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
  ('!', '!', '!', '!', 100),
]

def DecodeShrutiChart(line):
  values = [
      's',
      'r1',
      'r2',
      'r3',
      'r4',
      'g1',
      'g2',
      'g3',
      'g4',
      'm1',
      'm2',
      'm3',
      'm4',
      'p',
      'd1',
      'd2',
      'd3',
      'd4',
      'n1',
      'n2',
      'n3',
      'n4'
  ]
  decoded = []
  for i, x in enumerate(line):
    if x != '-':
      decoded.append(values[i])
  return ' '.join(decoded)


"""----------------------------------------------------------------------------
A recommended key on the keyboard for each of the swara.

From:
http://commons.wikimedia.org/wiki/Melakarta_ragams_(svg)
----------------------------------------------------------------------------"""

recommended_keys = {
  's': 0,
  'r1': 1,
  'r2': 1,
  'r3': 2,
  'r4': 2,
  'g1': 3,
  'g2': 3,
  'g3': 4,
  'g4': 4,
  'm1': 5,
  'm2': 6,
  'm3': 6,
  'm4': 6,
  'p': 7,
  'd1': 8,
  'd2': 8,
  'd3': 9,
  'd4': 9,
  'n1': 10,
  'n2': 10,
  'n3': 11,
  'n4': 11
}


shruti_dictionary = {}
for entry in shrutis:
  for name in entry[:-1]:
    shruti_dictionary[name] = entry[-1]


def Compute(scale):
  """Translate a list of 12 note/swaras names into pitch corrections."""
  values = [shruti_dictionary.get(x) for x in scale.split(' ')]
  equal = 2 ** (numpy.arange(12.0) / 12.0)
  shifts = (numpy.log2(values / equal) * 12 * 128).astype(int)
  silences = numpy.where(shifts > 127)
  if len(silences[0]):
    shifts[silences[0]] = 32767
  return shifts


def LayoutRaga(raga, silence_other_notes=False):
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
      if silence_other_notes:
        mapping[i] = '!'
      else:
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
    ('bhairav',
     LayoutRaga(DecodeShrutiChart('sr-----g-m---pd-----n-'), True)),
    ('gunakri',
     LayoutRaga(DecodeShrutiChart('s-r------m---p-d------'), True)),
    ('marwa',
     LayoutRaga(DecodeShrutiChart('s-r----g---m----d---n-'), True)),
    ('shree',
     LayoutRaga(DecodeShrutiChart('sr-----g---m-pd-----n-'), True)),
    ('purvi',
     LayoutRaga(DecodeShrutiChart('s-r----g---m-p-d----n-'), True)),
    ('bilawal',
     LayoutRaga(DecodeShrutiChart('s---r--g-m---p---d--n-'), True)),
    ('yaman',
     LayoutRaga(DecodeShrutiChart('s---r---g---mp---d---n'), True)),
    ('kafi',
     LayoutRaga(DecodeShrutiChart('s--r-g---m---p--d-n---'), True)),
    ('bhimpalasree',
     LayoutRaga(DecodeShrutiChart('s---r-g--m---p---d-n--'), True)),
    ('darbari',
     LayoutRaga(DecodeShrutiChart('s---rg---m---pd---n---'), True)),
    ('bageshree',
     LayoutRaga(DecodeShrutiChart('s--r-g---m---p--d-n---'), True)),
    ('rageshree',
     LayoutRaga(DecodeShrutiChart('s---r--g-m---p--d-n---'), True)),
    ('khamaj',
     LayoutRaga(DecodeShrutiChart('s---r--g-m---p---dn--n'), True)),
    ('mi\'mal',
     LayoutRaga(DecodeShrutiChart('s---rg---m---p--d-n-n-'), True)),
    ('parameshwari',
     LayoutRaga(DecodeShrutiChart('sr---g---m------d-n---'), True)),
    ('rangeshwari',
     LayoutRaga(DecodeShrutiChart('s---rg---m---p------n-'), True)),
    ('gangeshwari',
     LayoutRaga(DecodeShrutiChart('s------g-m---pd---n---'), True)),
    ('kameshwari',
     LayoutRaga(DecodeShrutiChart('s---r------m-p--d-n---'), True)),
    ('palas kafi',
     LayoutRaga(DecodeShrutiChart('s---rg---m---p---dn---'), True)),
    ('natbhairav',
     LayoutRaga(DecodeShrutiChart('s---r--g-m---pd-----n-'), True)),
    ('m.kauns',
     LayoutRaga(DecodeShrutiChart('s---r---gm----d---n---'), True)),
    ('bairagi',
     LayoutRaga(DecodeShrutiChart('sr-------m---p----n---'), True)),
    ('b.todi',
     LayoutRaga(DecodeShrutiChart('sr---g-------p----n---'), True)),
    ('chandradeep',
     LayoutRaga(DecodeShrutiChart('s----g---m---p----n---'), True)),
    ('kaushik todi',
     LayoutRaga(DecodeShrutiChart('s----g---m-m--d-------'), True)),
    ('jogeshwari',
     LayoutRaga(DecodeShrutiChart('s----g-g-m------d-n---'), True)),
    ('rasia',
     LayoutRaga(DecodeShrutiChart('s---r---g---mp---d---n'), True)),
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


lookup_tables.append(
    ('turbo_tempi', [270, 300, 330, 360, 420, 480, 600, 720, 960]))

"""----------------------------------------------------------------------------
Groove templates
----------------------------------------------------------------------------"""

def ConvertGrooveTemplate(values):
  # Center
  values = numpy.array(values)
  values -= values.mean()
  # Scale
  scale = numpy.abs(values).max() / 127.0
  values /= scale
  values = values.astype(int)
  # Fix rounding error
  values[8] -= values.sum()
  return values

lookup_tables.extend([
    ('groove_swing', ConvertGrooveTemplate(
      [1, 1, -1, -1, 1, 1, -1, -1, 1, 1, -1, -1, 1, 1, -1, -1])),
    ('groove_shuffle', ConvertGrooveTemplate(
      [1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1])),
    ('groove_push', ConvertGrooveTemplate(
      [-0.5, -0.5, 1, 0, -1, 0, 0, 0.7, 0, 0, 0.7, -0.4, -0.7, 0, 0.7, 0.0])),
    ('groove_lag', ConvertGrooveTemplate(
      [0.1, 0.2, 0.4, 0, 0.15, -0.2, -0.35, -0.5,
       0.5, 0.15, -0.4, -0.2, 0.45, -0.2, 0.4, -0.2])),
    ('groove_human', ConvertGrooveTemplate(
      [0.7, -0.8, 0.85, -0.75, 0.7, -0.7,  0.4, -0.3,
       0.5, -0.7, 0.8, -0.75, 0.8, -1, 0.5, -0.25])),
    ('groove_monkey', ConvertGrooveTemplate(
      [0.5, -0.6, 0.6, -0.8, 0.6, -0.7, 0.8, -0.7,
       0.4, -0.5, 0.9, -0.6, 0.9, -0.8, 0.6, -0.6]))])
 