// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /EHsc /MD /DNDEBUG
//
// ?rva003BE5C9@Rva003BE5C9@@QAEXXZ @0x003BE5C9 258B (dump range 18).
// Victory-screen emit with an EH frame: clears its +0x0C byte, runs the
// pinned GameLogic 0x00376D49 member and the pinned 0x003BBAD3 member,
// bails when the flag is set or when the pointer global or the local
// player is null, picks the cheer string from the +0x34/+0x1BC evil byte,
// builds three AsciiStrings on the stack (rowed StringBase ctor 0x0037BA0,
// releaseBuffer 0x00036410 cleanup), gates the GameOver/Victorious string
// on rowed 0x003BA8F3, and fires the pointer global's slot 0x17 with the
// three strings plus the evil byte.
#include "ascii_string.h"

class GameLogic
{
public:
	void rva00376D49();
};
extern GameLogic *TheGameLogic;

class Rva003BBAD3
{
public:
	void rva003BBAD3();
};

class Player;
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
};
extern Rva00E03138 *g_00E03138;

class Rva003BE5C9
{
public:
	void rva003BE5C9();
private:
	char m_pad[0x0C];
	unsigned char m_flagC;
};

void Rva003BE5C9::rva003BE5C9()
{
	m_flagC = 0;
	TheGameLogic->rva00376D49();
	((Rva003BBAD3 *)this)->rva003BBAD3();
	if (m_flagC != 0)
		return;
	Player *pl = ThePlayerList->m_localPlayer;
	if (g_00E03138 == 0 || pl == 0)
		return;
	Rva003BE5C9P34 *p = pl->m_p34;
	unsigned char c1 = p ? p->m_1bc : 0;
	AsciiString s1(c1 ? "Gui_VictoryCheerEvil" : "Gui_VictoryCheerGood");
	AsciiString s2("Gui_VictoryScreen");
	AsciiString s3(Rva003BA8F3Get() ? "APT:EndGameOver" : "APT:EndVictorious");
	Rva003BE5C9P34 *p2 = pl->m_p34;
	g_00E03138->slot23(s3, p2 ? p2->m_1bc : (unsigned char)0, s2, s1);
}
