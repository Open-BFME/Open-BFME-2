// cl: /MD
//
// ??0Rva0033FC42@@QAE@PAVStateMachine@@@Z, retail 0x0033FC1B, 33 bytes.
// State-derived ctor forwarding (machine, 0x7E4CE41F) to the unsigned-hash
// twin ??0State@@QAE@PAVStateMachine@@I@Z at 0x004D73FC then zeroing dword
// at +0x20 then installing vtable 0x00811DB0. This is the ctor for the
// rowed dtor ??1Rva0033FC42 at 0x0033FC42 (same vtable); the dtor plus slot6
// live in Rva0033FC42Dtor.cpp (non-novtable automatic vtable) while this TU
// uses novtable plus explicit store to get the And-before-vtable order.
// Caller is 0x00352272. Twin of 0x0033F33D/0x0033F6DA.

class StateMachine;

#include "../../Include/Common/StateMachine.h"

// Rva0033FC42_vftable gives way to the compiler table the data ledger binds there.
namespace
{
extern "C" char __identifier("??_7Rva0033FC42@@6B@");
inline char *rva0033FC42Vtable()
{
	return &__identifier("??_7Rva0033FC42@@6B@");
}
}

class __declspec(novtable) Rva0033FC42 : public State
{
public:
	Rva0033FC42(StateMachine *machine);

private:
	unsigned int m_20;
};

Rva0033FC42::Rva0033FC42(StateMachine *machine) : State(machine, 0x7E4CE41Fu)
{
	m_20 = 0;
	*reinterpret_cast<char **>(this) = rva0033FC42Vtable();
}
