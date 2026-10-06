// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?update@CountUpTransition@@UAEXH@Z @0x0035F896 337B: virtual slot 2 of vtable 0x0081667C, CountUpTransition::update. Ported from Open-BFME-1 GameWindowTransitionsStyles.cpp CountUpTransition::update; range-check start +0x10 end +0x14, start/end hide blocks, frameLength +0x04 hide, counting block with current +0x38 countState +0x3c intValue +0x34 drawState +0x28 format via g_Va007C9260 SetText, final fullText +0x2c SetText. Evidence: vslot slot2 like FullFade/TextOnFrame update rows plus donor plus callers none plus prev/next CountUpTransitionDestructorThunk.
#include "ascii_string.h"
#include "unicode_string.h"

typedef int Int;
typedef bool Bool;

#ifndef FALSE
#define FALSE 0
#define TRUE 1
#endif

extern const unsigned short g_Va007C9260[];

class GameWindow
{
public:
	Int winHide(Bool hide);
};

void __cdecl GadgetStaticTextSetText(GameWindow *win, UnicodeString text);

struct ICoord2D
{
	Int x;
	Int y;
};

class CountUpTransition
{
public:
	virtual ~CountUpTransition(void);
	virtual void init(GameWindow *win);
	virtual void update(Int frame);
	virtual void reverse(void);
	virtual void draw(void);
	virtual void skip(void);

	Int m_frameLength;	// +0x04
	Bool m_isFinished;	// +0x08
	Bool m_isForward;	// +0x09
	Bool m_isReversed;	// +0x0a
	unsigned char m_pad0B;	// +0x0b
	GameWindow *m_win;	// +0x0c
	Int m_startFrame;	// +0x10
	Int m_endFrame;		// +0x14
	ICoord2D m_pos;		// +0x18
	ICoord2D m_size;	// +0x20
	Int m_drawState;	// +0x28
	UnicodeString m_fullText;	// +0x2c
	UnicodeString m_partialText;	// +0x30
	Int m_intValue;		// +0x34
	Int m_currentValue;	// +0x38
	Int m_countState;	// +0x3c
};

void CountUpTransition::update(Int frame)
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
			m_currentValue = 0;
			UnicodeString currVal;
			currVal.format(g_Va007C9260, m_currentValue);
			GadgetStaticTextSetText(m_win, currVal);
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
	if (frame >= m_frameLength)
	{
		m_win->winHide(FALSE);
	}
	if (frame > m_startFrame && frame < m_frameLength)
	{
		m_win->winHide(FALSE);
		m_currentValue += m_countState;
		m_drawState = frame;
		if (m_currentValue > m_intValue)
			m_currentValue = m_intValue;
		UnicodeString currVal;
		currVal.format(g_Va007C9260, m_currentValue);
		GadgetStaticTextSetText(m_win, currVal);
	}
	if (frame == m_frameLength)
	{
		GadgetStaticTextSetText(m_win, m_fullText);
		m_isFinished = TRUE;
	}
}
