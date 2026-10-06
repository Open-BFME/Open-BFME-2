// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva002E6C4D@Rva002E6C4D@@QAEHXZ @0x002E6C4D 19B.
// Honest address name: unclaimed __thiscall null-checked ptr-chase bit test.
// Byte-exact model: mov eax [ecx] test je to false tail then
// mov eax [eax+0x2C] shr 2 and 1. True path falls through and false tail
// is xor eax eax ret.
// Evidence: 1 caller 0x002F19AF in UNCLAIMED 0x002F18D4; callees none;
// prev 0x002E6C0E in Disp8ShrAndDwordGetters.cpp and next 0x002E6DC4 in
// Rva002E6DC4Check.cpp; flags /O1 from PtrChaseNullOrZero siblings
// Rva002E6B06 shift 4 and Rva002E6AF3 shift 3 with same test-je xor-tail idioms.

class Rva002E6C4D
{
public:
	int rva002E6C4D();
	void *m_ptr;
};

struct Rva002E6C4DInner
{
	char m_pad[0x2c];
	unsigned int m_value;
};

int Rva002E6C4D::rva002E6C4D()
{
	if (m_ptr != 0)
		return (((Rva002E6C4DInner *)m_ptr)->m_value >> 2) & 1;
	return 0;
}
