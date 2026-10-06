// cl: /MD
//
// ?rva003EFDDB@Rva003EFDDBHolder@@QAEXHPAURva003EFDDBOut@@@Z, retail 0x003EFDDB, 26 bytes.
// __thiscall method comparing this+0x13C with a stack int and storing 0
// (equal) or -1 (different) at out+0x10 via branchless sete/dec. Leaf.
// Callers 0x00249BE8 0x003F02DC 0x003F355E 0x004FE04E. Prev 0x003EFDD7 lea
// getter / next 0x003EFE82 LivingWorldRegionID getter. Honest address name;
// owner class and member identities unproven.
struct Rva003EFDDBOut
{
	char m_pad[0x10];
	int m_flag;
};

struct Rva003EFDDBHolder
{
	char m_pad[0x13C];
	int m_val;
	void rva003EFDDB(int cmp, struct Rva003EFDDBOut *out);
};

void Rva003EFDDBHolder::rva003EFDDB(int cmp, struct Rva003EFDDBOut *out)
{
	if (m_val == cmp)
		out->m_flag = 0;
	else
		out->m_flag = -1;
}
