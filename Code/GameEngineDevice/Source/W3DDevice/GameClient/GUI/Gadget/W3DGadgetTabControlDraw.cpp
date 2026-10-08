// cl: /Ireference/shims/bfme2gwm /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME: BFME ABI slice for the retail W3DGadgetTabControlDraw body.
//
// The vendored ZH GameWindow header is four bytes short before m_instData.
// This callback therefore uses a TU-local window view whose draw-data arrays
// begin at the BFME offsets (+0x48, +0xB4 and +0x120).  BFME2 calls the
// default-draw dispatch out of line (0x0009DC32) where BFME1 inlined it.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char Bool;
typedef float Real;
typedef int Color;

class Image;
class GameWindow;
class WinInstanceData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord2D
{
	Int x;
	Int y;
};

struct BfmeWinDrawData
{
	const Image *image;
	Color color;
	Color borderColor;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
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

	Color winGetEnabledColor( Int index )
	{
		return m_enabledDrawData[ index ].color;
	}
	Color winGetEnabledBorderColor( Int index )
	{
		return m_enabledDrawData[ index ].borderColor;
	}
	Color winGetDisabledColor( Int index )
	{
		return m_disabledDrawData[ index ].color;
	}
	Color winGetDisabledBorderColor( Int index )
	{
		return m_disabledDrawData[ index ].borderColor;
	}
	Color winGetHiliteColor( Int index )
	{
		return m_hiliteDrawData[ index ].color;
	}
	Color winGetHiliteBorderColor( Int index )
	{
		return m_hiliteDrawData[ index ].borderColor;
	}

private:
	unsigned char m_unreconstructed_00[ 0x48 ];
	BfmeWinDrawData m_enabledDrawData[ 9 ];
	BfmeWinDrawData m_disabledDrawData[ 9 ];
	BfmeWinDrawData m_hiliteDrawData[ 9 ];
};

class BfmeGameWindowDrawSub
{
public:
	virtual void unused( void );
	virtual void draw( GameWindow *window, WinInstanceData *instData );
};

typedef void (__cdecl *BfmeGameWinDrawFunc)( GameWindow *, WinInstanceData * );

class BfmeGameWindowDispatch
{
public:
	unsigned char m_unreconstructed_00[ 0x1e8 ];
	BfmeGameWinDrawFunc m_draw;
	unsigned char m_unreconstructed_1ec[ 0x218 - 0x1ec ];
	BfmeGameWindowDrawSub m_drawSub;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowManager.h
class GameWindowManager
{
public:
	virtual void unused00( void );
	virtual void unused01( void );
	virtual void unused02( void );
	virtual void unused03( void );
	virtual void unused04( void );
	virtual void unused05( void );
	virtual void unused06( void );
	virtual void unused07( void );
	virtual void unused08( void );
	virtual void unused09( void );
	virtual void unused10( void );
	virtual void unused11( void );
	virtual void unused12( void );
	virtual void unused13( void );
	virtual void unused14( void );
	virtual void unused15( void );
	virtual void unused16( void );
	virtual void unused17( void );
	virtual void unused18( void );
	virtual void unused19( void );
	virtual void unused20( void );
	virtual void unused21( void );
	virtual void unused22( void );
	virtual void unused23( void );
	virtual void unused24( void );
	virtual void unused25( void );
	virtual void unused26( void );
	virtual void unused27( void );
	virtual void unused28( void );
	virtual void unused29( void );
	virtual void unused30( void );
	virtual void unused31( void );
	virtual void unused32( void );
	virtual void unused33( void );
	virtual void unused34( void );
	virtual void unused35( void );
	virtual void unused36( void );
	virtual void unused37( void );
	virtual void unused38( void );
	virtual void unused39( void );
	virtual void unused40( void );
	virtual void unused41( void );
	virtual void unused42( void );
	virtual void unused43( void );
	virtual void unused44( void );
	virtual void unused45( void );
	virtual void unused46( void );
	virtual void unused47( void );
	virtual void unused48( void );
	virtual void unused49( void );
	virtual void unused50( void );
	virtual void unused51( void );
	virtual void unused52( void );
	virtual void unused53( void );
	virtual void unused54( void );
	virtual void unused55( void );
	virtual void unused56( void );
	virtual void unused57( void );
	virtual void unused58( void );
	virtual void unused59( void );
	virtual void unused60( void );
	virtual void unused61( void );
	// BFME2: five more slots ahead of winFillRect than BFME1 (see
	// reference/shims/bfme2gwm/GameClient/GameWindowManager.h).
	virtual void unused62( void );
	virtual void unused63( void );
	virtual void unused64( void );
	virtual void unused65( void );
	virtual void unused66( void );
	virtual void winFillRect( Color color, Real width, Int startX, Int startY,
		Int endX, Int endY );
	virtual void winOpenRect( Color color, Real width, Int startX, Int startY,
		Int endX, Int endY );
};

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
	WIN_STATUS_BORDER = 0x00001000,
	WIN_STATUS_SEE_THRU = 0x00010000,
	WIN_COLOR_UNDEFINED = 0x00ffffff,
	TP_TOP_SIDE = 3,
	TP_BOTTOM_SIDE = 6
};

