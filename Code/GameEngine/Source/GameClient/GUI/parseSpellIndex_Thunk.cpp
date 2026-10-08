// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail RVA 0x005990A0. The outlined "SpellNN" name parser that sits one
// slot above the three BfmeAptScreenSpellStore callbacks at 0x005990E0,
// 0x00599180 and 0x005991E0, each of which spells the same test inline.
// Nothing in the image calls this copy, so it keeps a descriptive free name.

#include "ascii_string.h"
#include "unicode_string.h"
#include "../../Common/GameLogicObjectLookupView.h"

extern "C" __declspec(dllimport) int __cdecl atoi( const char * );
extern "C" __declspec(dllimport) int __cdecl strncmp(
	const char *, const char *, unsigned int );

// @?parseSpellIndex@@YAHPBD@Z 0x005990A0
static __declspec(noinline) int parseSpellIndex( const char *name )
{
	if( strncmp( name, "Spell", 5 ) != 0 )
		return -1;
	return atoi( name + 5 ) - 1;
}

int parseSpellIndexCall( const char *name )
{
	return parseSpellIndex( name );
}

// BFME2's spell store screen callbacks around the parser (0x0043C78A ..
// 0x0043D5F5), bound by name ("AptSpellStore::OnInitialized" ...) by the
// screen's registration 0x0043D686; the static parser above is what lets
// them pass the name in EAX. The view below covers only the fields they
// touch. The rowed OnBttnClose 0x0043C7C9 and OnBttnReset 0x0043D3DA view
// the same screen as Rva0043D3DA.
enum ScienceType
{
	SCIENCE_INVALID = 0
};

class ModuleData;

namespace _STL
{
template <class T> class allocator;
template <class T, class A> class vector
{
public:
	void push_back(const T &value);

	T *m_start;
	T *m_finish;
	T *m_end;
};
}

// The +0x288 member (Rva0043D3DAClear.cpp's Rva0043D3A8): vslot 0 tells
// whether a science is already chosen, vslot 1 the points left to spend;
// the rowed 0x0043D5CB adds one.
class CreateAHeroData;

// The player's rowed science checks 0x002AB82D and 0x002AB855 (BFME 1's
// isScienceDisabled and isScienceHidden), named by their rows' views.
class Player
{
public:
	bool rva002AB82D(CreateAHeroData *science) const;
	bool rva002AB855(CreateAHeroData *science) const;
};

class Rva0043D3A8
{
public:
	virtual bool v00(ScienceType science);
	virtual int v04();
	void rva0043D5CB(ScienceType science);

	Player *m_player; // +0x04, the local player the store buys for
};

class ScienceStore
{
public:
	// Unrowed 0x001FF4D3 (58 bytes; ret 8): the prerequisites check
	// 0x001FF47D, then the holder's vslot 1 points against
	// getSciencePurchaseCost; pinned by address.
	bool rva001FF4D3(Rva0043D3A8 *holder, ScienceType science) const;
	int getSciencePurchaseCost(ScienceType science) const;
	// Rowed 0x001FFC55; BFME 2 passes the science holder for the player.
	bool playerHasRootPrereqsForScience(const Player *player, ScienceType science) const;
};

extern ScienceStore *TheScienceStore;

// TheGameLogic (0x009FE78C): the end flag at +0x6D and the game mode at
// +0x110 (6 never pauses for the store) in the shared view, and the rowed
// 0x0023C902 check.
extern GameLogic *TheGameLogic;

class Rva0023C902
{
public:
	int rva0023C902();
};

class Rva005CB260;

// The folded forwarder to vslot 3 of what TheInGameUI's 0x000CF155
// returns (both pinned, as in AptQuitMenuCallbacks.cpp).
class Rva005CB265
{
public:
	virtual int rva005CB265();
};

