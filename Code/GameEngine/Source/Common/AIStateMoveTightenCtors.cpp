// cl: /DNDEBUG /MD /EHsc
//
// AIInternalMoveToState-derived state ctors, retail 0x0034286E (36B),
// 0x00342892 (29B), 0x003428AF (29B), 0x003428CC (37B).
//
// The mid ctor 0x0034286E carries the same vtable (0x008124D8), the same
// member shape (dword 0x4C zero via and plus byte 0x50 zero) and the same
// base (AIInternalMoveToState ctor pin 0x0033F279) as the rowed
// Rva00342843 ctor 0x00342843 (Rva00342843Ctor.cpp, hash 0x5106D8AC):
// it is that class's second constructor, forwarding (machine, hash)
// instead of baking the hash. The three leaves derive from it, pass
// their own hashes (0xD5F5D4FA, 0xE3F474A1, 0xE4366E82), install their
// own vtables, and - for 0x003428CC only - zero an int at +0x58 and a
// bool at +0x54 in the same and-before-vtable, byte-after order the
// precedent documents. Hierarchy views mirror Rva00342843Ctor.cpp so
// the emitted vtable references resolve the same way.

class StateMachine;
#include "../../../Libraries/Include/Lib/Coord3D.h"
class Xfer;
#include "../../Include/Common/StateMachine.h"
// The rowed virtuals of AIInternalMoveToState's retail table 0x00C10DE8 that have a provider;
// slots 2 and 7 stay State's until their bodies are named (LINK-513).
class AIInternalMoveToState : public State
{
public:
	AIInternalMoveToState(StateMachine *machine, unsigned int hash);
	virtual ~AIInternalMoveToState();
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
protected:
	virtual void xfer(Xfer *xfer);
	virtual bool computePath();
	Coord3D m_goalPosition;
	unsigned char m_pad2C[0x48 - (0x20 + sizeof(Coord3D))];
	bool m_adjustsDestination;
};
class Rva00342843 : public AIInternalMoveToState
{
public:
	Rva00342843(StateMachine *machine);
	Rva00342843(StateMachine *stateMachine, unsigned int hash);
private:
	int m_4C;
	bool m_50;
};
class Rva00342892 : public Rva00342843
{
public:
	Rva00342892(StateMachine *stateMachine);
};
class Rva003428AF : public Rva00342843
{
public:
	Rva003428AF(StateMachine *stateMachine);
};
class Rva003428CC : public Rva00342843
{
public:
	Rva003428CC(StateMachine *stateMachine);
private:
	bool m_54;
	char m_pad55[3];
	int m_58;
};

Rva00342843::Rva00342843(StateMachine *stateMachine, unsigned int hash)
	: AIInternalMoveToState(stateMachine, hash)
{
	m_4C = 0;
	m_50 = false;
}

Rva00342892::Rva00342892(StateMachine *stateMachine)
	: Rva00342843(stateMachine, 0xD5F5D4FAu)
{
}

Rva003428AF::Rva003428AF(StateMachine *stateMachine)
	: Rva00342843(stateMachine, 0xE3F474A1u)
{
}

Rva003428CC::Rva003428CC(StateMachine *stateMachine)
	: Rva00342843(stateMachine, 0xE4366E82u)
{
	m_58 = 0;
	m_54 = false;
}
