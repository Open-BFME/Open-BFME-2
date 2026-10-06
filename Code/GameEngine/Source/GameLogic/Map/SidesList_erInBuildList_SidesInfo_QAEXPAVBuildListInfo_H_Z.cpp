// cl: -DNDEBUG -MD -EHsc -D_STLP_USE_STATIC_LIB -Ireference/open-bfme-1/inputs/reference/shims/stringbaseascii -Ireference/open-bfme-1/inputs/reference/shims/buildlistinfo -Ireference/open-bfme-1/inputs/reference/shims/moduledata -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/game/GameEngine/Source/GameLogic/Map
// stlport
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

// FILE: SidesList.cpp /////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//                                                                          
//                       Westwood Studios Pacific.                          
//                                                                          
//                       Confidential Information                           
//                Copyright (C) 2001 - All Rights Reserved                  
//                                                                          
//-----------------------------------------------------------------------------
//
// Project:   RTS3
//
// File name: SidesList.cpp
//
// Created:   John Ahlquist, Nov 2001
//
// Desc:      Contains the information describing Sides (player, ai, neutral etc.)
//						in a scenario, including build lists for non-player sides.
//
//-----------------------------------------------------------------------------

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/DataChunk.h"
#include "Common/GameState.h"
#include "Common/PlayerTemplate.h"
#include "Common/WellKnownKeys.h"
#include "Common/Xfer.h"
#include "GameLogic/AI.h"
#include "GameLogic/Scripts.h"
#include "GameLogic/SidesList.h"

// The canonical StringBase<char> shim supplies BFME AsciiString layout.
// Retail inlines its reference release here; expose that base operation
// within this TU. Every existing sibling remains byte-verified.
#include "string_base.h"

inline AsciiString::~AsciiString() { ((StringBase<char>*)this)->releaseBuffer(); }

/**
* SidesInfo::reorderInBuildList - Reorders a build list entry as the nth entry.
*		
*/
void SidesInfo::reorderInBuildList(BuildListInfo *pBuildList, Int newPosition)
{
	/*Int oldPos =*/ removeFromBuildList(pBuildList);
	addToBuildList(pBuildList, newPosition);
}
