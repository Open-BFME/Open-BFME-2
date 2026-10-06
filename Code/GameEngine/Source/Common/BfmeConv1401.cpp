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

// Retail's callee at 0x009FACAD is the import thunk ?ji_009facad@@YAXXZ,
// defined in game/gen_small/imports_000.cpp as a no-argument jump stub; its
// caller supplies the three arguments on the stack, so the stub is reached
// through a typed pointer.
extern void __cdecl ji_009facad();
typedef void (__stdcall *Rva009FACADCalc)(BfmeMat4VKH *out,
    BfmeThingVKH *self, int a);

class BfmeThingVKH
{
public:
	BfmeMat4VKH bfmeGoVKH(int a);
};

BfmeMat4VKH BfmeThingVKH::bfmeGoVKH(int a)
{
	BfmeMat4VKH t;
	reinterpret_cast<Rva009FACADCalc>(&ji_009facad)(&t, this, a);
	return t;
}
