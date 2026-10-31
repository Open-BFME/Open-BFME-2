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

// TurretAIIdleScanState::xfer, ported from Zero Hour's TurretAI.cpp (GeneralsMD
// tree vendored under reference/open-bfme-1/inputs/reference) in BFME 2's Xfer
// spelling: slot 3 of the vftable whose slot-2 name getter returns
// TurretAIIdleScanState. Version, then m_desiredAngle (+0x20).

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

// The canonical State (Snapshot slots 0-3, 0x20 bytes) is the base.
#include "../../../Include/Common/StateMachine.h"
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

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID( Xfer *xfer, ObjectID *id );

// ------------------------------------------------------------------------------------------------
class TurretAIIdleScanState : public State
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	float m_desiredAngle;																											///< 0x20
};

// ------------------------------------------------------------------------------------------------
/** Xfer Method */
// ------------------------------------------------------------------------------------------------
void TurretAIIdleScanState::xfer( Xfer *xfer )
{
	xfer->Version1();
	*xfer == m_desiredAngle;
}  // end xfer
