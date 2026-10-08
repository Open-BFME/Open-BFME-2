// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva004D6468@Rva004D5A30@@QAE?AVAsciiString@@XZ, retail 0x004D6468, 141 bytes.
// Rva004D5A30 (type 9, dwords +0x1c/+0x20) contents slot 3 of 0x00860294: base
// NetCommandMsg::rva004D5B4C plus ", startFrame=%d endFrame=%d".
// Identity from vtable slot 3, ctor 0x004D5A30 layout, format
// "%s, startFrame=%d endFrame=%d" at 0x008604EC, callee base 0x004D5B4C,
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


__forceinline const char *GetStr004D6468(const AsciiString &s)
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

class Rva004D5A30 : public NetCommandMsg
{
public:
	AsciiString rva004D6468();
private:
	unsigned int m_1c;
	unsigned int m_20;
};

AsciiString Rva004D5A30::rva004D6468()
{
	AsciiString result;
	result.format("%s, startFrame=%d endFrame=%d", GetStr004D6468(((NetCommandMsg *)this)->rva004D5B4C()), m_1c, m_20);
	return result;
}
