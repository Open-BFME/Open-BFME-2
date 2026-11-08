// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// GameWindow::winGetStatus (retail 0x0030F45F, 4 bytes) and
// GameWindow::winSetUserData (retail 0x002B2210, 10 bytes): Zero Hour
// GameWindow.cpp accessors of m_status (+0x08, the offset GameWindowHide.cpp's
// rowed winSetStatus/winHide use) and m_userData (+0x2C, the offset the rowed
// winGetUserData reads). The GUI units that call them pin both names at these
// addresses. Retail folded each with an identical one-instruction accessor:
// winGetStatus lands as the ICF alias of the rowed
// CategoryModuleClass<1>::getName; winSetUserData replaces a gen-alias
// placeholder (Matrix3D::Set_Z_Translation's identical bytes).

typedef unsigned int UnsignedInt;
typedef int Int;
typedef int Color;
class GameFont;

#include "../../../Include/GameClient/Bfme2GameWindow.h"


UnsignedInt GameWindow::winGetStatus(void)
{
	return m_status;
}

void GameWindow::winSetUserData(void *data)
{
	m_userData = data;
}

// winGetStyle (0x005C4AF1, +0x3C), winGetParent (0x003140A4, +0x200) and
// winGetChild (0x003140C8, +0x204): pinned at those addresses by the GUI
// callers; m_parent and m_child are adjacent as in Zero Hour's GameWindow.h.
// Each is folded with an identical one-load getter already rowed there.
UnsignedInt GameWindow::winGetStyle(void)
{
	return m_instData.m_style;
}

GameWindow *GameWindow::winGetParent(void)
{
	return m_parent;
}

// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline GameWindow *GameWindow::winGetChild(void)
{
	return m_child;
}

// ?bfmeAnchorGameWindowWinGetChild absent-from-retail
GameWindow *bfmeAnchorGameWindowWinGetChild(GameWindow *gameWindow)
{
	return gameWindow->winGetChild();
}


// The window id (+0x34), the six text colours (+0x18C..+0x1A0) and the font
// (+0x1B4): each pinned by its GUI callers at a one-load getter that retail
// folded with an identical one already rowed.
Int GameWindow::winGetWindowId(void) { return m_instData.m_id; }
Color GameWindow::winGetEnabledTextColor(void) { return m_instData.m_enabledColor; }
Color GameWindow::winGetEnabledTextBorderColor(void) { return m_instData.m_enabledBorderColor; }
Color GameWindow::winGetDisabledTextColor(void) { return m_instData.m_disabledColor; }
Color GameWindow::winGetDisabledTextBorderColor(void) { return m_instData.m_disabledBorderColor; }
Color GameWindow::winGetHiliteTextColor(void) { return m_instData.m_hiliteColor; }
Color GameWindow::winGetHiliteTextBorderColor(void) { return m_instData.m_hiliteBorderColor; }
// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline GameFont *GameWindow::winGetFont(void) { return m_instData.m_font; }

// ?bfmeAnchorGameWindowWinGetFont absent-from-retail
GameFont *bfmeAnchorGameWindowWinGetFont(GameWindow *gameWindow)
{
	return gameWindow->winGetFont();
}

// The IME composite text colour and border (+0x1A4, +0x1A8), right after the
// six text colours as Zero Hour's m_imeCompositeText follows the hilite text:
// both text-entry draw callbacks (0x000A03BF, 0x000A0581) call them where
// Zero Hour's do, at one-load getters retail folded with identical rowed ones.
Color GameWindow::winGetIMECompositeTextColor(void) { return m_instData.m_imecompositeColor; }
Color GameWindow::winGetIMECompositeBorderColor(void) { return m_instData.m_imecompositeBorderColor; }

// winGetInstanceData (0x00314046, lea +0x30), winGetNext (0x003140F1,
// +0x1F8, just before m_prev/m_parent/m_child as in Zero Hour) and
// winGetOwner (0x005C4AF9, +0x44): pinned by their callers at one-instruction
// getters retail folded with identical rowed ones.
WinInstanceData *GameWindow::winGetInstanceData(void) { return &m_instData; }
GameWindow *GameWindow::winGetNext(void) { return m_next; }
GameWindow *GameWindow::winGetOwner(void) { return m_instData.m_owner; }

// winGetPrev (0x00314105, +0x1FC, between m_next and m_parent): pinned by
// GadgetTabControlFixupSubPaneList; folded with the identical rowed getter.
GameWindow *GameWindow::winGetPrev(void) { return m_prev; }

// winNextTab and winPrevTab: GadgetStaticTextInput (0x003213F0) calls both
// where its donor does, and both sites land on 0x000D43D0, the shared
// xor eax,eax / ret body. Zero Hour's tab walk is gone from BFME2; both
// return 0.
Int GameWindow::winNextTab(void) { return 0; }
Int GameWindow::winPrevTab(void) { return 0; }

// winGetTextLength (0x00313D64, 8 bytes): Zero Hour's forward to the
// instance data's text length, `add ecx, 0x30` then a jump to the rowed
// WinInstanceData::getTextLength (0x000A3DCC). GadgetListboxCreateScrollbar
// calls it for the listbox title test.
Int GameWindow::winGetTextLength(void)
{
	return m_instData.getTextLength();
}
