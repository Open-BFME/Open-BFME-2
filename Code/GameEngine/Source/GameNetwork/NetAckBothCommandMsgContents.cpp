// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva004D5DEF@NetAckBothCommandMsg@@QAE?AVAsciiString@@XZ, retail 0x004D5DEF, 151 bytes.
// NetAckBothCommandMsg contents slot 3 of 0x008601F4: base
// NetCommandMsg::rva004D5B4C plus ", commandID=%d, origPlayer=%d, origExeSID=%d, origExeFrame=%d".
// Identity from vtable slot 3, ctor 0x004D568F layout +0x1c word +0x1e byte +0x20 +0x24,
// format 0x00860360, callee base 0x004D5B4C, format 0x00038150,
// and empty fallback g_Rva0107301CEmptyString.
#include "ascii_string.h"

typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef int Int;

enum NetCommandType
{
	NETCOMMANDTYPE_UNKNOWN = -1
};

class MemoryPool;


__forceinline const char *GetStr004D5DEF(const AsciiString &s)
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

class NetAckBothCommandMsg : public NetCommandMsg
{
public:
	AsciiString rva004D5DEF();
private:
	UnsignedShort m_commandID;
	UnsignedByte m_originalPlayerID;
	char m_pad1F;
	UnsignedInt m_20;
	UnsignedInt m_24;
};

AsciiString NetAckBothCommandMsg::rva004D5DEF()
{
	AsciiString result;
	result.format("%s, commandID=%d, origPlayer=%d, origExeSID=%d, origExeFrame=%d", GetStr004D5DEF(((NetCommandMsg *)this)->rva004D5B4C()), m_commandID, m_originalPlayerID, m_20, m_24);
	return result;
}
