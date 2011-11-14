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

namespace = 'osclab'
target = 'osclab'
modifier = 'PROGMEM'
types = ['uint8_t', 'uint16_t']
includes = """
#include "avrlib/base.h"

#include <avr/pgmspace.h>
"""
create_specialized_manager = True


import lookup_tables
import waveforms

strings = """
none
saw
square
triang
zsaw
zreso
ztri
zpulse
zsync
pad
fm
waves
tampur
digitl
metall
bowed
slap
organ
male
user
8bits
crush
pwm
noise
vowel
belish
polatd
cello
clpswp
female
fmtvoc
frmnt2
res3hp
electp
vibes
"""

resources = [
  (strings,
   'string', 'STR_RES', 'prog_char', str, False),
  (lookup_tables.lookup_tables,
   'lookup_table', 'LUT_RES', 'prog_uint16_t', int, False),
  (waveforms.waveforms,
   'waveform', 'WAV_RES', 'prog_uint8_t', int, True)
]
