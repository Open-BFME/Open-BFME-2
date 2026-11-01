// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /DNDEBUG /MD /EHsc
// cl: /O1 /DNDEBUG /MD /GX
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


// BuildListInfo::xfer, ported from Zero Hour's GameEngine/Source/GameLogic/
// Map/SidesList.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference). It is slot 3 of the vftable whose
// name getter (0x00329EE3) returns "BuildListInfo". The layout is the one
// established by the matched assignment (BuildListInfoAssign.cpp, 0x003299AD).
//
// BFME 2 opens with the light-CRC gate and Version1, and drops ZH's version-2
// check on m_currentGatherers. It writes the resource gatherers one ObjectID
// at a time instead of ZH's xferUser block.

#include "ascii_string.h"
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"


class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;

#include "../../../Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

class Coord3DBase
{
public:
	float x;
	float y;
	float z;
};


typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID( Xfer *xfer, ObjectID *value );

#include "../../../../Libraries/Include/Lib/Coord2D.h"

#include "../../../Include/GameLogic/Bfme2BuildListInfo.h"

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void BuildListInfo::xfer( Xfer *xfer )
{
	if( xfer->IsLightCRC() )
		return;

	// version
	xfer->Version1();
	*xfer == m_buildingName;
	*xfer == m_templateName;
	*xfer == *(Coord3DBase *)&m_location;
	*xfer == m_rallyPointOffset;
	*xfer == m_angle;
	*xfer == m_isInitiallyBuilt;
	*xfer == m_numRebuilds;
	*xfer == m_script;
	*xfer == m_health;
	*xfer == m_whiner;
	*xfer == m_unsellable;
	*xfer == m_repairable;
	*xfer == m_automaticallyBuild;
	// m_renderObj we don't need to xfer this, its for the editor only
	// m_shadowObj we don't need to xfer this, its for the editor only
	// m_selected we don't need to xfer this, its for the editor only
	XferObjectID( xfer, (ObjectID *)&m_objectID );
	*xfer == m_objectTimestamp;
	*xfer == m_underConstruction;
	for( Int i = 0; i < MAX_RESOURCE_GATHERERS; ++i )
		XferObjectID( xfer, (ObjectID *)&m_resourceGatherers[ i ] );
	*xfer == m_isSupplyBuilding;
	*xfer == m_desiredGatherers;
	*xfer == m_priorityBuild;
	*xfer == m_currentGatherers;
}  // end xfer
