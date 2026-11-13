// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// BFME2's in-game quit menu Apt callbacks, 0x0051AFB9 onward, bound by
// these names ("AptQuitMenu::RestartMission" ...) as member pointers by the
// screen's registration; that binding is their only reference. The class
// is named for the strings' prefix.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
#include "ascii_string.h"
#include "unicode_string.h"

// restartMissionMenu's replay test expands isNotEmpty in place (test the
// buffer, then cmp word [eax+4]); the shared header keeps it out of line.
// Suppress the standalone local copy; string_base_inline.cpp owns retail's
// out-of-line predicate. The replay test retains this inline expression.
template <> __declspec(dllimport) __forceinline bool StringBase<unsigned short>::isNotEmpty() const { return m_data && m_data->length != 0; }

#include <string.h>

class AptSaveLoad
{
public:
	static void OpenScreen(int a, int b, bool c);
};
void __cdecl Rva00511730(int value);
void __cdecl Rva0051AF0BEnable(int value);
#include "../../../../../Include/GameClient/AptOptions.h"

// TheGameLogic (0x00DFE78C): the mode at +0x110, +0x114 and the rowed
// readers this unit calls.
class GameLogic
{
public:
	bool isInMultiplayerGame();
	void rva0023CD9E(bool paused, int pauseMode, bool affectMouse);
	void DoExitMap(bool selfDestruct);
	// Zero Hour calls clearGameData at the same point; the name is unproven here.
	void clearGameData(bool showScoreScreen, bool flag);

	unsigned char m_pad000[0x40];
	unsigned int m_40; // +0x40
	unsigned char m_pad044[0x6D - 0x44];
	bool m_6d; // +0x6D
	unsigned char m_pad06e[0x94 - 0x6E];
	int m_restartRankPoints; // +0x94, the rank points a restart passes on
	unsigned char m_pad098[0xA4 - 0x98];
	int m_restartDifficulty; // +0xA4, the difficulty a restart passes on
	unsigned char m_pad0a8[0x110 - 0xA8];
	int m_110; // +0x110
	int m_114; // +0x114
};

extern GameLogic *TheGameLogic;

// The rowed check 0x0023C902 on the same object.
#include "../../../../../Include/Common/Rva0023C902.h"

// The rowed bool field reader 0x00210C66 on the same object.
#include "../../../../../Include/GameNetwork/Rva00210C66CmpBoolField.h"

// TheGameText's fetch (vslot 15).
#include "../../../../../Include/GameClient/GameText.h"

extern GameTextInterface *TheGameText;

// TheMouse's rowed tooltip setter 0x001EEA6D (MouseRva001EEA6D.cpp).
#include "../../../../../../Libraries/Include/Lib/RGBColor.h"

class Mouse
{
	friend class AptQuitMenu;

public:
#define MOUSE_SLOT(N) virtual void slot##N();
	MOUSE_SLOT(00) MOUSE_SLOT(01) MOUSE_SLOT(02) MOUSE_SLOT(03) MOUSE_SLOT(04)
	MOUSE_SLOT(05) MOUSE_SLOT(06) MOUSE_SLOT(07) MOUSE_SLOT(08) MOUSE_SLOT(09)
	MOUSE_SLOT(10) MOUSE_SLOT(11) MOUSE_SLOT(12) MOUSE_SLOT(13) MOUSE_SLOT(14)
	MOUSE_SLOT(15) MOUSE_SLOT(16) MOUSE_SLOT(17) MOUSE_SLOT(18)
#undef MOUSE_SLOT
	virtual void setCursor(int cursor);
	void rva001EEA6D(UnicodeString tooltip, int delay, const RGBColor *color, float width);

private:
	void commitPendingCursor();
};

extern Mouse *TheMouse;

// The rowed 0x001EDDC6 on TheMouse (BFME1's bfmeSetYR).
class Rva001EDDC6
{
public:
	void rva001EDDC6(unsigned char value);
};

// TheLivingWorldLogic (0x009FEF10); its rowed
// isSelectionLocked 0x0004253A tells a war of the ring game apart.
#include "../../../../../Include/Common/BfmeSelectionState.h"

