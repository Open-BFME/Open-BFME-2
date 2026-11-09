// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?getContentsAsAsciiString@Rva004D59D1@@UAE?AVAsciiString@@XZ, retail 0x004D634E, 141 bytes.
// Rva004D59D1 (type 8, dwords +0x1c/+0x20) contents: base
// NetCommandMsg::getContentsAsAsciiString plus ", leavePlayer=%d playerLeaveFrame=%d".
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


__forceinline const char *GetStr004D634E(const AsciiString &asciiString)
{
	char *t = *(char * *)(void *)&asciiString;
	return t ? t + 8 : "";
}

#include "../../Include/GameNetwork/NetCommandMsg.h"

class Rva004D59D1 : public NetCommandMsg
{
public:
	AsciiString getContentsAsAsciiString();
private:
	unsigned int m_1c;
	unsigned int m_20;
};

AsciiString Rva004D59D1::getContentsAsAsciiString()
{
	AsciiString result;
	result.format("%s, leavePlayer=%d playerLeaveFrame=%d", GetStr004D634E(((NetCommandMsg *)this)->NetCommandMsg::getContentsAsAsciiString()), m_20, m_1c);
	return result;
}
