// cl: /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/Common/INI/INIDrawGroupInfo.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// parseInt 0x001DCC45 (46B), parsePercentToReal 0x001DCC73 (44B). Callee
// addresses are read off retail's call sites (reverse/symbols.csv). Only the
// placed bodies are carried; the donor's other definitions are omitted.
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

// FILE: INIDrawGroupInfo.cpp /////////////////////////////////////////////////////////////////////
// Author: John McDonald, October 2002
// Desc:   Parsing DrawGroupInfo INI entries
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/INI.h"
#include "GameClient/DrawGroupInfo.h"

void parseInt( INI* ini, void * /*instance*/, void *store, const void* userData )
{
	DrawGroupInfo *dgi = (DrawGroupInfo*) store;
	if (userData == 0) {
		store = &dgi->m_pixelOffsetX;
		dgi->m_usingPixelOffsetX = TRUE;
	} else { 
		store = &dgi->m_pixelOffsetY;
		dgi->m_usingPixelOffsetY = TRUE;
	}

	INI::parseInt(ini, NULL, store, NULL);
}

void parsePercentToReal( INI* ini, void * /*instance*/, void *store, const void* userData )
{
	DrawGroupInfo *dgi = (DrawGroupInfo*) store;
	if (userData == 0) {
		store = &dgi->m_pixelOffsetX;
		dgi->m_usingPixelOffsetX = FALSE;
	} else { 
		store = &dgi->m_pixelOffsetY;
		dgi->m_usingPixelOffsetY = FALSE;
	}

	INI::parsePercentToReal(ini, NULL, store, NULL);
}


