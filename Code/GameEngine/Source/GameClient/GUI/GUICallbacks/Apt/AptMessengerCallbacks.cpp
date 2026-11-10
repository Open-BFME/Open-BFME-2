// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// BFME2's messenger screen Apt callbacks "AptMessenger::OnButtonSend",
// "AptMessenger::OnBttn_0" and "AptMessenger::OnBttn_1", bound by those
// names as member pointers by the screen's registration; that binding is
// their only reference. The class is named for the strings' prefix. Both
// buttons act on the active tab (Rva005118F3Show.cpp's g_Va00E046BC).
// "AptMessenger::GameWindowSize" is a render callback, "AptMessenger::IsOpen"
// a static query bound through the free-function holder 0x004106FA and
// "AptMessenger::OnMessengerBttn" a static callback bound through 0x0023E8D8.
//
// The screen object is itself the window: GameWindowSize runs GameWindow's
// members on its own this. Its vftable 0x00C659A0 (destroyed by
// 0x005125ED) supplies the message handler, tab factory, update and tab
// teardown below; slot 15 answers "ShowPlayerButtons" and slot 16 makes a
// tab. /EHsc is for the tab factory's new-expression.

// Retail calls _mbscpy through the import thunk at 0x00629176.
#define _CRTIMP
#include <mbstring.h>
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include "unicode_string.h"

#include <string.h>

// Rva00511730Save.cpp's g_Va00E048C0, the chat entry's kept text.
extern UnicodeString g_Va00E048C0;

extern int g_Va00E046BC;

// The messenger's kept position (Apt's "MessengerX" and "MessengerY"
// strings) and maximized state. Defined once here, loader-zeroed: the
// set/get query paths above write before any meaningful read, and no
// ledger address is claimed for any of them yet.
char g_Va00E046C0[256] = {};
char g_Va00E047C0[256] = {};
bool g_Va00DD13D8 = true;

void __cdecl Rva005118F3Show(int index, bool clear);

// Rva00511730Save.cpp's close (0x00511730) helper; its open helper
// 0x005116C2 is AptMessenger::OpenScreen, declared in the class below.
void __cdecl Rva00511730(int unused);

#include <stdlib.h>
#include <stdio.h>

#include "../../../../Common/GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

class LANAPI;
extern LANAPI *TheLAN;

// TheIMEManager (0x00DFE728); slot names stay offset placeholders.
class IMEManager
{
public:
	virtual void m00() = 0;
	virtual void m04() = 0;
	virtual void m08() = 0;
	virtual void m0C() = 0;
	virtual void m10() = 0;
	virtual void m14() = 0;
	virtual void m18() = 0;
	virtual void m1C() = 0;
	virtual void m20() = 0;
	virtual void m24() = 0;
	virtual void m28() = 0;
	virtual void m2C() = 0;
	virtual void m30() = 0;
	virtual void m34() = 0;
	virtual void m38() = 0;
	virtual void m3C() = 0;
};

extern IMEManager *TheIMEManager;

// TheMouse (0x00DFDCA0) and its current button state at +0x4F0C, laid out
// as Zero Hour's MouseIO (left and right state at +0x18 and +0x24).
struct MouseIO
{
	unsigned char m_pad00[0x18];
	int leftState; // +0x18
	int leftEvent; // +0x1C
	int leftFrame; // +0x20
	int rightState; // +0x24
};

class Mouse
{
public:
	const MouseIO *getMouseStatus() { return &m_currMouse; }

private:
	unsigned char m_pad0000[0x4F0C];
	MouseIO m_currMouse; // +0x4F0C
};

extern Mouse *TheMouse;

#include "../../../../../Include/Common/Rva00222A8BTarget.h"

class Rva00222A8BTarget;
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

// The rowed dword getter 0x00314126 (+0x210) on the screen's window.
class Rva00314126DwordField
{
public:
	int get() const;
};

// The object that getter answers while the screen closes (state 4): a
// polymorphic object whose slot 1 is its deleting destructor.
class Rva00511E6DChild
{
public:
	virtual void v00();
	virtual ~Rva00511E6DChild();
	virtual void v08();
	virtual void v0C(int value);
};

// The AptMpGameSetup chat panel (0x00E06394) and its rowed 0x0057FDA1 test.
class Rva0057FD6E
{
public:
	bool rva0057FDA1();
};

