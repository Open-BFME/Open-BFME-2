// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva004D5B4C@NetCommandMsg@@QAE?AVAsciiString@@XZ, retail 0x004D5B4C, 223 bytes.
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

int DoesCommandRequireACommandID(NetCommandType type);
AsciiString Rva005813D4Get(int type);


__forceinline const char *GetStr004D5B4C(const AsciiString &s)
{
	char *t = *(char * *)(void *)&s;
	return t ? t + 8 : "";
}

class NetCommandMsg
{
public:
	AsciiString rva004D5B4C();
protected:
	virtual ~NetCommandMsg();
private:
	virtual MemoryPool *getObjectMemoryPool();
public:
	virtual Int getSortNumber();
	virtual AsciiString getContentsAsAsciiString();
protected:
	UnsignedInt m_timestamp;
	UnsignedInt m_executionFrame;
	UnsignedInt m_playerID;
	UnsignedShort m_id;
	NetCommandType m_commandType;
	Int m_referenceCount;
};

AsciiString NetCommandMsg::rva004D5B4C()
{
	AsciiString result;
	if ((unsigned char)DoesCommandRequireACommandID(m_commandType))
	{
		result.format("<sessionID=%d, frame=%d, player=%d, id=%d>, %s", m_timestamp, m_executionFrame, m_playerID, m_id, GetStr004D5B4C(Rva005813D4Get(m_commandType)));
	}
	else
	{
		result.format("<sessionID=%d, frame=%d, player=%d>, %s", m_timestamp, m_executionFrame, m_playerID, GetStr004D5B4C(Rva005813D4Get(m_commandType)));
	}
	return result;
}
