// cl: /MD
class Rva005C4CC1Sub {
public:
	char m_pad[0x34];
	int m_val34; // +0x34
	int m_val38; // +0x38
};

class Rva00DFE1C8Host {
public:
	void rva00210E5B(int a, int b);
};
extern Rva00DFE1C8Host *g_00DFE1C8;

class Rva005C4B56 {
public:
	void rva005C4B56(int setBits, int clearBits, int val);
	void rva005C4C69();
	void rva005C4C95();
private:
	char m_padAC[0xAC];
	Rva005C4CC1Sub *m_subAC; // +0xAC
	int m_b0; // +0xB0
};

void Rva005C4B56::rva005C4C69() {
	g_00DFE1C8->rva00210E5B(m_b0, 1);
	rva005C4B56(1, 0, m_subAC->m_val34);
}

void Rva005C4B56::rva005C4C95() {
	g_00DFE1C8->rva00210E5B(m_b0, 0);
	rva005C4B56(0, 1, m_subAC->m_val38);
}
