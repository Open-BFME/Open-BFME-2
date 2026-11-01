// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
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


// WorkOrder::xfer, ported from Zero Hour's GameEngine/Source/GameLogic/AI/
// AIPlayer.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference). It is slot 3 of the vftable whose
// name getter returns "WorkOrder".
//
// BFME 2 opens with the light-CRC gate and Version1. ZH's inline template-name
// round trip becomes the free helper 0x003063A9: it saves the template name
// (or the empty string) and on load looks it up through the thing factory.
// ZH's fields follow, then BFME 2's Int, AsciiString, UnsignedInt and two
// flags. A last Int (+0x2C) is written from a copy and not read back.

#include "ascii_string.h"

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

#include "../../../Include/Common/XferVersion.h"

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

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID( Xfer *xfer, ObjectID *value );

class ThingTemplate;

void Rva003063A9XferThingTemplate( Xfer *xfer, const ThingTemplate **thing );

#include "WorkOrder.h"

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void WorkOrder::xfer( Xfer *xfer )
{
	if( xfer->IsLightCRC() )
		return;

	// version
	xfer->Version1();

	// thing template
	Rva003063A9XferThingTemplate( xfer, &m_thing );

	// factory id
	XferObjectID( xfer, &m_factoryID );

	// num completed
	*xfer == m_numCompleted;

	// num required
	*xfer == m_numRequired;

	// is required
	*xfer == m_required;

	// is resource gatherer
	*xfer == m_isResourceGatherer;

	*xfer == m_bfmeInt1C;
	*xfer == m_bfmeString20;
	*xfer == m_bfmeUnsigned24;
	*xfer == m_bfmeFlag28;
	*xfer == m_bfmeFlag29;

	Int value2C = m_bfmeInt2C;
	*xfer == value2C;

}  // end xfer
