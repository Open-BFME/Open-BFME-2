// cl: /O1 /EHsc /DNDEBUG /MD /DWIN32 /D_WINDOWS
//
// ?rva00298835@Rva00298835@@QAEXPAUBfmeCopyElementA@@@Z @0x00298835 94B.
// Ensure-owned-then-copy: if the +0x104 slot does not already point at
// the embedded +0xA8 BfmeCopyElementA, heap-allocate a GeometryInfo
// there, then run rowed bfmeAssign into it.
//
// Target evidence (game.dat, read-only, capstone): EH prolog (mov eax
// cookie + call rowed __EH_prolog 0x629188, state slot [ebp-4], new
// pointer at [ebp-0x10]); rowed operator new 0x2FDA0 (push 0x5C,
// cdecl-cleand via pop ecx), rowed GeometryInfo ctor 0x29840D, rowed
// BfmeCopyElementA::bfmeAssign 0x64605 (struct spelling, PAU). The
// GeometryInfo view below is size-only (0x5C proven by the push);
// its real layout lives in GeometryInfoCtor.cpp. Holder and identities
// unproven: honest address-derived names; the sibling 0x29895A wrapper
// shares the +0xA8 member and may rehome here.
struct BfmeCopyElementA
{
	BfmeCopyElementA *bfmeAssign(BfmeCopyElementA *source);
};

class GeometryInfo
{
public:
	GeometryInfo();
private:
	unsigned char m_pad[0x5C];
};

class Rva00298835
{
public:
	void rva00298835(BfmeCopyElementA *p);
private:
	unsigned char m_pad00[0xA8];
	unsigned char m_padA8[0x104 - 0xA8];
	BfmeCopyElementA *m_104;
};

// ?rva00298835@Rva00298835@@QAEXPAUBfmeCopyElementA@@@Z
void Rva00298835::rva00298835(BfmeCopyElementA *p)
{
	if (m_104 == (BfmeCopyElementA *)&m_pad00[0xA8])
		m_104 = (BfmeCopyElementA *)new GeometryInfo;
	m_104->bfmeAssign(p);
}
