// cl: /DNDEBUG /MD /EHsc
//
// Win32GameEngine::update, retail 0x00041EC3 (166B), slot 10 of vtable
// 0x00BC2530 (GameEngine's own table 0x00BE7188 has GameEngine::update,
// 0x00225DA9, in slot 10, which this body calls first). Zero Hour's
// Win32GameEngine::update (GameEngineDevice/Source/Win32Device/Common/
// Win32GameEngine.cpp) less its TheAudio volume nudge, which BFME2 drops; the
// same body as Open-BFME-1's Win32GameEngine_update.cpp donor (revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, built /O2 there). Slots read off
// the calls: getQuitting +0x54 (21), serviceWindowsOS +0x5C (23, matched
// 0x00042121), isActive +0x60 (24); LANAPI update +0x28 (10) and setIsActive
// +0x38 (14). Game modes 5 and 1 are Zero Hour's GAME_INTERNET and GAME_LAN
// (isInInternetGame, isInLanGame), read at GameLogic+0x110.

typedef bool Bool;

// platformsdk
#define NO_STRICT // Match WinMain.cpp's HWND type for ApplicationHWnd.
#include <windows.h>
#undef near
#undef far

#define BFME_VSLOT(n) virtual void slot##n();

#include "../../Include/Common/GameEngine.h"

class Win32GameEngine : public GameEngine
{
public:
	virtual void reset();
	virtual void update();
};

#include "../../Include/GameNetwork/LANAPI.h"

#undef BFME_VSLOT

enum GameMode
{
	GAME_LAN = 1,
	GAME_INTERNET = 5
};

#include "../Common/GameLogicObjectLookupView.h"

extern HWND ApplicationHWnd;
extern LANAPI *TheLAN;
extern GameEngine *TheGameEngine;
extern GameLogic *TheGameLogic;

void Win32GameEngine::update()
{
	GameEngine::update();

	if (ApplicationHWnd && ::IsIconic(ApplicationHWnd))
	{
		while (ApplicationHWnd && ::IsIconic(ApplicationHWnd))
		{
			::Sleep(5);
			serviceWindowsOS();

			if (TheLAN != 0)
			{
				TheLAN->setIsActive(isActive());
				TheLAN->update();
			}

			if (TheGameEngine->getQuitting() || (TheGameLogic->m_110 == GAME_INTERNET) || (TheGameLogic->m_110 == GAME_LAN))
				break;
		}
	}

	serviceWindowsOS();
}

// ?reset@Win32GameEngine@@UAEXXZ @0x00041EBE 5B: slot 9 of vtable
// 0x00BC2530, right before update above. Zero Hour's Win32GameEngine::reset
// only extends GameEngine::reset: a tail jump to the rowed 0x00229708.
void Win32GameEngine::reset()
{
	GameEngine::reset();
}
