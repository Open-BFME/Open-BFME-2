// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ??4Rva003427DD@@QAEAAV0@ABV0@@Z, retail 0x003427DD, 45 bytes.
// Chain from 0x0033F16E (Rva0033F16E::assign). Assignment calling the
// member +0x04 assign via rowed 0x0033F16E then copying dword at +0x70 and
// +0x74 plus byte at +0x78, returning *this. Callers include 0x0035164E.
// Layout is pad to +0x04 plus Rva0033F16E plus pad to +0x70 plus ints plus
// byte. Identity stays honest Rva assignment like the 0x0033F16E row.

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

class Rva003427DD
{
public:
	Rva003427DD &operator=(const Rva003427DD &src);

private:
	char m_pad00[0x04];
	Rva0033F16E m_04;
	char m_pad6C[0x70 - 0x6C];
	unsigned int m_70;
	unsigned int m_74;
	unsigned char m_78;
};

Rva003427DD &Rva003427DD::operator=(const Rva003427DD &src)
{
	m_04 = src.m_04;
	m_70 = src.m_70;
	m_74 = src.m_74;
	m_78 = src.m_78;
	return *this;
}