// TheInGameUI (0x009FEDF0): vslot 94 shows or hides a menu, vslot 95 tells
// whether one is up; the byte at +0x16 lets mode 6 use the store.
class InGameUI
{
public:
#define IGUI_SLOT(N) virtual void slot##N();
	IGUI_SLOT(00) IGUI_SLOT(01) IGUI_SLOT(02) IGUI_SLOT(03) IGUI_SLOT(04)
	IGUI_SLOT(05) IGUI_SLOT(06) IGUI_SLOT(07) IGUI_SLOT(08) IGUI_SLOT(09)
	IGUI_SLOT(10) IGUI_SLOT(11) IGUI_SLOT(12) IGUI_SLOT(13) IGUI_SLOT(14)
	IGUI_SLOT(15) IGUI_SLOT(16) IGUI_SLOT(17) IGUI_SLOT(18) IGUI_SLOT(19)
	IGUI_SLOT(20) IGUI_SLOT(21) IGUI_SLOT(22) IGUI_SLOT(23) IGUI_SLOT(24)
	IGUI_SLOT(25) IGUI_SLOT(26) IGUI_SLOT(27) IGUI_SLOT(28) IGUI_SLOT(29)
	IGUI_SLOT(30) IGUI_SLOT(31) IGUI_SLOT(32) IGUI_SLOT(33) IGUI_SLOT(34)
	IGUI_SLOT(35) IGUI_SLOT(36) IGUI_SLOT(37) IGUI_SLOT(38) IGUI_SLOT(39)
	IGUI_SLOT(40) IGUI_SLOT(41) IGUI_SLOT(42) IGUI_SLOT(43) IGUI_SLOT(44)
	IGUI_SLOT(45) IGUI_SLOT(46) IGUI_SLOT(47) IGUI_SLOT(48) IGUI_SLOT(49)
	IGUI_SLOT(50) IGUI_SLOT(51) IGUI_SLOT(52) IGUI_SLOT(53) IGUI_SLOT(54)
	IGUI_SLOT(55) IGUI_SLOT(56) IGUI_SLOT(57) IGUI_SLOT(58) IGUI_SLOT(59)
	IGUI_SLOT(60) IGUI_SLOT(61) IGUI_SLOT(62) IGUI_SLOT(63) IGUI_SLOT(64)
	IGUI_SLOT(65) IGUI_SLOT(66) IGUI_SLOT(67) IGUI_SLOT(68) IGUI_SLOT(69)
	IGUI_SLOT(70) IGUI_SLOT(71) IGUI_SLOT(72) IGUI_SLOT(73) IGUI_SLOT(74)
	IGUI_SLOT(75) IGUI_SLOT(76) IGUI_SLOT(77) IGUI_SLOT(78) IGUI_SLOT(79)
	IGUI_SLOT(80) IGUI_SLOT(81) IGUI_SLOT(82) IGUI_SLOT(83) IGUI_SLOT(84)
	IGUI_SLOT(85) IGUI_SLOT(86) IGUI_SLOT(87) IGUI_SLOT(88) IGUI_SLOT(89)
	IGUI_SLOT(90) IGUI_SLOT(91) IGUI_SLOT(92) IGUI_SLOT(93)
#undef IGUI_SLOT
	virtual void slot94(bool visible);
	virtual bool slot95();

	Rva005CB260 *rva000CF155();

	unsigned char m_pad004[0x16 - 4];
	bool m_16; // +0x16
};

extern InGameUI *TheInGameUI;

extern "C" char *__cdecl _mbscpy(char *dest, const char *src);

// Rva0050E9D3Enable.cpp's 0x0043C96F.
void Rva0043C96FEnable(void);

// A spell button's entry: its science list at +0xA4.
struct SpellStoreEntry
{
	unsigned char m_pad[0xA4];
	ScienceType *m_sciences; // +0xA4
};

class Image;

// The spell book's buttons (CommandButtonIsReady.cpp): 0x0035B19E returns
// the image its +0xFC index picks from the list at +0xEC, 0x0035B1E9 and
// 0x0035B26F its label and description. The sciences span +0xA4..+0xA8 as
// in SpellStoreEntry.
class CommandButton
{
public:
	const Image *rva0035B19E() const;
	const AsciiString &rva0035B1E9() const;
	const AsciiString &rva0035B26F() const;
	unsigned int scienceCount() const { return m_sciencesEnd - m_sciences; }

	unsigned char m_pad000[0xA4];
	ScienceType *m_sciences; // +0xA4
	ScienceType *m_sciencesEnd; // +0xA8
};

class CommandSet
{
public:
	const CommandButton *getCommandButton(int index) const;
};

