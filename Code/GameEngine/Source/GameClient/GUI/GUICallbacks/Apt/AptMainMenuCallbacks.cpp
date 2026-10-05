// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD
//
// BFME2's main menu screen Apt callbacks, 0x00514A9B onward. The screen's
// registration binds each by the name it carries here ("AptMainMenu::
// LoadGame" ...) as a member pointer, which is the only reference to them,
// so the names are the binding strings' and the class is named for their
// prefix (BFME1 calls the screen BfmeAptScreenMainMenu). Most of them
// leave the menu: state +0x288 becomes 9 and +0x28C names the screen to
// open next.

extern "C" int __cdecl strcmp(const char *left, const char *right);

#include "unicode_string.h"

// TheGameState (VA 0x00DFF08C); its rowed 0x002DCCFB tells whether a save
// file exists (Rva002DC267Get.cpp's view).
class GameState;
extern GameState *TheGameState;

class Rva002DCCFB
{
public:
	bool rva002DCCFB(UnicodeString filename);
};

#include "ascii_string.h"

// The script event the exit button fires (a .data pointer to
// "ShellMainMenuExitPushed").
extern const char *g_009C108C;

class ScriptEngine
{
public:
	// Rowed 0x00357DD2 (fires a named script event).
	void rva00357DD2(const AsciiString &name);
};

extern ScriptEngine *TheScriptEngine;

// TheAudio: vslot 35 stops the given audio kinds.
class AudioManager
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34();
	virtual void v35(int a, int b, int c);
};

extern AudioManager *TheAudio;

class Shell
{
public:
	// Rowed 0x0035BEC7; unrowed 0x0035BD5D (a byte query) and 0x0035C2B9,
	// pinned by address.
	void rva0035BEC7();
	bool rva0035BD5D();
	void rva0035C2B9();

	unsigned char m_pad00[0x5D];
	bool m_5d; // +0x5D
};

// The shell's rowed 0x0035BD3F (its own address class).
class Rva0035BD3F
{
public:
	void rva0035BD3F();
};

class GameWindowTransitionsHandler
{
public:
	void setGroup(AsciiString groupName, bool immediate);
	void reverse(AsciiString groupName);
};

extern GameWindowTransitionsHandler *TheTransitionHandler;

class UserPreferences
{
public:
	virtual ~UserPreferences();
	virtual void setBool(const AsciiString &key, bool value);
	virtual bool write();
};

// The options file (its destructor is rowed as ??1Rva002E4272, pinned
// here under this name).
class OptionPreferences : public UserPreferences
{
public:
	OptionPreferences();
	virtual ~OptionPreferences();

	unsigned char m_rest[0x14 - 0x04];
};

extern Shell *TheShell;

// TheGameEngine: vslot 20 (Zero Hour's setQuitting position moved).
class GameEngine
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(bool value);
};

extern GameEngine *TheGameEngine;

// TheGlobalData's +0x28 (the frame rate TheGameEngine vslot 18 takes back).
class GlobalData;
extern GlobalData *TheGlobalData;

// OpaqueScalarDeletingDtorsB12.cpp's g_Va00E048DC (the open resource
// holder).
extern int g_Va00E048DC;

struct AptMainMenuGlobalData
{
	unsigned char m_pad00[0x28];
	int m_28; // +0x28
};

class GameEngineRate
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17();
	virtual void v18(int value);
};

// The credits roll (0x00E06474): vslot 9 stops it; deleted through vslot 0
// and a separate operator delete.
class AptMainMenuCredits
{
public:
	virtual void *deleteInstance(int flags);
	virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
	virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08();
	virtual void v09();
};

extern AptMainMenuCredits *g_Va00E06474;

class GameMessage;

// Zero Hour's TheMessageStream (VA 0x00E00950, the ledger's
// MessageStreamSubsystem); appendMessage is vslot 18.
class MessageStream
{
public:
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
	virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
	virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17();
	virtual GameMessage *appendMessage(int type);
};

extern MessageStream *MessageStreamSubsystem;

