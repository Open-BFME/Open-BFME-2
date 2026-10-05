// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// BFME2's LAN lobby gadget initialization callback, retail 0x00445DA5
// (153 bytes). The screen's constructor 0x00445EE3 binds it as a member
// function pointer on the whole screen object (vftable 0x00C3E0F8; the
// callback interface BfmeAptScreenLanLobby.cpp views sits at +0x27C).
//
// Donor: Open-BFME-1 GUICallbacks/Apt/BfmeAptScreenLanLobby_onInitGadget.cpp
// (BfmeAptScreenLanLobby::_bfme_onInitGadget, BFME1 0x005187F0); the name is
// the donor's identity for the same role and "LanLobby::" gadget names.
// BFME2 target evidence: only CustomGamesList (stored at +0x6A8, games
// tooltip 0x00445BAA) and NameEntry remain; NameEntry's link helper at
// +0x6AC (destroyed by ??1Rva0031455E) attaches through its vslot 1, and the
// screen clears +0x6C0 afterwards.

#include "unicode_string.h"

extern "C" int __cdecl strcmp(const char *left, const char *right);

class WinInstanceData;

class GameWindow
{
public:
	int winSetTooltipFunc(void (*tooltip)(GameWindow *window, WinInstanceData *data, unsigned int mouse));
};

class BfmeKeyLC;

void GadgetListBoxReset(GameWindow *window);
void GadgetTextEntrySetText(GameWindow *window, UnicodeString text);
void __cdecl Rva0032060D(GameWindow *window, int value);
void bfmeGo924F(BfmeKeyLC *key, unsigned short value);

// The custom games list tooltip, unrowed 0x00445BAA (507 bytes; BFME1's is
// Rva00518150LanLobbyTooltip), pinned by address.
void Rva00445BAALanLobbyTooltip(GameWindow *window, WinInstanceData *data, unsigned int mouse);

class Rva0031455E
{
public:
	virtual void v0();
	virtual void attach(GameWindow *window);
};

class BfmeAptScreenLanLobby
{
public:
	void _bfme_onInitGadget(const char *name, void *argument, GameWindow *window);

private:
	unsigned char m_pad000[0x6A8];
	GameWindow *m_customGamesList; // +0x6A8
	Rva0031455E m_nameEntryLink; // +0x6AC
	unsigned char m_pad6b0[0x6C0 - 0x6B0];
	unsigned char m_6c0; // +0x6C0
};

void BfmeAptScreenLanLobby::_bfme_onInitGadget(const char *name, void *, GameWindow *window)
{
	if (window != 0)
	{
		if (strcmp(name, "LanLobby::CustomGamesList") == 0)
		{
			GadgetListBoxReset(window);
			m_customGamesList = window;
			window->winSetTooltipFunc(Rva00445BAALanLobbyTooltip);
		}
		else if (strcmp(name, "LanLobby::NameEntry") == 0)
		{
			bfmeGo924F((BfmeKeyLC *)window, 0x0c);
			GadgetTextEntrySetText(window, UnicodeString::TheEmptyString);
			Rva0032060D(window, 0x80);
			m_nameEntryLink.attach(window);
			m_6c0 = 0;
		}
	}
}
