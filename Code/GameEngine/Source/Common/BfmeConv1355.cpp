// bfmeAssignVGO, retail 0x006CDB10 (66B).
// Ported from Open-BFME-1 Code/GameEngine/Source/Common/BfmeConv1355.cpp
// (BFME1 0x00892B90). Only the placed ref-counted assign is defined here;
// the donor's bfmeGoVGM viewport helper stays out (with it goes the donor's
// __ftol2 declaration), so the unmatched-definition gate passes. The refcount
// calls use their matched row names; the drop call retains bfmeDropVGO.

int __cdecl Rva006CFDF0DecRef(int *p);
class Rva00894D80Accessor
{
public:
	static unsigned int increment(unsigned int *p);
};
void __cdecl bfmeDropVGO(void *p);

class BfmeRefVGO
{
public:
	BfmeRefVGO &bfmeAssignVGO(const BfmeRefVGO &o);
	unsigned *m_bfmeP;
};

// ?bfmeAssignVGO@BfmeRefVGO@@QAEAAV1@ABV1@@Z, retail 0x006CDB10 (66B).
BfmeRefVGO &BfmeRefVGO::bfmeAssignVGO(const BfmeRefVGO &o)
{
	if (&o != this)
	{
		if (m_bfmeP && Rva006CFDF0DecRef((int *)m_bfmeP) == 0)
			bfmeDropVGO(m_bfmeP);
		m_bfmeP = o.m_bfmeP;
		if (m_bfmeP)
			Rva00894D80Accessor::increment(m_bfmeP);
	}
	return *this;
}

// Whole BFME 1 UnclaimedSmallLeaves02.cpp at9cbfb551fe emits this zero-word
// helper under two opaque const-member names in the named Common O2/x87/G6
// min5 sweep. Native6CDB60..6CDB6D is INT3-bounded, reads the first stack
// pointer, stores one zero dword through it, and pops4 bytes; ECX is unused.
// No direct/address references establish an original owner, member identity
// or return contract. This ordinary callee-pop pointer projection preserves
// the native effect without claiming those identities or a second class view.
void __stdcall Rva006CDB60ClearWord(unsigned int *slot)
{
    *slot = 0;
}
