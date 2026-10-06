// cl: /DNDEBUG /MD /EHsc
// class-gate: allow AsciiString retail forwards the single dword name key as VAsciiString to the rowed base 0x004D79E1 with no copy, as in Rva0034B952Ctor.cpp
//
// Zero Hour's AIAttackMoveStateMachine and the three states that own one,
// from GameEngine/Source/GameLogic/AI/AIStates.cpp (GeneralsMD tree vendored
// under reference/open-bfme-1/inputs/reference). Target evidence:
//  - AIAttackMoveStateMachine::AIAttackMoveStateMachine, retail 0x0034C6EF
//    (206 bytes): vtable 0x00C11E58, whose slot-2 name getter returns
//    "AIAttackMOveStateMachine" (sic; ZH spells the class
//    AIAttackMoveStateMachine). BFME 2 passes the machine's name as a
//    dword key (every caller pushes an immediate), forwarded unchanged as
//    the rowed StateMachine base ctor 0x004D79E1's (owner, name, false),
//    then ZH's three states in ZH's order: idle
//    (rowed ctor 0x0033FE65, argument 1), pick-up-crate (rowed 0x00342B87)
//    and attack (rowed AIAttackState 0x0034B0DD with false, true, false,
//    NULL), ids 0, 0x27 and 0xA, every success and failure id 0 (idle).
//  - AIAttackMoveToState::AIAttackMoveToState, retail 0x0034EBE8 (147
//    bytes): vtable 0x00C13548, whose slot 4 and 5 are the rowed
//    AIAttackMoveToState::onEnter and onExit. Base is the rowed
//    Rva0034005D ctor (ZH's AIMoveToState), whose +0x4C flag this ctor
//    clears; the machine (name key 0xc586154e) is kept at +0x54; BFME 2
//    adds +0x50, +0x58, +0x5C (5), a cleared Coord3D at +0x60 and +0x6C.
//  - AIAttackFollowWaypointPathState::AIAttackFollowWaypointPathState,
//    retail 0x0034F153 (113 bytes): vtable 0x00C13638 (slots 4-6 rowed
//    under this name), base the rowed (machine, asGroup, false) ctor
//    0x00342BFC; machine name key 0x1b42b558 at +0x68.
//  - AIFollowPathAsTeamState::AIFollowPathAsTeamState, retail 0x0034E307
//    (158 bytes): vtable 0x00C121E8 (slot-2 getter AIFollowPathAsTeamState,
//    slot 5 rowed under this name). The AIInternalMoveToState ctor
//    0x0033F279 with the caller's name key; the attack-move machine (name
//    key 0xc586154e, +0x5C) is created only when the Bool argument is set.
//    No ZH counterpart: members keep offset names.
// Every machine is created with plain operator new and started through its
// vslot 7 (initDefaultState, 0x004D770F in the machine's vtable).
typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef UnsignedInt StateID;
#define NULL 0
class AsciiString
{
public:
	AsciiString(UnsignedInt nameKey) : m_nameKey(nameKey) {}
	UnsignedInt m_nameKey;
};
#include "../../../../Libraries/Include/Lib/Coord3D.h"
class Object;
class AttackExitConditionsInterface;
struct StateConditionInfo;
struct State;
enum StateReturnType
{
	STATE_CONTINUE = 0
};
enum
{
	AI_IDLE = 0,
	AI_ATTACK_OBJECT = 0xA,
	AI_PICK_UP_CRATE = 0x27
};
class StateMachine
{
public:
	virtual ~StateMachine();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual StateReturnType updateStateMachine();
	virtual void clear();
	virtual StateReturnType resetToDefaultState();
	virtual StateReturnType initDefaultState();
	void defineState(StateID id, State *state, StateID successID, StateID failureID, const StateConditionInfo *conditions = NULL);
	Object *getOwner() const { return m_owner; }
protected:
	unsigned char m_pad04[0x14 - 0x04];
	Object *m_owner; // +0x14
	unsigned char m_pad18[0x3C - 0x18]; // operator new size 0x3C
};
// BFME 2's StateMachine constructor (owner, name, flag), rowed by address.
class Rva004D759C : public StateMachine
{
public:
	Rva004D759C(Object *owner, AsciiString name, Bool flag);
	virtual ~Rva004D759C();
};
class AIAttackMoveStateMachine : public Rva004D759C
{
public:
	AIAttackMoveStateMachine(Object *owner, UnsignedInt nameKey);
};
struct State
{
public:
	virtual ~State();
	Object *getMachineOwner() const { return m_machine->getOwner(); }
protected:
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
	unsigned char m_pad1C[0x20 - 0x1C];
};
class Rva0033FE65 : public State
{
public:
	Rva0033FE65(StateMachine *machine, int val);
private:
	unsigned char m_pad20[0x28 - 0x20];
};
class Rva00342B87 : public State
{
public:
	Rva00342B87(StateMachine *machine);
private:
	unsigned char m_pad20[0x50 - 0x20];
};
class AIAttackState : public State
{
public:
	AIAttackState(StateMachine *machine, Bool follow, Bool attackingObject, Bool forceAttacking, AttackExitConditionsInterface *attackParameters);
private:
	unsigned char m_pad20[0x50 - 0x20];
};

