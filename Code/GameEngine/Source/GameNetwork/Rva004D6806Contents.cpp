// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?getContentsAsAsciiString@Rva004D6806@@UAE?AVAsciiString@@XZ, retail 0x004D6806, 192 bytes.
// Rva004D6806 contents: base NetCommandMsg::getContentsAsAsciiString plus
// "%s, action=%d reason = %d, filename=%s" with dwords +0x1c/+0x20 and
// UnicodeString +0x24 translated to AsciiString.
// Identity from callees translate 0x00038220, base 0x004D5B4C, format
// 0x00038150, releaseBuffer 0x00036410, copy-ctor 0x000365F0, empty fallback
// g_Rva0107301CEmptyString, and format string at VA 0x00860570.
#include "ascii_string.h"
#include "unicode_string.h"

typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef int Int;

enum NetCommandType
{
	NETCOMMANDTYPE_UNKNOWN = -1
};

class MemoryPool;


__forceinline const char *GetStr004D6806(const AsciiString &asciiString)
{
	char *t = *(char * *)(void *)&asciiString;
	return t ? t + 8 : "";
}

#include "../../Include/GameNetwork/NetCommandMsg.h"

class Rva004D6806 : public NetCommandMsg
{
public:
	AsciiString getContentsAsAsciiString();
private:
	int m_action;
	int m_reason;
	UnicodeString m_filename;
};

AsciiString Rva004D6806::getContentsAsAsciiString()
{
	AsciiString result;
	AsciiString filenameAscii;
	filenameAscii.translate(m_filename);
	result.format("%s, action=%d reason = %d, filename=%s", GetStr004D6806(((NetCommandMsg *)this)->NetCommandMsg::getContentsAsAsciiString()), m_action, m_reason, GetStr004D6806(filenameAscii));
	return result;
}
