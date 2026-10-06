// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva002B2B66@Rva002B2B66@@QAEHXZ @0x002B2B66 18B
// Null-guarded indirect getter: pointer at +0x98, null returns -1 via
// or eax,-1, else dword at +0x14 of target. Evidence: 24 callers;
// unblocks 20 functions; neighbours are /O1.
struct Rva002B2B66Inner
{
	char m_pad[0x14];
	int m_val;
};

class Rva002B2B66
{
public:
	int rva002B2B66();

private:
	char m_pad[0x98];
	Rva002B2B66Inner *m_ptr;
};

int Rva002B2B66::rva002B2B66()
{
	Rva002B2B66Inner *p = m_ptr;
	if (p)
		return p->m_val;
	return -1;
}
