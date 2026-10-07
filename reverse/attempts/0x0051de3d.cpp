// ?rva0051DE3D@AptScoreScreen@@QAEXXZ
// partial score=0.98 date=2026-10-07
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// BFME2's score screen Apt callbacks, 0x0051BF75 onward, bound by these
// names ("AptScoreScreen::OnInitialized" ...) as member pointers by the
// screen's registration; that binding is their only reference. The class
// is named for the strings' prefix. +0x27C is the screen's state.

#include <vector>
#include "unicode_string.h"
#include "ascii_string.h"

extern "C" int __cdecl strcmp(const char *left, const char *right);
extern "C" char *__cdecl strcpy(char *destination, const char *source);
extern "C" __declspec(dllimport) int __cdecl sprintf(char *buffer, const char *format, ...);

// The objectives summary at +0x288: a count at +4, up to eight labels at
// +8 and their checked flags at +0x28.
struct AptScoreObjectives
{
	unsigned char m_pad00[4];
	int m_count; // +0x04
	AsciiString m_labels[8]; // +0x08
	bool m_checked[8]; // +0x28
};

class BfmeKeyLC;

// The list box user data byte +0x12 the score screen sets.
struct AptScoreListData
{
	unsigned char m_pad[0x12];
	bool m_12; // +0x12
};

class GameWindow
{
public:
	int winEnable(bool enable);
	void *winGetUserData();
	void winSetUserData(void *data);

protected:
	virtual ~GameWindow();

private:
	unsigned char m_pad004[0x218 - 4];
};

void GadgetTextEntrySetText(GameWindow *textEntry, UnicodeString text);
void GadgetTextEntrySetMaxChars(BfmeKeyLC *textEntry, unsigned short maxLength);

class GameWindowManager
{
public:
#define V(n) virtual void pad##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23)
	V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31)
	V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47)
	V(48)
#undef V
	virtual int winSetFocus(GameWindow *window) = 0;
};

extern GameWindowManager *TheWindowManager;

class Rva00222A8BTarget;
extern class Rva00222A8BTarget *TheRva00222A8BTarget;

class Rva00222479ByteOneSetter
{
public:
	void enable();
};

// TheLivingWorldLogic (VA 0x00DFEF10, the ledger's g_009FEF10); its
// unrowed 0x002B3740 returns a byte of its current entry, pinned by
// address.
class Rva0020E89C;

class Rva0020EAF6View
{
public:
	Rva0020E89C *rva0020EAF6(int index);
};

class Rva002BA8F1Logic
{
public:
	bool rva002B3740();

	unsigned char m_pad000[0xB0];
	Rva0020EAF6View *m_B0; // +0xB0, the regions
	int m_B4;
	int m_B8; // +0xB8, the current region's index
};

extern class Rva002BA8F1Logic *g_009FEF10;

class Image;

// A living world region (Rva0020E89CFetch.cpp): its display name, its
// bonuses at +0x90..+0x98 and its map image (Rva003F038EImageGet.cpp).
class Rva0020E89C
{
public:
	UnicodeString rva0020E89C();

	unsigned char m_pad00[0x90];
	int m_90; // +0x90, the resource bonus
	int m_94; // +0x94, the army bonus
	int m_98; // +0x98, the legendary bonus
};

class Rva003F038E
{
public:
	const Image *rva003F03B9();
};

// Rva00222A8BTarget sets a named Apt image (pinned 0x002239E2);
// BfmeAptWindowManagerSetText.cpp sets a named Apt text. Both are the
// window manager at 0x00DFE4CC.
class Rva00222A8BTarget
{
public:
	void rva002239E2(const AsciiString &name, const Image *image);
};

class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &name, const UnicodeString &text, bool unused);
};

extern BfmeAptWindowManager *g_bfmeAptWindowManager;

