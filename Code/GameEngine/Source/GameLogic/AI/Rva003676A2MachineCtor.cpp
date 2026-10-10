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
	StateMachine(Object *owner, UnsignedInt nameKey, Bool flag);
	virtual ~StateMachine();
	virtual Bool isInAttackState() const;
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
class Rva003676A2 : public StateMachine
{
public:
	Rva003676A2(Object *owner, UnsignedInt nameKey);
	virtual ~Rva003676A2();
	virtual Bool isInAttackState() const;

};

Rva003676A2::Rva003676A2(Object *owner, UnsignedInt nameKey) : StateMachine(owner, nameKey, false)
{

	// order matters: first state is the default state.
	defineState( 10, new Rva0036756A( this, 1, false ), 1012, 0 );
	defineState( 1012, new Rva003675AC( this, 1 ), 1013, 1013 );
	defineState( 1013, new Rva003675D6( this, false ), 0, 0 );
	defineState( 0, new Rva0033FE65( this, 1 ), 0, 0 );
}

// Rva003676A2::isInAttackState, retail 0x0036890E (126B): slot 11 of this
// machine's vtable 0x00C174E0 (StateMachine's isInAttackState slot). The
// final state 0 always counts; state 1013 counts while the owner's AI
// (Object +0x258) reports slot +0x168 and its slot +0x188 target either lacks
// flag bit 6 but has bit 4 (+0x4B8), or has a nonzero byte at +0x534.
// Roles beyond these reads are not established.
#define INVALID_STATE_ID 999999
struct Rva0036890ETarget
{
	Bool flagBit4() const { return (m_flags >> 4) & 1; }
	Bool flagBit6() const { return (m_flags >> 6) & 1; }
	unsigned char m_pad000[0x4B8];
	UnsignedInt m_flags;		// +0x4B8
	unsigned char m_pad4BC[0x534 - 0x4BC];
	unsigned char m_534;		// +0x534
};
template <int N> class Rva0036890ESlots : public Rva0036890ESlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva0036890ESlots<0>
{
};
class Rva0036890EAI : public Rva0036890ESlots<90>
{
public:
	virtual Bool slot168() = 0;				// +0x168
	virtual void s91() = 0; virtual void s92() = 0; virtual void s93() = 0; virtual void s94() = 0;
	virtual void s95() = 0; virtual void s96() = 0; virtual void s97() = 0;
	virtual Rva0036890ETarget *slot188() = 0;		// +0x188
};
struct Rva0036890EState { void *m_vtable; StateID m_ID; };
struct Rva0036890EObject { unsigned char m_pad000[0x258]; Rva0036890EAI *m_ai; };
struct Rva0036890EMachine { void *m_vtable; Rva0036890EState *m_currentState; unsigned char m_pad08[0x14 - 0x08]; Rva0036890EObject *m_owner; };

static __forceinline Bool rva0036890EAttacking(const Rva0036890EObject *owner)
{
	Rva0036890EAI *ai = owner->m_ai;
	if (ai && ai->slot168())
	{
		Rva0036890ETarget *target = ai->slot188();
		if (target)
		{
			if (!target->flagBit6() && target->flagBit4())
				return true;
			if ((float)target->m_534 != 0.0f)
				return true;
		}
	}
	return false;
}
Bool Rva003676A2::isInAttackState() const
{
	const Rva0036890EMachine *machine = (const Rva0036890EMachine *)this;
	StateID id = machine->m_currentState ? machine->m_currentState->m_ID : INVALID_STATE_ID;
	if (id == 0 || (id == 1013 && rva0036890EAttacking(machine->m_owner)))
		return true;
	return false;
}