// The living-world logic's player at +0x98 and its byte +0x3C5.
struct LivingWorldPlayer
{
	unsigned char m_pad000[0x3C5];
	bool m_3c5; // +0x3C5
};

struct LivingWorldLocal
{
	unsigned char m_pad000[0x98];
	LivingWorldPlayer *m_98; // +0x98
	unsigned char m_pad09c[0xB4 - 0x9C];
	bool m_b4; // +0xB4
	unsigned char m_pad0b5[0x168 - 0xB5];
	bool m_168; // +0x168
};

// The rowed two-flag predicate 0x0051AEEF on the same object.
class Rva0051AEEF
{
public:
	bool rva0051AEEF() const;
};

#include "../../../../../Include/Common/Rva002B2B66.h"

// The +0x10 view TheInGameUI's 0x000CF155 returns and the folded forwarder
// to its vslot 3 (0x005CB265), both pinned.
class Rva005CB260;

#include "../../../../../Include/Common/Rva005CB265.h"

// TheInGameUI (0x00DFEDF0): vslot 94 shows or hides the quit menu (BFME1's
// slot 84) and vslot 95 tells whether it is up.
#include "../../../../../Include/GameClient/InGameUI.h"

extern InGameUI *TheInGameUI;

// TheShell (0x00E01E48) and its rowed 0x0035BF4C (BFME1's Shell::hide).
#include "../../../../../Include/GameClient/Shell.h"

extern Shell *TheShell;

// TheNetwork (0x00DFEA28): vslot 37 quits the network game.
#include "../../../../../Include/GameNetwork/NetworkInterfaceClass.h"

extern NetworkInterface *TheNetwork;

#include "../../../../../Include/Common/MessageStream.h"

// TheMessageStream (0x00A00950); appendMessage is vslot 18.

extern MessageStream *TheMessageStream;

// The network quit's frame limit (.rdata 0x007ED97C).
extern unsigned int g_007ED97C;

// TheScriptEngine (0x009FE16C): +0x1A104 is negative unless the game is ending.
class ScriptEngine
{
public:
	unsigned char m_pad00000[0x1A104];
	int m_1a104; // +0x1A104
};

extern ScriptEngine *TheScriptEngine;

#include "../../../../../Include/GameClient/GameWindowTransitionsHandler.h"

extern GameWindowTransitionsHandler *TheTransitionHandler;

// TheDisplay (0x009FE9D8): vslots 87 and 88 hold the quit menu back.
#include "../../../../../Include/GameClient/Display.h"

extern Display *TheDisplay;

// Further screens that keep the quit menu closed while up
// (ColdGlobalDwordGetters.cpp).
extern int g_Va00E0492C;
extern int g_Va00E0330C;
class DisconnectMenu; extern DisconnectMenu *TheDisconnectMenu;

// TheLinearCampaignManager-like holder at 0x009FDC8C: a running campaign
// restarts through its +0x10 member (the rowed 0x001ECEF6).
struct Rva0023D607Holder
{
	unsigned char m_pad000[0x10];
	void *m_10; // +0x10
	void rva001ECEF6();
};

extern class LinearCampaignManager *TheLinearCampaignManager;

// TheWritableGlobalData (0x009FE758): the map name and the pending file.
#include "../../../../../Include/Common/GlobalData.h"

extern GlobalData *TheWritableGlobalData;

// TheGameState (0x009FF08C): the rowed save-directory test 0x002DC7C1 and
// the folded AsciiString +0x2C copy getter 0x0004F833 (rowed under
// Player::getBaseSide) that hands back the pristine map name.
class GameState;
extern GameState *TheGameState;

#include "../../../../../Include/Common/Rva002DC7C1.h"

class Player
{
public:
	AsciiString getBaseSide() const;
};

// TheRecorder (0x00A02290).
enum RecorderModeType
{
	RECORDERMODETYPE_RECORD,
	RECORDERMODETYPE_PLAYBACK
};

#include "../../../../../Include/Common/RecorderClass.h"

extern RecorderClass *TheRecorder;

// The rowed replay file name getter 0x0037B5A0 on TheRecorder.
class Rva0037B5A0
{
public:
	UnicodeString rva0037B5A0();
};

// TheGameEngine (0x009FE710): vslots 19 and 20.
#include "../../../../../Include/Common/GameEngine.h"

