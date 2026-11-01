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
// lead. The field names follow Generals' order and are inferences. BFME 2
// adds two flags before them, a second command result, and two trailing flags.

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

class Rva0026AFDAMember
{
public:
	void doXfer( Xfer *xfer );
private:
	unsigned char m_unrecovered00[ 0xC4 ];
};

class AIUpdateInterface
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer( Xfer *xfer );
};

class DeployStyleAIUpdate : public AIUpdateInterface
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	unsigned char m_unrecovered04[ 0x3E4 - 0x04 ];
	Rva0026AFDAMember m_lastOutsideCommand;																		///< 0x3E4
	Bool m_bfmeFlag4A8;																												///< 0x4A8
	Bool m_bfmeFlag4A9;																												///< 0x4A9
	unsigned char m_unrecovered4AA[ 2 ];
	Int m_bfmeCommandResult4AC;																								///< 0x4AC
	Int m_bfmeCommandResult4B0;																								///< 0x4B0
	Int m_state;																															///< 0x4B4
	UnsignedInt m_frameToWakeForDeploy;																				///< 0x4B8
	ObjectID m_designatedTargetID;																						///< 0x4BC
	ObjectID m_attackObjectID;																								///< 0x4C0
	Coord3DBase m_position;																										///< 0x4C4
	Bool m_isAttackMultiple;																									///< 0x4D0
	Bool m_isAttackObject;																										///< 0x4D1
	Bool m_isAttackPosition;																									///< 0x4D2
	Bool m_isGuardingPosition;																								///< 0x4D3
	Bool m_overriddenAttack;																									///< 0x4D4
	Bool m_bfmeFlag4D5;																												///< 0x4D5
	Bool m_bfmeFlag4D6;																												///< 0x4D6
};

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

	*xfer == m_bfmeFlag4A9;
	*xfer == m_bfmeFlag4A8;
	XferCommandResultTypes( xfer, &m_bfmeCommandResult4AC );
	*xfer == m_frameToWakeForDeploy;
	XferDeployStateTypes( xfer, &m_state );
	XferCommandResultTypes( xfer, &m_bfmeCommandResult4B0 );
	XferObjectID( xfer, &m_designatedTargetID );
	XferObjectID( xfer, &m_attackObjectID );
	*xfer == m_position;
	*xfer == m_isAttackMultiple;
	*xfer == m_isAttackObject;
	*xfer == m_isAttackPosition;
	*xfer == m_isGuardingPosition;
	*xfer == m_overriddenAttack;
	*xfer == m_bfmeFlag4D5;
	*xfer == m_bfmeFlag4D6;

	m_lastOutsideCommand.doXfer( xfer );

}  // end xfer
