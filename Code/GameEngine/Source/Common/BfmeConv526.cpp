// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Ported from Open-BFME-1 GameEngine/Source/Common/BfmeConv526.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?bfmeGoBSF@BfmeThingBSF@@QAEPAV1@PAGPAX@Z 0x004D04FF (31B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
struct BfmeSubBSF
{
	void bfmeSetBSF(void *what);
	unsigned char m_bfmeHead[4];
};

class BfmeThingBSF
{
public:
	BfmeThingBSF *bfmeGoBSF(unsigned short *src, void *what);
	unsigned short m_bfmeKey;
	unsigned char m_bfmePad[2];
	BfmeSubBSF m_bfmeSub;
};

BfmeThingBSF *BfmeThingBSF::bfmeGoBSF(unsigned short *src, void *what)
{
	m_bfmeKey = *src;
	m_bfmeSub.bfmeSetBSF(what);
	return this;
}