extern GameEngine *TheGameEngine;

// The living-world logic's rowed 0x002B36F3.
#include "../../../../../Include/GameLogic/Rva002BA8F1Logic.h"

void InitRandom(unsigned int seed);

// The panels the quit menu closes (all rowed).
void __cdecl Rva0043C96FEnable(void);
void __cdecl Rva004E855CClose(void);
void __cdecl Rva004E400DEnable(void);
#include "../../../../../Include/GameClient/AptPlayerTribute.h"

// The Apt callback functors (Rva0057BC63FunctorHolder.cpp, as in
// MpGameSetupSlots.cpp): a binding of an object and an eight-byte
// multiple-inheritance member pointer, and the refcounted holder rowed
// 0x0057BC63 builds from it.
class __multiple_inheritance FunctorTarget;
typedef void (FunctorTarget::*FunctorMethod)(void);

#include "../../../../../Include/GameClient/FunctorBinding.h"

#include "../../../../../Include/Common/FunctorWrapperHead.h"

class Rva0057BC63FunctorHolder
{
public:
	Rva0057BC63FunctorHolder(const FunctorBinding &binding);
	Rva0057BC63FunctorHolder(const Rva0057BC63FunctorHolder &other) : m_ptr(other.m_ptr)
	{
		if (m_ptr)
			++m_ptr->m_refCount;
	}

	FunctorWrapperHead *m_ptr;
};

// Builds a binding by value: the named result is copied out, which is the
// second sixteen-byte slot every registration in the constructor fills.
__forceinline FunctorBinding MakeBinding(FunctorMethod method, FunctorTarget *target)
{
	FunctorBinding binding(method, target);
	return binding;
}

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref);

template <class T> class AptRef : public Rva0057BC63FunctorHolder
{
public:
	AptRef(const FunctorBinding &binding) : Rva0057BC63FunctorHolder(binding) {}
	~AptRef()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr);
	}
};

class AptCommandMap;
class AptExternHandler;
class AptOverButtonHandler;

namespace _STL
{
	template <class T> class allocator {};

	template <class T, class A = allocator<T> > class vector
	{
	private:
		T *m_start;
		T *m_finish;
		T *m_endOfStorage;
	};
}

// The adders (AptCallbackAdders.cpp, all rowed): each registers with the
// Apt player and remembers the name.
class AptCommandMapAdder
{
public:
	void AddCommandMap(const AsciiString &name, AptRef<AptCommandMap> map);

private:
	_STL::vector<AsciiString> m_names;
};

class AptExternHandlerAdder
{
public:
	void AddExternHandler(const AsciiString &name, int arg, AptRef<AptExternHandler> handler);

private:
	_STL::vector<AsciiString> m_names;
};

class AptOverButtonHandlerAdder
{
public:
	void AddOverButtonHandler(const AsciiString &name, AptRef<AptOverButtonHandler> handler);

private:
	_STL::vector<AsciiString> m_names;
};

// The Apt player (0x00DFE4CC): the rowed background switch 0x002233A6
// and text setter 0x00225301.
#include "../../../../../../Libraries/Source/Apt/BfmeAptWindowManager.h"

// Existing target-owned background dispatchers; their address names preserve
// the unresolved original class/method identity carried by the donor aliases.
#include "../../../../../Include/Common/Rva00222A8BTarget.h"

extern BfmeAptWindowManager *g_bfmeAptWindowManager;

// The Apt screen base (BfmeAptGameWindowDestructor.cpp): a 0x218-byte
// GameWindow and, at +0x218, the 0x58-byte callback registry whose adders
// sit at +0x04, +0x10 and +0x1C.
#include "../../../../../Include/GameClient/Bfme2GameWindow.h"

class Rva005248D0
{
public:
	virtual ~Rva005248D0();

	AptCommandMapAdder m_commandMaps; // +0x04
	AptExternHandlerAdder m_externHandlers; // +0x10
	AptOverButtonHandlerAdder m_overButtonHandlers; // +0x1C

private:
	unsigned char m_pad028[0x58 - 0x28];
};

class _bfme_AptGameWindow : public GameWindow, public Rva005248D0
{
public:
	_bfme_AptGameWindow(void *context);
	virtual ~_bfme_AptGameWindow();

private:
	AsciiString m_filename; // +0x270
	int m_274;
	char m_278;
};

