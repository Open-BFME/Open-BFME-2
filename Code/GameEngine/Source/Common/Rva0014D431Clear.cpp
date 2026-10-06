// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva0014D431@Rva0014D431@@QAEXXZ @ 0x0014D431 15B: and [ecx+0xD4],0 / and [ecx+0xD0],0 / ret; caller 0x0017438B; honest address name.
class Rva0014D431
{
public:
	void rva0014D431();
private:
	char m_pad[0xD0];
	int m_d0;
	int m_d4;
};

void Rva0014D431::rva0014D431()
{
	m_d4 = 0;
	m_d0 = 0;
}
