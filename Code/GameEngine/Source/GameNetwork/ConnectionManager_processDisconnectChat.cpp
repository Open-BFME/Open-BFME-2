// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ConnectionManager::processDisconnectChat, retail 0x004D1023, 206 bytes.
//
// Donor: Open-BFME-1 game/GameEngine/Source/GameNetwork/
// ConnectionManagerProcessDisconnectChat.cpp (name, the "[name] text" format
// and the right-to-left temporaries: the text is fetched before the name).
// Target evidence: the null test of the disconnect menu global (VA 0x00E048D0,
// held in the data ledger as g_Va00E048D0), the message text getter 0x004D6119
// and getPlayerName 0x004D0198 on the message's player at +0x0C, the
// L"[%ls] %ls" literal at 0x007E0788 handed to UnicodeString::format(const
// unsigned short *, ...) 0x006CB5D0 directly (BFME 1 built a UnicodeString
// temporary for it), and the by-value copy passed to the chat-box wrapper
// 0x00513138 (BFME 1's DisconnectMenu::showChat).

#include "unicode_string.h"

typedef int Int;

// The ledger's name for NetDisconnectChatCommandMsg::getText (an inline
// forwarder is not expanded, so the body calls it by this name).
class Rva004D6119
{
public:
	UnicodeString rva004D6119() const;
};

class NetDisconnectChatCommandMsg : public Rva004D6119
{
public:
	Int getPlayerID() const { return m_playerID; }

private:
	void *m_vptr;
	Int m_timestamp;
	Int m_executionFrame;
	Int m_playerID;
};

// The ledger's name for the disconnect menu's showChat.
class Rva00513138
{
public:
	void rva00513138(UnicodeString text);
};

// TheDisconnectMenu.
extern int g_Va00E048D0;

class ConnectionManager
{
public:
	UnicodeString getPlayerName(Int playerID);

private:
	void processDisconnectChat(NetDisconnectChatCommandMsg *msg);
};

void ConnectionManager::processDisconnectChat(NetDisconnectChatCommandMsg *msg)
{
	if (g_Va00E048D0 != 0)
	{
		UnicodeString unitext;
		unitext.format(L"[%ls] %ls", getPlayerName(msg->getPlayerID()).str(), msg->rva004D6119().str());
		((Rva00513138 *)g_Va00E048D0)->rva00513138(unitext);
	}
}
