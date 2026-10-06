// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ??0Rva00382574@@QAE@ABV0@@Z, retail 0x00382574, 175 bytes.
// Copy ctor copying four dwords at +0..+0x0c, seven narrow strings at
// +0x10/+0x14/+0x18/+0x1c/+0x20/+0x24/+0x28 via the pinned StringBase copy,
// then the byte at +0x2c. Identity from caller 0x00383082 and the seven
// 0x365F0 calls plus ret 4 single arg.
#include "ascii_string.h"


struct Rva00382574
{
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	AsciiString m_10;
	AsciiString m_14;
	AsciiString m_18;
	AsciiString m_1c;
	AsciiString m_20;
	AsciiString m_24;
	AsciiString m_28;
	bool m_2c;

	Rva00382574(const Rva00382574 &other);
};

Rva00382574::Rva00382574(const Rva00382574 &other)
	: m_00(other.m_00)
	, m_04(other.m_04)
	, m_08(other.m_08)
	, m_0c(other.m_0c)
	, m_10(other.m_10)
	, m_14(other.m_14)
	, m_18(other.m_18)
	, m_1c(other.m_1c)
	, m_20(other.m_20)
	, m_24(other.m_24)
	, m_28(other.m_28)
	, m_2c(other.m_2c)
{
}
