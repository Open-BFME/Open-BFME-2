// cl: /O1 /DNDEBUG /MD
// ?reverse@TextOnFrameTransition@@UAEXXZ
// retail 0x0035FB18, 33 bytes. Virtual slot 3 (offset 0xC) of vtable 0x0081669C,
// the class of ??1Rva0035FA2A@@UAE@XZ (dtor clears +0xC then tail-calls base
// 0x001DBAC3) beside ?init@TextOnFrameTransition@@UAEXPAVGameWindow@@@Z.
// Ported from Open-BFME-1 Code/GameEngine/Source/GameClient/GUI/GameWindowTransitionsStyles.cpp
// TextOnFrameTransition::reverse: clear finished/forward then finish when the
// cached window is already hidden. winIsHidden stays out-of-line (declared-only,
// rowed at 0x00313CD9).

typedef int Int;
typedef bool Bool;

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
};

void TextOnFrameTransition::reverse(void)
{
	m_isFinished = FALSE;
	m_isForward = FALSE;
	if (m_win->winIsHidden())
	{
		m_isFinished = TRUE;
		m_frameLength = 0;
	}
}
