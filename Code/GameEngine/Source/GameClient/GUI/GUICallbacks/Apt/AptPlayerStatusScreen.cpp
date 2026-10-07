// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// BFME2's in-game player status / objectives screen (PlayerStatus.apt and
// Objectives.apt share it): its constructor, which binds the callbacks of
// AptPlayerStatusCallbacks.cpp by name, its extern query and its player
// table refresh. BFME 1's AptScreenFactories.cpp (0x0052C660) and
// AptObjectivesMenu.cpp (0x0052C220) are the donors.

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
	unsigned char m_pad000[0x110];
	int m_gameMode; // +0x110
};

extern GameLogic *TheGameLogic;

class InGameUI
{
public:
	unsigned char m_pad00[0x16];
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

// Retail's strcpy call lands on the import thunk rowed as ji_00629176.
#pragma comment(linker, "/alternatename:_strcpy=?ji_00629176@@YAXXZ")
