// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// BFME2's in-game player status / objectives screen (PlayerStatus.apt and
// Objectives.apt share it): its constructor, which binds the callbacks of
// AptPlayerStatusCallbacks.cpp by name, its extern query, its player
// table refresh and the opener that pushes it. BFME 1's
// AptScreenFactories.cpp (0x0052C660), AptObjectivesMenu.cpp (0x0052C220)
// and Rva0052B2A0Step.cpp are the donors.

#include <vector>
#include "ascii_string.h"
#include "unicode_string.h"

extern "C" void *__cdecl memset(void *destination, int value, unsigned int count);

class GameWindow
{
protected:
	virtual ~GameWindow();

private:
	unsigned char m_pad004[0x218 - 4];
};

// The Apt window manager (VA 0x00DFE4CC) and its background switch.
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

class Rva00222A8BTarget
{
public:
	void rva002233A6(int mode);
};

// The Apt callback functors (Rva0057BC63FunctorHolder.cpp, as in
// AptScoreScreenCallbacks.cpp).
class __multiple_inheritance FunctorTarget;
typedef void (FunctorTarget::*FunctorMethod)(void);

struct FunctorBinding
{
	FunctorBinding(FunctorMethod method, FunctorTarget *target) : m_target(target), m_method(method) {}

	FunctorTarget *m_target;
	unsigned int m_pad;
	FunctorMethod m_method;
};

class FunctorWrapperHead
{
public:
	void *m_vtbl;
	int m_refCount; // +0x04
};

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

class AptScreenInitGadgets;
void _bfme_setAptScreenRef(const AsciiString &name, AptRef<AptScreenInitGadgets> ref);

// The Apt screen base (BfmeAptGameWindowDestructor.cpp): a 0x218-byte
// GameWindow and, at +0x218, the 0x58-byte callback registry.
class Rva005248D0
{
public:
	virtual ~Rva005248D0();

	AptCommandMapAdder m_commandMaps; // +0x04
	AptExternHandlerAdder m_externHandlers; // +0x10

private:
	unsigned char m_pad01C[0x58 - 0x1C];
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

// The colors' element: a 4-byte value whose push_back is the folded copy
// at 0x002E01C6, not vector<int>'s (0x00688940); its type is unknown.
enum Rva004E476CColor
{
};

// The open player status screen (VA 0x00E04450).
struct GlobalA04450;
extern GlobalA04450 *g_Va00A04450;

class GameWindow;

class AptPlayerStatus : public _bfme_AptGameWindow
{
public:
	AptPlayerStatus(void *context);
	virtual ~AptPlayerStatus();

	// AptPlayerStatusCallbacks.cpp.
	void InitGadgets(const char *name, void *argument, GameWindow *window);
	void rva004E4A34(const char *unused);
	void PlayerColor(int slot, char *result, bool set);
	void Objective(int row, char *result, bool skip);
	// "AptObjectivesMenu::ReturnToGame" (rowed as the stdcall
	// Rva004E40A6Enable), pinned by address.
	void rva004E40A6(const char *unused);
	// Unrowed 0x004E434C: "NumOfPlayers", "InSkirmish" and
	// "AptObjectivesMenu::InputEnabled" by index, pinned by address.
	void rva004E434C(int query, char *result, bool set);
	// "Objective%d", the row's objective text
	// (AptPlayerStatusObjectiveText.cpp).
	void rva004E4553(int row, char *result, bool set);
	// Unrowed 0x004E476C: fills the player table from the game slots.
	void rva004E476C();
	// "PlayerTable:<row>:<column>" (rowed as the stdcall
	// Rva004E44FBSet; it ignores this), pinned by address.
	void rva004E44FB(int row, int column, const UnicodeString &text);

private:
	friend void Rva004E41AB();

	_STL::vector<Rva004E476CColor> m_colors; // +0x27C
	int m_state; // +0x288
	GameWindow *m_mute[8]; // +0x28C
	signed char m_slot[8]; // +0x2AC
};

extern "C" __declspec(dllimport) int __cdecl sprintf(char *buffer, const char *format, ...);

// The game mode at +0x110 (2 skirmish, 6 the one where the UI's +0x16
// flag decides whether input is enabled).
class GameLogic
{
public:
	bool isInMultiplayerGame();
	// The pinned pause setter (paused, reason, pause music).
	void rva0023CD9E(bool paused, int reason, bool music);
	// The pinned multiplayer-or-skirmish predicate.
	char rva0023C6FD();

