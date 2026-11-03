// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Ported from Open-BFME-1 GameEngine/Source/Common/BfmeConv1401.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?bfmeGoVKH@BfmeThingVKH@@QAE?AUBfmeMat4VKH@@H@Z 0x00075295 (40B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
// Open-BFME5 conversions.

struct BfmeMat4VKH
{
	int m_bfmeArr[16];
};

class BfmeThingVKH;

// Retail's callee is the d3dx9_27 import thunk _D3DXMatrixMultiply@12 at
// 0x0062AF26 (Code/masm_dumps/D3DX9ImportThunks.asm); the caller passes its
// three stack arguments in this unit's own types.
extern "C" void *__stdcall D3DXMatrixMultiply(BfmeMat4VKH *out,
    BfmeThingVKH *self, int a);

class BfmeThingVKH
{
public:
	BfmeMat4VKH bfmeGoVKH(int rightMatrixAddress);
};

BfmeMat4VKH BfmeThingVKH::bfmeGoVKH(int rightMatrixAddress)
{
	BfmeMat4VKH product;
	D3DXMatrixMultiply(&product, this, rightMatrixAddress);
	return product;
}
