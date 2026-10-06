// cl: /MD
// ?rva00341DFC@Rva0033F6DA@@QAEHXZ @0x00341DFC 38B: Rva0033F6DA slot 6.
// If m_20==0 return -2 else set m_machine+0x38 to 1 then call m_20 slot 0x10 then clear m_machine+0x38 and return result.
// Precedent State m_machine plus Snapshot slot shape.
// Vtable 0x00811740 slot 6.
class StateMachine;
class Snapshot;
class M20
{
public:
	virtual ~M20();
	virtual void p1();
	virtual void p2();
	virtual void p3();
	virtual int v4();
};
struct Mach
{
	char m_pad00[0x38];
	bool m_38;
};
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
	Mach *m_machine;
	bool m_tail1C;
	char m_pad1D[0x20 - 0x1D];
};
class Rva0033F6DA : public State
{
public:
	int rva00341DFC();
private:
	M20 *m_20;
};
int Rva0033F6DA::rva00341DFC()
{
	if (m_20 == 0)
		return -2;
	m_machine->m_38 = true;
	int r = m_20->v4();
	m_machine->m_38 = false;
	return r;
}
