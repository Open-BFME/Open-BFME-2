// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// BFME2's skirmish screen Apt callbacks, 0x00521741 onward, bound by these
// names ("AptSkirmish::OnInitialized" ...) as member pointers by the
// screen's registration; that binding is their only reference. The class
// is named for the strings' prefix. +0x6B8 is the screen's state, +0x6D0
// its profile name entry, +0x698 its SkirmishPreferences (whose user name
// list the profile callbacks walk; STLport and /EHsc are for them).

#include "unicode_string.h"

#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}


// Retail's string comparisons register no unwind state for their
// temporaries: StringBase<unsigned short>'s compare and compareNoCase are
// taken not to throw (as the throw() view in stlport_sort_mapmetadata.cpp).
template <> int StringBase<unsigned short>::compare(const StringBase<unsigned short> &str) const throw();
template <> int StringBase<unsigned short>::compareNoCase(const StringBase<unsigned short> &str) const throw();

// The user name list's base destructor is the rowed out-of-line 0x00433BD7.
extern template _STL::_List_base<UnicodeString, _STL::allocator<UnicodeString> >::~_List_base();

class GameWindow;

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

void GadgetTextEntrySetText(GameWindow *textEntry, UnicodeString text);
void GadgetListBoxGetSelected(GameWindow *listBox, int *selectIndex);
UnicodeString GadgetTextEntryGetText(GameWindow *textEntry);
void GadgetListBoxSetSelected(GameWindow *listBox, int selectIndex);
void GadgetListBoxReset(GameWindow *listBox);
int GadgetListBoxAddEntryText(GameWindow *listBox, UnicodeString text, int color, int row, int column, bool overwrite);

extern "C" int __cdecl strcmp(const char *left, const char *right);

class BfmeKeyLC;
class BfmeObjENK;
void GadgetTextEntrySetMaxChars(BfmeKeyLC *textEntry, unsigned short maxLength);
void bfmeGoENK(BfmeObjENK *listBox, char flag);

// The name entry link at +0x6C8 (as the LAN lobby's +0x6AC one): vslot 1
// attaches the window, kept at its +0x08.
class AptSkirmishEntryLink
{
public:
	virtual void v0();
	virtual void attach(GameWindow *window);

	void *m_04;
	GameWindow *m_window; // +0x08
};

// The skirmish screen instance (Rva0052192DInit.cpp's g_00E04930).
extern int g_00E04930;

class Rva00222A8BTarget;
extern class Rva00222A8BTarget *TheRva00222A8BTarget;

// MpGameSetupSlots.cpp's 0x0043DB23 runs an Apt function on a movie.
void Rva0043DB23(Rva00222A8BTarget *target, void *owner, const char *name);

class Rva00222479ByteOneSetter
{
public:
	void enable();
};

class GameInfo;
extern GameInfo *TheSkirmishGameInfo;

class AptSkirmish
{
public:
	// Target constructor 0x00521977 installs the primary table at VA
	// 0x00C67910. Its raw 15 entries put rva00523303 in slot 12 and the
	// rowed validator in slot 14; the other local slots remain placeholders.
	virtual void vslot0() = 0;
	virtual void vslot1() = 0;
	virtual void vslot2() = 0;
	virtual void vslot3() = 0;
	virtual void vslot4() = 0;
	virtual void vslot5() = 0;
	virtual void vslot6() = 0;
	virtual void vslot7() = 0;
	virtual void vslot8() = 0;
	virtual void vslot9() = 0;
	virtual void vslot10() = 0;
	virtual void vslot11() = 0;
	virtual void rva00523303();
	virtual void vslot13() = 0;
	virtual bool MPOwnerValidatGameInfo(GameInfo *gameInfo);

	void OnInitialized(const char *unused);
	// Bound under both "AptSkirmish::Back" and "AptSkirmish::Exit" (one
	// body or two folded), so it keeps its address.
	void rva0052174E(const char *unused);
	void StartGame(const char *unused);
	void OnStatsMenu(const char *unused);
	void OnProfilePopupCancel(const char *unused);
	void OnExitStatsScreen(const char *unused);
	void OnClosed(const char *unused);
	void OnNewProfileMenu(const char *unused);
	void OnDeleteProfileMenu(const char *unused);
	void OnChangeProfileMenu(const char *unused);
	void InitGadgets(const char *name, void *argument, GameWindow *window);
	UnicodeString GetListboxProfileSelectedName();
	void OnChangeProfile(const char *unused);
	void OnDeleteProfile(const char *unused);
	void OnAddProfileAccept(const char *unused);
	void InitCreateAHeroOnStartGame();