// ThePlayerList (0x009FEEE8): the local player at +0x10.
class PlayerList
{
public:
	Player *getLocalPlayer() { return m_local; }

private:
	unsigned char m_pad000[0x10];
	Player *m_local; // +0x10
};

extern PlayerList *ThePlayerList;

// TheControlBar's rowed lookup 0x0031DF89 (Rva0031D5F8Lookup.cpp): the
// player's command set.
class ControlBar;
extern ControlBar *TheControlBar;

class Rva0031D5F8
{
public:
	void *rva0031DF89(const void *key);
};

// The Apt window manager (0x009FE4CC): the rowed image binding 0x002239E2
// (Rva002239B2.cpp) and text setter.
class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &name, const UnicodeString &text, bool flag);
};

extern BfmeAptWindowManager *g_bfmeAptWindowManager;

class Rva002239B2
{
public:
	void rva002239E2(const AsciiString &name, const Image *image);
};

struct SpellStoreSlot
{
	const ModuleData *m_entry;
	int m_04;
};

class AptSpellStore
{
public:
	void OnInitialized(const char *unused);
	void OnRollOverBttnSpell(const char *name);
	void OnRollOutBttnSpell(const char *name);
	void InputEnabled(int query, char *result, bool skip);
	void OnClosed(const char *unused);
	void OnBttnSpell(const char *name);
	void rva0043C9FD();
	void rva0043CD3C();

private:
	unsigned char m_pad000[0x27C];
	_STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> > m_chosen; // +0x27C
	Rva0043D3A8 m_sciences; // +0x288
	unsigned char m_pad290[0x2A0 - 0x290];
	bool m_2a0; // +0x2A0
	bool m_2a1;
	bool m_2a2; // +0x2A2
	int m_2a4; // +0x2A4
	SpellStoreSlot m_slots[20]; // +0x2A8
	int m_348; // +0x348
	int m_34c; // +0x34C
	int m_350; // +0x350
	int m_hovered; // +0x354
	bool m_358; // +0x358
	bool m_359; // +0x359
};

// Retail 0x0043C78A, 63 bytes: "AptSpellStore::OnInitialized".
void AptSpellStore::OnInitialized(const char *unused)
{
	m_2a2 = false;
	m_348 = -1;
	m_34c = -1;
	m_350 = -1;
	m_hovered = -1;
	m_358 = false;
	m_359 = false;
	m_2a4 = 0;
	m_2a0 = true;
}

// Retail 0x0043C85D, 38 bytes: "AptSpellStore::OnRollOverBttnSpell".
void AptSpellStore::OnRollOverBttnSpell(const char *name)
{
	int index = parseSpellIndex(name);
	if (index >= 0 && index < 20)
	{
		m_hovered = index;
		m_359 = false;
	}
}

// Retail 0x0043C883, 32 bytes: "AptSpellStore::OnRollOutBttnSpell".
void AptSpellStore::OnRollOutBttnSpell(const char *name)
{
	int index = parseSpellIndex(name);
	if (index >= 0 && index < 20)
		m_hovered = -1;
}

// Retail 0x0043C8A3, 65 bytes: "AptSpellStore::InputEnabled", an Apt
// query callback like AptMpGameSetup's 0x00442F65.
void AptSpellStore::InputEnabled(int query, char *result, bool skip)
{
	if (query == 0 && !skip)
		_mbscpy(result, TheGameLogic->m_110 == 6 || TheInGameUI->m_16 ? "1" : "0");
}

// Retail 0x0043C9E5, 24 bytes: "AptSpellStore::OnClosed".
void AptSpellStore::OnClosed(const char *unused)
{
	if (m_2a2)
	{
		Rva0043C96FEnable();
		m_2a2 = false;
	}
}

