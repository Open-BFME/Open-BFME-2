// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
//
// AITNGuardMachine::AITNGuardMachine, retail 0x546001: a BFME 2 state machine constructor. The base
// is the rowed StateMachine constructor 0x004D79E1 with the name key 0x91632a45
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
	StateMachine(Object *owner, UnsignedInt nameKey, Bool flag);
	virtual ~StateMachine();
	void defineState(StateID id, State *state, StateID successID, StateID failureID, const StateConditionInfo *conditions = NULL);
protected:
	unsigned char m_pad04[0x3C - 0x04];
};
// BFME 2's StateMachine constructor (owner, name key, flag), rowed by address.
// Zero Hour's Coord3D::zero(); an inlined call keeps its stores in source order.
static __forceinline void zeroCoord3D(Coord3D &c)
{
	c.x = 0.0f;
	c.y = 0.0f;
	c.z = 0.0f;
}

class Rva00545DB0 : public State
{
public:
	Rva00545DB0(StateMachine *machine);
private:
	unsigned char m_pad04[0x58 - 0x04];
};
class Rva00545B4F : public State
{
public:
	Rva00545B4F(StateMachine *machine);
private:
	unsigned char m_pad04[0x30 - 0x04];
};
class AITNGuardInnerState : public State
{
public:
	AITNGuardInnerState(StateMachine *machine);
private:
	unsigned char m_pad04[0x30 - 0x04];
};
class Rva00545D7E : public State
{
public:
	Rva00545D7E(StateMachine *machine);
private:
	unsigned char m_pad04[0x2C - 0x04];
};
class Rva0036804F : public State
{
public:
	Rva0036804F(StateMachine *machine);
private:
	unsigned char m_pad04[0x50 - 0x04];
};
class AITNGuardAttackAggressorState : public State
{
public:
	AITNGuardAttackAggressorState(StateMachine *machine);
private:
	unsigned char m_pad04[0x2C - 0x04];
};
class AITNGuardMachine : public StateMachine
{
public:
	AITNGuardMachine(Object *owner);
	virtual ~AITNGuardMachine();
	Coord3D m_positionToGuard;	// +0x3C
	ObjectID m_nemesisToAttack;	// +0x48
	UnsignedInt m_4C;			// +0x4C
};
// condition 0x00545F10 (retail .rdata table entry)
Bool rva00545F10(State *thisState, void *userData);

AITNGuardMachine::AITNGuardMachine(Object *owner) : StateMachine(owner, 0x91632a45u, false)
{
	static const StateConditionInfo g_condC6A2FC[] =
	{
		{ (void *)rva00545F10, 5005, NULL },
		{ NULL, 0, NULL }	// keep last
	};
	m_nemesisToAttack = 0;
	m_4C = 0;
	zeroCoord3D(m_positionToGuard);
	// order matters: first state is the default state.
	defineState( 5003, new Rva00545DB0( this ), 5001, 5000, g_condC6A2FC );
	defineState( 5001, new Rva00545B4F( this ), 5000, 5003 );
	defineState( 5000, new AITNGuardInnerState( this ), 5002, 5002, g_condC6A2FC );
	defineState( 5002, new Rva00545D7E( this ), 5004, 5004 );
	defineState( 5004, new Rva0036804F( this ), 5003, 5003 );
	defineState( 5005, new AITNGuardAttackAggressorState( this ), 5003, 5003 );
}
