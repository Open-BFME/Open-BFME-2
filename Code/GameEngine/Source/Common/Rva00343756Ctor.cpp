// cl: /MD /EHsc
// ??0AttackContesterStateMachine@@QAE@PAVObject@@HI@Z @0x00343756 198B
// Name is a scalar hash: factory 34B1E9 pushes 0x30C4498F directly.
// Derived StateMachine ctor: base StateMachine with (owner, name, false),
// vtable, two states (500/501) via new 0x28/0x20 and defineState.
// Evidence: calls rowed base 0x004D79E1, new 0x0002FDA0, state ctors
// 0x0033F483/0x0033F43D, defineState 0x004D7B0F; vtable store; int arg at
// +0xC transformed to 0 or +0x20; ids 0x1F4/0x1F5/0x270F; cond 0x00C13164.
// The class is named by its vftable 0x00811BD0 (installed here and by the
// destructor 0x0033FB84 in Rva004D759CDerived.cpp), whose slot 2 getter
// 0x0033FB8F returns "AttackContesterStateMachine". Both states share one
// condition table, retail's 36 bytes at 0x00813164: {0x0034373F, 0x270F, 0},
// {0x0033FDEB, 0x270F, 2} and the terminator, the tests being the rowed
// rva0034373F and rva0033FDEB.
#include <new>

class Object;

class State;

#include "../../Include/Common/StateConditionInfo.h"

class StateMachine;
class Rva00343F8A;

int rva0034373F(State *state, void *);
bool cannotPossiblyAttackObject(Rva00343F8A *state, void *data);

class Rva0033F483
{
	unsigned char m_stateBytes[0x20]; // the 0x20-byte State base this view stands in for
public:
	Rva0033F483(StateMachine *machine, int arg);

private:
	int m_20;
	int m_24;
};

class Rva0033F43D
{
	unsigned char m_stateBytes[0x20]; // the 0x20-byte State base this view stands in for
public:
	Rva0033F43D(StateMachine *machine);
};

#include "../../Include/Common/StateMachine.h"
#include "../../Include/Common/StateMachineClass.h"

class AttackContesterStateMachine : public StateMachine
{
public:
	AttackContesterStateMachine(Object *owner, int val, unsigned int name);
	virtual ~AttackContesterStateMachine();
};

AttackContesterStateMachine::AttackContesterStateMachine(Object *owner, int val, unsigned int name)
	: StateMachine(owner, name, false)
{
	static const StateConditionInfo conditions[] =
	{
		{ (bool (*)(State *, void *))rva0034373F, 0x270F, 0 },
		{ (bool (*)(State *, void *))cannotPossiblyAttackObject, 0x270F, (void *)2 },
		{ 0, 0, 0 } // keep last
	};

	State *state = (State *)new Rva0033F483((StateMachine *)(void *)this, val ? val + 0x20 : 0);
	((StateMachine *)(void *)this)->defineState(0x1F4, state, 0x1F5, 0x270F, conditions);
	State *s2 = (State *)new Rva0033F43D((StateMachine *)(void *)this);
	((StateMachine *)(void *)this)->defineState(0x1F5, s2, 0x1F4, 0x270F, conditions);
}
