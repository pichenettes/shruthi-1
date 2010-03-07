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
# Generates .cc and .h files for string, lookup tables, etc.

"""Compiles python string tables/arrays into .cc and .h files.

TODO(pichenettes): rewrite this using the django templating engine.
"""

import os
import string
import sys

def Canonicalize(x):
  """Returns a lower case version of the string with funky chars stripped."""
  in_chr = ''.join(map(chr, range(256)))
  out_chr = range(256)
  for i in range(256):
    if chr(i) in string.uppercase:
      out_chr[i] = ord(chr(i).lower())
    elif chr(i) in string.lowercase:
      out_chr[i] = i
    elif chr(i) in string.digits:
      out_chr[i] = i
    elif i < 10:
      out_chr[i] = ord(str(i))
    elif chr(i) == '~':
      out_chr[i] = ord('T')
    elif chr(i) == '*':
      out_chr[i] = ord('P')
    elif chr(i) == '+':
      out_chr[i] = ord('S')
    elif chr(i) == '^':
      out_chr[i] = ord('x')
    elif chr(i) == '"':
      out_chr[i] = ord('p')
    else:
      out_chr[i] = ord('_')
  table = string.maketrans(in_chr, ''.join(map(chr, out_chr)))
  bad_chars = '\t\n\r-:()[]"\',;'
  return x.translate(table, bad_chars)


def CheckDups(collection):
  counts = {}
  for e in collection:
    counts[e] = counts.get(e, 0) + 1
  for k, v in counts.items():
    if v > 1:
      print 'Dupe:', k
      return True
  return False


def GenerateHeader(base_name, res):
  max_num_resources = 0
  for resource in res.resources:
    max_num_resources = max(max_num_resources, len(resource[0]))

  f = file(os.path.join(res.target, base_name + '.h'), 'w')
  header_guard = res.target.replace(os.path.sep, '_').upper()
  f.write(res.header + '\n\n')
  f.write('#ifndef %s_%s_H_\n' % (header_guard, base_name.upper()))
  f.write('#define %s_%s_H_\n\n' % (header_guard, base_name.upper()))
  f.write(res.includes + '\n\n')
  if res.create_specialized_manager:
    f.write('#include "hardware/resources/resources_manager.h"\n')

  if res.namespace:
    f.write('namespace %s {\n\n' % res.namespace)
  
  f.write('typedef %s ResourceId;\n\n' % res.types[max_num_resources > 255])
  
  for resource, table_name, prefix, c_type, python_type, ram in res.resources:
    f.write('extern const %s* %s_table[];\n\n' % (c_type, table_name))

  for resource, table_name, prefix, c_type, python_type, ram in res.resources:
    if python_type != str:
      canonical = {}
      for name, data in resource:
        if not tuple(data) in canonical:
          name = '%s_%s' % (prefix.lower(), Canonicalize(name))
          args = (c_type, name, res.modifier)
          f.write('extern const %s %s[] %s;\n' % args)
          canonical[tuple(data)] = name

  for resource, table_name, prefix, c_type, python_type, ram in res.resources:
    if python_type == str:
      for i, string in enumerate(resource):
        args = (prefix, Canonicalize(string).upper(), i, string)
        f.write('#define %s_%s %d  // %s\n' % args)
    else:
      for i, (name, data) in enumerate(resource):
        f.write('#define %s_%s %d\n' % (prefix, Canonicalize(name).upper(), i))
        args = (prefix, Canonicalize(name).upper(), len(data))
        f.write('#define %s_%s_SIZE %d\n' % args)
    
  if res.create_specialized_manager:
    f.write('typedef hardware_resources::ResourcesManager<\n')
    f.write('    ResourceId,\n')
    f.write('    hardware_resources::ResourcesTables<\n')
    f.write('        %s_table,\n' % res.resources[0][1])
    f.write('        %s_table> > ResourcesManager; \n' % res.resources[1][1])
  
  if res.namespace:
    f.write('\n}  // namespace %s\n' % res.namespace)
  f.write('\n#endif  // %s_%s_H_\n' % (header_guard, base_name.upper()))


def GenerateCc(base_name, res):
  f = file(os.path.join(res.target, base_name + '.cc'), 'w')
  f.write(res.header + '\n\n')
  f.write('#include "%s.h"\n' % base_name)
  if res.namespace:
    f.write('\nnamespace %s {\n\n' % res.namespace)
    
  for resource, table_name, prefix, c_type, python_type, ram in res.resources:
    if python_type == str:
      for string in resource:
        args = (c_type, '%s_%s' % (prefix.lower(), Canonicalize(string)),
                res.modifier, string.strip())
        f.write('static const %s %s[] %s = "%s";\n' % args)
      if ram:
        args = (c_type, table_name)
        f.write('\n\nconst %s* %s_table[] = {\n' % args)
      else:
        args = (res.modifier, c_type, table_name)
        f.write('\n\n%s const %s* %s_table[] = {\n' % args)
      for string in resource:
        f.write('  %s_%s,\n' % (prefix.lower(), Canonicalize(string)))
      f.write('};\n\n')
    else:
      canonical = {}
      for name, data in resource:
        if not tuple(data) in canonical:
          name = '%s_%s' % (prefix.lower(), Canonicalize(name))
          args = (c_type, name, res.modifier)
          f.write('const %s %s[] %s = {\n' % args)
          n_elements = len(data)
          for i in xrange(0, n_elements, 8):
            f.write('  ');
            for j in xrange(i, min(n_elements, i + 8)):
              f.write('%6d, ' % data[j]);
            f.write('\n');
          f.write('};\n')
          canonical[tuple(data)] = name
      if ram:
        args = (c_type, table_name)
        f.write('\n\nconst %s* %s_table[] = {\n' % args)
      else:
        args = (res.modifier, c_type, table_name)
        f.write('\n\n%s const %s* %s_table[] = {\n' % args)
      for name, data in resource:
        f.write('  %s,\n' % canonical[tuple(data)])
      f.write('};\n\n')

  if res.namespace:
    f.write('\n}  // namespace %s\n' % res.namespace)


def Compile(path):
  # A hacky way of loading the py file passed as an argument as a module +
  # a descent along the module path.
  base_name = os.path.splitext(path)[0]
  sys.path += [os.path.abspath('.')]
  res = __import__(base_name.replace('/', '.'))
  for part in base_name.split('/')[1:]:
    res = getattr(res, part)
  
  # Convert any big multi-line string into a list of string.
  for i, resource_tuple in enumerate(res.resources):
    if resource_tuple[-2] == str:
      resource_tuple = list(resource_tuple)
      resource_tuple[0] = [x for x in resource_tuple[0].split('\n') if x]
      if CheckDups(resource_tuple[0]):
        return
      if CheckDups([Canonicalize(x) for x in resource_tuple[0]]):
        return
      res.resources[i] = tuple(resource_tuple)
  
  base_name = 'resources'  #os.path.split(base_name)[-1]
  GenerateHeader(base_name, res)
  GenerateCc(base_name, res)


def main(argv):
  for i in xrange(1, len(argv)):
    Compile(argv[i])


if __name__ == '__main__':
  main(sys.argv)