	unsigned char m_pad000[0x6D];
	bool m_6d; // +0x6D
	unsigned char m_pad06e[0x110 - 0x6E];
	int m_gameMode; // +0x110
};

extern GameLogic *TheGameLogic;

class Rva0023C902
{
public:
	int rva0023C902();
};

// The +0x10 view TheInGameUI's 0x000CF155 returns and the folded forwarder
// to its vslot 3 (0x005CB265), both pinned (as in AptQuitMenuCallbacks.cpp).
class Rva005CB260;

class Rva005CB265
{
public:
	virtual int rva005CB265();
};

// TheInGameUI (0x00DFEDF0): vslot 94 shows or hides the menu, vslot 95
// reports one already up.
class InGameUI
{
public:
#define UI_SLOT(N) virtual void slot##N();
	UI_SLOT(00) UI_SLOT(01) UI_SLOT(02) UI_SLOT(03) UI_SLOT(04) UI_SLOT(05) UI_SLOT(06) UI_SLOT(07)
	UI_SLOT(08) UI_SLOT(09) UI_SLOT(10) UI_SLOT(11) UI_SLOT(12) UI_SLOT(13) UI_SLOT(14) UI_SLOT(15)
	UI_SLOT(16) UI_SLOT(17) UI_SLOT(18) UI_SLOT(19) UI_SLOT(20) UI_SLOT(21) UI_SLOT(22) UI_SLOT(23)
	UI_SLOT(24) UI_SLOT(25) UI_SLOT(26) UI_SLOT(27) UI_SLOT(28) UI_SLOT(29) UI_SLOT(30) UI_SLOT(31)
	UI_SLOT(32) UI_SLOT(33) UI_SLOT(34) UI_SLOT(35) UI_SLOT(36) UI_SLOT(37) UI_SLOT(38) UI_SLOT(39)
	UI_SLOT(40) UI_SLOT(41) UI_SLOT(42) UI_SLOT(43) UI_SLOT(44) UI_SLOT(45) UI_SLOT(46) UI_SLOT(47)
	UI_SLOT(48) UI_SLOT(49) UI_SLOT(50) UI_SLOT(51) UI_SLOT(52) UI_SLOT(53) UI_SLOT(54) UI_SLOT(55)
	UI_SLOT(56) UI_SLOT(57) UI_SLOT(58) UI_SLOT(59) UI_SLOT(60) UI_SLOT(61) UI_SLOT(62) UI_SLOT(63)
	UI_SLOT(64) UI_SLOT(65) UI_SLOT(66) UI_SLOT(67) UI_SLOT(68) UI_SLOT(69) UI_SLOT(70) UI_SLOT(71)
	UI_SLOT(72) UI_SLOT(73) UI_SLOT(74) UI_SLOT(75) UI_SLOT(76) UI_SLOT(77) UI_SLOT(78) UI_SLOT(79)
	UI_SLOT(80) UI_SLOT(81) UI_SLOT(82) UI_SLOT(83) UI_SLOT(84) UI_SLOT(85) UI_SLOT(86) UI_SLOT(87)
	UI_SLOT(88) UI_SLOT(89) UI_SLOT(90) UI_SLOT(91) UI_SLOT(92) UI_SLOT(93)
#undef UI_SLOT
	virtual void slot94(bool visible);
	virtual bool slot95();

	Rva005CB260 *rva000CF155();

