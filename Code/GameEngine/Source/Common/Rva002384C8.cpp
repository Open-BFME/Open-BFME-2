// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHs
//
// ?rva002384C8@Rva002384C8@@QAE?AVUnicodeString@@XZ @0x002384C8 84B
// No callers; thiscall returns UnicodeString by value via translate of
// AsciiString member at +0x1C. Honest address name.
#include "ascii_string.h"
#include "unicode_string.h"

class Rva002384C8
{
public:
	UnicodeString rva002384C8();
private:
	char m_pad[0x1C];
	AsciiString m_str;
};

UnicodeString Rva002384C8::rva002384C8()
{
	UnicodeString tmp;
	tmp.translate(m_str);
	return tmp;
}
