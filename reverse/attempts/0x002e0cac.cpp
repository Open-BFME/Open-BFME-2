// ?rva002E0CAC@Rva002E0CACOwner@@QAEHXZ
// partial score=0.95 date=2026-10-06
// cl: /O1 /DNDEBUG /MD
//
// ?rva002E0CAC@Rva002E0CACOwner@@QAEHXZ @0x002E0CAC 40B: min selector
// (thiscall, int return). Returns the smaller of ([+0x40]+0x10 plus +0x290)
// and ([+0x40]+0x14) via two ebp locals and a jl. Honest address-derived
// names; intermediate identities unproven.

struct Rva002E0CACMid
{
	int m_00[4];
	int m_10;
	int m_14;
};

class Rva002E0CACOwner
{
public:
	int rva002E0CAC();
private:
	char m_pad00[0x40];
	Rva002E0CACMid *m_p40;
	char m_pad44[0x290 - 0x44];
	int m_290;
};

// ?rva002E0CAC@Rva002E0CACOwner@@QAEHXZ
int Rva002E0CACOwner::rva002E0CAC()
{
	Rva002E0CACMid *p = m_p40;
	int a = p->m_10;
	a += m_290;
	int b = p->m_14;
	int *sel = (a < b) ? &a : &b;
	return *sel;
}
