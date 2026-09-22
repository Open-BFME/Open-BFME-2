// cl: /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
/*
** Command & Conquer Generals Zero Hour(tm)
** Copyright 2025 Electronic Arts Inc.
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program. If not, see <http://www.gnu.org/licenses/>.
**
** Donor: reference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/
** Code/Libraries/Source/WWVegas/WWLib/ini.cpp and widestring.h. Target
** interval and identity are separately checked against BFME 2 retail.
*/
// Retail 0x618840 encodes the wchar buffer through Base64Straw and Put_String.
// Its constructor at 0x6164B0 uses the established empty singleton, wcslen,
// and wide-string allocation paths. Both bodies retain their complete returns.
#include "always.h"
#include "b64straw.h"
#include "ini.h"
#include "trim.h"
#include "xstraw.h"
#include "widestring.h"
#include <malloc.h>

bool INIClass::Put_Wide_String(char const * section, char const * entry, wchar_t const * string)
{
	if (section == NULL || entry == NULL || string == NULL) {
		return(false);
	}

	WideStringClass temp_string(string, true);
	int len = temp_string.Get_Length();

	if (len == 0) {
		Put_String(section, entry, "");
	} else {
		char *buffer = (char*) _alloca((len * 8) + 32);
		BufferStraw straw(string, (len*2) + 2);
		Base64Straw bstraw(Base64Straw::ENCODE);
		bstraw.Get_From(straw);

		int new_length = 0;
		int added = 0;
		do {
			added = bstraw.Get(buffer + new_length, 16);
			new_length += added;
		} while (added);
		buffer[new_length] = 0;
		WWASSERT(new_length != 0);
		Put_String(section, entry, buffer);
	}
	return(true);
}
