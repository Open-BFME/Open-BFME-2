// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?init@CountUpTransition@@UAEXPAVGameWindow@@@Z @0x0035F739 349B: virtual slot 1 of vtable 0x0081667C, CountUpTransition::init. Ported from Open-BFME-1 GameWindowTransitionsStyles.cpp CountUpTransition::init; winGetSize winGetScreenPosition winIsHidden early-out, GetText set, virtual update startFrame, translate atoi countState frameLength MIN, format SetText. Evidence: vslot slot1 plus donor plus rows winGetSize winGetScreenPosition winIsHidden GetText translate atoi plus prev CountUpTransitionDestructorThunk next CountUpTransitionUpdate.
#include "ascii_string.h"
#include "unicode_string.h"

typedef int Int;
typedef bool Bool;

#ifndef FALSE
#define FALSE 0
#define TRUE 1
#endif

#ifndef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

extern const unsigned short g_Va007C9260[];

extern "C" __declspec(dllimport) int __cdecl atoi(const char *str);

class GameWindow
{
public:
	Int winGetSize(Int *x, Int *y);
	Int winGetScreenPosition(Int *x, Int *y);
	Bool winIsHidden(void);
	Int winHide(Bool hide);
};

UnicodeString __cdecl GadgetStaticTextGetText(GameWindow *window);
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
	ICoord2D m_size;		// +0x20
	Int m_drawState;	// +0x28
	UnicodeString m_fullText;	// +0x2c
	UnicodeString m_partialText;	// +0x30
	Int m_intValue;		// +0x34
	Int m_currentValue;	// +0x38
	Int m_countState;	// +0x3c
};

void CountUpTransition::init(GameWindow *win)
{
	if (win)
	{
		m_win = win;
		m_win->winGetSize(&m_size.x, &m_size.y);
		m_win->winGetScreenPosition(&m_pos.x, &m_pos.y);

		if (m_win->winIsHidden())
		{
			m_isForward = TRUE;
			m_isFinished = TRUE;
			m_frameLength = 0;
			return;
		}
	}
	m_fullText = GadgetStaticTextGetText(m_win);
	m_isForward = FALSE;
	update(m_startFrame);
	m_isFinished = FALSE;
	m_isForward = TRUE;

	AsciiString tempStr;
	tempStr.translate(m_fullText);
	m_intValue = atoi(tempStr.str());
	if (m_intValue < m_endFrame)
	{
		m_countState = 1;
		m_frameLength = MIN(m_intValue, m_endFrame);
	}
	else if (m_intValue / 100 < m_endFrame)
	{
		m_countState = 100;
		m_frameLength = MIN(m_intValue / 100, m_endFrame);
	}
	else
	{
		m_countState = 1000;
		m_frameLength = MIN(m_intValue / 1000, m_endFrame);
	}

	m_currentValue = 0;
	UnicodeString currVal;
	currVal.format(g_Va007C9260, m_currentValue);
	GadgetStaticTextSetText(m_win, currVal);
}
