// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// getButtonTextColors 0x000A4999 (92B), drawButtonText 0x000A49F5 (248B),
// Rva000A52AEDrawNumber 0x000A52AE (304B) and W3DGadgetPushButtonDraw
// 0x000A53DE (783B): Zero Hour's W3DPushButton.cpp through BFME1's matched
// split of it (Open-BFME-1 game/GameEngineDevice/Source/W3DDevice/
// GameClient/GUI/Gadget/W3DPushButtonText_Thunk.cpp, W3DPushButtonDraw_Thunk.cpp
// and W3DPushButtonDrawNumber00794B70.cpp), built /O1 /arch:SSE like the
// matched W3DHorizontalSlider.cpp sibling; /G7 gives drawButtonText's
// byte-register `and cl, 1` for the wrap-centered flag.
//
// Target evidence: the function lexicon entry at 0x009B3D18 names
// W3DGadgetPushButtonDraw and points at 0x000A53DE, which push-button gadget
// vtable 0x00BC9204 slot 3 also calls. It calls 0x000A49F5 with the window in
// ECX and instData in EAX (a same-TU static) after the out-of-line
// WinInstanceData::getTextLength, as Zero Hour calls drawButtonText; the
// helper's body is Zero Hour's apart from the colour pick, which goes through
// 0x000A4999 with (window, instData, &textColor, &dropColor). That callee tests
// WIN_STATUS_ENABLED and WIN_STATE_HILITED and stores the matching rowed
// GameWindow text and text-border colour getters, so it carries BFME1's name
// getButtonTextColors. 0x000A52AE runs when the button data's +0x28 byte is 1,
// formats the +0x2C count with L"%d" into the +0x30 DisplayString and draws it
// at the bottom right; nothing names it, so the address stays in the name.
//
// BFME2 deltas from Zero Hour: the draw colours are read straight from the
// GameWindow draw data, the text is set with setTextColor and drawn with a 1,1
// drop offset, the video buffer, overlay image, clocks and border go through
// float-coordinate Display members, and the clock reset goes back through
// winSetUserData.

#include "unicode_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef unsigned char Bool;
typedef float Real;
typedef int Color;

class GameFont;
class VideoBuffer;
class Image;

struct ICoord2D
{
	Int x;
	Int y;
};

// BFME DisplayString slots: setText +0x04, getTextLength +0x0C, setFont +0x18,
// getFont +0x1C, setWordWrap +0x20, setWordWrapCentered +0x24, setTextColor
// +0x28, draw +0x38, getSize +0x3C.
class DisplayString
{
public:
	virtual void unused00();
	virtual void setText( UnicodeString text );
	virtual void unused02();
	virtual Int getTextLength( void );
	virtual void unused04();
	virtual void unused05();
	virtual void setFont( GameFont *font );
	virtual GameFont *getFont( void );
	virtual void setWordWrap( Int wordWrap );
	virtual void setWordWrapCentered( Bool isCentered );
	virtual void setTextColor( Color color, Color dropColor );
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void draw( Int x, Int y, Int xDrop, Int yDrop );
	virtual void getSize( Int *width, Int *height );
};

// Only the members these bodies touch; the offsets are BFME2 retail's.
class WinInstanceData
{
public:
	UnsignedInt getState( void ) { return m_state; }
	UnsignedInt getStatus( void ) { return m_status; }
	Int getTextLength( void );

	unsigned char m_unreconstructed00[ 0x08 ];
	UnsignedInt m_state;                                   // +0x08
	UnsignedInt m_style;                                   // +0x0C
	UnsignedInt m_status;                                  // +0x10
	unsigned char m_unreconstructed14[ 0x188 ];
	DisplayString *m_text;                                 // +0x19C
	DisplayString *m_tooltip;                              // +0x1A0
	VideoBuffer *m_videoBuffer;                            // +0x1A4
};

struct WinDrawData
{
	const Image *image;
	Color color;
	Color borderColor;
};

// The enabled, disabled and hilite draw data sit at +0x48, +0xB4 and +0x120.
class GameWindow
{
public:
	Int winGetScreenPosition( Int *x, Int *y );
	Int winGetSize( Int *width, Int *height );
	UnsignedInt winGetStatus( void );
	void *winGetUserData( void );
	void winSetUserData( void *data );
	GameFont *winGetFont( void );
	Color winGetEnabledTextColor( void );
	Color winGetEnabledTextBorderColor( void );
	Color winGetDisabledTextColor( void );
	Color winGetDisabledTextBorderColor( void );
	Color winGetHiliteTextColor( void );
	Color winGetHiliteTextBorderColor( void );

