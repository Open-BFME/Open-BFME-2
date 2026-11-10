// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// BFME2's score screen Apt callbacks, 0x0051BF75 onward, bound by these
// names ("AptScoreScreen::OnInitialized" ...) as member pointers by the
// screen's registration; that binding is their only reference. The class
// is named for the strings' prefix. +0x27C is the screen's state.

class Rva002BA8F1Logic;
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
// Retail keeps the STLport vector growth provider without exception guards
// (0x002A1C02), while this screen's C++ locals still need /EHs cleanup.
#include <stl/_config.h>
#pragma push_macro("_STLP_TRY")
#pragma push_macro("_STLP_UNWIND")
#undef _STLP_TRY
#undef _STLP_UNWIND
#define _STLP_TRY
#define _STLP_UNWIND(action)
#include <vector>
#pragma pop_macro("_STLP_UNWIND")
#pragma pop_macro("_STLP_TRY")
#include "unicode_string.h"
#include "ascii_string.h"
// bfme link decl-only begin
namespace _STL { template <> _Bit_iter<_Bit_reference, _Bit_reference *>::_Bit_iter(); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ??0?$_Bvector_base@V?$allocator@_N@_STL@@@_STL@@QAE@ABV?$allocator@_N@1@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> _Bvector_base<allocator<bool> >::_Bvector_base(const allocator<bool> &); }

extern "C" int __cdecl strcmp(const char *left, const char *right);
extern "C" char *__cdecl strcpy(char *destination, const char *source) throw();
extern "C" __declspec(dllimport) int __cdecl sprintf(char *buffer, const char *format, ...);

// The objectives summary at +0x288: a count at +4 and up to eight
// checked flags at +0x28.
struct AptScoreObjectives
{
	AsciiString m_faction; // +0x00, read by query PlayerFaction
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

// The Apt window manager at 0x009FE4CC, under the ledger's name.
class BfmeAptWindowManager { public: void bfmeSetText(const AsciiString &name, const UnicodeString &text, bool unused); };
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

class Rva00222479ByteOneSetter
{
public:
	void enable();
};

// TheLivingWorldLogic (VA 0x00DFEF10, the ledger's g_009FEF10); its
// unrowed 0x002B3740 returns a byte of its current entry, pinned by
// address.
class Rva002104B6
{
public:
	void *rva002104B6(void *name);
};

class Rva002BA8F1Logic
{
public:
	bool rva002B3740();

	unsigned char m_pad000[0xB0];
	Rva002104B6 *m_B0; // +0xB0, its regions by name
	int m_B4;
	int m_B8; // +0xB8, current region index
};

// The persistent-unit list box (BFME 1's ScoreScreenRva005778E0.cpp):
// Zero Hour's list box gadget API, the living world's armies of
// persistent units from GameLogic and their thing templates.
class Image;
void GadgetListBoxReset(GameWindow *listbox);
int GadgetListBoxGetNumColumns(GameWindow *listbox);
void GadgetListBoxSetColumnWidths(GameWindow *listbox, int numColumns, int *widths);
int GadgetListBoxAddEntryText(GameWindow *listbox, UnicodeString text, int color, int row, int column, bool overwrite);
int GadgetListBoxAddEntryImage(GameWindow *listbox, const Image *image, int row, int column, int height, int width, bool overwrite, int color);
// GadgetListBoxSetItemData(listbox, data, row, column).
void GadgetListBoxSetItemData(GameWindow *listbox, void *data, int row, int column);
void GadgetListBoxSetTopVisibleEntry(GameWindow *listbox, int top);

extern int g_00DD16C4;

struct AptScorePersistentUnit
{
	unsigned char m_pad00[4];
	AsciiString m_templateName; // +0x04
	unsigned char m_pad08[4];
	int m_0C;
	unsigned char m_pad10[0x94 - 0x10];
	int m_94;
	int m_98;
	int m_9C;
	UnicodeString m_name; // +0xA0
	AsciiString m_regionName; // +0xA4
	bool m_upgraded; // +0xA8
};

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

class GameLogic;
extern GameLogic *TheGameLogic;

// 0x002401C0 is rowed (Common/Rva002401C0Forward.cpp) as an address-named
// forward on GameLogic returning its army list as four-byte words; each
// word is an army record pointer here.
class Rva002401C0
{
public:
	_STL::vector<unsigned int> rva002401C0();
};

class ThingTemplate
{
public:
	const Image *getButtonImage();

