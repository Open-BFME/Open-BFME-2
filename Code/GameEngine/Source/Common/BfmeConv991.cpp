// cl: /O1
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

class BfmeA991
{
public:
	virtual void bfmeVA0991();
	virtual void bfmeVA1991();
	virtual void bfmeVA2991();
	virtual void bfmeVA3991();
	virtual void bfmeVA4991();
	virtual void bfmeStop991A();

	void bfmeGo991A();

	char m_bfmePad[0x1c0];
	char m_bfmeOn;
};


class BfmeB991
{
public:
	virtual void bfmeVB0991();
	virtual void bfmeVB1991();
	virtual void bfmeTick991();

	void bfmeSet991(int a);

	char m_bfmePad[0x1c];
	int m_bfmeSlot;
};

extern BfmeB991 *g_bfmeB991;
extern int g_bfmeVal991;

void bfmeGo991B(int a)
{
	if (!g_bfmeB991)
		return;

	g_bfmeB991->bfmeSet991(a);
	g_bfmeB991->bfmeTick991();
	g_bfmeB991->m_bfmeSlot = g_bfmeVal991;
}

class BfmeDev991
{
public:
	virtual void bfmeVD0991();
	virtual void bfmeVD1991();
	virtual void bfmeVD2991();
	virtual void bfmeVD3991();
	virtual void bfmeVD4991();
	virtual void bfmeReset991(int a, int b);
};

class BfmeC991
{
public:
	char bfmeGo991C(int a, int b);
	char bfmeSend991(int a, int b);

	char m_bfmePad[4];
	BfmeDev991 *m_bfmeDev;
	int m_bfmeKind;
};

