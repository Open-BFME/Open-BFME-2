// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?getContentsAsAsciiString@Rva004D57AE@@UAE?AVAsciiString@@XZ, retail 0x004D6040, 138 bytes.
// Rva004D57AE (type 11, dword +0x1c) contents: base
// NetCommandMsg::getContentsAsAsciiString plus ", destroyPlayer=%d" with the +0x1c dword.
// Identity from vtable slot 3 of 0x00860234, format "%s, destroyPlayer=%d" at
// 0x0086044C, callee base 0x004D5B4C, format 0x00038150, and empty fallback
// g_Rva0107301CEmptyString.
#include "ascii_string.h"

typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef int Int;

enum NetCommandType
{
	NETCOMMANDTYPE_UNKNOWN = -1
};

class MemoryPool;


__forceinline const char *GetStr004D6040(const AsciiString &asciiString)
{
	char *t = *(char * *)(void *)&asciiString;
	return t ? t + 8 : "";
}

#include "../../Include/GameNetwork/NetCommandMsg.h"

class Rva004D57AE : public NetCommandMsg
{
public:
	AsciiString getContentsAsAsciiString();
private:
	unsigned int m_1c;
};

AsciiString Rva004D57AE::getContentsAsAsciiString()
{
	AsciiString result;
	result.format("%s, destroyPlayer=%d", GetStr004D6040(((NetCommandMsg *)this)->NetCommandMsg::getContentsAsAsciiString()), m_1c);
	return result;
}
