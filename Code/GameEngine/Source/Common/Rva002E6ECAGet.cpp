// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?get@Rva002E6ECA@@QBEHXZ @0x002E6ECA 46B.
// Honest address name: unclaimed predicate with 14 callers and no donor
// string vtable or export to prove a real identity. Byte-exact model:
// byte flag at +0x48 gates an int at +0x60 tested for 1 2 3 4 7 8.
// Evidence: 14 UNCLAIMED callers; callees none; prev/next are Disp getters
// in the same Common dir; flags /O1 from Disp siblings with the same
// xor-inc and cmp-imm8 idioms.

struct Rva002E6ECA
{
	char m_pad[0x48];
	unsigned char m_48;
	char m_pad2[0x60 - 0x49];
	int m_60;
	int get() const;
};

int Rva002E6ECA::get() const
{
	if (m_48) {
		int v = m_60;
		return v == 1 || v == 2 || v == 3 || v == 4 || v == 7 || v == 8;
	}
	return 0;
}
