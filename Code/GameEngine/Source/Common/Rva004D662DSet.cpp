// cl: /Ireference/shims/bfme2_ascii /Oy- /MD /EHsc
// ?rva004D662D@Rva004D65DC@@QAEXVAsciiString@@@Z @0x004D662D (52B):
// AsciiString setter on Rva004D65DC: copies the by-value argument into the
// +0x20 member via pin-only operator= 0x000366F0, then destroys the parameter
// via rowed StringBase<char> releaseBuffer 0x00036410 (inlined dtor, EH state).
// Evidence: caller 0x00592520 builds its object with Rva004D65DC ctor
// 0x004D65DC then calls this with an AsciiString temp; caller 0x004D12B2.

#include "ascii_string.h"


class Rva004D65DC
{
public:
	void rva004D662D(AsciiString s);
private:
	char m_pad00[0x20];
	AsciiString m_str20;
};

void Rva004D65DC::rva004D662D(AsciiString s)
{
	AsciiString &slot = m_str20;
	slot = s;
}
