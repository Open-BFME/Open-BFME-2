// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva00068295@Rva00068295@@QAEXXZ 0x00068295 35B
// If +0x3850 calls rowed rva000EA24D, if +0x3854 tail-jmps rowed rva000E7016.
// Same +0x3850/+0x3854 members and flags as Rva000682B8 neighbour.
// Evidence: callees rowed; chain from just-landed 0x000E7016.
class Rva000EA24D
{
public:
	void rva000EA24D();
};

class Rva000E7016
{
public:
	void rva000E7016();
};

class Rva00068295
{
public:
	void rva00068295();
private:
	unsigned char m_pad[0x3850];
	Rva000EA24D *m_3850;
	Rva000E7016 *m_3854;
};

void Rva00068295::rva00068295()
{
	if (m_3850)
		m_3850->rva000EA24D();
	if (m_3854)
		m_3854->rva000E7016();
}
