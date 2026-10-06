// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva0033FCC8@Rva0033FCC8@@QAEXXZ, retail 0x0033FCC8, 20 bytes.
// Copies uint at +0x20 to +0x58 and 12 bytes at +0x24 to +0x5C via three
// movsd. Called with the +0x30 member of AIUpdate-like callers
// (0x00262F19 slot 117 family) which save/clear the +0x38 bool around the
// call. Layout is pad to +0x20 then uint plus 12-byte block then pad to
// +0x58 then uint plus 12-byte block. Identity stays honest Rva address
// name; no vtable or donor proves the owner.

struct TwelveBytes
{
	char data[12];
};

class Rva0033FCC8
{
public:
	void rva0033FCC8();

private:
	char m_pad00[0x20];
	unsigned int m_20;
	TwelveBytes m_24;
	char m_pad30[0x58 - 0x30];
	unsigned int m_58;
	TwelveBytes m_5C;
};

void Rva0033FCC8::rva0033FCC8()
{
	m_58 = m_20;
	m_5C = m_24;
}
