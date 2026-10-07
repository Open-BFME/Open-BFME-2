// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// New draw/helper donor: Open-BFME-1 1399ad37d42ea52a63829e417c46a1ba9ed2cd20,
// game/GameEngine/Source/GameClient/GUI/ButtonFlashTransition_draw.cpp and
// GUI/PushButtonImageDrawThreeRva0059ABC0.cpp; semantic source also ZH
// GameWindowTransitionsStyles.cpp (three-piece enabled button rendering).
// Target evidence: draw owns slot 4 of retail vtable RVA 0x8165F0 and calls
// the three-piece helper at 0x35E6A1. Existing init/update prove the same
// +0x09 direction, +0x0c window, +0x10/+0x14 position, +0x18/+0x1c size,
// +0x20 state and +0x24 gradient layout. Helper calls the named window
// instance-data/screen-position/size bodies and reads enabled images 0/6/5,
// image offsets +0x17c/+0x180 and dimensions +0x24/+0x28.
// Target-specific changes: clipping slots +0xa8/+0xb0; all image calls use
// the already-rowed out-of-line W3DDisplay wrapper (0x4D6B3), draw rectangles
// use existing providers 0x8EEF0/0x4263F. Receiver casts preserve those ABIs;
// they make no further claim about the private W3DDisplay implementation.
// Extents include draw's jump table: helper 733 bytes, draw 909 bytes.
// Empty ICoord2D constructor preserves the donor's non-POD expression shape.
// ?update@ButtonFlashTransition@@UAEXH@Z
// ?update@ButtonFlashTransition@@UAEXH@Z @0x0035E387 564B: vslot update slot 2 offset 0x08 of vtable 0x008165F0.
// Target facts (retail + table, independent): vtable 0x8165F0 dump 34E675 7EE975 87E375 BDD175 05EA75 D03F4B 03E675 = slot0 0x35E634 scalar, slot1 0x35E97E init, slot2 0x35E387 update, slot3 0x35D1BD reverse(9B shared), slot4 0x35EA05 draw (0-gap after init 0x35E97E+135), slot5 0xB3FD0 empty, slot6 0x35E603 skip-forwarder(calls own slot2); 32B .rdata (data_xrefs 0x8165F0 from 0x35E378+0x35E60B vptr stores); retail 564B 0x35E387..0x35E5BB single ret4 at 0x35E5B8; prologue push ebx/esi/edi mov edi,[esp+0x10] mov esi,ecx or [esi+0x20],-1 xor ebx,ebx cmp edi,ebx/0x11 ja tail jmp [edi*4+0x75E5BB]; table at 0x35E5BB 18 entries 0..17 (8/9/10->0x35E5A4 tail cmp 7/0xB mov 0x12); 15 winHide calls all to rowed 0x313C64 (?winHide@GameWindow@@QAEH_N@Z), no Audio/TheAudio, no EH frame; branchless drawState (neg/sbb/and + sete/lea: 1vs7 via and+7, 2vs6 via lea*4+2, 3vs5 via lea+eax+3, 4 unconditional, 5vs3/6vs2 via shared jmp to 0x35E43B/0x35E415, 7vs1 via and6+inc) + shared GRADE tails (push ebx/1 + jmp to common call: 11/16,12/15,13/14,14/13,15/12? actually 15->0xF,16->0x10); layout +0x04 frameLength Int, +0x08 isFinished Bool byte (c6 46 08 01), +0x09 isForward Bool byte (38 5E 09 / 8A 46 09), +0x0A isReversed Bool, +0x0C win, +0x10/0x14 pos, +0x18/0x1C size, +0x20 drawState Int dword (83 4E 20 FF / C7/89), +0x24 gradient; callers: init 0x35E97E calls slot2 update(0), skip 0x35E603 calls own slot2, ctor 0x35E60B vtable+clear 0x24, dtor 0x35E378 clear+0xC+base 0x1DBAC3.
// Donor facts (BFME1 6583b3c1, not reused for audio): GameWindowTransitionsStyles.cpp ButtonFlashTransition::update same switch 0..17 + SHOW_BACKGROUND 18, same winHide patternConstants (1vs7,2vs6,3vs5,4,5vs3,6vs2,7vs1,11vs16,12vs15,13vs14? etc., END finished); donor case1 forward has AudioEventRTS "GUIButtonsFadeIn" + TheAudio->addAudioEvent (EH frame) + commented GUIBlip in GRADE_IN_1; donor // cl: /O2 /MD (draw TU) vs sibling updates /O1 /DNDEBUG /MD; donor layout Transition+pos/size/drawState/gradient matches target offsets.
// Inference (unproven, separate): ButtonFlashTransition identity/slot2 supported by table+init-update(0)+skip-forwarder+ctor/dtor same vtable, but pin_consistency --symbol/--check still required, no symbols.csv change, no new private view (compatible with FamilyTailDtors1DBAC3.cpp ButtonFlashTransition layout 30a9fecd7f, full 7-slot observed vtable, TU-scoped decl only, no canonical header).
// r4 fresh cause (no repeated audio-donor): retail proves no audio/EH, 15 winHide only; prior 637B (72B table +1B) delta starts +0x13 (jump disp shift from 1B) root al-vs-eax at 0x35E3F1 (24 FA byte vs 83 E0 FA dword, 2B vs 3B) for case1 1vs7 (7-6*forward); case7 7vs1 uses dword and6+inc (matches), so width is case-specific, not tree-wide; loop folding (branchless + shared GRADE tails) already exact in prior, preserved.
// r4 trials (4 wrapper slots, run_build_slot.py absent so explain_mismatch wrapper only, no raw compile_source, no commits/push/headers/naked/gen_asm/fallback): slot1 explain prior 637B first-diff +0x13; slot2 re-explain with context (same); slot3 case1 if/else -> ternary (1vs7 constants) still dword AND 637B; slot4 case1 forward 1 -> frame (donor-like frame==1, no audio) still dword AND 637B. No byte gain, same 0.85 bank kept, own Code removed.