class AptQuitMenu : public _bfme_AptGameWindow
{
public:
	AptQuitMenu(void *context);
	virtual ~AptQuitMenu();

	void OnInitialized(const char *unused);
	void RestartMission(const char *unused);
	void ExitMission(const char *unused);
	void OptionsScreen(const char *unused);
	void ReturnToGame(const char *unused);
	void SaveMenu(const char *unused);
	void LoadMenu(const char *unused);
	// Bound under the button clip "QuitMenu/Restart/TheButton" (0x0051BD98)
	// rather than a method name, so it keeps its address.
	void HandleOverRestartButton(const char *unused);
	// Retail 0x0051AF46, 115 bytes: Apt query answering the quit-menu
	// restart-button label: count "1" for query 0, and for query 1 the
	// Restart/Forfeit/Surrender word matching HandleOverRestartButton's tooltip pick.
	void Externs(int query, char *value, bool set);

private:
	bool m_exit; // +0x27C
	bool m_27d;
	bool m_restart; // +0x27E
	int m_280;
};

// The open quit menu (0x00E04910), set by its constructor. Defined here, in the
// unit whose rowed constructor assigns it (AptQuitMenu::AptQuitMenu below), so
// every reader binds one definition instead of an unresolved external. Retail
// creates the menu at runtime, so the object is zero-initialised, the state
// every reader tests: the stale pointer retail's image holds in the 4-byte
// .data slot at RVA 0x009A4910 is overwritten before any code reads it.
AptQuitMenu *TheAptQuitMenu;

// Retail 0x0051AFB9, 10 bytes: "AptQuitMenu::RestartMission".
void AptQuitMenu::RestartMission(const char *unused)
{
	m_restart = true;
}

// Retail 0x0051AFC3, 26 bytes: "AptQuitMenu::ExitMission".
void AptQuitMenu::ExitMission(const char *unused)
{
	m_exit = true;
	Rva00511730(0);
	Rva0051AF0BEnable(2);
}

// Retail 0x0051AFDD, 17 bytes: "AptQuitMenu::OptionsScreen".
void AptQuitMenu::OptionsScreen(const char *unused)
{
	AptOptions::OpenScreen(false, false, false, false);
}

// Retail 0x0051AFEE, 11 bytes: "AptQuitMenu::ReturnToGame".
void AptQuitMenu::ReturnToGame(const char *unused)
{
	Rva0051AF0BEnable(0);
}

// Retail 0x0051AFF9, 81 bytes: "AptQuitMenu::SaveMenu" opens the save
// screen (3) in the current game's mode: 8 without +0x114, 16 by the
// 0x00210C66 field, 4 in a multiplayer game, else 2 in mode 2 and 1.
void AptQuitMenu::SaveMenu(const char *unused)
{
	GameLogic *logic = TheGameLogic;
	int kind;
	if (logic->m_114 == 0)
		kind = 8;
	else if (((Rva00210C66CmpBoolField *)logic)->get())
		kind = 16;
	else if (logic->isInMultiplayerGame())
		kind = 4;
	else
		kind = (logic->m_110 == 2) + 1;
	AptSaveLoad::OpenScreen(3, kind, true);
}

// Retail 0x0051B04A, 81 bytes: "AptQuitMenu::LoadMenu", the same for the
// load screen (2).
void AptQuitMenu::LoadMenu(const char *unused)
{
	GameLogic *logic = TheGameLogic;
	int kind;
	if (logic->m_114 == 0)
		kind = 8;
	else if (((Rva00210C66CmpBoolField *)logic)->get())
		kind = 16;
	else if (logic->isInMultiplayerGame())
		kind = 4;
	else
		kind = (logic->m_110 == 2) + 1;
	AptSaveLoad::OpenScreen(2, kind, true);
}

