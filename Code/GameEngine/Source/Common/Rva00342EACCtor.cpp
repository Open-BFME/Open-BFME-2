// cl: /MD /EHsc
// ??0Rva00342EAC@@QAE@PAVStateMachine@@@Z @0x00342EAC 37B: AIInternalMoveToState-derived ctor, hash 0x822AD648, vtable 0x00812E90, dwords 0x4C 0x50 zero via and.
// Donor Code/GameEngine/Source/GameLogic/AI/AIStatesSmallUpdates.cpp AIFollowWaypointPathExactState ctor pattern (base + vtable + members).
// Callers 0x00343C08 0x0035251C 0x00545DB7 unclaimed.
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
class Rva00342EAC : public AIInternalMoveToState
{
public:
	Rva00342EAC(StateMachine *machine);
private:
	int m_4C;
	int m_50;
};
Rva00342EAC::Rva00342EAC(StateMachine *machine)
	: AIInternalMoveToState(machine, 0x822AD648u)
{
	m_4C = 0;
	m_50 = 0;
}

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?onEnter@AIInternalMoveToState@@UAEHXZ=?onEnter@AIEnterState@@UAE?AW4StateReturnType@@XZ")
#pragma comment(linker, "/alternatename:?onExit@AIInternalMoveToState@@UAEXXZ=?onExit@AIEnterState@@UAEXW4StateExitType@@@Z")
#pragma comment(linker, "/alternatename:?update@AIInternalMoveToState@@UAEHXZ=?update@AIEnterState@@UAE?AW4StateReturnType@@XZ")
#pragma comment(linker, "/alternatename:?xfer@AIInternalMoveToState@@UAEXXZ=?xfer@Rva00341930@@MAEXPAVXfer@@@Z")
