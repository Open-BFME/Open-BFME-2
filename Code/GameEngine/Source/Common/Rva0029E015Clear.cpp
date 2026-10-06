// cl: /MD
// ?rva0029E015@Rva0029B63A@@QAEXXZ @0x0029E015 41B.
// Chain from 0x0029B63A same-this call proves Rva0029B63A class: if m_4 clear list via that row then re-link head to self.
// Callers 0x0029FACC 0x0029FAB2 0x002A3E55. Unlocks 0x002A3E24.
struct Rva0029B63ANode {
	void *m_0;
	void *m_4;
	Rva0029B63ANode *m_8;
	Rva0029B63ANode *m_C;
};
class Rva0029B63A {
public:
	void rva0029B63A(Rva0029B63ANode *p);
	void rva0029E015();
private:
	struct Head {
		void *m_0;
		Rva0029B63ANode *m_4;
		Head *m_8;
		Head *m_C;
	};
	Head *m_0;
	int m_4;
};
void Rva0029B63A::rva0029E015()
{
	if (m_4 == 0)
		return;
	rva0029B63A(m_0->m_4);
	m_0->m_8 = m_0;
	m_0->m_4 = 0;
	m_0->m_C = m_0;
	m_4 = 0;
}
