// cl: /O1 /DNDEBUG /MD /arch:SSE
// ??0Rva00545D7E@@QAE@PAVStateMachine@@@Z @ 0x00545D7E 44B
// State-derived ctor: State(machine, 0xCDECC1F9), vtable 0x00C6A198,
// exitConditions vtable 0x00C6A13C at +0x20 with +0x24 zero and +0x28 zero.
// Evidence: sibling AITNGuardAttackAggressorState ctor pattern; callee pin ??0State@@QAE@PAVStateMachine@@I@Z at 0x004D73FC; caller 0x00546108.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

typedef unsigned int UnsignedInt;
typedef UnsignedInt StateID;
#include "../../Include/Common/StateMachine.h"
#include "../../Include/Common/StateMachineClass.h"
struct Rva00545D7EExitConditions
{
	const void *m_vptr;
	UnsignedInt m_04;
};
extern const void *const g_00C6A198[];
extern "C" const void *const __identifier("??_7Rva00545D43@@6B@")[];
class Rva00545D7E : public State
{
public:
	Rva00545D7E(StateMachine *machine);
private:
	Rva00545D7EExitConditions m_exit;
	void *m_28;
};
Rva00545D7E::Rva00545D7E(StateMachine *machine)
	: State(machine, 0xCDECC1F9u)
{
	_ReadWriteBarrier();
	m_exit.m_04 = 0;
	m_exit.m_vptr = __identifier("??_7Rva00545D43@@6B@");
	_ReadWriteBarrier();
	m_28 = 0;
}
