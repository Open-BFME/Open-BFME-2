// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /O1 /G6 /arch:SSE
// stlport
//
// AptStrategicPlayerStatus::AptStrategicPlayerStatus, retail 0x00523825
// (1327 bytes).
//
// Identity (target evidence): WorldBuilder's AptStrategicPlayerStatus.cpp
// names the body; it installs the two vftables 0x00C67C34/0x00C67C30 the
// rowed destructor 0x00523775 expects, sets the singleton 0x00E04934 that
// destructor clears, and binds "StrategicPlayerStatus::..." callbacks to the
// rowed StrategicPlayerStatus handlers (OnCloseWindow 0x00523481, the colour
// and status queries 0x0052373A/0x00523438). The binding idiom is the one
// the matched AptScoreScreen constructor 0x0051D1E6 uses.
//
// No Zero Hour counterpart; the player loop, faction icons and scenario
// texts are read from the retail bytes. Field names beyond the rowed
// callbacks' are address-derived.

#include <vector>
#include "unicode_string.h"
#include "ascii_string.h"

class GameWindow
{
protected:
	virtual ~GameWindow();
private:
	unsigned char m_pad004[0x218 - 4];
};

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
class AptOverButtonHandler;

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

// The image binder at +0x40 of the Apt window half (0x00524306 family):
// window name to image name.
class Rva00524306
{
public:
	void rva00524767(const AsciiString &name, const AsciiString &image);
private:
	_STL::vector<AsciiString> m_names;
};

class Rva005248D0
{
public:
	virtual ~Rva005248D0();
	AptCommandMapAdder m_commandMaps; // +0x04
	AptExternHandlerAdder m_externHandlers; // +0x10
	AptOverButtonHandlerAdder m_overButtonHandlers; // +0x1C
private:
	unsigned char m_pad028[0x40 - 0x28];
public:
	Rva00524306 m_imageAdder; // +0x40
private:
	unsigned char m_pad04C[0x58 - 0x4C];
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

class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &name, const UnicodeString &text, bool placeholder);
};

extern BfmeAptWindowManager *g_bfmeAptWindowManager;

class GameTextInterface
{
public:
#define TEXT_SLOT(N) virtual void slot##N();
	TEXT_SLOT(00) TEXT_SLOT(01) TEXT_SLOT(02) TEXT_SLOT(03) TEXT_SLOT(04) TEXT_SLOT(05) TEXT_SLOT(06)
	TEXT_SLOT(07) TEXT_SLOT(08) TEXT_SLOT(09) TEXT_SLOT(10) TEXT_SLOT(11) TEXT_SLOT(12) TEXT_SLOT(13)
#undef TEXT_SLOT
	// Overloaded virtuals are laid out in reverse declaration order: the
	// AsciiString fetch is vslot 14, the char one vslot 15.
	virtual UnicodeString fetch(const char *label, bool *exists = 0);
	virtual UnicodeString fetch(const AsciiString &label, bool *exists = 0);
};

extern GameTextInterface *TheGameText;

class RGBColor
{
public:
	int getAsInt() const;
	float red, green, blue;
};

struct Rva00523825Faction
{
	unsigned char m_pad00[0x20];
	AsciiString m_iconName; // +0x20
};

class Rva002E2903Player
{
public:
	unsigned char m_pad000[0x1C];
	UnicodeString m_displayName; // +0x1C
	unsigned char m_pad020[0x34 - 0x20];
	int m_34; // +0x34, the alliance compared against the local player's
	unsigned char m_pad038[0x40 - 0x38];
	Rva00523825Faction *m_faction; // +0x40
	unsigned char m_pad044[0x184 - 0x44];
	RGBColor m_color; // +0x184
	unsigned char m_pad190[0x3C4 - 0x190];
	unsigned char m_3C4; // +0x3C4, nonzero once the player is dead
	unsigned char m_3C5; // +0x3C5, nonzero once the player has left
};

class Rva002E1001
{
public:
	int rva002E1001(); // WB LivingWorldPlayer::GetNumRegionsOwned
};

struct Rva002E0D02Arg;
int CountOwnedUnits(Rva002E0D02Arg *player);

