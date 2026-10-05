// cl: /O1 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /DBFME_MODULE_NO_MPO /Ireference/open-bfme-1/inputs/reference/shims/dockupdate /Ireference/open-bfme-1/inputs/reference/shims/moduledata /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
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


// Header view differs only in struct/class decoration and const qualification.
// Native call is the existing 57-byte coordinate equality at RVA 0x3702.
#pragma comment(linker, "/alternatename:??8Coord3D@@QAE_NABU0@@Z=??8Coord3D@@QBE_NABV0@@Z")
