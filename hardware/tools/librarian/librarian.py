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
# Text-editor based patch librarian.
#
# To save patches from the Shruti-1:
#   make eeprom_backup
#
# To dump/disassemble the patch data:
#   python hardware/tools/librarian/librarian.py -d \
#       hardware/shruti/data/patch_library.hex > library.txt
#
# library.txt contains the patches, one line per patch.
# You can edit it, archive it, copy/paste patches from other people etc, post
# them on twitter, whatever.
#
# To create a patch library for the Shruti-1, put 16 lines of patches in a text
# file, and create a .hex file from it.
#   python hardware/tools/librarian/librarian.py -c \
#       library.txt > hardware/shruti/data/patch_library.hex
#
# And upload the resulting file to the Shruti-1:
#   make eeprom_restore


"""Converts a patch to a copy-and-paste friendly text format."""

import logging
import optparse
import os
import sys

# Allows the code to be run from the project root directory
sys.path.append('.')

NAME_LEN = 8
PATCH_SIZE = 64
EEPROM_SIZE = 1024
DATA_SIZE = PATCH_SIZE - NAME_LEN

from hardware.tools.hexfile import hexfile


if __name__ == '__main__':
  parser = optparse.OptionParser()
  parser.add_option(
      '-c',
      '--compile',
      dest='compile',
      action='store_true',
      help='Converts from an edited text file to a dump .hex file')
  parser.add_option(
      '-d',
      '--dump',
      dest='compile',
      action='store_false',
      help='Converts from a dump .hex file to an editable text file')
  
  options, args = parser.parse_args()
  if len(args) != 1:
    logging.fatal('Specify one, and only one eeprom .hex file!')
    sys.exit(1)

  if not options.compile:
    data = hexfile.LoadHexFile(file(args[0]))
    if not data:
      logging.fatal('Error while loading .hex file')
      sys.exit(2)

    if len(data) != EEPROM_SIZE:
      logging.fatal('Eeprom data must be 1024 bytes long')
      sys.exit(1)
  
    for offset in range(0, EEPROM_SIZE, PATCH_SIZE):
      name = ''.join(
          map(chr, data[offset + PATCH_SIZE - NAME_LEN:offset + PATCH_SIZE]))
      hex_data = ''.join(
          '%02x' % x for x in data[offset:offset + PATCH_SIZE - NAME_LEN])
      print name + '\t' + hex_data
  else:
    blob = []
    for line in file(args[0]):
      name, data = line.strip().split('\t')
      name = name[:NAME_LEN]
      name = name + ' ' * (len(name) - NAME_LEN)
      assert len(name) == NAME_LEN
      assert len(data) == DATA_SIZE * 2
      data = [int(data[x:x+2], 16) for x in xrange(0, DATA_SIZE * 2, 2)]
      data += map(ord, name)
      assert len(data) == PATCH_SIZE
      blob += data
    assert len(blob) == EEPROM_SIZE
    hexfile.WriteHexFile(blob, sys.stdout)
