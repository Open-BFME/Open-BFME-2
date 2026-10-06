// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva00382234@Rva00382234@@QAEXVAsciiString@@@Z 0x00382234 55B
// Sets AsciiString at +0xFE8 from by-value param; temp destroyed via releaseBuffer.
// Evidence: calls 0x000366F0 AsciiString assign and 0x00036410 releaseBuffer; callers 0x382710 0x383929.
#include "ascii_string.h"


class Rva00382234
{
	char m_pad[0xFE8];
	AsciiString m_fe8;
public:
	void rva00382234(AsciiString s);
};

void Rva00382234::rva00382234(AsciiString s)
{
	AsciiString* src = &s;
	AsciiString* dst = &m_fe8;
	*dst = *src;
}