extern int g_Va00E06394;

// AptGlobalQueryCallbacks.cpp's global Apt callback "PlaySound"
// (0x00412A51) plays the named audio event.
void __cdecl PlaySound(const char *eventName);

// The tab each messenger tab index shows (0x00C65734).
static const int s_tabIds[2] = { 0, 1 };

// The messenger's incoming-message listener: vftable 0x00C6573C, built by
// the unrowed 0x005114BD. The class is named for that constructor.
class Rva005114BD
{
public:
	virtual void rva00511620(int tab, int unused);
};

// The messenger instance (Rva00511730Save.cpp's AptMessenger::s_instance).
struct Rva00511730State;

// A render callback's position and size: two floats each (the type is
// inferred from use).
#include "../../../../../../Libraries/Include/Lib/Coord2D.h"

class Rva005B000C;

class GameWindow
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual bool v15();
	virtual Rva005B000C *v16(int index);

	int winSetPosition(int x, int y);
	int winGetPosition(int *x, int *y);
	int winSetSize(int width, int height);
	int winGetSize(int *width, int *height);
};

// A tab's chat entry; its recovered 0x005B000C sends the typed line, pinned
// by address.
// Call-only view of the query/send receiver now owned in ChatWindowsInGame.cpp.
#include "../../../../../Include/Common/ChatWindowsInGame.h"
class Rva005AFC21Class {public:void rva005AFC21(GameWindow*);};
class Rva005AFC4CClass {public:void rva005AFC4C(GameWindow*);};
class Rva005B000C
{
public:
	virtual void v00();
	virtual void v01();
	virtual ~Rva005B000C();


	// The recovered tab message handler is called through ChatWindowsInGame.

	// Unrowed 0x005AFC21 and 0x005AFC4C keep the tab's chat and player
	// list windows, pinned by address.
	void rva005AFC21(GameWindow *window);
	void rva005AFC4C(GameWindow *window);
};

// The native20B constructor at 0x005AF9EF installs the same C7287C
// vtable and receives the independently proven 0x24-byte chat-tab allocation.
class Rva005AF9EF : public Rva005B000C
{
public:
	Rva005AF9EF();

private:
	unsigned char m_pad004[0x24 - 0x4];
};

// The native Apt screen base handler is rowed at 0x0051274F.
// This call-only view preserves the complete-this pointer; its full layout
// remains in BfmeAptGameWindowMessages.cpp, alongside the native vftable evidence.
class _bfme_AptGameWindow
{
public:
	int rva0051274F(int message, unsigned int wParam, unsigned int lParam);
};

// The rowed 0x005AFD43 keeps a tab's chat entry window and its text.
class Rva005AFD43
{
public:
	void rva005AFD43(GameWindow *window, const UnicodeString &text);
};

class AptMessengerOnline { public: void OnBttnInvite(); };	// 0x005AE7C6 (WB)
class AptMessenger : public GameWindow
{
public:
 static AptMessenger *s_instance;
	friend class Rva005114BD;

public:
	void OnButtonSend(const char *unused);
	void InitGadgets(const char *name, void *argument, GameWindow *window);
	void OnBttn_0(const char *unused);
	void OnBttn_1(const char *unused);
	void GameWindowSize(const Coord2D *position, const Coord2D *size, void *unused3, void *unused4);
	static void IsOpen(int query, char *result, bool skip);
	static void OnMessengerBttn(const char *unused);
	static void OpenScreen();
	void rva00511AD4(int query, char *value, bool set);
	int rva00511990(int message, unsigned int wParam, unsigned int lParam);
	void rva005118B2();
	void rva00511826();
	int rva00511E6D();

	// Unrowed tab actions and the refresh 0x00511CE6, pinned by address.
	void rva005AE886();
	void rva005AE990();
	void rva005AEA3E();
	void rva005AE90F();
	void rva00511CE6();

private:
	unsigned char m_pad004[0x274 - 0x4];
	void *m_274; // +0x274, the screen's Apt movie
	bool m_closed; // +0x278
	unsigned char m_pad279[0x27C - 0x279];
	int m_state; // +0x27C
	Rva005B000C **m_entries; // +0x280, one per tab
	unsigned char m_pad284[0x28C - 0x284];
	struct MessengerButton *m_buttons; // +0x28C, one per button
	unsigned char m_pad290[0x298 - 0x290];
	GameWindow *m_chatEntry; // +0x298
	bool m_29c; // +0x29C
	bool m_dragging; // +0x29D
	unsigned char m_pad29e[0x2A0 - 0x29E];
	bool m_2a0; // +0x2A0
};

