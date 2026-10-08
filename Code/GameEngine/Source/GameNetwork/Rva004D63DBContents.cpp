// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva004D63DB@Rva004D63DB@@QAE?AVAsciiString@@XZ, retail 0x004D63DB, 141 bytes.
// Rva004D63DB (dwords +0x1c/+0x20) contents: base
// NetCommandMsg::rva004D5B4C plus ", leavePlayer=%d, reason = %d".
// Identity from same-shape sibling Rva004D59D1 0x004D634E (141B), callee base
// 0x004D5B4C, format "%s, leavePlayer=%d, reason = %d" at 0x008604CC,
// format 0x00038150, and empty fallback g_Rva0107301CEmptyString.
#include "ascii_string.h"

typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef int Int;

enum NetCommandType
{
	NETCOMMANDTYPE_UNKNOWN = -1
};

class MemoryPool;


__forceinline const char *GetStr004D63DB(const AsciiString &s)
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

class Rva004D63DB : public NetCommandMsg
{
public:
	AsciiString rva004D63DB();
private:
	unsigned int m_1c;
	unsigned int m_20;
};

AsciiString Rva004D63DB::rva004D63DB()
{
	AsciiString result;
	result.format("%s, leavePlayer=%d, reason = %d", GetStr004D63DB(((NetCommandMsg *)this)->rva004D5B4C()), m_1c, m_20);
	return result;
}
