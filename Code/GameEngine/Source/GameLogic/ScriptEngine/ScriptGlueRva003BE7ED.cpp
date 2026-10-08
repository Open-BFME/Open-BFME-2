// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /EHsc /MD /DNDEBUG
// stlport
//
// ?rva003BE7ED@Rva003BE7ED@@QAEXXZ @0x003BE7ED 239B (dump range 18).
// Defeat-screen emit, mirror of the landed 0x003BE5C9 victory-screen emit:
// enables through the rowed ScriptEngine byte setter 0x00203BE1, clears its
// +0x0C flag, runs the rowed GameLogic 0x00376D49 member, gates on the flag,
// the 0x00E03138 global, its slot 0x54 (proceed when false) and the local
// player, builds two AsciiStrings on the stack (rowed StringBase char* ctor
// 0x0037BA0, releaseBuffer 0x00036410 cleanup), picks the evil byte from the
// player's +0x34/+0x1BC exactly like 0x003BE5C9, fires the global's slot
// 0x17 with (defeat string, evil, screen string, static string), then runs
// the rowed 0x0021A4E6 member on the 0x00DFE344 global, clears the
// 0x00E02D6C +0x2D byte, conditionally runs the rowed 0x001EB0CA member on
// the 0x00DFDC8C global, and applies through the rowed ScriptEngine copier
// 0x002036C0. Class layout twins Rva003BE5C9 (+0x0C flag); same-class
// unproven so kept distinct. Cross-class rowed callees are called through
// their rowed views (zero-byte casts).
#include "ascii_string.h"
#include <algorithm>

class GameLogic
{
public:
	void rva00376D49();
};
extern GameLogic *TheGameLogic;

class Rva00203BE1ByteOneSetter
{
public:
	void enable();
};

class Rva002036C0GlobalCopier
{
public:
	void apply();
};

class ScriptEngine;
extern ScriptEngine *TheScriptEngine;

struct Rva003BE5C9P34
{
	unsigned char m_pad[0x1BC];
	unsigned char m_1bc;
};

class Player
{
public:
	char m_pad[0x34];
	Rva003BE5C9P34 *m_p34; // +0x34
};

class PlayerList
{
public:
	char m_pad00[0x10];
	Player *m_localPlayer; // +0x10
};
extern PlayerList *ThePlayerList;

class Rva00E03138
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s0a(); virtual void s0b();
	virtual void s0c(); virtual void s0d(); virtual void s0e(); virtual void s0f();
	virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13();
	virtual void s14();
	virtual bool rva0054();
	virtual void s16();
	virtual void slot23(const AsciiString &a, unsigned char b, const AsciiString &c, const AsciiString &d);
};
extern Rva00E03138 *g_00E03138;

class CreateAHeroData;

// Both range-7 bodies use the registry at VA 0x00DFE358 through the already
// matched _STL::find specialization at 0x0020E873. Their direct callees and
// member offsets are target evidence; the CreateAHeroData* spelling is only
// the existing registry specialization's ABI view of the value at +0x1E0.
extern unsigned int g_00DFE358;

class Rva0021937DTarget
{
public:
	void rva004089C7(int, int);
	void rva004074CF();
};

class CreateAHeroManager
{
public:
	void rva0021A4E6();
	int rva002192C0();
	char m_pad000[0x1A4];
	unsigned int m_1A4;
	unsigned int m_1A8;
	unsigned int m_1AC;
	unsigned int m_1B0;
	char m_pad1B4[0x2C];
	CreateAHeroData *m_1E0;
};
extern CreateAHeroManager *TheCreateAHeroManager;

class Rva0021A54A : public CreateAHeroManager
{
public:
	void rva0021A54A();
};

struct Rva00E02D6CDefeatView
{
	unsigned char m_pad[0x2D];
	unsigned char m_flag2D;
};
extern Rva00E02D6CDefeatView *g_00E02D6C;

class Rva001EB0CAHolder
{
public:
	void rva001EB0CA();
};
extern Rva001EB0CAHolder *g_00DFDC8C;


class Rva003BE7ED
{
public:
	void rva003BE7ED();
private:
	char m_pad[0x0C];
	unsigned char m_flagC; // +0x0C
};

void Rva003BE7ED::rva003BE7ED()
{
	((Rva00203BE1ByteOneSetter *)TheScriptEngine)->enable();
	m_flagC = false;
	TheGameLogic->rva00376D49();
	if (m_flagC == 0) {
		if (g_00E03138 != 0) {
			if (!g_00E03138->rva0054()) {
				Player *player = ThePlayerList->m_localPlayer;
				if (player != 0) {
					AsciiString s1("Gui_DefeatScreen");
					AsciiString s2("APT:EndDefeat");
					Rva003BE5C9P34 *p = player->m_p34;
					g_00E03138->slot23(s2, p ? p->m_1bc : (unsigned char)0, s1, AsciiString::TheEmptyString);
				}
			}
		}
	}
	TheCreateAHeroManager->rva0021A4E6();
	g_00E02D6C->m_flag2D = false;
	if (g_00DFDC8C != 0)
		g_00DFDC8C->rva001EB0CA();
	((Rva002036C0GlobalCopier *)TheScriptEngine)->apply();
}

// ?rva0021A4E6@CreateAHeroManager@@QAEXXZ @ 0x0021A4E6 100B. Direct
// registry membership check, state helper 0x002192C0, calls through the
// target's +0x1E0 member, and clears that member; the owner/type names for the
// two direct helper views remain address-derived where their ledger pins say so.
void CreateAHeroManager::rva0021A4E6()
{
	CreateAHeroData **slot = &m_1E0;
	CreateAHeroData *hero = *slot;
	CreateAHeroManager *manager = this;
	if (hero != 0) {
		CreateAHeroData **end = (CreateAHeroData **)*(unsigned int *)((char *)&g_00DFE358 + 4);
		if (_STL::find((CreateAHeroData **)g_00DFE358, end, *slot) != end) {
			int state = manager->rva002192C0();
			if (state != 0) {
				if (state != 3)
					goto clear;
				((Rva0021937DTarget *)hero)->rva004089C7(manager->m_1A4, 1);
			} else {
				((Rva0021937DTarget *)hero)->rva004089C7(manager->m_1AC, 1);
			}
			((Rva0021937DTarget *)*slot)->rva004074CF();
		}
	clear:
		*slot = 0;
	}
}

// ?rva0021A54A@Rva0021A54A@@QAEXXZ @ 0x0021A54A 100B. Same call and
// registry pattern as 0x0021A4E6, with its target fields at +0x1A8/+0x1B0.
void Rva0021A54A::rva0021A54A()
{
	CreateAHeroData **slot = &m_1E0;
	CreateAHeroData *hero = *slot;
	CreateAHeroManager *manager = this;
	if (hero != 0) {
		CreateAHeroData **end = (CreateAHeroData **)*(unsigned int *)((char *)&g_00DFE358 + 4);
		if (_STL::find((CreateAHeroData **)g_00DFE358, end, *slot) != end) {
			int state = manager->rva002192C0();
			if (state != 0) {
				if (state != 3)
					goto clear;
				((Rva0021937DTarget *)hero)->rva004089C7(manager->m_1A8, 1);
			} else {
				((Rva0021937DTarget *)hero)->rva004089C7(manager->m_1B0, 1);
			}
			((Rva0021937DTarget *)*slot)->rva004074CF();
		}
	clear:
		*slot = 0;
	}
}
