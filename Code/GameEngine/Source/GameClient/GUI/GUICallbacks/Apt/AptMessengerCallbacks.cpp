// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /arch:SSE
//
// BFME2's messenger screen Apt callbacks "AptMessenger::OnButtonSend",
// "AptMessenger::OnBttn_0" and "AptMessenger::OnBttn_1", bound by those
// names as member pointers by the screen's registration; that binding is
// their only reference. The class is named for the strings' prefix. Both
// buttons act on the active tab (Rva005118F3Show.cpp's g_Va00E046BC).
// "AptMessenger::GameWindowSize" is a render callback and
// "AptMessenger::IsOpen" a static query bound through the free-function
// holder 0x004106FA.
//
// The screen object is itself the window: GameWindowSize runs GameWindow's
// members on its own this.

#include "unicode_string.h"

extern "C" char *__cdecl strcpy(char *destination, const char *source);
extern "C" int __cdecl strcmp(const char *left, const char *right);

// Rva00511730Save.cpp's g_Va00E048C0, the chat entry's kept text.
extern UnicodeString g_Va00E048C0;

extern int g_Va00E046BC;

// The messenger instance (Rva00511730Save.cpp's g_Va00E046B8).
struct Rva00511730State;
extern Rva00511730State *g_Va00E046B8;

// A render callback's position and size: two floats each (the type is
// inferred from use).
struct Coord2D
{
	float x;
	float y;
};

class GameWindow
{
public:
	int winSetPosition(int x, int y);
	int winGetPosition(int *x, int *y);
	int winSetSize(int width, int height);
	int winGetSize(int *width, int *height);
};

// A tab's chat entry; its unrowed 0x005B000C sends the typed line, pinned
// by address.
class Rva005B000C
{
public:
	void rva005B000C();
	// Unrowed 0x005AFC21 and 0x005AFC4C keep the tab's chat and player
	// list windows, pinned by address.
	void rva005AFC21(GameWindow *window);
	void rva005AFC4C(GameWindow *window);
};

// The rowed 0x005AFD43 keeps a tab's chat entry window and its text.
class Rva005AFD43
{
public:
	void rva005AFD43(GameWindow *window, const UnicodeString &text);
};

class AptMessenger : public GameWindow
{
public:
	void OnButtonSend(const char *unused);
	void InitGadgets(const char *name, void *argument, GameWindow *window);
	void OnBttn_0(const char *unused);
	void OnBttn_1(const char *unused);
	void GameWindowSize(const Coord2D *position, const Coord2D *size, void *unused3, void *unused4);
	static void IsOpen(int query, char *result, bool skip);

	// Unrowed tab actions and the refresh 0x00511CE6, pinned by address.
	void rva005AE886();
	void rva005AE990();
	void rva005AEA3E();
	void rva005AE90F();
	void rva005AE7C6();
	void rva00511CE6();

private:
	unsigned char m_pad000[0x278];
	bool m_closed; // +0x278
	unsigned char m_pad279[0x280 - 0x279];
	Rva005B000C **m_entries; // +0x280, one per tab
	unsigned char m_pad284[0x298 - 0x284];
	GameWindow *m_chatEntry; // +0x298
	unsigned char m_pad29c[0x2A0 - 0x29C];
	bool m_2a0; // +0x2A0
};

// Retail 0x005119E4, 27 bytes: "AptMessenger::OnButtonSend".
void AptMessenger::OnButtonSend(const char *unused)
{
	Rva005B000C *entry = m_entries[g_Va00E046BC];
	if (entry)
		entry->rva005B000C();
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
			rva005AE7C6();
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
		AptMessenger *messenger = (AptMessenger *)g_Va00E046B8;
		if (messenger && !messenger->m_closed)
			strcpy(result, "1");
		else
			strcpy(result, "0");
	}
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
			m_entries[0]->rva005AFC4C(window);
	}
	else if (strcmp(name, "Messenger::PlayersTab_1") == 0)
	{
		if (m_entries[1])
			m_entries[1]->rva005AFC4C(window);
	}
	else if (strcmp(name, "Messenger::ChatTab_0") == 0)
	{
		if (m_entries[0])
			m_entries[0]->rva005AFC21(window);
	}
	else if (strcmp(name, "Messenger::ChatTab_1") == 0)
	{
		if (m_entries[1])
			m_entries[1]->rva005AFC21(window);
	}
}

// Retail's strcpy call lands on the import thunk rowed as ji_00629176.
#pragma comment(linker, "/alternatename:_strcpy=?ji_00629176@@YAXXZ")
