// cl: /MD
// ??0Rva005445D4@@QAE@PAVStateMachine@@@Z, retail 0x005445D4, 37 bytes.
// Derived State ctor via rowed/pinned State hash ctor 0x004D73FC with hash
// 0x90B65C1D then zero of +0x20/+0x24 then vtable 0x00869A20. Evidence:
// vtable store at [this]; base StateCtor hash pin; caller 0x005449DD in
// FUN_009448a1; prev 0x005440CD same dir.
class StateMachine;

class __declspec(novtable) State
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
	unsigned char m_pad1D[0x20 - 0x1D];
};

extern const void *const g_00C69A20[];

class Rva005445D4 : public State
{
public:
	Rva005445D4(StateMachine *machine);
private:
	int m_20;
	int m_24;
};

Rva005445D4::Rva005445D4(StateMachine *machine) : State(machine, 0x90B65C1Du)
{
	m_20 = 0;
	m_24 = 0;
	*(const void **)this = g_00C69A20;
}
