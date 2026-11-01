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

// AIWanderInPlaceState::xfer, ported from Zero Hour's GameEngine/Source/
// GameLogic/AI/AIStates.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference): slot 3 of the vftable 0x00C12AC8
// whose slot-2 name getter returns AIWanderInPlaceState. The version and
// the AIInternalMoveToState base (0x0033FF76), then in BFME 2 the light-CRC
// early-out, then ZH's m_origin +0x4C, m_waitFrames +0x58 and m_timer +0x5C.

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



typedef int Int;

class AIInternalMoveToState
{
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer( Xfer *xfer );
	char m_unrecovered04[ 0x4C - 0x04 ];
};

class AIWanderInPlaceState : public AIInternalMoveToState
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	Coord3DBase m_origin;																											///< 0x4C
	Int m_waitFrames;																													///< 0x58
	Int m_timer;																															///< 0x5C
};

// ------------------------------------------------------------------------------------------------
/** Xfer Method */
// ------------------------------------------------------------------------------------------------
void AIWanderInPlaceState::xfer( Xfer *xfer )
{
	xfer->Version1();
	AIInternalMoveToState::xfer(xfer);
	if( xfer->IsLightCRC() )
		return;
	*xfer == m_origin;
	*xfer == m_waitFrames;
	*xfer == m_timer;
}  // end xfer
