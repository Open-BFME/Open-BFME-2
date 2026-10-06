// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Ported from Open-BFME-1 GameEngine/Source/Common/BfmeConv2142.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?bfmeEitherQP@@YAHPAX0@Z 0x004D93B5 (45B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
char bfmeTestQP(void *a, void *b);

int bfmeEitherQP(void *a, void *b)
{
	if (bfmeTestQP(a, b) || bfmeTestQP(b, a))
		return 1;

	return 0;
}