class GameTextInterface
{
public:
	virtual ~GameTextInterface();
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	// MSVC 7.1 lays overloaded virtuals in reverse declaration order: the
	// char label fetch is slot 0x3C.
	virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
	virtual UnicodeString fetch(const AsciiString &label, bool *exists = 0) = 0;
};

extern GameTextInterface *TheGameText;

// A persistent unit of an army: its template's name at +4 and, at +0xA8,
// whether its veterancy upgraded on the map.
struct AptScorePersistentUnit
{
	int m_00;
	AsciiString m_templateName; // +0x04
	unsigned char m_pad08[0xA8 - 0x08];
	bool m_upgraded; // +0xA8
};

// An army (Rva0040CC0EIndexedGetters.cpp): its units are the second
// dwords of the eight-byte entries at +0x40.
struct Rva0040CC0EEntry
{
	int first;
	int second;
};

class Rva0040CB2CIndexedField
{
public:
	int get(int index) const;

	unsigned char m_pad[0x40];
	_STL::vector<Rva0040CC0EEntry> m_entries; // +0x40
};

class GameLogic
{
public:
	// Unrowed 0x002401C0: a copy of the armies of the army summary at
	// +0x184; pinned by address.
	_STL::vector<Rva0040CB2CIndexedField *> rva002401C0();
};

extern GameLogic *TheGameLogic;

class ThingTemplate
{
public:
	const Image *getButtonImage();

	unsigned char m_pad000[0x113];
	unsigned char m_113; // +0x113, bit 2: a hero
	unsigned char m_pad114[0x638 - 0x114];
	int m_638; // +0x638, the hero's place in the list
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

extern ThingFactory *TheThingFactory;

// A hero of the score screen's list, sorted by its template's place
// (the folded sort 0x0051D868, the first dword) and pushed through the
// folded twelve-byte push_back 0x002DF89B; both pinned by address.
struct Rva0051DE3DHero
{
	int order;
	bool upgraded;
	const Image *image;
};

namespace _STL
{
template <class RandomAccessIter> void sort(RandomAccessIter first, RandomAccessIter last);
}

// AptHeroPowerText.cpp: one region bonus row, numbered through *index.
class Rva0051C2E2
{
public:
	void rva0051C2E2(int *index, const AsciiString &name, int bonus);
};

// The Apt callback functors (Rva0057BC63FunctorHolder.cpp, as in
// AptQuitMenuCallbacks.cpp): a binding of an object and an eight-byte
// multiple-inheritance member pointer, and the refcounted holder rowed
// 0x0057BC63 builds from it.
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

// 0x00411458 stores the reference under the name in the screen table
// (MpGameSetupSlots.cpp); pinned by address.
class AptScreenInitGadgets;
void _bfme_setAptScreenRef(const AsciiString &name, AptRef<AptScreenInitGadgets> ref);

// The Apt screen base (BfmeAptGameWindowDestructor.cpp): a 0x218-byte
// GameWindow and, at +0x218, the 0x58-byte callback registry whose adders
// sit at +0x04, +0x10 and +0x1C.
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

// "AptScoreScreen::Save" binds the time line's save-replay body 0x0051E3C3
// (AptTimeLineCallbacks.cpp), one body or two folded.
class AptTimeLine
{
public:
	void rva0051E3C3(const char *unused);
};

// The open score screen (0x00E04914), set by its constructor and cleared
// by its destructor (BfmeAptScreenScoreDestructor.cpp).
extern int g_00E04914;

class AptScoreScreen : public _bfme_AptGameWindow
{
public:
	AptScoreScreen(void *context);
	virtual ~AptScoreScreen();

