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

// RiderChangeContain::xfer, ported from Zero Hour's GameEngine/Source/GameLogic/
// Object/Contain/RiderChangeContain.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference): slot 3 of the vftable whose slot-2
// name getter returns RiderChangeContain. In BFME 2 the base is
// SiegeEngineContain (slot 3 of 0x00C470F8, 0x0047C322); ZH's
// m_extraSlotsInUse (+0x138) and m_frameExitNotBusy (+0x13C) follow. ZH's
// m_payloadCreated is gone.

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


class Thing;
class ModuleData;
class SiegeEngineContain
{
public:
	SiegeEngineContain(Thing *thing, const ModuleData *moduleData);
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer( Xfer *xfer );
	char m_unrecovered04[ 0x138 - 0x04 ]; // +0x04
};

typedef int Int;
typedef unsigned int UnsignedInt;

class RiderChangeContain : public SiegeEngineContain
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	Int m_extraSlotsInUse;																										///< 0x138
	UnsignedInt m_frameExitNotBusy;																						///< 0x13C
};

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void RiderChangeContain::xfer( Xfer *xfer )
{

	// version
	xfer->Version1();

	// extend base class
	SiegeEngineContain::xfer( xfer );

	// extra slots in use
	*xfer == m_extraSlotsInUse;

	// frame exit not busy
	*xfer == m_frameExitNotBusy;

}  // end xfer
