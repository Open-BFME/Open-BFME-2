// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva0052B024@Rva0052B024@@QAEXE@Z @0x0052B024 33B refresh loop over [ecx+0x2c,0x30) via rowed 0x005C41C9.
// Evidence: unlock lane all callees rowed; caller at 0x004E0618 in 0x004E060C; neighbours 0x0052AF7E and 0x0052B53C share /O1.
class Rva005C41C9
{
public:
	void rva005C41C9(unsigned char v);
};
class Rva0052B024
{
public:
	void rva0052B024(unsigned char v);
private:
	char m_pad[0x2c];
	Rva005C41C9 **m_begin;
	Rva005C41C9 **m_end;
};
void Rva0052B024::rva0052B024(unsigned char v)
{
	Rva005C41C9 **begin = m_begin;
	Rva005C41C9 **end = m_end;
	for (Rva005C41C9 **p = begin; p != end; ++p)
		(*p)->rva005C41C9(v);
}
