// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva004D634E@Rva004D59D1@@QAE?AVAsciiString@@XZ, retail 0x004D634E, 141 bytes.
// Rva004D59D1 (type 8, dwords +0x1c/+0x20) contents: base
// NetCommandMsg::rva004D5B4C plus ", leavePlayer=%d playerLeaveFrame=%d".
// Identity from vtable slot 3 of 0x00860274, format at 0x008604A4, callee base
// 0x004D5B4C, format 0x00038150, and empty fallback g_Rva0107301CEmptyString.
// Push order is base then +0x20 then +0x1c (retail pushes +0x1c first).
#include "ascii_string.h"

typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef int Int;

enum NetCommandType
{
	NETCOMMANDTYPE_UNKNOWN = -1
};

class MemoryPool;


__forceinline const char *GetStr004D634E(const AsciiString &s)
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

class Rva004D59D1 : public NetCommandMsg
{
public:
	AsciiString rva004D634E();
private:
	unsigned int m_1c;
	unsigned int m_20;
};

AsciiString Rva004D59D1::rva004D634E()
{
	AsciiString result;
	result.format("%s, leavePlayer=%d playerLeaveFrame=%d", GetStr004D634E(((NetCommandMsg *)this)->rva004D5B4C()), m_20, m_1c);
	return result;
}