// Retail 0x005119E4, 27 bytes: "AptMessenger::OnButtonSend".
void AptMessenger::OnButtonSend(const char *unused)
{
	Rva005B000C *entry = m_entries[g_Va00E046BC];
	if (entry)
		reinterpret_cast<ChatWindowsInGame *>(entry)->rva005B000C();
}

// Retail 0x005AEF16, 28 bytes: "AptMessenger::OnBttn_0".
void AptMessenger::OnBttn_0(const char *unused)
{
	switch (g_Va00E046BC)
	{
	case 0:
		rva005AE886();
		break;
	case 1:
		rva005AE990();
		break;
	}
}

// Retail 0x005AEF32, 57 bytes: "AptMessenger::OnBttn_1".
void AptMessenger::OnBttn_1(const char *unused)
{
	switch (g_Va00E046BC)
	{
	case 0:
		if (m_2a0)
			rva005AE90F();
		else
			((AptMessengerOnline *)this)->OnBttnInvite();
		break;
	case 1:
		rva005AEA3E();
		break;
	}
	rva00511CE6();
}

// Retail 0x0051155B, 197 bytes: "AptMessenger::GameWindowSize" moves and
// sizes the window to the rectangle Apt renders it in when either changed.
void AptMessenger::GameWindowSize(const Coord2D *position, const Coord2D *size, void *unused3, void *unused4)
{
	int width;
	int height;
	winGetSize(&width, &height);
	int x;
	int y;
	winGetPosition(&x, &y);
	if ((float)x != position->x || (float)y != position->y
		|| (float)width != size->x || (float)height != size->y)
	{
		winSetPosition((int)position->x, (int)position->y);
		winSetSize((int)size->x, (int)size->y);
	}
}

// Retail 0x005115E9, 54 bytes: "AptMessenger::IsOpen", an Apt query
// answering "1" while the messenger is up and not closing.
void AptMessenger::IsOpen(int query, char *result, bool skip)
{
	if (query == 0 && !skip)
	{
		AptMessenger *messenger = (AptMessenger *)AptMessenger::s_instance;
		if (messenger && !messenger->m_closed)
			_mbscpy(reinterpret_cast<unsigned char *>(result), reinterpret_cast<const unsigned char *>("1"));
		else
			_mbscpy(reinterpret_cast<unsigned char *>(result), reinterpret_cast<const unsigned char *>("0"));
	}
}

// Retail 0x005117DF, 23 bytes: "AptMessenger::OnMessengerBttn" (bound at
// 0x005120A2) closes the messenger when it is up and opens it otherwise.
void AptMessenger::OnMessengerBttn(const char *unused)
{
	if (AptMessenger::s_instance)
		Rva00511730(0);
	else
		OpenScreen();
}

// Retail 0x005119FF, 213 bytes: "AptMessenger::InitGadgets" hands the chat
// entry (with the kept text) to the active tab and each tab its player and
// chat lists.
void AptMessenger::InitGadgets(const char *name, void *argument, GameWindow *window)
{
	if (strcmp(name, "Messenger::ChatEntry") == 0)
	{
		m_chatEntry = window;
		Rva005B000C *tab = m_entries[g_Va00E046BC];
		if (tab)
			((Rva005AFD43 *)tab)->rva005AFD43(window, g_Va00E048C0);
	}
	else if (strcmp(name, "Messenger::PlayersTab_0") == 0)
	{
		if (m_entries[0])
			((Rva005AFC4CClass*)m_entries[0])->rva005AFC4C(window);
	}
	else if (strcmp(name, "Messenger::PlayersTab_1") == 0)
	{
		if (m_entries[1])
			((Rva005AFC4CClass*)m_entries[1])->rva005AFC4C(window);
	}
	else if (strcmp(name, "Messenger::ChatTab_0") == 0)
	{
		if (m_entries[0])
			((Rva005AFC21Class*)m_entries[0])->rva005AFC21(window);
	}
	else if (strcmp(name, "Messenger::ChatTab_1") == 0)
	{
		if (m_entries[1])
			((Rva005AFC21Class*)m_entries[1])->rva005AFC21(window);
	}
}