	unsigned char m_pad04[0x16 - 4];
	bool m_16; // +0x16
};

extern InGameUI *TheInGameUI;

// The extern queries' names, by index (0x00C621A8).
static const char *const s_externNames[] = { "NumOfPlayers", "InSkirmish", "AptObjectivesMenu::InputEnabled" };

// Retail 0x004E4A45, 954 bytes: the screen's constructor. The first one
// opened becomes g_Va00A04450 and binds its callbacks by name under both
// screens' prefixes, the three extern queries, "Objective1".."12" with
// their "Status" twins, "ScoreScreen:PlayerColor:0".."7", switches the
// window manager's background and binds InitGadgets as its screen
// reference.
#pragma pointers_to_members(full_generality, multiple_inheritance)
AptPlayerStatus::AptPlayerStatus(void *context)
	: _bfme_AptGameWindow(context),
	  m_state(2)
{
	if (g_Va00A04450 != 0)
		return;
	g_Va00A04450 = (GlobalA04450 *)this;
	memset(m_mute, 0, sizeof(m_mute));
	memset(m_slot, 0, sizeof(m_slot));
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptPlayerStatus::rva004E4A34);
		AsciiString name("AptObjectivesMenu::OnInitialized");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptPlayerStatus::rva004E40A6);
		AsciiString name("AptObjectivesMenu::ReturnToGame");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptPlayerStatus::rva004E4A34);
		AsciiString name("AptPlayerStatus::OnInitialized");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptPlayerStatus::rva004E40A6);
		AsciiString name("AptPlayerStatus::ReturnToGame");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptPlayerStatus::rva004E434C);
		int query = 0;
		FunctorBinding binding = MakeBinding(method, reinterpret_cast<FunctorTarget *>(this));
		for (; query < 3; ++query)
		{
			AsciiString name(s_externNames[query]);
			m_externHandlers.AddExternHandler(name, query, AptRef<AptExternHandler>(binding));
		}
	}
	AsciiString name;
	{
		FunctorMethod textMethod = reinterpret_cast<FunctorMethod>(&AptPlayerStatus::rva004E4553);
		int index = 0;
		FunctorBinding text = MakeBinding(textMethod, reinterpret_cast<FunctorTarget *>(this));
		FunctorMethod statusMethod = reinterpret_cast<FunctorMethod>(&AptPlayerStatus::Objective);
		FunctorBinding status = MakeBinding(statusMethod, reinterpret_cast<FunctorTarget *>(this));
		for (; index < 12; ++index)
		{
			name.format("Objective%d", index + 1);
			m_externHandlers.AddExternHandler(name, index, AptRef<AptExternHandler>(text));
			name.concat("Status");
			m_externHandlers.AddExternHandler(name, index, AptRef<AptExternHandler>(status));
		}
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptPlayerStatus::PlayerColor);
		int slot = 0;
		FunctorBinding binding = MakeBinding(method, reinterpret_cast<FunctorTarget *>(this));
		for (; slot < 8; ++slot)
		{
			name.format("ScoreScreen:PlayerColor:%d", slot);
			m_externHandlers.AddExternHandler(name, slot, AptRef<AptExternHandler>(binding));
		}
	}
	((Rva00222A8BTarget *)g_bfmeAptWindowManager)->rva002233A6(2);
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptPlayerStatus::InitGadgets);
		AsciiString screen("AptPlayerStatus::InitGadgets");
		_bfme_setAptScreenRef(screen, AptRef<AptScreenInitGadgets>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
}

// Retail 0x004E434C, 166 bytes: "NumOfPlayers" (the number of colors once
// the rows are up), "InSkirmish" and "AptObjectivesMenu::InputEnabled",
// answered "0" or "1" ("0" when set).
void AptPlayerStatus::rva004E434C(int query, char *result, bool set)
{
	result[0] = '0';
	result[1] = 0;
	switch (query)
	{
	case 0:
		if (!set && m_state == 1)
			sprintf(result, "%d", m_colors.size());
		break;
	case 1:
		if (!set)
			strcpy(result, TheGameLogic && TheGameLogic->m_gameMode == 2 ? "1" : "0");
		break;
	case 2:
		if (!set)
			strcpy(result, TheGameLogic->m_gameMode != 6 || TheInGameUI->m_16 ? "1" : "0");
		break;
	}
}

enum NameKeyType
{
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Player
{
public:
	// The pinned 7-byte flag getter (BFME 1's isPlayerObserver).
	bool rva002AA223() const;
};

class PlayerList
{
public:
	Player *findPlayerWithNameKey(NameKeyType key);
};

extern PlayerList *ThePlayerList;

class GameSlot
{
public:
	bool isOccupied() const;
	bool isHuman() const;
	bool isAI() const;
	UnicodeString getApparentPlayerTemplateDisplayName() const;
	int getApparentColor() const;
	const UnicodeString &getName() const { return m_name; }

