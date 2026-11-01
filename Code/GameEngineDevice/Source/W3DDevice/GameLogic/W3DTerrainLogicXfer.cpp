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

// W3DTerrainLogic::xfer, ported from Zero Hour's GameEngineDevice/Source/
// W3DDevice/GameLogic/W3DTerrainLogic.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference): slot 3 of the vftable whose slot-2
// name getter returns W3DTerrainLogic. The version, then the TerrainLogic
// base (slot 3 of 0x00BFB2C8, 0x00283845).

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

#include "../../../../GameEngine/Include/Common/BfmeXfer.h"

#include "../../../../GameEngine/Include/Common/XferVersion.h"

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


#include "../../../../GameEngine/Include/GameLogic/TerrainLogic.h"

class W3DTerrainLogic : public TerrainLogic
{
protected:
	virtual void xfer( Xfer *xfer );
};

// ------------------------------------------------------------------------------------------------
/** Xfer
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void W3DTerrainLogic::xfer( Xfer *xfer )
{

	// version
	xfer->Version1();

	// extend base class
	TerrainLogic::xfer( xfer );

}  // end xfer