// Retail 0x00511AD4, 325 bytes: the messenger's Apt variables, bound as
// "MessengerX", "MessengerY", "MessengerActiveTab", "IsMaximized",
// "ShowPlayerButtons" and "MessengerSetDragging" in that order.
void AptMessenger::rva00511AD4(int query, char *value, bool set)
{
	switch (query)
	{
	case 0:
		if (set)
			_mbscpy(reinterpret_cast<unsigned char *>(g_Va00E046C0), reinterpret_cast<const unsigned char *>(value));
		else
			_mbscpy(reinterpret_cast<unsigned char *>(value), reinterpret_cast<const unsigned char *>(g_Va00E046C0));
		break;
	case 1:
		if (set)
			_mbscpy(reinterpret_cast<unsigned char *>(g_Va00E047C0), reinterpret_cast<const unsigned char *>(value));
		else
			_mbscpy(reinterpret_cast<unsigned char *>(value), reinterpret_cast<const unsigned char *>(g_Va00E047C0));
		break;
	case 2:
		if (set)
			Rva005118F3Show(atoi(value), false);
		else if (TheGameLogic && TheGameLogic->isInMultiplayerGame() && TheLAN)
			value[0] = 0;
		else
			_snprintf(value, 0xFF, "%d", g_Va00E046BC);
		break;
	case 3:
		if (set)
		{
			g_Va00DD13D8 = value[0] == 't' || atoi(value) != 0;
			m_29c = true;
		}
		else
			_mbscpy(reinterpret_cast<unsigned char *>(value), reinterpret_cast<const unsigned char *>(g_Va00DD13D8 ? "1" : "0"));
		break;
	case 4:
		if (!set)
			_mbscpy(reinterpret_cast<unsigned char *>(value), reinterpret_cast<const unsigned char *>(v15() ? "1" : "0"));
		break;
	case 5:
		if (set)
			m_dragging = atoi(value) != 0;
		else
			_mbscpy(reinterpret_cast<unsigned char *>(value), reinterpret_cast<const unsigned char *>(m_dragging ? "1" : "0"));
		break;
	}
}

// Retail 0x00511990, 84 bytes: vftable 0x00C659A0 slot 2, the window
// message handler: the base class's, then each tab's; a tab that takes the
// message marks the screen for a refresh.
int AptMessenger::rva00511990(int message, unsigned int wParam, unsigned int lParam)
{
	int result = ((_bfme_AptGameWindow *)this)->rva0051274F(message, wParam, lParam);
	for (int i = 0; i < 2; ++i)
	{
		if (m_entries[i] && reinterpret_cast<ChatWindowsInGame *>(m_entries[i])->rva005B00C8(message, wParam, lParam))
		{
			m_29c = true;
			result = 1;
		}
	}
	return result;
}

// Retail 0x00511826, 140 bytes: vftable 0x00C659A0 slot 12 makes both
// tabs; in a multiplayer game the second is the game's chat.
void AptMessenger::rva00511826()
{
	bool multiplayer = TheGameLogic && TheGameLogic->isInMultiplayerGame();
	for (int i = 0; i < 2; ++i)
	{
		if (i == 1 && multiplayer)
			m_entries[1] = new Rva005AF9EF;
		else
		{
			Rva005B000C **entries = m_entries;
			entries[i] = v16(i);
		}
	}
}