class Rva002BA8F1Logic
{
public:
	Rva002E2903Player *rva002B52A8(int index);
	unsigned char m_pad000[0x8C];
	_STL::vector<Rva002E2903Player *> m_players; // +0x8C
	Rva002E2903Player *m_localPlayer; // +0x98
};

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

class Rva004FCB61
{
public:
	UnicodeString rva004fcb61();
};

class Rva004FCB85
{
public:
	UnicodeString rva004fcb85();
};

class Rva005E755E
{
public:
	UnicodeString rva005e755e();
};

// The current campaign scenario (+0x1C of the selected campaign entry).
struct Rva00523825Scenario
{
	unsigned char m_pad00[4];
	AsciiString m_name; // +0x04
};

struct Rva00523825Campaign
{
	unsigned char m_pad00[0x1C];
	Rva00523825Scenario *m_scenario; // +0x1C
};

class Rva00E02D6C
{
public:
	unsigned char m_pad00[0x10];
	int m_current; // +0x10
	Rva00523825Campaign **m_campaigns; // +0x14
	Rva00523825Campaign **getCampaigns() const { return m_campaigns; }
};

extern Rva00E02D6C *TheCampaignManager;

struct GlobalA04934;
extern GlobalA04934 *g_Va00A04934;


class StrategicPlayerStatus
{
public:
	void OnInitialized(const char *unused);
	void OnCloseWindow(const char *unused);
	void rva00523438(int query, char *value, bool set);
	void rva0052373A(int query, char *value, bool set);
};

// The constructor binds "StrategicPlayerStatus::OnInitialized" to the
// shared empty RET 4 body at 0x0047A69C.
void StrategicPlayerStatus::OnInitialized(const char *unused)
{
}

// Retail 0x005235D5, 357 bytes: fills one player's "%s:Name_%d",
// "%s:Territories_%d", "%s:Regions_%d" and "%s:Status_%d" texts. File
// static, compiled before its caller: MSVC passes the player in ESI.
static void Rva005235D5(Rva002E2903Player *player, int index, const char *kind)
{
	AsciiString window;
	UnicodeString text;
	window.format("%s:Name_%d", kind, index);
	g_bfmeAptWindowManager->bfmeSetText(window, player->m_displayName, false);
	window.format("%s:Territories_%d", kind, index);
	text.format(L"%d", ((Rva002E1001 *)player)->rva002E1001());
	g_bfmeAptWindowManager->bfmeSetText(window, text, false);
	window.format("%s:Regions_%d", kind, index);
	text.format(L"%d", CountOwnedUnits((Rva002E0D02Arg *)player));
	g_bfmeAptWindowManager->bfmeSetText(window, text, false);
	window.format("%s:Status_%d", kind, index);
	bool present = player->m_3C5 == 0;
	bool alive = player->m_3C4 == 0;
	const char *label;
	if (present)
	{
		if (alive)
			label = "GUI:PlayerAlive";
		else
			label = "GUI:PlayerDead";
	}
	else
	{
		label = "GUI:PlayerGone";
	}
	g_bfmeAptWindowManager->bfmeSetText(window, TheGameText->fetch(label), false);
}

// The status queries, by index (0x00DD17C8).
static const char *s_statusNames[] = { "PlayerIndex", "NumAlliedPlayers", "NumEnemyPlayers" };

class __multiple_inheritance AptStrategicPlayerStatus : public _bfme_AptGameWindow
{
public:
	AptStrategicPlayerStatus(void *context);
	virtual ~AptStrategicPlayerStatus();
private:
	int m_playerIndex; // +0x27C
	int m_numAllied; // +0x280
	int m_numEnemies; // +0x284
	_STL::vector<unsigned int> m_colors; // +0x288
};

