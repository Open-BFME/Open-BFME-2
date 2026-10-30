// cl: /GR- /EHsc- /Ireference/open-bfme-1/game/GameEngine/Include /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
//
// Bodies ported from Open-BFME-1's GameEngine/Source/Common/BfmeConv803.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus
// /O1). Compiled that way each body below places uniquely on unclaimed
// game.dat .text by masked whole-.text search, and ./build.sh reproduces it
// byte for byte: bfmeGoEBL 0x0036173F (23B). Callee addresses are read off
// retail's call sites (reverse/symbols.csv). Only the placed bodies are
// carried; the donor's other definitions are omitted.
class BfmeObjEBJ;

extern "C" unsigned char bfmeStrEBJ[];


class BfmeObjEBK
{
public:
	void bfmeTwoEBK(void *x, void *b);
};

// Retail body at 0x007E8900 is BfmeThingRF::bfmeGoRF; declared here (no real
// header owns it) so this call spells its defining mangled name.
class BfmeThingRF
{
public:
	void *bfmeGoRF(void *key, void *fallback);
};

extern void *g_bfmeXEBK;


class BfmeObjEBL
{
public:
	void *m_bfmeA;
	void *m_bfmeB;
};

extern unsigned char *g_validityBegin;
extern unsigned char *g_validityEnd;

// LINK: the call is rowed as Rva00361624::rva00361624 (0x00361624), which also
// returns its first argument; the result is unused here.
class Rva0036105B;
class Rva00361624
{
public:
	Rva0036105B *rva00361624(Rva0036105B *a, Rva0036105B *b);
};

void bfmeGoEBL()
{
	((Rva00361624 *)&g_validityBegin)->rva00361624((Rva0036105B *)g_validityBegin, (Rva0036105B *)g_validityEnd);
}

char bfmeCmpEBMa(void *a, void *b);
char bfmeCmpEBMb(void *a, void *b);


struct BfmeSubEBN
{
	unsigned char m_bfmeHead[0x20];
	char m_bfmeC;
	unsigned char m_bfmePad[3];
	void *m_bfmeP;
};

class BfmeObjEBN
{
public:
	BfmeSubEBN *bfmeGetEBN();
};
