// cl: /DNDEBUG /MD /EHsc
//
// ??1AttackHordeStateMachine@@UAE@XZ, retail 0x0033FB20, 77 bytes. Slot 2 of
// vtable 0x00811B18 is the name getter 0x0033FB6D returning
// "AttackHordeStateMachine"; its ctor 0x00343367 shares the vtable.
// Dtor restoring vtable 0x00811B18, calling Object::rva0028C197 0x0028C197
// on member +0x14 when present then virtual slot 0x250 on its result when
// present, then calling the pinned base 0x004D759C. Caller is the deleting
// dtor 0x003435DF. Precedent is the Object+0x250 iface pattern
// (ObjectRva0028C197) with BfmeVirtualSlots for the 0x250 slot. Layout is
// base plus pad to +0x14 plus Object pointer.

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

#include "../GameLogic/Object/object.h"

#define BFME_SNAPSHOT_NAME_SLOT
#include "../../Include/Common/StateMachine.h"
#include "../../Include/Common/StateMachineClass.h"

class AttackHordeStateMachine : public StateMachine
{
public:
	virtual ~AttackHordeStateMachine();

};

AttackHordeStateMachine::~AttackHordeStateMachine()
{
	if (m_owner != 0) {
		Ret250 *p = (Ret250 *)m_owner->rva0028C197();
		if (p != 0) {
			p->method250();
		}
	}
}
