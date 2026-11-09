// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?getContentsAsAsciiString@NetCommandMsg@@UAE?AVAsciiString@@XZ, retail 0x004D5B4C, 223 bytes.
// NetCommandMsg contents formatter: when DoesCommandRequireACommandID says the
// type needs an id, formats "<sessionID=%d, frame=%d, player=%d, id=%d>, %s"
// with the Rva type name, else "<sessionID=%d, frame=%d, player=%d>, %s".
// Identity from member offsets matching NetCommandMsgCtor (+4 timestamp, +8
// frame, +0xC player, +0x10 word id, +0x14 type), vtable slot 3 of 6 derived
// classes, callees DoesCommandRequireACommandID 0x005811B5, Rva Get 0x005813D4,
// format 0x00038150, and empty fallback g_Rva0107301CEmptyString.
#include "ascii_string.h"

typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef int Int;

enum NetCommandType
{
	NETCOMMANDTYPE_UNKNOWN = -1,
	NETCOMMANDTYPE_GAMECOMMAND = 4
};

class MemoryPool;

bool DoesCommandRequireACommandID(NetCommandType type);
AsciiString Rva005813D4Get(int type);


__forceinline const char *GetStr004D5B4C(const AsciiString &asciiString)
{
	char *t = *(char * *)(void *)&asciiString;
	return t ? t + 8 : "";
}

#include "../../Include/GameNetwork/NetCommandMsg.h"

AsciiString NetCommandMsg::getContentsAsAsciiString()
{
	AsciiString result;
	if (DoesCommandRequireACommandID(m_commandType))
	{
		result.format("<sessionID=%d, frame=%d, player=%d, id=%d>, %s", m_timestamp, m_executionFrame, m_playerID, m_id, GetStr004D5B4C(Rva005813D4Get(m_commandType)));
	}
	else
	{
		result.format("<sessionID=%d, frame=%d, player=%d>, %s", m_timestamp, m_executionFrame, m_playerID, GetStr004D5B4C(Rva005813D4Get(m_commandType)));
	}
	return result;
}
