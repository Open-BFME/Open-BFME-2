// cl: /DNDEBUG /MD /EHsc
// ??0Rva00342843@@QAE@PAVStateMachine@@@Z @0x00342843 37B
// AIInternalMoveToState-derived ctor, hash 0x5106D8AC, vtable 0x008124D8,
// dword 0x4C zero via and plus byte 0x50 zero. Recipe from landed precedent
// Rva00342B87Ctor.cpp (33B, same base + vtable + 0x4C shape) plus byte-zero
// member like Rva003429B9Ctor.cpp. Donor AIStatesSmallUpdates.cpp
// AIFollowWaypointPathExactState ctor pattern (base + vtable + members).
// Evidence: base pin 0x0033F279 AIInternalMoveToState ctor; caller 0x00351D8C.
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
private:
	int m_4C;
	bool m_50;
};
Rva00342843::Rva00342843(StateMachine *machine)
	: AIInternalMoveToState(machine, 0x5106D8ACu)
{
	m_4C = 0;
	m_50 = false;
}

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?onEnter@AIInternalMoveToState@@UAEHXZ=?onEnter@AIMoveAndTightenState@@UAE?AW4StateReturnType@@XZ")
#pragma comment(linker, "/alternatename:?onExit@AIInternalMoveToState@@UAEXXZ=?onExit@AIInternalMoveToState@@UAEXW4StateExitType@@@Z")
#pragma comment(linker, "/alternatename:?update@AIInternalMoveToState@@UAEHXZ=?update@AIMoveAndTightenState@@UAE?AW4StateReturnType@@XZ")
#pragma comment(linker, "/alternatename:?xfer@AIInternalMoveToState@@UAEXXZ=?xfer@Rva00340123@@MAEXPAVXfer@@@Z")
