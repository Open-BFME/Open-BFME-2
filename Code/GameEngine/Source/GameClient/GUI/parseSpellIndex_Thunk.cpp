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
// whether a science is already chosen; the rowed 0x0043D5CB adds one.
class Player;

class Rva0043D3A8
{
public:
	virtual bool v00(ScienceType science);
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

// The spell book's buttons: unrowed 0x0035B19E (37 bytes) returns the
// image its +0xFC index picks from the list at +0xEC, or null; pinned by
// address. The sciences start at +0xA4 as in SpellStoreEntry.
class CommandButton
{
public:
	const Image *rva0035B19E() const;

	unsigned char m_pad000[0xA4];
	ScienceType *m_sciences; // +0xA4
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