// Retail 0x0043D5F5, 145 bytes: "AptSpellStore::OnBttnSpell". Under the
// same gate as OnBttnReset, a valid "SpellNN" button whose entry's first
// science is not chosen yet and is purchasable gets recorded and added.
void AptSpellStore::OnBttnSpell(const char *name)
{
	if (TheGameLogic->m_110 == 6)
	{
		if (!TheInGameUI->m_16)
			return;
	}
	int index = parseSpellIndex(name);
	if (index < 0 || index >= 20)
		return;
	if (m_2a2)
		return;
	const ModuleData *entry = m_slots[index].m_entry;
	if (!entry)
		return;
	ScienceType science = *((const SpellStoreEntry *)entry)->m_sciences;
	if (!m_sciences.v00(science) && TheScienceStore->rva001FF4D3(&m_sciences, science))
	{
		m_chosen.push_back(entry);
		m_sciences.rva0043D5CB(science);
	}
}


// Retail 0x0043C9FD, 331 bytes, the constructor's last call; BFME 1's
// BfmeAptScreenSpellStore::unidentified_000062DF
// (AptScreenSpellStoreUpdate000062DF.cpp) is the donor. Unless the store
// is closing, the local player's command set fills the twenty slots: each
// button is recorded, its image bound as "SpellStore/Buttons/SpellN" and
// its first science's cost published as "APT:SpellNCost". BFME 2 reads
// the buttons from the player's command set instead of the control bar's
// windows and keeps the player in the science holder.
void AptSpellStore::rva0043C9FD()
{
	if (m_2a2)
		return;
	Player *player = ThePlayerList->getLocalPlayer();
	if (!player)
		return;
	const CommandSet *set = (const CommandSet *)((Rva0031D5F8 *)TheControlBar)->rva0031DF89(player);
	if (!set)
		return;
	m_sciences.m_player = player;
	for (int i = 0; i < 20; ++i)
	{
		const CommandButton *button = set->getCommandButton(i);
		if (!button)
			continue;
		SpellStoreSlot *slot = &m_slots[i];
		slot->m_entry = (const ModuleData *)button;
		slot->m_04 = 0;
		const Image *image = button->rva0035B19E();
		if (image)
		{
			AsciiString name;
			name.format("SpellStore/Buttons/Spell%d", i + 1);
			((Rva002239B2 *)g_bfmeAptWindowManager)->rva002239E2(name, image);
		}
		int cost = TheScienceStore->getSciencePurchaseCost(*button->m_sciences);
		UnicodeString costText;
		costText.format(L"%d", cost);
		AsciiString costName;
		costName.format("APT:Spell%dCost", i + 1);
		g_bfmeAptWindowManager->bfmeSetText(costName, costText, false);
	}
}

// The open spell store (VA 0x00E03314; BFME 1's g_purchaseScienceWindow).
extern int g_Va00E03314;

// Rva0050E9D3Enable.cpp's guarded singleton; its +4 byte enables the store.
void *Rva0043C9B3Get(void);

// TheAptPalantir's BFME 2 counterpart (RadarWindowOverride.cpp).
class RadarWindowOverrideSource
{
public:
	bool hasOverrideWindow() const;
};

extern RadarWindowOverrideSource *theRadarWindowOverrideSource;

// Further screens that keep the store closed while up
// (ColdGlobalDwordGetters.cpp, AptDisconnectScreen.cpp).
extern int g_Va00E0330C;
extern int g_Va00E04910;
extern int g_Va00E048D0;

// TheScriptEngine (0x009FE16C): +0x1A104 is negative unless the game is ending.
class ScriptEngine
{
public:
	unsigned char m_pad00000[0x1A104];
	int m_1a104; // +0x1A104
};

extern ScriptEngine *TheScriptEngine;

class GameWindowTransitionsHandler
{
public:
	bool isFinished();
};

extern GameWindowTransitionsHandler *TheTransitionHandler;

