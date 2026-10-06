// cl: /DNDEBUG /MD
//
// Two of a four-strong homogeneous family at 0x003BD32B..0x003BD391
// (34B each, dump range 18). Each resolves the 0x00E031E8 global's +0x10
// slot to a Rva004266A1 (the rowed QAEEH family at 0x0042680D proves the
// class) and forwards (index - 1, flag). The two callees differ only in the
// stored byte offset (+5 vs +6 in their bodies, read from retail); the flag
// is the pushed 0/1. The fourth member (0x003BD34D) is claimed by another
// seat and is deliberately absent here.
//
// ?rva003BD32B@@YGXH@Z @0x003BD32B: callee 0x0042682B, flag 1.
// ?rva003BD36F@@YGXH@Z @0x003BD36F: callee 0x00426914, flag 1.
// 0x003BD391 (flag 0 to 0x00426914) is banked as partial 32/34 in
// reverse/attempts/0x003BD391.cpp: identical source shape emits the slot10
// load into ecx instead of eax whenever the pushed flag is 0 (nine source
// variants tested); the two flag-1 sisters below are exact.
class Rva004266A1
{
public:
	void rva0042682B(int index, unsigned char value);
	void rva00426914(int index, unsigned char value);
};

struct Rva004266A1Holder
{
	char m_pad[0x10];
	Rva004266A1 *m_slot10;
};

extern Rva004266A1Holder *g_00E031E8;

void __stdcall rva003BD32B(int index)
{
	Rva004266A1Holder *holder = g_00E031E8;
	if (holder == 0)
		return;
	Rva004266A1 *p = holder->m_slot10;
	if (p == 0)
		return;
	p->rva0042682B(index - 1, 1);
}

void __stdcall rva003BD36F(int index)
{
	Rva004266A1Holder *holder = g_00E031E8;
	if (holder == 0)
		return;
	Rva004266A1 *p = holder->m_slot10;
	if (p == 0)
		return;
	p->rva00426914(index - 1, 1);
}
