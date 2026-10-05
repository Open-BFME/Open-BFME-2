// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /O1 /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
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
#include <list>

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

// Window manager vslots 44 and 45 are registerTabList and clearTabList
// (GameWindowManager_registerTabList.cpp; vtable 0x007C7C90). Retail copies
// the window into a temporary before the push_back, so the list is spelled
// here with int elements: its out-of-line bodies are the int list's
// (ICF-identical to the GameWindow * list) and already pinned.
class GameWindowManager
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
	virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
	virtual void registerTabList(_STL::list<int> tabList);
	virtual void clearTabList();
};

extern GameWindowManager *TheWindowManager;

class BfmeAptScreenLanLobby
{
public:
	void _bfme_onInitGadget(const char *name, void *argument, GameWindow *window);
	void rva00446386(bool enable);

private:
	unsigned char m_pad000[0x6A8];
	GameWindow *m_customGamesList; // +0x6A8
	Rva0031455E m_nameEntryLink; // +0x6AC
	unsigned char m_pad6b0[0x6B4 - 0x6B0];
	GameWindow *m_6b4; // +0x6B4
	unsigned char m_pad6b8[0x6BB - 0x6B8];
	bool m_6bb; // +0x6BB
	unsigned char m_pad6bc[0x6C0 - 0x6BC];
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

// Retail 0x00446386, 183 bytes. Name unknown. Tracks the flag at +0x6BB;
// when it turns on (and the window at +0x6B4 exists) it replaces the window
// manager's tab list with a one-entry list holding that window; when it
// turns off it only clears the tab list. /GX (not /EHsc) keeps retail's
// state reset before the list's destructor, as for registerTabList.
void BfmeAptScreenLanLobby::rva00446386(bool enable)
{
	if (enable == m_6bb)
		return;
	GameWindow *window = m_6b4;
	if (!window)
		return;
	m_6bb = enable;
	if (enable)
	{
		_STL::list<int> tabList;
		tabList.push_back((int)m_6b4);
		TheWindowManager->clearTabList();
		TheWindowManager->registerTabList(tabList);
	}
	else
		TheWindowManager->clearTabList();
}
