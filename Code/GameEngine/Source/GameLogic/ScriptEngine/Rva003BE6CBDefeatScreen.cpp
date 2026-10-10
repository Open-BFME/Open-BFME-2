// cl: /I. /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /G7 /EHsc /MD /DNDEBUG /arch:SSE
//
// ?rva003BE6CB@Rva003BE6CB@@QAEXXZ @0x003BE6CB 290B (dump range 18).
// Defeat-screen emit with an EH frame: clears its +0x0C byte, runs the
// pinned GameLogic 0x00376D49 member and the rowed 0x001EB0CA holder member
// when set, runs the pinned 0x003BBAD3 member, skips the screen when the flag
// is set or when the pointer global or the local player is null, else builds two
// AsciiStrings on the stack (rowed StringBase ctor 0x0037BA0,
// releaseBuffer 0x00036410 cleanup), gates the second on rowed uchar
// 0x003BA8F3, fires the pointer global's slot 0x17 with (second, evil
// byte, first, AsciiString::TheEmptyString), optionally fires slot 0x1B
// when rowed GameLogic_bool 0x00200084 agrees, clears the campaign flag,
// re-runs the holder member, and finishes through the rowed 0x002036B4
// apply and the pinned 0x0021A4E6 member. The clearing of the campaign flag and
// everything after it runs on every path (the bank's early returns were
// branches to that tail).
#include "ascii_string.h"

#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

class Rva0023C6A4
{
public:
	bool rva00200084();
};

class Rva003BBAD3
{
public:
	void rva003BBAD3();
};

class Rva001EB0CAHolder
{
public:
	void rva001EB0CA();
};
extern Rva001EB0CAHolder *TheVisualHolder;

class Player;
struct Rva003BE6CBP34
{
	unsigned char m_pad[0x1BC];
	unsigned char m_1bc;
};
class Player
{
public:
	char m_pad[0x34];
	Rva003BE6CBP34 *m_p34; // +0x34
};
class PlayerList
{
public:
	char m_pad00[0x10];
	Player *m_localPlayer; // +0x10
};
extern PlayerList *ThePlayerList;

unsigned char Rva003BA8F3Get();

class Rva00E03138
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void s16();
	virtual void s17();
	virtual void s18();
	virtual void s19();
	virtual void s20();
	virtual void s21();
	virtual void s22();
	virtual void slot23(const AsciiString &a, unsigned char b, const AsciiString &c, const AsciiString &d);
	virtual void s24();
	virtual void s25();
	virtual void s26();
	virtual void slot27(int v);
};
extern Rva00E03138 *g_00E03138;

class Rva002036B4GlobalCopier
{
public:
	void apply();
};
class ScriptEngine;
extern ScriptEngine *TheScriptEngine;	// the global at 0x00DFE16C; 0x002036B4 is one of its members

class Rva0021A4E6
{
public:
	void rva0021A4E6();
};
extern Rva0021A4E6 *TheHeroManager;

class Rva00E02D6C
{
public:
	char m_pad[0x2D];
	bool m_flag2D;
};
extern Rva00E02D6C *TheCampaignManager;

class Rva003BE6CB
{
public:
	void rva003BE6CB();
private:
	char m_pad[0x0C];
	unsigned char m_flagC;
};

void Rva003BE6CB::rva003BE6CB()
{
	m_flagC = 0;
	TheGameLogic->rva00376D49();
	if (TheVisualHolder != 0)
		TheVisualHolder->rva001EB0CA();
	((Rva003BBAD3 *)this)->rva003BBAD3();
	if (m_flagC == 0) {
		Player *pl = ThePlayerList->m_localPlayer;
		if (g_00E03138 != 0 && pl != 0) {
			{
				AsciiString s1("Gui_DefeatScreen");
				AsciiString s2(Rva003BA8F3Get() ? "APT:EndGameOver" : "APT:EndDefeat");
				Rva003BE6CBP34 *p = pl->m_p34;
				g_00E03138->slot23(s2, p ? p->m_1bc : (unsigned char)0, s1, AsciiString::TheEmptyString);
			}
			if (((Rva0023C6A4 *)TheGameLogic)->rva00200084())
				g_00E03138->slot27(1);
		}
	}
	TheCampaignManager->m_flag2D = false;
	if (TheVisualHolder != 0)
		TheVisualHolder->rva001EB0CA();
	((Rva002036B4GlobalCopier *)TheScriptEngine)->apply();
	TheHeroManager->rva0021A4E6();
}
