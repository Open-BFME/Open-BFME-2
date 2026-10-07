// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva002E15BC@Rva002E15BC@@QAEXPAX@Z @0x002E15BC 42B.
// Bit-clear method: if arg+4 nonzero return, else clear bit arg+0x38 in
// this+0x1D8 array via ~(1u << (bit & 31)). Evidence: caller 0x0020EDB5
// passing element plus this; prev/next share /O1.
#include "../../../Libraries/Source/WWVegas/WWLib/FixedStorage128.h"

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
	unsigned int m_bits[32];
	void rva002E15BC(void *arg);
	void rva002E1588(void *arg, bool flag);
	void rva002E14E9(const BfmeFixedStorage128 &mask);
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

class UpgradeCenter;
extern UpgradeCenter *TheUpgradeCenter;
struct Rva0026F0F0
{
	void *rva0026F0F0(const void *mask);
};
struct Rva00046827
{
	int rva00046827();
};

// Native 002E14E9..002E1588, 159B, RET4. The adjacent rowed set/clear
// methods prove the receiver's mask at +1D8 and the template's +04/+38/+78
// fields. Both native temporary masks are 128 bytes, copied by 0004548B.
// Original class and method names remain unresolved.
void Rva002E15BC::rva002E14E9(const BfmeFixedStorage128 &mask)
{
	BfmeFixedStorage128 unchecked(mask);
	BfmeFixedStorage128 accepted(mask);
	while (reinterpret_cast<Rva00046827 *>(&unchecked)->rva00046827() > 0) {
		Rva002E15BCArg *arg = static_cast<Rva002E15BCArg *>(
			reinterpret_cast<Rva0026F0F0 *>(TheUpgradeCenter)->rva0026F0F0(&unchecked));
		if (!arg)
			break;
		if (!arg->m_78 || arg->m_04 != 0) {
			unsigned int bit = static_cast<unsigned int>(arg->m_38);
			reinterpret_cast<unsigned int *>(accepted.bytes)[bit >> 5] &= ~(1u << (bit & 31));
		}
		unsigned int bit = static_cast<unsigned int>(arg->m_38);
		reinterpret_cast<unsigned int *>(unchecked.bytes)[bit >> 5] &= ~(1u << (bit & 31));
	}
	*reinterpret_cast<BfmeFixedStorage128 *>(m_bits) = accepted;
}
