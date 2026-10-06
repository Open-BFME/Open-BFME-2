// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ??4Rva00235A37@@QAEAAV0@ABV0@@Z @0x00235A37 127B
// Copy assignment over 4 ints plus 7 AsciiStrings plus byte at +0x2C via
// pin-only AsciiString assign 0x000366F0. Evidence: unlock lane unblocks
// 0x00381F04; callers 0x00237683 0x00381FCA 0x0038393B; prev/next MultiPlayMult.
#include "ascii_string.h"

class Rva00235A37
{
public:
	Rva00235A37 &operator=(const Rva00235A37 &other);
private:
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	AsciiString m_10;
	AsciiString m_14;
	AsciiString m_18;
	AsciiString m_1C;
	AsciiString m_20;
	AsciiString m_24;
	AsciiString m_28;
	unsigned char m_2C;
};

Rva00235A37 &Rva00235A37::operator=(const Rva00235A37 &other)
{
	m_00 = other.m_00;
	m_04 = other.m_04;
	m_08 = other.m_08;
	m_0C = other.m_0C;
	m_10 = other.m_10;
	m_14 = other.m_14;
	m_18 = other.m_18;
	m_1C = other.m_1C;
	m_20 = other.m_20;
	m_24 = other.m_24;
	m_28 = other.m_28;
	m_2C = other.m_2C;
	return *this;
}
