// cl: -GR- -EHsc-
// ?Run@Rva005A6903Box@@QAEXH@Z @0x005A6903 92B: bounds-checked slot refresh.
// Index >= 8 returns early; else the +0x28 sub-object consumes the index,
// the +0x38 field of m_8[idx] stores through the m_90C[idx] pointer, the
// pinned predicate gates on, +0x10 stamps 1 with an early-out when the index
// is current, otherwise the byte/dword tables update with the pinned
// counter. All three callees pop nothing (callee cleanup), hence bare
// call sites; targets read from retail REL32.
struct Rva005A6903Obj
{
	char pad[0x38];
	int m_38;
};

struct Rva005A6903Sub
{
	void DoX(int idx);
};

struct Rva005A6903Box
{
	char pad0[8];
	Rva005A6903Obj **m_8;
	int m_C;
	int m_10;
	int m_14;
	char pad1[0x28 - 0x18];
	Rva005A6903Sub m_28;
	char pad2[0x8e4 - 0x29];
	unsigned char m_8E4[8];
	int m_8EC[8];
	int *m_90C[8];

	bool Check();
	void Run(int idx);
};

// 0x005A671D ignores incoming ecx (loads its context from the 0xE063FC
// global first thing), so it is spelled as a free function: no ecx setup.
int Rva005A671DNext();

void Rva005A6903Box::Run(int idx)
{
	if ((unsigned short)idx >= 8)
		return;
	m_28.DoX(idx);
	idx = (unsigned short)idx;
	Rva005A6903Obj *o = m_8[idx];
	int *p = m_90C[idx];
	*p = o->m_38;
	if (!Check())
		return;
	if (idx == m_14) {
		m_10 = 1;
		return;
	}
	m_10 = 1;
	m_8E4[idx] = 0;
	m_8EC[idx] = Rva005A671DNext();
}
