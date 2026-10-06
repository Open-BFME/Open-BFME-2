// ?rva005F963ASelect@@YIXPAVRva005F963A@@HH@Z
// partial score=0.8 date=2026-10-06
// cl: /O1 /DNDEBUG /MD
// ?rva005F963ASelect@@YIXPAVRva005F963A@@HH@Z @0x005F963A 77B evidence:
// fastcall select (this, fwd-dead-in-edx, arg): cur = m_4C; if cur>=0 and
// m_40[cur]->m_28 != 3 return; if arg == cur return; if cur>=0
// m_40[cur] takes pinned thiscall-0 ?rva005F9567@Rva005F963AElem@@QAEXXZ
// @0x005F9567; m_2C takes pinned fastcall ?rva009CC208@@YIXPAURva009CC208Sub@@HH@Z
// @0x009CC208(arg) with fwd untouched in edx; m_4C = arg; reloaded element
// takes pinned thiscall-0 ?rva005F94C2@Rva005F963AElem@@QAEXXZ @0x005F94C2;
// ret 4. Sibling 0x005F9687 queued separately. TU-local views only.
struct Rva005F963AElem
{
	char m_pad[0x28];
	int m_28;
	void rva005F9567();
	void rva005F94C2();
};

struct Rva009CC208Sub
{
	char m_pad[4];
};

void __fastcall rva009CC208(Rva009CC208Sub *sub, int fwd, int x);

class Rva005F963A
{
public:
	char m_pad[0x2C];
	Rva009CC208Sub *m_2C;
	char m_pad2[0x40 - 0x30];
	Rva005F963AElem **m_40;
	char m_pad3[0x4C - 0x44];
	int m_4C;
};

// ?rva005F963ASelect@@YIXPAVRva005F963A@@HH@Z present-unmatched
void __fastcall rva005F963ASelect(Rva005F963A *o, int fwd, int arg)
{
	int cur = o->m_4C;
	if (cur >= 0)
	{
		if (o->m_40[cur]->m_28 != 3)
			return;
	}
	if (arg == cur)
		return;
	if (cur >= 0)
		o->m_40[cur]->rva005F9567();
	rva009CC208(o->m_2C, fwd, arg);
	o->m_4C = arg;
	Rva005F963AElem *e = o->m_40[o->m_4C];
	e->rva005F94C2();
}
