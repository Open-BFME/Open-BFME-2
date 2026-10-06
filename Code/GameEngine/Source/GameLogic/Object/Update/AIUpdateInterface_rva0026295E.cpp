// cl: /DNDEBUG /MD
//
// ?rva0026295E@AIUpdateInterface@@QAEXXZ, retail 0x0026295E, 15 bytes.
// Sibling clearer in the AIUpdateInterface +0x134/+0x3BF cluster beside
// 0x0026293E: zeroes the int at +0x134 via the /O1 and-idiom then clears the
// byte at +0x3BF. Layout follows the landed wakeUpNow 0x00262871 (+0x3C2)
// and setQueue 0x0026282A (+0x17C) TUs with m_turretAI at +0x20C bounding the
// tail. Leaf with no callees.

class AIUpdateInterface
{
	char m_pad00[0x134];
	int m_field134;
	char m_pad138[0x3BF - 0x138];
	bool m_flag3BF;
public:
	void rva0026295E();
};

void AIUpdateInterface::rva0026295E()
{
	m_field134 = 0;
	m_flag3BF = false;
}
