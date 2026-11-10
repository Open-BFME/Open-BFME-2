// cl: /DNDEBUG /MD /EHsc
// ??0NetGameCommandMsg@@QAE@PAVGameMessage@@@Z @0x004D5CBE 151B: NetGameCommandMsg from GameMessage copy ctor.
// Target evidence: base ??0NetCommandMsg 0x004D5593 then vtable RVA 0x008601E4 plus +0x14=4 plus +0x24 from [arg+0x10] plus loop getArgument 0x0030F4EA plus getArgumentDataType 0x0030F50C plus addArgument 0x004D5A7A; caller 0x004D0E06; donor reference/open-bfme-1/game/GameEngine/Source/GameNetwork/NetGameCommandMsgFromGameMessage.cpp.
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef int Int;
typedef bool Bool;
class AsciiString;

enum NetCommandType
{
	NETCOMMANDTYPE_UNKNOWN = -1,
	NETCOMMANDTYPE_GAMECOMMAND = 4
};

enum GameMessageArgumentDataType
{
	ARGUMENTDATATYPE_UNKNOWN = 12
};

union GameMessageArgumentType
{
	int integer;
	float real;
	int pixelRegion[4];
};

#include "../../Include/Common/MessageStream.h"

#include "../../Include/GameNetwork/NetCommandMsg.h"

class GameMessageArgument;

#include "../../Include/GameNetwork/NetGameCommandMsg.h"

NetGameCommandMsg::NetGameCommandMsg(GameMessage *msg) : NetCommandMsg()
{
	m_numArgs = 0;
	m_argSize = 0;
	m_argList = 0;
	m_argTail = 0;
	m_commandType = NETCOMMANDTYPE_GAMECOMMAND;
	m_type = msg->getType();
	int count = msg->getArgumentCount();
	for (int i = 0; i < count; ++i)
		addArgument(msg->getArgumentDataType(i), *msg->getArgument(i));
}
