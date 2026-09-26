// cl: /O1 /MD
// ?bfmeGoCAE@BfmeThingCAE@@QAEHXZ, retail 0x004C0E68, 35 bytes. Ported from
// BFME1 BfmeConv565 (BfmeThingCAE::bfmeGoCAE returns 3, RunCAE at slot 8
// offset 0x20); head 0xD0 to 0xF0 per retail (same as DHB precedent at
// 0x4C0E46); AskCAE shares the folded Ask body at 0x4C0D4F (twin pin, 8
// existing Ask pins there); tail jmp slot 8 with default 3.
class BfmeInnerCAE
{
public:
	virtual void bfmeSpareCAE0();
	virtual void bfmeSpareCAE1();
	virtual void bfmeSpareCAE2();
	virtual void bfmeSpareCAE3();
	virtual void bfmeSpareCAE4();
	virtual void bfmeSpareCAE5();
	virtual void bfmeSpareCAE6();
	virtual void bfmeSpareCAE7();
	virtual int bfmeRunCAE();
};

struct BfmeSubCAE
{
	unsigned char m_bfmeHead[0x10];
	BfmeInnerCAE m_bfmeInner;
};

class BfmeOuterCAE
{
public:
	bool bfmeAskCAE();
};

class BfmeThingCAE
{
public:
	int bfmeGoCAE();
	unsigned char m_bfmeHead[0xf0];
	BfmeSubCAE *m_bfmeSub;
};

int BfmeThingCAE::bfmeGoCAE()
{
	if (((BfmeOuterCAE *)((char *)this - 0x10))->bfmeAskCAE())
		return m_bfmeSub->m_bfmeInner.bfmeRunCAE();
	return 3;
}
