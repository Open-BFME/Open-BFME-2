// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?getContentsAsAsciiString@Rva004D64F5@@UAE?AVAsciiString@@XZ, retail 0x004D650E, 152 bytes.
// Rva004D64F5 (type 5, AsciiString +0x1c) contents: base
// NetCommandMsg::getContentsAsAsciiString plus ", challenge=%s" with the +0x1c string.
// Identity from vtable slot 3 of 0x0086050C, format "%s, challenge=%s" at
// 0x0086051C, callee base 0x004D5B4C, format 0x00038150, and empty fallback
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


__forceinline const char *GetStr004D650E(const AsciiString &asciiString)
{
	char *t = *(char * *)(void *)&asciiString;
	return t ? t + 8 : "";
}

#include "../../Include/GameNetwork/NetCommandMsg.h"

class Rva004D64F5 : public NetCommandMsg
{
public:
	AsciiString getContentsAsAsciiString();
private:
	AsciiString m_1c;
};

AsciiString Rva004D64F5::getContentsAsAsciiString()
{
	AsciiString result;
	result.format("%s, challenge=%s", GetStr004D650E(((NetCommandMsg *)this)->NetCommandMsg::getContentsAsAsciiString()), GetStr004D650E(m_1c));
	return result;
}