// TheDisplay (0x009FE9D8): vslots 87 and 88 hold the store back.
class Display
{
public:
#define DISPLAY_SLOT(N) virtual void slot##N();
	DISPLAY_SLOT(00) DISPLAY_SLOT(01) DISPLAY_SLOT(02) DISPLAY_SLOT(03) DISPLAY_SLOT(04)
	DISPLAY_SLOT(05) DISPLAY_SLOT(06) DISPLAY_SLOT(07) DISPLAY_SLOT(08) DISPLAY_SLOT(09)
	DISPLAY_SLOT(10) DISPLAY_SLOT(11) DISPLAY_SLOT(12) DISPLAY_SLOT(13) DISPLAY_SLOT(14)
	DISPLAY_SLOT(15) DISPLAY_SLOT(16) DISPLAY_SLOT(17) DISPLAY_SLOT(18) DISPLAY_SLOT(19)
	DISPLAY_SLOT(20) DISPLAY_SLOT(21) DISPLAY_SLOT(22) DISPLAY_SLOT(23) DISPLAY_SLOT(24)
	DISPLAY_SLOT(25) DISPLAY_SLOT(26) DISPLAY_SLOT(27) DISPLAY_SLOT(28) DISPLAY_SLOT(29)
	DISPLAY_SLOT(30) DISPLAY_SLOT(31) DISPLAY_SLOT(32) DISPLAY_SLOT(33) DISPLAY_SLOT(34)
	DISPLAY_SLOT(35) DISPLAY_SLOT(36) DISPLAY_SLOT(37) DISPLAY_SLOT(38) DISPLAY_SLOT(39)
	DISPLAY_SLOT(40) DISPLAY_SLOT(41) DISPLAY_SLOT(42) DISPLAY_SLOT(43) DISPLAY_SLOT(44)
	DISPLAY_SLOT(45) DISPLAY_SLOT(46) DISPLAY_SLOT(47) DISPLAY_SLOT(48) DISPLAY_SLOT(49)
	DISPLAY_SLOT(50) DISPLAY_SLOT(51) DISPLAY_SLOT(52) DISPLAY_SLOT(53) DISPLAY_SLOT(54)
	DISPLAY_SLOT(55) DISPLAY_SLOT(56) DISPLAY_SLOT(57) DISPLAY_SLOT(58) DISPLAY_SLOT(59)
	DISPLAY_SLOT(60) DISPLAY_SLOT(61) DISPLAY_SLOT(62) DISPLAY_SLOT(63) DISPLAY_SLOT(64)
	DISPLAY_SLOT(65) DISPLAY_SLOT(66) DISPLAY_SLOT(67) DISPLAY_SLOT(68) DISPLAY_SLOT(69)
	DISPLAY_SLOT(70) DISPLAY_SLOT(71) DISPLAY_SLOT(72) DISPLAY_SLOT(73) DISPLAY_SLOT(74)
	DISPLAY_SLOT(75) DISPLAY_SLOT(76) DISPLAY_SLOT(77) DISPLAY_SLOT(78) DISPLAY_SLOT(79)
	DISPLAY_SLOT(80) DISPLAY_SLOT(81) DISPLAY_SLOT(82) DISPLAY_SLOT(83) DISPLAY_SLOT(84)
	DISPLAY_SLOT(85) DISPLAY_SLOT(86)
#undef DISPLAY_SLOT
	virtual bool slot87();
	virtual bool slot88();
};

extern Display *TheDisplay;

// BFME 1's HideInGameChat and HideDiplomacy, then the rowed 0x0050E9D3.
void Rva004E855CClose(void);
void Rva004E400DEnable(void);
void Rva0050E9D3Enable(void);

class Mouse
{
public:
#define MOUSE_SLOT(N) virtual void slot##N();
	MOUSE_SLOT(00) MOUSE_SLOT(01) MOUSE_SLOT(02) MOUSE_SLOT(03) MOUSE_SLOT(04)
	MOUSE_SLOT(05) MOUSE_SLOT(06) MOUSE_SLOT(07) MOUSE_SLOT(08) MOUSE_SLOT(09)
	MOUSE_SLOT(10) MOUSE_SLOT(11) MOUSE_SLOT(12) MOUSE_SLOT(13) MOUSE_SLOT(14)
	MOUSE_SLOT(15) MOUSE_SLOT(16) MOUSE_SLOT(17) MOUSE_SLOT(18)
#undef MOUSE_SLOT
	virtual void setCursor(int cursor);
};

extern Mouse *TheMouse;

// TheShell (0x00E01E48): the rowed 0x0035C7CF (BFME 1's showShell).
class Shell
{
public:
	void rva0035C7CF(bool flag);
	void push(AsciiString name, bool flag);
};

extern Shell *TheShell;

