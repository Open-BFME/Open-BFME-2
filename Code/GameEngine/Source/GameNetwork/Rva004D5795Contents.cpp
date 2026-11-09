// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?getContentsAsAsciiString@Rva004D5795@@UAE?AVAsciiString@@XZ, retail 0x004D5FB4, 140 bytes.
// Rva004D5795 (player-leave, type 10, bool +0x1c) contents: base
// NetCommandMsg::getContentsAsAsciiString plus ", leavingPlayer=%d" with the +0x1c byte.
// Identity from vtable slot 3 of 0x00860224, movzx byte +0x1c, format
// "%s, leavingPlayer=%d" at 0x00860434, callee base 0x004D5B4C, format
// 0x00038150, and empty fallback g_Rva0107301CEmptyString.
#include "ascii_string.h"

typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef int Int;

enum NetCommandType
{
	NETCOMMANDTYPE_UNKNOWN = -1
};

class MemoryPool;


__forceinline const char *GetStr004D5FB4(const AsciiString &asciiString)
{
	char *t = *(char * *)(void *)&asciiString;
	return t ? t + 8 : "";
}

#include "../../Include/GameNetwork/NetCommandMsg.h"

class Rva004D5795 : public NetCommandMsg
{
public:
	AsciiString getContentsAsAsciiString();
private:
	bool m_1c;
};

AsciiString Rva004D5795::getContentsAsAsciiString()
{
	AsciiString result;
	result.format("%s, leavingPlayer=%d", GetStr004D5FB4(((NetCommandMsg *)this)->NetCommandMsg::getContentsAsAsciiString()), m_1c);
	return result;
}
