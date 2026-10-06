// cl: /MD
//
// ??0Rva00342619@@QAE@PAVStateMachine@@@Z, retail 0x00342619, 29 bytes.
// State-derived ctor (machine) forwarding hash 0x9B3AE6B6 to the
// (StateMachine*, unsigned int) ICF twin at 0x004D73FC (pinned
// ??0State@@QAE@PAVStateMachine@@I@Z, same body as the rowed VAsciiString
// overload), then installing vtable 0x008123D8. Seventh member of the
// StateDerivedCtors_muse-a7a4 six-ctor family (same 29B esi-homing shape,
// ret 4, hash immediate, novtable plus explicit vftable store). Sole caller
// is unclaimed site 0x00352A67.

class StateMachine;

class State
{
public:
	State(StateMachine *machine, unsigned int hash);
	virtual ~State();
};

// Rva00342619_vftable: matched references place it at VA 0xc123d8 (retail .rdata value 7).
extern "C" char Rva00342619_vftable = 7;

class __declspec(novtable) Rva00342619 : public State
{
public:
	Rva00342619(StateMachine *machine);
	virtual ~Rva00342619();
};

Rva00342619::Rva00342619(StateMachine *machine) : State(machine, 0x9B3AE6B6u)
{
	*reinterpret_cast<char **>(this) = &Rva00342619_vftable;
}
