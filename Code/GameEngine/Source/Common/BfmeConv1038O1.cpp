// cl: /DNDEBUG /MD
//
// Bodies ported from Open-BFME-1's GameEngine/Source/Common/BfmeConv1038.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus
// /O1). Compiled that way each body below places uniquely on unclaimed
// game.dat .text by masked whole-.text search, and ./build.sh reproduces it
// byte for byte: bfmeGo1038E 0x0040D025 (28B). Callee addresses are read off
// retail's call sites (reverse/symbols.csv). Only the placed bodies are
// carried; the donor's other definitions are omitted.
// Open-BFME5 conversions.

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

extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *h);
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

BfmeY1038 * __stdcall bfmeFind1038(int a);

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

// ?bfmeFind1038@@YGPAVBfmeY1038@@H@Z @0x0040D008 29B: forward int arg to rowed-adjacent Rva002BA8F1Logic::rva002B488E via g_009FEF10 then return +0x78 slot or null. Evidence: LINK BONUS 2 files 81B; pin name; callers at 0x0040D029 and 0x0040D280 set.
BfmeY1038 * __stdcall bfmeFind1038(int a)
{
	Rva002B488EResult *r = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->rva002B488E(a);
	return r != 0 ? r->m_78 : 0;
}

int __stdcall bfmeGo1038E(int a)
{
	BfmeY1038 *y = bfmeFind1038(a);

	if (y == 0)
		return -1;

	return y->bfmeVal1038();
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

