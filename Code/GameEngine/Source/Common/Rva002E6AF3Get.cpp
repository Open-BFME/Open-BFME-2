// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?get@Rva002E6AF3@@QBEHXZ @0x002E6AF3 19B.
// Honest address name: unclaimed const getter with 22 callers and no donor
// string vtable or export to prove a real identity. Byte-exact model:
// null-checked ptr-chase at +0 then (dword at +0x2C >> 3) & 1. Evidence:
// 22 UNCLAIMED callers e.g. 0x002F44AE; callees none; prev/next are
// dx8wrapper and Disp8Shr getters; flags /O1 for xor-eax false tail.
// Positive if-form places true path inline per §4.6.

class Rva002E6AF3
{
public:
	int get() const;
	void *m_ptr;
};
struct Rva002E6AF3Inner
{
	char m_pad[0x2C];
	unsigned int m_2C;
};
int Rva002E6AF3::get() const
{
	if (m_ptr)
		return (((Rva002E6AF3Inner *)m_ptr)->m_2C >> 3) & 1;
	return 0;
}
