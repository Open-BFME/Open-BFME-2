// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/reference/shims/asciistring_downloadmanager /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
/*
** Command & Conquer Generals Zero Hour(tm)
** Copyright 2025 Electronic Arts Inc.
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
*/

#include "Common/AsciiString.h"

bool GetUnsignedIntFromRegistry(AsciiString path, AsciiString key, unsigned int &val);

// ?GetRegistryVersion@@YAIXZ
// Zero Hour's GetRegistryVersion (Common/System/registry.cpp): the "Version"
// value, defaulting to 65536. BFME1's neighbouring MapPackVersion reader is
// the donor; BFME2's body at 0x002351D1 reads "Version".
unsigned int GetRegistryVersion(void)
{
	unsigned int val = 65536;
	GetUnsignedIntFromRegistry("", "Version", val);
	return val;
}
