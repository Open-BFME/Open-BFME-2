// cl: /DNDEBUG /MD
// Unfilled update/draw slots of the BFME 2 window transitions in the vtable
// run 0x008163D8..0x008166D8, ported from Zero Hour's
// GameWindowTransitionsStyles.cpp where a donor body exists. Slot order is
// Zero Hour's (0 dtor, 1 init, 2 update, 3 reverse, 4 draw); the rowed init,
// update and draw siblings in the same tables pin each class layout.
// Display calls go through the rowed float wrappers on TheDisplay
// (0x00DFE9D8): fill 0x0004263F, open rect 0x0008EEF0, image 0x0004D6B3.
//
// ?update@FlashTransition@@UAEXH@Z @ 0x0035EDE5 (121B) and
// ?draw@FlashTransition@@UAEXXZ @ 0x0035EEF8 (728B): vtable 0x0081661C
// slots 2 and 4 (class of ??1Rva0035ED92). Zero Hour FlashTransition minus
// the frame-1 audio event; the draw keeps the donor's alpha sequence
// (100/33, 150/66, 200/99, 250/75, 250/50, 250/25, 250/10) with BFME's gold
// GameMakeColor(255, 203, 45, a).
//
// ?draw@FadeTransition@@UAEXXZ @ 0x0035F538 (224B incl. jump table): vtable
// 0x0081665C slot 4 beside the rowed FadeTransition::update 0x0035F43D.
//
// ?draw@MainMenuScaleUpTransition@@UAEXXZ @ 0x0035E185 (129B): vtable
// 0x00816594 slot 4 beside the rowed init 0x0035E01E (same layout).
//
// ?update@Rva0035D53C@@UAEXH@Z @ 0x0035D5C4 (106B): vtable 0x00816510 and
// 0x008165D0 slot 2 beside the rowed init 0x0035D54B and draw 0x0035D62E.
// Flash-style frames 0..6 without the background frames; the draw state is
// recorded even with no window.
//
// ?draw@Rva0035D0D1@@UAEXXZ @ 0x0035D2B2 (69B): vtable 0x008163D8 slot 4
// (INI StartFrame/EndFrame/ViewsToFade/LeaveSilent). Unless the transition
// handler's +0x34 count is positive, re-apply each selected channel's focus
// volume (rowed 0x0035D20C) through TheAudio (0x00DFE6E8) slot +0xF0, Zero
// Hour's AudioManager::setVolume(Real, AudioAffect).
//
// ?rva0035F63B@CountUpTransition@@UAEXXZ @ 0x0035F63B (15B): slot 6 of the
// CountUp (0x0081667C) and TextOnFrame (0x0081669C) tables; unless finished,
// run update(m_endFrame). The slot's Zero Hour name is not established.
//
// ?draw@MainMenuMediumScaleUpTransition@@UAEXXZ @ 0x0035DDBD (152B): vtable
// 0x00816574 slot 4 beside the rowed init 0x0035DF18; Zero Hour's body.
//
// ?init@ControlBarArrowTransition@@UAEXPAVGameWindow@@@Z @ 0x0035D83E (230B):
// vtable 0x00816530 slot 1 beside the rowed update/draw; Zero Hour's body.
// The retail rate literals 1/16 and 1/6 fix BEGIN_FADE 16 and END 22.
//
// ?update@Rva0035D0D1@@UAEXH@Z @ 0x0035D14A (115B): slot 2 of the same
// table as the focus-volume draw; the volume (+0x20) runs 1 -> 0 forward
// (computed in double) and snaps at either end.
//
// ?update@Rva0035D352@@UAEXH@Z @ 0x0035D3C7 (119B): vtable 0x00816478 slot
// 2. Outside the end frames the audio is held through TheAudio slot +0x104
// (+0x19 records it); at the end frame it is released through slot +0x108
// with !(+0x18). The audio slot names are not established.

typedef int Int;
typedef bool Bool;
typedef float Real;
typedef unsigned char UnsignedByte;
typedef int Color;

#ifndef NULL
#define NULL 0
#endif

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

class Image
{
public:
	Int getImageWidth() const { return m_imageSize.x; }
	Int getImageHeight() const { return m_imageSize.y; }

	unsigned char m_unreconstructed_00[0x24];
	ICoord2D m_imageSize;	// +0x24
};

