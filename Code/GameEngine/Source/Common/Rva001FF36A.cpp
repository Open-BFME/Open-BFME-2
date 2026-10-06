// cl: /MD
//
// ?rva001FF36A@Rva001FF36A@@QAE_NHHHHHH@Z @0x001FF36A 63B
// Leaf with conditional stores to +0 +0x0C +0x10 plus unconditional +0x14
// then base pin 0x002E8548 when +4 is zero else false.
// Evidence: pin name; callee 0x002E8548 pin-only; caller 0x002EBABF in
// Rva002EBA88; prev ReloadIniFileNotices and next VtableVirtualForwarders.
class Rva002E8548
{
public:
	bool rva002E8548(int a, int b);
	int m_00;
	int m_04;
	int m_08;
};

class Rva001FF36A : public Rva002E8548
{
public:
	bool rva001FF36A(int a1, int a2, int a3, int a4, int a5, int a6);
	int m_0C;
	int m_10;
	int m_14;
};

bool Rva001FF36A::rva001FF36A(int a1, int a2, int a3, int a4, int a5, int a6)
{
	if (a1)
		m_00 = a1;
	if (a4)
		m_0C = a4;
	if (a5)
		m_10 = a5;
	m_14 = a6;
	if (m_04 == 0)
		return rva002E8548(a2, a3);
	return false;
}
