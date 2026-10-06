// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Ported from Open-BFME-1 GameEngine/Source/Common/BfmeConv808.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?bfmeGoEFFa@@YAHPAX@Z 0x00333722 (25B)
//   ?bfmeGoEFFb@@YAHPAX@Z 0x0033373B (25B)
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

int bfmeGoEFFa(void *a)
{
	bfmeTwoEFF(1, bfmeOneEFF(a, 1));
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

int bfmeGoEFFb(void *a)
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

