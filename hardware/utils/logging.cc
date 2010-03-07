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
// Googley logging/assert functions. Used for the unit tests and for making
// development/debugging on a non-AVR platform (eg OS X) easier.

#include "logging.h"

#ifdef __TEST__

namespace hardware_utils {

/* extern */
char* kSegmentFaultCauser = "Used to cause artificial segmentation fault";

/* extern */
const char* severity_name[] = {
  AS_STRING(INFO), AS_STRING(WARNING), AS_STRING(ERROR), AS_STRING(FATAL)
};

}  // namespace hardware_utils

#endif __TEST__