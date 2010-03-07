// Copyright 2009 Olivier Gillet.
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
// Base header.

#ifndef HARDWARE_BASE_BASE_H_
#define HARDWARE_BASE_BASE_H_

#include <inttypes.h>

#ifndef NULL
#define NULL 0
#endif

typedef union {
  uint16_t value;
  uint8_t bytes[2];
} Word;

#define abs(x) ((x) > 0 ? (x) : -(x))

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)

#endif  // HARDWARE_BASE_BASE_H_
