// cl: /O1 /DNDEBUG /MD /arch:SSE
// ?init@FullFadeTransition@@UAEXPAVGameWindow@@@Z
// retail 0x0035F1DF, 98 bytes. Virtual slot 1 (offset 0x4) of vtable 0x0081663C,
// the class of ??1Rva0035F1D0@@UAE@XZ (dtor clears +0xC then tail-calls base
// 0x001DBAC3).
// Ported from Open-BFME-1 Code/GameEngine/Source/GameClient/GUI/GameWindowTransitionsStyles.cpp
// FullFadeTransition::init: cache size/position when win is present, run one
// update step from m_startFrame (+0x10), then m_percent (+0x28) is 1.0f over
// (m_endFrame (+0x14) / 2). winGetSize/winGetScreenPosition stay out-of-line
// (declared-only, rowed at 0x00313BC6/0x00313B3C); update is virtual at slot 8.

typedef int Int;
typedef bool Bool;

#ifndef FALSE
#define FALSE 0
#define TRUE 1
#endif

struct ICoord2D
{
	Int x;
	Int y;
};

typedef float Real;

class GameWindow
{
public:
	Int winGetSize(Int *width, Int *height);
	Int winGetScreenPosition(Int *x, Int *y);
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
	ICoord2D m_pos;			// +0x18
	ICoord2D m_size;		// +0x20
	Real m_percent;			// +0x28
	Int m_drawState;		// +0x2c
};

void FullFadeTransition::init(GameWindow *win)
{
	if (win)
	{
		m_win = win;
		m_win->winGetSize(&m_size.x, &m_size.y);
		m_win->winGetScreenPosition(&m_pos.x, &m_pos.y);
	}
	m_isForward = FALSE;
	update(m_startFrame);
	m_isFinished = FALSE;
	m_isForward = TRUE;
	m_percent = 1.0f / (m_endFrame / 2);
}