inline Int BitTest( UnsignedInt bits, UnsignedInt mask )
{
	return ( bits & mask ) != 0;
}

#define WIN_DRAW_LINE_WIDTH 1.0f

#define BFME_DRAW_TAB( NUMBER, INDEX ) \
	if( tabData->tabCount >= NUMBER ) \
	{ \
		if( tabData->subPaneDisabled[ INDEX ] ) \
		{ \
			color = tabControl->winGetDisabledColor( NUMBER ); \
			border = tabControl->winGetDisabledBorderColor( NUMBER ); \
		} \
		else if( tabData->activeTab == INDEX ) \
		{ \
			color = tabControl->winGetHiliteColor( NUMBER ); \
			border = tabControl->winGetHiliteBorderColor( NUMBER ); \
		} \
		else \
		{ \
			color = tabControl->winGetEnabledColor( NUMBER ); \
			border = tabControl->winGetEnabledBorderColor( NUMBER ); \
		} \
		if( border != WIN_COLOR_UNDEFINED ) \
		{ \
			TheWindowManager->winOpenRect( border, WIN_DRAW_LINE_WIDTH, \
				tabX, tabY, tabX + tabWidth, tabY + tabHeight ); \
		} \
		if( color != WIN_COLOR_UNDEFINED ) \
		{ \
			TheWindowManager->winFillRect( color, WIN_DRAW_LINE_WIDTH, \
				tabX + 1, tabY + 1, tabX + tabWidth - 1, tabY + tabHeight - 1 ); \
		} \
	} \
	tabX += tabDeltaX; \
	tabY += tabDeltaY;

// ?W3DGadgetTabControlDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z
void W3DGadgetTabControlDraw( GameWindow *tabControl,
	WinInstanceData *instData )
{
	ICoord2D origin, size;

	tabControl->winGetScreenPosition( &origin.x, &origin.y );
	tabControl->winGetSize( &size.x, &size.y );

	tabControl->rva0009DC32( instData );

	if( BitTest( tabControl->winGetStatus(), WIN_STATUS_BORDER ) == 1 &&
		!BitTest( tabControl->winGetStatus(), WIN_STATUS_SEE_THRU ) )
	{
		tabControl->winDrawBorder();
	}

	TabControlData *tabData = (TabControlData *)tabControl->winGetUserData();

	Int tabX, tabY, tabWidth, tabHeight, tabDeltaX, tabDeltaY;
	tabX = origin.x + tabData->tabsLeftLimit;
	tabY = origin.y + tabData->tabsTopLimit;
	tabWidth = tabData->tabWidth;
	tabHeight = tabData->tabHeight;
	if( ( tabData->tabEdge == TP_TOP_SIDE ) ||
		( tabData->tabEdge == TP_BOTTOM_SIDE ) )
	{
		tabDeltaX = tabWidth;
		tabDeltaY = 0;
	}
	else
	{
		tabDeltaX = 0;
		tabDeltaY = tabHeight;
	}

	Color color, border;

	BFME_DRAW_TAB( 1, 0 )
	BFME_DRAW_TAB( 2, 1 )
	BFME_DRAW_TAB( 3, 2 )
	BFME_DRAW_TAB( 4, 3 )
	BFME_DRAW_TAB( 5, 4 )
	BFME_DRAW_TAB( 6, 5 )
	BFME_DRAW_TAB( 7, 6 )
	BFME_DRAW_TAB( 8, 7 )
}

#undef BFME_DRAW_TAB

// Clean BF1 9cbfb551fe20dae985f91f2319d8997287b6a705
// GameEngineDevice/Source/W3DDevice/GameClient/GUI/Gadget/W3DTabControl.cpp
// and its GadgetTabControl accessors supply the fixed-index draw-field
// expressions, compiled /O1 /arch:SSE /G7. The ZH header's arrays start four
// bytes too early; donor labels from an unadjusted placement are not target
// identities. These functions use this file's already-verified BFME2
// GameWindow arrays48/B4/120 with image/color/border offsets0/4/8.
// Each independent native leaf below loads its stack argument, reads one
// raw32 draw field, and returns with RET0. Every start follows a prior RET
// (A3155 follows the existing A3143 draw callback's RET4). Address-owned
// names retain uncertainty about original callable names and color signedness.
// Native0x000A3155..0x000A315D; offset0x70: EnabledColor index3.
unsigned Rva000A3155TabDrawField(GameWindow *window)
{
    return (unsigned)window->winGetEnabledColor(3);
}