typedef int Int;
typedef bool Bool;

#ifndef FALSE
#define FALSE 0
#define TRUE 1
#endif

enum
{
	BUTTONFLASHTRANSITION_START = 0,
	BUTTONFLASHTRANSITION_FADE_IN_1 = 1,
	BUTTONFLASHTRANSITION_FADE_IN_2 = 2,
	BUTTONFLASHTRANSITION_FADE_IN_3 = 3,
	BUTTONFLASHTRANSITION_FADE_TO_BACKGROUND_1 = 4,
	BUTTONFLASHTRANSITION_FADE_TO_BACKGROUND_2 = 5,
	BUTTONFLASHTRANSITION_FADE_TO_BACKGROUND_3 = 6,
	BUTTONFLASHTRANSITION_FADE_TO_BACKGROUND_4 = 7,
	BUTTONFLASHTRANSITION_FADE_TO_GRADE_IN_1 = 11,
	BUTTONFLASHTRANSITION_FADE_TO_GRADE_IN_2 = 12,
	BUTTONFLASHTRANSITION_FADE_TO_GRADE_OUT_1 = 13,
	BUTTONFLASHTRANSITION_FADE_TO_GRADE_OUT_2 = 14,
	BUTTONFLASHTRANSITION_FADE_TO_GRADE_OUT_3 = 15,
	BUTTONFLASHTRANSITION_FADE_TO_GRADE_OUT_4 = 16,
	BUTTONFLASHTRANSITION_END = 17,
	BUTTONFLASHTRANSITION_SHOW_BACKGROUND = 18
};

typedef unsigned char UnsignedByte;
typedef float Real;
typedef int Color;
struct ICoord2D
{
	Int x;
	Int y;
	ICoord2D() {}
};

struct IRegion2D
{
	ICoord2D lo;
	ICoord2D hi;
};

class Image
{
public:
	Int getImageWidth(void) const { return m_imageSize.x; }
	Int getImageHeight(void) const { return m_imageSize.y; }

private:
	unsigned char m_unreconstructed_00[0x24];
	ICoord2D m_imageSize; // retail this+0x24
};

struct WinDrawData
{
	const Image *image;
	unsigned char m_unreconstructed_04[0x8];
};

class WinInstanceData
{
public:
	unsigned char m_unreconstructed_000[0x18];
	WinDrawData m_enabledDrawData[9]; // retail this+0x18
	unsigned char m_unreconstructed_084[0xF8];
	ICoord2D m_imageOffset; // retail this+0x17c
};

class GameWindow
{
public:
	Int winHide(bool);
	WinInstanceData *winGetInstanceData(void);
	Int winGetScreenPosition(Int *x, Int *y);
	Int winGetSize(Int *width, Int *height);

	const Image *winGetEnabledImage(Int index)
	{
		return m_instData.m_enabledDrawData[index].image;
	}

private:
	unsigned char m_unreconstructed_00[0x30];
	WinInstanceData m_instData; // retail this+0x30
};