class GameWindow
{
public:
	Int winHide(Bool hide);
	Int winGetSize(Int *width, Int *height);
	Int winGetScreenPosition(Int *x, Int *y);
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class GameWindowManager
{
public:
	virtual void pad00(); virtual void pad01(); virtual void pad02(); virtual void pad03();
	virtual void pad04(); virtual void pad05(); virtual void pad06(); virtual void pad07();
	virtual void pad08(); virtual void pad09(); virtual void pad10(); virtual void pad11();
	virtual void pad12(); virtual void pad13(); virtual void pad14(); virtual void pad15();
	virtual void pad16(); virtual void pad17(); virtual void pad18(); virtual void pad19();
	virtual void pad20(); virtual void pad21(); virtual void pad22(); virtual void pad23();
	virtual void pad24(); virtual void pad25(); virtual void pad26(); virtual void pad27();
	virtual void pad28(); virtual void pad29(); virtual void pad30(); virtual void pad31();
	virtual void pad32(); virtual void pad33(); virtual void pad34(); virtual void pad35();
	virtual void pad36(); virtual void pad37(); virtual void pad38(); virtual void pad39();
	virtual void pad40(); virtual void pad41(); virtual void pad42(); virtual void pad43();
	virtual void pad44(); virtual void pad45(); virtual void pad46(); virtual void pad47();
	virtual void pad48(); virtual void pad49(); virtual void pad50(); virtual void pad51();
	virtual void pad52(); virtual void pad53(); virtual void pad54(); virtual void pad55();
	virtual void pad56(); virtual void pad57(); virtual void pad58(); virtual void pad59();
	virtual GameWindow *winGetWindowFromId(GameWindow *window, Int id);	// +0xF0
};
extern GameWindowManager *TheWindowManager;

class ControlBar
{
public:
	const Image *getArrowImage() { return m_arrowImage; }

	unsigned char m_unreconstructed_000[0x26c];
	const Image *m_arrowImage;	// +0x26C
};
extern ControlBar *TheControlBar;

// The window's instance data carries the enabled draw image at +0x48;
// retail reads it inline (winGetEnabledImage(0)).
struct TransitionWindowImages
{
	unsigned char m_unreconstructed_00[0x48];
	const Image *m_enabledImage[1];
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
	void rva0004D6B3(Image *image, float x0, float y0, float x1, float y1, int color, int mode);
	void rva0008EEF0(float x0, float y0, float x1, float y1, float w, int color);
};

static __forceinline void drawFillRect(Int x, Int y, Int width, Int height, Color color)
{
	((Rva0004263F *)TheDisplay)->rva0004263F((Real)x, (Real)y, (Real)width, (Real)height, color);
}

static __forceinline void drawOpenRect(Int x, Int y, Int width, Int height, Real lineWidth, Color color)
{
	((W3DDisplay *)TheDisplay)->rva0008EEF0((Real)x, (Real)y, (Real)width, (Real)height, lineWidth, color);
}

static __forceinline void drawImage(const Image *image, Int startX, Int startY, Int endX, Int endY, Color color = 0xFFFFFFFF)
{
	((W3DDisplay *)TheDisplay)->rva0004D6B3((Image *)image, (Real)startX, (Real)startY, (Real)endX, (Real)endY, color, 2);
}

class GameWindowTransitionsHandler
{
public:
	char m_pad00[0x34];
	Int m_34;	// +0x34
};
extern GameWindowTransitionsHandler *TheTransitionHandler;

class AudioManager
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
	virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
	virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
	virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();
	virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47();
	virtual void s48(); virtual void s49(); virtual void s50(); virtual void s51();
	virtual void s52(); virtual void s53(); virtual void s54(); virtual void s55();
	virtual void s56(); virtual void s57(); virtual void s58(); virtual void s59();
	virtual void setVolume(Real volume, Int whichToAffect);	// +0xF0
	virtual void s61(); virtual void s62(); virtual void s63(); virtual void s64();
	virtual void vslot104();		// +0x104
	virtual void vslot108(Bool flag);	// +0x108
};
extern AudioManager *TheAudio;

float LookupFocusChannelVolume(int channel);

// Common Transition base: vtable, frame length, flags and window.
class Transition
{
public:
	virtual ~Transition();
	virtual void init(GameWindow *win);
	virtual void update(Int frame);
	virtual void reverse();
	virtual void draw();

