// cl: /DNDEBUG /MD /GX /Ireference/shims/moduledata
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

// Snapshot xfer methods of Zero Hour AIStates.cpp states (GeneralsMD tree
// vendored under reference/open-bfme-1/inputs/reference) in BFME 2's Xfer
// spelling. Each is slot 3 of its state's vftable, identified by the
// slot-2 name getter. Base xfers: AIInternalMoveToState (0x0033FF76) and,
// in BFME 2, AIIdleState (0x0033FEA3) under AIFaceState. BFME 2 adds one
// more Bool to AIAttackAimAtTargetState (+0x23) and a version-2 Bool to
// AIExitState (+0x24). Its Version struct is passed by reference and its
// operator== chains. The BFME 2-only states below them (AIMoveToStateSA,
// BackAwayAndCowerStateMachine, AIUncontrollableCower, the melee horde-wait,
// melee approach/squish and fire-during-approach states, and
// AIAttackPositionAimAtTargetState, AIHordeExitState and AIRampageState) are
// named the same way; their members are known only by offset and by the
// Xfer overload each is passed to. AIMoveOntoWallState and AIHarvestState
// save a sub-machine the way Zero Hour's attack states do (has-machine Bool,
// recreated with a 0x3C-byte new on load, then its snapshot). The
// giant-bird states and GiantBirdGuardMachine at the end are named the same
// way; the guard-state body also fills the attack-aggressor and inner guard
// tables, and the AIGiantBirdAttack body the DozerActionMoveToActionPosState
// table (identical code, named by the first table). AIEnterAndAttackState
// and GiantBirdGuardReturnState follow.

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
#include "Common/Snapshot.h"

#include "../../../Include/Common/BfmeXfer.h"

#include "../../../Include/Common/XferVersion.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

#include "../../../../Libraries/Include/Lib/Coord3DBase.h"

#include "../../../../Libraries/Include/Lib/ICoord2D.h"

#include "../../../Include/Common/StateMachineClass.h"

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID( Xfer *xfer, ObjectID *id );


#include "../../../Include/GameLogic/AIInternalMoveToState.h"

class AIIdleState : public State
{
protected:
	virtual void xfer( Xfer *xfer );
	unsigned short m_20, m_22; bool m_24, m_25; char m_unrecovered26[0x2C - 0x26];
};

// ------------------------------------------------------------------------------------------------
class AIMoveAndEvacuateState : public AIInternalMoveToState
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	Coord3DBase m_origin;																											///< 0x4C
};

// ------------------------------------------------------------------------------------------------
class AIMoveAndDeleteState : public AIInternalMoveToState
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	Bool m_appendGoalPosition;																								///< 0x4C
};

// ------------------------------------------------------------------------------------------------
class AIFaceState : public AIIdleState
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	Bool m_canTurnInPlace;																										///< 0x2C
};

// ------------------------------------------------------------------------------------------------
class AIAttackAimAtTargetState : public State
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	char m_pad20[0x21 - 0x20];
	Bool m_canTurnInPlace;																										///< 0x21
	Bool m_setLocomotor;																											///< 0x22
	Bool m_bfmeFlag23;																												///< 0x23
};

// ------------------------------------------------------------------------------------------------
class AIExitState : public State
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	ObjectID m_entryToClear;																									///< 0x20
	Bool m_bfmeFlag24;																												///< 0x24
};

// ------------------------------------------------------------------------------------------------
// BFME 2 states with no Zero Hour counterpart, named by their tables'
// slot-2 name literals; members are labelled by offset and Xfer type only.
class AIMoveToStateSA : public AIInternalMoveToState
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	UnsignedInt m_bfmeValue4C;																								///< 0x4C
	Bool m_bfmeFlag50;																												///< 0x50
};

class BackAwayAndCowerStateMachine : public StateMachine
{
protected:
	virtual void xfer( Xfer *xfer );
};

class AIUncontrollableCower : public State
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	Bool m_bfmeFlag20;																												///< 0x20
};

class AIAttackMeleeHordeWaitState : public State
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	UnsignedInt m_bfmeValue20;																								///< 0x20
};

class AIAttackMeleeHordeWaitPathState : public State
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	UnsignedInt m_bfmeValue20;																								///< 0x20
	Int m_bfmeValue24;																												///< 0x24
};

class AIAttackMeleeApproachState : public AIInternalMoveToState
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	UnsignedInt m_bfmeValue4C;																								///< 0x4C
	Coord3DBase m_bfmePosition50;																							///< 0x50
	ICoord2D m_bfmeCell5C;																										///< 0x5C
};

