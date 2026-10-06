// cl: /MD
// ??0Rva003678F7@@QAE@PAVStateMachine@@@Z @0x003678F7 29B
// State-derived ctor hash 0xA36413A3 vtable 0x008175A8. Evidence: caller
// 0x00367DDF unclaimed; rowed State base 0x004D73FC via I twin
// ??0State@@QAE@PAVStateMachine@@I@Z; precedent Rva0033F6DA hash-plus-vtable.
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

// Rva003678F7_vftable: matched references place it at VA 0xc175a8 (retail .rdata value 7).
extern "C" char Rva003678F7_vftable = 7;

class __declspec(novtable) Rva003678F7 : public State
{
public:
	Rva003678F7(StateMachine *machine);
};

Rva003678F7::Rva003678F7(StateMachine *machine) : State(machine, 0xA36413A3u)
{
	*reinterpret_cast<char **>(this) = &Rva003678F7_vftable;
}
