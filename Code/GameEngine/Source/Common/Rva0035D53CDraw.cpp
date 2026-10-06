// cl: /MD
// ?draw@Rva0035D53C@@UAEXXZ @0x0035D62E 138B: vslot draw slot 4 offset 0x10 of vtable 0x00816510 (class of ??1Rva0035D53C) and 0x008165D0. Evidence: same vtable as landed init 0x0035D54B slot 1 plus rowed W3DDisplay draw 0x0004D6B3 plus TheDisplay 0x00DFE9D8 plus image win+0x48 plus drawState 1..5 plus center 0x24/0x28 plus inc 0x2C/0x30.

typedef int Int;
typedef unsigned char Bool;

struct ICoord2D
{
	Int x;
	Int y;
};

class Image;
class Display;
extern Display *TheDisplay;

class W3DDisplay
{
public:
	void rva0004D6B3(Image *image, float x0, float y0, float x1, float y1, int color, int mode);
};

class GameWindow;

struct WindowImages
{
	unsigned char m_pad[0x48];
	const Image *m_enabledImage;
};

class Rva001DBAA4
{
public:
	virtual ~Rva001DBAA4();
	Rva001DBAA4();
	Int m_4;
	Bool m_8;
	Bool m_9;
	Bool m_A;
	char m_padB;
	GameWindow *m_win;
};

class Rva0035D53C : public Rva001DBAA4
{
public:
	virtual void init(GameWindow *win);
	virtual void update(Int frame);
	virtual void slot3();
	virtual void draw();
	ICoord2D m_pos;
	ICoord2D m_size;
	Int m_20;
	Int m_24;
	Int m_28;
	Int m_2C;
	Int m_30;
};

void Rva0035D53C::draw()
{
	if (!m_win)
		return;
	const Image *image = ((const WindowImages *)m_win)->m_enabledImage;
	if (m_20 <= 0 || m_20 >= 6)
		return;
	Int x = m_24 - ((m_2C * m_20) / 2);
	Int y = m_28 - ((m_30 * m_20) / 2);
	Int x1 = x + m_2C * m_20;
	Int y1 = y + m_30 * m_20;
	((W3DDisplay *)TheDisplay)->rva0004D6B3((Image *)image, (float)x, (float)y, (float)x1, (float)y1, -1, 2);
}
