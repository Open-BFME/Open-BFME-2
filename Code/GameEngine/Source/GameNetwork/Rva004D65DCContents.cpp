// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?getContentsAsAsciiString@Rva004D65DC@@UAE?AVAsciiString@@XZ, retail 0x004D6661, 167 bytes.
// Rva004D65DC (type 6, AsciiStrings +0x1c/+0x20) contents slot 3 of 0x00860530:
// base NetCommandMsg::getContentsAsAsciiString plus ", authToken=%s, authKey=%s".
// Identity from vtable slot 3, ctor 0x004D65DC layout, setter 0x004D662D (+0x20),
// dtor 0x004D6708, format "%s, authToken=%s, authKey=%s" at 0x00860540,
// callee base 0x004D5B4C, format 0x00038150, empty fallback g_Rva0107301CEmptyString.
#include "ascii_string.h"

typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef int Int;

enum NetCommandType
{
	NETCOMMANDTYPE_UNKNOWN = -1
};

class MemoryPool;


__forceinline const char *GetStr004D6661(const AsciiString &asciiString)
{
	char *t = *(char * *)(void *)&asciiString;
	return t ? t + 8 : "";
}

#include "../../Include/GameNetwork/NetCommandMsg.h"

class Rva004D65DC : public NetCommandMsg
{
public:
	AsciiString getContentsAsAsciiString();
private:
	AsciiString m_authKey;
	AsciiString m_authToken;
};

AsciiString Rva004D65DC::getContentsAsAsciiString()
{
	AsciiString result;
	result.format("%s, authToken=%s, authKey=%s", GetStr004D6661(((NetCommandMsg *)this)->NetCommandMsg::getContentsAsAsciiString()), GetStr004D6661(m_authToken), GetStr004D6661(m_authKey));
	return result;
}
