// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Ported from Open-BFME-1 GameEngine/Source/Common/BfmeConv1803.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?bfmeInitZQ@BfmeOwnerZQ@@QAEPAV1@PAX000@Z 0x000EF272 (40B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
extern int BfmeVfZQ;

class BfmeOwnerZQ
{
public:
	BfmeOwnerZQ *bfmeInitZQ(void *first, void *second, void *third, void *fourth);
	void bfmeBaseInitZQ(void *first, void *second, void *third, void *fourth, int fifth, int sixth);

	void *m_bfmeVfZQ;
};

BfmeOwnerZQ *BfmeOwnerZQ::bfmeInitZQ(void *first, void *second, void *third, void *fourth)
{
	bfmeBaseInitZQ(first, second, third, fourth, 1, 0);
	m_bfmeVfZQ = &BfmeVfZQ;

	return this;
}
