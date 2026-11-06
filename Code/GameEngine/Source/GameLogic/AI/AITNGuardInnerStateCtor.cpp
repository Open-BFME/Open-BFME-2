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

#include "../../../Include/GameLogic/AITNGuard.h"
extern "C" const void *const __identifier("??_7Rva00545D43@@6B@")[];
AITNGuardInnerState::AITNGuardInnerState(StateMachine *machine)
	: State(machine, 0xD405C261u)
{
	_ReadWriteBarrier();
	m_exitConditions.m_attackGiveUpFrame = 0;
	m_exitConditions.m_vptr = __identifier("??_7Rva00545D43@@6B@");
}

// Retail vtable 0x00C6A140 slot 1 points at 0x005CB26A (mov eax,[ecx];
// jmp [eax+0x10]): a tail call to slot 4, onEnter. The body is shared by
// identical code folding with the rowed forwarder in Rva005CB26AForwarder.cpp.
void AITNGuardInnerState::loadPostProcess()
{
	onEnter();
}

// Retail vtable 0x00C6A140 slot 2 points at 0x00545D78, which returns the
// literal "AITNGuardInnerState" at VA 0x00C6A184.
const char *AITNGuardInnerState::GetSnapshotName() const
{
	return "AITNGuardInnerState";
}

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?update@State@@UAE?AW4StateReturnType@@XZ=?update@AITNGuardInnerState@@UAE?AW4StateReturnType@@XZ")
