// cl: /Ireference/shims/bfme2_ascii /Oy- /MD /EHsc
// ?rva004D65F9@Rva004D64F5@@QAEXVAsciiString@@@Z @0x004D65F9 (52B):
// AsciiString setter on Rva004D64F5: copies the by-value argument into the
// +0x1c member via pin-only operator= 0x000366F0, then destroys the parameter
// via rowed StringBase<char> releaseBuffer 0x00036410 (inlined dtor, EH state).
// Evidence: caller 0x00592496 builds esi with Rva004D64F5 ctor 0x004D64F5
// then calls this with an AsciiString temp; callers 0x004D12B2 etc.

#include "ascii_string.h"


class Rva004D64F5
{
public:
	void rva004D65F9(AsciiString s);
private:
	char m_pad00[0x1c];
	AsciiString m_str1c;
};

void Rva004D64F5::rva004D65F9(AsciiString s)
{
	AsciiString &slot = m_str1c;
	slot = s;
}