// Retail 0x0051AF46, 115 bytes: Apt query answering the quit-menu
// restart-button label: count "1" for query 0, and for query 1 the
// Restart/Forfeit/Surrender word matching HandleOverRestartButton's tooltip pick.
void AptQuitMenu::Externs(int query, char *value, bool set)
{
	if (!set)
	{
		value[0] = '0';
		value[1] = 0;
	}
	switch (query)
	{
	case 0:
		if (set)
			return;
		value[0] = '1';
		return;
	case 1:
		break;
	default:
		return;
	}
	if (set)
		return;
	const char *label;
	GameLogic *logic = TheGameLogic;
	if (logic == 0 || logic->m_114 == 3)
		label = "Restart";
	else if (TheLivingWorldLogic != 0 && ((BfmeSelectionState *)TheLivingWorldLogic)->isSelectionLocked())
		label = "Surrender";
	else
		label = "Forfeit";
	strcpy(value, label);
}

// Retail 0x0051B15E, 512 bytes: the quit menu's destructor, as BFME1's
// ~BfmeAptScreenQuitMenu (AptQuitMenu.cpp there). The open menu hides
// itself, unpauses a single player game and, when exiting, quits the
// network game, ends the war of the ring battle (0x448 surrender unless
// selection is locked, then 0x6B8 with the rowed 0x002B2B66) or runs
// GameLogic's exit tail 0x0023D0E3, and shows background 1; otherwise it
// hides the background unless +0x27D. Then "APT:Pause" is relabelled.
// Retail reads TheGameLogic once, keeps it across isInMultiplayerGame and
// rereads it only after the three calls that can change it; the rereads
// are spelled out.
AptQuitMenu::~AptQuitMenu()
{
	if (this != TheAptQuitMenu)
		return;
	TheAptQuitMenu = 0;
	if (TheInGameUI)
		TheInGameUI->rva0029AC03(false);
	GameLogic *logic = TheGameLogic;
	if (logic && !logic->isInMultiplayerGame())
	{
		logic->rva0023CD9E(false, m_280, true);
		logic = TheGameLogic;
	}
	if (TheMouse)
	{
		TheMouse->commitPendingCursor();
		logic = TheGameLogic;
	}
	if (TheShell && !m_exit)
	{
		TheShell->rva0035BF4C(false);
		logic = TheGameLogic;
	}
	if (logic && m_exit)
	{
		if (logic->m_40 < g_007ED97C && (logic->m_110 == 1 || logic->m_110 == 5) && TheNetwork)
			TheNetwork->quitGame();
		else if (logic->m_114 != 3 && TheLivingWorldLogic)
		{
			if (((LivingWorldLocal *)TheLivingWorldLogic)->m_98)
				((LivingWorldLocal *)TheLivingWorldLogic)->m_98->m_3c5 = true;
			if (!((BfmeSelectionState *)TheLivingWorldLogic)->isSelectionLocked())
			{
				GameMessage *surrender = TheMessageStream->appendMessage(0x448);
				surrender->appendBooleanArgument(true);
			}
			GameMessage *msg = TheMessageStream->appendMessage(0x6B8);
			msg->appendIntegerArgument(((Rva002B2B66 *)TheLivingWorldLogic)->rva002B2B66());
		}
		else
			logic->DoExitMap(true);
		if (g_bfmeAptWindowManager)
			((Rva00222A8BTarget *)g_bfmeAptWindowManager)->rva002233A6(1);
	}
	else if (!m_27d && g_bfmeAptWindowManager)
		((Rva00222A8BTarget *)g_bfmeAptWindowManager)->rva00222F55(false);
	AsciiString key("APT:Pause");
	g_bfmeAptWindowManager->bfmeSetText(key, TheGameText->fetch("APT:Pause"), false);
}