class AIAttackFireDuringApproachState : public AIInternalMoveToState
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	UnsignedInt m_bfmeValue4C;																								///< 0x4C
	Coord3DBase m_bfmePosition50;																							///< 0x50
	ICoord2D m_bfmeCell5C;																										///< 0x5C
	ObjectID m_bfmeObject64;																									///< 0x64
	Bool m_bfmeFlag68;																												///< 0x68
};

class AIAttackMeleeSquishState : public AIInternalMoveToState
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	UnsignedInt m_bfmeValue4C;																								///< 0x4C
	Coord3DBase m_bfmePosition50;																							///< 0x50
	ICoord2D m_bfmeCell5C;																										///< 0x5C
	Bool m_bfmeFlag64;																												///< 0x64
};

class AIAttackPositionAimAtTargetState : public State
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	Bool m_bfmeFlag20;																												///< 0x20
	Bool m_bfmeFlag21;																												///< 0x21
};

class AIHordeExitState : public State
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	Bool m_bfmeFlag20;																												///< 0x20
};

class AIRampageState : public State
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	Bool m_bfmeFlag20;																												///< 0x20
	UnsignedInt m_bfmeValue24;																								///< 0x24
	UnsignedInt m_bfmeValue28;																								///< 0x28
};

// The sub-machines two BFME 2 states own and recreate on load; their
// constructors are pinned by address (owner identities from their tables'
// slot-2 name literals: MoveOntoWallStateMachine and AIHarvestMachine).
class Object;
class Rva0033FC0A : public Snapshot
{
public:
	Rva0033FC0A( Object *owner, UnsignedInt nameKey );
protected:
	virtual void crc( Xfer *xfer );
	virtual void xfer( Xfer *xfer );
	virtual void loadPostProcess( void );
private:
	char m_unrecovered04[ 0x3C - 0x04 ];																				///< to 0x3C bytes (operator new size)
};

class Rva00544C51 : public Snapshot
{
public:
	Rva00544C51( Object *owner );
protected:
	virtual void crc( Xfer *xfer );
	virtual void xfer( Xfer *xfer );
	virtual void loadPostProcess( void );
private:
	char m_unrecovered04[ 0x3C - 0x04 ];																				///< to 0x3C bytes (operator new size)
};

class AIMoveOntoWallState : public State
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	Rva0033FC0A *m_wallMachine;																								///< 0x20
};

class AIHarvestState : public State
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	Rva00544C51 *m_harvestMachine;																						///< 0x20
	Bool m_bfmeFlag24;																												///< 0x24
};

// BFME 2 giant-bird states and guard machine, named the same way.
#include "../../../Include/GameLogic/AIGuardMachine.h"

class GiantBirdGuardMachine : public AIGuardMachine
{
protected:
	virtual void xfer( Xfer *xfer );
};

class AIGiantBirdFollowThruState : public State
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	Bool m_bfmeFlag20;																												///< 0x20
	Int m_bfmeValue24;																												///< 0x24
};

class GiantBirdGuardOuterState : public State
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	char m_pad20[0x24 - 0x20];
	Int m_bfmeValue24;																												///< 0x24
	Coord3DBase m_bfmePosition28;																							///< 0x28
	float m_bfmeReal34;																												///< 0x34
	UnsignedInt m_bfmeValue38;																								///< 0x38
};

class AIGiantBirdSwoopState : public State
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	UnsignedInt m_bfmeRaw20;																									///< 0x20, 4 raw bytes
	Coord3DBase m_bfmePosition24;																							///< 0x24
	Bool m_bfmeFlag30;																												///< 0x30
	UnsignedInt m_bfmeValue34;																								///< 0x34
	float m_bfmeReal38;																												///< 0x38
};

class AIGiantBirdAttack : public State
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	UnsignedInt m_bfmeRaw20;																									///< 0x20, 4 raw bytes
};

class AIEnterAndAttackState : public AIInternalMoveToState
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	ObjectID m_bfmeObject4C;																									///< 0x4C
	ObjectID m_bfmeObject50;																									///< 0x50
};

class GiantBirdGuardReturnState : public State
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	char m_pad20[0x24 - 0x20];
	UnsignedInt m_bfmeValue24;																								///< 0x24
	Coord3DBase m_bfmePosition28;																							///< 0x28
};

