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

#include "../../../Include/Common/Rva0023C6A4.h"

#include "../../../Include/Common/Rva003BBAD3.h"

#include "../../../Include/GameClient/Rva001EB0CAHolder.h"
// The holder is the global at 0x00DFDC8C, TheLinearCampaignManager.
class LinearCampaignManager;
extern LinearCampaignManager *TheLinearCampaignManager;

class Player;
#include "../../../Include/Common/PlayerTemplate.h"
#include "../../../Include/Common/Player.h"
#include "../../../Include/Common/PlayerList.h"
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
class VictoryConditionsInterface; extern VictoryConditionsInterface *TheVictoryConditions;

#include "../../../Include/GameLogic/Rva002036B4GlobalCopier.h"
class ScriptEngine;
extern ScriptEngine *TheScriptEngine;	// the global at 0x00DFE16C; 0x002036B4 is one of its members

// The global at 0x00DFE344; 0x0021A4E6 is rowed as its member.
#include "../../../Include/GameLogic/CreateAHeroManager.h"
extern CreateAHeroManager *TheCreateAHeroManager;

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
	if (TheLinearCampaignManager != 0)
		((Rva001EB0CAHolder *)TheLinearCampaignManager)->rva001EB0CA();
	((Rva003BBAD3 *)this)->rva003BBAD3();
	if (m_flagC == 0) {
		Player *pl = ThePlayerList->m_local;
		if (TheVictoryConditions != 0 && pl != 0) {
			{
				AsciiString s1("Gui_DefeatScreen");
				AsciiString s2(Rva003BA8F3Get() ? "APT:EndGameOver" : "APT:EndDefeat");
				const PlayerTemplate *p = pl->m_playerTemplate;
				((Rva00E03138 *)TheVictoryConditions)->slot23(s2, p ? p->m_isEvil : false, s1, AsciiString::TheEmptyString);
			}
			if (((Rva0023C6A4 *)TheGameLogic)->rva00200084())
				((Rva00E03138 *)TheVictoryConditions)->slot27(1);
		}
	}
	TheCampaignManager->m_flag2D = false;
	if (TheLinearCampaignManager != 0)
		((Rva001EB0CAHolder *)TheLinearCampaignManager)->rva001EB0CA();
	((Rva002036B4GlobalCopier *)TheScriptEngine)->apply();
	TheCreateAHeroManager->rva0021A4E6();
}
