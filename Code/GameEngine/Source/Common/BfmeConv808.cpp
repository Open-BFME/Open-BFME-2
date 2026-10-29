// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Ported from Open-BFME-1 GameEngine/Source/Common/BfmeConv808.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?CurDrawableHideModule@@YAHPAX@Z 0x00333722 (25B)
//   ?CurDrawableShowModule@@YAHPAX@Z 0x0033373B (25B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
struct BfmeAEFC
{
	unsigned char m_bfmeHead[0x40];
	float m_bfmeF;
};

struct BfmeBEFC
{
	unsigned char m_bfmeHead[8];
	float m_bfmeF;
};

void __stdcall bfmeCallEFC(BfmeAEFC *a, float v);


struct BfmeBEFD
{
	unsigned char m_bfmeHead[0x40];
	float m_bfmeF;
};


struct BfmeNodeEFE
{
	BfmeNodeEFE *bfmeUpdEFE();
	unsigned char m_bfmeHead[4];
	BfmeNodeEFE *m_bfmeQ;
	unsigned char m_bfmePad[0x18];
	int m_bfmeX;
};

struct BfmeThingEFE
{
	int bfmeGoEFE();
	unsigned char m_bfmeHead[4];
	BfmeNodeEFE *m_bfmeP;
	unsigned char m_bfmePad[0x18];
	int m_bfmeX;
};


void *__cdecl bfmeOneEFF(void *a, int n);
void __cdecl bfmeTwoEFF(int n, void *r);

int CurDrawableHideModule(void *luaState)
{
	bfmeTwoEFF(1, bfmeOneEFF(luaState, 1));
	return 0;
}

class BfmeThingEFG
{
public:
	BfmeThingEFG *bfmeGoEFGa(BfmeThingEFG *o);
	BfmeThingEFG *bfmeGoEFGb(BfmeThingEFG *o);
	void bfmeClearEFG();
	void bfmeCopyEFG(BfmeThingEFG *o);
};



void __cdecl bfmeTwoEFFb(int n, void *r);

int CurDrawableShowModule(void *a)
{
	bfmeTwoEFFb(0, bfmeOneEFF(a, 1));
	return 0;
}

struct BfmeNodeEFH
{
	BfmeNodeEFH *bfmeUpdEFH();
	unsigned char m_bfmeHead[4];
	BfmeNodeEFH *m_bfmeQ;
	unsigned char m_bfmePad[0x10c];
	char m_bfmeC;
};

struct BfmeThingEFH
{
	char bfmeGoEFH();
	unsigned char m_bfmeHead[4];
	BfmeNodeEFH *m_bfmeP;
	unsigned char m_bfmePad[0x10c];
	char m_bfmeC;
};


// Each retail call in this body reads an address the ledger already carries
// under the rowed name below. Bind the donor spelling to that owner so one
// address keeps one definition and the unit links.
//   0x003336AD reads ?Rva003336ADGet@@YA_N_NPBD@Z
#pragma comment(linker, "/alternatename:?bfmeTwoEFF@@YAXHPAX@Z=?Rva003336ADGet@@YA_N_NPBD@Z")
//   0x007473B0 reads _lua_tostring
#pragma comment(linker, "/alternatename:?bfmeOneEFF@@YAPAXPAXH@Z=_lua_tostring")
//   0x003336AD reads ?Rva003336ADGet@@YA_N_NPBD@Z
#pragma comment(linker, "/alternatename:?bfmeTwoEFFb@@YAXHPAX@Z=?Rva003336ADGet@@YA_N_NPBD@Z")