// ------------------------------------------------------------------------------------------------
/** Xfer Method */
// ------------------------------------------------------------------------------------------------
void AIMoveAndEvacuateState::xfer( Xfer *xfer )
{
	xfer->Version1();
	AIInternalMoveToState::xfer(xfer);
	*xfer == m_origin;
}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Xfer Method */
// ------------------------------------------------------------------------------------------------
void AIMoveAndDeleteState::xfer( Xfer *xfer )
{
	Xfer::Version version( 1, 1 );
	*xfer == version;
	AIInternalMoveToState::xfer(xfer);
	*xfer == m_appendGoalPosition;
}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Xfer Method */
// ------------------------------------------------------------------------------------------------
void AIFaceState::xfer( Xfer *xfer )
{
	AIIdleState::xfer(xfer);
	Xfer::Version version( 1, 1 );
	*xfer == version == m_canTurnInPlace;
}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Xfer Method */
// ------------------------------------------------------------------------------------------------
void AIAttackAimAtTargetState::xfer( Xfer *xfer )
{
	xfer->Version1();
	*xfer == m_canTurnInPlace;
	*xfer == m_setLocomotor;
	*xfer == m_bfmeFlag23;
}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Xfer Method */
// ------------------------------------------------------------------------------------------------
void AIExitState::xfer( Xfer *xfer )
{
	Xfer::Version version( 1, 2 );
	*xfer == version;
	XferObjectID( xfer, &m_entryToClear );
	if( version.m_minimum >= 2 )
		*xfer == m_bfmeFlag24;
}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Xfer Method */
// ------------------------------------------------------------------------------------------------
void AIMoveToStateSA::xfer( Xfer *xfer )
{
	Xfer::Version version( 1, 1 );
	*xfer == version;
	AIInternalMoveToState::xfer(xfer);
	if( xfer->IsLightCRC() )
		return;
	*xfer == m_bfmeValue4C;
	*xfer == m_bfmeFlag50;
}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Xfer Method */
// ------------------------------------------------------------------------------------------------
void BackAwayAndCowerStateMachine::xfer( Xfer *xfer )
{
	xfer->Version1();
	StateMachine::xfer(xfer);
}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Xfer Method */
// ------------------------------------------------------------------------------------------------
void AIUncontrollableCower::xfer( Xfer *xfer )
{
	xfer->Version1();
	*xfer == m_bfmeFlag20;
	xfer->Version1();
}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Xfer Method */
// ------------------------------------------------------------------------------------------------
void AIAttackMeleeHordeWaitState::xfer( Xfer *xfer )
{
	xfer->Version1();
	if( xfer->IsLightCRC() )
		return;
	*xfer == m_bfmeValue20;
}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Xfer Method */
// ------------------------------------------------------------------------------------------------
void AIAttackMeleeHordeWaitPathState::xfer( Xfer *xfer )
{
	Xfer::Version version( 1, 2 );
	*xfer == version;
	if( xfer->IsLightCRC() )
		return;
	*xfer == m_bfmeValue20;
	if( version.m_minimum > 1 )
		*xfer == m_bfmeValue24;
}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Xfer Method */
// ------------------------------------------------------------------------------------------------
void AIAttackMeleeApproachState::xfer( Xfer *xfer )
{
	xfer->Version1();
	AIInternalMoveToState::xfer(xfer);
	if( xfer->IsLightCRC() )
		return;
	*xfer == m_bfmePosition50;
	*xfer == m_bfmeCell5C;
	*xfer == m_bfmeValue4C;
}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Xfer Method */
// ------------------------------------------------------------------------------------------------
void AIAttackFireDuringApproachState::xfer( Xfer *xfer )
{
	xfer->Version1();
	AIInternalMoveToState::xfer(xfer);
	if( xfer->IsLightCRC() )
		return;
	*xfer == m_bfmePosition50;
	*xfer == m_bfmeCell5C;
	*xfer == m_bfmeValue4C;
	XferObjectID( xfer, &m_bfmeObject64 );
	*xfer == m_bfmeFlag68;
}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Xfer Method */
// ------------------------------------------------------------------------------------------------
void AIAttackMeleeSquishState::xfer( Xfer *xfer )
{
	xfer->Version1();
	AIInternalMoveToState::xfer(xfer);
	if( xfer->IsLightCRC() )
		return;
	*xfer == m_bfmePosition50;
	*xfer == m_bfmeCell5C;
	*xfer == m_bfmeValue4C;
	*xfer == m_bfmeFlag64;
}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Xfer Method */
// ------------------------------------------------------------------------------------------------
void AIAttackPositionAimAtTargetState::xfer( Xfer *xfer )
{
	xfer->Version1();
	*xfer == m_bfmeFlag20;
	*xfer == m_bfmeFlag21;
}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Xfer Method */
// ------------------------------------------------------------------------------------------------
void AIHordeExitState::xfer( Xfer *xfer )
{
	Xfer::Version version( 1, 2 );
	*xfer == version;
	if( version.m_minimum >= 2 )
		*xfer == m_bfmeFlag20;
}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Xfer Method */
// ------------------------------------------------------------------------------------------------
void AIRampageState::xfer( Xfer *xfer )
{
	Xfer::Version version( 1, 1 );
	*xfer == version;
	*xfer == m_bfmeFlag20;
	*xfer == m_bfmeValue24;
	*xfer == m_bfmeValue28;
}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Xfer Method */
// ------------------------------------------------------------------------------------------------
void AIMoveOntoWallState::xfer( Xfer *xfer )
{
	xfer->Version1();
	Bool hasMachine = m_wallMachine != 0;
	*xfer == hasMachine;
	if( hasMachine && m_wallMachine == 0 )
		m_wallMachine = new Rva0033FC0A( getMachineOwner(), 0xD30E2FB3 );
	if( hasMachine )
		*xfer == *m_wallMachine;
}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Xfer Method */
// ------------------------------------------------------------------------------------------------
void AIHarvestState::xfer( Xfer *xfer )
{
	if( xfer->IsLightCRC() )
		return;
	xfer->Version1();
	Bool hasMachine = m_harvestMachine != 0;
	*xfer == hasMachine;
	if( hasMachine && m_harvestMachine == 0 )
		m_harvestMachine = new Rva00544C51( getMachineOwner() );
	if( hasMachine )
		*xfer == *m_harvestMachine;
	*xfer == m_bfmeFlag24;
}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Xfer Method */
// ------------------------------------------------------------------------------------------------
void GiantBirdGuardMachine::xfer( Xfer *xfer )
{
	xfer->Version1();
	if( !xfer->IsLightCRC() )
		AIGuardMachine::xfer( xfer );
}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Xfer Method */
// ------------------------------------------------------------------------------------------------
void AIGiantBirdFollowThruState::xfer( Xfer *xfer )
{
	Xfer::Version version( 1, 2 );
	*xfer == version;
	*xfer == m_bfmeFlag20;
	if( version.m_minimum >= 2 )
		*xfer == m_bfmeValue24;
}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Xfer Method */
// ------------------------------------------------------------------------------------------------
void GiantBirdGuardOuterState::xfer( Xfer *xfer )
{
	xfer->Version1();
	*xfer == m_bfmeValue38;
	*xfer == m_bfmePosition28;
	*xfer == m_bfmeValue24;
	*xfer == m_bfmeReal34;
}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Xfer Method */
// ------------------------------------------------------------------------------------------------
void AIGiantBirdSwoopState::xfer( Xfer *xfer )
{
	xfer->Version1();
	xfer->XferRawBytes( &m_bfmeRaw20, 4 );
	*xfer == m_bfmePosition24;
	*xfer == m_bfmeFlag30;
	*xfer == m_bfmeValue34;
	*xfer == m_bfmeReal38;
}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Xfer Method */
// ------------------------------------------------------------------------------------------------
void AIGiantBirdAttack::xfer( Xfer *xfer )
{
	xfer->Version1();
	xfer->XferRawBytes( &m_bfmeRaw20, 4 );
}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Xfer Method */
// ------------------------------------------------------------------------------------------------
void AIEnterAndAttackState::xfer( Xfer *xfer )
{
	xfer->Version1();
	AIInternalMoveToState::xfer(xfer);
	XferObjectID( xfer, &m_bfmeObject4C );
	XferObjectID( xfer, &m_bfmeObject50 );
}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Xfer Method */
// ------------------------------------------------------------------------------------------------
void GiantBirdGuardReturnState::xfer( Xfer *xfer )
{
	xfer->Version1();
	*xfer == m_bfmeValue24;
	*xfer == m_bfmePosition28;
}  // end xfer

// Native AIIdleState snapshot, vftable RVA 0x00811E08 slot 3.
void AIIdleState::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 2);
	*xfer == version;
	*xfer == m_20;
	*xfer == m_24;
	*xfer == m_25;
	if (version.m_minimum >= 2) {
		*xfer == m_22;
	}
}
