// ?rva005FB4A1Attach@@YIPAVRva005FB4A1@@PAV1@HPAPAV1@@Z
// partial score=0.85 date=2026-10-06
// cl: /O1 /Oy- /EHsc /DNDEBUG /MD
// ?rva005FB4A1Attach@@YIPAVRva005FB4A1@@PAV1@HPAPAV1@@Z @0x005FB4A1 62B
// evidence: thiscall-1 factory (this, out-pp) news Rva005FB4A1(12) via
// rowed ??2@YAPAXI@Z @0x002FDA0; the inline ctor zeroes m_04, installs
// vtable 0x00C79F24 by literal store, copies the outer m_08; the undefined
// dtor gives the new-expression its truncated EH state slot
// (and [ebp-4],0 with no transitions); stores to *pp; ref-bumps m_04 when
// non-null; returns pp; ret 4. Same shape as 0x005FB2CC (vtable differs).
// TU-local view only.
class Rva005FB4A1
{
public:
	__forceinline Rva005FB4A1(int m08);
	~Rva005FB4A1();
	int m_vt;
	int m_04;
	int m_08;
};

__forceinline Rva005FB4A1::Rva005FB4A1(int m08)
{
	m_04 = 0;
	((int *)this)[0] = 0x00C79F24;
	m_08 = m08;
}

// ?rva005FB4A1Attach@@YIPAVRva005FB4A1@@PAV1@HPAPAV1@@Z present-unmatched
Rva005FB4A1 *__fastcall rva005FB4A1Attach(Rva005FB4A1 *o, int fwd, Rva005FB4A1 **pp)
{
	volatile int framePad;
	framePad &= 0;
	Rva005FB4A1 *p = new Rva005FB4A1(o->m_08);
	if (p)
	{
	}
	else
	{
		p = 0;
	}
	*pp = p;
	if (p)
		p->m_04++;
	return (Rva005FB4A1 *)pp;
}
