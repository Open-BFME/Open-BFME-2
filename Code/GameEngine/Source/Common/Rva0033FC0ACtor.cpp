// cl: /MD /EHsc
// ??0Rva0033FC0A@@QAE@PAVObject@@I@Z @0x00343BC9 213B
// Derived StateMachine ctor: base StateMachine with (owner, key, false),
// vtable 0x00C11D50, three states (0/1/2) via new 0x54/0x28/0x50 and defineState.
// Evidence: pin ??0Rva0033FC0A@@QAE@PAVObject@@I@Z ret 8; calls rowed base
// 0x004D79E1, new 0x0002FDA0, state ctors 0x00342EAC/0x0033F6C0/0x0034005D,
// defineState 0x004D7B0F; callers xfer 0x00343D33 onEnter; vtable store;
// ids 0/1/2 success 1/2/0x270E failure 0x270F/0x270F/0x270E cond null.
#include <new>

class Object;

#include "../../Include/Common/StateConditionInfo.h"

class StateMachine;


class Rva00342EAC
{
	unsigned char m_stateBytes[0x20]; // the 0x20-byte State base this view stands in for
public:
	Rva00342EAC(StateMachine *machine);
private:
	char m_extra[0x54 - 0x20];
};

class Rva0033F6C0
{
	unsigned char m_stateBytes[0x20]; // the 0x20-byte State base this view stands in for
public:
	Rva0033F6C0(StateMachine *machine);
private:
	char m_extra[0x28 - 0x20];
};

class Rva0034005D
{
	unsigned char m_stateBytes[0x20]; // the 0x20-byte State base this view stands in for
public:
	Rva0034005D(StateMachine *machine);
private:
	char m_extra[0x50 - 0x20];
};

#include "../../Include/Common/StateMachine.h"
#include "../../Include/Common/StateMachineClass.h"

extern const void *const g_00C11D50[];

class Rva0033FC0A : public StateMachine
{
public:
	Rva0033FC0A(Object *owner, unsigned int key);
	// The complete/deleting destructors belong to Rva004D759CDerived.cpp (opaque derived dtors).
	// Leaving this implicit emits a competing call to the opaque base spelling.
	virtual ~Rva0033FC0A();
};

Rva0033FC0A::Rva0033FC0A(Object *owner, unsigned int key)
	: StateMachine(owner, key, false)
{
	State *state = (State *)new Rva00342EAC((StateMachine *)(void *)this);
	((StateMachine *)(void *)this)->defineState(0, state, 1, 0x270F, 0);
	State *s1 = (State *)new Rva0033F6C0((StateMachine *)(void *)this);
	((StateMachine *)(void *)this)->defineState(1, s1, 2, 0x270F, 0);
	State *s2 = (State *)new Rva0034005D((StateMachine *)(void *)this);
	((StateMachine *)(void *)this)->defineState(2, s2, 0x270E, 0x270E, 0);
}
