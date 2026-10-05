// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD
//
// BFME2's save/load screen Apt callbacks, 0x00433DB1 onward, bound by these
// names ("AptSaveLoad::OnClosed" ...) as member pointers by the screen's
// registration; that binding is their only reference. The class is named
// for the strings' prefix. +0x27C is the screen's state.

#include "unicode_string.h"

extern "C" int __cdecl strcmp(const char *left, const char *right);

class GameWindow;
class BfmeKeyLC;

void GadgetTextEntrySetText(GameWindow *textEntry, UnicodeString text);
void bfmeGo924F(BfmeKeyLC *textEntry, unsigned short maxLength);
void Rva0032060D(GameWindow *textEntry, int value);

// Rva00433D27Enable.cpp's 0x00433D27.
void Rva00433D27Enable();

// TheShell (VA 0x00E01E48, the ledger's g_Va00A01E48).
struct GlobalA01E48
{
	unsigned char m_pad[0x54];
	bool m_54; // +0x54
	unsigned char m_pad55[0x5D - 0x55];
	bool m_5d; // +0x5D
};

extern struct GlobalA01E48 *g_Va00A01E48;

// The pending confirmation at +0x280 keeps its kind at +0x28.
struct AptSaveLoadPending
{
	unsigned char m_pad[0x28];
	int m_kind; // +0x28
};

class AptSaveLoad
{
public:
	void OnClosed(const char *unused);
	void Cancel(const char *unused);
	// Bound as "AptSaveLoad::OnInitialized" and
	// "AptSaveLoad::ConfirmationCancel" (and by the options screen as
	// "AptOptions::OnInitialized"): one body or several folded, so it keeps
	// its address.
	void rva00433DF1(const char *unused);
	// Bound without a name as the saved-game prompt's answer (0x00434EFA),
	// so it keeps its address.
	void rva00433D71(int button);
	void Delete(const char *unused);
	void Load(const char *unused);
	void ConfirmationOk(const char *unused);
	void InitGadgets(const char *name, void *argument, GameWindow *window);

	// Unrowed 0x00434AAE (220 bytes; fills the lists), pinned by address.
	void rva00434AAE();

	// Unrowed 0x0043448C, 0x00435224 and 0x00434B8A, pinned by address.
	void rva0043448C();
	void rva00435224();
	void rva00434B8A();

	// Unrowed 0x00433F7F (94 bytes; banked), pinned by address.
	int rva00433F7F();

private:
	unsigned char m_pad000[0x27C];
	int m_state; // +0x27C
	AptSaveLoadPending *m_pending; // +0x280
	unsigned char m_pad284[0x288 - 0x284];
	GameWindow *m_gameList; // +0x288
	GameWindow *m_autoSaveList; // +0x28C
	GameWindow *m_fileName; // +0x290
	unsigned char m_pad294[0x29C - 0x294];
	bool m_29c; // +0x29C
	unsigned char m_pad29d[0x2A0 - 0x29D];
	int m_mode; // +0x2A0
	unsigned char m_pad2a4[0x2A8 - 0x2A4];
	int m_2a8; // +0x2A8
};

// The rowed 0x00433FDD (Rva00433FDDSet.cpp's view of this screen).
class Rva00433FDD
{
public:
	void rva00433FDD();
};

// Retail 0x00433D71, 37 bytes. Name unknown. Keeps the answer to the
// "APT:MultiplayerGameSaved" prompt: button 2 gives 1, button 3 gives 2.
void AptSaveLoad::rva00433D71(int button)
{
	if (button == 2)
		m_2a8 = 1;
	else if (button == 3)
		m_2a8 = 2;
}

// Retail 0x00433DB1, 47 bytes: "AptSaveLoad::OnClosed" flags the shell
// unless a kind 6 confirmation closed it in state 6.
void AptSaveLoad::OnClosed(const char *unused)
{
	if (g_Va00A01E48)
	{
		if (m_state != 6 || !m_pending || m_pending->m_kind != 6)
			g_Va00A01E48->m_54 = true;
	}
	Rva00433D27Enable();
}

// Retail 0x00433DE0, 17 bytes: "AptSaveLoad::Cancel".
void AptSaveLoad::Cancel(const char *unused)
{
	if (m_state == 0)
		Rva00433D27Enable();
}

// Retail 0x00433DF1, 13 bytes: bound as "AptSaveLoad::OnInitialized",
// "AptSaveLoad::ConfirmationCancel" and "AptOptions::OnInitialized".
void AptSaveLoad::rva00433DF1(const char *unused)
{
	m_state = 1;
}

// Retail 0x00434318, 31 bytes: "AptSaveLoad::Delete".
void AptSaveLoad::Delete(const char *unused)
{
	if (m_state == 0 && rva00433F7F())
		m_state = 16;
}

// Retail 0x004348CA, 76 bytes: "AptSaveLoad::Load" takes the selected
// entry (0x00433F7F) and loads it: state 14 with +0x29C, 0x0043448C in mode
// 4, else state 3.
void AptSaveLoad::Load(const char *unused)
{
	if (m_state == 0)
	{
		m_pending = (AptSaveLoadPending *)rva00433F7F();
		if (m_29c)
			m_state = 14;
		else if (m_mode == 4)
			rva0043448C();
		else
			m_state = 3;
	}
}

// Retail 0x004357CF, 74 bytes: "AptSaveLoad::ConfirmationOk" finishes the
// confirmation the state (0x12..0x15) is waiting on.
void AptSaveLoad::ConfirmationOk(const char *unused)
{
	if (m_state == 0x12)
	{
		if (m_mode == 4)
			rva0043448C();
		else
			m_state = 3;
	}
	else if (m_state == 0x13)
		rva00435224();
	else if (m_state == 0x14)
		rva00434B8A();
	else if (m_state == 0x15)
		((Rva00433FDD *)this)->rva00433FDD();
}

// Retail 0x00435172, 178 bytes: "AptSaveLoad::InitGadgets" keeps the
// "GameList" and "AutoSaveList" boxes (state 2) and sets up the emptied
// "FileNameTextEntry" (40 characters), then fills the lists.
void AptSaveLoad::InitGadgets(const char *name, void *argument, GameWindow *window)
{
	if (!window)
		return;
	if (strcmp(name, "GameList") == 0)
	{
		m_gameList = window;
		m_state = 2;
	}
	else if (strcmp(name, "AutoSaveList") == 0)
	{
		m_autoSaveList = window;
		m_state = 2;
	}
	else if (strcmp(name, "FileNameTextEntry") == 0)
	{
		m_fileName = window;
		GadgetTextEntrySetText(window, UnicodeString(L""));
		bfmeGo924F((BfmeKeyLC *)window, 40);
		Rva0032060D(window, 8);
		rva00434AAE();
		if (m_state == 0)
			m_state = 1;
	}
}
