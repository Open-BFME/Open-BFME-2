// cl: /MD
// ??0Rva004D7B70@@QAE@PAVStateMachine@@I@Z at retail 0x004D7B70 (28B).
// State-derived ctor forwarding (machine, hash) to ??0State@@QAE@PAVStateMachine@@I@Z
// 0x004D73FC then installing vtable 0x00860790. Same esi-homing recipe as
// StateDerivedCtors_muse-a7a4.cpp six (29B) but passing its own second
// argument through (ret 8) instead of a hash immediate. The State ctor's
// second parameter is a destructor-less 4-byte value (StateCtor.cpp), so the
// pass-through is spelled `unsigned int` too. Callers in BoxEmissionVolumeInfo dtors.

class StateMachine;

class State
{
public:
	State(StateMachine *machine, unsigned int hash);
	virtual ~State();
};

// Rva004D7B70_vftable: matched references place it at VA 0xc60790 (retail .rdata value 7).
extern "C" char Rva004D7B70_vftable = 7;

class __declspec(novtable) Rva004D7B70 : public State
{
public:
	Rva004D7B70(StateMachine *machine, unsigned int hash);
	virtual ~Rva004D7B70();
};

Rva004D7B70::Rva004D7B70(StateMachine *machine, unsigned int hash) : State(machine, hash)
{
	*reinterpret_cast<char **>(this) = &Rva004D7B70_vftable;
}
