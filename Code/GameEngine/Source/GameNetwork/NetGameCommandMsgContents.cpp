// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva004D5D55@NetGameCommandMsg@@QAE?AVAsciiString@@XZ @0x004D5D55 154B: NetGameCommandMsg contents slot 3 of 0x008601E4.
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


__forceinline const char *GetStr004D5D55(const AsciiString &s)
{
	char *t = *(char * *)(void *)&s;
	return t ? t + 8 : "";
}

class GameMessage
{
public:
	enum Type
	{
		MSG_INVALID = 0
	};
	static AsciiString getCommandTypeAsAsciiString(Type t);
};

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

class NetGameCommandMsg : public NetCommandMsg
{
public:
	AsciiString rva004D5D55();
private:
	Int m_numArgs;
	Int m_argSize;
	Int m_type;
	void *m_argList;
	void *m_argTail;
};

AsciiString NetGameCommandMsg::rva004D5D55()
{
	AsciiString result;
	result.format("<session=%d,frame=%d, player=%d, id=%d>, %s", m_timestamp, m_executionFrame, m_playerID, m_id, GetStr004D5D55(GameMessage::getCommandTypeAsAsciiString((GameMessage::Type)m_type)));
	return result;
}
