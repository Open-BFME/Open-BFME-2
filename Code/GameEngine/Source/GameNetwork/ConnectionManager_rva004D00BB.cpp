// cl: /O1 /DNDEBUG /DWIN32 -D_WINDOWS -MD -EHsc -Ireference/open-bfme-1/game/GameEngine/Source/GameNetwork -ICode/GameEngine/Source/Common
// platformsdk
// ?requestLeave@ConnectionManager@@QAEXH@Z @0x004D00BB 179B: ConnectionManager local disconnect-player send.
// Target evidence: new 0x24 Rva004D5A10 (0x004D5A10) whose +0x1C slot is set through the Rva004D57AE setter
// 0x00318B09 and +0x20 through the folded dword setter 0x00317B9B (argument), TheGameLogic+0x38 frame at +4,
// execution frame -1, DoesCommandRequireACommandID 0x005811B5 plus GenerateNextCommandID 0x005811A8,
// sendLocalCommandDirect 0x004CF6E4 to all, the connection flush 0x004CF8D5 and detach 0x004D55BC, then the
// m_lastTime stamp at +0x12130 through timeGetTime only when it is still zero. The only direct caller is the
// null-checked forwarder 0x004D0E8B/0x0025E27F; the own name stays an address name.

#include <new>
#include <windows.h>
#include "GameLogicObjectLookupView.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;

#include "../../Include/GameNetwork/NetCommandMsg.h"
#include "../../Include/GameNetwork/BFMENetInformPlayerLeaveFrameCommandMsg.h"

class Rva004D5A10 : public NetCommandMsg
{
public:
	Rva004D5A10();
private:
	char m_pad1C[0x24 - 0x1C];
};

class Rva004D57AE
{
public:
	void setPlayerIndex(UnsignedInt v);
};

class BfmeOwnerFY
{
public:
	void bfmeShutdownFY();
};

extern GameLogic *TheGameLogic;

bool DoesCommandRequireACommandID(NetCommandType type);
UnsignedShort GenerateNextCommandID();

struct NetCommandListNode
{
	NetCommandMsg *m_msg;
	NetCommandListNode *m_next;
	UnsignedInt m_pad08;
	UnsignedByte m_relay;
};

#include "../../Include/GameNetwork/NetCommandListClass.h"

class ConnectionManager
{
public:
	void requestLeave(Int arg);
	void resendPendingCommands();
	void sendLocalCommand(NetCommandMsg *msg, UnsignedByte relay);
	void sendLocalCommandDirect(NetCommandMsg *msg, UnsignedByte relay);
private:
	void *m_vptr;
	char m_pad04[0x12028 - 4];
	UnsignedInt m_localPlayerID;
	char m_pad1202C[0x12124 - 0x1202C];
	NetCommandList *m_list12124;
	char m_pad12128[0x12130 - 0x12128];
	UnsignedInt m_lastTime;
};

void ConnectionManager::requestLeave(Int arg)
{
	Rva004D5A10 *cmd = new Rva004D5A10();
	((Rva004D57AE *)cmd)->setPlayerIndex(m_localPlayerID);
	cmd->m_playerID = m_localPlayerID;
	((BFMENetInformPlayerLeaveFrameCommandMsg *)cmd)->setLeavingPlayerID(arg);
	if (DoesCommandRequireACommandID(cmd->m_commandType))
		cmd->m_id = GenerateNextCommandID();
	cmd->m_timestamp = TheGameLogic->getTimestamp();
	cmd->m_executionFrame = (UnsignedInt)-1;
	sendLocalCommandDirect(cmd, 0xff);
	((BfmeOwnerFY *)this)->bfmeShutdownFY();
	cmd->detach();
	if (m_lastTime == 0)
		m_lastTime = timeGetTime();
}

// ?resendPendingCommands@ConnectionManager@@QAEXXZ @0x004D016E (42B)
void ConnectionManager::resendPendingCommands()
{
	if (m_list12124 != 0)
	{
		for (NetCommandListNode *node = reinterpret_cast<NetCommandListNode *>(m_list12124->m_first); node != 0; node = node->m_next)
			sendLocalCommand(node->m_msg, node->m_relay);
	}
}
