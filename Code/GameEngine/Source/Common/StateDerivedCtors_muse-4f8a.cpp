// cl: /MD
// ??0Rva0048896B@@QAE@PAVStateMachine@@@Z @0x0048896B 29B
// State-derived ctor calling ??0State@@QAE@PAVStateMachine@@I@Z (0x004D73FC,
// ICF twin pin of the rowed VAsciiString overload) then installing its own
// vtable. Retail pushes hash 0x69EAAB49 with no AsciiString construction,
// same 29B esi-homing shape as the six in StateDerivedCtors_muse-a7a4.cpp.
// Vtable 0x0084B620 from retail bytes; sole caller 0x00488EB5 in FUN_00888DAB.

class StateMachine;

class State
{
public:
	State(StateMachine *machine, unsigned int hash);
	virtual ~State();
};

// Rva0048896B_vftable: matched references place it at VA 0xc4b620 (retail .rdata value 7).
extern "C" char Rva0048896B_vftable = 7;

class __declspec(novtable) Rva0048896B : public State
{
public:
	Rva0048896B(StateMachine *machine);
	virtual ~Rva0048896B();
};

Rva0048896B::Rva0048896B(StateMachine *machine) : State(machine, 0x69EAAB49u)
{
	*reinterpret_cast<char **>(this) = &Rva0048896B_vftable;
}