	unsigned char m_unreconstructed00[ 0x48 ];
	WinDrawData m_enabledDrawData[ 9 ];                    // +0x48
	WinDrawData m_disabledDrawData[ 9 ];                   // +0xB4
	WinDrawData m_hiliteDrawData[ 9 ];                     // +0x120
};

class GameWindowManager
{
public:
	virtual void unused00(); virtual void unused01(); virtual void unused02(); virtual void unused03();
	virtual void unused04(); virtual void unused05(); virtual void unused06(); virtual void unused07();
	virtual void unused08(); virtual void unused09(); virtual void unused10(); virtual void unused11();
	virtual void unused12(); virtual void unused13(); virtual void unused14(); virtual void unused15();
	virtual void unused16(); virtual void unused17(); virtual void unused18(); virtual void unused19();
	virtual void unused20(); virtual void unused21(); virtual void unused22(); virtual void unused23();
	virtual void unused24(); virtual void unused25(); virtual void unused26(); virtual void unused27();
	virtual void unused28(); virtual void unused29(); virtual void unused30(); virtual void unused31();
	virtual void unused32(); virtual void unused33(); virtual void unused34(); virtual void unused35();
	virtual void unused36(); virtual void unused37(); virtual void unused38(); virtual void unused39();
	virtual void unused40(); virtual void unused41(); virtual void unused42(); virtual void unused43();
	virtual void unused44(); virtual void unused45(); virtual void unused46(); virtual void unused47();
	virtual void unused48(); virtual void unused49(); virtual void unused50(); virtual void unused51();
	virtual void unused52(); virtual void unused53(); virtual void unused54(); virtual void unused55();
	virtual void unused56(); virtual void unused57(); virtual void unused58(); virtual void unused59();
	virtual void unused60(); virtual void unused61(); virtual void unused62(); virtual void unused63();
	virtual void unused64(); virtual void unused65(); virtual void unused66();
	virtual void winFillRect( Color color, Real width,
		Int startX, Int startY, Int endX, Int endY );         // +0x10C
	virtual void winOpenRect( Color color, Real width,
		Int startX, Int startY, Int endX, Int endY );         // +0x110
};

class Display
{
public:
	virtual void unused00(); virtual void unused01(); virtual void unused02(); virtual void unused03();
	virtual void unused04(); virtual void unused05(); virtual void unused06(); virtual void unused07();
	virtual void unused08(); virtual void unused09(); virtual void unused10(); virtual void unused11();
	virtual void unused12(); virtual void unused13(); virtual void unused14(); virtual void unused15();
	virtual void unused16(); virtual void unused17(); virtual void unused18(); virtual void unused19();
	virtual void unused20(); virtual void unused21(); virtual void unused22(); virtual void unused23();
	virtual void unused24(); virtual void unused25(); virtual void unused26(); virtual void unused27();
	virtual void unused28(); virtual void unused29(); virtual void unused30(); virtual void unused31();
	virtual void unused32(); virtual void unused33(); virtual void unused34(); virtual void unused35();
	virtual void unused36(); virtual void unused37(); virtual void unused38(); virtual void unused39();
	virtual void unused40(); virtual void unused41(); virtual void unused42(); virtual void unused43();
	virtual void unused44(); virtual void unused45(); virtual void unused46(); virtual void unused47();
	virtual void unused48(); virtual void unused49(); virtual void unused50(); virtual void unused51();
	virtual void unused52(); virtual void unused53(); virtual void unused54(); virtual void unused55();
	virtual void unused56(); virtual void unused57(); virtual void unused58(); virtual void unused59();
	virtual void unused60(); virtual void unused61(); virtual void unused62(); virtual void unused63();
	virtual void unused64();
	virtual void drawVideoBuffer( VideoBuffer *buffer, Real startX, Real startY,
		Real endX, Real endY, Color color = -1 );             // +0x104
};

// Non-virtual float-coordinate members of the display, rowed under their
// address names (W3DDisplayDrawImageMode.cpp and Rva000A4826Call.cpp).
class W3DDisplay
{
public:
	void rva0004D6B3( Image *image, Real startX, Real startY, Real endX, Real endY,
		Int color, Int mode );
	void rva0008EEF0( Real startX, Real startY, Real width, Real height,
		Real lineWidth, Int color );
};

class Rva000A4826
{
public:
	void rva000A4826( Real startX, Real startY, Real width, Real height,
		Real percent, Int color );
	void rva000A4875( Real startX, Real startY, Real width, Real height,
		Real percent, Int color );
};

