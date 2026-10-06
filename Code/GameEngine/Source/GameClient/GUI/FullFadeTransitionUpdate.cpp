// cl: /DNDEBUG /MD
// ?update@FullFadeTransition@@UAEXH@Z
// retail 0x0035F241, 114 bytes. Virtual slot 2 (offset 0x8) of vtable 0x0081663C,
// the FullFadeTransition class (init 0x0035F1DF just landed from this TU family).
// Ported from Open-BFME-1 Code/GameEngine/Source/GameClient/GUI/GameWindowTransitionsStyles.cpp
// FullFadeTransition::update: range-check frame against m_startFrame (+0x10)
// and m_endFrame (+0x14), hide/unhide at the ends, flip visibility at
// m_endFrame/2, then m_drawState (+0x2c) is frame. winHide stays out-of-line
// (declared-only, rowed at 0x00313C64).

typedef int Int;
typedef bool Bool;

#ifndef FALSE
#define FALSE 0
#define TRUE 1
#endif

typedef unsigned char UnsignedByte;
typedef int Color;

inline Color GameMakeColor(UnsignedByte red, UnsignedByte green, UnsignedByte blue, UnsignedByte alpha)
{
	return (alpha << 24) | (red << 16) | (green << 8) | (blue);
}

class GameWindow
{
public:
	Int winHide(Bool hide);
};

class Display;
extern Display *TheDisplay;

class Rva0004263F
{
public:
	void rva0004263F(float a, float b, float c, float d, int color);
};

class W3DDisplay
{
public:
	void rva0008EEF0(float x0, float y0, float x1, float y1, float w, int color);
};

class FullFadeTransition
{
public:
	virtual ~FullFadeTransition(void);
	virtual void init(GameWindow *win);
	virtual void update(Int frame);
	virtual void reverse(void);
	virtual void draw(void);
	virtual void skip(void);

	Int m_frameLength;		// +0x04
	Bool m_isFinished;		// +0x08
	Bool m_isForward;		// +0x09
	Bool m_isReversed;		// +0x0a
	unsigned char m_pad0B;		// +0x0b
	GameWindow *m_win;		// +0x0c
	Int m_startFrame;		// +0x10
	Int m_endFrame;			// +0x14
	Int m_posX;			// +0x18
	Int m_posY;			// +0x1c
	Int m_sizeX;			// +0x20
	Int m_sizeY;			// +0x24
	float m_percent;		// +0x28
	Int m_drawState;		// +0x2c
};

void FullFadeTransition::update(Int frame)
{
	m_drawState = -1;
	if (frame < m_startFrame || frame > m_endFrame)
	{
		return;
	}
	if (frame == m_startFrame)
	{
		if (!m_isForward && m_win)
		{
			m_win->winHide(TRUE);
			m_isFinished = TRUE;
		}
	}
	else if (frame == m_endFrame)
	{
		if (m_isForward && m_win)
		{
			m_win->winHide(FALSE);
			m_isFinished = TRUE;
		}
	}
	if (frame == m_endFrame / 2)
	{
		if (m_isForward)
			m_win->winHide(FALSE);
		else
			m_win->winHide(TRUE);
	}
	m_drawState = frame;
}

void FullFadeTransition::draw(void)
{
	Int alpha;
	if (m_drawState > m_endFrame / 2)
		alpha = (Int)((float)(m_endFrame - m_drawState) * m_percent * 255.0f);
	else
		alpha = (Int)((float)m_drawState * m_percent * 255.0f);
	if (alpha > 255)
		alpha = 255;
	((Rva0004263F *)TheDisplay)->rva0004263F((float)m_posX, (float)m_posY, (float)m_sizeX, (float)m_sizeY, GameMakeColor(0, 0, 0, (UnsignedByte)alpha));
	((W3DDisplay *)TheDisplay)->rva0008EEF0((float)m_posX, (float)m_posY, (float)m_sizeX, (float)m_sizeY, 1.0f, GameMakeColor(255, 190, 0, (UnsignedByte)alpha));
}
