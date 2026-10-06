// cl: /MD
//
// ??0Rva0033F33D@@QAE@PAVStateMachine@@@Z, retail 0x0033F33D, 33 bytes.
// State-derived ctor forwarding (machine, 0x6D9C1CB9) to the unsigned-hash
// twin ??0State@@QAE@PAVStateMachine@@I@Z at 0x004D73FC then zeroing dword
// at +0x20 then installing vtable 0x00810EE0. Caller is 0x0035245D.
// Recipe is StateDerivedCtors_muse-a7a4 hash-plus-vtable with the And-zero
// tail (And is the /O1 size form of =0).

class StateMachine;

class State
{
public:
	State(StateMachine *machine, unsigned int hash);
	virtual ~State();

	int m_id;
	int m_successStateID;
	int m_failureStateID;
	void *m_transitionsFirst;
	void *m_transitionsLast;
	StateMachine *m_machine;
	bool m_tail1C;
	char m_pad1D[0x20 - 0x1D];
};

// Rva0033F33D_vftable: matched references place it at VA 0xc10ee0 (retail .rdata value -15).
extern "C" char Rva0033F33D_vftable = -15;

class __declspec(novtable) Rva0033F33D : public State
{
public:
	Rva0033F33D(StateMachine *machine);

private:
	unsigned int m_20;
};

Rva0033F33D::Rva0033F33D(StateMachine *machine) : State(machine, 0x6D9C1CB9u)
{
	m_20 = 0;
	*reinterpret_cast<char **>(this) = &Rva0033F33D_vftable;
}
