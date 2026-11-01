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


// Anim2D::xfer, ported from Zero Hour's GameEngine/Source/GameClient/System/
// Anim2D.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference) onto the BFME 2 layout. It is slot 3
// of the vftable whose name getter returns "Anim2D".
//
// BFME 2 bumps the version to (1, 2). Version 2 adds an ICoord2D at +0x2C
// after ZH's fields.

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


typedef unsigned char UnsignedByte;
typedef unsigned short UnsignedShort;
typedef unsigned int UnsignedInt;
typedef float Real;

#include "../../../../Libraries/Include/Lib/ICoord2D.h"

class Anim2D
{
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer( Xfer *xfer );
private:
	UnsignedShort m_currentFrame;																							///< 0x04
	UnsignedInt m_lastUpdateFrame;																						///< 0x08
	char m_unrecovered0C[ 0x10 - 0x0C ];
	UnsignedByte m_status;																										///< 0x10
	UnsignedShort m_minFrame;																									///< 0x12
	UnsignedShort m_maxFrame;																									///< 0x14
	UnsignedInt m_framesBetweenUpdates;																				///< 0x18
	Real m_alpha;																															///< 0x1C
	char m_unrecovered20[ 0x2C - 0x20 ];
	ICoord2D m_bfmeOffset2C;																									///< 0x2C
};

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version
	* 2: BFME 2 ICoord2D at +0x2C */
// ------------------------------------------------------------------------------------------------
void Anim2D::xfer( Xfer *xfer )
{

	// version
	Xfer::Version version( 1, 2 );
	*xfer == version;

	// current frame
	*xfer == m_currentFrame;

	// last update frame
	*xfer == m_lastUpdateFrame;

	// status
	*xfer == m_status;

	// min frame
	*xfer == m_minFrame;

	// max frame
	*xfer == m_maxFrame;

	// frames between updates
	*xfer == m_framesBetweenUpdates;

	// alpha
	*xfer == m_alpha;

	if( version.m_minimum >= 2 )
		*xfer == m_bfmeOffset2C;

}  // end xfer
