// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -Ireference/open-bfme-1/game/GameEngine/Source/GameNetwork

// ?sendLocalGameMessage@ConnectionManager@@QAEXPAVGameMessage@@@Z @0x004D0E06 133B: ConnectionManager send GameMessage as NetGameCommandMsg via TheGameLogic frame and local player slot then sendLocalCommand relay 0xff and detach.
// Target evidence: new NetGameCommandMsg(GameMessage*) 0x004D5CBE then TheGameLogic+0x38 timestamp plus this+0x12028 playerID plus DoesCommandRequireACommandID 0x005811B5 plus GenerateNextCommandID 0x005811A8 plus sendLocalCommand 0x004CFF21 plus detach 0x004D55BC; caller 0x0025E75F.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;

void *__cdecl operator new(UnsignedInt size);
#include <new>

enum NetCommandType
{
	NETCOMMANDTYPE_UNKNOWN = -1,
	NETCOMMANDTYPE_GAMECOMMAND = 4
};

#include "../../Include/Common/MessageStream.h"

#include "../../Include/GameNetwork/NetCommandMsg.h"

class NetGameCommandMsg : public NetCommandMsg
{
public:
	NetGameCommandMsg(GameMessage *msg);
private:
	Int m_numArgs;
	Int m_argSize;
	Int m_type;
	void *m_argList;
	void *m_argTail;
};

#include "../Common/GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

bool DoesCommandRequireACommandID(NetCommandType type);
UnsignedShort GenerateNextCommandID();

class ConnectionManager
{
public:
	void sendLocalGameMessage(GameMessage *msg);
	void sendLocalCommand(NetCommandMsg *msg, UnsignedByte relay);
private:
	void *m_vptr;
	char m_pad04[0x12028 - 4];
	UnsignedInt m_localPlayerID;
};

void ConnectionManager::sendLocalGameMessage(GameMessage *msg)
{
	NetGameCommandMsg *cmd = new NetGameCommandMsg(msg);
	cmd->m_timestamp = TheGameLogic->getTimestamp();
	cmd->m_executionFrame = (UnsignedInt)-1;
	cmd->m_playerID = m_localPlayerID;
	if (DoesCommandRequireACommandID(cmd->m_commandType))
		cmd->m_id = GenerateNextCommandID();
	sendLocalCommand(cmd, 0xff);
	cmd->detach();
}