	unsigned char m_pad00[0x1C];
	int m_teamNumber; // +0x1C
	unsigned char m_pad20[0x30 - 0x20];
	UnicodeString m_name; // +0x30
	AsciiString m_playerName; // +0x34
};

class GameInfo
{
public:
	GameSlot *getSlot(int index);
	const GameSlot *getConstSlot(int index) const;
};

extern GameInfo *TheGameInfo;

// TheNetwork's isPlayerConnected (vslot 51).
class NetworkInterface
{
public:
#define NET_SLOT(N) virtual void slot##N();
	NET_SLOT(00) NET_SLOT(01) NET_SLOT(02) NET_SLOT(03) NET_SLOT(04) NET_SLOT(05) NET_SLOT(06) NET_SLOT(07)
	NET_SLOT(08) NET_SLOT(09) NET_SLOT(10) NET_SLOT(11) NET_SLOT(12) NET_SLOT(13) NET_SLOT(14) NET_SLOT(15)
	NET_SLOT(16) NET_SLOT(17) NET_SLOT(18) NET_SLOT(19) NET_SLOT(20) NET_SLOT(21) NET_SLOT(22) NET_SLOT(23)
	NET_SLOT(24) NET_SLOT(25) NET_SLOT(26) NET_SLOT(27) NET_SLOT(28) NET_SLOT(29) NET_SLOT(30) NET_SLOT(31)
	NET_SLOT(32) NET_SLOT(33) NET_SLOT(34) NET_SLOT(35) NET_SLOT(36) NET_SLOT(37) NET_SLOT(38) NET_SLOT(39)
	NET_SLOT(40) NET_SLOT(41) NET_SLOT(42) NET_SLOT(43) NET_SLOT(44) NET_SLOT(45) NET_SLOT(46) NET_SLOT(47)
	NET_SLOT(48) NET_SLOT(49) NET_SLOT(50)
#undef NET_SLOT
	virtual bool isPlayerConnected(int slot);
};

extern NetworkInterface *TheNetwork;

// The victory conditions (VA 0x00E03138): vslot 16 asks whether a player
// has been defeated.
struct UnknownE03138
{
#define VICTORY_SLOT(N) virtual void slot##N();
	VICTORY_SLOT(00) VICTORY_SLOT(01) VICTORY_SLOT(02) VICTORY_SLOT(03) VICTORY_SLOT(04) VICTORY_SLOT(05)
	VICTORY_SLOT(06) VICTORY_SLOT(07) VICTORY_SLOT(08) VICTORY_SLOT(09) VICTORY_SLOT(10) VICTORY_SLOT(11)
	VICTORY_SLOT(12) VICTORY_SLOT(13) VICTORY_SLOT(14) VICTORY_SLOT(15)
#undef VICTORY_SLOT
	virtual bool hasBeenDefeated(Player *player);
};

extern UnknownE03138 *g_00E03138;

// TheGameText's fetch by label (vslot 14).
class GameTextInterface
{
public:
#define TEXT_SLOT(N) virtual void slot##N();
	TEXT_SLOT(00) TEXT_SLOT(01) TEXT_SLOT(02) TEXT_SLOT(03) TEXT_SLOT(04) TEXT_SLOT(05) TEXT_SLOT(06)
	TEXT_SLOT(07) TEXT_SLOT(08) TEXT_SLOT(09) TEXT_SLOT(10) TEXT_SLOT(11) TEXT_SLOT(12) TEXT_SLOT(13)
#undef TEXT_SLOT
	virtual UnicodeString fetch(const AsciiString &label, bool *exists = 0);
};

extern GameTextInterface *TheGameText;

class MultiplayerColorDefinition
{
public:
	unsigned char m_pad00[0x10];
	int m_color; // +0x10
};

class MultiplayerSettings
{
public:
	MultiplayerColorDefinition *getColor(int index);
};

extern MultiplayerSettings *TheMultiplayerSettings;

// Retail 0x004E476C, 712 bytes: on the PlayerStatus screen (+0x288 == 1),
// one table row per occupied slot whose player exists: name, faction, team
// and state, the player's color, and the slot behind the row (-1 for the
// unused rows). BFME 1's AptObjectivesMenu.cpp (0x0052C220) is the donor.
void AptPlayerStatus::rva004E476C()
{
	if (m_state != 1)
		return;
	int row = 0;
	for (int i = 0; i < 8; ++i)
	{
		const GameSlot *slot = TheGameInfo->getConstSlot(i);
		if (!slot || !slot->isOccupied())
			continue;
		AsciiString name = TheGameInfo->getSlot(i)->m_playerName;
		if (name.isEmpty())
			continue;
		Player *player = ThePlayerList->findPlayerWithNameKey(TheNameKeyGenerator->nameToKey(name));
		if (!player)
			continue;
		bool connected = false;
		if ((TheNetwork && TheNetwork->isPlayerConnected(i)) || (!TheNetwork && slot->isHuman()))
			connected = true;
		if (slot->isAI())
			connected = true;
		bool alive = !g_00E03138->hasBeenDefeated(player);
		bool observer = player->rva002AA223();
		rva004E44FB(row, 0, slot->getName());
		rva004E44FB(row, 1, slot->getApparentPlayerTemplateDisplayName());
		AsciiString team;
		team.format("Team:%d", slot->m_teamNumber + 1);
		if (slot->isAI() && slot->m_teamNumber == -1)
			team = "Team:AI";
		rva004E44FB(row, 2, TheGameText->fetch(team));
		team = "";
		if (connected)
		{
			if (alive)
				team = "GUI:PlayerAlive";
			else if (observer)
				team = "GUI:PlayerObserver";
			else
				team = "GUI:PlayerDead";
		}
		else
		{
			if (observer)
				team = "GUI:PlayerObserverGone";
			else
				team = "GUI:PlayerGone";
		}
		rva004E44FB(row, 3, TheGameText->fetch(team));
		m_colors.push_back((Rva004E476CColor)TheMultiplayerSettings->getColor(slot->getApparentColor())->m_color);
		m_slot[row] = (signed char)i;
		++row;
	}
	for (; row < 8; ++row)
		m_slot[row] = -1;
}

// The objectives gate singleton (Rva0050E9D3Enable.cpp): its +4 flag
// allows the screen.
void *Rva004E4179Get();

struct Rva004E4179Gate
{
	int m_0;
	bool m_enabled; // +0x04
};

// The in-game chat close (BFME 1's HideInGameChat).
void Rva004E855CClose();

class ScriptEngine
{
public:
	unsigned char m_pad00000[0x1A104];
	int m_1a104; // +0x1A104, negative when no script holds the screen
};

extern ScriptEngine *TheScriptEngine;

class GameWindowTransitionsHandler
{
public:
	bool isFinished();
};

extern GameWindowTransitionsHandler *TheTransitionHandler;

// TheDisplay's vslots 87 and 88 (a movie or a letterbox up).
class Display
{
public:
#define DISPLAY_SLOT(N) virtual void slot##N();
	DISPLAY_SLOT(00) DISPLAY_SLOT(01) DISPLAY_SLOT(02) DISPLAY_SLOT(03) DISPLAY_SLOT(04) DISPLAY_SLOT(05)
	DISPLAY_SLOT(06) DISPLAY_SLOT(07) DISPLAY_SLOT(08) DISPLAY_SLOT(09) DISPLAY_SLOT(10) DISPLAY_SLOT(11)
	DISPLAY_SLOT(12) DISPLAY_SLOT(13) DISPLAY_SLOT(14) DISPLAY_SLOT(15) DISPLAY_SLOT(16) DISPLAY_SLOT(17)
	DISPLAY_SLOT(18) DISPLAY_SLOT(19) DISPLAY_SLOT(20) DISPLAY_SLOT(21) DISPLAY_SLOT(22) DISPLAY_SLOT(23)
	DISPLAY_SLOT(24) DISPLAY_SLOT(25) DISPLAY_SLOT(26) DISPLAY_SLOT(27) DISPLAY_SLOT(28) DISPLAY_SLOT(29)
	DISPLAY_SLOT(30) DISPLAY_SLOT(31) DISPLAY_SLOT(32) DISPLAY_SLOT(33) DISPLAY_SLOT(34) DISPLAY_SLOT(35)
	DISPLAY_SLOT(36) DISPLAY_SLOT(37) DISPLAY_SLOT(38) DISPLAY_SLOT(39) DISPLAY_SLOT(40) DISPLAY_SLOT(41)
	DISPLAY_SLOT(42) DISPLAY_SLOT(43) DISPLAY_SLOT(44) DISPLAY_SLOT(45) DISPLAY_SLOT(46) DISPLAY_SLOT(47)
	DISPLAY_SLOT(48) DISPLAY_SLOT(49) DISPLAY_SLOT(50) DISPLAY_SLOT(51) DISPLAY_SLOT(52) DISPLAY_SLOT(53)
	DISPLAY_SLOT(54) DISPLAY_SLOT(55) DISPLAY_SLOT(56) DISPLAY_SLOT(57) DISPLAY_SLOT(58) DISPLAY_SLOT(59)
	DISPLAY_SLOT(60) DISPLAY_SLOT(61) DISPLAY_SLOT(62) DISPLAY_SLOT(63) DISPLAY_SLOT(64) DISPLAY_SLOT(65)
	DISPLAY_SLOT(66) DISPLAY_SLOT(67) DISPLAY_SLOT(68) DISPLAY_SLOT(69) DISPLAY_SLOT(70) DISPLAY_SLOT(71)
	DISPLAY_SLOT(72) DISPLAY_SLOT(73) DISPLAY_SLOT(74) DISPLAY_SLOT(75) DISPLAY_SLOT(76) DISPLAY_SLOT(77)
	DISPLAY_SLOT(78) DISPLAY_SLOT(79) DISPLAY_SLOT(80) DISPLAY_SLOT(81) DISPLAY_SLOT(82) DISPLAY_SLOT(83)
	DISPLAY_SLOT(84) DISPLAY_SLOT(85) DISPLAY_SLOT(86)
#undef DISPLAY_SLOT
	virtual bool slot87();
	virtual bool slot88();
};

extern Display *TheDisplay;

// TheMouse's vslot 19 (the cursor).
class Mouse
{
public:
#define MOUSE_SLOT(N) virtual void slot##N();
	MOUSE_SLOT(00) MOUSE_SLOT(01) MOUSE_SLOT(02) MOUSE_SLOT(03) MOUSE_SLOT(04) MOUSE_SLOT(05) MOUSE_SLOT(06)
	MOUSE_SLOT(07) MOUSE_SLOT(08) MOUSE_SLOT(09) MOUSE_SLOT(10) MOUSE_SLOT(11) MOUSE_SLOT(12) MOUSE_SLOT(13)
	MOUSE_SLOT(14) MOUSE_SLOT(15) MOUSE_SLOT(16) MOUSE_SLOT(17) MOUSE_SLOT(18)
#undef MOUSE_SLOT
	virtual void slot19(int cursor);
};

extern Mouse *TheMouse;

class Shell
{
public:
	// The pinned shell show/hide.
	void rva0035C7CF(bool show);
	void push(AsciiString filename, bool shutdownImmediately);
};

extern Shell *TheShell;

// The disconnect menu (VA 0x00E048D0).
extern int g_Va00E048D0;

// Retail 0x004E41AB, 359 bytes: opens the in-game objectives (or, in
// multiplayer and skirmish, player status) screen unless one is up or
// the game is busy, pausing a single player game. Called by
// AptPalantir::OnBttnObjectives. BFME 1's Rva0052B2A0Step.cpp is the
// donor.
void Rva004E41AB()
{
	if (g_Va00A04450 != 0)
		return;
	if (!((Rva004E4179Gate *)Rva004E4179Get())->m_enabled)
		return;
	if (TheInGameUI->slot95())
		return;
	if ((unsigned char)((Rva0023C902 *)TheGameLogic)->rva0023C902())
		return;
	if (TheGameLogic->m_6d)
		return;
	if (TheScriptEngine->m_1a104 >= 0)
		return;
	if (!TheTransitionHandler->isFinished())
		return;
	if (TheDisplay != 0)
	{
		if (TheDisplay->slot88())
			return;
		if (TheDisplay->slot87())
			return;
	}
	GameLogic *logic = TheGameLogic;
	if (!logic->isInMultiplayerGame() && logic->m_gameMode != 6)
		logic->rva0023CD9E(true, 0, true);
	if (g_Va00E048D0 != 0)
		return;
	Rva004E855CClose();
	((Rva005CB265 *)TheInGameUI->rva000CF155())->Rva005CB265::rva005CB265();
	TheMouse->slot19(2);
	TheShell->rva0035C7CF(false);
	int mode;
	if (TheGameLogic->rva0023C6FD())
	{
		mode = 1;
		TheShell->push(AsciiString("PlayerStatus.apt"), false);
	}
	else
	{
		mode = 0;
		TheShell->push(AsciiString("Objectives.apt"), false);
	}
	if (g_Va00A04450 != 0)
		((AptPlayerStatus *)g_Va00A04450)->m_state = mode;
	TheInGameUI->slot94(true);
}

// Retail's strcpy call lands on the import thunk rowed as ji_00629176.
#pragma comment(linker, "/alternatename:_strcpy=?ji_00629176@@YAXXZ")