// Retail 0x0043CB48, 378 bytes: BFME 1's finishShowPurchaseScience
// (ControlBar_finishShowPurchaseScience.cpp), the donor and source of the
// name. Nothing happens while a store is open, the store is disabled, a
// menu is up, the palantir has no override window, another screen holds it
// back, the game is loading or ending, a transition is running or the
// display is busy. Otherwise a single player game outside mode 6 pauses,
// the chat, diplomacy and side panels close and the shell pushes
// "SpellStore.apt". BFME 2 adds the enable flag, 0x00E04910, the pause and
// the 0x0050E9D3 and side panel calls.
void finishShowPurchaseScience(void)
{
	if (g_Va00E03314)
		return;
	if (!((unsigned char *)Rva0043C9B3Get())[4])
		return;
	if (TheInGameUI->slot95())
		return;
	if (!theRadarWindowOverrideSource || !theRadarWindowOverrideSource->hasOverrideWindow())
		return;
	if (g_Va00E0330C)
		return;
	if (g_Va00E04910)
		return;
	if ((unsigned char)((Rva0023C902 *)TheGameLogic)->rva0023C902())
		return;
	if (TheGameLogic->m_6d)
		return;
	if (TheScriptEngine->m_1a104 >= 0)
		return;
	if (!TheTransitionHandler->isFinished())
		return;
	if (TheDisplay)
	{
		if (TheDisplay->slot88())
			return;
		if (TheDisplay->slot87())
			return;
	}
	if (g_Va00E048D0)
		return;

	GameLogic *logic = TheGameLogic;
	if (!logic->isInMultiplayerGame() && logic->m_110 != 6)
		logic->rva0023CD9E(true, 0, true);
	Rva004E855CClose();
	Rva004E400DEnable();
	Rva0050E9D3Enable();
	((Rva005CB265 *)TheInGameUI->rva000CF155())->Rva005CB265::rva005CB265();
	TheMouse->setCursor(2);
	TheShell->rva0035C7CF(false);
	TheShell->push(AsciiString("SpellStore.apt"), false);
	TheInGameUI->slot94(true);
}

// TheGameText (0x009FF0BC), as in Drawable_rva00276641.cpp: vslot 14
// fetches by AsciiString label.
class GameTextInterface
{
public:
	virtual ~GameTextInterface() {}
	virtual void slot00() = 0;
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
	virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
	virtual UnicodeString fetch(const AsciiString &label, bool *exists = 0) = 0;
};

extern GameTextInterface *TheGameText;

// The screen's rowed OnBttnClose 0x0043C7C9, layout query 0x0043C933,
// science check 0x0043C6EA (on the +0x288 holder) and button state setter
// 0x0043C8E4, named by their rows' views.
class Rva0043D3DA
{
public:
	void rva0043C7C9(int unused);
};

int Rva0043C933Get(void);

class Rva0043C6EA
{
public:
	bool rva0043C6EA(int science);
};

class Rva0043C8E4
{
public:
	void rva0043C8E4(int slot, int state);
};

// The screen's Apt movie (rowed 0x00222547) and the window manager's
// ActionScript call 0x00222A8B.
class GameWindow;
GameWindow *Rva00222547Get(GameWindow *window);

class Rva00222A8BTarget
{
public:
	int invoke(void *window, const char *function, int argc, const char *arg,
		void *arg1, void *arg2, void *arg3, void *arg4);
};

