// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva000E440D@Rva000E440D@@QAE_NXZ retail 0x000E440D 21B
// Evidence: xor cmp byte +0x9C je cmp dword +0x98 2 je inc ret; callers 0x000E5AEF 0x000E5CDE 0x000E5DE1 0x000E606C
class Rva000E440D
{
public:
	bool rva000E440D();
private:
	char m_pad00[0x98];
	int m_98;
	bool m_9C;
};

bool Rva000E440D::rva000E440D()
{
	return m_9C != 0 && m_98 != 2;
}
