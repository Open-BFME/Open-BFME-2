// cl: /DNDEBUG /MD
//
// ?rva0026293E@AIUpdateInterface@@QAEXXZ, retail 0x0026293E, 32 bytes.
// Sibling conditional setter in the AIUpdateInterface +0x134 cluster beside
// clearer 0x0026295E: when the byte at +0x3BD is already zero and the int at
// +0x134 is positive zeroes the int at +0x138 and sets the byte at +0x3BF.
// Layout follows the landed wakeUpNow (+0x3C2) and setQueue (+0x17C) TUs.
// Leaf with no callees.

class AIUpdateInterface
{
	char m_pad00[0x134];
	int m_field134;
	int m_field138;
	char m_pad13C[0x3BD - 0x13C];
	bool m_flag3BD;
	char m_pad3BE;
	bool m_flag3BF;
public:
	void rva0026293E();
};

void AIUpdateInterface::rva0026293E()
{
	if (m_flag3BD == false && m_field134 > 0)
	{
		m_field138 = 0;
		m_flag3BF = true;
	}
}
