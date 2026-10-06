// cl: /MD
// ?rva0029E03E@Rva0029B667@@QAEXXZ @0x0029E03E 41B.
// Chain from 0x0029B667 twin of 0x0029E015: same-this call proves Rva0029B667 class, relink head. Caller 0x0029FB18. Unlocks 0x0029FB03.
struct Rva0029B667Node {
	void *m_0;
	void *m_4;
	Rva0029B667Node *m_8;
	Rva0029B667Node *m_C;
};
class Rva0029B667 {
public:
	void rva0029B667(Rva0029B667Node *p);
	void rva0029E03E();
private:
	struct Head {
		void *m_0;
		Rva0029B667Node *m_4;
		Head *m_8;
		Head *m_C;
	};
	Head *m_0;
	int m_4;
};
void Rva0029B667::rva0029E03E()
{
	if (m_4 == 0)
		return;
	rva0029B667(m_0->m_4);
	m_0->m_8 = m_0;
	m_0->m_4 = 0;
	m_0->m_C = m_0;
	m_4 = 0;
}
