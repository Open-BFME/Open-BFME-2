// cl: /GR- /EHsc- /Ireference/open-bfme-1/game/GameEngine/Include /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
//
// Bodies ported from Open-BFME-1's GameEngine/Source/Common/BfmeConv803.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus
// /O1). Compiled that way each body below places uniquely on unclaimed
// game.dat .text by masked whole-.text search, and ./build.sh reproduces it
// byte for byte: bfmeGoEBL 0x0036173F (23B). Callee addresses are read off
// retail's call sites (reverse/symbols.csv). Only the placed bodies are
// carried; the donor's other definitions are omitted.
// BfmeObjEBJ only ever receives the INI* receiver of INI::initFromINI, so the
// call below goes through the real header rather than a stand-in member whose
// name nothing defines.
#include "Common/INI/INI.h"

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
	void bfmeCallEBL(void *a, void *b);
	void *m_bfmeA;
	void *m_bfmeB;
};

extern BfmeObjEBL g_bfmeObjEBL;

void bfmeGoEBL()
{
	g_bfmeObjEBL.bfmeCallEBL(g_bfmeObjEBL.m_bfmeA, g_bfmeObjEBL.m_bfmeB);
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

// The global(s) below are defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
#pragma comment(linker, "/alternatename:?g_bfmeObjEBL@@3VBfmeObjEBL@@A=?g_validityBegin@@3PAEA")
