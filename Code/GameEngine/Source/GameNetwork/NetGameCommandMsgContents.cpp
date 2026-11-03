// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?getContentsAsAsciiString@NetGameCommandMsg@@UAE?AVAsciiString@@XZ @0x004D5D55 154B: NetGameCommandMsg contents slot 3 of 0x008601E4.
// Target evidence: vtable 0x008601E4 slot 3, members +4/+8/+0xC/+0x10 word +0x24 from retail pushes, format "<session=%d,frame=%d, player=%d, id=%d>, %s" at 0x00860330, callees getCommandTypeAsAsciiString 0x0030FA44 plus format 0x00038150 plus releaseBuffer 0x00036410 plus StringBase copy 0x000365F0, empty fallback g_Rva0107301CEmptyString; donor BFME1 NetCommandMsg_getContentsAsAsciiString.cpp plus NetGameCommandMsgCtor.cpp layout.
#include "ascii_string.h"

typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef int Int;

enum NetCommandType
{
	NETCOMMANDTYPE_UNKNOWN = -1
};

class MemoryPool;


__forceinline const char *GetStr004D5D55(const AsciiString &asciiString)
{
	char *t = *(char * *)(void *)&asciiString;
	return t ? t + 8 : "";
}

#include "../../Include/Common/MessageStream.h"

#include "../../Include/GameNetwork/NetCommandMsg.h"

#include "../../Include/GameNetwork/NetGameCommandMsg.h"

AsciiString NetGameCommandMsg::getContentsAsAsciiString()
{
	AsciiString result;
	result.format("<session=%d,frame=%d, player=%d, id=%d>, %s", m_timestamp, m_executionFrame, m_playerID, m_id, GetStr004D5D55(GameMessage::getCommandTypeAsAsciiString((GameMessage::Type)m_type)));
	return result;
}
