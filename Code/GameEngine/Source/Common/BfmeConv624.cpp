// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Ported from Open-BFME-1 GameEngine/Source/Common/BfmeConv624.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?bfmeGoCME@BfmeThingCME@@QAEHPAX@Z 0x0027F0D3 (53B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
struct BfmeTempCME
{
	BfmeTempCME();
	unsigned char m_bfmeHead[0x14];
	int m_bfmeResult;
};

class BfmeThingCME
{
public:
	void bfmeCallCME(void *what, float value, BfmeTempCME *out, int one, int two);
	int bfmeGoCME(void *what);
	int rva0027F108(void *what, float value, int one, int two);
};

int BfmeThingCME::bfmeGoCME(void *what)
{
	BfmeTempCME tmp;
	bfmeCallCME(what, 10.0f, &tmp, 0, 0);
	return tmp.m_bfmeResult;
}

int BfmeThingCME::rva0027F108(void *what, float value, int one, int two)
{
	BfmeTempCME tmp;
	bfmeCallCME(what, value, &tmp, one, two);
	return tmp.m_bfmeResult;
}
