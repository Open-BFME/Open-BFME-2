// cl: /Ireference/shims/bfme2_ascii /MD
// ??4Rva001EAFC1@@QAEAAV0@ABV0@@Z @0x001EAFC1 61B: honest sub-record assign
// 3 dwords at +0x00/+0x04/+0x08 then UnicodeString at +0x0C via pinned set
// 0x00037150 then AsciiString at +0x10 via pinned 0x000366F0 then byte at
// +0x14; returns *this (ret 4). Called as sub-object at +0x94 in
// ??4BfmeAssignRecord172 (0x001EB20E) and at +0xB0 in 0x002E0D93; 0x18 bytes
// (0xB0->0xC8 and 0x94->0xAC); no donor; honest Rva class.

#include "ascii_string.h"


class Rva001EAFC1
{
public:
	Rva001EAFC1 &operator=(const Rva001EAFC1 &other);
private:
	int m_00;
	int m_04;
	int m_08;
	StringBase<unsigned short> m_0C;
	AsciiString m_10;
	unsigned char m_14;
};

Rva001EAFC1 &Rva001EAFC1::operator=(const Rva001EAFC1 &other)
{
	m_00 = other.m_00;
	m_04 = other.m_04;
	m_08 = other.m_08;
	m_0C.set(other.m_0C);
	m_10 = other.m_10;
	m_14 = other.m_14;
	return *this;
}
