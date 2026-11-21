// cl: /DNDEBUG /MD /EHsc
// ??0Rva00342B87@@QAE@PAVStateMachine@@@Z @0x00342B87 33B: AIInternalMoveToState-derived ctor, hash 0x67979DC4, vtable 0x008128D0, dword 0x4C zero via and.
// Donor Code/GameEngine/Source/GameLogic/AI/AIStatesSmallUpdates.cpp AIFollowWaypointPathExactState ctor pattern (base + vtable + members).
// Callers 0x0034B9C5 0x0034C75E 0x00352887 0x00368056 unclaimed.
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
class Rva00342B87 : public AIInternalMoveToState
{
public:
	Rva00342B87(StateMachine *machine);
protected:
	virtual void xfer(Xfer *xfer);	// 0x00340C2D
private:
	int m_4C;
};
Rva00342B87::Rva00342B87(StateMachine *machine)
	: AIInternalMoveToState(machine, 0x67979DC4u)
{
	m_4C = 0;
}

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?onEnter@AIInternalMoveToState@@UAEHXZ=?onEnter@Rva00340C5F@@QAEHXZ")
#pragma comment(linker, "/alternatename:?onExit@AIInternalMoveToState@@UAEXXZ=?onExit@AIMoveToState@@UAEXW4StateExitType@@@Z")
#pragma comment(linker, "/alternatename:?update@AIInternalMoveToState@@UAEHXZ=?update@AIPickUpCrateState@@UAE?AW4StateReturnType@@XZ")
