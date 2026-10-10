// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
//
// AIDockMachine::AIDockMachine, retail 0x5448a1: a BFME 2 state machine constructor. The base
// is the rowed StateMachine constructor 0x004D79E1 with the name key 0x2b638eb7
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

class Rva005447ED : public State
{
public:
	Rva005447ED(StateMachine *machine);
private:
	unsigned char m_pad04[0x4C - 0x04];
};
class Rva00544095 : public State
{
public:
	Rva00544095(StateMachine *machine);
private:
	unsigned char m_pad04[0x24 - 0x04];
};
class Rva00544810 : public State
{
public:
	Rva00544810(StateMachine *machine);
private:
	unsigned char m_pad04[0x4C - 0x04];
};
class Rva0054482D : public State
{
public:
	Rva0054482D(StateMachine *machine);
private:
	unsigned char m_pad04[0x4C - 0x04];
};
class Rva0054484A : public State
{
public:
	Rva0054484A(StateMachine *machine);
private:
	unsigned char m_pad04[0x4C - 0x04];
};
class Rva005445D4 : public State
{
public:
	Rva005445D4(StateMachine *machine);
private:
	unsigned char m_pad04[0x28 - 0x04];
};
class Rva00544884 : public State
{
public:
	Rva00544884(StateMachine *machine);
private:
	unsigned char m_pad04[0x4C - 0x04];
};
class Rva00544867 : public State
{
public:
	Rva00544867(StateMachine *machine);
private:
	unsigned char m_pad04[0x4C - 0x04];
};
class AIDockMachine : public StateMachine
{
public:
	AIDockMachine(Object *owner);
	virtual ~AIDockMachine();
	// condition 0x005440F6, the only entry of the .rdata table 0x00869C78
	// (Zero Hour's ableToAdvance: wait-for-clearance -> advance-position)
	static Bool ableToAdvance(State *thisState, void *userData);
	int m_approachPosition;	// +0x3C dock approach slot (-1: none)
};

AIDockMachine::AIDockMachine(Object *owner) : StateMachine(owner, 0x2b638eb7u, false)
{
	static const StateConditionInfo g_condC69C78[] =
	{
		{ (void *)ableToAdvance, 2, NULL },
		{ NULL, 0, NULL }	// keep last
	};

	// order matters: first state is the default state.
	defineState( 0, new Rva005447ED( this ), 1, 9999 );
	defineState( 1, new Rva00544095( this ), 3, 9999, g_condC69C78 );
	defineState( 2, new Rva00544810( this ), 1, 9999 );
	defineState( 3, new Rva0054482D( this ), 4, 6 );
	defineState( 4, new Rva0054484A( this ), 5, 6 );
	defineState( 5, new Rva005445D4( this ), 6, 6 );
	defineState( 6, new Rva00544884( this ), 7, 9999 );
	defineState( 7, new Rva00544867( this ), 9998, 9999 );

	m_approachPosition = -1;
}
