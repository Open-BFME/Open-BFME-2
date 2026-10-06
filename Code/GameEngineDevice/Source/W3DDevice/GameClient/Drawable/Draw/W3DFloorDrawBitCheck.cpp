// cl: /DNDEBUG /MD
// ?test@Rva000CF0D6@@QBE_NPBV1@@Z @0x000CF0D6 41B
// Honest Rva name; free function in 000CF page between W3DFloorDraw xfer
// (0xCF074) and ctor (0xCF10B). Compares 19 dwords: (this[i] & other[i])==other[i].
// Callers at 0xCF38F (same page loop stride 0x4C) and distant weapon logic
// (0x2C810A etc.). No callees; gate can resolve. Prev/next both /O1 /DNDEBUG /MD.
class Rva000CF0D6
{
public:
	bool test(const Rva000CF0D6 *other) const;
	unsigned int m_bits[19];
};

bool Rva000CF0D6::test(const Rva000CF0D6 *other) const
{
	for (unsigned i = 0; i < 19; ++i) {
		if ((m_bits[i] & other->m_bits[i]) != other->m_bits[i])
			return false;
	}
	return true;
}
