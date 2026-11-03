// cl: /DNDEBUG /DWIN32 -D_WINDOWS -MD -EHsc -Ireference/open-bfme-1/game/GameEngine/Source/GameNetwork
// platformsdk

// ?rva004D0A0A@ConnectionManager@@QAEXXZ @0x004D0A0A 154B: ConnectionManager keepalive-style send via Rva004D5795 plus slot byte plus TheGameLogic frame plus Does plus sendLocalCommand plus timeGetTime.
// Target evidence: new Rva004D5795 0x004D5795 then setter 0x0006EDE3 via setDisconnectSlot pin plus TheGameLogic+0x38 plus DoesCommandRequireACommandID 0x005811B5 plus GenerateNextCommandID 0x005811A8 plus sendLocalCommand 0x004CFF21 plus detach 0x004D55BC plus timeGetTime IAT; caller 0x0025E75F.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;

#define NOMINMAX
#include <windows.h>
#include <new>

enum NetCommandType
{
	NETCOMMANDTYPE_UNKNOWN = -1
};

#include "../../Include/GameNetwork/NetCommandMsg.h"

class Rva004D5795 : public NetCommandMsg
{
public:
	Rva004D5795();
private:
	bool m_1c;
	char m_pad1D[0x20 - 0x1D];
};

class NetDisconnectPlayerCommandMsg
{
public:
	void setDisconnectSlot(UnsignedByte slot);
};

#include "../Common/GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

bool DoesCommandRequireACommandID(NetCommandType type);
UnsignedShort GenerateNextCommandID();

class ConnectionManager
{
public:
	void rva004D0A0A();
	void sendLocalCommand(NetCommandMsg *msg, UnsignedByte relay);
private:
	void *m_vptr;
	char m_pad04[0x12028 - 4];
	union
	{
		UnsignedByte m_slotByte;
		UnsignedInt m_localPlayerID;
	};
	char m_pad1202C[0x12130 - 0x12028 - 4];
	UnsignedInt m_lastTime;
};

void ConnectionManager::rva004D0A0A()
{
	Rva004D5795 *cmd = new Rva004D5795();
	((NetDisconnectPlayerCommandMsg *)cmd)->setDisconnectSlot(m_slotByte);
	cmd->m_timestamp = TheGameLogic->getTimestamp();
	cmd->m_executionFrame = (UnsignedInt)-1;
	if (DoesCommandRequireACommandID(cmd->m_commandType))
		cmd->m_id = GenerateNextCommandID();
	cmd->m_playerID = m_localPlayerID;
	sendLocalCommand(cmd, 0xff);
	cmd->detach();
	m_lastTime = timeGetTime();
}
