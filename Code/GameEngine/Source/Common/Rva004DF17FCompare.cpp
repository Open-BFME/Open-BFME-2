// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva004DF17F@Rva004DF17F@@QBE_NXZ, RVA 0x004DF17F, 14 bytes.
// Dword compare: returns m_04 >= m_08 as bool.
// Evidence: mov eax [ecx+4] xor edx edx cmp eax [ecx+8] setge dl mov al dl;
// caller at 0x003E41B2 tests al; same shape as rowed 0x005C743B 13B with disp8 shift.
class Rva004DF17F
{
public:
	bool rva004DF17F() const;
	int m_00;
	int m_04;
	int m_08;
};

bool Rva004DF17F::rva004DF17F() const
{
	return m_04 >= m_08;
}
