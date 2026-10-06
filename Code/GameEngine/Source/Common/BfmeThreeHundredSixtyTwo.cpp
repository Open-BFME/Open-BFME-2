// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Ported from Open-BFME-1 GameEngine/Source/Common/BfmeThreeHundredSixtyTwo.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?bfmeKillVE@BfmeThingVE@@QAEPAXH@Z 0x000AD930 (40B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
// Retail vtable 0x0107C7D0: BfmeParserBindingBaseVE's vftable, i.e.
// ??_7BfmeParserBindingBaseVE@@6B@ (targets/game/reverse/dir32_addresses.csv).
// The declaration carries no C++ name: __identifier spells the retail symbol
// exactly, so the store below references the defining name.
extern "C" unsigned char __identifier("??_7BfmeParserBindingBaseVE@@6B@")[];

void bfmeFreeVE(void *what);

class BfmeSubVE
{
public:
	void bfmeDropVE(void *what);
};

class BfmeThingVE
{
public:
	void *bfmeKillVE(int flags);
	void *m_bfmeVft;
	BfmeSubVE *m_bfmeSub;
	void *m_bfmeWhat;
};

void *BfmeThingVE::bfmeKillVE(int flags)
{
	void *what = m_bfmeWhat;
	BfmeSubVE *sub = m_bfmeSub;
	m_bfmeVft = __identifier("??_7BfmeParserBindingBaseVE@@6B@");
	sub->bfmeDropVE(what);
	if ((flags & 1) != 0)
		bfmeFreeVE(this);
	return this;
}
