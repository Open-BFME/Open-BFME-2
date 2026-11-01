// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Bodies ported from Open-BFME-1's GameEngine/Source/Common/BfmeConv991.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus
// /O1). Compiled that way each body below places uniquely on unclaimed
// game.dat .text by masked whole-.text search, and ./build.sh reproduces it
// byte for byte: bfmeGo991B 0x0004CB32 (45B). Callee addresses are read off
// retail's call sites (reverse/symbols.csv). Only the placed bodies are
// carried; the donor's other definitions are omitted.
// Open-BFME5 conversions.

void bfmeStepA991(void);
void bfmeStepB991(void);
void bfmeFinish991(void);



class BfmeB991
{
public:
	virtual void bfmeVB0991();
	virtual void bfmeVB1991();
	virtual void bfmeTick991();


	char m_bfmePad[0x1c];
	int m_bfmeSlot;
};

// Retail 0x0004CB40 calls the verified W3DSmudgeManager::render owner at
// 0x000A6E08. The donor's integer argument carries its RenderInfoClass address.
class RenderInfoClass;
class W3DSmudgeManager
{
public:
	void render(RenderInfoClass &rinfo);
};

extern BfmeB991 *g_bfmeB991;
extern int g_bfmeVal991;

void bfmeGo991B(int a)
{
	if (!g_bfmeB991)
		return;

	reinterpret_cast<W3DSmudgeManager *>(g_bfmeB991)->render(
		*reinterpret_cast<RenderInfoClass *>(a));
	g_bfmeB991->bfmeTick991();
	g_bfmeB991->m_bfmeSlot = g_bfmeVal991;
}



