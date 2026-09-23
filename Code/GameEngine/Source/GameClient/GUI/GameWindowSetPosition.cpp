// cl: /O1 /DNDEBUG /MD
//
// ?winSetPosition@GameWindow@@QAEHHH@Z, retail 0x00313A9E, 70 bytes.
// GameWindow position setter: notifies the child at +0x4 through its third
// virtual (four int args: current m_x/m_y plus the new x/y), then stores the
// new position and orders the rect pairs through orderPairs (rowed at
// 0x31394A, shared-layout helper operating on +0x14/+0x1C/+0x18/+0x20).
//
// Shape: null-guarded virtual call (je skips), base-plus-arg stores for the
// far corners, direct stores for the near corners, then the orderPairs call.
// Zero new pins except the GameWindow-spelled orderPairs alias (same bytes as
// the rowed Rva helper; bodies identical, pins additive). Row supersedes the
// winSetPosition pin.

class GameWindowChild
{
public:
	virtual void childAnchor0();
	virtual void childAnchor1();
	virtual void onChildPosition(int curX, int curY, int newX, int newY);
};

class GameWindow
{
public:
	int winSetPosition(int x, int y);
	void orderPairs();

private:
	unsigned char m_pad[0x4]; // +0..+3
	GameWindowChild *m_child; // +0x4
	unsigned char m_pad08[0x4]; // +0x8..+0xB
	int m_baseX; // +0xC
	int m_baseY; // +0x10
	int m_x; // +0x14
	int m_y; // +0x18
	int m_x2; // +0x1C
	int m_y2; // +0x20
};

// ?winSetPosition@GameWindow@@QAEHHH@Z @0x00313A9E
int GameWindow::winSetPosition(int x, int y)
{
	if (m_child != 0)
		m_child->onChildPosition(m_x, m_y, x, y);
	m_x2 = m_baseX + x;
	m_x = x;
	m_y = y;
	m_y2 = m_baseY + y;
	orderPairs();
	return 0;
}