class W3DDisplay { public: void rva0004D6B3(Image *,float,float,float,float,int,int); void rva0008EEF0(float,float,float,float,float,int); };
class Display { public:
virtual void unused00();
virtual void unused01();
virtual void unused02();
virtual void unused03();
virtual void unused04();
virtual void unused05();
virtual void unused06();
virtual void unused07();
virtual void unused08();
virtual void unused09();
virtual void unused10();
virtual void unused11();
virtual void unused12();
virtual void unused13();
virtual void unused14();
virtual void unused15();
virtual void unused16();
virtual void unused17();
virtual void unused18();
virtual void unused19();
virtual void unused20();
virtual void unused21();
virtual void unused22();
virtual void unused23();
virtual void unused24();
virtual void unused25();
virtual void unused26();
virtual void unused27();
virtual void unused28();
virtual void unused29();
virtual void unused30();
virtual void unused31();
virtual void unused32();
virtual void unused33();
virtual void unused34();
virtual void unused35();
virtual void unused36();
virtual void unused37();
virtual void unused38();
virtual void unused39();
virtual void unused40();
virtual void unused41();
virtual void setClipRegion(IRegion2D *);
virtual void unused43();
virtual void enableClipping(Bool);
};

extern Display *TheDisplay;

inline const Image *GadgetButtonGetLeftEnabledImage(GameWindow *window)
{
	return window->winGetEnabledImage(0);
}

inline const Image *GadgetButtonGetMiddleEnabledImage(GameWindow *window)
{
	return window->winGetEnabledImage(5);
}

inline const Image *GadgetButtonGetRightEnabledImage(GameWindow *window)
{
	return window->winGetEnabledImage(6);
}

inline Color GameMakeColor(unsigned char red, unsigned char green,
	unsigned char blue, unsigned char alpha)
{
	return (alpha << 24) | (red << 16) | (green << 8) | (blue);
}

class ButtonFlashTransition
{
public:
	virtual ~ButtonFlashTransition();
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
	Int m_posX;			// +0x10
	Int m_posY;			// +0x14
	Int m_sizeX;			// +0x18
	Int m_sizeY;			// +0x1c
	Int m_drawState;		// +0x20
	const Image *m_gradient;	// +0x24
};

