// cl: /O1 /DNDEBUG /MD /arch:SSE
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

class GameWindow
{
public:
	Int winHide(Bool hide);
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
