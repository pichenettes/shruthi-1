# Copyright 2009 Olivier Gillet.
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

VERSION        = 0.97
MCU_NAME       = 644
TARGET         = shruthi1
PACKAGES       = avrlib avrlib/i2c avrlib/devices shruthi
RESOURCES      = shruthi/resources
EXTRA_DEFINES  = -DDISABLE_DEFAULT_UART_RX_ISR
# EXTRA_DEFINES  = -DPORTAMENTO_SAVE_HACK -DDISABLE_DEFAULT_UART_RX_ISR

LOCK           = 2f
LFUSE          = ff
HFUSE          = d6
EFUSE          = fd

include avrlib/makefile.mk

include $(DEP_FILE)