void ButtonFlashTransition::update(Int frame)
{
	m_drawState = -1;
	if (frame < BUTTONFLASHTRANSITION_START || frame > BUTTONFLASHTRANSITION_END)
	{
		return;
	}
	switch (frame) {
	case BUTTONFLASHTRANSITION_START:
		{
			if (m_isForward || !m_win)
				break;
			m_win->winHide(TRUE);
			m_isFinished = TRUE;
		}
		break;
	case BUTTONFLASHTRANSITION_FADE_IN_1:
		{
			if (!m_win)
				break;
			m_win->winHide(TRUE);
			if (m_isForward)
				m_drawState = BUTTONFLASHTRANSITION_FADE_IN_1;
			else
				m_drawState = BUTTONFLASHTRANSITION_FADE_TO_BACKGROUND_4;
		}
		break;
	case BUTTONFLASHTRANSITION_FADE_IN_2:
		{
			if (!m_win)
				break;
			m_win->winHide(TRUE);
			if (m_isForward)
				m_drawState = frame;
			else
				m_drawState = BUTTONFLASHTRANSITION_FADE_TO_BACKGROUND_3;
		}
		break;
	case BUTTONFLASHTRANSITION_FADE_IN_3:
		{
			if (!m_win)
				break;
			m_win->winHide(TRUE);
			if (m_isForward)
				m_drawState = frame;
			else
				m_drawState = BUTTONFLASHTRANSITION_FADE_TO_BACKGROUND_2;
		}
		break;
	case BUTTONFLASHTRANSITION_FADE_TO_BACKGROUND_1:
		{
			if (!m_win)
				break;
			m_win->winHide(TRUE);
			if (m_isForward)
				m_drawState = frame;
			else
				m_drawState = BUTTONFLASHTRANSITION_FADE_TO_BACKGROUND_1;
		}
		break;
	case BUTTONFLASHTRANSITION_FADE_TO_BACKGROUND_2:
		{
			if (!m_win)
				break;
			m_win->winHide(TRUE);
			if (m_isForward)
				m_drawState = frame;
			else
				m_drawState = BUTTONFLASHTRANSITION_FADE_IN_3;
		}
		break;
	case BUTTONFLASHTRANSITION_FADE_TO_BACKGROUND_3:
		{
			if (!m_win)
				break;
			m_win->winHide(TRUE);
			if (m_isForward)
				m_drawState = frame;
			else
				m_drawState = BUTTONFLASHTRANSITION_FADE_IN_2;
		}
		break;
	case BUTTONFLASHTRANSITION_FADE_TO_BACKGROUND_4:
		{
			if (!m_win)
				break;
			m_win->winHide(TRUE);
			if (m_isForward)
				m_drawState = frame;
			else
				m_drawState = BUTTONFLASHTRANSITION_FADE_IN_1;
		}
		break;
	case BUTTONFLASHTRANSITION_FADE_TO_GRADE_IN_1:
		{
			if (!m_win)
				break;
			if (m_isForward)
			{
				m_win->winHide(FALSE);
				m_drawState = frame;
			}
			else
			{
				m_win->winHide(TRUE);
				m_drawState = BUTTONFLASHTRANSITION_FADE_TO_GRADE_OUT_4;
			}
		}
		break;
	case BUTTONFLASHTRANSITION_FADE_TO_GRADE_IN_2:
		{
			if (!m_win)
				break;
			if (m_isForward)
			{
				m_win->winHide(FALSE);
				m_drawState = frame;
			}
			else
			{
				m_win->winHide(TRUE);
				m_drawState = BUTTONFLASHTRANSITION_FADE_TO_GRADE_OUT_3;
			}
		}
		break;
	case BUTTONFLASHTRANSITION_FADE_TO_GRADE_OUT_1:
		{
			if (!m_win)
				break;
			if (m_isForward)
			{
				m_win->winHide(FALSE);
				m_drawState = frame;
			}
			else
			{
				m_win->winHide(TRUE);
				m_drawState = BUTTONFLASHTRANSITION_FADE_TO_GRADE_OUT_2;
			}
		}
		break;
	case BUTTONFLASHTRANSITION_FADE_TO_GRADE_OUT_2:
		{
			if (!m_win)
				break;
			if (m_isForward)
			{
				m_win->winHide(FALSE);
				m_drawState = frame;
			}
			else
			{
				m_win->winHide(TRUE);
				m_drawState = BUTTONFLASHTRANSITION_FADE_TO_GRADE_OUT_1;
			}
		}
		break;
	case BUTTONFLASHTRANSITION_FADE_TO_GRADE_OUT_3:
		{
			if (!m_win)
				break;
			if (m_isForward)
			{
				m_win->winHide(FALSE);
				m_drawState = frame;
			}
			else
			{
				m_win->winHide(FALSE);
				m_drawState = BUTTONFLASHTRANSITION_FADE_TO_GRADE_IN_2;
			}
		}
		break;
	case BUTTONFLASHTRANSITION_FADE_TO_GRADE_OUT_4:
		{
			if (!m_win)
				break;
			if (m_isForward)
			{
				m_win->winHide(FALSE);
				m_drawState = frame;
			}
			else
			{
				m_win->winHide(FALSE);
				m_drawState = BUTTONFLASHTRANSITION_FADE_TO_GRADE_IN_1;
			}
		}
		break;
	case BUTTONFLASHTRANSITION_END:
		{
			if (!m_isForward || !m_win)
				break;
			m_win->winHide(FALSE);
			m_isFinished = TRUE;
		}
		break;
	}
	if (frame > BUTTONFLASHTRANSITION_FADE_TO_BACKGROUND_4 && frame < BUTTONFLASHTRANSITION_FADE_TO_GRADE_IN_1)
		m_drawState = BUTTONFLASHTRANSITION_SHOW_BACKGROUND;
}

	void PushButtonImageDrawThree(GameWindow *window, Int alpha)
	{
		WinInstanceData *instData = window->winGetInstanceData();
		const Image *leftImage, *rightImage, *centerImage;
		ICoord2D origin, size, start, end;
		Int xOffset, yOffset;
		Int i;
		Int color = GameMakeColor(255,255,255,alpha);

		window->winGetScreenPosition(&origin.x, &origin.y);
		window->winGetSize(&size.x, &size.y);

		xOffset = instData->m_imageOffset.x;
		yOffset = instData->m_imageOffset.y;

		leftImage = GadgetButtonGetLeftEnabledImage(window);
		rightImage = GadgetButtonGetRightEnabledImage(window);
		centerImage = GadgetButtonGetMiddleEnabledImage(window);

		if (leftImage == 0 || rightImage == 0 || centerImage == 0)
			return;

		ICoord2D leftSize, rightSize;
		leftSize.x = leftImage->getImageWidth();
		leftSize.y = leftImage->getImageHeight();
		rightSize.x = rightImage->getImageWidth();
		rightSize.y = rightImage->getImageHeight();

		ICoord2D leftEnd, rightStart;
		leftEnd.x = origin.x + leftSize.x + xOffset;
		leftEnd.y = origin.y + size.y + yOffset;
		rightStart.x = origin.x + size.x - rightSize.x + xOffset;
		rightStart.y = origin.y + yOffset;

		Int centerWidth, pieces;
		centerWidth = rightStart.x - leftEnd.x;

		if (centerWidth <= 0)
		{
			start.x = origin.x + xOffset;
			start.y = origin.y + yOffset;
			end.y = leftEnd.y;
			end.x = origin.x + xOffset + size.x / 2;
			reinterpret_cast<W3DDisplay *>(TheDisplay)->rva0004D6B3((Image *)leftImage, start.x, start.y, end.x, end.y, color, 2);

			start.y = rightStart.y;
			start.x = end.x;
			end.x = origin.x + size.x;
			end.y = start.y + size.y;
			reinterpret_cast<W3DDisplay *>(TheDisplay)->rva0004D6B3((Image *)rightImage, start.x, start.y, end.x, end.y, color, 2);
		}
		else
		{
			pieces = centerWidth / centerImage->getImageWidth();

			start.x = leftEnd.x;
			start.y = origin.y + yOffset;
			end.y = start.y + size.y + yOffset;
			for (i = 0; i < pieces; i++)
			{
				end.x = start.x + centerImage->getImageWidth();
				reinterpret_cast<W3DDisplay *>(TheDisplay)->rva0004D6B3((Image *)centerImage, start.x, start.y,
					end.x, end.y, color, 2);
				start.x += centerImage->getImageWidth();
			}

			IRegion2D reg;
			reg.lo.x = start.x;
			reg.lo.y = start.y;
			reg.hi.x = rightStart.x;
			reg.hi.y = end.y;
			centerWidth = rightStart.x - start.x;
			if (centerWidth > 0)
			{
				TheDisplay->setClipRegion(&reg);
				end.x = start.x + centerImage->getImageWidth();
				reinterpret_cast<W3DDisplay *>(TheDisplay)->rva0004D6B3((Image *)centerImage, start.x, start.y,
					end.x, end.y, color, 2);
				TheDisplay->enableClipping(FALSE);
			}

			start.x = origin.x + xOffset;
			start.y = origin.y + yOffset;
			end = leftEnd;
			reinterpret_cast<W3DDisplay *>(TheDisplay)->rva0004D6B3((Image *)leftImage, start.x, start.y, end.x, end.y,
				color, 2);

			start = rightStart;
			end.x = start.x + rightSize.x;
			end.y = start.y + size.y;
			reinterpret_cast<W3DDisplay *>(TheDisplay)->rva0004D6B3((Image *)rightImage, start.x, start.y, end.x, end.y,
				color, 2);
		}
	}

