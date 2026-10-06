// cl: /MD
// TheGameLogic is the global at 0x00DFE78C; the banked attempt read it
// through a literal-address macro, which changed the load order.
//
// ?rva00271B03@Rva00271B03@@QAEXXZ retail 0x00271B03 35 bytes.
// Max tracking via TheGameLogic frame: if m04 then v=m04[0x594]+frame if v>m388
// then m388=v. Unblocks 0x0027B18C. Prev/next in Common with /O1 /MD.
// Evidence: callers 0x0027B418 0x0027B44B plus TheGameLogic 0x00DFE78C plus
// frame +0x40 plus offsets +0x04 +0x594 +0x388.

struct Inner594
{
	unsigned char m_pre[0x594];
	unsigned int m_value;
};

class GameLogic
{
public:
	unsigned char m_pre[0x40];
	unsigned int m_frame;
};

extern GameLogic *TheGameLogic;
class Rva00271B03
{
public:
	void rva00271B03();

private:
	unsigned char m_pre04[4];
	Inner594 *m_04;
	unsigned char m_mid[0x388 - 0x08];
	int m_388;
};

void Rva00271B03::rva00271B03()
{
	if (m_04 != 0)
	{
		unsigned int v1 = m_04->m_value;
		unsigned int v2 = TheGameLogic->m_frame;
		unsigned int v = v1 + v2;
		if (v > m_388)
			m_388 = v;
	}
}
