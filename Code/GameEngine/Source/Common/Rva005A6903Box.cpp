// cl: -GR- -EHsc-
// NAT::processPlayerJoin @0x005A6903 92B (WorldBuilder name, its
// __FUNCTION__ string "NAT::processPlayerJoin"; WB calls
// PortNegotiationSchema::playerJoin where retail calls 0x005DC291): bounds-checked slot refresh.
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
	void rva005DC070(int idx);
};

// Retail resets an eight-byte value with a dword and a ushort member;
// the last two bytes are padding, copied with the member representation.
struct Rva005A695FValue
{
	__forceinline Rva005A695FValue() : value00(0), value04(0) {}
	int value00;
	unsigned short value04;
};

struct NAT
{
	char pad0[8];
	Rva005A6903Obj **m_8;
	int m_C;
	int m_10;
	int m_14;
	int m_18;
	char pad1[0x28 - 0x1C];
	Rva005A6903Sub m_28;
	char pad2[0x8e4 - 0x29];
	unsigned char m_8E4[8];
	int m_8EC[8];
	Rva005A695FValue *m_90C[8];
	char pad3[0x94C - 0x92C];
	int m_94C;
	int m_950;

	bool rva005A6709();
	void processPlayerJoin(int idx);
	void rva005A695F(int idx);
};

// 0x005A671D ignores incoming ecx (loads its context from the 0xE063FC
// global first thing), so it is spelled as a free function: no ecx setup.
int Rva005A671DNext();

void NAT::processPlayerJoin(int idx)
{
	if ((unsigned short)idx >= 8)
		return;
	m_28.DoX(idx);
	idx = (unsigned short)idx;
	Rva005A6903Obj *o = m_8[idx];
	Rva005A695FValue *p = m_90C[idx];
	p->value00 = o->m_38;
	if (!rva005A6709())
		return;
	if (idx == m_14) {
		m_10 = 1;
		return;
	}
	m_10 = 1;
	m_8E4[idx] = 0;
	m_8EC[idx] = Rva005A671DNext();
}

// Native 0x005A695F..0x005A69C0 RET4 shares the NAT tables and +0x28
// sub-object with the named join and reconnect siblings. This operation's
// original name remains unknown; it clears the selected slot and its value.
void NAT::rva005A695F(int idx)
{
	if ((unsigned short)idx >= 8)
		return;
	int slot = (unsigned short)idx;
	if (m_18 == slot)
	{
		m_18 = -1;
		m_94C = 0;
		m_950 = 0;
	}
	m_28.rva005DC070(idx);
	m_8E4[slot] = 0;
	m_8EC[slot] = 0;
	*m_90C[slot] = Rva005A695FValue();
}
