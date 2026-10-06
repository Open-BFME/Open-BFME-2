// cl: /MD
// ??0Rva00367647@@QAE@PAVStateMachine@@_N@Z @0x00367647 40B
// State-derived ctor hash 0xA3ED2B68 vtable 0x00817478 plus int 0 at +0x20
// plus bool at +0x24. Evidence: callers 0x00367CA4 0x00367CD8; rowed State
// base 0x004D73FC via I twin; precedent StateDerivedCtors_muse-a7a4.cpp.
class StateMachine;
class State
{
public:
	State(StateMachine *machine, unsigned int hash);
	virtual ~State();
private:
	char m_pad[0x20 - 4];
};
// Rva00367647_vftable: matched references place it at VA 0xc17478 (retail .rdata value 7).
extern "C" char Rva00367647_vftable = 7;
class __declspec(novtable) Rva00367647 : public State
{
public:
	Rva00367647(StateMachine *machine, bool flag);
	virtual ~Rva00367647();
private:
	int m_20;
	bool m_24;
};
Rva00367647::Rva00367647(StateMachine *machine, bool flag) : State(machine, 0xA3ED2B68u)
{
	m_20 = 0;
	m_24 = flag;
	*reinterpret_cast<char **>(this) = &Rva00367647_vftable;
}