#pragma pointers_to_members(full_generality, multiple_inheritance)
AptStrategicPlayerStatus::AptStrategicPlayerStatus(void *context)
	: _bfme_AptGameWindow(context),
	  m_playerIndex(0),
	  m_numAllied(0),
	  m_numEnemies(0)
{
	if (g_Va00A04934 != 0 || TheLivingWorldLogic == 0 || TheCampaignManager == 0)
		return;
	g_Va00A04934 = (GlobalA04934 *)this;
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&StrategicPlayerStatus::OnInitialized);
		AsciiString name("StrategicPlayerStatus::OnInitialized");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&StrategicPlayerStatus::OnCloseWindow);
		AsciiString name("StrategicPlayerStatus::OnCloseWindow");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	AsciiString name;
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&StrategicPlayerStatus::rva0052373A);
		int index = 0;
		FunctorBinding binding = MakeBinding(method, reinterpret_cast<FunctorTarget *>(this));
		for (; index < 6; ++index)
		{
			name.format("StrategicPlayerStatus::EnemyColor_%d", index + 6);
			m_externHandlers.AddExternHandler(name, index, AptRef<AptExternHandler>(binding));
		}
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&StrategicPlayerStatus::rva00523438);
		int index = 0;
		FunctorBinding binding = MakeBinding(method, reinterpret_cast<FunctorTarget *>(this));
		for (; index < 3; ++index)
		{
			name.format("StrategicPlayerStatus::%s", s_statusNames[index]);
			m_externHandlers.AddExternHandler(name, index, AptRef<AptExternHandler>(binding));
		}
	}

	Rva002E2903Player *localPlayer = ((Rva002BA8F1Logic *)TheLivingWorldLogic)->m_localPlayer;
	if (localPlayer == 0)
		return;
	AsciiString unused;
	int count = ((Rva002BA8F1Logic *)TheLivingWorldLogic)->m_players.size();
	for (int i = 0; i < count; ++i)
	{
		Rva002E2903Player *player = ((Rva002BA8F1Logic *)TheLivingWorldLogic)->rva002B52A8(i);
		if (player == 0)
			continue;
		int index = 0;
		const char *kind = 0;
		if (localPlayer->m_34 == player->m_34)
		{
			index = m_numAllied++;
			kind = "Allied";
		}
		else
		{
			index = m_numEnemies++;
			kind = "Enemy";
		}
		name.format("StrategicPlayerStatus::%sColor_%d", kind, index);
		{
			FunctorMethod method = reinterpret_cast<FunctorMethod>(&StrategicPlayerStatus::rva0052373A);
			FunctorBinding binding = MakeBinding(method, reinterpret_cast<FunctorTarget *>(this));
			m_externHandlers.AddExternHandler(name, i, AptRef<AptExternHandler>(binding));
		}
		m_colors.push_back(player->m_color.getAsInt() | 0xff000000);
		Rva00523825Faction *faction = player->m_faction;
		AsciiString icon;
		icon.format("%sFactionIcon_%d", kind, index);
		m_imageAdder.rva00524767(icon, faction->m_iconName);
		Rva005235D5(player, index, kind);
	}

	Rva00523825Campaign *campaign = TheCampaignManager->getCampaigns()[TheCampaignManager->m_current];
	Rva00523825Scenario *scenario = campaign->m_scenario;
	if (scenario == 0)
		return;
	UnicodeString title = TheGameText->fetch(scenario->m_name);
	{
		AsciiString window("StrategicPlayerStatus:ScenarioName");
		g_bfmeAptWindowManager->bfmeSetText(window, title, false);
	}
	{
		AsciiString window("StrategicPlayerStatus:Objectives");
		g_bfmeAptWindowManager->bfmeSetText(window, ((Rva004FCB61 *)scenario)->rva004fcb61(), false);
	}
	{
		AsciiString window("StrategicPlayerStatus:ScenarioFiction");
		g_bfmeAptWindowManager->bfmeSetText(window, ((Rva005E755E *)scenario)->rva005e755e(), false);
	}
	{
		AsciiString window("StrategicPlayerStatus:GameType");
		g_bfmeAptWindowManager->bfmeSetText(window, ((Rva004FCB85 *)scenario)->rva004fcb85(), false);
	}
	UnicodeString numPlayers;
	numPlayers.format(L"%d", m_numEnemies + m_numAllied);
	{
		AsciiString window("StrategicPlayerStatus:NumPlayers");
		g_bfmeAptWindowManager->bfmeSetText(window, numPlayers, false);
	}
}
