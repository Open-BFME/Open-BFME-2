// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?getContentsAsAsciiString@Rva004D5A30@@UAE?AVAsciiString@@XZ, retail 0x004D6468, 141 bytes.
// Rva004D5A30 (type 9, dwords +0x1c/+0x20) contents slot 3 of 0x00860294: base
// NetCommandMsg::getContentsAsAsciiString plus ", startFrame=%d endFrame=%d".
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


__forceinline const char *GetStr004D6468(const AsciiString &asciiString)
{
	char *t = *(char * *)(void *)&asciiString;
	return t ? t + 8 : "";
}

#include "../../Include/GameNetwork/NetCommandMsg.h"

class Rva004D5A30 : public NetCommandMsg
{
public:
	AsciiString getContentsAsAsciiString();
private:
	unsigned int m_1c;
	unsigned int m_20;
};

AsciiString Rva004D5A30::getContentsAsAsciiString()
{
	AsciiString result;
	result.format("%s, startFrame=%d endFrame=%d", GetStr004D6468(((NetCommandMsg *)this)->NetCommandMsg::getContentsAsAsciiString()), m_1c, m_20);
	return result;
}
