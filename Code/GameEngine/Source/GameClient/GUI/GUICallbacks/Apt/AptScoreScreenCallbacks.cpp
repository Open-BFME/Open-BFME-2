// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD
//
// BFME2's score screen Apt callbacks, 0x0051BF75 onward, bound by these
// names ("AptScoreScreen::OnInitialized" ...) as member pointers by the
// screen's registration; that binding is their only reference. The class
// is named for the strings' prefix. +0x27C is the screen's state.

#include "unicode_string.h"

extern "C" int __cdecl strcmp(const char *left, const char *right);

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

private:
	unsigned char m_pad000[0x27C];
	int m_state; // +0x27C
	unsigned char m_pad280[0x2A0 - 0x280];
	GameWindow *m_units; // +0x2A0
	GameWindow *m_rename; // +0x2A4
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