	// Unrowed 0x00521CFF (358 bytes), pinned by address; 0x00522556 is
	// defined below.
	void rva00521CFF();
	void rva00522556();

private:
	unsigned char m_pad004[0x274 - 4];
	void *m_274; // +0x274, the screen's Apt movie
	unsigned char m_pad278[0x6B8 - 0x278];
	int m_state; // +0x6B8
	unsigned char m_pad6bc[0x6C0 - 0x6BC];
	bool m_6c0; // +0x6C0, target flag tested and cleared by slot 12
	bool m_6c1; // +0x6C1
	bool m_6c2; // +0x6C2
	unsigned char m_pad6c3[0x6C4 - 0x6C3];
	GameWindow *m_profiles; // +0x6C4
	AptSkirmishEntryLink m_nameEntry; // +0x6C8 (the window at +0x6D0)
};

// Retail 0x00521643, 21 bytes. Name unknown. With the skirmish screen up,
// the Apt window manager's 0x00222479 (as Rva00433D27Enable and its twins).
void Rva00521643Enable()
{
	if (g_00E04930 == 0)
		return;
	((Rva00222479ByteOneSetter *)TheRva00222A8BTarget)->enable();
}

// Retail 0x00521741, 13 bytes: "AptSkirmish::OnInitialized".
void AptSkirmish::OnInitialized(const char *unused)
{
	m_state = 1;
}

// Retail 0x0052174E, 8 bytes: bound as "AptSkirmish::Back" and
// "AptSkirmish::Exit".
void AptSkirmish::rva0052174E(const char *unused)
{
	Rva00521643Enable();
}

// Retail 0x00521756, 13 bytes: "AptSkirmish::StartGame".
void AptSkirmish::StartGame(const char *unused)
{
	m_state = 10;
}

class SkirmishPreferences
{
public:
	SkirmishPreferences(int profileIndex);
	virtual ~SkirmishPreferences();
	virtual void v1();
	virtual void v2();
	virtual void v3slotC();
	bool Rva0043B9E8();
	_STL::list<UnicodeString> getUserNames_Rva0043C2D0();
	UnicodeString Rva0043B9F5();
	UnicodeString Rva0043BB88();
	void Rva0043C2EB(const UnicodeString &name);
	int Rva0043BBB6(UnicodeString name);
	void rva0043C612(const UnicodeString &name);
	void setCurrentUserName(const UnicodeString &name);
	// Unrowed 0x0043BE7C, pinned by address.
	void rva0043BE7C();

private:
	// Target constructor and helper accesses agree with UserPreferences at
	// +0x00..+0x13, then profile index +0x14, names +0x18, current name +0x1C.
	unsigned char m_baseTail[0x10];
	int m_profileIndex;
	void *m_userNames;
	void *m_currentUserName;
};

// The screen's member at +0x668; its unrowed 0x005C1ABA takes the current
// user name, pinned by address.
class Rva005C1ABA
{
public:
	virtual void vslot0();
	virtual void vslot1();
	virtual void vslot2();
	virtual void vslot3();
	void rva005C1ABA(const UnicodeString &name);
};
// Target memberwise assignment at 0x005232D0 copies the 0x20-byte preference
// record shape; its owning type remains address-derived in the ledger.
struct Rva005232D0
{
	Rva005232D0 &operator=(const Rva005232D0 &other);
};
class GameSlot;
class GameInfo
{
public:
	virtual void *v0slot0(int v);
	GameSlot *getSlot(int index);
};
extern GameInfo *TheSkirmishGameInfo;
extern int g_Va00E0333C;
void __cdecl operator delete(void *p);
class Panel00E0333C
{
public:
	virtual void p0();
	virtual void p1slot4();
};
void Rva00521643Enable();

// Retail 0x00521763, 13 bytes: "AptSkirmish::OnStatsMenu".
void AptSkirmish::OnStatsMenu(const char *unused)
{
	m_state = 8;
}

