// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva001EB298@Rva001EB298@@QAEXVAsciiString@@@Z, retail 0x001EB298, 52 bytes.
// __thiscall setter taking AsciiString by value (ret 4): copies param into member at +0x2C
// via rowed StringBase<char>::set 0x000366F0 then destroys param via rowed releaseBuffer
// 0x00036410 with EH_prolog state 0/-1. Evidence: ecx+0x2C set + ebp+8 release, callers
// 0x001EB42E and 0x002412CC, beside Rva001EB2CCMapPath.
#include "ascii_string.h"

class Rva001EB298
{
	char pad[0x2C];
	AsciiString m_str;
public:
	void rva001EB298(AsciiString s);
};

void Rva001EB298::rva001EB298(AsciiString s)
{
	m_str = s;
}
