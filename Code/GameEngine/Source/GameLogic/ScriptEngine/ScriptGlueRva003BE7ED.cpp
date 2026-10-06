// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /EHsc /MD /DNDEBUG
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

class CreateAHeroManager
{
public:
	void rva0021A4E6();
};
extern CreateAHeroManager *TheCreateAHeroManager;

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

extern AsciiString g_00DE0878;

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
					g_00E03138->slot23(s2, p ? p->m_1bc : (unsigned char)0, s1, g_00DE0878);
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
