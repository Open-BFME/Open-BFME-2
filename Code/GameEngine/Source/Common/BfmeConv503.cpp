// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Ported from Open-BFME-1 GameEngine/Source/Common/BfmeConv503.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?bfmeGoBOE@@YGXPAX000@Z 0x00514CEB (26B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
class BfmeSinkBOE
{
public:
	void bfmeDoBOE(void *one, void *two);
};

extern BfmeSinkBOE *g_bfmeSinkBOE;

void __stdcall bfmeGoBOE(void *one, void *two, void *three, void *four)
{
	BfmeSinkBOE *sink = g_bfmeSinkBOE;
	if (sink != 0)
		sink->bfmeDoBOE(one, two);
}
