// cl: /O1 /DNDEBUG /MD
// ?update@AIRampageState@@UAE?AW4StateReturnType@@XZ @0x0034FE10 94B
// Slot 6 (update) of vtable 0x00811A08 (ctor Rva0033F80E 0x0033F80E stores it).
// Sibling onEnter 0x0034BD1B and onExit 0x0034BDF8 prove the class is
// AIRampageState with Bool +0x20 and frame ints +0x24/+0x28; helper
// rva0034BE57's own comment names this update as its caller.
#include "../../../Include/Common/StateMachine.h"
#include "../../../Include/Common/StateMachineClass.h"

template <int N> class VSlots : public VSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class VSlots<0>
{
};

class Slot62Iface : public VSlots<62>
{
public:
	virtual void slot62() = 0;
};

class Object
{
public:
	unsigned char m_pad00[0x250];
	Slot62Iface *m_250; // +0x250
};

class BfmeSubBGB
{
public:
	bool rva00298893();
};

#include "../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;



class AIRampageState : public State
{
public:
	virtual StateReturnType update();
	void rva0034BE57(Object *obj);
private:
	bool m_20; // +0x20
	unsigned char m_pad21[0x24 - 0x21];
	unsigned int m_24; // +0x24
	unsigned int m_28; // +0x28
};

StateReturnType AIRampageState::update()
{
	Object *owner = m_machine->getOwner();
	if (!owner)
		return STATE_FAILURE;
	rva0034BE57(owner);
	if (m_28 <= TheGameLogic->getFrame())
	{
		Slot62Iface *iface = owner->m_250;
		if (iface)
			iface->slot62();
		m_28 = (unsigned int)-1;
	}
	if (m_24 <= TheGameLogic->getFrame())
	{
		((BfmeSubBGB *)owner)->rva00298893();
		return STATE_SUCCESS;
	}
	return STATE_CONTINUE;
}
