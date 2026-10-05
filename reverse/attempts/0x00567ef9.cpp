// ?Make@Rva00567EF9Maker@@QAEPAPAURva00567EF9Val@@PAPAU2@@Z
// partial score=0.85 date=2026-10-05
// cl: /O1 /GX-

struct Rva00567EF9Val
{
	~Rva00567EF9Val() {}
	void *m_tag;
	int m_refs;
	int m_a;
	int m_b;
	Rva00567EF9Val(int a, int b);
};

extern int g_rva00567EF9Tag;

inline Rva00567EF9Val::Rva00567EF9Val(int a, int b)
{
	m_refs = 0;
	m_tag = &g_rva00567EF9Tag;
	m_a = a;
	m_b = b;
}

struct Rva00567EF9Maker
{
	int m_00;
	int m_04;
	int m_a;
	int m_b;
	Rva00567EF9Val **Make(Rva00567EF9Val **out);
};

Rva00567EF9Val **Rva00567EF9Maker::Make(Rva00567EF9Val **out)
{
	Rva00567EF9Val *slot = 0;
	Rva00567EF9Val *p = new Rva00567EF9Val(m_a, m_b);
	*out = p;
	if (p != 0)
		p->m_refs++;
	return out;
}
