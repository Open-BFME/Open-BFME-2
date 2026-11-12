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

// Snapshot xfer methods of Zero Hour AITNGuard.cpp (GeneralsMD tree vendored
// under reference/open-bfme-1/inputs/reference) in BFME 2's Xfer spelling,
// identified as slot 3 of the vftables whose slot-2 name getters return
// AITNGuardInnerState, AITNGuardReturnState and AITNGuardMachine.
// BFME 2 differences: the inner state xfers a Bool (+0x28); the return state
// runs AIEnterState's xfer (0x00341930) and the light-CRC early-out before
// its version; the machine runs the StateMachine base first, then the
// light-CRC early-out and Version(1,2), with four version-2 raw bytes
// (+0x4C) after ZH's nemesis and guard position.

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

#include "../../../Include/Common/StateMachine.h"
#include "../../../Include/GameLogic/AITNGuard.h"

// The state base: only its virtual table matters to these bodies.

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID( Xfer *xfer, ObjectID *id );

#include "../../../Include/Common/StateMachineClass.h"

// AIEnterState: its xfer 0x00341930 is rowed under the placeholder Rva00341930.
class Rva00341930 : public State
{
protected:
	virtual void xfer( Xfer *xfer );
};

// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
class AITNGuardReturnState : public Rva00341930
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	char m_unrecovered20[ 0x54 - sizeof(State) ];
	UnsignedInt m_nextReturnScanTime;																					///< 0x54
};

// ------------------------------------------------------------------------------------------------
#include "../../../Include/GameLogic/AITNGuardMachine.h"

// ------------------------------------------------------------------------------------------------
/** Xfer Method */
// ------------------------------------------------------------------------------------------------
void AITNGuardInnerState::xfer( Xfer *xfer )
{
	xfer->Version1();
	*xfer == m_scanForEnemy;
}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Xfer Method */
// ------------------------------------------------------------------------------------------------
void AITNGuardReturnState::xfer( Xfer *xfer )
{
	Rva00341930::xfer(xfer);
	if( xfer->IsLightCRC() )
		return;
	xfer->Version1();
	*xfer == m_nextReturnScanTime;
}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Xfer Method */
// ------------------------------------------------------------------------------------------------
void AITNGuardMachine::xfer( Xfer *xfer )
{
	StateMachine::xfer(xfer);
	if( xfer->IsLightCRC() )
		return;
	Xfer::Version version( 1, 2 );
	*xfer == version;
	XferObjectID( xfer, reinterpret_cast<ObjectID *>(&m_nemesisToAttack) );
	*xfer == asBase(m_positionToGuard);
	if( version.m_minimum >= 2 )
		xfer->XferRawBytes( &m_guardMode, 4 );
}  // end xfer