// Retail 0x0051B369, 398 bytes: opens the quit menu, as BFME1's
// showQuitMenu (ShowQuitMenu.cpp there; Zero Hour QuitMenu.cpp's
// ToggleQuitMenu show arm). Nothing happens while a quit menu exists, the
// menu is up, another screen holds it back, the game is loading or ending
// (0x0023C902, +0x6D, the script engine), a war of the ring battle is
// resolving or a transition is running. Otherwise the side panels close,
// a single player game pauses, and the shell pushes "QuitMenu.apt".
// Name inferred from the donors.
void ShowQuitMenu()
{
	if (TheAptQuitMenu)
		return;
	if (TheInGameUI->slot95())
		return;
	if (g_Va00E0492C)
		return;
	if (g_Va00E0330C)
		return;
	if ((unsigned char)((Rva0023C902 *)TheGameLogic)->rva0023C902())
		return;
	if (TheGameLogic->m_6d)
		return;
	if (TheScriptEngine->m_1a104 >= 0)
		return;
	if (TheLivingWorldLogic && ((LivingWorldLocal *)TheLivingWorldLogic)->m_b4 && ((LivingWorldLocal *)TheLivingWorldLogic)->m_168)
		return;
	if (!TheTransitionHandler->isFinished())
		return;
	if (TheDisconnectMenu)
		return;
	if (TheDisplay)
	{
		if (TheDisplay->slot88())
			return;
		if (TheDisplay->slot87())
			return;
	}
	if (TheLivingWorldLogic && ((Rva0051AEEF *)TheLivingWorldLogic)->rva0051AEEF())
		return;

	Rva0043C96FEnable();
	Rva004E855CClose();
	Rva004E400DEnable();
	AptPlayerTribute::CloseScreen();
	((Rva005CB265 *)TheInGameUI->rva000CF155())->Rva005CB265::rva005CB265();
	((Rva001EDDC6 *)TheMouse)->rva001EDDC6(1);

	GameLogic *logic = TheGameLogic;
	if (!logic->isInMultiplayerGame())
		logic->rva0023CD9E(true, 0, true);
	TheMouse->setCursor(2);
	TheShell->showShell(false);
	TheShell->push(AsciiString("QuitMenu.apt"), false);
	TheInGameUI->rva0029AC03(true);
}

// Retail 0x0051B4F7, 23 bytes: closes the open quit menu (as its
// ReturnToGame does) or opens one; Zero Hour QuitMenu.cpp's name.
void ToggleQuitMenu()
{
	if (TheAptQuitMenu)
	{
		Rva0051AF0BEnable(0);
		return;
	}
	ShowQuitMenu();
}

// Retail 0x0051B90B, 468 bytes: Zero Hour QuitMenu.cpp's
// restartMissionMenu, run by the quit menu's update once RestartMission
// set +0x27E. Closes the menu; a running campaign restarts itself.
// Otherwise the game is cleared and either the replay plays again or a
// new game (0x1E) starts on the pristine map in the same mode,
// difficulty, rank points and frame limit.
void restartMissionMenu()
{
	Rva0051AF0BEnable(2);
	if (((Rva0023D607Holder *)TheLinearCampaignManager) && ((Rva0023D607Holder *)TheLinearCampaignManager)->m_10)
	{
		((Rva0023D607Holder *)TheLinearCampaignManager)->rva001ECEF6();
		return;
	}
	int gameMode = TheGameLogic->m_110;
	AsciiString mapName = TheWritableGlobalData->m_mapName;
	if (((Rva002DC7C1 *)TheGameState)->rva002DC7C1(UnicodeString(mapName)))
		mapName = ((Player *)TheGameState)->getBaseSide();

	UnicodeString replayFile = ((Rva0037B5A0 *)TheRecorder)->rva0037B5A0();
	if (TheRecorder->getMode() == RECORDERMODETYPE_RECORD)
		TheRecorder->stopRecording();

	int rankPointsStartedWith = TheGameLogic->m_restartRankPoints;
	int diff = TheGameLogic->m_restartDifficulty;
	int fps = TheGameEngine->getFramesPerSecondLimit();

	TheGameLogic->clearGameData(false, false);
	TheGameEngine->setQuitting(false);
	if (TheLivingWorldLogic)
		((Rva002BA8F1Logic *)TheLivingWorldLogic)->rva002B36F3();

	if (replayFile.isNotEmpty())
	{
		TheRecorder->playbackFile(replayFile);
	}
	else
	{
		TheWritableGlobalData->field0AC0 = mapName;
		GameMessage *msg = TheMessageStream->appendMessage(0x1E);
		msg->appendIntegerArgument(gameMode);
		msg->appendIntegerArgument(diff);
		msg->appendIntegerArgument(rankPointsStartedWith);
		msg->appendIntegerArgument(fps);
		if (gameMode != 2)
			InitRandom(0);
	}
	TheInGameUI->m_8C5 = true;
}

