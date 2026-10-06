// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Ported from Open-BFME-1 GameEngine/Source/Common/BfmeConv2133Forward.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?bfmeForward@Gen_001D5EE0Target@@QAEXPAX0@Z 0x000A8B0A (25B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
class Shadow
{
public:
	void setSize(float width, float height);
};

class Gen_001D5EE0Target
{
public:
	void bfmeForward(void *width, void *height);
};

void Gen_001D5EE0Target::bfmeForward(void *width, void *height)
{
	((Shadow *)this)->setSize(*(float *)&width, *(float *)&height);
}
