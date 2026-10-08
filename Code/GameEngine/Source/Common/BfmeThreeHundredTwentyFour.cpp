class BfmeMemberRV
{
public:
	bool bfmeAskRV();
};

struct BfmeWorldRV
{
	unsigned char m_bfmeHead[0x210];	// BFME1 0x274
	BfmeMemberRV *m_bfmeOther;
};

extern class ControlBar *TheControlBar;
// g_bfmeWorldRV: matched references place it at VA 0xe01cfc (zero-filled .bss).
// The global at this VA is TheControlBar; this name aliases it rather than
// defining a second variable the rest of the game never sees.
#pragma comment(linker, "/alternatename:?g_bfmeWorldRV@@3PAUBfmeWorldRV@@A=?TheControlBar@@3PAVControlBar@@A")

class BfmeThingRV
{
public:
	BfmeMemberRV *bfmePickRV();
	unsigned char m_bfmeHead[0x10];	// BFME1 0xc
	BfmeMemberRV *m_bfmeMine;
};

BfmeMemberRV *BfmeThingRV::bfmePickRV()
{
	BfmeMemberRV *mine = m_bfmeMine;
	if (mine == 0)
		return 0;
	if (!mine->bfmeAskRV())
	{
		BfmeWorldRV *world = (*(BfmeWorldRV **)&TheControlBar);
		if (world != 0)
		{
			BfmeMemberRV *other = world->m_bfmeOther;
			if (other != 0)
				return other;
		}
	}
	return mine;
}

// Negated ask wrapper at retail 0x002A7DD0 (14 bytes), appended here: the
// body is mov ecx,[ecx+0x10]; call bfmeAskRV; neg al; sbb eax,eax; inc eax;
// ret, i.e. it returns the logical negation of BfmeMemberRV::bfmeAskRV on the
// pointer-owned member at +0x10. The owning class is unproven (12 call sites
// plus one tail-jmp at 0x0009DFD7), so the ledger name below claims only the
// address plus the witnessed shape. Same declared-only callee as above, so
// the gate resolves the call through its pin.

class Rva002A7DD0
{
public:
	int rva002A7DD0();

private:
	char m_lead[0x10];
	BfmeMemberRV *m_ptr10; // +0x10
};

int Rva002A7DD0::rva002A7DD0()
{
	return !m_ptr10->bfmeAskRV();
}