// Retail 0x0051B50E, 167 bytes. Name unknown. Shows the restart button's
// tooltip: restart in a campaign (mode 3) or without a game, else forfeit,
// or surrender in a war of the ring game.
void AptQuitMenu::HandleOverRestartButton(const char *unused)
{
	const char *label;
	if (TheGameLogic && TheGameLogic->m_114 != 3)
	{
		if (TheLivingWorldLogic && ((BfmeSelectionState *)TheLivingWorldLogic)->isSelectionLocked())
			label = "TOOLTIP:QuitMenu/Surrender/WOTRSurrender";
		else
			label = "TOOLTIP:QuitMenu/Forfeit/WOTRForfeit";
	}
	else
		label = "TOOLTIP:QuitMenu/Restart/TheButton";
	bool exists = false;
	UnicodeString tooltip = TheGameText->fetch(label, &exists);
	if (exists)
		TheMouse->rva001EEA6D(tooltip, -1, 0, 1.0f);
}

// Retail 0x0051B8EA, 5 bytes: the toggle as AptPalantir::OnBttnOptions
// (0x002D30C7) reaches it, a tail jump. Name unknown.
void Rva0051B8EA()
{
	ToggleQuitMenu();
}

// The extern handlers' names, by query (0x00C66BF8).
static const char *const s_externNames[] = { "HasFocus", "AptQuitMenu::RestartPopupType" };

// Retail 0x0051BADF, 1016 bytes: the quit menu's constructor. The first
// one opened becomes TheAptQuitMenu and binds its callbacks by name
// ("AptQuitMenu::OnInitialized" ... "AptQuitMenu::LoadMenu", the restart
// button's tooltip and the two Externs queries), switches the Apt player
// to background 2 and, in a multiplayer game, relabels "APT:Pause" with
// "GUI:Menu". As BFME1's BfmeAptScreenQuitMenu constructor
// (BfmeAptScreenQuitMenuConstructor.cpp) with BFME2's adders.
// The handlers are bound as eight-byte multiple-inheritance member pointers.
// The Externs loop's counter is declared before its binding is copied out,
// which keeps it in the dead context slot rather than a register.
#pragma pointers_to_members(full_generality, multiple_inheritance)
AptQuitMenu::AptQuitMenu(void *context) : _bfme_AptGameWindow(context)
{
	m_exit = false;
	m_27d = false;
	m_restart = false;
	m_280 = 0;
	if (TheAptQuitMenu != 0)
		return;
	TheAptQuitMenu = this;
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptQuitMenu::OnInitialized);
		AsciiString name("AptQuitMenu::OnInitialized");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptQuitMenu::RestartMission);
		AsciiString name("AptQuitMenu::RestartMission");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptQuitMenu::ExitMission);
		AsciiString name("AptQuitMenu::ExitMission");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptQuitMenu::OptionsScreen);
		AsciiString name("AptQuitMenu::OptionsScreen");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptQuitMenu::ReturnToGame);
		AsciiString name("AptQuitMenu::ReturnToGame");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptQuitMenu::SaveMenu);
		AsciiString name("AptQuitMenu::SaveMenu");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptQuitMenu::LoadMenu);
		AsciiString name("AptQuitMenu::LoadMenu");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptQuitMenu::HandleOverRestartButton);
		AsciiString name("QuitMenu/Restart/TheButton");
		m_overButtonHandlers.AddOverButtonHandler(name, AptRef<AptOverButtonHandler>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptQuitMenu::Externs);
		int query = 0;
		FunctorBinding binding = MakeBinding(method, reinterpret_cast<FunctorTarget *>(this));
		for (; query < 2; ++query)
		{
			AsciiString name(s_externNames[query]);
			m_externHandlers.AddExternHandler(name, query, AptRef<AptExternHandler>(binding));
		}
	}
	((Rva00222A8BTarget *)g_bfmeAptWindowManager)->rva002233A6(2);
	if (TheGameLogic && TheGameLogic->isInMultiplayerGame())
	{
		AsciiString key("APT:Pause");
		g_bfmeAptWindowManager->bfmeSetText(key, TheGameText->fetch("GUI:Menu"), false);
	}
}


extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

// The rowed 0x00222547 window helper, whose integer result the Apt layer
// passes through as the movie pointer.
#include "../../../../../../Libraries/Source/Apt/AptPlayerClass.h"

