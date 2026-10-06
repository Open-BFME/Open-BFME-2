// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ??0Rva0029E067@@QAE@ABU0@@Z @0x0029E067 127B
// Copy ctor: StringBase<char> at +0/+4 via pin 0x000365F0 plus int/byte tail
// +8..+30. Unblocks 0x0029FB63; caller 0x0029E14E.
template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#include "ascii_string.h"


struct Rva0029E067
{
	AsciiString m_00;
	AsciiString m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	unsigned char m_1C;
	int m_20;
	int m_24;
	int m_28;
	int m_2C;
	int m_30;
	Rva0029E067(const Rva0029E067 &src);
};

Rva0029E067::Rva0029E067(const Rva0029E067 &src) : m_00(src.m_00), m_04(src.m_04)
{
	m_08 = src.m_08;
	m_0C = src.m_0C;
	m_10 = src.m_10;
	m_14 = src.m_14;
	m_18 = src.m_18;
	m_1C = src.m_1C;
	m_20 = src.m_20;
	m_24 = src.m_24;
	m_28 = src.m_28;
	m_2C = src.m_2C;
	m_30 = src.m_30;
}
