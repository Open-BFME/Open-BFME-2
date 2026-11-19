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
class State
{
public:
	virtual ~State();
	virtual void slot01();
	virtual void slot02();
	virtual void xfer(Xfer *xfer);
	virtual int onEnter();
	virtual void onExit();
	virtual int update();
protected:
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine;
};
class AIInternalMoveToState : public State
{
public:
	AIInternalMoveToState(StateMachine *machine, unsigned int hash);
	virtual ~AIInternalMoveToState();
	virtual int onEnter();
	virtual void onExit();
	virtual int update();
protected:
	virtual void xfer(Xfer *xfer);	// 0x0033FF76
	unsigned char m_pad1C[0x20 - 0x1C];
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
