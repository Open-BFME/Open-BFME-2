// cl: /O1 /DNDEBUG /MD /arch:SSE
// Init and draw slots of three BFME 2 window transitions that share the rowed
// update 0x0036044A and reverse 0x0035D1BD. Class names are address-derived;
// the slot meanings follow Zero Hour's Transition (init 1, update 2,
// reverse 3, draw 4) and the rowed siblings in the same vtables.
//
// ?draw@Rva0035FF76@@UAEXXZ @ 0x0036012D (152B): vtable 0x0081670C slot 4.
// Alpha min(255, frame(+0x2C) * rate(+0x28) * 255), rectangle copied from
// TheTransitionHandler (0x00DFDC14) +0x54..+0x60 into +0x18..+0x24, then the
// rowed fill wrapper 0x0004263F on TheDisplay with the colour bytes
// +0x3C/+0x3D/+0x3E that init 0x0035FF85 produced.
//
// ?init@Rva003601C5@@UAEXPAVGameWindow@@@Z @ 0x003601DB (104B): vtable
// 0x00816778 slot 1 (its draw is the rowed cross-fade 0x003602EF, which reads
// the images at +0x30/+0x34). Finished at once unless both images are set;
// otherwise the rectangle is the full display (TheDisplay slots +0x40/+0x44).
//
// ?init@Rva00360474@@UAEXPAVGameWindow@@@Z @ 0x003603E7 (99B) and
// ?draw@Rva00360474@@UAEXXZ @ 0x0036051D (127B): vtable 0x00816808 slots 1
// and 4 (ctor 0x00360474 clears the image at +0x30). Single-image variant of
// the cross fade: draw mode 2 through the rowed W3DDisplay wrapper 0x0004D6B3.

typedef int Int;
typedef bool Bool;
typedef float Real;
typedef unsigned char UnsignedByte;
typedef int Color;

#ifndef FALSE
#define FALSE 0
#define TRUE 1
#endif

inline Color GameMakeColor(UnsignedByte red, UnsignedByte green, UnsignedByte blue, UnsignedByte alpha)
{
	return (alpha << 24) | (red << 16) | (green << 8) | (blue);
}

struct ICoord2D
{
	Int x;
	Int y;
};

class GameWindow;
class Image;

class Display
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual Int getWidth();		// +0x40
	virtual Int getHeight();	// +0x44
};
extern Display *TheDisplay;

class Rva0004263F
{
public:
	void rva0004263F(float a, float b, float c, float d, int color);
};

class W3DDisplay
{
public:
	void rva0004D6B3(Image *image, float x0, float y0, float x1, float y1, int color, int mode);
};

class GameWindowTransitionsHandler
{
public:
	char m_pad00[0x54];
	ICoord2D m_screenPos;	// +0x54
	ICoord2D m_screenSize;	// +0x5C
};
extern GameWindowTransitionsHandler *TheTransitionHandler;

class Rva0035FF76
{
public:
	virtual ~Rva0035FF76();
	virtual void init(GameWindow *win);
	virtual void update(Int frame);
	virtual void reverse();
	virtual void draw();

	Int m_frameLength;	// +0x04
	Bool m_isFinished;	// +0x08
	Bool m_isForward;	// +0x09
	Bool m_isReversed;	// +0x0A
	GameWindow *m_win;	// +0x0C
	Int m_startFrame;	// +0x10
	Int m_endFrame;		// +0x14
	ICoord2D m_pos;		// +0x18
	ICoord2D m_size;	// +0x20
	Real m_percent;		// +0x28
	Int m_drawState;	// +0x2C
	Real m_fadeRed;		// +0x30
	Real m_fadeGreen;	// +0x34
	Real m_fadeBlue;	// +0x38
	UnsignedByte m_red;	// +0x3C
	UnsignedByte m_green;	// +0x3D
	UnsignedByte m_blue;	// +0x3E
};

void Rva0035FF76::draw()
{
	Int alpha = (Int)((Real)m_drawState * m_percent * 255.0f);
	if (alpha > 255)
		alpha = 255;
	m_pos = TheTransitionHandler->m_screenPos;
	m_size = TheTransitionHandler->m_screenSize;
	((Rva0004263F *)TheDisplay)->rva0004263F((Real)m_pos.x, (Real)m_pos.y, (Real)m_size.x, (Real)m_size.y,
		GameMakeColor(m_red, m_green, m_blue, (UnsignedByte)alpha));
}

class Rva003601C5
{
public:
	virtual ~Rva003601C5();
	virtual void init(GameWindow *win);
	virtual void update(Int frame);
	virtual void reverse();
	virtual void draw();

	Int m_frameLength;	// +0x04
	Bool m_isFinished;	// +0x08
	Bool m_isForward;	// +0x09
	Bool m_isReversed;	// +0x0A
	GameWindow *m_win;	// +0x0C
	Int m_startFrame;	// +0x10
	Int m_endFrame;		// +0x14
	ICoord2D m_pos;		// +0x18
	ICoord2D m_size;	// +0x20
	Real m_percent;		// +0x28
	Int m_drawState;	// +0x2C
	Image *m_fadeIn;	// +0x30
	Image *m_fadeOut;	// +0x34
};

void Rva003601C5::init(GameWindow *)
{
	m_isForward = FALSE;
	update(m_startFrame);
	m_isFinished = FALSE;
	m_isForward = TRUE;
	m_percent = 1.0f / (m_endFrame - 1);
	if (m_fadeIn && m_fadeOut)
	{
		m_pos.x = m_pos.y = 0;
		m_size.x = TheDisplay->getWidth();
		m_size.y = TheDisplay->getHeight();
	}
	else
	{
		m_isFinished = TRUE;
	}
}

class Rva00360474
{
public:
	virtual ~Rva00360474();
	virtual void init(GameWindow *win);
	virtual void update(Int frame);
	virtual void reverse();
	virtual void draw();

	Int m_frameLength;	// +0x04
	Bool m_isFinished;	// +0x08
	Bool m_isForward;	// +0x09
	Bool m_isReversed;	// +0x0A
	GameWindow *m_win;	// +0x0C
	Int m_startFrame;	// +0x10
	Int m_endFrame;		// +0x14
	ICoord2D m_pos;		// +0x18
	ICoord2D m_size;	// +0x20
	Real m_percent;		// +0x28
	Int m_drawState;	// +0x2C
	Image *m_image;		// +0x30
};

void Rva00360474::init(GameWindow *)
{
	m_isForward = FALSE;
	update(m_startFrame);
	m_isFinished = FALSE;
	m_isForward = TRUE;
	m_percent = 1.0f / (m_endFrame - 1);
	if (!m_image)
	{
		m_isFinished = TRUE;
	}
	else
	{
		m_pos.x = m_pos.y = 0;
		m_size.x = TheDisplay->getWidth();
		m_size.y = TheDisplay->getHeight();
	}
}

void Rva00360474::draw()
{
	if (m_drawState < 0)
		return;
	Int alpha = (Int)((Real)m_drawState * m_percent * 255.0f);
	if (alpha > 255)
		alpha = 255;
	((W3DDisplay *)TheDisplay)->rva0004D6B3(m_image, (Real)m_pos.x, (Real)m_pos.y, (Real)(m_pos.x + m_size.x), (Real)(m_pos.y + m_size.y),
		GameMakeColor(255, 255, 255, (UnsignedByte)alpha), 2);
}
