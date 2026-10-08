// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Ported from Open-BFME-1 GameEngine/Source/Common/BfmeConv1611.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?bfmeCreateVTD@@YAPAVBfmeThingVTD@@XZ 0x00225F44 (50B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
// Open-BFME5 conversions.

void *__cdecl operator new(unsigned int size);
void __cdecl operator delete(void *block);

// The object built is Rva0060061A (one vtable pointer; its ctor is the rowed
// ??0Rva0060061A at 0x00600611, the call retail makes).
class BfmeThingVTD;
class Rva0060061A
{
public:
	Rva0060061A();
	virtual ~Rva0060061A();
};

BfmeThingVTD *bfmeCreateVTD()
{
	return (BfmeThingVTD *)new Rva0060061A;
}
