// ?rva002EC3CE@Rva002EC3CE@@QAE_NHH@Z
// partial score=0.8 date=2026-10-06
// cl: /O1 /DNDEBUG /MD
// Dump lane range 13: ?rva002EC3CE @0x002EC3CE 171B. Thiscall bool probe
// over two int args: two rowed-2E7BF0 gated probes (the second fed by the
// rowed Object 0x28B511 getter; its first two pushes are hoisted above
// that getter call), then the 0x2CB35C float-gated probe and the 0x2EAA41
// probe, finishing with a 12-byte copy into +0x34. The three probe
// targets are unrowed so they are pinned as addresses; identities and
// signatures beyond the observed push shapes are unproven.
class Rva002EC3CEProbes
{
public:
	bool rva002E7BF0(int p1, int p2, bool p3, int p4, int p5, int p6, void *p7, bool p8);
	bool rva002EAA41(int p1, int p2, int p3, int p4, int p5, bool p6);
};

class Rva002CB35CObj
{
public:
	bool rva002CB35C(int p1, void *p2, void *p3, void *p4, float p5, int p6);
};

class Object
{
public:
	int rva0028B511() const;
};

struct Rva002EC3CEInner
{
	char _00[12];
};

class Rva002EC3CE
{
public:
	bool rva002EC3CE(int a1, int a2);
	Rva002EC3CEProbes *m_0;
	int m_4;
	int m_8;
	bool m_C;
	char _D[3];
	int m_10;
	Rva002EC3CEInner m_14;
	bool m_20;
	char _21[3];
	Rva002CB35CObj *m_24;
	Object *m_28;
	void *m_2C;
	int m_30;
	void *m_34;
	bool m_38;
};

bool Rva002EC3CE::rva002EC3CE(int a1, int a2)
{
	bool ok = m_0->rva002E7BF0(m_4, m_8, m_C, a1, a2, m_10, &m_14, m_20);
	if (!ok)
	{
		// Retail compares m_38 against al (the false result), not imm 0.
		if (m_38 == ok)
			return false;
		if (!m_0->rva002E7BF0(m_4, m_8, m_C, a1, a2, m_28->rva0028B511(), &m_14, m_20))
			return false;
	}
	void *p2c = m_2C;
	if (!m_24->rva002CB35C((int)m_28, &m_14, p2c, (char *)p2c + 0x38, 0.0f, 1))
		return false;
	if (!m_0->rva002EAA41((int)m_28, a1, a2, m_10, m_30, m_C))
		return false;
	*(Rva002EC3CEInner *)m_34 = m_14;
	return true;
}
