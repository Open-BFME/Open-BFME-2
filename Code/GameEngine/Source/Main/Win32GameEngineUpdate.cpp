// cl: /O1 /DNDEBUG /MD /EHsc
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
typedef void *HWND;

extern "C" {
__declspec(dllimport) int __stdcall IsIconic(HWND hWnd);
__declspec(dllimport) void __stdcall Sleep(unsigned long ms);
}

#define BFME_VSLOT(n) virtual void slot##n();

class GameEngine
{
public:
	BFME_VSLOT(0) BFME_VSLOT(1) BFME_VSLOT(2) BFME_VSLOT(3) BFME_VSLOT(4)
	BFME_VSLOT(5) BFME_VSLOT(6) BFME_VSLOT(7) BFME_VSLOT(8) BFME_VSLOT(9)
	virtual void update();						///< pinned 0x00225DA9
	BFME_VSLOT(11) BFME_VSLOT(12) BFME_VSLOT(13) BFME_VSLOT(14) BFME_VSLOT(15)
	BFME_VSLOT(16) BFME_VSLOT(17) BFME_VSLOT(18) BFME_VSLOT(19) BFME_VSLOT(20)
	virtual Bool getQuitting();
	BFME_VSLOT(22)
	virtual void serviceWindowsOS();
	virtual Bool isActive();
};

class Win32GameEngine : public GameEngine
{
public:
	virtual void update();
};

class LANAPI
{
public:
	BFME_VSLOT(0) BFME_VSLOT(1) BFME_VSLOT(2) BFME_VSLOT(3) BFME_VSLOT(4)
	BFME_VSLOT(5) BFME_VSLOT(6) BFME_VSLOT(7) BFME_VSLOT(8) BFME_VSLOT(9)
	virtual void update();
	BFME_VSLOT(11) BFME_VSLOT(12) BFME_VSLOT(13)
	virtual void setIsActive(Bool isActive);
};

#undef BFME_VSLOT

enum GameMode
{
	GAME_LAN = 1,
	GAME_INTERNET = 5
};

class GameLogic
{
public:
	Bool isInLanGame() const { return m_gameMode == GAME_LAN; }
	Bool isInInternetGame() const { return m_gameMode == GAME_INTERNET; }

private:
	char m_unmodelled_00[0x110];
	int m_gameMode;								// +0x110
};

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

			if (TheGameEngine->getQuitting() || TheGameLogic->isInInternetGame() || TheGameLogic->isInLanGame())
				break;
		}
	}

	serviceWindowsOS();
}
