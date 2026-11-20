// cl: /DNDEBUG /MD /EHsc
// ??0Rva00342826@@QAE@PAVStateMachine@@@Z @0x00342826 29B
// AIInternalMoveToState-derived ctor, hash 0x0DA1899B, vtable 0x00812490,
// no extra members. Recipe from sibling Rva00342843Ctor.cpp (37B, same base
// + vtable shape) and precedent Rva00342B87Ctor.cpp. Donor
// AIStatesSmallUpdates.cpp AIFollowWaypointPathExactState ctor pattern.
// Evidence: base pin 0x0033F279 AIInternalMoveToState ctor; caller 0x00351D5C.
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
class Rva00342826 : public AIInternalMoveToState
{
public:
	Rva00342826(StateMachine *machine);
};
Rva00342826::Rva00342826(StateMachine *machine)
	: AIInternalMoveToState(machine, 0x0DA1899Bu)
{
}

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?onEnter@AIInternalMoveToState@@UAEHXZ=?onEnter@AIMoveOutOfTheWayState@@UAE?AW4StateReturnType@@XZ")
#pragma comment(linker, "/alternatename:?onExit@AIInternalMoveToState@@UAEXXZ=?onExit@Rva00347AAC@@UAEXW4StateExitType@@@Z")
#pragma comment(linker, "/alternatename:?update@AIInternalMoveToState@@UAEHXZ=?rva00349D8D@Rva00349D8D@@QAEXXZ")
