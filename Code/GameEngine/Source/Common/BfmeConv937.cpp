// BfmeThing937C::bfmeGo937C, retail 0x00176C70 (22B).
// Ported from Open-BFME-1 Code/GameEngine/Source/Common/BfmeConv937.cpp
// (BFME1 0x00958700). Only the placed null-checked accessor is defined here;
// the donor's 937A/937B/937E helpers stay out, so the unmatched-definition
// gate passes. Retail throws E_POINTER through the single pinned helper when
// the slot is null, then returns it.

void __stdcall bfmeThrow937C(unsigned int code);

class BfmeThing937C
{
public:
	void *bfmeGo937C();
	void *m_bfmeP;
};

// ?bfmeGo937C@BfmeThing937C@@QAEPAXXZ, retail 0x00176C70 (22B).
void *BfmeThing937C::bfmeGo937C()
{
	if (m_bfmeP == 0)
		bfmeThrow937C(0x80004003);
	return m_bfmeP;
}

class Rva0013107A
{
public:
	void PostLoad(const char *name);
};

class BfmeThing937B
{
public:
	virtual void *bfmeVirt937B();
	void bfmeGo937B();
	char m_bfmePad[0x10];
	Rva0013107A *m_bfmeSub;
};

// ?bfmeGo937B@BfmeThing937B@@QAEXXZ, retail 0x00132129 (18B).
//
// Virtual slot 0 plus the +0x14 sub call (vptr + pad seat the member). The
// callee is the recovered texture PostLoad at 0x00131E6E; the free-function
// twin name there is eliminated by the thiscall read of ecx.
void BfmeThing937B::bfmeGo937B()
{
	void *r = bfmeVirt937B();
	m_bfmeSub->PostLoad(static_cast<const char *>(r));
}

// Retail's call sites in this unit's matched rows land on bodies rowed under
// other spellings at the same addresses (same ABI). Bind the spellings used here.
#pragma comment(linker, "/alternatename:?bfmeThrow937C@@YGXI@Z=?_com_issue_error@@YGXJ@Z")
