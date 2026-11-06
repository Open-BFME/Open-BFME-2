// cl: /Ireference/shims/moduledata /DNDEBUG /MD /GX
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


// AIGuardRetaliateState::xfer and AITunnelNetworkGuardState::xfer, ported from
// Zero Hour's GameEngine/Source/GameLogic/AI/AIStates.cpp (GeneralsMD tree
// vendored under reference/open-bfme-1/inputs/reference). Each is slot 3 of
// the vftable whose name getter returns its class: 0x00C117F0
// (0x0033F745, "AIGuardRetaliateState") and
// 0x00C11850 (0x0033F76C, "AITunnelNetworkGuardState").
//
// BFME 2 opens with the light-CRC gate and Version1. The machine member sits
// at +0x20, and the owner comes from the state's machine (+0x18) at +0x14. The
// sub-machines are allocated by plain operator new: AIGuardRetaliateMachine
// (0x4C bytes, ctor 0x0054551F) and AITNGuardMachine (0x50 bytes, ctor
// 0x00546001).

#include "Common/Snapshot.h"

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

class Object;

class AIGuardRetaliateMachine : public Snapshot
{
public:
	AIGuardRetaliateMachine( Object *owner );
protected:
	virtual void crc( Xfer *xfer );
	virtual void xfer( Xfer *xfer );
	virtual void loadPostProcess( void );
private:
	char m_unrecovered04[ 0x4C - 0x04 ];
};

class AITNGuardMachine : public Snapshot
{
public:
	AITNGuardMachine( Object *owner );
protected:
	virtual void crc( Xfer *xfer );
	virtual void xfer( Xfer *xfer );
	virtual void loadPostProcess( void );
private:
	char m_unrecovered04[ 0x50 - 0x04 ];
};

#include "../../../Include/Common/StateMachine.h"
#include "../../../Include/Common/StateMachineClass.h"

// ------------------------------------------------------------------------------------------------
class AIGuardRetaliateState : public State
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	AIGuardRetaliateMachine *m_guardRetaliateMachine;													///< 0x20
};

// ------------------------------------------------------------------------------------------------
class AITunnelNetworkGuardState : public State
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	AITNGuardMachine *m_guardMachine;																					///< 0x20
};

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void AIGuardRetaliateState::xfer( Xfer *xfer )
{
	if( xfer->IsLightCRC() )
		return;

	// version
	xfer->Version1();

	Bool hasMachine = m_guardRetaliateMachine!=0;

	*xfer == hasMachine;

	if (hasMachine && m_guardRetaliateMachine==0)
	{
		// create new state machine for guard behavior
		m_guardRetaliateMachine = new AIGuardRetaliateMachine( getMachineOwner() );
	}
	if (hasMachine)
	{
		*xfer == *m_guardRetaliateMachine;
	}

}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void AITunnelNetworkGuardState::xfer( Xfer *xfer )
{
	if( xfer->IsLightCRC() )
		return;

	// version
	xfer->Version1();

	Bool hasMachine = m_guardMachine!=0;

	*xfer == hasMachine;

	if (hasMachine && m_guardMachine==0)	{
		// create new state machine for guard behavior
		m_guardMachine = new AITNGuardMachine( getMachineOwner() );
	}
	if (hasMachine) {
		*xfer == *m_guardMachine;
	}

}  // end xfer
