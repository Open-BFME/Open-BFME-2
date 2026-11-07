// cl: /Ireference/shims/bfme2gwm /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// BFME ABI reconstruction of the image-backed tab-control draw callback at
// retail RVA 0x00797EF0.  The tab-data offsets and the callback dispatch are
// the BFME layouts; no generated body is included here.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char Bool;
typedef float Real;
typedef int Color;

class Image;
class GameWindow;
class WinInstanceData;

#include "../../../../../../Libraries/Include/Lib/ICoord2D.h"

struct BfmeWinDrawData
{
	const Image *image;
	Color color;
	Color borderColor;
};

class GameWindow
{
public:
	Int winGetScreenPosition( Int *x, Int *y );
	Int winGetSize( Int *width, Int *height );
	UnsignedInt winGetStatus( void );
	void winDrawBorder( void );
	void *winGetUserData( void );
	// BFME2 keeps the default-draw dispatch BFME1 inlined out of line: 0x0009DC32
	// (five callers) tries 0x0009DC05, else draws through the sub-object at +0x218.
	Int rva0009DC32( WinInstanceData *instData );

	const Image *winGetEnabledImage( Int index )
	{
		return m_enabledDrawData[ index ].image;
	}
	const Image *winGetDisabledImage( Int index )
	{
		return m_disabledDrawData[ index ].image;
	}
	const Image *winGetHiliteImage( Int index )
	{
		return m_hiliteDrawData[ index ].image;
	}

private:
	unsigned char m_unreconstructed_00[ 0x48 ];
	BfmeWinDrawData m_enabledDrawData[ 9 ];
	BfmeWinDrawData m_disabledDrawData[ 9 ];
	BfmeWinDrawData m_hiliteDrawData[ 9 ];
};

typedef void (__cdecl *BfmeGameWinDrawFunc)( GameWindow *, WinInstanceData * );

#include "../../../../../../GameEngine/Include/GameClient/GameWindowManager.h"

extern GameWindowManager *TheWindowManager;

struct TabControlData
{
	Int tabOrientation;
	Int tabEdge;
	Int tabWidth;
	Int tabHeight;
	Int tabCount;
	GameWindow *subPanes[ 8 ];
	Bool subPaneDisabled[ 8 ];
	Int paneBorder;
	Int activeTab;
	Int tabsLeftLimit;
	Int tabsRightLimit;
	Int tabsTopLimit;
	Int tabsBottomLimit;
};

enum
{
	TP_TOP_SIDE = 3,
	TP_BOTTOM_SIDE = 6,
	WIN_STATUS_BORDER = 0x00001000,
	WIN_STATUS_SEE_THRU = 0x00010000
};

#define BFME_DRAW_TAB_IMAGE( NUMBER, INDEX ) \
	if( tabData->tabCount >= NUMBER ) \
	{ \
		if( tabData->subPaneDisabled[ INDEX ] ) \
			image = tabControl->winGetDisabledImage( INDEX + 1 ); \
		else if( tabData->activeTab == INDEX ) \
			image = tabControl->winGetHiliteImage( INDEX + 1 ); \
		else \
			image = tabControl->winGetEnabledImage( INDEX + 1 ); \
		if( image != 0 ) \
			TheWindowManager->winDrawImage( image, tabX, tabY, \
				tabX + tabWidth, tabY + tabHeight, -1 ); \
	} \
	tabX += tabDeltaX; \
	tabY += tabDeltaY;