	Int m_frameLength;	// +0x04
	Bool m_isFinished;	// +0x08
	Bool m_isForward;	// +0x09
	Bool m_isReversed;	// +0x0A
	GameWindow *m_win;	// +0x0C
};

//-----------------------------------------------------------------------------

enum
{
	FLASHTRANSITION_START = 0,
	FLASHTRANSITION_FADE_IN_1 = 1,
	FLASHTRANSITION_FADE_IN_2 = 2,
	FLASHTRANSITION_FADE_IN_3 = 3,
	FLASHTRANSITION_FADE_TO_BACKGROUND_1 = 4,
	FLASHTRANSITION_FADE_TO_BACKGROUND_2 = 5,
	FLASHTRANSITION_FADE_TO_BACKGROUND_3 = 6,
	FLASHTRANSITION_FADE_TO_BACKGROUND_4 = 7,
	FLASHTRANSITION_END
};

class FlashTransition : public Transition
{
public:
	virtual void update(Int frame);
	virtual void draw();

	ICoord2D m_pos;		// +0x10
	ICoord2D m_size;	// +0x18
	Int m_drawState;	// +0x20
};

void FlashTransition::update(Int frame)
{
	m_drawState = -1;
	if (frame < FLASHTRANSITION_START || frame > FLASHTRANSITION_END)
	{
		return;
	}
	switch (frame) {
	case FLASHTRANSITION_START:
		{
			if (m_isForward || !m_win)
				break;
			m_win->winHide(TRUE);
			m_isFinished = TRUE;
		}
		break;
	case FLASHTRANSITION_FADE_IN_1:
		// The donor plays GUIBoarderFadeIn here; retail keeps the separate
		// case 1 arm with no event left in it.
		if (m_isForward)
		{
		}
	case FLASHTRANSITION_FADE_IN_2:
	case FLASHTRANSITION_FADE_IN_3:
		{
			if (!m_win)
				break;
			m_win->winHide(TRUE);
			m_drawState = frame;
		}
		break;
	case FLASHTRANSITION_FADE_TO_BACKGROUND_1:
	case FLASHTRANSITION_FADE_TO_BACKGROUND_2:
	case FLASHTRANSITION_FADE_TO_BACKGROUND_3:
	case FLASHTRANSITION_FADE_TO_BACKGROUND_4:
		{
			if (!m_win)
				break;
			m_win->winHide(FALSE);
			m_drawState = frame;
		}
		break;
	case FLASHTRANSITION_END:
		{
			if (!m_isForward || !m_win)
				break;
			m_win->winHide(FALSE);
			m_isFinished = TRUE;
		}
		break;
	}
}

void FlashTransition::draw()
{
	switch (m_drawState)
	{
		case FLASHTRANSITION_FADE_IN_1:
		{
			drawOpenRect(m_pos.x + 1, m_pos.y + 1, m_size.x - 2, m_size.y, 1, GameMakeColor(255, 203, 45, 100));
			drawFillRect(m_pos.x + 1, m_pos.y + 1, m_size.x - 2, m_size.y, GameMakeColor(255, 203, 45, 33));
		}
		break;
		case FLASHTRANSITION_FADE_IN_2:
		{
			drawOpenRect(m_pos.x + 1, m_pos.y + 1, m_size.x - 2, m_size.y, 1, GameMakeColor(255, 203, 45, 150));
			drawFillRect(m_pos.x + 1, m_pos.y + 1, m_size.x - 2, m_size.y, GameMakeColor(255, 203, 45, 66));
		}
		break;
		case FLASHTRANSITION_FADE_IN_3:
		{
			drawOpenRect(m_pos.x + 1, m_pos.y + 1, m_size.x - 2, m_size.y, 1, GameMakeColor(255, 203, 45, 200));
			drawFillRect(m_pos.x + 1, m_pos.y + 1, m_size.x - 2, m_size.y, GameMakeColor(255, 203, 45, 99));
		}
		break;
		case FLASHTRANSITION_FADE_TO_BACKGROUND_1:
		{
			drawOpenRect(m_pos.x + 1, m_pos.y + 1, m_size.x - 2, m_size.y, 1, GameMakeColor(255, 203, 45, 250));
			drawFillRect(m_pos.x + 1, m_pos.y + 1, m_size.x - 2, m_size.y, GameMakeColor(255, 203, 45, 75));
		}
		break;
		case FLASHTRANSITION_FADE_TO_BACKGROUND_2:
		{
			drawOpenRect(m_pos.x + 1, m_pos.y + 1, m_size.x - 2, m_size.y, 1, GameMakeColor(255, 203, 45, 250));
			drawFillRect(m_pos.x + 1, m_pos.y + 1, m_size.x - 2, m_size.y, GameMakeColor(255, 203, 45, 50));
		}
		break;
		case FLASHTRANSITION_FADE_TO_BACKGROUND_3:
		{
			drawOpenRect(m_pos.x + 1, m_pos.y + 1, m_size.x - 2, m_size.y, 1, GameMakeColor(255, 203, 45, 250));
			drawFillRect(m_pos.x + 1, m_pos.y + 1, m_size.x - 2, m_size.y, GameMakeColor(255, 203, 45, 25));
		}
		break;
		case FLASHTRANSITION_FADE_TO_BACKGROUND_4:
		{
			drawOpenRect(m_pos.x + 1, m_pos.y + 1, m_size.x - 2, m_size.y, 1, GameMakeColor(255, 203, 45, 250));
			drawFillRect(m_pos.x + 1, m_pos.y + 1, m_size.x - 2, m_size.y, GameMakeColor(255, 203, 45, 10));
		}
		break;
	}
}

