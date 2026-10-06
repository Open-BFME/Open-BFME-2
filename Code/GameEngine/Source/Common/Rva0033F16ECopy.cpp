// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ??4Rva0033F16E@@QAEAAV0@ABV0@@Z, retail 0x0033F16E, 151 bytes.
// Assignment copying dwords at +0x04-+0x1C plus bytes at +0x20/+0x21 plus
// dwords at +0x24/+0x28/+0x2C plus 12B at +0x30 via movsd plus dwords at
// +0x3C/+0x40/+0x44/+0x48 plus byte at +0x4C plus dwords at +0x50/+0x54
// plus 12B at +0x58 via movsd plus dword at +0x64, preserving +0x00.
// Caller is 0x003427EC. Next row is another ??4 (DamageInfoOutput). Layout
// is pad to +0x04 then members with 2B gap at +0x22 and 3B gap at +0x4D.
// Identity stays honest Rva; vptr at +0x00 untouched like operator=.

struct TwelveBytes0033F16E
{
	char data[12];
};

class Rva0033F16E
{
public:
	Rva0033F16E &operator=(const Rva0033F16E &src);

private:
	char m_pad00[0x04];
	unsigned int m_04;
	unsigned int m_08;
	unsigned int m_0C;
	unsigned int m_10;
	unsigned int m_14;
	unsigned int m_18;
	unsigned int m_1C;
	unsigned char m_20;
	unsigned char m_21;
	char m_pad22[0x24 - 0x22];
	unsigned int m_24;
	unsigned int m_28;
	unsigned int m_2C;
	TwelveBytes0033F16E m_30;
	unsigned int m_3C;
	unsigned int m_40;
	unsigned int m_44;
	unsigned int m_48;
	unsigned char m_4C;
	char m_pad4D[0x50 - 0x4D];
	unsigned int m_50;
	unsigned int m_54;
	TwelveBytes0033F16E m_58;
	unsigned int m_64;
};

Rva0033F16E &Rva0033F16E::operator=(const Rva0033F16E &src)
{
	m_04 = src.m_04;
	m_08 = src.m_08;
	m_0C = src.m_0C;
	m_10 = src.m_10;
	m_14 = src.m_14;
	m_18 = src.m_18;
	m_1C = src.m_1C;
	m_20 = src.m_20;
	m_21 = src.m_21;
	m_24 = src.m_24;
	m_28 = src.m_28;
	m_2C = src.m_2C;
	m_30 = src.m_30;
	m_3C = src.m_3C;
	m_40 = src.m_40;
	m_44 = src.m_44;
	m_48 = src.m_48;
	m_4C = src.m_4C;
	m_50 = src.m_50;
	m_54 = src.m_54;
	m_58 = src.m_58;
	m_64 = src.m_64;
	return *this;
}