	void OnInitialized(const char *unused);
	void Timeline(const char *unused);
	void RestartGame(const char *unused);
	void Continue(const char *unused);
	void InitGadgets(const char *name, void *argument, GameWindow *window);
	void RenameCancel(const char *unused);
	// Rowed in Rva0051C17EMethod.cpp.
	void OnButtonRenameAccept(int unused);
	void objectiveChecked(int index, char *result, bool skip);
	void heroVetUpgrade(int index, char *result, bool skip);
	// Unrowed 0x0051CE72: the Apt queries "ShowSaveReplay" ...
	// "NumberFormatter" by index.
	void Externs(int query, char *value, bool set);
	void rva0051DE3D();
	// Unrowed 0x0051DA24: fills the persistent units list; pinned by
	// address.
	bool rva0051DA24();

private:
	int m_state; // +0x27C
	int m_280;
	bool m_284;
	AptScoreObjectives *m_objectives; // +0x288
	_STL::vector<bool> m_heroUpgrades; // +0x28C
	GameWindow *m_units; // +0x2A0
	GameWindow *m_rename; // +0x2A4
	int m_renaming; // +0x2A8
	int m_renameIndex; // +0x2AC
	AsciiString m_2b0;
	int m_lastX; // +0x2B4
	int m_lastY; // +0x2B8
	int m_hoverFrames; // +0x2BC
	AsciiString m_tooltip; // +0x2C0
};

// Retail 0x0051BF75, 38 bytes: "AptScoreScreen::OnInitialized" focuses
// the screen's window unless a restart is pending.
void AptScoreScreen::OnInitialized(const char *unused)
{
	if (m_state != 3)
	{
		TheWindowManager->winSetFocus((GameWindow *)this);
		m_state = 1;
	}
}

// Retail 0x0051BF9B, 14 bytes: "AptScoreScreen::Timeline".
void AptScoreScreen::Timeline(const char *unused)
{
	((Rva00222479ByteOneSetter *)TheRva00222A8BTarget)->enable();
}

// Retail 0x0051BFA9, 13 bytes: "AptScoreScreen::RestartGame".
void AptScoreScreen::RestartGame(const char *unused)
{
	m_state = 3;
}

// Retail 0x0051BFB6, 28 bytes: "AptScoreScreen::Continue".
void AptScoreScreen::Continue(const char *unused)
{
	g_009FEF10->rva002B3740();
	m_state = 3;
}

// Retail 0x0051C7CC, 124 bytes: "AptScoreScreen::InitGadgets" keeps the
// "PersistentUnitsListBox" (flagging its data's +0x12) and the emptied
// "RenameUnitsTextEntry" (at most 20 characters).
void AptScoreScreen::InitGadgets(const char *name, void *argument, GameWindow *window)
{
	if (!window)
		return;
	if (strcmp(name, "PersistentUnitsListBox") == 0)
	{
		m_units = window;
		AptScoreListData *data = (AptScoreListData *)window->winGetUserData();
		data->m_12 = true;
		window->winSetUserData(data);
	}
	else if (strcmp(name, "RenameUnitsTextEntry") == 0)
	{
		m_rename = window;
		GadgetTextEntrySetText(window, UnicodeString::TheEmptyString);
		GadgetTextEntrySetMaxChars((BfmeKeyLC *)window, 20);
	}
}

// Retail 0x0051BFD2, 34 bytes: "AptScoreScreen::RenameCancel" drops the
// rename and enables the units list again.
void AptScoreScreen::RenameCancel(const char *unused)
{
	m_renaming = 0;
	m_renameIndex = -1;
	if (m_units)
		m_units->winEnable(true);
}

// Retail 0x0051BFF4, 86 bytes: "objectiveChecked%d" for each objective,
// an Apt query answering whether it was checked off.
void AptScoreScreen::objectiveChecked(int index, char *result, bool skip)
{
	if (skip)
		return;
	strcpy(result, "0");
	AptScoreObjectives *objectives = m_objectives;
	if (objectives && index >= 0 && index < objectives->m_count && index < 8)
		sprintf(result, "%d", objectives->m_checked[index] != 0);
}

// Retail 0x0051C992, 122 bytes: "heroVetUpgrade%d" for each of twelve
// heroes, an Apt query answering whether the hero's veterancy upgraded.
void AptScoreScreen::heroVetUpgrade(int index, char *result, bool skip)
{
	if (skip)
		return;
	strcpy(result, "0");
	if (index >= 0 && (unsigned int)index < m_heroUpgrades.size() && index < 12)
		sprintf(result, "%d", m_heroUpgrades[index] ? 1 : 0);
}

// The extern handlers' names, by query (0x00DD16A8).
static const char *s_externNames[] = { "ShowSaveReplay", "ShowCampaign", "heroVetCount", "PlayerFaction", "numberOfObjectives", "objectivesPerScore", "NumberFormatter" };

// Retail 0x0051D1E6, 1184 bytes: the score screen's constructor. The
// first one opened becomes g_00E04914 and binds its callbacks by name
// ("AptScoreScreen::OnInitialized" ... "AptScoreScreen::RenameCancel"),
// the seven extern queries, "objectiveChecked1".."8" and
// "heroVetUpgrade1".."12", and InitGadgets as its screen reference.
#pragma pointers_to_members(full_generality, multiple_inheritance)
AptScoreScreen::AptScoreScreen(void *context)
	: _bfme_AptGameWindow(context),
	  m_state(0),
	  m_280(2),
	  m_284(false),
	  m_objectives(0),
	  m_units(0),
	  m_rename(0),
	  m_renaming(0),
	  m_renameIndex(-1),
	  m_lastX(0),
	  m_lastY(0),
	  m_hoverFrames(0),
	  m_tooltip("APT:NULL")
{
	if (g_00E04914 != 0)
		return;
	g_00E04914 = (int)this;
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptScoreScreen::OnInitialized);
		AsciiString name("AptScoreScreen::OnInitialized");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptTimeLine::rva0051E3C3);
		AsciiString name("AptScoreScreen::Save");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptScoreScreen::Timeline);
		AsciiString name("AptScoreScreen::Timeline");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptScoreScreen::Continue);
		AsciiString name("AptScoreScreen::Continue");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptScoreScreen::RestartGame);
		AsciiString name("AptScoreScreen::RestartGame");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptScoreScreen::OnButtonRenameAccept);
		AsciiString name("AptScoreScreen::RenameAccept");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptScoreScreen::RenameCancel);
		AsciiString name("AptScoreScreen::RenameCancel");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptScoreScreen::Externs);
		int query = 0;
		FunctorBinding binding = MakeBinding(method, reinterpret_cast<FunctorTarget *>(this));
		for (; query < 7; ++query)
		{
			AsciiString name(s_externNames[query]);
			m_externHandlers.AddExternHandler(name, query, AptRef<AptExternHandler>(binding));
		}
	}
	AsciiString name;
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptScoreScreen::objectiveChecked);
		int index = 0;
		FunctorBinding binding = MakeBinding(method, reinterpret_cast<FunctorTarget *>(this));
		for (; index < 8; ++index)
		{
			name.format("objectiveChecked%d", index + 1);
			m_externHandlers.AddExternHandler(name, index, AptRef<AptExternHandler>(binding));
		}
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptScoreScreen::heroVetUpgrade);
		int index = 0;
		FunctorBinding binding = MakeBinding(method, reinterpret_cast<FunctorTarget *>(this));
		for (; index < 12; ++index)
		{
			name.format("heroVetUpgrade%d", index + 1);
			m_externHandlers.AddExternHandler(name, index, AptRef<AptExternHandler>(binding));
		}
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptScoreScreen::InitGadgets);
		AsciiString screen("AptScoreScreen::InitGadgets");
		_bfme_setAptScreenRef(screen, AptRef<AptScreenInitGadgets>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
}

