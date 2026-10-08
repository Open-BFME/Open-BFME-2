// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
//
// Rva003676A2::Rva003676A2, retail 0x3676a2: a BFME 2 state machine constructor. The base
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

class Rva0036756A : public State
{
public:
	Rva0036756A(StateMachine *machine, int a0, Bool a1);
private:
	unsigned char m_pad04[0x3C - 0x04];
};
class Rva003675AC : public State
{
public:
	Rva003675AC(StateMachine *machine, int a0);
private:
	unsigned char m_pad04[0x24 - 0x04];
};
class Rva003675D6 : public State
{
public:
	Rva003675D6(StateMachine *machine, Bool a0);
private:
	unsigned char m_pad04[0x28 - 0x04];
};
class Rva0033FE65 : public State
{
public:
	Rva0033FE65(StateMachine *machine, int a0);
private:
	unsigned char m_pad04[0x28 - 0x04];
};
class Rva003676A2 : public Rva004D759C
{
public:
	Rva003676A2(Object *owner, UnsignedInt nameKey);
	virtual ~Rva003676A2();

};

Rva003676A2::Rva003676A2(Object *owner, UnsignedInt nameKey) : Rva004D759C(owner, nameKey, false)
{

	// order matters: first state is the default state.
	defineState( 10, new Rva0036756A( this, 1, false ), 1012, 0 );
	defineState( 1012, new Rva003675AC( this, 1 ), 1013, 1013 );
	defineState( 1013, new Rva003675D6( this, false ), 0, 0 );
	defineState( 0, new Rva0033FE65( this, 1 ), 0, 0 );
}
