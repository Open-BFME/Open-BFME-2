// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva0033F852@Rva0033F852@@QAEXPBUSource0033F852@@@Z, retail 0x0033F852, 21 bytes.
// m_40 = src ? src->m_34 : 0. Twin of 0x0033F83D (m_3C = src->m_74 : 0),
// called from the same 0x003511E3 on the same +0x20 object. Layout is pad
// to +0x40 then int; source has int at +0x34. Identity stays honest Rva
// address name.

struct Source0033F852
{
	char m_pad00[0x34];
	int m_34;
};

class Rva0033F852
{
public:
	void rva0033F852(const Source0033F852 *src);

private:
	char m_pad00[0x40];
	int m_40;
};

void Rva0033F852::rva0033F852(const Source0033F852 *src)
{
	m_40 = src ? src->m_34 : 0;
}
