// cl: /DNDEBUG /MD
// platformsdk
//
// Bodies ported from Open-BFME-1's GameEngine/Source/Common/BfmeConv1038.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus
// /O1). Compiled that way each body below places uniquely on unclaimed
// game.dat .text by masked whole-.text search, and ./build.sh reproduces it
// byte for byte: 0x0040D025 (28B, first ported as bfmeGo1038E). Callee addresses are read off
// retail's call sites (reverse/symbols.csv). Only the placed bodies are
// carried; the donor's other definitions are omitted.
// Open-BFME5 conversions.

#include <windows.h>

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
struct Rva008BD5B0Key
{
	int unused;
	int value;
};

struct Rva008BD5B0Item
{
	char pad[0x50];
	Rva008BD5B0Key *key;
};

class Rva008BD5B0
{
public:
	void insert(Rva008BD5B0Item *item);

	Rva008BD5B0Item *items[32];
	int count;
};

class BfmeB1038
{
public:
	void bfmeDone1038(void);
};

class BfmeA1038
{
public:
	virtual void bfmeVA01038();
	virtual void bfmeVA11038();
	virtual void bfmeVA21038();
	virtual void bfmeVA31038();
	virtual void bfmeVA41038();
	virtual void bfmeVA51038();
	virtual void bfmeVA61038();
	virtual void bfmeVA71038();
	virtual void bfmeVA81038();
	virtual void bfmeVA91038();
	virtual void bfmeVA101038();
	virtual void bfmeVA111038();
	virtual void bfmeVA121038();
	virtual void bfmeVA131038();
	virtual void bfmeVA141038();
	virtual void bfmeVA151038();
	virtual void bfmeVA161038();
	virtual void bfmeVA171038();
	virtual void bfmeVA181038();
	virtual void bfmeVA191038();
	virtual void bfmeVA201038();
	virtual void bfmeVA211038();
	virtual void bfmeVA221038();
	virtual void bfmeVA231038();
	virtual void bfmeVA241038();
	virtual void bfmeVA251038();
	virtual void bfmeVA261038();
	virtual void bfmeVA271038();
	virtual void bfmeVA281038();
	virtual void bfmeVA291038();
	virtual void bfmeVA301038();
	virtual void bfmeVA311038();
	virtual void bfmeVA321038();
	virtual void bfmeVA331038();
	virtual void bfmeVA341038();
	virtual void bfmeVA351038();
	virtual void bfmeVA361038();
	virtual void bfmeVA371038();
	virtual void bfmeVA381038();
	virtual void bfmeVA391038();
	virtual void bfmeVA401038();
	virtual void bfmeVA411038();
	virtual void bfmeVA421038();
	virtual void bfmeVA431038();
	virtual void bfmeVA441038();
	virtual void bfmeVA451038();
	virtual void bfmeVA461038();
	virtual void bfmeVA471038();
	virtual void bfmeVA481038();
	virtual char bfmeAsk1038();
	void bfmeGo1038A(void);
	void bfmeStep1038(void);
};

struct Rva007EB810Diag
{
	virtual void v0();
	virtual void report(const char *message);
};

Rva007EB810Diag *Rva007EB810Get(void);
extern char g_bfmeMsg1038[];

class BfmeD1038
{
public:
	void bfmeGo1038D(void);

	char m_bfmePad[4];
	void *m_bfmeHandle;
};

class BfmeY1038
{
public:
	int bfmeVal1038(void);
};

// 0x0040D008..0x0040D3FF are ArmySummarySystem members: retail reaches each
// through a GameLogic forwarder that adds 0x184 to ECX (0x0023D012..0x0023D0C8),
// and WorldBuilder's twins of 0x0040FAFE/0x0040D3E8 call the lookup's twin
// 0x0108E170 as __thiscall on their own this.
class ArmySummarySystem
{
public:
	void *rva0040D008(int id);
	int rva0040D025(int id);
};

struct Rva002B488EResult
{
	char m_pad[0x78];
	BfmeY1038 *m_78;
};

class Rva002BA8F1Logic
{
public:
	Rva002B488EResult *rva002B488E(int a);
};

// ?rva0040D008@ArmySummarySystem@@QAEPAXH@Z @0x0040D008 29B: the army lookup
// by id (WorldBuilder twin 0x0108E170 calls LivingWorldLogic::findArmy and
// returns its +0x78 summary or null). Never reads this.
void *ArmySummarySystem::rva0040D008(int id)
{
	Rva002B488EResult *army = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->rva002B488E(id);
	return army != 0 ? army->m_78 : 0;
}

int ArmySummarySystem::rva0040D025(int id)
{
	BfmeY1038 *summary = (BfmeY1038 *)rva0040D008(id);

	if (summary == 0)
		return -1;

	return summary->bfmeVal1038();
}

class BfmeSubF1038
{
public:
	void bfmeAdd1038(int a, int b);
};

class BfmeAObj1038
{
public:
	void bfmeStop1038F(void);

	char m_bfmePad[0x122c];
	BfmeSubF1038 m_bfmeSub;
};

extern BfmeAObj1038 *g_bfmeA1038;
extern int g_bfmeB1038;
extern int g_bfmeC1038;
void bfmeFlush1038(void);

class BfmeI1038
{
public:
	void bfmeGo1038I(void);

	char m_bfmePad[0x508];
	void (__cdecl *m_bfmeFn)(int);
	char m_bfmeFlag;
};
