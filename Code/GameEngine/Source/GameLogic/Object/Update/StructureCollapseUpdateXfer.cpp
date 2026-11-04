// cl: /DNDEBUG /MD
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


// StructureCollapseUpdate::xfer, ported from Zero Hour's GameEngine/Source/
// GameLogic/Object/Update/StructureCollapseUpdate.cpp (GeneralsMD tree
// vendored under reference/open-bfme-1/inputs/reference). It is slot 3 of the
// vftable whose name getter returns "StructureCollapseUpdate".
//
// BFME 2 order: the UpdateModule base (0x0044DF9F) first, then the light-CRC
// gate and Version1, then ZH's fields and three more BFME 2 Reals
// (+0x38..+0x40).

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

#include "../../../../Include/Common/BfmeXfer.h"

#include "../../../../Include/Common/XferVersion.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

#include "../../../../../Libraries/Include/Lib/Coord3DBase.h"

typedef float Real;

enum StructureCollapseStateType
{
	COLLAPSESTATE_STANDING
};

#include "../../../../Include/GameLogic/Module/UpdateModule.h"

class StructureCollapseUpdate : public UpdateModule
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	char m_unrecovered20[0x24 - 0x20]; // +0x20, unrecovered bytes before this class's fields
	UnsignedInt m_collapseFrame;																							///< 0x24
	UnsignedInt m_burstFrame;																									///< 0x28
	StructureCollapseStateType m_collapseState;																///< 0x2C
	Real m_collapseVelocity;																									///< 0x30
	Real m_currentHeight;																											///< 0x34
	Real m_bfmeReal38;																												///< 0x38
	Real m_bfmeReal3C;																												///< 0x3C
	Real m_bfmeReal40;																												///< 0x40
};

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void StructureCollapseUpdate::xfer( Xfer *xfer )
{

	// extend base class
	UpdateModule::xfer( xfer );

	if( xfer->IsLightCRC() )
		return;

	// version
	xfer->Version1();

	// collapse frame
	*xfer == m_collapseFrame;

	// burst frame
	*xfer == m_burstFrame;

	// collapse state
	xfer->XferRawBytes( &m_collapseState, sizeof( StructureCollapseStateType ) );

	// collapse velocity
	*xfer == m_collapseVelocity;

	// current height
	*xfer == m_currentHeight;

	*xfer == m_bfmeReal38;
	*xfer == m_bfmeReal3C;
	*xfer == m_bfmeReal40;

}  // end xfer