//-----------------------------------------------------------------------------

enum
{
	FADETRANSITION_START = 0,
	FADETRANSITION_FADE_IN_1 = 1,
	FADETRANSITION_FADE_IN_2 = 2,
	FADETRANSITION_FADE_IN_3 = 3,
	FADETRANSITION_FADE_IN_4 = 4,
	FADETRANSITION_FADE_IN_5 = 5,
	FADETRANSITION_FADE_IN_6 = 6,
	FADETRANSITION_FADE_IN_7 = 7,
	FADETRANSITION_FADE_IN_8 = 8,
	FADETRANSITION_FADE_IN_9 = 9,
	FADETRANSITION_END
};

class FadeTransition : public Transition
{
public:
	virtual void draw();

	ICoord2D m_pos;		// +0x10
	ICoord2D m_size;	// +0x18
	Int m_drawState;	// +0x20
};

void FadeTransition::draw()
{
	if (!m_win)
		return;
	const Image *image = ((const TransitionWindowImages *)m_win)->m_enabledImage[0];
	switch (m_drawState)
	{
		case FADETRANSITION_FADE_IN_1:
		{
			drawImage(image, m_pos.x, m_pos.y, m_pos.x + m_size.x, m_pos.y + m_size.y, GameMakeColor(255, 255, 255, 25));
		}
		break;
		case FADETRANSITION_FADE_IN_2:
		{
			drawImage(image, m_pos.x, m_pos.y, m_pos.x + m_size.x, m_pos.y + m_size.y, GameMakeColor(255, 255, 255, 50));
		}
		break;
		case FADETRANSITION_FADE_IN_3:
		{
			drawImage(image, m_pos.x, m_pos.y, m_pos.x + m_size.x, m_pos.y + m_size.y, GameMakeColor(255, 255, 255, 75));
		}
		break;
		case FADETRANSITION_FADE_IN_4:
		{
			drawImage(image, m_pos.x, m_pos.y, m_pos.x + m_size.x, m_pos.y + m_size.y, GameMakeColor(255, 255, 255, 100));
		}
		break;
		case FADETRANSITION_FADE_IN_5:
		{
			drawImage(image, m_pos.x, m_pos.y, m_pos.x + m_size.x, m_pos.y + m_size.y, GameMakeColor(255, 255, 255, 125));
		}
		break;
		case FADETRANSITION_FADE_IN_6:
		{
			drawImage(image, m_pos.x, m_pos.y, m_pos.x + m_size.x, m_pos.y + m_size.y, GameMakeColor(255, 255, 255, 150));
		}
		break;
		case FADETRANSITION_FADE_IN_7:
		{
			drawImage(image, m_pos.x, m_pos.y, m_pos.x + m_size.x, m_pos.y + m_size.y, GameMakeColor(255, 255, 255, 175));
		}
		break;
		case FADETRANSITION_FADE_IN_8:
		{
			drawImage(image, m_pos.x, m_pos.y, m_pos.x + m_size.x, m_pos.y + m_size.y, GameMakeColor(255, 255, 255, 200));
		}
		break;
		case FADETRANSITION_FADE_IN_9:
		{
			drawImage(image, m_pos.x, m_pos.y, m_pos.x + m_size.x, m_pos.y + m_size.y, GameMakeColor(255, 255, 255, 225));
		}
	}
}