// The standard button data prefix followed by BFME-only fields.
struct PushButtonData
{
	UnsignedByte drawClock;                                // +0x00
	Int percentClock;                                      // +0x04
	Color colorClock;                                      // +0x08
	Bool drawBorder;                                       // +0x0C
	Color colorBorder;                                     // +0x10
	void *userData;                                        // +0x14
	Image *overlayImage;                                   // +0x18
	unsigned char m_unreconstructed1C[ 0x0C ];
	UnsignedByte drawNumber;                               // +0x28
	UnsignedInt number;                                    // +0x2C
	DisplayString *numberText;                             // +0x30
};

enum
{
	WIN_STATUS_ENABLED = 0x00000008,
	WIN_STATUS_WRAP_CENTERED = 0x00040000,
	WIN_STATE_HILITED = 0x00000002,
	WIN_STATE_SELECTED = 0x00000004,
	WIN_COLOR_UNDEFINED = 0x00FFFFFF,
	NO_CLOCK = 0,
	NORMAL_CLOCK = 1,
	INVERSE_CLOCK = 2
};

inline Int BitTest( UnsignedInt bits, UnsignedInt mask )
{
	return ( bits & mask ) != 0;
}

#define WIN_DRAW_LINE_WIDTH 1.0f
#define FALSE 0
#define NULL 0

extern GameWindowManager *TheWindowManager;
extern Display *TheDisplay;

// Coordinates with an empty default constructor; see W3DCheckBox.cpp.
struct CtorCoord : ICoord2D
{
	CtorCoord() {}
};

// getButtonTextColors ========================================================
/** Pick the text and drop colours for the window's state */
//=============================================================================
void getButtonTextColors( GameWindow *window, WinInstanceData *instData,
													Color *textColor, Color *dropColor )
{

	if( BitTest( window->winGetStatus(), WIN_STATUS_ENABLED ) == FALSE )
	{
		*textColor = window->winGetDisabledTextColor();
		*dropColor = window->winGetDisabledTextBorderColor();
	}  // end if, disabled
	else if( BitTest( instData->getState(), WIN_STATE_HILITED ) )
	{
		*textColor = window->winGetHiliteTextColor();
		*dropColor = window->winGetHiliteTextBorderColor();
	}  // end else if, hilited
	else
	{
		*textColor = window->winGetEnabledTextColor();
		*dropColor = window->winGetEnabledTextBorderColor();
	}  // end enabled only

}  // end getButtonTextColors

// drawButtonText =============================================================
/** Draw button text to the screen */
//=============================================================================
static void drawButtonText( GameWindow *window, WinInstanceData *instData )
{
	CtorCoord origin, size, textPos;
	Int width, height;
	Color textColor, dropColor;
	DisplayString *text = instData->m_text;

	// sanity
	if( text == NULL || text->getTextLength() == 0 )
		return;

	// get window position and size
	window->winGetScreenPosition( &origin.x, &origin.y );
	window->winGetSize( &size.x, &size.y );

	// set whether or not we center the wrapped text
	text->setWordWrapCentered( BitTest( instData->getStatus(), WIN_STATUS_WRAP_CENTERED ) );
	text->setWordWrap( size.x );

	// get the right text color
	getButtonTextColors( window, instData, &textColor, &dropColor );

	// set our font to that of our parent if not the same
	if( text->getFont() != window->winGetFont() )
		text->setFont( window->winGetFont() );

	// get text size
	text->getSize( &width, &height );

	// where to draw
	textPos.x = origin.x + (size.x / 2) - (width / 2);
	textPos.y = origin.y + (size.y / 2) - (height / 2);

	// draw it
	text->setTextColor( textColor, dropColor );
	text->draw( textPos.x, textPos.y, 1, 1 );

}  // end drawButtonText

// Rva000A52AEDrawNumber ======================================================
/** Draw the button's count at its bottom right */
//=============================================================================
void Rva000A52AEDrawNumber( GameWindow *window, WinInstanceData *instData,
														PushButtonData *data )
{

	if( data == NULL || data->number < 1 )
		return;

	CtorCoord origin, size;
	Int width, height;
	window->winGetSize( &size.x, &size.y );
	window->winGetScreenPosition( &origin.x, &origin.y );

	DisplayString *text = data->numberText;
	if( text == NULL )
		return;

	UnicodeString displayNumber;
	displayNumber.format( L"%d", data->number );
	text->setText( displayNumber );

	Color textColor, dropColor;
	getButtonTextColors( window, instData, &textColor, &dropColor );

	if( text->getFont() != window->winGetFont() )
		text->setFont( window->winGetFont() );

	text->getSize( &width, &height );

	Int textX = size.x * 0.5f - width * 0.5f + origin.x;
	Int textY = origin.y + size.y - height;
	text->setTextColor( textColor, dropColor );
	text->draw( textX, textY, 1, 1 );

}  // end Rva000A52AEDrawNumber

