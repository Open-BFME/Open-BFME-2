// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva005686C1@Rva005686C1@@QAEHH@Z @0x005686C1 24B: bounds-checked indexed
// dword getter returning 0 on out-of-range. Reads ecx plus int index with
// ret 4. Array of 4 dwords at +0x2C. Caller at 0x005C938B in 0x005C9311 passes
// index 0. Prev 0x005686B9 word getter and next 0x00568721 Less share page.
class Rva005686C1
{
public:
	int rva005686C1(int index);
private:
	char m_pad[0x2C];
	int m_vals[4];
};
int Rva005686C1::rva005686C1(int index)
{
	if (index < 0 || index >= 4)
		return 0;
	return m_vals[index];
}
