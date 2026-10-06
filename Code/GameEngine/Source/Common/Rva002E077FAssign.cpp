// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ??4Rva002E077F@@QAEAAV0@ABV0@@Z @0x002E077F 45B operator= copying 6 dwords at +4..+0x18 then returning this
// Evidence: no callees; caller 0x002E0BFE in 0x002E0BEB; neighbours 0x002E071E compare and 0x002E07AC adder share /O1
class Rva002E077F
{
public:
	Rva002E077F &operator=(const Rva002E077F &src);
	virtual ~Rva002E077F();
private:
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	int m_14;
	int m_18;
};

Rva002E077F &Rva002E077F::operator=(const Rva002E077F &src)
{
	m_04 = src.m_04;
	m_08 = src.m_08;
	m_0c = src.m_0c;
	m_10 = src.m_10;
	m_14 = src.m_14;
	m_18 = src.m_18;
	return *this;
}