AIAttackMoveStateMachine::AIAttackMoveStateMachine(Object *owner, UnsignedInt nameKey) : Rva004D759C(owner, AsciiString(nameKey), false)
{
	// order matters: first state is the default state.
	defineState( AI_IDLE, new Rva0033FE65( this, 1 ), AI_IDLE, AI_IDLE );
	defineState( AI_PICK_UP_CRATE, new Rva00342B87( this ), AI_IDLE, AI_IDLE );
	defineState( AI_ATTACK_OBJECT, new AIAttackState( this, false, true, false, NULL ), AI_IDLE, AI_IDLE );
}

// Zero Hour's Coord3D::zero(); VC7.1 keeps an inlined call's stores in
// source order after the preceding ones, where plain member stores are not.
inline void zeroCoord3D(Coord3D &c)
{
	c.x = 0.0f;
	c.y = 0.0f;
	c.z = 0.0f;
}
class AIInternalMoveToState : public State
{
public:
	AIInternalMoveToState(StateMachine *machine, unsigned int hash);
	virtual ~AIInternalMoveToState();
protected:
	unsigned char m_pad20[0x4C - 0x20];
};
// ZH's AIMoveToState, rowed by address.
class Rva0034005D : public AIInternalMoveToState
{
public:
	Rva0034005D(StateMachine *machine);
protected:
	Bool m_unk4C; // +0x4C
};
class AIAttackMoveToState : public Rva0034005D
{
public:
	AIAttackMoveToState(StateMachine *machine);
private:
	Int m_50;
	StateMachine *m_attackMoveMachine; // +0x54
	UnsignedInt m_58;
	Int m_5C;
	Coord3D m_60;
	Int m_6C;
};

AIAttackMoveToState::AIAttackMoveToState(StateMachine *machine) : Rva0034005D(machine)
{
	m_50 = 0;
	m_unk4C = false;
	m_58 = 0;
	m_5C = 5;
	m_attackMoveMachine = new AIAttackMoveStateMachine(getMachineOwner(), 0xc586154eu);
	m_attackMoveMachine->initDefaultState();
	zeroCoord3D(m_60);
	m_6C = 0;
}

// ZH's AIFollowWaypointPathState, rowed by address (BFME 2 adds a flag).
class Rva00342BAE : public AIInternalMoveToState
{
public:
	Rva00342BAE(StateMachine *machine, Bool asGroup, Bool flag2);
private:
	unsigned char m_pad4C[0x68 - 0x4C];
};
class AIAttackFollowWaypointPathState : public Rva00342BAE
{
public:
	AIAttackFollowWaypointPathState(StateMachine *machine, Bool asGroup);
private:
	StateMachine *m_attackFollowMachine; // +0x68
};

AIAttackFollowWaypointPathState::AIAttackFollowWaypointPathState(StateMachine *machine, Bool asGroup) : Rva00342BAE(machine, asGroup, false)
{
	m_attackFollowMachine = new AIAttackMoveStateMachine(getMachineOwner(), 0x1b42b558u);
	m_attackFollowMachine->initDefaultState();
}

class AIFollowPathAsTeamState : public AIInternalMoveToState
{
public:
	AIFollowPathAsTeamState(StateMachine *machine, Bool attackMove, unsigned int hash);
private:
	Int m_4C;
	Int m_50;
	Bool m_54;
	Bool m_55;
	Bool m_56;
	Bool m_57;
	Int m_58;
	StateMachine *m_attackMoveMachine; // +0x5C
	Real m_60;
	Bool m_64;
};

AIFollowPathAsTeamState::AIFollowPathAsTeamState(StateMachine *machine, Bool attackMove, unsigned int hash) : AIInternalMoveToState(machine, hash)
{
	m_4C = 0;
	m_50 = 5;
	m_54 = true;
	m_55 = false;
	m_56 = false;
	m_57 = false;
	m_58 = 0;
	m_attackMoveMachine = NULL;
	m_60 = 0.0f;
	m_64 = false;
	if (attackMove)
	{
		m_attackMoveMachine = new AIAttackMoveStateMachine(getMachineOwner(), 0xc586154eu);
		m_attackMoveMachine->initDefaultState();
	}
}
