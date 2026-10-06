// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?add@Rva002E07AC@@QAEXH@Z @0x002E07AC 13B.
// Honest address name: __thiscall void adder with 1 caller and no callees.
// Byte-exact model: m_290 += v.
// Evidence: 1 caller jmp at 0x005C43A6 in 0x005C436E;
// prev 0x002E071E compare (/O1 /DNDEBUG /MD) and next 0x002E07C6 const getter.

struct Rva002E07AC
{
	char m_pad[0x290];
	int m_290;
	void add(int v);
};

void Rva002E07AC::add(int v)
{
	m_290 += v;
}
