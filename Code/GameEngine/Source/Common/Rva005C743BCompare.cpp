// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva005C743B@Rva005C743B@@QBE_NXZ, retail 0x005C743B 13B.
// Dword compare: returns m_00 >= m_04 as bool.
// Evidence: mov eax [ecx] xor edx edx cmp eax [ecx+4] setge dl mov al dl;
// callers at 0x55A82A 0x55A85B share this.

class Rva005C743B
{
public:
	bool rva005C743B() const;
	int m_00;
	int m_04;
};

bool Rva005C743B::rva005C743B() const
{
	return m_00 >= m_04;
}
