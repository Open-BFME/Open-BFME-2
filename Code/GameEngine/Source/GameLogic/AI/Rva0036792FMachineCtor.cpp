// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
//
// Rva0036792F::Rva0036792F, retail 0x36792f: a BFME 2 state machine constructor. The base
// is the rowed StateMachine constructor 0x004D79E1 with the name key 0x0
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
class StateMachine;
struct State
{
public:
	virtual ~State();
protected:
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
};
class StateMachine
{
public:
	virtual ~StateMachine();
	void defineState(StateID id, State *state, StateID successID, StateID failureID, const StateConditionInfo *conditions = NULL);
	Object *getOwner() const { return m_owner; }
protected:
	unsigned char m_pad04[0x14 - 0x04];
	Object *m_owner; // +0x14
	unsigned char m_pad18[0x3C - 0x18];
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

class GiantBirdNormalFlightState : public State
{
public:
	GiantBirdNormalFlightState(StateMachine *machine, Bool a0, Bool a1);
private:
	unsigned char m_pad1C[0x24 - 0x1C];
};
class Rva0036756A : public State
{
public:
	Rva0036756A(StateMachine *machine, int a0, Bool a1);
private:
	unsigned char m_pad1C[0x3C - 0x1C];
};
class Rva003675AC : public State
{
public:
	Rva003675AC(StateMachine *machine, int a0);
private:
	unsigned char m_pad1C[0x24 - 0x1C];
};
class Rva003675D6 : public State
{
public:
	Rva003675D6(StateMachine *machine, Bool a0);
private:
	unsigned char m_pad1C[0x28 - 0x1C];
};
class Rva00367518 : public State
{
public:
	Rva00367518(StateMachine *machine);
private:
	unsigned char m_pad1C[0x5C - 0x1C];
};
class Rva00367647 : public State
{
public:
	Rva00367647(StateMachine *machine, Bool a0);
private:
	unsigned char m_pad1C[0x28 - 0x1C];
};
// The rowed sub-machine 0x003676A2; slot 7 (+0x1C) starts its default state.
class Rva003676A2
{
public:
	Rva003676A2(Object *owner, UnsignedInt nameKey);
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06();
	virtual void initDefaultState();
private:
	unsigned char m_pad04[0x3C - 0x04];
};
// A giant-bird flight state (0x003677BE) that runs its own 0x003676A2
// machine (name key 0xC586154E) from construction.
class Rva003677BE : public GiantBirdNormalFlightState
{
public:
	Rva003677BE(StateMachine *machine);
private:
	UnsignedInt m_24;			// +0x24
	Rva003676A2 *m_subMachine;	// +0x28
	int m_2C;					// +0x2C
};
class Rva003678F7 : public State
{
public:
	Rva003678F7(StateMachine *machine);
private:
	unsigned char m_pad1C[0x20 - 0x1C];
};
// Zero Hour's AIStateMachine (rowed constructor 0x00351C48).
class AIStateMachine : public Rva004D759C
{
public:
	AIStateMachine(Object *owner, UnsignedInt nameKey);
	virtual ~AIStateMachine();
private:
	unsigned char m_pad3C[0x68 - 0x3C];
};
class Rva0036792F : public AIStateMachine
{
public:
	Rva0036792F(Object *owner, UnsignedInt nameKey);
	virtual ~Rva0036792F();

};

Rva003677BE::Rva003677BE(StateMachine *machine) : GiantBirdNormalFlightState(machine, false, true)
{
	m_2C = 5;
	m_subMachine = new Rva003676A2(m_machine->getOwner(), 0xc586154eu);
	m_subMachine->initDefaultState();
	m_24 = 0;
}

Rva0036792F::Rva0036792F(Object *owner, UnsignedInt nameKey) : AIStateMachine(owner, nameKey)
{

	// order matters: first state is the default state.
	defineState( 1001, new GiantBirdNormalFlightState( this, false, true ), 78, 78 );
	defineState( 1002, new GiantBirdNormalFlightState( this, true, true ), 78, 78 );
	defineState( 1024, new GiantBirdNormalFlightState( this, false, true ), 0, 0 );
	defineState( 1010, new Rva0036756A( this, 1, false ), 1012, 0 );
	defineState( 1011, new Rva0036756A( this, 1, true ), 1012, 0 );
	defineState( 1012, new Rva003675AC( this, 1 ), 1013, 1013 );
	defineState( 1013, new Rva003675D6( this, false ), 0, 1010 );
	defineState( 1007, new Rva0036756A( this, 1, false ), 1008, 0 );
	defineState( 1008, new Rva003675AC( this, 1 ), 1009, 1009 );
	defineState( 1009, new Rva003675D6( this, true ), 1007, 1007 );
	defineState( 1003, new Rva0036756A( this, 0, false ), 1005, 0 );
	defineState( 1004, new Rva0036756A( this, 0, true ), 1012, 0 );
	defineState( 1005, new Rva003675AC( this, 0 ), 1006, 1006 );
	defineState( 1006, new Rva003675D6( this, false ), 78, 78 );
	defineState( 1014, new Rva00367518( this ), 78, 78 );
	defineState( 1015, new Rva00367647( this, false ), 78, 78 );
	defineState( 1016, new Rva00367647( this, true ), 78, 78 );
	defineState( 1019, new Rva003677BE( this ), 78, 78 );
	defineState( 1020, new GiantBirdNormalFlightState( this, false, true ), 0, 0 );
	defineState( 1023, new GiantBirdNormalFlightState( this, false, true ), 0, 0 );
	defineState( 1021, new GiantBirdNormalFlightState( this, false, false ), 1022, 1022 );
	defineState( 1022, new Rva003678F7( this ), 0, 0 );
}
