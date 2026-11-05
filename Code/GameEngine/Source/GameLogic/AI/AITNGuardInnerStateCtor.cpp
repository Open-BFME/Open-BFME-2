// cl: /DNDEBUG /MD
// ??0AITNGuardInnerState@@QAE@PAVStateMachine@@@Z @0x00545D50 40B
// AITNGuardInnerState ctor: State(machine, 0xD405C261), vtable 0x00C6A140,
// exitConditions vtable 0x00C6A13C at +0x20 with giveUpFrame 0 at +0x24.
// Prev/next neighbours live in AITNGuardStates.cpp (same dir, // cl: /O1
// /DNDEBUG /MD /arch:SSE /EHsc); this unit uses the precedent
// AIStatesSmallUpdates.cpp flags (no /EHsc, same 40B ctor shape) plus a
// compiler barrier to pin the derived vptr store ahead of the body stores.
// Evidence: pinned State hash ctor 0x004D73FC, vtable slot 5 onExit 0x00545BB7,
// caller 0x005460D0, hash 0xD405C261.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef UnsignedInt StateID;
#include "../../../Include/Common/StateMachineClass.h"
struct TunnelNetworkExitConditions
{
	const void *m_vptr;
	UnsignedInt m_attackGiveUpFrame; // +0x04 (state +0x24)
};
extern "C" const void *const __identifier("??_7Rva00545D43@@6B@")[];
class AITNGuardMachine;
class AITNGuardInnerState : public State
{
public:
	AITNGuardInnerState(StateMachine *machine);
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
private:
	TunnelNetworkExitConditions m_exitConditions; // +0x20
	Bool m_scanForEnemy; // +0x28
	void *m_attackState; // +0x2C
protected:
	// retail slot 3: the rowed ?xfer@AITNGuardInnerState@@MAEXPAVXfer@@@Z
	virtual void xfer(Xfer *xfer);
public:
	// retail vftable slot: the rowed override
	virtual StateReturnType update();
};

AITNGuardInnerState::AITNGuardInnerState(StateMachine *machine)
	: State(machine, 0xD405C261u)
{
	_ReadWriteBarrier();
	m_exitConditions.m_attackGiveUpFrame = 0;
	m_exitConditions.m_vptr = __identifier("??_7Rva00545D43@@6B@");
}

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?update@State@@UAE?AW4StateReturnType@@XZ=?update@AITNGuardInnerState@@UAE?AW4StateReturnType@@XZ")
