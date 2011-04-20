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

"""Tool for "reassembling" a backup .Syx file.

usage:
  python reassemble_backup.py -o path_to/backup.syx path_to/unpacked_backup.txt
"""

import logging
import optparse
import sys

# Allows the code to be run from the project root directory
sys.path.append('.')


def ParseSequence(data, name):
  steps = data.split('\t')
  assert len(steps) == 16
  sequence_data = []
  for step in steps:
    symbol, note, velocity, controller = tuple(step.split(' '))
    note = int(note)
    velocity = int(velocity, 16)
    controller = int(controller, 16)
    gate = 0x80 if symbol != '.' else 0
    legato = 0x80 if symbol == '-' else 0
    sequence_data.append(gate | note)
    sequence_data.append(legato | velocity | controller)
  return sequence_data


def ParseHexDump(data, name):
  byte_string = [chr(int(data[i:i+2], 16)) for i in xrange(0, len(data), 2)]
  byte_string = ''.join(byte_string)
  byte_string = byte_string.replace('$NAME___', (name.strip() + (' ' * 8))[:8])
  return map(ord, byte_string)
  

MEMORY_LAYOUT = [
  (1,  16, 'settings'),
  (16, 92, 'patch'),
  (16, 32, 'sequence'),
  (1,  48, 'padding')] + [
  (64, 92, 'patch'),
  (64, 32, 'sequence'),
  (1,  256, 'padding')] * 7


PARSERS = {
  'padding': ParseHexDump,
  'settings': ParseHexDump,
  'patch': ParseHexDump,
  'sequence': ParseSequence
}


def Parse(file_name):
  content = {}
  for line in file(file_name):
    tokens = line.strip().split('\t')
    if not tokens or not tokens[0] or tokens[0].startswith('#'):
      continue
    kind = tokens[0]
    name = tokens[1]
    data = PARSERS[kind]('\t'.join(tokens[2:]), name)
    content.setdefault(kind, []).append(data)
  return content
  

def Assemble(content):
  counters = {}
  image = []
  for num_entries, entry_size, kind in MEMORY_LAYOUT:
    for _ in xrange(num_entries):
      index = counters.get(kind, 0)
      counters[kind] = index + 1
      if index >= len(content[kind]):
        break
      data = content[kind][index]
      assert len(data) == entry_size
      image.extend(data)
  return image


def WriteSyx(f, image):
  for i, offset in enumerate(xrange(0, len(image), 128)):
    block = image[offset:offset + 128]
    checksum = sum(block) & 0xff
    # SysEx header
    f.write('\xf0')
    # Mutable Instruments
    f.write('\x00\x20\x77')
    # Shruthi-1
    f.write('\x00\x02')
    f.write(chr(0x40 + (i / 128)))
    f.write(chr(i % 128))
    for b in block + [checksum]:
      f.write(chr(b >> 4))
      f.write(chr(b & 0xf))
    # End of packet, thanks for listening!
    f.write('\xf7')
  

def main(options, args):
  content = Parse(args[0])
  image = Assemble(content)
  f = file(options.output_file, 'wb')
  if options.syx:
    WriteSyx(f, image)
  else:
    f.write(''.join(map(chr, image[2048:])))
  f.close()


if __name__ == '__main__':
  parser = optparse.OptionParser()
  parser.add_option(
      '-o',
      '--output_file',
      dest='output_file',
      default=None,
      help='Write output file to sysex file FILE',
      metavar='FILE')
  parser.add_option(
      '-s',
      '--syx',
      dest='syx',
      action="store_true",
      default=True,
      help='Output to .syx format')
  parser.add_option(
      '-b',
      '--bin',
      dest='syx',
      action="store_false",
      default=False,
      help='Output to .syx format')

  options, args = parser.parse_args()
  if len(args) != 1:
    logging.fatal('Specify a source and destination syx file')
  else:
    main(options, args)