// Retail 0x00521770, 158 bytes: state machine for stats/profile screens.
// Cases 2/3/4 on m_state; case 2 checks SkirmishPreferences at +0x698,
// tears down TheSkirmishGameInfo, notifies g_Va00E0333C panel and re-enables.
void AptSkirmish::OnProfilePopupCancel(const char *unused)
{
	(void)unused;
	switch (m_state) {
	case 2: {
		m_6c1 = true;
		m_state = 7;
		SkirmishPreferences *prefs = (SkirmishPreferences *)((char *)this + 0x698);
		if (prefs->Rva0043B9E8())
			return;
		prefs->v3slotC();
		GameInfo *g = TheSkirmishGameInfo;
		void *toFree;
		if (g != 0)
			toFree = g->v0slot0(0);
		else
			toFree = 0;
		operator delete(toFree);
		TheSkirmishGameInfo = 0;
		Panel00E0333C *panel = (Panel00E0333C *)(void *)g_Va00E0333C;
		if (panel != 0)
			panel->p1slot4();
		Rva00521643Enable();
		break;
	}
	case 3:
		m_6c1 = true;
		m_state = 5;
		break;
	case 4:
		m_6c1 = true;
		m_state = 7;
		break;
	}
}

// Retail 0x00521826, 27 bytes: "AptSkirmish::OnExitStatsScreen".
void AptSkirmish::OnExitStatsScreen(const char *unused)
{
	if (m_state == 8 || m_state == 9)
		m_state = 7;
}

// Retail 0x00521E65, 17 bytes: "AptSkirmish::OnClosed".
void AptSkirmish::OnClosed(const char *unused)
{
	if (m_state == 11)
		rva00521CFF();
}

// Retail 0x00521E76, 76 bytes: "AptSkirmish::OnNewProfileMenu" focuses
// and clears the profile name entry.
void AptSkirmish::OnNewProfileMenu(const char *unused)
{
	m_state = 2;
	TheWindowManager->winSetFocus(m_nameEntry.m_window);
	GadgetTextEntrySetText(m_nameEntry.m_window, UnicodeString::TheEmptyString);
	m_6c2 = true;
}

// Retail 0x0052266B, 22 bytes: "AptSkirmish::OnDeleteProfileMenu".
void AptSkirmish::OnDeleteProfileMenu(const char *unused)
{
	rva00522556();
	m_state = 3;
}

// Retail 0x00522681, 22 bytes: "AptSkirmish::OnChangeProfileMenu".
void AptSkirmish::OnChangeProfileMenu(const char *unused)
{
	rva00522556();
	m_state = 4;
}

// Retail 0x00522918, 187 bytes: "AptSkirmish::InitGadgets" links the
// emptied "Skirmish::CreatePersonaEntry" (11 characters) and keeps the
// "Skirmish::SelectProfile" list, refilling it (0x00522556).
void AptSkirmish::InitGadgets(const char *name, void *argument, GameWindow *window)
{
	if (!window)
		return;
	if (strcmp(name, "Skirmish::CreatePersonaEntry") == 0)
	{
		m_nameEntry.attach(window);
		UnicodeString text = UnicodeString::TheEmptyString;
		GameWindow *entry = m_nameEntry.m_window;
		GadgetTextEntrySetMaxChars((BfmeKeyLC *)entry, 11);
		GadgetTextEntrySetText(m_nameEntry.m_window, text);
	}
	else if (strcmp(name, "Skirmish::SelectProfile") == 0)
	{
		bfmeGoENK((BfmeObjENK *)window, 1);
		m_profiles = window;
		rva00522556();
	}
}

// Retail 0x00522697, 182 bytes. Name unknown: the profile selected in the
// "Skirmish::SelectProfile" list, read from the preferences' user names
// (the empty string with no list or no selection).
UnicodeString AptSkirmish::GetListboxProfileSelectedName()
{
	if (!m_profiles)
		return UnicodeString::TheEmptyString;
	int selected;
	GadgetListBoxGetSelected(m_profiles, &selected);
	if (selected == -1)
		return UnicodeString::TheEmptyString;
	_STL::list<UnicodeString> names = ((SkirmishPreferences *)((char *)this + 0x698))->getUserNames_Rva0043C2D0();
	_STL::list<UnicodeString>::iterator it = names.begin();
	_STL::advance(it, selected);
	if (it == names.end())
		return UnicodeString::TheEmptyString;
	return *it;
}

// Retail 0x005229D3, 190 bytes: "AptSkirmish::OnChangeProfile" makes the
// selected profile the current user when it is another one.
void AptSkirmish::OnChangeProfile(const char *unused)
{
	UnicodeString name = GetListboxProfileSelectedName();
	SkirmishPreferences *prefs = (SkirmishPreferences *)((char *)this + 0x698);
	if (name.compare(prefs->Rva0043B9F5()) != 0)
	{
		prefs->rva0043BE7C();
		prefs->v3slotC();
		prefs->setCurrentUserName(name);
		prefs->v3slotC();
		((Rva005C1ABA *)((char *)this + 0x668))->rva005C1ABA(prefs->Rva0043B9F5());
		m_state = 5;
	}
	m_6c1 = true;
}

