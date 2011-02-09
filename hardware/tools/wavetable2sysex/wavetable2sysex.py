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

"""Utility for building a "user" wavetable to be sent by SysEx.

usage:
  python wavetable2sysex.py \
    [--output_file path_to/wavetable.mid] \
    path_to/firmware.hex
"""

import logging
import optparse
import os
import sys

# Allows the code to be run from the project root directory
sys.path.append('.')

from music.midi import midifile


def CreateMidifile(
    input_file_name,
    data,
    output_file,
    options):
  size = len(data)
  _, input_file_name = os.path.split(input_file_name)
  comments = [
      'Contains wavetable data for Shruthi-1',
      'Created from %(input_file_name)s' % locals(),
      'Size: %(size)d' % locals()]
  m = midifile.Writer()
  if options.write_comments:
    for comment in comments:
      m.AddTrack().AddEvent(0, midifile.TextEvent(comment))
  t = m.AddTrack()
  t.AddEvent(0, midifile.TempoEvent(120.0))
  t.AddEvent(1, midifile.SysExEvent(
      options.manufacturer_id,
      options.device_id,
      options.update_command + midifile.Nibblize(data)))
  f = file(output_file, 'wb')
  m.Write(f, format=1)
  f.close()


if __name__ == '__main__':
  parser = optparse.OptionParser()
  parser.add_option(
      '-o',
      '--output_file',
      dest='output_file',
      default=None,
      help='Write output file to FILE',
      metavar='FILE')
  parser.add_option(
      '-m',
      '--manufacturer_id',
      dest='manufacturer_id',
      default='\x00\x20\x77',
      help='Manufacturer ID to use in SysEx message')
  parser.add_option(
      '-v',
      '--device_id',
      dest='device_id',
      default='\x00\x02',
      help='Device ID to use in SysEx message')
  parser.add_option(
      '-u',
      '--update_command',
      dest='update_command',
      default='\x03\x00',
      help='Wavetable transfer SysEx command')
  parser.add_option(
      '-c',
      '--comments',
      dest='write_comments',
      action='store_true',
      default=False,
      help='Store additional technical gibberish')

  options, args = parser.parse_args()
  if len(args) != 1:
    logging.fatal('Specify one, and only one wavetable .bin file!')
    sys.exit(1)

  data = file(args[0]).read()
  if not data or len(data) < 129 * 8:
    logging.fatal('Error while loading .hex file')
    sys.exit(2)

  output_file = options.output_file
  if not output_file:
    if '.bin' in args[0]:
      output_file = args[0].replace('.bin', '.mid')
    else:
      output_file = args[0] + '.mid'

  CreateMidifile(
      args[0],
      data[:129 * 8],
      output_file,
      options)
