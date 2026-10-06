// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva002E6F8B@Rva002E6F8B@@QAEPAV1@XZ @0x002E6F8B 7B.
// Honest address name: unclaimed __thiscall clearer with 1 caller and no donor
// string vtable or export to prove a real identity. Byte-exact model:
// zeroes byte at +0xC and returns this (mov eax,ecx fences the 7-byte shape
// vs the 5-byte void setter). Evidence: UNCLAIMED caller 0x002ED535
// lea ecx,[ebp-0x40] ignores return; callees none; prev/next are Disp float
// getters in the same Common dir; flags /O1 minimal frameless match.

class Rva002E6F8B
{
public:
	Rva002E6F8B *rva002E6F8B();
private:
	char m_pad[0xC];
	unsigned char m_C;
};
Rva002E6F8B *Rva002E6F8B::rva002E6F8B()
{
	m_C = 0;
	return this;
}