// Retail 0x00511E6D, 235 bytes: vftable 0x00C659A0 slot 5, the update:
// closes the screen (state 2) or tears its window object down (state 4),
// updates both tabs, refreshes when marked, and stops a drag once both
// mouse buttons are up.
int AptMessenger::rva00511E6D()
{
	switch (m_state)
	{
	case 2:
		m_state = 3;
		((Rva00222A8BTarget *)g_bfmeAptWindowManager)->invoke(((AptMessenger *)AptMessenger::s_instance)->m_274, "CloseScreen", 0, 0, 0, 0, 0, 0);
		break;
	case 4:
	{
		Rva00511E6DChild *child = (Rva00511E6DChild *)((Rva00314126DwordField *)this)->get();
		if (!child)
			return 1;
		child->v0C(0);
		::delete child;
		if (TheIMEManager)
			TheIMEManager->m3C();
		break;
	}
	}
	for (int i = 0; i < 2; ++i)
	{
		if (m_entries[i])
			reinterpret_cast<ChatWindowsInGame *>(m_entries[i])->rva005AFCB4(false);
	}
	if (m_29c)
	{
		rva00511CE6();
		m_29c = false;
	}
	if (m_dragging)
	{
		const MouseIO *io = TheMouse->getMouseStatus();
		if (io && io->leftState == 0 && io->rightState == 0)
			((Rva00222A8BTarget *)g_bfmeAptWindowManager)->invoke(m_274, "StopUpdatePosition", 0, 0, 0, 0, 0, 0);
	}
	return 1;
}

// Retail 0x00511620, 162 bytes: vftable 0x00C6573C slot 0. A message
// arrived on a tab: flash the messenger button (and the tab while the
// messenger is up) and, unless that tab is showing, play the buddy or
// lobby message sound (none for the lobby inside a game's chat).
void Rva005114BD::rva00511620(int tab, int unused)
{
	((Rva00222A8BTarget *)g_bfmeAptWindowManager)->invoke(0, "MessengerButtonFlash", 0, 0, 0, 0, 0, 0);
	bool buddy = tab == 0;
	const char *sound = 0;
	if (buddy)
		sound = "GUIMessageBuddy";
	else if (!g_Va00E06394 || !((Rva0057FD6E *)g_Va00E06394)->rva0057FDA1())
		sound = "GUIMessageLobby";
	AptMessenger *messenger = (AptMessenger *)AptMessenger::s_instance;
	if (messenger)
	{
		((Rva00222A8BTarget *)g_bfmeAptWindowManager)->invoke(messenger->m_274, buddy ? "FlashTab0" : "FlashTab1", 0, 0, 0, 0, 0, 0);
		if (sound && tab != s_tabIds[g_Va00E046BC])
			PlaySound(sound);
	}
	else if (sound)
		PlaySound(sound);
}

// Retail 0x005118B2, 65 bytes: vftable 0x00C659A0 slot 13 frees both tabs
// and forgets the chat entry window.
void AptMessenger::rva005118B2()
{
	for (int i = 0; i < 2; ++i)
	{
		::delete m_entries[i];
		m_entries[i] = 0;
	}
	m_chatEntry = 0;
}

// Retail 0x00511CE6, 310 bytes: refreshes the two messenger buttons when the
// screen is maximized: each takes its text from the "APT:MessengerBttn_%d"
// key (a blank when the button has no label) and is enabled by its flag.
#include "ascii_string.h"

struct MessengerButton
{
	AsciiString label;
	bool enabled;
};

#include "../../../../../../Libraries/Source/Apt/BfmeAptWindowManager.h"

#include "../../../../../Include/GameClient/GameText.h"

extern GameTextInterface *TheGameText;
int __cdecl Rva00511C3AInvoke(Rva00222A8BTarget *target, void *owner, const char *name, const int &a, const bool &b);

void AptMessenger::rva00511CE6()
{
	if (!g_Va00DD13D8)
		return;
	v14();
	for (int i = 0; i < 2; ++i)
	{
		AsciiString key;
		key.format("APT:MessengerBttn_%d", i);
		int index = *(volatile int *)&i;
		MessengerButton *buttons = m_buttons;
		if (((const StringBase<char> *)&buttons[index].label)->isEmpty())
		{
			g_bfmeAptWindowManager->bfmeSetText(key, UnicodeString(L" "), false);
			void *movie = ((AptMessenger *)AptMessenger::s_instance)->m_274;
			bool enabled = false;
			Rva00511C3AInvoke(((Rva00222A8BTarget *)g_bfmeAptWindowManager), movie, "EnableButton", i, enabled);
		}
		else
		{
			g_bfmeAptWindowManager->bfmeSetText(key, TheGameText->fetch(buttons[i].label, 0), false);
			MessengerButton *current = m_buttons;
			void *movie = ((AptMessenger *)AptMessenger::s_instance)->m_274;
			Rva00511C3AInvoke(((Rva00222A8BTarget *)g_bfmeAptWindowManager), movie, "EnableButton", i, current[i].enabled);
		}
	}
}
