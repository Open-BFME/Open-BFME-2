// cl: /DNDEBUG /MD /GX
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

// ScriptGroup::xfer, ported from Zero Hour's GameEngine/Source/GameLogic/
// ScriptEngine/Scripts.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference): slot 3 of the vftable whose slot-2
// name getter returns ScriptGroup. BFME 2 keeps only the active flag (+0x0C),
// transferred through a local copy. ZH's version-2 gate and per-script
// list are gone.

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

#include "../../../../Libraries/Include/Lib/Coord3DBase.h"


typedef bool Bool;

class ScriptGroup
{
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer( Xfer *xfer );
private:
	char m_unrecovered04[ 0x0C - 0x04 ];
	Bool m_isGroupActive;																											///< 0x0C
};

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void ScriptGroup::xfer( Xfer *xfer )
{

	// version
	xfer->Version1();

	// active
	Bool active = m_isGroupActive;
	*xfer == active;
	m_isGroupActive = active;

}  // end xfer
