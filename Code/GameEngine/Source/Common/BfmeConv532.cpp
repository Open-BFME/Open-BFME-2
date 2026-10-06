// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Ported from Open-BFME-1 GameEngine/Source/Common/BfmeConv532.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?bfmeGoBUC@@YAXPAVBfmeSubBUC@@PAX111@Z 0x00456520 (29B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
class BfmeSubBUC
{
public:
	void bfmeDoBUC(void *one, void *two, void *three, void *four);
};

void bfmeGoBUC(BfmeSubBUC *sub, void *one, void *two, void *three, void *four)
{
	if (sub != 0)
		sub->bfmeDoBUC(one, two, three, four);
}
