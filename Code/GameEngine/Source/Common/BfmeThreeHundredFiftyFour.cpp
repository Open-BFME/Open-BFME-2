// BFME2 carries five more virtuals ahead of bfmeHeadUC than BFME1 (slot 0x48, not 0x34).
extern int g_bfmeVtableCZ[];					// retail 0x008E4A10

class BfmeThingUC;
class BfmeNodeUC;

class BfmeSubUC
{
public:
	virtual void bfmeSpareUC0();
	virtual void bfmeSpareUC1();
	virtual void bfmeSpareUC2();
	virtual void bfmeSpareUC3();
	virtual void bfmeSpareUC4();
	virtual void bfmeSpareUC5();
	virtual void bfmeSpareUC6();
	virtual void bfmeSpareUC7();
	virtual void bfmeSpareUC8();
	virtual void bfmeSpareUC9();
	virtual void bfmeSpareUCA();
	virtual void bfmeSpareUCB();
	virtual void bfmeSpareUCC();
	virtual void bfmeSpareUCD();
	virtual void bfmeSpareUCE();
	virtual void bfmeSpareUCF();
	virtual void bfmeSpareUCG();
	virtual void bfmeSpareUCH();
	virtual BfmeNodeUC *bfmeHeadUC();
	void bfmeDropUC(BfmeThingUC *who);
};

class BfmeThingUC
{
public:
	void bfmeResetUC();
	void *m_bfmeVft;
	unsigned char m_bfmeGap[8];
	BfmeSubUC *m_bfmeSub;
};

class BfmeNodeUC
{
public:
	virtual void bfmeSpareNodeUC();
	virtual BfmeNodeUC *bfmeNextUC();
	BfmeNodeUC *m_bfmeNext;
};

// The list head at 0x00E0ABB0 (ColdGlobalDwordGetters.cpp), read through this unit's view.
struct BfmeNodeEQB;
extern "C" BfmeNodeEQB *g_bfmeHeadEQB;

void BfmeThingUC::bfmeResetUC()
{
	BfmeSubUC *sub = m_bfmeSub;
	m_bfmeVft = (unsigned char *)g_bfmeVtableCZ;
	if (sub != 0)
		sub->bfmeDropUC(this);
}

void BfmeSubUC::bfmeDropUC(BfmeThingUC *who)
{
	BfmeNodeUC *previous = 0;
	BfmeNodeUC *at = bfmeHeadUC();
	while (at != 0)
	{
		if ((BfmeThingUC *)at == who)
		{
			if (at != 0)
			{
				if (previous != 0)
					previous->m_bfmeNext = at->m_bfmeNext;
				else
					g_bfmeHeadEQB = (BfmeNodeEQB *)at->m_bfmeNext;
			}
			break;
		}
		previous = at;
		at = at->bfmeNextUC();
	}
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeDropVIH@BfmeSubVIH@@QAEXPAVBfmeThingVIH@@@Z=?bfmeDropUC@BfmeSubUC@@QAEXPAVBfmeThingUC@@@Z")