void W3DGadgetTabControlImageDraw( GameWindow *tabControl,
		WinInstanceData *instData )
{
	ICoord2D origin, size;
	tabControl->winGetScreenPosition( &origin.x, &origin.y );
	tabControl->winGetSize( &size.x, &size.y );
	(void)size;

	tabControl->rva0009DC32( instData );
	if( ( tabControl->winGetStatus() & WIN_STATUS_BORDER ) != 0 &&
		( tabControl->winGetStatus() & WIN_STATUS_SEE_THRU ) == 0 )
		tabControl->winDrawBorder();

	TabControlData *tabData = (TabControlData *)tabControl->winGetUserData();
	Int tabX = origin.x + tabData->tabsLeftLimit;
	Int tabY = origin.y + tabData->tabsTopLimit;
	Int tabWidth = tabData->tabWidth;
	Int tabHeight = tabData->tabHeight;
	Int tabDeltaX;
	Int tabDeltaY;
	if( tabData->tabEdge == TP_TOP_SIDE || tabData->tabEdge == TP_BOTTOM_SIDE )
	{
		tabDeltaX = tabWidth;
		tabDeltaY = 0;
	}
	else
	{
		tabDeltaX = 0;
		tabDeltaY = tabHeight;
	}

	const Image *image = 0;
	BFME_DRAW_TAB_IMAGE( 1, 0 )
	BFME_DRAW_TAB_IMAGE( 2, 1 )
	BFME_DRAW_TAB_IMAGE( 3, 2 )
	BFME_DRAW_TAB_IMAGE( 4, 3 )
	BFME_DRAW_TAB_IMAGE( 5, 4 )
	BFME_DRAW_TAB_IMAGE( 6, 5 )
	BFME_DRAW_TAB_IMAGE( 7, 6 )
	BFME_DRAW_TAB_IMAGE( 8, 7 )
}

// Clean BF1 9cbfb551fe20dae985f91f2319d8997287b6a705
// GameEngineDevice/Source/W3DDevice/GameClient/GUI/Gadget/W3DTabControl.cpp
// and its GadgetTabControl accessors supply these fixed-index image reads,
// compiled /O1 /arch:SSE /G7. The ZH header's arrays start four bytes too
// early; unadjusted donor names are not target identities. This file's
// already-verified BFME2 GameWindow arrays48/B4/120 use image offset0 in
// each 12-byte draw record. Each independent native leaf loads its stack
// GameWindow argument and the recorded image pointer then returns RET0;
// every start follows a prior RET. The address-owned names preserve the
// unknown original callable identities.
// Native0x0009FCFD..0x0009FD08; offset0xD8: DisabledImage index3.
const Image *getDisabledImage3(GameWindow *window)
{
    return window->winGetDisabledImage(3);
}

// Native0x0009FD3F..0x0009FD4A; offset0x144: HiliteImage index3.
const Image *getHiliteImage3(GameWindow *window)
{
    return window->winGetHiliteImage(3);
}

// Native0x000A0C79..0x000A0C84; offset0x84: EnabledImage index5.
const Image *getEnabledImage5(GameWindow *window)
{
    return window->winGetEnabledImage(5);
}

// Native0x000A0C84..0x000A0C8F; offset0x90: EnabledImage index6.
const Image *getEnabledImage6(GameWindow *window)
{
    return window->winGetEnabledImage(6);
}

// Native0x000A0CA5..0x000A0CB0; offset0xF0: DisabledImage index5.
const Image *getDisabledImage5(GameWindow *window)
{
    return window->winGetDisabledImage(5);
}

// Native0x000A0CB0..0x000A0CBB; offset0xFC: DisabledImage index6.
const Image *getDisabledImage6(GameWindow *window)
{
    return window->winGetDisabledImage(6);
}

// Native0x000A0CD1..0x000A0CDC; offset0x15C: HiliteImage index5.
const Image *getHiliteImage5(GameWindow *window)
{
    return window->winGetHiliteImage(5);
}

// Native0x000A0CDC..0x000A0CE7; offset0x168: HiliteImage index6.
const Image *getHiliteImage6(GameWindow *window)
{
    return window->winGetHiliteImage(6);
}

// Native0x000A3191..0x000A319C; offset0x9C: EnabledImage index7.
const Image *getEnabledImage7(GameWindow *window)
{
    return window->winGetEnabledImage(7);
}

