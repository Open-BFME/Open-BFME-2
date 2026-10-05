// ?rva003BD391@@YGXH@Z
// partial score=0.94 date=2026-10-05
// ?rva003BD391@@YGXH@Z @0x003BD391 34B -- partial 32/34
// Same source shape as the exact flag-1 sisters, but the pushed flag 0 makes
// MSVC7.1/O1 load slot10 into ecx (8b4810/85c9, index into eax, no final
// mov ecx,eax: 32B) instead of eax (34B exact). Nine variants tested:
// plain, hoisted int, (uchar)0 cast, false, const zero, -1+index, nameless,
// &&-chain, nested ifs, two-locals, 1-1. All flag-0 spellings give ecx.
class Rva004266A1 { public: void rva00426914(int index, unsigned char value); };
struct Rva004266A1Holder { char m_pad[0x10]; Rva004266A1 *m_slot10; };
extern Rva004266A1Holder *g_00E031E8;
void __stdcall rva003BD391(int index)
{
	Rva004266A1Holder *holder = g_00E031E8;
	if (holder == 0)
		return;
	Rva004266A1 *p = holder->m_slot10;
	if (p == 0)
		return;
	p->rva00426914(index - 1, 0);
}
