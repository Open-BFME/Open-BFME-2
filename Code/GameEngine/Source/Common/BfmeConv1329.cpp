// Open-BFME5 conversions.
// ??0BfmeThingUBB@@QAE@XZ, retail 0x00329DC2 (36B). Ported from Open-BFME-1
// Code/GameEngine/Source/Common/BfmeConv1329.cpp (BFME1 0x001925D0). Trimmed
// to the placed UBB constructor; the UBA constructor is declared-only here.
// Callee bfmeInitUBB resolves via the new ledger pin at 0x00313581 (the
// donor's own family name; Ghidra 30B body, not a thunk).


class BfmeSubUBB
{
public:
	void bfmeInitUBB(int a);
};

class BfmeThingUBB
{
public:
	BfmeThingUBB();
	volatile short m_bfme00;
	volatile short m_bfme02;
	volatile short m_bfme04;
	volatile short m_bfme06;
	volatile int m_bfme08;
	BfmeSubUBB m_bfmeSub;
};

// ??0BfmeThingUBB@@QAE@XZ
BfmeThingUBB::BfmeThingUBB()
{
	m_bfme00 = 0;
	m_bfme02 = 0;
	m_bfme04 = 0;
	m_bfme06 = 0;
	m_bfme08 = 0;
	m_bfmeSub.bfmeInitUBB(0);
}
