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

"""Tool for "disassembling" a backup .Syx file.

usage:
  python disassemble_backup.py -o path_to/unpacked_backup.txt path_to/backup.syx
"""

import logging
import optparse
import sys

# Allows the code to be run from the project root directory
sys.path.append('.')


MEMORY_LAYOUT = [
  (1,  16, 'settings', lambda x, y: 'settings'),
  (16, 92, 'patch', lambda x, y: y[68:76]),
  (16, 32, 'sequence', lambda x, y: 'sequence_%d' % x),
  (1,  48, 'padding', lambda x, y: 'padding'),
  (64, 92, 'patch', lambda x, y: y[68:76]),
  (64, 32, 'sequence', lambda x, y: 'sequence_%d' % x)
]


def Denibblize(nibblized_data):
  data = []
  for nibble_hi, nibble_lo in zip(nibblized_data[::2], nibblized_data[1::2]):
    data.append(chr((ord(nibble_hi) << 4) | ord(nibble_lo)))
  return ''.join(data)
  

def ExtractSyxData(syx_content):
  data = []
  packets = [p for p in syx_content.split('\xf0') if p]
  for index, packet in enumerate(packets):
    head = 0
    tail = len(packet)
    
    # Remove trailing 0xf7
    assert packet[-1] == '\xf7'
    tail -= 1
    # Remove trailing checksum
    tail -= 2
    
    # Remove leading manufacturer id
    assert packet[head:head + 3] == '\x00\x20\x77'
    head += 3
    
    # Remove leading product id (Shruthi-1)
    assert packet[head:head + 2] == '\x00\x02'
    head += 2
    
    # Remove leading command
    assert packet[head] == '\x40'
    assert packet[head + 1] == chr(index)
    head += 2
    
    data.append(packet[head:tail])
  
  return Denibblize(''.join(data))


def Parse(data):
  content = {}
  offset = 0
  for entries, size, kind, name_extractor in MEMORY_LAYOUT:
    extracted_items = content.setdefault(kind, [])
    for entry in range(entries):
      block = data[offset:offset + size]
      offset += size
      name = name_extractor(len(extracted_items), block)
      block = block.replace(name, '$NAME' + '_' * (len(name) - 5))
      name = ''.join('_' if ord(c) < 32 or ord(c) > 126 else c for c in name)
      extracted_items.append((name, block))
  return content


def main(options, args):
  data = file(args[0]).read()
  content = Parse(ExtractSyxData(data))
  output = file(options.output_file, 'w') if options.output_file else sys.stdout
  for content_type, content in content.items():
    for name, data in content:
      data = ''.join('%02x' % ord(byte) for byte in data)
      output.write('%(content_type)s\t%(name)s\t%(data)s\n' % locals())
  output.close()


if __name__ == '__main__':
  parser = optparse.OptionParser()
  parser.add_option(
      '-o',
      '--output_file',
      dest='output_file',
      default=None,
      help='Write output file to FILE',
      metavar='FILE')
  options, args = parser.parse_args()
  if len(args) != 1:
    logging.fatal('Specify a source and destination hex file')
  else:
    main(options, args)
