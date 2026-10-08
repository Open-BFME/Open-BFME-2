// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva004D5E86@NetAckStage1CommandMsg@@QAE?AVAsciiString@@XZ, retail 0x004D5E86, 151 bytes.
// NetAckStage1CommandMsg contents slot 3 of 0x00860204: base
// NetCommandMsg::rva004D5B4C plus ", commandID=%d, origPlayer=%d, origExeSID=%d, origExecFrame=%d".
// Identity from vtable slot 3, ctor 0x004D56E6 layout +0x1c word +0x1e byte +0x20 +0x24,
// format 0x008603A0, callee base 0x004D5B4C, format 0x00038150,
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


__forceinline const char *GetStr004D5E86(const AsciiString &s)
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

class NetAckStage1CommandMsg : public NetCommandMsg
{
public:
	AsciiString rva004D5E86();
private:
	UnsignedShort m_commandID;
	UnsignedByte m_originalPlayerID;
	char m_pad1F;
	UnsignedInt m_20;
	UnsignedInt m_24;
};

AsciiString NetAckStage1CommandMsg::rva004D5E86()
{
	AsciiString result;
	result.format("%s, commandID=%d, origPlayer=%d, origExeSID=%d, origExecFrame=%d", GetStr004D5E86(((NetCommandMsg *)this)->rva004D5B4C()), m_commandID, m_originalPlayerID, m_20, m_24);
	return result;
}
