// cl: /MD
//
// ??0AIGuardState@@QAE@PAVStateMachine@@@Z, retail 0x0033F6DA, 33 bytes.
// State-derived ctor forwarding (machine, 0xEBE7A650) to the unsigned-hash
// twin ??0State@@QAE@PAVStateMachine@@I@Z at 0x004D73FC then zeroing dword
// at +0x20 then installing vtable 0x00811740. Caller is 0x00352703. Twin of
// 0x0033F33D (hash 0x6D9C1CB9 vtable 0x00810EE0). Recipe is
// StateDerivedCtors_muse-a7a4 hash-plus-vtable with And-zero tail.

class StateMachine;

#include "../../Include/Common/StateMachine.h"

// Rva0033F6DA_vftable: matched references place it at VA 0xc11740 (retail .rdata value 37).
extern "C" char Rva0033F6DA_vftable = 37;

class __declspec(novtable) AIGuardState : public State
{
public:
	AIGuardState(StateMachine *machine);

private:
	unsigned int m_20;
};

AIGuardState::AIGuardState(StateMachine *machine) : State(machine, 0xEBE7A650u)
{
	m_20 = 0;
	*reinterpret_cast<char **>(this) = &Rva0033F6DA_vftable;
}
