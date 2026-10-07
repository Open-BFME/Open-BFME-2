// cl: /O1 /MD /arch:SSE /G7
// ?rva005EB88F@Rva005EB88F@@QAEXXZ, RVA 0x005EB88F, 59 bytes.
// Address-based state dispatch. Evidence: retail reads the state at +8, invokes the rowed predicate at +0x34, uses the pinned manager method with +4, and tail-calls the rowed Rva005EB825 method through +0.
class Rva00222A8BTarget
{
public:
	// Native provider compares the incoming 32-bit index with 14 and returns AL.
	bool rva0022277D(int index);
};
class BfmeAptWindowManager : public Rva00222A8BTarget {};
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
class Rva005FA854
{
public:
	bool rva005FA854();
};
class Rva005EB825
{
public:
	void rva005EB825();
};
class Rva005EB88F
{
public:
	Rva005EB825 *m_stateObject;
	void *m_04;
	int m_state;
	char m_pad0C[0x34 - 0x0C];
	Rva005FA854 m_predicate;
	void rva005EB88F();
};
void Rva005EB88F::rva005EB88F()
{
	switch (m_state)
	{
	case 2:
		if (m_predicate.rva005FA854())
			m_stateObject->rva005EB825();
		break;
	case 4:
		g_bfmeAptWindowManager->rva0022277D(reinterpret_cast<int>(m_04));
		m_state = 0;
		break;
	case 5:
		m_stateObject->rva005EB825();
		break;
	}
}
