// ?update@ButtonFlashTransition@@UAEXH@Z
// partial score=0.85 date=2026-10-05
// ?update@ButtonFlashTransition@@UAEXH@Z
// partial score=0.85 date=2026-10-05 seat-8-r4 (refined, no byte gain)
// cl: /O1 /DNDEBUG /MD
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

class GameWindow
{
public:
	Int winHide(Bool hide);
};

class Image;

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
