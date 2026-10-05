// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD
//
// BFME2's lobby chat panel Apt callbacks "AptMpChat::Send" (0x0057FDE0)
// and "AptMpChat::InitGadgets" (0x0057FDEF), bound by those names as member
// pointers by the panel's registration 0x0057FFB9; that binding is their
// only reference. The class is named for the strings' prefix (the
// MpGameSetup panel's +0x244 member).

#include "unicode_string.h"

extern "C" int __cdecl strcmp(const char *left, const char *right);
extern "C" char *__cdecl strcpy(char *destination, const char *source);

class GameWindow;

// The chat helper the panel keeps at +0x64: its unrowed 0x005B000C (188
// bytes) sends the typed line, 0x005AFC21 and 0x005AFC4C take the chat and
// player list windows (all pinned by address), and the rowed 0x005AFD43
// sets the entry's text (its own address class).
class Rva005B000C
{
public:
	void rva005B000C();
	void rva005AFC21(GameWindow *window);
	void rva005AFC4C(GameWindow *window);
};

class Rva005AFD43
{
public:
	void rva005AFD43(GameWindow *window, const UnicodeString &text);
};

class AptMpChat
{
public:
	void Send(const char *unused);
	void InitGadgets(const char *name, void *argument, GameWindow *window);
	// Bound as "MpChat::Initialized" and "MpClans::Initialized": one body
	// or two folded, so it keeps its address.
	void rva0057FDBF(int query, char *result, bool skip);

private:
	unsigned char m_pad00[0x64];
	Rva005B000C *m_entry; // +0x64
	bool m_initialized; // +0x68
};

// Retail 0x0057FDBF, 33 bytes: bound as "MpChat::Initialized" and
// "MpClans::Initialized", an Apt query answering "1".
void AptMpChat::rva0057FDBF(int query, char *result, bool skip)
{
	if (query == 0 && !skip)
		strcpy(result, "1");
}

// Retail 0x0057FDE0, 15 bytes: "AptMpChat::Send".
void AptMpChat::Send(const char *unused)
{
	if (m_entry)
		m_entry->rva005B000C();
}

// Retail 0x0057FDEF, 124 bytes: "AptMpChat::InitGadgets" hands the "Chat",
// "ChatPlayers" and (emptied) "ChatEntry" windows to the helper.
void AptMpChat::InitGadgets(const char *name, void *argument, GameWindow *window)
{
	if (!m_entry)
		return;
	m_initialized = false;
	if (strcmp(name, "Chat") == 0)
		m_entry->rva005AFC21(window);
	else if (strcmp(name, "ChatPlayers") == 0)
		m_entry->rva005AFC4C(window);
	else if (strcmp(name, "ChatEntry") == 0)
		((Rva005AFD43 *)m_entry)->rva005AFD43(window, UnicodeString::TheEmptyString);
	m_initialized = true;
}

// Retail's strcpy call lands on the import thunk rowed as ji_00629176.
#pragma comment(linker, "/alternatename:_strcpy=?ji_00629176@@YAXXZ")
