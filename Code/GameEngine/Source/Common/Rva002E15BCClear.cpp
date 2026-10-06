// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva002E15BC@Rva002E15BC@@QAEXPAX@Z @0x002E15BC 42B.
// Bit-clear method: if arg+4 nonzero return, else clear bit arg+0x38 in
// this+0x1D8 array via ~(1u << (bit & 31)). Evidence: caller 0x0020EDB5
// passing element plus this; prev/next share /O1.
struct Rva002E15BCArg
{
	int m_00;
	int m_04;
	char m_pad[0x38 - 8];
	int m_38;
	char m_pad2[0x78 - 0x3C];
	unsigned char m_78;
};

struct Rva002E15BC
{
	char m_pad[0x1D8];
	unsigned int m_bits[1];
	void rva002E15BC(void *arg);
	void rva002E1588(void *arg, bool flag);
};

void Rva002E15BC::rva002E15BC(void *argp)
{
	Rva002E15BCArg *arg = (Rva002E15BCArg *)argp;
	if (arg->m_04 != 0)
		return;
	unsigned int bit = (unsigned int)arg->m_38;
	m_bits[bit >> 5] &= ~(1u << (bit & 31));
}

// ?rva002E1588@Rva002E15BC@@QAEXPAX_N@Z @0x002E1588 52B.
// Bit-set sibling: if arg+4 nonzero return; if flag set but arg+0x78 zero
// return; else set bit arg+0x38 in this+0x1D8. Evidence: caller 0x0020ED75.
void Rva002E15BC::rva002E1588(void *argp, bool flag)
{
	Rva002E15BCArg *arg = (Rva002E15BCArg *)argp;
	if (arg->m_04 != 0)
		return;
	if (flag != 0 && arg->m_78 == 0)
		return;
	unsigned int bit = (unsigned int)arg->m_38;
	m_bits[bit >> 5] |= (1u << (bit & 31));
}
