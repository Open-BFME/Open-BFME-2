// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva002AAE81@Rva002AAE81@@QAEXVAsciiString@@@Z 0x002AAE81 52B
// Sets AsciiString at +8 from by-value param via temp dst-src order.
// Evidence: calls 0x000366F0 assign plus 0x00036410 release; callers 0x2AAF19 etc.
#include "ascii_string.h"


class Rva002AAE81
{
	char m_pad[8];
	AsciiString m_8;
public:
	void rva002AAE81(AsciiString s);
};

void Rva002AAE81::rva002AAE81(AsciiString s)
{
	AsciiString* src = &s;
	AsciiString* dst = &m_8;
	*dst = *src;
}
