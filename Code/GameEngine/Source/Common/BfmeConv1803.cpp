// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Ported from Open-BFME-1 GameEngine/Source/Common/BfmeConv1803.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ??0BfmeOwnerZQ@@QAE@PAX000@Z 0x000EF272 (40B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
extern int BfmeVfZQ;

class BfmeOwnerZQ
{
public:
	BfmeOwnerZQ(void *first, void *second, void *third, void *fourth);
	void bfmeBaseInitZQ(void *first, void *second, void *third, void *fourth, int fifth, int sixth);

	void *m_bfmeVfZQ;
	char unknown04[0x3C-4];
};

BfmeOwnerZQ::BfmeOwnerZQ(void *first, void *second, void *third, void *fourth)
{
	bfmeBaseInitZQ(first, second, third, fourth, 1, 0);
	m_bfmeVfZQ = &BfmeVfZQ;

}

// Target EF902..EF961 independently proves this is the constructor of a
// newly allocated3C-byte texture resource: four constructor arguments are
// height,width,format,3 and its result is adopted by the existing retaining
// setterEF87B. The old BF1-derived bfmeInitZQ spelling represented exactly
// this body as an initialization method. Rename its sole owner to the
// constructor and keep its complete40B bytes; no alias or added coverage.
// The class name and six-argument base initializer remain donor placeholders.
