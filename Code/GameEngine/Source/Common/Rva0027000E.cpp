// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva0027000E@Rva0027000E@@QAE_NXZ @0x0027000E 23B
// Returns int at +0xB8 == 3 OR == 4.
// Evidence: no donor; honest Rva name; callers at 0x002755E6 0x00276C34.
class Rva0027000E
{
public:
	bool rva0027000E();
private:
	unsigned char m_pad[0xb8];
	int m_b8;
};

bool Rva0027000E::rva0027000E()
{
	return m_b8 == 3 || m_b8 == 4;
}
