// cl: /MD
//
// ??0Rva003426AB@@QAE@PAVStateMachine@@@Z, retail 0x003426AB, 29 bytes.
// State-derived ctor (machine) forwarding hash 0x9AA7C3F8 to the
// (StateMachine*, unsigned int) ICF twin at 0x004D73FC (pinned
// ??0State@@QAE@PAVStateMachine@@I@Z, same body as the rowed VAsciiString
// overload), then installing vtable 0x00812438. Same family as the landed
// 0x00342619 (hash 0x9B3AE6B6, vtable 0x008123D8) and the
// StateDerivedCtors_muse-a7a4 six (same 29B esi-homing shape, ret 4, hash
// immediate, novtable plus explicit vftable store). Sole caller is unclaimed
// site 0x00352AC8.

class StateMachine;

class State
{
public:
	State(StateMachine *machine, unsigned int hash);
	virtual ~State();
};

// Rva003426AB_vftable: matched references place it at VA 0xc12438 (retail .rdata value 7).
extern "C" char Rva003426AB_vftable = 7;

class __declspec(novtable) Rva003426AB : public State
{
public:
	Rva003426AB(StateMachine *machine);
	virtual ~Rva003426AB();
};

Rva003426AB::Rva003426AB(StateMachine *machine) : State(machine, 0x9AA7C3F8u)
{
	*reinterpret_cast<char **>(this) = &Rva003426AB_vftable;
}
