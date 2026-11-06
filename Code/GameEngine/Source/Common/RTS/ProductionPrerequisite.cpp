// cl: /Ireference/shims/zh_ascii_outofline /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7 /arch:SSE) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

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

// FILE: ProductionPrerequisite.cpp /////////////////////////////////////////////////////////
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
// File name: ProductionPrerequisite.cpp
//
// Created:   Steven Johnson, October 2001
//
// Desc:      @todo
//
//-----------------------------------------------------------------------------

// PrereqUnitRec's destructor calls the retail out-of-line ~AsciiString (0x0048BA39),
// not the Zero Hour inline releaseBuffer whose freeBytes retail lacks.
#define BFME_ASCIISTRING_DTOR_OUTOFLINE
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/ProductionPrerequisite.h"
#include "Common/Player.h"
#include "Common/ThingFactory.h"
#include "Common/ThingTemplate.h"
#include "GameLogic/Object.h"
#include "GameClient/Drawable.h"
#include "GameClient/GameText.h"

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

// The exact retail constructor is emitted by ProductionPrerequisiteCtorThunk.cpp.

//-----------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/Common/RTS/ProductionPrerequisiteDestructorThunk.cpp
// ProductionPrerequisite::~ProductionPrerequisite: defined in ProductionPrerequisiteCtor.cpp (its row's unit).

//-----------------------------------------------------------------------------
//=============================================================================
// ProductionPrerequisite::resolveNames is defined with its retail-matched body in Code/GameEngine/Source/Common/RTS/ProductionPrerequisiteResolveNames.cpp (0x004F4B6D).

//-----------------------------------------------------------------------------
Int ProductionPrerequisite::calcNumPrereqUnitsOwned(const Player *player, Int counts[MAX_PREREQ]) const
{
	// Taking the member address keeps the rowed vector helper instantiated.
	void (std::vector<PrereqUnitRec>::*emitPushBack)(const PrereqUnitRec &) =
		&std::vector<PrereqUnitRec>::push_back;
	(void)emitPushBack;
	const ThingTemplate *thingTemplate[MAX_PREREQ];
	UnsignedInt cnt = m_prereqUnits.size();
	if (cnt > MAX_PREREQ)
		cnt = MAX_PREREQ;
	UnsignedInt i;
	for (i = 0; i < cnt; i++)
		thingTemplate[i] = m_prereqUnits[i].unit;
	int j;
	for (j = cnt; j < MAX_PREREQ; j++)
		thingTemplate[j] = NULL;
	player->countObjectsByThingTemplate(cnt, thingTemplate, false, counts);
	return cnt;
}

//-----------------------------------------------------------------------------
Int ProductionPrerequisite::getAllPossibleBuildFacilityTemplates(const ThingTemplate* thingTemplate[], Int maxtmpls) const
{
	Int count = 0;
	for (int i = 0; i < m_prereqUnits.size(); i++)
	{
		if (i > 0 && !(m_prereqUnits[i].flags & UNIT_OR_WITH_PREV))
			break;
		if (count >= maxtmpls)
			break;
		thingTemplate[count++] = m_prereqUnits[i].unit;
	}
	return count;
}

//-----------------------------------------------------------------------------
const ThingTemplate *ProductionPrerequisite::getExistingBuildFacilityTemplate( const Player *player ) const
{
	DEBUG_ASSERTCRASH(player, ("player may not be null"));
	if (m_prereqUnits.size())
	{
		Int ownCount[MAX_PREREQ];
		Int cnt = calcNumPrereqUnitsOwned(player, ownCount);
		for (int i = 0; i < cnt; i++)
		{
			if (i > 0 && !(m_prereqUnits[i].flags & UNIT_OR_WITH_PREV))
				break;
			if (ownCount[i])
				return m_prereqUnits[i].unit;
		} 
	}
	return NULL;
}

//-----------------------------------------------------------------------------
// ProductionPrerequisite::isSatisfied is defined with its retail-matched body in Code/GameEngine/Source/Common/RTS/ProductionPrerequisiteIsSatisfied_ProductionPrerequisite_isSatisfied.cpp (0x004F4CE5).

//-------------------------------------------------------------------------------------------------
/** Add a unit prerequisite, if 'orWithPrevious' is set then this unit is said
	* to be an alternate prereq to the previously added unit, otherwise this becomes
	* a new 'block' and is required in ADDDITION to other entries. 
	* Return FALSE if no space left to add unit */
//-------------------------------------------------------------------------------------------------
// The byte-verified overloads are owned by
// Common/Thing/ProductionPrerequisiteAddUnitPrereq.cpp. Retain this unit's
// rowed vector helper without a second, unverified addUnitPrereq definition.


//-------------------------------------------------------------------------------------------------
/** Add a unit prerequisite, if 'orWithPrevious' is set then this unit is said
	* to be an alternate prereq to the previously added unit, otherwise this becomes
	* a new 'block' and is required in ADDDITION to other entries. 
	* Return FALSE if no space left to add unit */
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// ProductionPrerequisite::getRequiresList is defined with its retail-matched body in Code/GameEngine/Source/Common/RTS/ProductionPrerequisiteIsSatisfied_ProductionPrerequisite_isSatisfied.cpp (0x004F4DF2).
