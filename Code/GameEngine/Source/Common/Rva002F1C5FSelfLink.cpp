// cl: /O1 /DNDEBUG /MD
//
// Self-link init methods: each runs an unrowed member helper (pinned from
// the body's own REL32), zeroes its +4 word and its pointed-to sub-object's
// byte+0/dword+4, self-links the sub-object's +8/+0xC words, and returns
// this.
// 0x002F1C5F -> 0x002F0C32. 0x002F1CB3 -> 0x002F0C55.
// 0x004152BC -> 0x004151C4.

struct Sub002F1C5F
{
	unsigned char flag;
	char pad[3];
	int m_04;
	Sub002F1C5F *m_08;
	Sub002F1C5F *m_0C;
};

class Rva002F1C5F
{
public:
	Rva002F1C5F *rva002F1C5F(int a0, int a1);
private:
	void helper(int x);
	Sub002F1C5F *m_00;
	int m_04;
};
Rva002F1C5F *Rva002F1C5F::rva002F1C5F(int a0, int a1)
{
	helper(a1);
	m_04 = 0;
	m_00->flag = 0;
	m_00->m_04 = 0;
	m_00->m_08 = m_00;
	m_00->m_0C = m_00;
	return this;
}

struct Sub002F1CB3
{
	unsigned char flag;
	char pad[3];
	int m_04;
	Sub002F1CB3 *m_08;
	Sub002F1CB3 *m_0C;
};

class Rva002F1CB3
{
public:
	Rva002F1CB3 *rva002F1CB3(int a0, int a1);
private:
	void helper(int x);
	Sub002F1CB3 *m_00;
	int m_04;
};
Rva002F1CB3 *Rva002F1CB3::rva002F1CB3(int a0, int a1)
{
	helper(a1);
	m_04 = 0;
	m_00->flag = 0;
	m_00->m_04 = 0;
	m_00->m_08 = m_00;
	m_00->m_0C = m_00;
	return this;
}

struct Sub004152BC
{
	unsigned char flag;
	char pad[3];
	int m_04;
	Sub004152BC *m_08;
	Sub004152BC *m_0C;
};

class Rva004152BC
{
public:
	Rva004152BC *rva004152BC(int a0, int a1);
private:
	void helper(int x);
	Sub004152BC *m_00;
	int m_04;
};
Rva004152BC *Rva004152BC::rva004152BC(int a0, int a1)
{
	helper(a1);
	m_04 = 0;
	m_00->flag = 0;
	m_00->m_04 = 0;
	m_00->m_08 = m_00;
	m_00->m_0C = m_00;
	return this;
}
