// ?rva005FA98CSwap@@YIXPAVRva005FA98C@@HHHHHH@Z
// partial score=0.8 date=2026-10-06
// cl: /O1 /EHa /DNDEBUG /MD
// ?rva005FA98CSwap@@YIXPAVRva005FA98C@@HHHHHH@Z @0x005FA98C 84B evidence:
// fastcall guarded swap (this, fwd-dead-in-edx, unused, b, c, d, e) with
// ebp frame: d==e returns; b/c checked against o->m_04->m_18/m_1C else
// return; esi/edi = rowed thiscall ?rva005FA8F5@Rva005FA8F5@@QAEPAURva005FA8F5Entry@@H@Z
// @0x005FA8F5 on ambient this with (d)/(e); pinned fastcall
// ?rva00A00062@@YIXPAVRva00A00062Sub@@HHH@Z @0x00A00062 on m_04+8 with
// (esi->m_04, edi->m_04); then swaps [esi+4]/[edi+4]; ret 0x14.
// Same fastcall family as 0x005F8E37. TU-local views only.
struct Rva005FA8F5Entry
{
	char m_pad[4];
	int m_04;
};

Rva005FA8F5Entry *__stdcall rva005FA8F5Find(int arg);

struct Rva00A00062Sub
{
	char m_pad[0x10];
};
void __fastcall rva00A00062(Rva00A00062Sub *sub, int fwd, int s1, int s2);

struct Rva005FA98CM04
{
	char m_pad[8];
	Rva00A00062Sub m_sub08;
	int m_18;
	int m_1C;
};

class Rva005FA98C
{
public:
	char m_pad[4];
	Rva005FA98CM04 *m_04;
};

// ?rva005FA98CSwap@@YIXPAVRva005FA98C@@HHHHHH@Z present-unmatched
void __fastcall rva005FA98CSwap(Rva005FA98C *o, int fwd, int unused, int b, int c, int d, int e)
{
	if (d == e)
		return;
	Rva005FA98CM04 *m = o->m_04;
	if (b != m->m_18)
		return;
	if (c != m->m_1C)
		return;
	Rva005FA8F5Entry *r1 = rva005FA8F5Find(d);
	Rva005FA8F5Entry *r2 = rva005FA8F5Find(e);
	rva00A00062(&m->m_sub08, fwd, r1->m_04, r2->m_04);
	int t = r1->m_04;
	r1->m_04 = r2->m_04;
	r2->m_04 = t;
}
