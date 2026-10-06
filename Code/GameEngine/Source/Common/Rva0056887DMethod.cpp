// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva0056887D@Rva0056887D@@QAEAAV1@ABV1@G@Z @0x0056887D 28B: copy 4+4 from src
// plus word param at +8; returns this. Two dwords at +0/+4 from src, word at
// +8 from second arg. Callers at 0x0056984B 0x00569C58 unclaimed.
class Rva0056887D
{
public:
	Rva0056887D &rva0056887D(const Rva0056887D &src, unsigned short w);

private:
	int m00; // +0
	int m04; // +4
	short m08; // +8
};

Rva0056887D &Rva0056887D::rva0056887D(const Rva0056887D &src, unsigned short w)
{
	m00 = src.m00;
	m04 = src.m04;
	m08 = w;
	return *this;
}
