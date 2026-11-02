// ?InitGadgets@AptOnlineCustomMatch@@QAEXPBDHPAVGameWindow@@@Z
// partial score=0.99 date=2026-10-05
// cl: /Ireference/shims/bfmelist /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva005A083C@AptOnlineCustomMatch@@QAEXXZ, retail 0x005A083C 140B. Unlock: builds 2-int list from +0x498/+0x49C when both non-null then WindowManager 0xB4/0xB0.
// Evidence: callees list base/push_front/push_back/dup/dtor rowed in stlport_list_int_o1; TheWindowManager global; caller 0x005A0D56.
#include <list>

#include "../../Include/GameClient/GameWindowManager.h"
extern GameWindowManager *TheWindowManager;

class GameWindow;
class WinInstanceData;
class BfmeKeyLC;
typedef void (__cdecl *GameWinTooltipFunc)(GameWindow *window, WinInstanceData *data, unsigned int flags);
void __cdecl GadgetListBoxReset(GameWindow *window);
void __cdecl GadgetTextEntrySetValidationFlags(GameWindow *window, int value);
void __cdecl GadgetTextEntrySetMaxChars(BfmeKeyLC *k, unsigned short w);
#include <string.h>

#include "../../Include/GameClient/Bfme2GameWindow.h"

struct Rva005A0C6EUserData
{
	char m_pad[0x12];
	unsigned char m_12;
};

class AptOnlineCustomMatch
{
public:
	void rva005A083C();
	void InitGadgets(const char *name, int a2, GameWindow *a3);
	// Rowed 0x005A08C8 in AptOnlineCustomMatch.cpp.
	static void GamesListTooltipFunc(GameWindow *window, WinInstanceData *data, unsigned int flags);
private:
	char m_pad[0x48C];
	GameWindow *m_48C;
	GameWindow *m_490;
	GameWindow *m_494;
	int m_498;
	int m_49C;
};




void AptOnlineCustomMatch::InitGadgets(const char *name, int a2, GameWindow *gameWindow)
{
	if (gameWindow == 0)
		return;
	if (strcmp(name, "GameList") == 0) {
		GadgetListBoxReset(gameWindow);
		m_48C = gameWindow;
		Rva005A0C6EUserData *ud = (Rva005A0C6EUserData *)gameWindow->winGetUserData();
		ud->m_12 = 1;
		gameWindow->winSetUserData(ud);
		gameWindow->winSetTooltipFunc(GamesListTooltipFunc);
		return;
	}
	if (strcmp(name, "Lobbies") == 0) {
		m_490 = gameWindow;
		return;
	}
	if (strcmp(name, "GameInfo") == 0) {
		GadgetListBoxReset(gameWindow);
		m_494 = gameWindow;
		return;
	}
	if (strcmp(name, "GameName") == 0) {
		m_498 = (int)gameWindow;
		GadgetTextEntrySetMaxChars((BfmeKeyLC *)gameWindow, 0x14);
		gameWindow->winSetStatus(2);
		rva005A083C();
	} else {
		if (strcmp(name, "GamePassword") != 0)
			return;
		m_49C = (int)gameWindow;
		GadgetTextEntrySetValidationFlags(gameWindow, 5);
		GadgetTextEntrySetMaxChars((BfmeKeyLC *)gameWindow, 0x14);
		gameWindow->winSetStatus(2);
		rva005A083C();
	}
}