// The game mode TheGameLogic (0x00DFE78C) keeps at +0x110.
class GameLogic;
extern GameLogic *TheGameLogic;

struct AptMainMenuGameLogic
{
	unsigned char m_pad000[0x110];
	int m_mode; // +0x110
};

class AptMainMenu
{
public:
	void LoadGame(const char *unused);
	void Options(const char *value);
	void GoodCampaign(const char *value);
	void EvilCampaign(const char *value);
	void CreateAHero(const char *unused);
	void WarOfTheRing(const char *unused);
	void LoadCampaign(const char *unused);
	void Skirmish(const char *unused);
	void LoadReplay(const char *unused);
	void StopGameMovie(const char *unused);
	void ContinueCampaign(const char *unused);
	void OnInitialized(const char *unused);
	void ExitGame(const char *unused);
	void BattleSchool(const char *unused);
	void CreditsExit(const char *unused);

	// "AptMainMenu::ResetResolution" (0x00514C15, 214 bytes), unrowed and
	// pinned by address.
	void ResetResolution(const char *unused);

	// Bound without a name by the LAN and online openers (0x00515C64,
	// 0x005160DE) and the tutorial prompt (0x00515980); they keep their
	// addresses.
	void rva00514B8D();
	void rva00514BA1();
	void rva00514BB5();
	void rva00514DC0(int button);

private:
	unsigned char m_pad000[0x27C];
	bool m_initialized; // +0x27C
	bool m_pendingRestart; // +0x27D
	bool m_restart; // +0x27E
	bool m_27f;
	bool m_280;
	bool m_tutorialPending; // +0x281
	bool m_282; // +0x282
	unsigned char m_pad283[0x288 - 0x283];
	int m_state; // +0x288
	int m_next; // +0x28C
	unsigned char m_pad290[0x2A4 - 0x290];
	AsciiString m_2a4; // +0x2A4
	char m_side; // +0x2A8
};

// Retail 0x00514A9B, 23 bytes: "AptMainMenu::LoadGame".
void AptMainMenu::LoadGame(const char *unused)
{
	m_state = 9;
	m_next = 1;
}

// Retail 0x00514AB2, 46 bytes: "AptMainMenu::Options", 5 when the value
// is "true", else 4.
void AptMainMenu::Options(const char *value)
{
	m_state = 9;
	m_next = strcmp(value, "true") ? 4 : 5;
}

// Retail 0x00514AE0, 35 bytes: "AptMainMenu::GoodCampaign", keeping the
// value's first character.
void AptMainMenu::GoodCampaign(const char *value)
{
	m_state = 9;
	m_next = 11;
	m_side = *value;
}

// Retail 0x00514B03, 35 bytes: "AptMainMenu::EvilCampaign".
void AptMainMenu::EvilCampaign(const char *value)
{
	m_state = 9;
	m_next = 12;
	m_side = *value;
}

// Retail 0x00514B26, 18 bytes: "AptMainMenu::CreateAHero".
void AptMainMenu::CreateAHero(const char *unused)
{
	m_state = 9;
	m_next = 9;
}

// Retail 0x00514B38, 23 bytes: "AptMainMenu::WarOfTheRing".
void AptMainMenu::WarOfTheRing(const char *unused)
{
	m_state = 9;
	m_next = 8;
}

// Retail 0x00514B4F, 23 bytes: "AptMainMenu::LoadCampaign".
void AptMainMenu::LoadCampaign(const char *unused)
{
	m_state = 9;
	m_next = 2;
}

// Retail 0x00514BC9, 23 bytes: "AptMainMenu::Skirmish".
void AptMainMenu::Skirmish(const char *unused)
{
	m_state = 9;
	m_next = 7;
}

// Retail 0x00514BE0, 23 bytes: "AptMainMenu::LoadReplay".
void AptMainMenu::LoadReplay(const char *unused)
{
	m_state = 9;
	m_next = 3;
}

