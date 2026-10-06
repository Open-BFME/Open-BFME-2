// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva0033F83D@Rva0033F83D@@QAEXPBUSource0033F83D@@@Z, retail 0x0033F83D, 21 bytes.
// m_3C = src ? src->m_74 : 0. Called from 0x003511E3 with the Object* from
// findObjectByID 0x00049DC5. Layout is pad to +0x3C then int; source has
// int at +0x74. Identity stays honest Rva address name; no vtable or donor
// proves the owner.

struct Source0033F83D
{
	char m_pad00[0x74];
	int m_74;
};

class Rva0033F83D
{
public:
	void rva0033F83D(const Source0033F83D *src);

private:
	char m_pad00[0x3C];
	int m_3C;
};

void Rva0033F83D::rva0033F83D(const Source0033F83D *src)
{
	m_3C = src ? src->m_74 : 0;
}
