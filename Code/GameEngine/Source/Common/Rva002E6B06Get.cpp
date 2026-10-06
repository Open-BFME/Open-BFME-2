// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva002E6B06@Rva002E6B06@@QAEHXZ @0x002E6B06 19B.
// Honest address name: unclaimed __thiscall null-checked ptr-chase bit test.
// Byte-exact model: mov eax [ecx] test je to shared false tail then
// mov eax [eax+0x2C] shr 4 and 1. True path falls through and false tail
// is xor eax eax ret.
// Evidence: 22 callers in 0x002Fxxxx free bodies pushing thiscall context;
// callees none; prev is dx8wrapper Get_Vertex_Count and next is a Disp8
// shr-and getter in Common; flags /O1 from PtrChaseNullOrZero sibling
// with the same test-je and xor-tail idioms.

class Rva002E6B06
{
public:
	int rva002E6B06();
	void *m_ptr;
};

struct Rva002E6B06Inner
{
	char m_pad[0x2c];
	unsigned int m_value;
};

int Rva002E6B06::rva002E6B06()
{
	if (m_ptr != 0)
		return (((Rva002E6B06Inner *)m_ptr)->m_value >> 4) & 1;
	return 0;
}
