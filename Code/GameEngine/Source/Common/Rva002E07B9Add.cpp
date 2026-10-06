// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?add@Rva002E07B9@@QAEXH@Z @0x002E07B9 13B.
// Honest address name: __thiscall void adder with 1 caller and no callees.
// Byte-exact model: m_294 += v. Sibling of 0x002E07AC (+0x290) same recipe.
// Evidence: 1 caller jmp at 0x005C43A0 in 0x005C436E;
// prev 0x002E07AC adder (/O1) and next 0x002E07C6 const getter.

struct Rva002E07B9
{
	char m_pad[0x294];
	int m_294;
	void add(int v);
};

void Rva002E07B9::add(int v)
{
	m_294 += v;
}
