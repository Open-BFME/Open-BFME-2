// cl: /DNDEBUG /MD
//
// ?rva002E071E@Rva002E071E@@QBE_NPBV1@@Z @0x002E071E 48B.
// Equality-like predicate: true when dword at +0x14 matches, else compares
// dword at +0x34 with -1 as invalid sentinel.
// Evidence: 15 callers including 0x0020E316 0x0020FFBC 0x00211CB9; callees none;
// neighbours 0x002E0675 Disp8 setters and 0x002E07C6 const getters in Common.

class Rva002E071E
{
public:
	bool rva002E071E(const Rva002E071E *other) const;

private:
	char m_pad00[0x14];
	int m_14;
	char m_pad18[0x1C];
	int m_34;
};

bool Rva002E071E::rva002E071E(const Rva002E071E *other) const
{
	if (other->m_14 == m_14)
		return true;
	if (m_34 == -1 || other->m_34 == -1)
		return false;
	return m_34 == other->m_34;
}