// The living world's rowed 0x002B254F, whose int callers read only its low byte.
#include "../../../../../Include/Common/Rva002B254F.h"

// The 0x00DFEF18 singleton (address-named view) and its +0x14 dword.
class Rva002D3627Host
{
public:
	unsigned char m_pad000[0x14];
	int m_14; // +0x14
};

class LivingWorld; extern LivingWorld *TheLivingWorld;

// Greys out the named button of a screen's Apt movie.
static __forceinline void DisableButton(GameWindow *window, const char *button)
{
	((Rva00222A8BTarget *)g_bfmeAptWindowManager)->invoke(reinterpret_cast<void *>(AptPlayer::GetLevelIndex(window)), "disableButton", 1, button, 0, 0, 0, 0);
}

// Retail 0x0051B5B5, 821 bytes: "AptQuitMenu::OnInitialized". Disables
// what the current game cannot do -- in a multiplayer game or a replay
// restart (or, in a war of the ring game, exit), save unless a saveable war
// of the ring game still has players to lose, and load; in a war of the
// ring game restart and the save buttons by the living world's state --
// then labels the restart button Restart, Forfeit or Surrender.
// Ported from U1 r6 bank (ws/u1/build/W7-U1/wins/pc_0x0051b5b5.cpp, exact
// nd0 via chain.py barrier after the else-branch livingWorld local).
void AptQuitMenu::OnInitialized(const char *unused_in)
{
	const char * unused = unused_in;
	if ((TheGameLogic && TheGameLogic->isInMultiplayerGame())
		|| (TheRecorder && TheRecorder->getMode() == RECORDERMODETYPE_PLAYBACK))
	{
		if (TheGameLogic->m_114 != 3)
		{
			if (TheLivingWorldLogic && ((BfmeSelectionState *)TheLivingWorldLogic)->isSelectionLocked())
				DisableButton(this, "ExitMission");
		}
		else
			DisableButton(this, "Restart");
		if (!((Rva00210C66CmpBoolField *)TheGameLogic)->get() || !TheLivingWorldLogic || !((BfmeSelectionState *)TheLivingWorldLogic)->isSelectionLocked())
			DisableButton(this, "Save");
		if (((Rva00210C66CmpBoolField *)TheGameLogic)->get() && TheLivingWorldLogic)
		{
			if (((Rva002BA8F1Logic *)TheLivingWorldLogic)->rva002B5256(false) < ((Rva002BA8F1Logic *)TheLivingWorldLogic)->rva002B5256(true))
				DisableButton(this, "Save");
		}
		DisableButton(this, "Load");
	}
	else
	{
		BfmeSelectionState *livingWorld = ((BfmeSelectionState *)TheLivingWorldLogic);
		_ReadWriteBarrier();
		if (livingWorld && livingWorld->isSelectionLocked())
		{
			if (!TheGameLogic || TheGameLogic->m_114 == 3
				|| (unsigned char)((Rva002B254F *)livingWorld)->rva002B254F() != 0)
				DisableButton(this, "Restart");
			int count = ((Rva002D3627Host *)TheLivingWorld)->m_14;
			if (count == 0)
			{
				DisableButton(this, "Save");
				DisableButton(this, "Load");
			}
			if ((unsigned char)((Rva002B254F *)TheLivingWorldLogic)->rva002B254F() != 0)
				DisableButton(this, "Save");
		}
	}
	if (TheGameLogic && TheGameLogic->m_114 != 3)
	{
		if (TheLivingWorldLogic && ((BfmeSelectionState *)TheLivingWorldLogic)->isSelectionLocked())
		{
			AsciiString key("APT:RestartOrSurrender");
			g_bfmeAptWindowManager->bfmeSetText(key, TheGameText->fetch("APT:Surrender"), false);
		}
		else
		{
			AsciiString key("APT:RestartOrSurrender");
			g_bfmeAptWindowManager->bfmeSetText(key, TheGameText->fetch("APT:Forfeit"), false);
		}
	}
	else
	{
		AsciiString key("APT:RestartOrSurrender");
		g_bfmeAptWindowManager->bfmeSetText(key, TheGameText->fetch("APT:Restart"), false);
	}
}