// W3DGadgetPushButtonDraw ====================================================
/** Draw colored pushbutton using standard graphics */
//=============================================================================
void W3DGadgetPushButtonDraw( GameWindow *window, WinInstanceData *instData )
{
	Color color, border;
	CtorCoord origin, size, start, end;

	// get window position and size
	window->winGetScreenPosition( &origin.x, &origin.y );
	window->winGetSize( &size.x, &size.y );

	//
	// get pointer to image we want to draw depending on our state,
	// see GadgetPushButton.h for info
	//
	if( BitTest( window->winGetStatus(), WIN_STATUS_ENABLED ) == FALSE )
	{

		if( BitTest( instData->getState(), WIN_STATE_SELECTED ) )
		{
			color			= window->m_disabledDrawData[ 1 ].color;
			border		= window->m_disabledDrawData[ 1 ].borderColor;
		}
		else
		{
			color			= window->m_disabledDrawData[ 0 ].color;
			border		= window->m_disabledDrawData[ 0 ].borderColor;
		}

	}  // end if, disabled
	else if( BitTest( instData->getState(), WIN_STATE_HILITED ) )
	{

		if( BitTest( instData->getState(), WIN_STATE_SELECTED ) )
		{
			color			= window->m_hiliteDrawData[ 1 ].color;
			border		= window->m_hiliteDrawData[ 1 ].borderColor;
		}
		else
		{
			color			= window->m_hiliteDrawData[ 0 ].color;
			border		= window->m_hiliteDrawData[ 0 ].borderColor;
		}

	}  // end else if, hilited and enabled
	else
	{

		if( BitTest( instData->getState(), WIN_STATE_SELECTED ) )
		{
			color			= window->m_enabledDrawData[ 1 ].color;
			border		= window->m_enabledDrawData[ 1 ].borderColor;
		}
		else
		{
			color			= window->m_enabledDrawData[ 0 ].color;
			border		= window->m_enabledDrawData[ 0 ].borderColor;
		}

	}  // end else, enabled only

	// compute draw position
	start.x = origin.x;
	start.y = origin.y;
	end.x = start.x + size.x;
	end.y = start.y + size.y;

	// box and border
	if( border != WIN_COLOR_UNDEFINED )
	{

		TheWindowManager->winOpenRect( border, WIN_DRAW_LINE_WIDTH,
																	 start.x, start.y, end.x, end.y );

	}  // end if

	if( color != WIN_COLOR_UNDEFINED )
	{

		// draw inside border
		start.x++;
		start.y++;
		end.x--;
		end.y--;
		TheWindowManager->winFillRect( color, WIN_DRAW_LINE_WIDTH,
																	 start.x, start.y, end.x, end.y );

	}  // end if

	// draw the button text
	if( instData->getTextLength() )
		drawButtonText( window, instData );

	// if we have a video buffer, draw the video buffer
	if ( instData->m_videoBuffer )
	{
		TheDisplay->drawVideoBuffer( instData->m_videoBuffer, origin.x, origin.y, origin.x + size.x, origin.y + size.y );
	}

	PushButtonData *pData = (PushButtonData *)window->winGetUserData();
	if( pData )
	{
		if( pData->overlayImage )
		{
			//Render the overlay image now.
			((W3DDisplay *)TheDisplay)->rva0004D6B3( pData->overlayImage, origin.x, origin.y, origin.x + size.x, origin.y + size.y, -1, 2 );
		}

		if( pData->drawClock )
		{
			if( pData->drawClock == NORMAL_CLOCK )
			{
				((Rva000A4826 *)TheDisplay)->rva000A4826( origin.x, origin.y, size.x, size.y, pData->percentClock, pData->colorClock );
			}
			else if( pData->drawClock == INVERSE_CLOCK )
			{
				((Rva000A4826 *)TheDisplay)->rva000A4875( origin.x, origin.y, size.x, size.y, pData->percentClock, pData->colorClock );
			}
			pData->drawClock = NO_CLOCK;
			window->winSetUserData( pData );
		}

		if( pData->drawNumber == 1 )
			Rva000A52AEDrawNumber( window, instData, pData );

		if( pData->drawBorder && pData->colorBorder != WIN_COLOR_UNDEFINED )
		{
			((W3DDisplay *)TheDisplay)->rva0008EEF0( origin.x - 1, origin.y - 1, size.x + 2, size.y + 2, 1, pData->colorBorder );
		}
	}

}  // end W3DGadgetPushButtonDraw