//-----------------------------------------------------------------------------

class MainMenuScaleUpTransition : public Transition
{
public:
	virtual void draw();

	Int m_startFrame;		// +0x10
	Int m_endFrame;			// +0x14
	ICoord2D m_pos;			// +0x18
	ICoord2D m_size;		// +0x20
	Int m_drawState;		// +0x28
	ICoord2D m_growPos;		// +0x2c
	ICoord2D m_growSize;		// +0x34
	ICoord2D m_incrementPos;	// +0x3c
	ICoord2D m_incrementSize;	// +0x44
	GameWindow *m_growWin;		// +0x4c
};

void MainMenuScaleUpTransition::draw()
{
	if (!m_win)
		return;
	const Image *image = ((const TransitionWindowImages *)m_growWin)->m_enabledImage[0];
	if (m_drawState <= m_startFrame || m_drawState >= m_endFrame)
		return;
	Int x = m_pos.x + ((m_incrementPos.x * m_drawState));
	Int y = m_pos.y + ((m_incrementPos.y * m_drawState));
	Int x1 = x + m_size.x + ((m_incrementSize.x * m_drawState));
	Int y1 = y + m_size.y + ((m_incrementSize.y * m_drawState));
	drawImage(image, x, y, x1, y1);
}

//-----------------------------------------------------------------------------

class Rva0035D53C : public Transition
{
public:
	virtual void update(Int frame);

	ICoord2D m_pos;		// +0x10
	ICoord2D m_size;	// +0x18
	Int m_drawState;	// +0x20
};

void Rva0035D53C::update(Int frame)
{
	m_drawState = -1;
	if (frame < 0 || frame > 6)
	{
		return;
	}
	switch (frame) {
	case 0:
		{
			if (m_isForward || !m_win)
				break;
			m_win->winHide(TRUE);
			m_isFinished = TRUE;
		}
		break;
	case 1:
		if (m_isForward)
		{
		}
	case 2:
	case 3:
	case 4:
	case 5:
		{
			if (m_win)
				m_win->winHide(TRUE);
			m_drawState = frame;
		}
		break;
	case 6:
		{
			if (!m_isForward || !m_win)
				break;
			m_win->winHide(FALSE);
			m_isFinished = TRUE;
		}
		break;
	}
}

//-----------------------------------------------------------------------------

class Rva0035D0D1 : public Transition
{
public:
	virtual void update(Int frame);
	virtual void draw();

	Int m_startFrame;	// +0x10
	Int m_endFrame;		// +0x14
	Int m_viewsToFade;	// +0x18
	Bool m_leaveSilent;	// +0x1C
	Real m_volume;		// +0x20
};

void Rva0035D0D1::update(Int frame)
{
	if (frame < m_startFrame || frame > m_endFrame)
		return;
	if (m_isForward && (frame == m_endFrame || m_startFrame == m_endFrame))
	{
		m_volume = 0.0f;
		m_isFinished = TRUE;
	}
	else if (!m_isForward && (frame == m_startFrame || m_startFrame == m_endFrame))
	{
		m_isFinished = TRUE;
		m_volume = 1.0f;
	}
	else
	{
		m_volume = 1.0 - (double)(frame - m_startFrame) / (m_endFrame - m_startFrame);
	}
}

void Rva0035D0D1::draw()
{
	if (TheTransitionHandler && TheTransitionHandler->m_34 <= 0)
	{
		for (Int i = 0; i < 3; ++i)
		{
			Int affect = 1 << i;
			if (m_viewsToFade & affect)
			{
				Real volume = LookupFocusChannelVolume(i);
				TheAudio->setVolume(volume, affect);
			}
		}
	}
}

//-----------------------------------------------------------------------------

class CountUpTransition : public Transition
{
public:
	virtual void s5();
	virtual void rva0035F63B();

	Int m_startFrame;	// +0x10
	Int m_endFrame;		// +0x14
};

void CountUpTransition::rva0035F63B()
{
	if (!m_isFinished)
		update(m_endFrame);
}

//-----------------------------------------------------------------------------

