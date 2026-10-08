// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /DBFME_MODULE_NO_MPO /Ireference/open-bfme-1/inputs/reference/shims/dockupdate /Ireference/open-bfme-1/inputs/reference/shims/moduledata /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
//
// DockUpdate::getExitPosition, BFME2 0x00589A4E, 99 bytes.
// Reference logic: Open-BFME-1 6583b3c1ff21db4a561285717028fdafc780b7db,
// game/GameEngine/Source/GameLogic/Object/Update/DockUpdate/DockUpdate.cpp.
// Target: interface-relative loaded flag +0x30, enter +4, exit +0x1C,
// owner -0x18; full-object loadDockPositions uses this-0x20. Position
// fallback is docker+0x38, and Thing::convertBonePosToWorldPos is 0x30A528.
// Identity: MonsterDockUpdate interface vtable 0xC51D18 slot 7 points to
// 0x989A4E, following the donor getExitPosition slot; the matched ctor and
// onExitReached consumer independently establish this interface.
// stlport
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

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

// FILE: DockUpdate.cpp /////////////////////////////////////////////////////////////////////////////
// Author: Graham Smallwood Feb 2002
// Desc:   Behavior common to all DockUpdates is here.  Everything but action()
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#include "Common/Debug.h"
#include "Common/Xfer.h"
#include "GameClient/Drawable.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Object.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/Module/DockUpdate.h"

void DockUpdate::getExitPosition( Object* docker, Coord3D *position )
{

	// load dock positions if not loaded yet
	if( m_positionsLoaded == FALSE )
		loadDockPositions();

	// sanity
	if( position == NULL )
		return;

	// If I don't have a bone, you are fine where you are.
	Coord3D zero;
	zero.zero();
	if( m_enterPosition == zero )
	{
		*position = *docker->getPosition();
		return;
	}

	// take local space position and convert to world space
	getObject()->convertBonePosToWorldPos( &m_exitPosition, NULL, position, NULL );

}


// Interface slot 6 at 0xC51D18: native RVA 0x005899EB, 99 bytes.
void DockUpdate::getDockPosition( Object* docker, Coord3D *position )
{

	// load dock positions if not loaded yet
	if( m_positionsLoaded == FALSE )
		loadDockPositions();

	// sanity
	if( position == NULL )
		return;

	// If I don't have a bone, you are fine where you are.
	Coord3D zero;
	zero.zero();
	if( m_enterPosition == zero )
	{
		*position = *docker->getPosition();
		return;
	}

	// take local space position and convert to world space
	getObject()->convertBonePosToWorldPos( &m_dockPosition, NULL, position, NULL );

}


// Interface slot 5 at 0xC51D18: native RVA 0x00589972, 121 bytes.
void DockUpdate::getEnterPosition( Object* docker, Coord3D *position )
{

	// load dock positions if not loaded yet
	if( m_positionsLoaded == FALSE )
		loadDockPositions();

	// sanity
	if( position == NULL )
		return;

	// If I don't have a bone, you are fine where you are, unless you fly, in which case I should recenter you
	Coord3D zero;
	zero.zero();
	if( m_enterPosition == zero )
	{
		if( docker->isUsingAirborneLocomotor() )
		{
			*position = *getObject()->getPosition();
			return;
		}
		*position = *docker->getPosition();
		return;
	}

	// take local space position and convert to world space
	getObject()->convertBonePosToWorldPos( &m_enterPosition, NULL, position, NULL );

}


// Interface slot 1 at 0xC51D18: native RVA 0x0058A1A1, 239 bytes.
Bool DockUpdate::reserveApproachPosition( Object* docker, Coord3D *position, Int *index )
{

	// load dock positions if not loaded yet
	if( m_positionsLoaded == FALSE )
		loadDockPositions();

	// sanity
	if( position == NULL )
		return FALSE;

	ObjectID dockerID = docker->getID();

	for( Int positionIndex = 0; positionIndex < m_approachPositionOwners.size(); ++positionIndex )
	{
		if( m_approachPositionOwners[positionIndex] == dockerID )
		{
			*position = computeApproachPosition( positionIndex, docker );
			*index = positionIndex;
			return TRUE;
		}
		if( m_approachPositionOwners[positionIndex] == INVALID_ID )
		{
			m_approachPositionOwners[positionIndex] = dockerID;
			*position = computeApproachPosition( positionIndex, docker );
			*index = positionIndex;
			return TRUE;
		}
	}

	// If I make it out of the loop, I am full, so dynamic approach buildings should make a new entry instead of saying no
	if( m_numberApproachPositions == DYNAMIC_APPROACH_VECTOR_FLAG )
	{
		Coord3D zero;
		zero.zero();
		m_approachPositions.push_back( zero );
		m_approachPositionOwners.push_back( INVALID_ID );
		m_approachPositionReached.push_back( FALSE );

		loadDockPositions();// refresh this new one

		positionIndex = m_approachPositionOwners.size() - 1;// The new last spot
		m_approachPositionOwners[positionIndex] = dockerID;
		*position = computeApproachPosition( positionIndex, docker );
		*index = positionIndex;
		return TRUE;
	}

	return FALSE;
}

