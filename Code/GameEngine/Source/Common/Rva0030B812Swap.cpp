// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva0030B812@Rva0030B812@@QAEXPAU1@@Z, retail 0x0030B812, 31 bytes.
// Swap holder via rowed inner swap 0x0030B76F plus int at +0x28.
// Evidence: chain from 0x0030B76F; callers 0x00329106 0x00330BC7; prev swap /O1 /Ob0 /EHsc /arch:SSE next reserve vector e8.

struct Rva0030B76F
{
	void rva0030B76F(Rva0030B76F *other);
	char m_pad[0x28];
};

struct Rva0030B812
{
	void rva0030B812(Rva0030B812 *other);
	Rva0030B76F m_00;
	int m_28;
};

void Rva0030B812::rva0030B812(Rva0030B812 *other)
{
	m_00.rva0030B76F(&other->m_00);
	int t = m_28;
	m_28 = other->m_28;
	other->m_28 = t;
}
