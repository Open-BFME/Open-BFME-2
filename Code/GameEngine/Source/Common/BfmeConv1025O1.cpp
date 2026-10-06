// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Bodies ported from Open-BFME-1's GameEngine/Source/Common/BfmeConv1025.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus
// /O1). Compiled that way each body below places uniquely on unclaimed
// game.dat .text by masked whole-.text search, and ./build.sh reproduces it
// byte for byte: bfmeGo1025G 0x00512838 (44B). Callee addresses are read off
// retail's call sites (reverse/symbols.csv). Only the placed bodies are
// carried; the donor's other definitions are omitted.
// Open-BFME5 conversions.

class BfmeB1025
{
public:
	virtual void bfmeVB01025();
	virtual void bfmeVB11025();
	virtual void bfmeVB21025();
	virtual void bfmeVB31025();
	virtual void bfmeVB41025();
	virtual void bfmeVB51025();
	virtual void bfmeVB61025();
	virtual void bfmeVB71025();
	virtual void bfmeVB81025();
	virtual void bfmeVB91025();
	virtual void bfmeVB101025();
	virtual void bfmeVB111025();
	virtual void bfmeVB121025();
	virtual void bfmeVB131025();
	virtual void bfmeVB141025();
	virtual void bfmeVB151025();
	virtual void bfmeVB161025();
	virtual void bfmeVB171025();
	virtual void bfmeVB181025();
	virtual void bfmeVB191025();
	virtual void bfmeVB201025();
	virtual void bfmeVB211025();
	virtual void bfmeVB221025();
	virtual void bfmeVB231025();
	virtual void bfmeVB241025();
	virtual void bfmeVB251025();
	virtual void bfmeVB261025();
	virtual void bfmeVB271025();
	virtual void bfmeVB281025();
	virtual void bfmeVB291025();
	virtual void bfmeVB301025();
	virtual void bfmeVB311025();
	virtual void bfmeVB321025();
	virtual void bfmeVB331025();
	virtual void bfmeVB341025();
	virtual void bfmeVB351025();
	virtual void bfmeVB361025();
	virtual void bfmeVB371025();
	virtual void bfmeVB381025();
	virtual void bfmeVB391025();
	virtual void bfmeVB401025();
	virtual void bfmeVB411025();
	virtual void bfmeVB421025();
	virtual void bfmeVB431025();
	virtual void bfmeVB441025();
	virtual void bfmeVB451025();
	virtual void bfmeVB461025();
	virtual void bfmeVB471025();
	virtual void bfmeVB481025();
	virtual void bfmeVB491025();
	virtual void bfmeVB501025();
	virtual void bfmeVB511025();
	virtual void bfmeVB521025();
	virtual void bfmeVB531025();
	virtual void bfmeVB541025();
	virtual void bfmeVB551025();
	virtual void bfmeVB561025();
	virtual void bfmeVB571025();
	virtual void bfmeFree1025(int h);
};

extern BfmeB1025 *g_bfmeB1025;

class BfmeA1025
{
public:
	void bfmeGo1025A(void);

	char m_bfmePad[0x54];
	int m_bfmeH;
};


struct BfmeK1025
{
	char m_bfmePad[0x24];
	int m_bfmeKey;
};

class BfmeD1025
{
public:
	unsigned short bfmeLookup1025(int k, int a, int b);
};

extern BfmeD1025 *g_bfmeD1025;

class BfmeC1025
{
public:
	int bfmeGo1025C(void);

	char m_bfmePad[0xc];
	void *m_bfmeA;
	BfmeK1025 *m_bfmeB;
};


class BfmeP1025
{
public:
	char bfmeSay1025(char *t);
};

extern BfmeP1025 *g_bfmeP1025;
extern char g_bfmeLit1025[];

struct BfmeR1025
{
	char *m_bfmeName;
};


extern "C" void _WriteBarrier();

template <typename T>
class StringBase
{
public:
	StringBase(const StringBase<T> &other);
	~StringBase() { releaseBuffer(); }

	void *m_bfmeBuffer;

private:
	void releaseBuffer();
};

typedef StringBase<unsigned short> BfmeString1025;

struct BfmeEntry1025
{
	BfmeEntry1025(const BfmeEntry1025 &other) : m_text(other.m_text)
	{
		m_count = other.m_count;
		_WriteBarrier();
		m_other = other.m_other;
	}

	BfmeString1025 m_text;
	int m_count;
	int m_other;
};

struct BfmeNode1025
{
	BfmeNode1025 *m_next;
	BfmeNode1025 *m_previous;
	BfmeEntry1025 m_entry;
};

class BfmeH1025
{
public:
	int bfmeVal1025(void);

	char m_bfmeBeforeList[0xc0];
	BfmeNode1025 *m_list;
};


// The canonical global at 0x012F1028 (EA's "TheLivingWorldLogic", defined in
// game/GameEngine/Source/GameLogic/LivingWorld/LivingWorldLogic.cpp). This TU
// views it through the local BfmeH1025 struct above.
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

extern char g_bfmeFmt1025[];
extern "C" __declspec(dllimport) void __cdecl sprintf(int a, char *f, int b);

void __stdcall bfmeGo1025G(int unused, int b, char skip)
{
	if (skip != 0)
		return;

	if (TheLivingWorldLogic == 0)
		return;

	sprintf(b, g_bfmeFmt1025,
		((BfmeH1025 *)TheLivingWorldLogic)->bfmeVal1025());
}

