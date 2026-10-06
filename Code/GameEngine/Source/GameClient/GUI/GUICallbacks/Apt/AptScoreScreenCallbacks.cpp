// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// BFME2's score screen Apt callbacks, 0x0051BF75 onward, bound by these
// names ("AptScoreScreen::OnInitialized" ...) as member pointers by the
// screen's registration; that binding is their only reference. The class
// is named for the strings' prefix. +0x27C is the screen's state.

#include <vector>
#include "unicode_string.h"

extern "C" int __cdecl strcmp(const char *left, const char *right);
extern "C" char *__cdecl strcpy(char *destination, const char *source);
extern "C" __declspec(dllimport) int __cdecl sprintf(char *buffer, const char *format, ...);

// The objectives summary at +0x288: a count at +4 and up to eight
// checked flags at +0x28.
struct AptScoreObjectives
{
	unsigned char m_pad00[4];
	int m_count; // +0x04
	unsigned char m_pad08[0x28 - 0x08];
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
};

void GadgetTextEntrySetText(GameWindow *textEntry, UnicodeString text);
void bfmeGo924F(BfmeKeyLC *textEntry, unsigned short maxLength);

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
class Rva002BA8F1Logic
{
public:
	bool rva002B3740();
};

extern class Rva002BA8F1Logic *g_009FEF10;

class AptScoreScreen
{
public:
	void OnInitialized(const char *unused);
	void Timeline(const char *unused);
	void RestartGame(const char *unused);
	void Continue(const char *unused);
	void InitGadgets(const char *name, void *argument, GameWindow *window);
	void RenameCancel(const char *unused);
	void objectiveChecked(int index, char *result, bool skip);
	void heroVetUpgrade(int index, char *result, bool skip);

private:
	unsigned char m_pad000[0x27C];
	int m_state; // +0x27C
	unsigned char m_pad280[0x288 - 0x280];
	AptScoreObjectives *m_objectives; // +0x288
	_STL::vector<bool> m_heroUpgrades; // +0x28C
	GameWindow *m_units; // +0x2A0
	GameWindow *m_rename; // +0x2A4
	int m_renaming; // +0x2A8
	int m_renameIndex; // +0x2AC
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
		bfmeGo924F((BfmeKeyLC *)window, 20);
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

// Retail's strcpy call lands on the import thunk rowed as ji_00629176.
#pragma comment(linker, "/alternatename:_strcpy=?ji_00629176@@YAXXZ")
