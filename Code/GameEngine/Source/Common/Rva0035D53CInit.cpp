// cl: /MD
// ?init@Rva0035D53C@@UAEXPAVGameWindow@@@Z @0x0035D54B 121B: vslot init slot 1 offset 0x4 of vtable 0x00816510 (class of ??1Rva0035D53C) and 0x008165D0. Evidence: same vtable slot as rowed init pattern plus rowed winGetSize 0x00313BC6 plus rowed winGetScreenPosition 0x00313B3C plus virtual update slot 2 plus size/2 center plus size/6.

typedef int Int;
typedef unsigned char Bool;

struct ICoord2D
{
	Int x;
	Int y;
};

class GameWindow
{
public:
	Int winGetSize(Int *width, Int *height);
	Int winGetScreenPosition(Int *x, Int *y);
};

class Rva001DBAA4
{
public:
	virtual ~Rva001DBAA4();
	Rva001DBAA4();
	Int m_4;		// +0x04
	Bool m_8;		// +0x08
	Bool m_9;		// +0x09
	Bool m_A;		// +0x0A
	char m_padB;
	GameWindow *m_win;	// +0x0C
};

class Rva0035D53C : public Rva001DBAA4
{
public:
	virtual void init(GameWindow *win);
	virtual void update(Int frame);
	ICoord2D m_pos;		// +0x10
	ICoord2D m_size;	// +0x18
	Int m_20;		// +0x20
	Int m_24;		// +0x24
	Int m_28;		// +0x28
	Int m_2C;		// +0x2C
	Int m_30;		// +0x30
};

void Rva0035D53C::init(GameWindow *win)
{
	if (win) {
		m_win = win;
		m_win->winGetSize(&m_size.x, &m_size.y);
		m_win->winGetScreenPosition(&m_pos.x, &m_pos.y);
	}
	m_9 = 0;
	update(0);
	m_8 = 0;
	m_24 = m_pos.x + m_size.x / 2;
	m_28 = m_pos.y + m_size.y / 2;
	m_2C = m_size.x / 6;
	m_9 = 1;
	m_30 = m_size.y / 6;
}