	unsigned char m_pad00[0x30];
	UnicodeString m_displayName; // +0x30
	unsigned char m_pad034[0x113 - 0x34];
	unsigned char m_113; // +0x113, hero bit 2
	unsigned char m_pad114[0x638 - 0x114];
	int m_638; // +0x638, hero display order
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

extern ThingFactory *TheThingFactory;

class Rva0020E89C
{
public:
	UnicodeString rva0020E89C();
	unsigned char m_pad00[0x90];
	int m_90; // resource bonus
	int m_94; // army bonus
	int m_98; // legendary bonus
};

class Rva0051D009
{
public:
	AsciiString rva0051D009(int value);
	AsciiString rva0051CC8DFormat(AsciiString text);
};

class Rva0020EAF6View { public: Rva0020E89C *rva0020EAF6(int index); };
class Rva003F038E { public: const Image *rva003F03B9(); };
class Rva002239B2 { public: void rva002239E2(const AsciiString &name, const Image *image); };
class Rva0051C2E2 { public: void rva0051C2E2(int *index, const AsciiString &name, int bonus); };
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
	// MSVC 7.1 reverses overloaded virtual declarations: char fetch is +0x3C.
	virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
	virtual UnicodeString fetch(const AsciiString &label, bool *exists = 0) = 0;
};
extern GameTextInterface *TheGameText;
// Twelve-byte hero record, sorted by display order and pushed through the
// folded record provider at 0x002DF89B.
struct Rva0051DE3DHero
{
	int order;
	bool upgraded;
	const Image *image;
};
struct PrereqUnitRec
{
	unsigned int m_data[3];
	~PrereqUnitRec() {}
};
struct BfmeE12Key;
// One list row, sorted by its operator< (0x005EC52E) before display.
struct Rva0051DA24Row
{
	Rva0051DA24Row(AptScorePersistentUnit *u, ThingTemplate *t) : unit(u), thing(t) {}
	AptScorePersistentUnit *unit;
	ThingTemplate *thing;

	bool operator<(const Rva0051DA24Row &other) const;
};

namespace _STL
{
template <class RandomAccessIter> void sort(RandomAccessIter first, RandomAccessIter last);
}
// The rowed sort at 0x0051D9E1 (ScoreRowSort.cpp) names this 8-byte record
// by its stand-in S4SortElem8.
struct S4SortElem8;

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
#include "../../../../../../Libraries/Source/Apt/AptCommandMapAdder.h"

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
	// Retail 0x0051DA24: fills the persistent-unit list box.
	bool PopulatePersistentUnitsListbox();
	void CollectGameData();

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
	((Rva00222479ByteOneSetter *)g_bfmeAptWindowManager)->enable();
}

// Retail 0x0051BFA9, 13 bytes: "AptScoreScreen::RestartGame".
void AptScoreScreen::RestartGame(const char *unused)
{
	m_state = 3;
}