// Retail 0x00514BF7, 30 bytes: "AptMainMenu::StopGameMovie" (BFME1's
// AptScreenSelectorCallbacks.cpp has its own): outside game mode 9 it posts
// message 0x1D.
void AptMainMenu::StopGameMovie(const char *unused)
{
	if (((AptMainMenuGameLogic *)TheGameLogic)->m_mode != 9)
		MessageStreamSubsystem->appendMessage(0x1D);
}

// Retail 0x00515041, 51 bytes: "AptMainMenu::ContinueCampaign" stays on
// the menu (state 1) when the campaign autosave "00000000.sav" exists.
void AptMainMenu::ContinueCampaign(const char *unused)
{
	if (((Rva002DCCFB *)TheGameState)->rva002DCCFB(UnicodeString(L"00000000.sav")))
		m_state = 1;
}

// Retail 0x00514E76, 42 bytes: "AptMainMenu::OnInitialized".
void AptMainMenu::OnInitialized(const char *unused)
{
	ResetResolution(0);
	m_initialized = true;
	if (m_pendingRestart)
	{
		m_restart = true;
		m_pendingRestart = false;
	}
}

// Retail 0x005152E7, 114 bytes: "AptMainMenu::ExitGame" fires the
// "ShellMainMenuExitPushed" script event, stops audio, runs the shell's
// 0x0035BEC7 and sets TheGameEngine's vslot 20.
void AptMainMenu::ExitGame(const char *unused)
{
	{
		AsciiString name(g_009C108C);
		TheScriptEngine->rva00357DD2(name);
	}
	TheAudio->v35(2, 1, 0);
	TheShell->rva0035BEC7();
	TheGameEngine->v20(true);
}

// Retail 0x00515074, 169 bytes: "AptMainMenu::BattleSchool" runs the
// "MainMenuToBattleSchool" transition and clears the options file's
// "FlashTutorial" flag.
void AptMainMenu::BattleSchool(const char *unused)
{
	if (TheShell)
		TheShell->m_5d = true;
	TheTransitionHandler->setGroup(AsciiString("MainMenuToBattleSchool"), false);
	if (TheShell)
		((Rva0035BD3F *)TheShell)->rva0035BD3F();
	OptionPreferences prefs;
	prefs.setBool(AsciiString("FlashTutorial"), false);
	prefs.write();
	m_tutorialPending = false;
}

// Retail 0x00515231, 182 bytes: "AptMainMenu::CreditsExit" stops and frees
// the credits, restores the shell's audio unless 0x0035BD5D holds, reverses
// the "MainMenuToCreditsScreen" transition and resets the menu.
void AptMainMenu::CreditsExit(const char *unused)
{
	if (g_Va00E06474)
	{
		g_Va00E06474->v09();
		::operator delete(g_Va00E06474 ? g_Va00E06474->deleteInstance(0) : 0);
		g_Va00E06474 = 0;
	}
	if (!TheShell || !TheShell->rva0035BD5D())
	{
		TheAudio->v35(2, 1, 0);
		TheShell->rva0035C2B9();
	}
	TheTransitionHandler->reverse(AsciiString("MainMenuToCreditsScreen"));
	m_state = 0;
	m_2a4.clear();
	TheShell->m_5d = false;
	((GameEngineRate *)TheGameEngine)->v18(((AptMainMenuGlobalData *)TheGlobalData)->m_28);
}

// Retail 0x00514B8D, 20 bytes. Name unknown. State 5 while the resource
// holder g_Va00E048DC is set.
void AptMainMenu::rva00514B8D()
{
	if (g_Va00E048DC)
		m_state = 5;
}

// Retail 0x00514BA1, 20 bytes. Name unknown. State 6 likewise.
void AptMainMenu::rva00514BA1()
{
	if (g_Va00E048DC)
		m_state = 6;
}

// Retail 0x00514BB5, 20 bytes. Name unknown. State 7 likewise.
void AptMainMenu::rva00514BB5()
{
	if (g_Va00E048DC)
		m_state = 7;
}

// Retail 0x00514DC0, 26 bytes. Name unknown. In state 8 keeps whether the
// prompt was answered with button 2.
void AptMainMenu::rva00514DC0(int button)
{
	if (m_state == 8)
		m_282 = button == 2;
}