// Retail 0x0051DE3D, 1061 bytes: fills the screen. Each objective's
// label is "APT:objective%d"; the heroes of the player's armies, in their
// templates' order, set the veterancy icons and the upgrade flags; in the
// living world the region names the map, lists its bonuses, shows its
// image, and in state 1 the persistent units list follows.
void AptScoreScreen::rva0051DE3D()
{
	if (!m_objectives)
		return;
	for (int i = 0; i < m_objectives->m_count; ++i)
	{
		AsciiString key;
		key.format("APT:objective%d", i);
		g_bfmeAptWindowManager->bfmeSetText(key, TheGameText->fetch(m_objectives->m_labels[i].str()), false);
	}
	if (!TheGameLogic || !TheThingFactory)
		return;
	_STL::vector<Rva0051DE3DHero> heroes;
	_STL::vector<Rva0040CB2CIndexedField *> armies = TheGameLogic->rva002401C0();
	for (unsigned int i = 0; i < armies.size(); ++i)
	{
		Rva0040CB2CIndexedField *army = armies[i];
		if (!army)
			return;
		int count = army->m_entries.size();
		for (int j = 0; j < count; ++j)
		{
			AptScorePersistentUnit *unit = (AptScorePersistentUnit *)army->get(j);
			ThingTemplate *thing = (ThingTemplate *)TheThingFactory->findTemplate(unit->m_templateName);
			if (thing && (thing->m_113 & 4))
			{
				Rva0051DE3DHero hero;
				hero.order = thing->m_638;
				hero.upgraded = unit->m_upgraded;
				hero.image = thing->getButtonImage();
				heroes.push_back(hero);
			}
		}
	}
	_STL::sort(heroes.begin(), heroes.end());
	m_heroUpgrades.clear();
	for (unsigned int k = 0; k < heroes.size(); ++k)
	{
		AsciiString key;
		key.format("SubMenus/HeroVeterancy/HeroSelection/HeroSelection%d/icon/Image", m_heroUpgrades.size() + 1);
		TheRva00222A8BTarget->rva002239E2(key, heroes[k].image);
		m_heroUpgrades.push_back(heroes[k].upgraded);
	}
	Rva002BA8F1Logic *livingWorld = g_009FEF10;
	if (livingWorld)
	{
		int id = livingWorld->m_B8;
		Rva0020EAF6View *regions = livingWorld->m_B0;
		Rva0020E89C *region = regions->rva0020EAF6(id);
		if (region)
		{
			{
				AsciiString key("APT:ScoreMapName");
				g_bfmeAptWindowManager->bfmeSetText(key, region->rva0020E89C(), false);
			}
			int index = 1;
			{
				AsciiString key("LW:RegionBonusArmy");
				((Rva0051C2E2 *)this)->rva0051C2E2(&index, key, region->m_94);
			}
			{
				AsciiString key("LW:RegionLegendaryBonus");
				((Rva0051C2E2 *)this)->rva0051C2E2(&index, key, region->m_98);
			}
			{
				AsciiString key("LW:RegionBonusResource");
				((Rva0051C2E2 *)this)->rva0051C2E2(&index, key, region->m_90);
			}
			while (index <= 3)
			{
				AsciiString key("");
				((Rva0051C2E2 *)this)->rva0051C2E2(&index, key, -1);
			}
			{
				AsciiString key("Result/Infos/ScoreMap/Picture/Image");
				TheRva00222A8BTarget->rva002239E2(key, ((Rva003F038E *)region)->rva003F03B9());
			}
			{
				AsciiString key("SubMenus/TerritoryBonus/TerritoryMap/TerritoryMap/Picture/Image");
				TheRva00222A8BTarget->rva002239E2(key, ((Rva003F038E *)region)->rva003F03B9());
			}
			if (m_280 == 1)
				rva0051DA24();
		}
	}
}

// Retail's strcpy call lands on the import thunk rowed as ji_00629176.
#pragma comment(linker, "/alternatename:_strcpy=?ji_00629176@@YAXXZ")