class Rva0004263F { public: void rva0004263F(float,float,float,float,int); };
void ButtonFlashTransition::draw()
{
    switch (m_drawState) {
    case 1:
        reinterpret_cast<W3DDisplay *>(TheDisplay)->rva0008EEF0((float)m_posX, (float)m_posY, (float)m_sizeX, (float)m_sizeY, 1.0f, 0x64ffcb2d);
        reinterpret_cast<Rva0004263F *>(TheDisplay)->rva0004263F((float)m_posX, (float)m_posY, (float)m_sizeX, (float)m_sizeY, 0x4bffcb2d);
        break;
    case 2:
        reinterpret_cast<W3DDisplay *>(TheDisplay)->rva0008EEF0((float)m_posX, (float)m_posY, (float)m_sizeX, (float)m_sizeY, 1.0f, 0x96ffcb2d);
        reinterpret_cast<Rva0004263F *>(TheDisplay)->rva0004263F((float)m_posX, (float)m_posY, (float)m_sizeX, (float)m_sizeY, 0x96ffcb2d);
        break;
    case 3:
        reinterpret_cast<W3DDisplay *>(TheDisplay)->rva0008EEF0((float)m_posX, (float)m_posY, (float)m_sizeX, (float)m_sizeY, 1.0f, 0xc8ffcb2d);
        reinterpret_cast<Rva0004263F *>(TheDisplay)->rva0004263F((float)m_posX, (float)m_posY, (float)m_sizeX, (float)m_sizeY, 0xc8ffcb2d);
        break;
    case 4:
        PushButtonImageDrawThree(m_win, 255);
        reinterpret_cast<W3DDisplay *>(TheDisplay)->rva0008EEF0((float)m_posX, (float)m_posY, (float)m_sizeX, (float)m_sizeY, 1.0f, 0xfaffcb2d);
        reinterpret_cast<Rva0004263F *>(TheDisplay)->rva0004263F((float)m_posX, (float)m_posY, (float)m_sizeX, (float)m_sizeY, 0x96ffcb2d);
        break;
    case 5:
        PushButtonImageDrawThree(m_win, 255);
        reinterpret_cast<W3DDisplay *>(TheDisplay)->rva0008EEF0((float)m_posX, (float)m_posY, (float)m_sizeX, (float)m_sizeY, 1.0f, 0xfaffcb2d);
        reinterpret_cast<Rva0004263F *>(TheDisplay)->rva0004263F((float)m_posX, (float)m_posY, (float)m_sizeX, (float)m_sizeY, 0x64ffcb2d);
        break;
    case 6:
        PushButtonImageDrawThree(m_win, 255);
        reinterpret_cast<W3DDisplay *>(TheDisplay)->rva0008EEF0((float)m_posX, (float)m_posY, (float)m_sizeX, (float)m_sizeY, 1.0f, 0xfaffcb2d);
        reinterpret_cast<Rva0004263F *>(TheDisplay)->rva0004263F((float)m_posX, (float)m_posY, (float)m_sizeX, (float)m_sizeY, 0x32ffcb2d);
        break;
    case 7:
        PushButtonImageDrawThree(m_win, 255);
        reinterpret_cast<W3DDisplay *>(TheDisplay)->rva0008EEF0((float)m_posX, (float)m_posY, (float)m_sizeX, (float)m_sizeY, 1.0f, 0xfaffcb2d);
        reinterpret_cast<Rva0004263F *>(TheDisplay)->rva0004263F((float)m_posX, (float)m_posY, (float)m_sizeX, (float)m_sizeY, 0x0fffcb2d);
        break;
    case 11:
        if (m_isForward) PushButtonImageDrawThree(m_win, 255);
        reinterpret_cast<W3DDisplay *>(TheDisplay)->rva0004D6B3((Image *)m_gradient, (float)m_posX, (float)m_posY,
                              (float)(m_posX + m_sizeX), (float)(m_posY + m_sizeY), 0x64ffffff, 2);
        break;
    case 12:
        reinterpret_cast<W3DDisplay *>(TheDisplay)->rva0004D6B3((Image *)m_gradient, (float)m_posX, (float)m_posY,
                              (float)(m_posX + m_sizeX), (float)(m_posY + m_sizeY), 0xc8ffffff, 2);
        break;
    case 13:
        if (!m_isForward) PushButtonImageDrawThree(m_win, 255);
        reinterpret_cast<W3DDisplay *>(TheDisplay)->rva0004D6B3((Image *)m_gradient, (float)m_posX, (float)m_posY,
                              (float)(m_posX + m_sizeX), (float)(m_posY + m_sizeY), 0x96ffffff, 2);
        break;
    case 14:
        if (!m_isForward) PushButtonImageDrawThree(m_win, 255);
        reinterpret_cast<W3DDisplay *>(TheDisplay)->rva0004D6B3((Image *)m_gradient, (float)m_posX, (float)m_posY,
                              (float)(m_posX + m_sizeX), (float)(m_posY + m_sizeY), 0x64ffffff, 2);
        break;
    case 15:
        if (!m_isForward) PushButtonImageDrawThree(m_win, 255);
        reinterpret_cast<W3DDisplay *>(TheDisplay)->rva0004D6B3((Image *)m_gradient, (float)m_posX, (float)m_posY,
                              (float)(m_posX + m_sizeX), (float)(m_posY + m_sizeY), 0x32ffffff, 2);
        break;
    case 16:
        if (!m_isForward) PushButtonImageDrawThree(m_win, 255);
        reinterpret_cast<W3DDisplay *>(TheDisplay)->rva0004D6B3((Image *)m_gradient, (float)m_posX, (float)m_posY,
                              (float)(m_posX + m_sizeX), (float)(m_posY + m_sizeY), 0x11ffffff, 2);
        break;
    case 18:
        PushButtonImageDrawThree(m_win, 255);
        break;
    }
}
