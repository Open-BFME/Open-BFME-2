// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?rva00214E02@Rva00214E02@@QAEPAV1@ABV1@@Z retail 0x00214E02 274 bytes.
// Copy-assign: five AsciiStrings at +0x00 +0x04 +0x08 +0x14 +0x94 via rowed
// StringBase<char>::set 0x000366F0, ints/bytes plus four 12-byte blocks,
// returns this with ret 4. Evidence: callers at 0x002150C8 0x00215278
// 0x002152A6, callees rowed, neighbours Rva00214D59Pack/Rva00214F14Init.
#include "ascii_string.h"

struct Block12
{
	int v[3];
};

class Rva00214E02
{
public:
	Rva00214E02 *rva00214E02(const Rva00214E02 &src);
private:
	AsciiString m_00;
	AsciiString m_04;
	AsciiString m_08;
	int m_0C;
	int m_10;
	AsciiString m_14;
	int m_18;
	int m_1C;
	Block12 m_20;
	Block12 m_2C;
	int m_38;
	int m_3C;
	int m_40;
	int m_44;
	unsigned char m_48;
	unsigned char m_49;
	unsigned char m_4A;
	char _pad4B;
	int m_4C;
	Block12 m_50;
	int m_5C;
	Block12 m_60;
	int m_6C;
	Block12 m_70;
	int m_7C;
	int m_80;
	int m_84;
	int m_88;
	int m_8C;
	int m_90;
	AsciiString m_94;
};

Rva00214E02 *Rva00214E02::rva00214E02(const Rva00214E02 &src)
{
	((StringBase<char> *)&m_00)->set(*(const StringBase<char> *)&src.m_00);
	((StringBase<char> *)&m_04)->set(*(const StringBase<char> *)&src.m_04);
	((StringBase<char> *)&m_08)->set(*(const StringBase<char> *)&src.m_08);
	m_0C = src.m_0C;
	m_10 = src.m_10;
	((StringBase<char> *)&m_14)->set(*(const StringBase<char> *)&src.m_14);
	m_18 = src.m_18;
	m_1C = src.m_1C;
	m_20 = src.m_20;
	m_2C = src.m_2C;
	m_38 = src.m_38;
	m_3C = src.m_3C;
	m_40 = src.m_40;
	m_44 = src.m_44;
	m_48 = src.m_48;
	m_49 = src.m_49;
	m_4A = src.m_4A;
	m_4C = src.m_4C;
	m_50 = src.m_50;
	m_5C = src.m_5C;
	m_60 = src.m_60;
	m_6C = src.m_6C;
	m_70 = src.m_70;
	m_7C = src.m_7C;
	m_80 = src.m_80;
	m_84 = src.m_84;
	m_88 = src.m_88;
	m_8C = src.m_8C;
	m_90 = src.m_90;
	((StringBase<char> *)&m_94)->set(*(const StringBase<char> *)&src.m_94);
	return this;
}