// Native0x000A3165..0x000A3170; offset0x88: EnabledColor index5.
unsigned Rva000A3165TabDrawField(GameWindow *window)
{
    return (unsigned)window->winGetEnabledColor(5);
}

// Native0x000A317B..0x000A3186; offset0x94: EnabledColor index6.
unsigned Rva000A317BTabDrawField(GameWindow *window)
{
    return (unsigned)window->winGetEnabledColor(6);
}

// Native0x000A3186..0x000A3191; offset0x98: EnabledBorderColor index6.
unsigned Rva000A3186TabDrawField(GameWindow *window)
{
    return (unsigned)window->winGetEnabledBorderColor(6);
}

// Native0x000A319C..0x000A31A7; offset0xA0: EnabledColor index7.
unsigned Rva000A319CTabDrawField(GameWindow *window)
{
    return (unsigned)window->winGetEnabledColor(7);
}

// Native0x000A31A7..0x000A31B2; offset0xA4: EnabledBorderColor index7.
unsigned Rva000A31A7TabDrawField(GameWindow *window)
{
    return (unsigned)window->winGetEnabledBorderColor(7);
}

// Native0x000A31BD..0x000A31C8; offset0xAC: EnabledColor index8.
unsigned Rva000A31BDTabDrawField(GameWindow *window)
{
    return (unsigned)window->winGetEnabledColor(8);
}

// Native0x000A31E9..0x000A31F4; offset0xDC: DisabledColor index3.
unsigned Rva000A31E9TabDrawField(GameWindow *window)
{
    return (unsigned)window->winGetDisabledColor(3);
}

// Native0x000A31FF..0x000A320A; offset0xF4: DisabledColor index5.
unsigned Rva000A31FFTabDrawField(GameWindow *window)
{
    return (unsigned)window->winGetDisabledColor(5);
}

// Native0x000A3215..0x000A3220; offset0x100: DisabledColor index6.
unsigned Rva000A3215TabDrawField(GameWindow *window)
{
    return (unsigned)window->winGetDisabledColor(6);
}

// Native0x000A3220..0x000A322B; offset0x104: DisabledBorderColor index6.
unsigned Rva000A3220TabDrawField(GameWindow *window)
{
    return (unsigned)window->winGetDisabledBorderColor(6);
}

// Native0x000A3236..0x000A3241; offset0x10C: DisabledColor index7.
unsigned Rva000A3236TabDrawField(GameWindow *window)
{
    return (unsigned)window->winGetDisabledColor(7);
}

// Native0x000A3241..0x000A324C; offset0x110: DisabledBorderColor index7.
unsigned Rva000A3241TabDrawField(GameWindow *window)
{
    return (unsigned)window->winGetDisabledBorderColor(7);
}

// Native0x000A3257..0x000A3262; offset0x118: DisabledColor index8.
unsigned Rva000A3257TabDrawField(GameWindow *window)
{
    return (unsigned)window->winGetDisabledColor(8);
}

// Native0x000A3283..0x000A328E; offset0x148: HiliteColor index3.
unsigned Rva000A3283TabDrawField(GameWindow *window)
{
    return (unsigned)window->winGetHiliteColor(3);
}

// Native0x000A3299..0x000A32A4; offset0x160: HiliteColor index5.
unsigned Rva000A3299TabDrawField(GameWindow *window)
{
    return (unsigned)window->winGetHiliteColor(5);
}

// Native0x000A32AF..0x000A32BA; offset0x16C: HiliteColor index6.
unsigned Rva000A32AFTabDrawField(GameWindow *window)
{
    return (unsigned)window->winGetHiliteColor(6);
}

// Native0x000A32BA..0x000A32C5; offset0x170: HiliteBorderColor index6.
unsigned Rva000A32BATabDrawField(GameWindow *window)
{
    return (unsigned)window->winGetHiliteBorderColor(6);
}

// Native0x000A32D0..0x000A32DB; offset0x178: HiliteColor index7.
unsigned Rva000A32D0TabDrawField(GameWindow *window)
{
    return (unsigned)window->winGetHiliteColor(7);
}

// Native0x000A32DB..0x000A32E6; offset0x17C: HiliteBorderColor index7.
unsigned Rva000A32DBTabDrawField(GameWindow *window)
{
    return (unsigned)window->winGetHiliteBorderColor(7);
}

// Native0x000A32F1..0x000A32FC; offset0x184: HiliteColor index8.
unsigned Rva000A32F1TabDrawField(GameWindow *window)
{
    return (unsigned)window->winGetHiliteColor(8);
}