// Retail 0x00522556, 277 bytes: refills the "Skirmish::SelectProfile" list
// with the user names, selecting the current one, and disables the select
// button when there is none.
void AptSkirmish::rva00522556()
{
	if (!m_profiles)
		return;
	GadgetListBoxReset(m_profiles);
	_STL::list<UnicodeString> names = ((SkirmishPreferences *)((char *)this + 0x698))->getUserNames_Rva0043C2D0();
	_STL::list<UnicodeString>::iterator it = names.begin();
	UnicodeString name;
	int count = 0;
	int selected = 0;
	for (; it != names.end(); ++it)
	{
		name = *it;
		GadgetListBoxAddEntryText(m_profiles, name, -1, -1, -1, true);
		if (name.compareNoCase(((SkirmishPreferences *)((char *)this + 0x698))->Rva0043B9F5()) == 0)
			selected = count;
		++count;
	}
	if (count == 0)
	{
		void *movie = m_274;
		Rva0043DB23(TheRva00222A8BTarget, movie, "PopupSelectBttnDisable");
	}
	GadgetListBoxSetSelected(m_profiles, selected);
}

// Retail 0x00522833, 229 bytes: "AptSkirmish::OnDeleteProfile" deletes the
// selected profile; deleting the current user switches to the one the
// preferences answer next. The list is refilled either way.
void AptSkirmish::OnDeleteProfile(const char *unused)
{
	UnicodeString name = GetListboxProfileSelectedName();
	SkirmishPreferences *prefs = (SkirmishPreferences *)((char *)this + 0x698);
	bool current = prefs->Rva0043B9F5().compare(name) == 0;
	prefs->Rva0043C2EB(name);
	if (current && prefs->Rva0043B9E8())
	{
		name = prefs->Rva0043BB88();
		prefs->setCurrentUserName(name);
		prefs->v3slotC();
		((Rva005C1ABA *)((char *)this + 0x668))->rva005C1ABA(prefs->Rva0043B9F5());
	}
	rva00522556();
}

// Retail expands UnicodeString::isEmpty inline as the header test
// (m_data == 0 || m_data->length == 0); the shared shim keeps it out of
// line (as MpGameSetupSlots.cpp notes).
static inline bool unicodeIsEmpty(const UnicodeString &text)
{
	const unsigned char *data = *(const unsigned char *const *)&text;
	return data == 0 || *(const unsigned short *)(data + 4) == 0;
}

// Retail 0x00521B56, 260 bytes: "AptSkirmish::OnAddProfileAccept" adds the
// trimmed name typed in the profile entry as a new user and makes it the
// current one, unless it is empty or already known.
void AptSkirmish::OnAddProfileAccept(const char *unused)
{
	if (m_state != 2)
		return;
	UnicodeString name = UnicodeString::TheEmptyString;
	if (m_nameEntry.m_window)
		name = GadgetTextEntryGetText(m_nameEntry.m_window);
	name.trim();
	if (unicodeIsEmpty(name))
		return;
	if (((SkirmishPreferences *)((char *)this + 0x698))->Rva0043BBB6(name) < 0)
	{
		SkirmishPreferences *prefs = (SkirmishPreferences *)((char *)this + 0x698);
		prefs->rva0043C612(name);
		prefs->setCurrentUserName(name);
		prefs->v3slotC();
		((Rva005C1ABA *)((char *)this + 0x668))->rva005C1ABA(prefs->Rva0043B9F5());
		m_6c1 = true;
		m_state = 5;
	}
}

// AptSkirmish::MPOwnerValidatGameInfo, retail 0x0052180E (24B): true only
// when the skirmish game info exists and is the one asked about.
bool AptSkirmish::MPOwnerValidatGameInfo(GameInfo *gameInfo)
{
	if (TheSkirmishGameInfo && TheSkirmishGameInfo == gameInfo)
		return true;
	return false;
}

// Retail 0x005218AF, 126 bytes. WorldBuilder names this
// AptSkirmish::InitCreateAHeroOnStartGame and its assertions check the
// GameInfo, hero manager, slot, and hero-result guards. BFME1's AptSkirmish
// donor at 6583b3c1 predates Create-A-Hero and has no counterpart for this
// method; the target disassembly supplies the loop and call order. The slot
// offsets are cross-checked against the matched GameSlot and CreateAHeroData
// views in MpGameSetupSlots.cpp and GameSlot_rva0037AD8D.cpp.
class CreateAHeroData
{
public:
	virtual ~CreateAHeroData();
	CreateAHeroData &operator=(const CreateAHeroData &that);

private:
	unsigned char m_fields[0x13C];
};