// Retail 0x0043CD3C, 1059 bytes: the store's frame update; BFME 1's
// Rva005999B0Screen::frameUpdate (Palantir/SpellStore005999B0.cpp) is the
// donor. Without the palantir's override window the store closes. Once
// initialized it switches the "SetLayout" to the game's mode, toggles the
// help text with the hovered button, fills the help and description of a
// newly hovered button (with the disabled tooltip when its first unchosen
// science cannot be bought), publishes the points left and refreshes each
// slot's state. BFME 2 reads the buttons' own label and description
// getters, asks the science holder instead of the player and adds the
// chosen and buyable states.
void AptSpellStore::rva0043CD3C()
{
	if (!theRadarWindowOverrideSource || !theRadarWindowOverrideSource->hasOverrideWindow())
	{
		((Rva0043D3DA *)this)->rva0043C7C9(0);
		return;
	}
	if (!m_2a0)
		return;
	int mode = Rva0043C933Get();
	if (mode != m_2a4)
	{
		((Rva00222A8BTarget *)g_bfmeAptWindowManager)->invoke(Rva00222547Get((GameWindow *)this), "SetLayout", 1,
			mode == 2 ? "_multiplayer" : mode == 0 ? "_campaignGood" : "_campaignEvil", 0, 0, 0, 0);
		m_2a4 = mode;
		return;
	}
	Player *player = ThePlayerList->getLocalPlayer();
	bool selected = m_hovered >= 0;
	if (selected != m_358)
	{
		((Rva00222A8BTarget *)g_bfmeAptWindowManager)->invoke(Rva00222547Get((GameWindow *)this), "ShowSpellHelpText", 1,
			selected ? "_on" : "_off", 0, 0, 0, 0);
		m_358 = selected;
	}
	if (selected && !m_359)
	{
		const CommandButton *button = (const CommandButton *)m_slots[m_hovered].m_entry;
		if (button)
		{
			static AsciiString help("APT:SpellHelpText");
			g_bfmeAptWindowManager->bfmeSetText(help, TheGameText->fetch(button->rva0035B1E9()), false);
			static AsciiString desc("APT:SpellDescription");
			static AsciiString disabled("TOOLTIP:ScienceDisabled");
			{
				UnicodeString text = TheGameText->fetch(button->rva0035B26F());
				for (unsigned int i = 0; i < button->scienceCount(); ++i)
				{
					ScienceType science = button->m_sciences[i];
					if (!m_sciences.v00(science))
					{
						if (science != (ScienceType)-1
							&& (player->rva002AB82D((CreateAHeroData *)science)
								|| player->rva002AB855((CreateAHeroData *)science)
								|| !TheScienceStore->playerHasRootPrereqsForScience((const Player *)&m_sciences, science)))
						{
							text += (unsigned short)10;
							text += TheGameText->fetch(disabled);
						}
						break;
					}
				}
				g_bfmeAptWindowManager->bfmeSetText(desc, text, false);
			}
			m_359 = true;
		}
	}
	int points = m_sciences.v04();
	if (points != m_350)
	{
		static AsciiString pointsKey("APT:SpellStoreSpellPoints");
		UnicodeString text;
		text.format(L"%d", points);
		g_bfmeAptWindowManager->bfmeSetText(pointsKey, text, false);
		m_350 = points;
	}
	for (int i = 0; i < 20; ++i)
	{
		int state = 0;
		const CommandButton *button = (const CommandButton *)m_slots[i].m_entry;
		if (button)
		{
			ScienceType science = *button->m_sciences;
			if (science != (ScienceType)-1)
			{
				if (((Rva0043C6EA *)&m_sciences)->rva0043C6EA(science))
					state = 2;
				else if (!m_sciences.v00(science))
					state = TheScienceStore->rva001FF4D3(&m_sciences, science) ? 5 : 1;
				else
					state = m_slots[i].m_04 == 5 ? 4 : 3;
			}
		}
		if (state != m_slots[i].m_04)
		{
			((Rva0043C8E4 *)this)->rva0043C8E4(i, state);
			m_slots[i].m_04 = state;
		}
	}
}

// RegistryAsciiPath.cpp's "text + AsciiString" node (rowed 0x002226E5) and
// its materializer 0x0022309D.
class Rva000B3F84Pair
{
public:
	Rva000B3F84Pair() {}

	const char *m_ptr;
	int m_len;
};

// The declared copy constructor keeps the operator+ result in place when
// it binds to the helper's reference (retail passes it without a copy).
struct Rva002226E5TextPlusString
{
	Rva002226E5TextPlusString(const Rva002226E5TextPlusString &other);
	operator AsciiString();

	Rva000B3F84Pair m_left;
	const AsciiString *m_right;
};

Rva002226E5TextPlusString operator+(const char *left, const AsciiString &right);

// Retail 0x0043D35A, 78 bytes: converts a "text + AsciiString" node and
// copies the converted temporary into the return value. Its one caller is
// the texture preload below.
AsciiString Rva0043D35AMakeAsciiString(const Rva002226E5TextPlusString &text)
{
	return const_cast<Rva002226E5TextPlusString &>(text);
}

