// cl: /DNDEBUG /MD
// ?init@TextOnFrameTransition@@UAEXPAVGameWindow@@@Z
// retail 0x0035FA90, 62 bytes. Dedicated TU.
//
// Ported from Open-BFME-1
// Code/GameEngine/Source/GameClient/GUI/GameWindowTransitionsStyles.cpp
// (matched there): cache the window, finish immediately when it is already
// hidden, else restart forward from frame zero. Retail adaptations, all
// measured from the target bytes: winIsHidden stays out-of-line
// (declared-only here, pinned to its matched row); update is virtual at
// slot 8; Bool is bool so the pin mangling (QAE_NXZ) resolves.

typedef int Int;
typedef bool Bool;

#ifndef NULL
#define NULL 0
#endif

#ifndef FALSE
#define FALSE 0
#define TRUE 1
#endif

class GameWindow
{
public:
	Bool winIsHidden(void);
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
	Int m_unknown10;		// +0x10, passed to update by retail init
};

enum
{
	TEXTONFRAMETRANSITION_START = 0
};

// ?init@TextOnFrameTransition@@UAEXPAVGameWindow@@@Z
void TextOnFrameTransition::init(GameWindow *win)
{

	if (win)
	{
		m_win = win;
	}
	if (m_win->winIsHidden())
	{
		m_isFinished = TRUE;
		m_isForward = TRUE;
		m_frameLength = 0;
	}
	else
	{
		m_isForward = FALSE;
		update(m_unknown10);
		m_isFinished = FALSE;
		m_isForward = TRUE;
	}
}
