// cl: /O1 /DNDEBUG /MD
// ?update@TextOnFrameTransition@@UAEXH@Z
// retail 0x0035FACE, 74 bytes. Virtual slot 2 (offset 0x8) of vtable 0x0081669C,
// the TextOnFrameTransition class (dtor 0x0035FA2A clears +0xC, init 0x0035FA90,
// reverse 0x0035FB18 just landed from this TU family).
// Ported from Open-BFME-1 Code/GameEngine/Source/GameClient/GUI/GameWindowTransitionsStyles.cpp
// TextOnFrameTransition::update: range-check frame against m_startFrame (+0x10)
// and m_endFrame (+0x14) then hide/unhide the cached window. winHide stays
// out-of-line (declared-only, rowed at 0x00313C64).

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

class TextOnFrameTransition
{
public:
	virtual ~TextOnFrameTransition(void);
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
};

void TextOnFrameTransition::update(Int frame)
{
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
}
