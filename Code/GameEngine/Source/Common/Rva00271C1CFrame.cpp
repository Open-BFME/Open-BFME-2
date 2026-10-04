// cl: /O1 /MD
// ?rva00271C1C@Rva00271C1C@@QAEXXZ @0x00271C1C 28B
// Frame sum via TheGameLogic: if TheGameLogic then m384 = m04[0x558] + frame.
// Prev Rva00271B03MaxFrame 0x00271B03 35B max-tracking via TheGameLogic frame
// with m04[0x594] and m388; same GameLogic m_frame +0x40 and global
// 0x00DFE78C. Evidence: caller 0x004DBD66 plus TheGameLogic plus offsets
// +0x04 +0x558 +0x384 plus prev plus next with /O1.
struct Inner558
{
	unsigned char m_pre[0x558];
	unsigned int m_value;
};

class GameLogic
{
public:
	unsigned char m_pre[0x40];
	unsigned int m_frame;
};

extern GameLogic *TheGameLogic;

class Rva00271C1C
{
public:
	void rva00271C1C();

private:
	unsigned char m_pre04[4];
	Inner558 *m_04;
	unsigned char m_mid[0x384 - 0x08];
	int m_384;
};

void Rva00271C1C::rva00271C1C()
{
	if (TheGameLogic == 0)
		return;
	m_384 = m_04->m_value + TheGameLogic->m_frame;
}
