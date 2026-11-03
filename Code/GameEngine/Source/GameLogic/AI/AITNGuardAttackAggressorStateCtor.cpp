// cl: /DNDEBUG /MD
// ??0AITNGuardAttackAggressorState@@QAE@PAVStateMachine@@@Z @0x00545E80 44B
// AITNGuardAttackAggressorState ctor: State(machine, 0x33E96013), vtable
// 0x00C6A298, exitConditions vtable 0x00C6A13C at +0x20 with giveUpFrame 0
// at +0x24, m_attackState 0 at +0x28. Sibling of AITNGuardInnerState ctor
// 0x00545D50 (same file family, same State hash pattern, same barrier to
// pin the derived vptr store ahead of the body stores).
// Evidence: pinned State hash ctor 0x004D73FC, vtable slot 5 onExit
// 0x00545CF7 slot 6 update 0x0054684E, caller 0x00546172, hash 0x33E96013.
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
class AITNGuardAttackAggressorState : public State
{
public:
	AITNGuardAttackAggressorState(StateMachine *machine);
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
private:
	TunnelNetworkExitConditions m_exitConditions; // +0x20
	void *m_attackState; // +0x28
};

AITNGuardAttackAggressorState::AITNGuardAttackAggressorState(StateMachine *machine)
	: State(machine, 0x33E96013u)
{
	_ReadWriteBarrier();
	m_exitConditions.m_attackGiveUpFrame = 0;
	m_exitConditions.m_vptr = __identifier("??_7Rva00545D43@@6B@");
	_ReadWriteBarrier();
	m_attackState = 0;
}

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?slot01@State@@UAEXXZ=?rva005CB26A@Rva005CB26A@@QAEHXZ")
#pragma comment(linker, "/alternatename:?slot02@State@@UAEXXZ=?Rva00545EACGet@@YAHXZ")
#pragma comment(linker, "/alternatename:?slot03@State@@UAEXXZ=?Rva00306A9BDoXfer@@YGXPAVXfer@@@Z")
