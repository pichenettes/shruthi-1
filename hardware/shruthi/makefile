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

VERSION        = 0.1
TARGET         = shruthi1
PACKAGES       = hardware/base hardware/hal hardware/hal/devices hardware/midi hardware/utils hardware/shruthi
RESOURCES      = hardware/shruthi/resources

include hardware/base.mk


# ------------------------------------------------------------------------------
# Resources
# ------------------------------------------------------------------------------

RESOURCE_COMPILER = hardware/tools/resources_compiler/resources_compiler.py

resources:	$(wildcard $(RESOURCES)/*.py) 
		python $(RESOURCE_COMPILER) $(RESOURCES)/resources.py

include $(DEP_FILE)


# ------------------------------------------------------------------------------
# Patch libraries
# ------------------------------------------------------------------------------

LIBRARIAN = hardware/tools/librarian/librarian.py

dump_patches: eeprom_backup
	$(LIBRARIAN) -d $(EEPROM_DATA) > $(PATCH_LIBRARY)

upload_patches:
	$(LIBRARIAN) -c $(PATCH_LIBRARY) > $(EEPROM_DATA)
	$(AVRDUDE) $(AVRDUDE_COM_OPTS) $(AVRDUDE_SER_OPTS) \
		-U eeprom:w:$(EEPROM_DATA):i