// Native0x000A31B2..0x000A31BD; offset0xA8: EnabledImage index8.
const Image *getEnabledImage8(GameWindow *window)
{
    return window->winGetEnabledImage(8);
}

// Native0x000A322B..0x000A3236; offset0x108: DisabledImage index7.
const Image *getDisabledImage7(GameWindow *window)
{
    return window->winGetDisabledImage(7);
}

// Native0x000A324C..0x000A3257; offset0x114: DisabledImage index8.
const Image *getDisabledImage8(GameWindow *window)
{
    return window->winGetDisabledImage(8);
}

// Native0x000A32C5..0x000A32D0; offset0x174: HiliteImage index7.
const Image *getHiliteImage7(GameWindow *window)
{
    return window->winGetHiliteImage(7);
}

// Native0x000A32E6..0x000A32F1; offset0x180: HiliteImage index8.
const Image *getHiliteImage8(GameWindow *window)
{
    return window->winGetHiliteImage(8);
}

// Native0x000A47C6..0x000A47CE; offset0x6C: EnabledImage index3.
const Image *getEnabledImage3(GameWindow *window)
{
    return window->winGetEnabledImage(3);
}


// Current BF1 9cb clean-source min5 receipts expose these addresses under
// multiple incompatible donor labels. Those labels are not target identities.
// Each native leaf independently reads the window in stack argument4 and
// one raw field, then RET0; every previous boundary is a complete RET/RET4.
// The existing BF2 GameWindow arrays48/B4/120, nine12-byte records and their
// image0/color4/border8 fields independently establish the selected methods.
// Original wrapper names and total argument counts remain unknown. No donor offset is transferred.

// Native0009FCC4..0009FCCC: rawword60; winGetEnabledImage(2).
const Image *getEnabledImage2(GameWindow *window)
{
    return window->winGetEnabledImage(2);
}

// Native0009FCDC..0009FCE7: rawwordB4; winGetDisabledImage(0).
const Image *getDisabledImage0(GameWindow *window)
{
    return window->winGetDisabledImage(0);
}

// Native0009FCE7..0009FCF2: rawwordC0; winGetDisabledImage(1).
const Image *getDisabledImage1(GameWindow *window)
{
    return window->winGetDisabledImage(1);
}

// Native0009FCF2..0009FCFD: rawwordCC; winGetDisabledImage(2).
const Image *getDisabledImage2(GameWindow *window)
{
    return window->winGetDisabledImage(2);
}

// Native0009FD1E..0009FD29: rawword120; winGetHiliteImage(0).
const Image *getHiliteImage0(GameWindow *window)
{
    return window->winGetHiliteImage(0);
}

// Native0009FD29..0009FD34: rawword12C; winGetHiliteImage(1).
const Image *getHiliteImage1(GameWindow *window)
{
    return window->winGetHiliteImage(1);
}

// Native0009FD34..0009FD3F: rawword138; winGetHiliteImage(2).
const Image *getHiliteImage2(GameWindow *window)
{
    return window->winGetHiliteImage(2);
}

// Native000A262E..000A2639: rawwordE4; winGetDisabledImage(4).
const Image *getDisabledImage4(GameWindow *window)
{
    return window->winGetDisabledImage(4);
}

// Native000A264F..000A265A: rawword150; winGetHiliteImage(4).
const Image *getHiliteImage4(GameWindow *window)
{
    return window->winGetHiliteImage(4);
}

// Native000A47BE..000A47C6: rawword54; winGetEnabledImage(1).
const Image *getEnabledImage1(GameWindow *window)
{
    return window->winGetEnabledImage(1);
}

// Native000A47CE..000A47D6: rawword78; winGetEnabledImage(4).
const Image *getEnabledImage4(GameWindow *window)
{
    return window->winGetEnabledImage(4);
}

// Native000A47D6..000A47DE: rawword48; winGetEnabledImage(0).
const Image *getEnabledImage0(GameWindow *window)
{
    return window->winGetEnabledImage(0);
}
