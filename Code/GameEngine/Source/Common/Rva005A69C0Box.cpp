// cl: -O1 -Oy- -GR- -EHsc-
// ?Run@Rva005A69C0Box@@QAEXHHH@Z @0x005A69C0 140B: two-slot validated swap
// prep. After the predicate and triple ushort-guard (a<8, b<8, a!=b), both
// slots must be present and human (pinned 0x3FF0F1); the +0x28 sub-object
// consumes the full (a, b, c) via the pinned 3-arg callee 0x5DC187, then
// +0x10 stamps 1 while the byte table clears the non-current index. All
// call targets read from retail REL32; true identities unproven.
struct Rva005A69C0Obj
{
	bool IsHuman();
};

struct Rva005A69C0Sub
{
	void Do3(int a, int b, int c);
};

struct Rva005A69C0Box
{
	char pad0[8];
	Rva005A69C0Obj **m_8;
	int m_C;
	int m_10;
	int m_14;
	char pad1[0x28 - 0x18];
	Rva005A69C0Sub m_28;
	char pad2[0x8e4 - 0x29];
	unsigned char m_8E4[8];
	int m_8EC[8];
	int *m_90C[8];

	bool Check();
	void Run(int a, int b, int c);
};

void Rva005A69C0Box::Run(int a, int b, int c)
{
	if (!Check())
		return;
	if ((unsigned short)a >= 8)
		return;
	if ((unsigned short)b >= 8)
		return;
	if ((unsigned short)a == (unsigned short)b)
		return;
	int an = (unsigned short)a;
	Rva005A69C0Obj *oa = m_8[an];
	if (oa == 0)
		return;
	int bn = (unsigned short)b;
	if (m_8[bn] == 0)
		return;
	if (!oa->IsHuman())
		return;
	if (!m_8[bn]->IsHuman())
		return;
	m_28.Do3(a, b, c);
	if (an == m_14) {
		m_10 = 1;
		m_8E4[bn] = 0;
	} else {
		m_10 = 1;
		m_8E4[an] = 0;
	}
}
