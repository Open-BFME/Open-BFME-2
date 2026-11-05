// cl: /DNDEBUG /MD /EHsc
//
// ??1AttackPositionHordeStateMachine@@UAE@XZ, retail 0x0033FBB7, 77 bytes.
// Dtor restoring vtable 0x00811CF0, calling Object::rva0028C197 0x0028C197
// on member +0x14 when present then virtual slot 0x250 on its result when
// present, then calling the pinned base 0x004D759C. Caller is the deleting
// dtor 0x00343BAD. Precedent is the Object+0x250 iface pattern
// (ObjectRva0028C197) with BfmeVirtualSlots for the 0x250 slot. The owner
// is the canonical StateMachine field at +0x14. The name is a target fact:
// vftable 0x00811CF0 (deleting dtor 0x00343BAD in slot 0) has the name
// getter 0x0033FC04 in slot 2, returning "AttackPositionHordeStateMachine";
// its constructor is 0x00343A86.

class Object;

template <int N>
class BfmeVirtualSlots : public BfmeVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template <>
class BfmeVirtualSlots<0>
{
};

class Ret250 : public BfmeVirtualSlots<148>
{
public:
	virtual void method250();
};

#include "../../Include/Common/StateMachineClass.h"
#include "../GameLogic/Object/object.h"

class AttackPositionHordeStateMachine : public StateMachine
{
public:
	virtual ~AttackPositionHordeStateMachine();
};

AttackPositionHordeStateMachine::~AttackPositionHordeStateMachine()
{
	if (m_owner != 0) {
		Ret250 *p = (Ret250 *)m_owner->rva0028C197();
		if (p != 0) {
			p->method250();
		}
	}
}