class MainMenuMediumScaleUpTransition : public Transition
{
public:
	virtual void draw();

	Int m_startFrame;		// +0x10
	Int m_endFrame;			// +0x14
	ICoord2D m_pos;			// +0x18
	ICoord2D m_size;		// +0x20
	Int m_drawState;		// +0x28
	ICoord2D m_growPos;		// +0x2c
	ICoord2D m_growSize;		// +0x34
	ICoord2D m_incrementSize;	// +0x3c
	GameWindow *m_growWin;		// +0x44
};

void MainMenuMediumScaleUpTransition::draw()
{
	if (!m_win)
		return;
	const Image *image = ((const TransitionWindowImages *)m_win)->m_enabledImage[0];
	if (m_drawState <= m_startFrame || m_drawState >= m_endFrame)
		return;
	Int x = m_pos.x - ((m_incrementSize.x * m_drawState) / 2);
	Int y = m_pos.y - ((m_incrementSize.y * m_drawState) / 2);
	Int x1 = m_pos.x + m_size.x + ((m_incrementSize.x * m_drawState) / 2);
	Int y1 = m_pos.y + m_size.y + ((m_incrementSize.y * m_drawState) / 2);
	drawImage(image, x, y, x1, y1);
}

//-----------------------------------------------------------------------------

enum
{
	CONTROLBARARROWTRANSITION_START = 0,
	CONTROLBARARROWTRANSITION_BEGIN_FADE = 16,
	CONTROLBARARROWTRANSITION_END = 22
};

class ControlBarArrowTransition : public Transition
{
public:
	virtual void init(GameWindow *win);

	ICoord2D m_pos;			// +0x10
	ICoord2D m_incrementPos;	// +0x18
	ICoord2D m_size;		// +0x20
	Real m_percent;			// +0x28
	Real m_fadePercent;		// +0x2C
	Int m_drawState;		// +0x30
	const Image *m_arrowImage;	// +0x34
};

void ControlBarArrowTransition::init(GameWindow *win)
{
	m_isForward = FALSE;
	update(CONTROLBARARROWTRANSITION_START);
	m_isFinished = FALSE;
	m_isForward = TRUE;

	m_percent = 1.0f / CONTROLBARARROWTRANSITION_BEGIN_FADE;
	m_fadePercent = 1.0f / (CONTROLBARARROWTRANSITION_END - CONTROLBARARROWTRANSITION_BEGIN_FADE);

	m_arrowImage = TheControlBar->getArrowImage();
	GameWindow *twin = TheWindowManager->winGetWindowFromId(NULL, TheNameKeyGenerator->nameToKey("ControlBar.wnd:ButtonGeneral"));
	if (!twin || !m_arrowImage)
	{
		m_isFinished = TRUE;
		return;
	}
	ICoord2D screenPos, screenSize;
	twin->winGetScreenPosition(&screenPos.x, &screenPos.y);
	twin->winGetSize(&screenSize.x, &screenSize.y);

	m_incrementPos.x = 0;
	m_incrementPos.y = screenPos.y * m_percent;

	m_pos.y = 0 - m_arrowImage->getImageHeight() + 20;
	m_pos.x = (screenPos.x + screenSize.x / 2) - m_arrowImage->getImageWidth() / 2;

	m_size.x = m_arrowImage->getImageWidth();
	m_size.y = m_arrowImage->getImageHeight();
}

//-----------------------------------------------------------------------------

class Rva0035D352 : public Transition
{
public:
	virtual void update(Int frame);

	Int m_startFrame;	// +0x10
	Int m_endFrame;		// +0x14
	Bool m_keepFrozen;	// +0x18
	Bool m_frozen;		// +0x19
};

void Rva0035D352::update(Int frame)
{
	if (frame < m_startFrame || frame > m_endFrame)
		return;
	if ((m_isForward && (frame == m_endFrame || m_startFrame == m_endFrame)) ||
	    (!m_isForward && (frame == m_startFrame || m_startFrame == m_endFrame)))
	{
		if (m_frozen)
		{
			if (m_keepFrozen)
				TheAudio->vslot108(FALSE);
			else
				TheAudio->vslot108(TRUE);
			m_frozen = FALSE;
		}
		m_isFinished = TRUE;
	}
	else if (!m_frozen)
	{
		TheAudio->vslot104();
		m_frozen = TRUE;
	}
}