class FileSystem
{
public:
	bool doesFileExist(const char *filename) const;
};

extern FileSystem *TheFileSystem;

// The texture handle's views (W3D: TextureClass and its filter at +0x1C):
// rowed BFME2LoadParticleTexture 0x00132D89, getFilter 0x00132856 and the
// quality forwarder 0x00132FE9.
class TextureClass
{
public:
	void Release_Ref();
};

template <class T>
class RefCountPtr
{
public:
	~RefCountPtr() { if (m_ptr) m_ptr->Release_Ref(); }

	T *m_ptr;
};

class BFME2ParticleTextureHandle : public RefCountPtr<TextureClass>
{
};

BFME2ParticleTextureHandle BFME2LoadParticleTexture(const char *filename, int a, int b);

// WW3D's TextureFilterClass: min, mag and mip filters, then the U and V
// address modes (1 clamps).
class ShroudFilter
{
public:
	int m_minFilter;
	int m_magFilter;
	int m_mipFilter;
	int m_uAddressMode; // +0x0C
	int m_vAddressMode; // +0x10
};

class ShroudTexture
{
public:
	ShroudFilter *getFilter();
};

class TextureAsset
{
public:
	void rva00132FE9(bool flag);
};

// The asset list GameLogicInit.cpp and Rva00081CDFWaterTextures.cpp fill
// for the asset merge 0x0061F010: an STLport set, a pad word and a changed
// flag.
struct Rva001408C0Target;

namespace _STL
{
template <class T> struct _Identity {};
template <class T> struct less {};

template <class Key, class Value, class Identity, class Compare, class Allocator>
class _Rb_tree
{
public:
	~_Rb_tree();

private:
	void *m_storage[3];
};

template <class T, class Compare, class Allocator>
class set
{
	typedef _Rb_tree<T, T, _Identity<T>, Compare, Allocator> Tree;
	Tree m_tree;

public:
	set();
	~set() {}
};
}

typedef Rva001408C0Target *Rva001408C0Key;
typedef _STL::set<Rva001408C0Key, _STL::less<Rva001408C0Key>,
	_STL::allocator<Rva001408C0Key> > Rva001408C0Set;

struct AssetList00208F90
{
	Rva001408C0Set m_prototypes;
	unsigned int m_treeLayoutPad;
	bool m_changed;
	AssetList00208F90() : m_treeLayoutPad(0), m_changed(true) {}
	AssetList00208F90 &operator<<(const AsciiString &name);
};

void bfmeMergeReceiverKeys(int value);

// The 0x00A099F8 singleton GameLogicInit.cpp brackets its loads with; the
// spell store merges its textures only when it exists.
class Rva009EB960;
extern Rva009EB960 *Rva0134FAA0;

// Retail 0x0043D467, 356 bytes: called once by GameLogic 0x00248278. It
// preloads the spell store's numbered textures "apt_spellstore_1",
// "apt_spellstore_2", ... (each as .dds, else .tga, under art/textures/)
// until one is missing, clamping their U and V addressing.
void rva0043D467(void)
{
	static const char *const extensions[] = { "dds", "tga" };

	if (!TheFileSystem)
		return;
	for (int index = 1; ; )
	{
		AsciiString name;
		unsigned int i;
		for (i = 0; i < sizeof(extensions) / sizeof(extensions[0]); ++i)
		{
			name.format("apt_spellstore_%d.%s", index, extensions[i]);
			if (TheFileSystem->doesFileExist(Rva0043D35AMakeAsciiString("art/textures/" + name).str()))
				break;
		}
		if (i >= sizeof(extensions) / sizeof(extensions[0]))
			break;
		BFME2ParticleTextureHandle texture = BFME2LoadParticleTexture(name.str(), 1, 0);
		((ShroudTexture *)&texture)->getFilter()->m_vAddressMode = 1;
		((ShroudTexture *)&texture)->getFilter()->m_uAddressMode = 1;
		((TextureAsset *)&texture)->rva00132FE9(true);
		if (Rva0134FAA0)
		{
			AssetList00208F90 assets;
			assets << name;
			bfmeMergeReceiverKeys((int)&assets);
		}
		++index;
	}
}