class GameSlot
{
public:
	bool isOccupied() const;
	void rva0037AD8D(const CreateAHeroData &data);

	void *m_vtable;
	unsigned char m_pad00[0x50 - 0x04];
	int m_heroKind; // +0x50, nonzero before this screen assigns a hero
	int m_hero0c; // +0x54
	int m_hero10; // +0x58
	int m_hero; // +0x5C, CreateAHeroData list index
};

class Rva0040A3F9
{
public:
	CreateAHeroData *rva0040A32F(int index);
};

class CreateAHeroManager
{
public:
	Rva0040A3F9 *rva0021F797();
};

// The canonical data-ledger symbol at RVA 0x009FE344 is TheHeroManager.
// GameEngine::init registers this same target object under the subsystem name
// TheCreateAHeroManager; its pointer type here is inferred from target calls.
class Rva0021A54A;
extern Rva0021A54A *TheHeroManager;

// These are the target's direct helpers from 0x005218AF. Ghidra bounds
// 0x0044C2C6 at 270 bytes; this caller pushes no arguments and the target
// body returns void. WB maps it to SelectRandomHero by call graph, but the
// target identity stays address-derived. The 106-byte 0x0021A428 helper is
// thiscall with one pointer argument (ECX is the manager and the callee pops
// four bytes); this call and 0x005B5B1E and 0x005B694F establish that ABI.
// WB leaves it unnamed and its operation is unresolved. The existing
// UseSub spellings are caller aliases only. The manager pointer is expressed
// through its canonical data-ledger name above.
void rva0044C2C6();
class Rva005B5B0CMgr
{
public:
	void UseSub(void *hero);
};

class AptMpGameSetup
{
public:
	void rva0044303D();
};

// Retail 0x00523303 (249 bytes), primary AptSkirmish vtable slot 12. Its
// thiscall body refreshes the AptMpGameSetup panel at +0x288, state +0x6B8,
// profile index +0x304, flag +0x6C0, preferences +0x698 and name member
// +0x668. Constructor 0x00521977 installs the table at VA 0x00C67910; the
// raw slot-12 pointer is 0x00523303. BFME1's AptSkirmish constructor
// supports the screen-family provenance only, so the target method keeps an
// address-derived name.
void AptSkirmish::rva00523303()
{
	((AptMpGameSetup *)((char *)this + 0x288))->rva0044303D();
	if (m_state == 9)
		m_state = 7;

	if (!m_6c0)
	{
		SkirmishPreferences preferences(
			*(int *)((char *)this + 0x304));
		*((Rva005232D0 *)((char *)this + 0x698)) =
			*(const Rva005232D0 *)&preferences;
	}
	SkirmishPreferences *prefs =
		(SkirmishPreferences *)((char *)this + 0x698);
	if (prefs->Rva0043BBB6(prefs->Rva0043B9F5()) < 0)
	{
		prefs->setCurrentUserName(prefs->Rva0043BB88());
		prefs->v3slotC();
	}
	Rva005C1ABA *nameMember = (Rva005C1ABA *)((char *)this + 0x668);
	nameMember->vslot3();
	nameMember->rva005C1ABA(prefs->Rva0043B9F5());
	m_6c0 = false;
}

void AptSkirmish::InitCreateAHeroOnStartGame()
{
	GameInfo *gameInfo = TheSkirmishGameInfo;
	if (gameInfo == 0)
		return;

	rva0044C2C6();
	CreateAHeroManager *heroManager = (CreateAHeroManager *)TheHeroManager;
	if (heroManager == 0)
		return;

	Rva0040A3F9 *heroes = heroManager->rva0021F797();
	for (int i = 0; i < 8; ++i)
	{
		GameSlot *slot = gameInfo->getSlot(i);
		if (slot == 0 || !slot->isOccupied() || slot->m_heroKind == 0)
			continue;

		CreateAHeroData *hero = heroes->rva0040A32F(slot->m_hero);
		if (hero == 0)
			continue;

		if (i == 0)
			((Rva005B5B0CMgr *)TheHeroManager)->UseSub(hero);
		slot->rva0037AD8D(*hero);
	}
}
