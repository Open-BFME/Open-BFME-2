// cl: /DNDEBUG /MD /GX
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


// DeployStyleAIUpdate::xfer, ported from Generals' and Zero Hour's
// GameEngine/Source/GameLogic/Object/Update/AIUpdate/DeployStyleAIUpdate.cpp
// (trees vendored under reference/open-bfme-1/inputs/reference). It is slot 3
// of the vftable whose name getter (0x0048E8F1) returns "DeployStyleAIUpdate".
//
// BFME 2 keeps the Generals (version 3) field set rather than ZH's version 4
// reduction, without the version checks. The AIUpdateInterface base comes
// first, then the light-CRC gate and Version1, then the fields, and last the
// +0x3E4 command storage's doXfer (0x003533BF). That member is
// Rva0026AFDAMember, as the matched ctor/dtor name it; Generals'
// m_lastOutsideCommand (AICommandParmsStorage) is the donor-carried semantic
// lead. Generals' field order supplies semantic leads. BFME 2
// adds two flags before them, a second command result, and two trailing flags.
// The shared header uses target offset spellings; its +0x4C4 float triple
// is transferred through the original 12-byte Coord3DBase view.

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

#include "../../../../../Include/Common/BfmeXfer.h"

#include "../../../../../Include/Common/XferVersion.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

#include "../../../../../../Libraries/Include/Lib/Coord3DBase.h"


typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

enum ObjectID
{
	INVALID_ID = 0
};

void XferCommandResultTypes( Xfer *xfer, Int *value );
void XferDeployStateTypes( Xfer *xfer, Int *value );
void XferObjectID( Xfer *xfer, ObjectID *value );

#include "../../../../../Include/GameLogic/Module/AIUpdate.h"
#include "../../../../../Include/GameLogic/Module/DeployStyleAIUpdateClass.h"

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void DeployStyleAIUpdate::xfer( Xfer *xfer )
{

 // extend base class
	AIUpdateInterface::xfer(xfer);

	if( xfer->IsLightCRC() )
		return;

	xfer->Version1();

	*xfer == m_4A9;
	*xfer == m_4A8;
	XferCommandResultTypes( xfer, &m_4AC );
	*xfer == m_4B8;
	XferDeployStateTypes( xfer, &m_4B4 );
	XferCommandResultTypes( xfer, &m_4B0 );
	XferObjectID( xfer, &m_4BC );
	XferObjectID( xfer, &m_4C0 );
	*xfer == *reinterpret_cast<Coord3DBase *>(m_4C4);
	*xfer == m_4D0;
	*xfer == m_4D1;
	*xfer == m_4D2;
	*xfer == m_4D3;
	*xfer == m_4D4;
	*xfer == m_4D5;
	*xfer == m_4D6;

	m_member3E4.doXfer( xfer );

}  // end xfer