// Retail 0x0051BFB6, 28 bytes: "AptScoreScreen::Continue".
void AptScoreScreen::Continue(const char *unused)
{
	(*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->rva002B3740();
	m_state = 3;
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


// Retail's strcpy call lands on the import thunk rowed as ji_00629176.

// Retail 0x0051DA24, 1049 bytes: BFME 1's 0x005778E0 on BFME 2's armies.
// Each living-world army's persistent units with a known template become
// a row (name, button image, region, four counters, the unit as item
// data) of the +0x2A0 list box, sorted first.
bool AptScoreScreen::PopulatePersistentUnitsListbox()
{
	if (!TheGameLogic || !TheThingFactory || !m_units)
		return false;
	_STL::vector<Rva0051DA24Row> rows;
	_STL::vector<unsigned int> armies = ((Rva002401C0 *)TheGameLogic)->rva002401C0();
	for (unsigned int i = 0; i < armies.size(); ++i)
	{
		Rva0040CB2CIndexedField *army = (Rva0040CB2CIndexedField *)armies[i];
		if (!army)
			return false;
		int count = army->m_entries.size();
		for (int j = 0; j < count; ++j)
		{
			AptScorePersistentUnit *unit = (AptScorePersistentUnit *)army->get(j);
			ThingTemplate *thing = (ThingTemplate *)TheThingFactory->findTemplate(unit->m_templateName);
			if (thing)
			{
				Rva0051DA24Row row(unit, thing);
				rows.push_back(row);
			}
		}
	}
	if (rows.size() == 0)
		return false;
	_STL::sort((S4SortElem8 *)rows.begin(), (S4SortElem8 *)rows.end());
	GadgetListBoxReset(m_units);
	if (GadgetListBoxGetNumColumns(m_units) < 7)
	{
		int widths[7] = { 10, 25, 17, 13, 13, 12, 8 };
		GadgetListBoxSetColumnWidths(m_units, 7, widths);
	}
	const int color = g_00DD16C4;
	for (_STL::vector<Rva0051DA24Row>::iterator it = rows.begin(); it != rows.end(); ++it)
	{
		AptScorePersistentUnit *unit = it->unit;
		ThingTemplate *thing = it->thing;
		UnicodeString text;
		if (!unit->m_name.isEmpty())
			text = unit->m_name;
		else
			text = thing->m_displayName;
		int row = GadgetListBoxAddEntryText(m_units, text, color, -1, 1, true);
		const Image *image = thing->getButtonImage();
		if (image)
			GadgetListBoxAddEntryImage(m_units, image, row, 0, 40, 40, true, -1);
		Rva002104B6 *regions = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->m_B0;
		Rva0020E89C *region = (Rva0020E89C *)regions->rva002104B6(&unit->m_regionName);
		if (region)
			GadgetListBoxAddEntryText(m_units, region->rva0020E89C(), color, row, 2, true);
		text.translate(((Rva0051D009 *)this)->rva0051D009(unit->m_0C));
		GadgetListBoxAddEntryText(m_units, text, color, row, 3, true);
		text.translate(((Rva0051D009 *)this)->rva0051D009(unit->m_94));
		GadgetListBoxAddEntryText(m_units, text, color, row, 4, true);
		text.translate(((Rva0051D009 *)this)->rva0051D009(unit->m_98));
		GadgetListBoxAddEntryText(m_units, text, color, row, 5, true);
		text.translate(((Rva0051D009 *)this)->rva0051D009(unit->m_9C));
		GadgetListBoxAddEntryText(m_units, text, color, row, 6, true);
		GadgetListBoxSetItemData(m_units, (void *)unit, row, 0);
	}
	GadgetListBoxSetTopVisibleEntry(m_units, 0);
	return true;
}

class GlobalData;
extern GlobalData *TheWritableGlobalData;
// The native query reads this float directly; no full GlobalData layout is
// asserted. WB reads the corresponding score option at its own +0x115C.
struct AptScoreOptionView { unsigned char prefix[0x1184]; float objectivesPerScore; };

// WB 01460190 names this handler and identifies all seven query branches.
// Native 0051CE72..0051D009 supplies the release-build guards and layout.
// Its fifth query actually passes a double with the same "%d" literal used
// by the integer queries; preserve that retail vararg call as observed.
void AptScoreScreen::Externs(int query, char *value, bool set)
{
	if (!set) {
		value[0] = '0';
		value[1] = 0;
	}
	if (query == 0) {
		if (!set) sprintf(value, "%d", m_280 == 1);
	} else if (query == 1) {
		if (!set) sprintf(value, "%d", m_280 == 0);
	} else if (query == 2) {
		if (!set) sprintf(value, "%d", m_heroUpgrades.size());
	} else if (query == 3) {
		if (!set && m_objectives) strcpy(value, m_objectives->m_faction.str());
	} else if (query == 4) {
		if (!set && m_objectives) sprintf(value, "%d", m_objectives->m_count);
	} else if (query == 5) {
		if (!set) sprintf(value, "%d", reinterpret_cast<AptScoreOptionView *>(TheWritableGlobalData)->objectivesPerScore);
	} else if (query == 6) {
		if (set) m_2b0.set(value);
		else {
			const AsciiString &formatted = reinterpret_cast<Rva0051D009 *>(this)->rva0051CC8DFormat(m_2b0);
			if (formatted.getLength() >= 255) return;
			strcpy(value, formatted.str());
		}
	}
}

// Retail 0x0051DE3D, 1061 B: objectives, hero icons and region bonuses.
void AptScoreScreen::CollectGameData()
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
	_STL::vector<unsigned int> armies = ((Rva002401C0 *)TheGameLogic)->rva002401C0();
	for (unsigned int i = 0; i < armies.size(); ++i)
	{
		Rva0040CB2CIndexedField *army = (Rva0040CB2CIndexedField *)armies[i];
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
				((_STL::vector<PrereqUnitRec> *)&heroes)->push_back(*(const PrereqUnitRec *)&hero);
			}
		}
	}
	_STL::sort<BfmeE12Key *>((BfmeE12Key *)heroes.begin(), (BfmeE12Key *)heroes.end());
	m_heroUpgrades.clear();
	unsigned int k = 0;
	for (; k < heroes.size(); ++k)
	{
		AsciiString key;
		int slot = m_heroUpgrades.size() + 1;
		key.format("SubMenus/HeroVeterancy/HeroSelection/HeroSelection%d/icon/Image", slot);
		((Rva002239B2 *)g_bfmeAptWindowManager)->rva002239E2(key, heroes[k].image);
		m_heroUpgrades.push_back(heroes[k].upgraded);
	}
	Rva002BA8F1Logic *livingWorld = *(Rva002BA8F1Logic **)&TheLivingWorldLogic;
	if (livingWorld)
	{
		int id = livingWorld->m_B8;
		Rva0020EAF6View *regions = (Rva0020EAF6View *)livingWorld->m_B0;
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
				{
					// Merged paths preserve the native allocation weights (docs/recipes.md).
					if (m_280 == 1)
					{
						((Rva0051C2E2 *)this)->rva0051C2E2(&index, key, region->m_90);
					}
					else
					{
						((Rva0051C2E2 *)this)->rva0051C2E2(&index, key, region->m_90);
					}
				}
			}
			while (index <= 3)
			{
				AsciiString key("");
				((Rva0051C2E2 *)this)->rva0051C2E2(&index, key, -1);
			}
			{
				AsciiString key("Result/Infos/ScoreMap/Picture/Image");
				((Rva002239B2 *)g_bfmeAptWindowManager)->rva002239E2(key, ((Rva003F038E *)region)->rva003F03B9());
			}
			{
				AsciiString key("SubMenus/TerritoryBonus/TerritoryMap/TerritoryMap/Picture/Image");
				((Rva002239B2 *)g_bfmeAptWindowManager)->rva002239E2(key, ((Rva003F038E *)region)->rva003F03B9());
			}
			if (m_280 == 1)
				PopulatePersistentUnitsListbox();
		}
	}
}
