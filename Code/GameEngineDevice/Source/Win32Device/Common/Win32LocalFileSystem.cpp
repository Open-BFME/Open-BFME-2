// cl: -DNDEBUG -MD -EHsc -Ireference/open-bfme-1/inputs/reference/shims/win32localfilesystem_wide -Ireference/open-bfme-1/inputs/reference/shims/asciistring_thin -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad -Ireference/open-bfme-1/game/GameEngineDevice/Source/Win32Device/Common
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

///////// Win32LocalFileSystem.cpp /////////////////////////
// Bryan Cleveland, August 2002
////////////////////////////////////////////////////////////

// BFME's retail AsciiStringData has an extra 4-byte field (debug ptr) before the
// string buffer, so force the _INTERNAL layout without enabling debug side effects.
#define _INTERNAL
#define DISABLE_ALLOW_DEBUG_UTILS
#define DISABLE_MEMORYPOOL_DEBUG_CUSTOM_NEW

#include <windows.h>
#include "Common/AsciiString.h"
#include "Common/GameMemory.h"
#include "Common/PerfTimer.h"
#include "Win32Device/Common/Win32LocalFileSystem.h"
#include "Win32Device/Common/Win32LocalFile.h"
#include <io.h>

// ?doesFileExist@Win32LocalFileSystem@@UBE_NPBD@Z
// retail 0x0060487E, 23 bytes. Dedicated TU carrying the Open-BFME-1 donor
// preamble (game/GameEngineDevice/Source/Win32Device/Common/
// Win32LocalFileSystem.cpp, reference/open-bfme-1) and only this body; the
// donor's other definitions are omitted. Compiled /Os the donor emits it
// byte-identical to retail (unique masked placement on unclaimed .text).
//
// Retail calls the imported _waccess at 0x00BBA400 (msvcr71.dll!_waccess)
// through its IAT slot and folds the `== 0` test into neg/sbb/inc, which is
// what this spelling gives. The donor body reads _access (the narrow CRT
// call), but retail's IAT slot 0x00BBA400 provably holds msvcr71.dll!_waccess,
// so the wide CRT call is what the target actually contains; the donor's
// narrow spelling is the donor's own divergence, not a target fact.

//DECLARE_PERF_TIMER(Win32LocalFileSystem_doesFileExist)
Bool Win32LocalFileSystem::doesFileExist(const Char *filename) const
{
	//USE_PERF_TIMER(Win32LocalFileSystem_doesFileExist)
	if (_waccess((const wchar_t *)filename, 0) == 0) {
		return TRUE;
	}
	return FALSE;
}
