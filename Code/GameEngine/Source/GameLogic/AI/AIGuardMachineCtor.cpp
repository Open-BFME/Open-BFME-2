// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
//
// AIGuardMachine::AIGuardMachine, retail 0x543163: a BFME 2 state machine constructor. The base
// is the rowed StateMachine constructor 0x004D79E1 with the caller's name key
// (its unsigned spelling is pinned); each state comes from plain operator
// new and its rowed constructor, registered with the IDs and transitions
// read from the retail call sequence (Zero Hour's defineState pattern).
#include "../../../../Libraries/Include/Lib/Coord3D.h"
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef UnsignedInt StateID;
typedef UnsignedInt ObjectID;
#define NULL 0
class Object;
struct StateConditionInfo
{
	void *m_test;
	StateID m_toStateID;
	void *m_userData;
};
struct State
{
public:
	virtual ~State();
};
class StateMachine
{
public:
	virtual ~StateMachine();
	void defineState(StateID id, State *state, StateID successID, StateID failureID, const StateConditionInfo *conditions = NULL);
protected:
	unsigned char m_pad04[0x3C - 0x04];
};
// BFME 2's StateMachine constructor (owner, name key, flag), rowed by address.
class Rva004D759C : public StateMachine
{
public:
	Rva004D759C(Object *owner, UnsignedInt nameKey, Bool flag);
	virtual ~Rva004D759C();
};
// Zero Hour's Coord3D::zero(); an inlined call keeps its stores in source order.
static __forceinline void zeroCoord3D(Coord3D &c)
{
	c.x = 0.0f;
	c.y = 0.0f;
	c.z = 0.0f;
}

class AIGuardReturnState : public State
{
public:
	AIGuardReturnState(StateMachine *machine);
private:
	unsigned char m_pad04[0x50 - 0x04];
};
class Rva00542D25 : public State
{
public:
	Rva00542D25(StateMachine *machine);
private:
	unsigned char m_pad04[0x30 - 0x04];
};
class AIGuardInnerState : public State
{
public:
	AIGuardInnerState(StateMachine *machine);
private:
	unsigned char m_pad04[0x48 - 0x04];
};
class AIGuardOuterState : public State
{
public:
	AIGuardOuterState(StateMachine *machine);
private:
	unsigned char m_pad04[0x44 - 0x04];
};
class Rva0036804F : public State
{
public:
	Rva0036804F(StateMachine *machine);
private:
	unsigned char m_pad04[0x50 - 0x04];
};
class AIGuardAttackAggressorState : public State
{
public:
	AIGuardAttackAggressorState(StateMachine *machine);
private:
	unsigned char m_pad04[0x44 - 0x04];
};
class AIGuardMachine : public Rva004D759C
{
public:
	AIGuardMachine(Object *owner, UnsignedInt nameKey);
	virtual ~AIGuardMachine();
	ObjectID m_targetToGuard;	// +0x3C
	void *m_areaToGuard;		// +0x40
	ObjectID m_nemesisToAttack;	// +0x44
	Coord3D m_positionToGuard;	// +0x48
	Coord3D m_54;				// +0x54
	Bool m_60;					// +0x60
	float m_64;					// +0x64
	UnsignedInt m_68;			// +0x68
	UnsignedInt m_6C;			// +0x6C
	UnsignedInt m_70;			// +0x70
};
// condition 0x005430E7 (retail .rdata table entry)
Bool rva005430E7(State *thisState, void *userData);

AIGuardMachine::AIGuardMachine(Object *owner, UnsignedInt nameKey) : Rva004D759C(owner, nameKey, false)
{
	static const StateConditionInfo g_condC698F0[] =
	{
		{ (void *)rva005430E7, 5005, NULL },
		{ NULL, 0, NULL }	// keep last
	};
	m_targetToGuard = 0;
	m_areaToGuard = NULL;
	m_nemesisToAttack = 0;
	zeroCoord3D(m_positionToGuard);
	zeroCoord3D(m_54);
	m_60 = false;
	m_64 = 0.0f;
	m_68 = 0;
	m_6C = 0;
	m_70 = 0;
	// order matters: first state is the default state.
	defineState( 5003, new AIGuardReturnState( this ), 5001, 5000, g_condC698F0 );
	defineState( 5001, new Rva00542D25( this ), 5000, 5003, g_condC698F0 );
	defineState( 5000, new AIGuardInnerState( this ), 5002, 5002 );
	defineState( 5002, new AIGuardOuterState( this ), 5004, 5004 );
	defineState( 5004, new Rva0036804F( this ), 5003, 5003 );
	defineState( 5005, new AIGuardAttackAggressorState( this ), 5003, 5003 );
}
