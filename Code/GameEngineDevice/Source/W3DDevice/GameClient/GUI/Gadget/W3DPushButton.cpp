// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// getButtonTextColors 0x000A4999 (92B), drawButtonText 0x000A49F5 (248B),
// W3DGadgetPushButtonImageDrawThree 0x000A4B7C (1184B), Rva000A52AEDrawNumber
// 0x000A52AE (304B) and W3DGadgetPushButtonDraw 0x000A53DE (783B): Zero Hour's
// W3DPushButton.cpp through BFME1's matched split of it (Open-BFME-1
// game/GameEngineDevice/Source/W3DDevice/GameClient/GUI/Gadget/
// W3DPushButtonText_Thunk.cpp, W3DPushButtonDraw_Thunk.cpp,
// W3DPushButtonImageDrawThree.cpp and W3DPushButtonDrawNumber00794B70.cpp),
// built /O1 /arch:SSE like the matched W3DHorizontalSlider.cpp sibling; /G7
// gives drawButtonText's byte-register `and cl, 1` for the wrap-centered flag.
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
// symbols.csv pins 0x000A4B7C as W3DGadgetPushButtonImageDrawThree, the callee
// of the lexicon-named W3DGadgetPushButtonImageDraw (0x000A6019) at the site
// BFME1's dispatcher calls it; it too reaches drawButtonText in registers.
//
// BFME2 deltas from Zero Hour: the draw colours are read straight from the
// GameWindow draw data, the text is set with setTextColor and drawn with a 1,1
// drop offset, the video buffer, overlay image, clocks and border go through
// float-coordinate Display members, and the clock reset goes back through
// winSetUserData.

#include "ascii_string.h"
#include "unicode_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef unsigned char Bool;
typedef float Real;
typedef int Color;

class GameFont;
class VideoBuffer;

struct ICoord2D
{
	Int x;
	Int y;
};

struct IRegion2D
{
	ICoord2D lo;
	ICoord2D hi;
};

// Only the image size is read here, at +0x24 and +0x28.
class Image
{
public:
	Int getImageWidth( void ) const { return m_width; }
	Int getImageHeight( void ) const { return m_height; }

	unsigned char m_unreconstructed00[ 0x24 ];
	Int m_width;                                           // +0x24
	Int m_height;                                          // +0x28
};

class ImageCollection
{
public:
	const Image *findImageByName( const AsciiString &name );
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
	unsigned char m_unreconstructed14[ 0x168 ];
	ICoord2D m_imageOffset;                                // +0x17C
	unsigned char m_unreconstructed184[ 0x18 ];
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
	virtual void unused64(); virtual void unused65();
	virtual void winDrawImage( const Image *image, Int startX, Int startY,
		Int endX, Int endY, Color color = 0xFFFFFFFF );       // +0x108
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
	virtual void unused40(); virtual void unused41();
	virtual void setClipRegion( IRegion2D *region );      // +0xA8
	virtual void unused43();
	virtual void enableClipping( Bool onoff );             // +0xB0
	virtual void unused45(); virtual void unused46(); virtual void unused47();
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
	void rva000A47DE( Real startX, Real startY, Real width, Real height,
		Int color );
	void rva000A48C4( Int image, Real startX, Real startY, Real endX, Real endY,
		Real percent, Int color );
};

// Render-state helpers bracketing the radial (masked) cameo draw.
void Rva00118AC0( void );
void Rva00118BA0( void );
void Rva00118C20( void );
void Rva00118B50( void );

// PushButtonData +0x34 flag (GadgetButtonFlag34Get.cpp).
bool Rva00327E0EGet( GameWindow *window );

// The local player's +0x34 object decides which of the two global radial
// clock colours is used.
struct LocalPlayerInfo
{
	unsigned char m_unreconstructed00[ 0x1BC ];
	Bool m_flag1BC;                                        // +0x1BC
};

class Player
{
public:
	unsigned char m_unreconstructed00[ 0x34 ];
	LocalPlayerInfo *m_info;                               // +0x34
};

class PlayerList
{
public:
	unsigned char m_unreconstructed00[ 0x10 ];
	// Retail's button bodies access +0x10 directly; this local layout view
	// does not supply the shared getter for the other PlayerList views.
	Player *m_local;                                       // +0x10
};

struct BfmePushButtonGlobalDataView
{
public:
	unsigned char m_unreconstructed00[ 0x1160 ];
	Color m_radialClockColor;                              // +0x1160
	Color m_radialClockColorFlagged;                       // +0x1164
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
	WIN_STATUS_USE_OVERLAY_STATES = 0x00200000,
	WIN_STATUS_NOT_READY = 0x00400000,
	WIN_STATUS_FLASHING = 0x00800000,
	WIN_STATUS_ALWAYS_COLOR = 0x01000000,
	WIN_STATUS_RADIAL = 0x04000000,                        // ZH's SHORTCUT_BUTTON bit
	WIN_STATUS_NO_STATE_IMAGES = 0x40000000,
	WIN_STATUS_GRAY_OVERLAY = 0x80000000,
	WIN_STATE_HILITED = 0x00000002,
	WIN_STATE_SELECTED = 0x00000004,
	WIN_COLOR_UNDEFINED = 0x00FFFFFF,
	NO_CLOCK = 0,
	NORMAL_CLOCK = 1,
	INVERSE_CLOCK = 2
};

enum DrawImageMode
{
	DRAW_IMAGE_SOLID = 0,
	DRAW_IMAGE_GRAYSCALE = 1,
	DRAW_IMAGE_ALPHA = 2,
	DRAW_IMAGE_RADIAL_GRAYSCALE = 4
};

inline Color GameMakeColor( UnsignedByte red, UnsignedByte green, UnsignedByte blue, UnsignedByte alpha )
{
	return ( alpha << 24 ) | ( red << 16 ) | ( green << 8 ) | blue;
}

inline Int BitTest( UnsignedInt bits, UnsignedInt mask )
{
	return ( bits & mask ) != 0;
}

#define WIN_DRAW_LINE_WIDTH 1.0f
#define RADIAL_CLOCK_SCALE ( 46.0f / 48.0f )
#define FALSE 0
#define NULL 0

extern GameWindowManager *TheWindowManager;
extern Display *TheDisplay;
extern ImageCollection *TheMappedImageCollection;
extern PlayerList *ThePlayerList;
// Retail's DIR32 references use the GameClient-owned slot at VA 0x00DFE758.
// Keep the measured +0x1160/+0x1164 view local and use its canonical provider.
class GlobalData;
extern GlobalData *TheWritableGlobalData;

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

// drawRadialOverlay ==========================================================
/** Draw a radial overlay image centred on the button, scaled to its size */
//=============================================================================
static void drawRadialOverlay( const Image *image, ICoord2D *start, ICoord2D *size,
															 Color color )
{
	Real radiusX = size->x * 0.5f;
	Real radiusY = size->y * 0.5f;
	Real centerX = start->x + radiusX;
	Real centerY = start->y + radiusY;
	radiusX = radiusX * image->getImageWidth() / 48.0f;
	radiusY = radiusY * image->getImageHeight() / 48.0f;

	((W3DDisplay *)TheDisplay)->rva0004D6B3( (Image *)image, centerX - radiusX, centerY - radiusY,
		centerX + radiusX, centerY + radiusY, color, DRAW_IMAGE_ALPHA );

}  // end drawRadialOverlay

// W3DGadgetPushButtonImageDrawThree ==========================================
/** Draw a horizontal button from left, repeating center and right images */
//=============================================================================
void W3DGadgetPushButtonImageDrawThree( GameWindow *window, WinInstanceData *instData )
{
	const Image *leftImage, *rightImage, *centerImage;
	CtorCoord origin, size, start, end;
	Int xOffset, yOffset;
	Int i;

	// get screen position and size
	window->winGetScreenPosition( &origin.x, &origin.y );
	window->winGetSize( &size.x, &size.y );

	// get image offset
	xOffset = instData->m_imageOffset.x;
	yOffset = instData->m_imageOffset.y;

	if( BitTest( window->winGetStatus(), WIN_STATUS_ENABLED ) == FALSE )
	{

		if( BitTest( instData->getState(), WIN_STATE_SELECTED ) )
		{
			leftImage		= window->m_disabledDrawData[ 1 ].image;
			rightImage	= window->m_disabledDrawData[ 4 ].image;
			centerImage	= window->m_disabledDrawData[ 3 ].image;
		}
		else
		{
			leftImage		= window->m_disabledDrawData[ 0 ].image;
			rightImage	= window->m_disabledDrawData[ 6 ].image;
			centerImage	= window->m_disabledDrawData[ 5 ].image;
		}

	}  // end if, disabled
	else if( BitTest( instData->getState(), WIN_STATE_HILITED ) )
	{

		if( BitTest( instData->getState(), WIN_STATE_SELECTED ) )
		{
			leftImage		= window->m_hiliteDrawData[ 1 ].image;
			rightImage	= window->m_hiliteDrawData[ 4 ].image;
			centerImage	= window->m_hiliteDrawData[ 3 ].image;
		}
		else
		{
			leftImage		= window->m_hiliteDrawData[ 0 ].image;
			rightImage	= window->m_hiliteDrawData[ 6 ].image;
			centerImage	= window->m_hiliteDrawData[ 5 ].image;
		}

	}  // end else if, hilited and enabled
	else
	{

		if( BitTest( instData->getState(), WIN_STATE_SELECTED ) )
		{
			leftImage		= window->m_enabledDrawData[ 1 ].image;
			rightImage	= window->m_enabledDrawData[ 4 ].image;
			centerImage	= window->m_enabledDrawData[ 3 ].image;
		}
		else
		{
			leftImage		= window->m_enabledDrawData[ 0 ].image;
			rightImage	= window->m_enabledDrawData[ 6 ].image;
			centerImage	= window->m_enabledDrawData[ 5 ].image;
		}

	}  // end else, enabled only

	// sanity, we need to have these images to make it look right
	if( leftImage == NULL || rightImage == NULL || centerImage == NULL )
		return;

	// get image sizes for the ends
	CtorCoord leftSize, rightSize;
	leftSize.x = leftImage->getImageWidth();
	rightSize.x = rightImage->getImageWidth();

	// get two key points used in the end drawing
	CtorCoord leftEnd, rightStart;
	leftEnd.x = origin.x + leftSize.x + xOffset;
	leftEnd.y = origin.y + size.y + yOffset;
	rightStart.x = origin.x + size.x - rightSize.x + xOffset;
	rightStart.y = origin.y + yOffset;

	// draw the center repeating bar
	Int centerWidth, pieces;

	// get width we have to draw our repeating center in
	centerWidth = rightStart.x - leftEnd.x;

	if( centerWidth <= 0 )
	{

		// draw left end
		start.x = origin.x + xOffset;
		start.y = origin.y + yOffset;
		end.y = leftEnd.y;
		end.x = origin.x + xOffset + size.x / 2;
		TheWindowManager->winDrawImage( leftImage, start.x, start.y, end.x, end.y );

		// draw right end
		start.y = rightStart.y;
		start.x = end.x;
		end.x = origin.x + size.x;
		end.y = start.y + size.y;
		TheWindowManager->winDrawImage( rightImage, start.x, start.y, end.x, end.y );

	}
	else
	{

		// how many whole repeating pieces will fit in that width
		pieces = centerWidth / centerImage->getImageWidth();

		// draw the pieces
		start.x = leftEnd.x;
		start.y = origin.y + yOffset;
		end.y = start.y + size.y + yOffset;
		for( i = 0; i < pieces; i++ )
		{

			end.x = start.x + centerImage->getImageWidth();
			TheWindowManager->winDrawImage( centerImage, start.x, start.y, end.x, end.y );
			start.x += centerImage->getImageWidth();

		}  // end for i

		// draw the clipped remainder of the center under the right end
		IRegion2D reg;
		reg.lo.x = start.x;
		reg.lo.y = start.y;
		reg.hi.x = rightStart.x;
		reg.hi.y = end.y;
		centerWidth = rightStart.x - start.x;
		if( centerWidth > 0 )
		{
			TheDisplay->setClipRegion( &reg );
			end.x = start.x + centerImage->getImageWidth();
			TheWindowManager->winDrawImage( centerImage, start.x, start.y, end.x, end.y );
			TheDisplay->enableClipping( FALSE );
		}

		// draw left end
		start.x = origin.x + xOffset;
		start.y = origin.y + yOffset;
		end = leftEnd;
		TheWindowManager->winDrawImage( leftImage, start.x, start.y, end.x, end.y );

		// draw right end
		start = rightStart;
		end.x = start.x + rightSize.x;
		end.y = start.y + size.y;
		TheWindowManager->winDrawImage( rightImage, start.x, start.y, end.x, end.y );

	}

	// draw the button text
	if( instData->getTextLength() )
		drawButtonText( window, instData );

	// get window position
	window->winGetScreenPosition( &start.x, &start.y );
	window->winGetSize( &size.x, &size.y );

	// if we have a video buffer, draw the video buffer
	if ( instData->m_videoBuffer )
	{
		TheDisplay->drawVideoBuffer( instData->m_videoBuffer, start.x, start.y, start.x + size.x, start.y + size.y );
	}

	PushButtonData *pData = (PushButtonData *)window->winGetUserData();
	if( pData )
	{
		if( pData->overlayImage )
		{
			((W3DDisplay *)TheDisplay)->rva0004D6B3( pData->overlayImage, origin.x, origin.y, origin.x + size.x, origin.y + size.y, -1, 2 );
		}

		if( pData->drawClock )
		{
			if( pData->drawClock == NORMAL_CLOCK )
			{
				((Rva000A4826 *)TheDisplay)->rva000A4826( start.x, start.y, size.x, size.y, pData->percentClock, pData->colorClock );
			}
			else if( pData->drawClock == INVERSE_CLOCK )
			{
				((Rva000A4826 *)TheDisplay)->rva000A4875( start.x, start.y, size.x, size.y, pData->percentClock, pData->colorClock );
			}
			pData->drawClock = NO_CLOCK;
			window->winSetUserData( pData );
		}

		if( pData->drawBorder && pData->colorBorder != WIN_COLOR_UNDEFINED )
		{
			((W3DDisplay *)TheDisplay)->rva0008EEF0( start.x - 1, start.y - 1, size.x + 2, size.y + 2, 1, pData->colorBorder );
		}
	}

}  // end W3DGadgetPushButtonImageDrawThree

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

// W3DGadgetPushButtonImageDrawOne ============================================
/** Draw pushbutton using a single image */
//=============================================================================
void W3DGadgetPushButtonImageDrawOne( GameWindow *window, WinInstanceData *instData )
{
	static const Image *pushedOverlayIcon = TheMappedImageCollection->findImageByName( "Cameo_push" );
	static const Image *hilitedOverlayIcon = TheMappedImageCollection->findImageByName( "Cameo_hilited" );
	static const Image *radialPushedIcon = TheMappedImageCollection->findImageByName( "RadialPush" );
	static const Image *radialHilitedIcon = TheMappedImageCollection->findImageByName( "RadialOver" );
	static const Image *radialBorderIcon = TheMappedImageCollection->findImageByName( "RadialBorder" );
	static const Image *radialClockOverlay1 = TheMappedImageCollection->findImageByName( "RadialClockOverlay1" );
	static const Image *radialClockOverlay2 = TheMappedImageCollection->findImageByName( "RadialClockOverlay2" );

	// the drawing locals live in their own scope below the statics; that scope
	// is what lets the last lookup temporary share the others' frame slot
	{
		const Image *image;
		CtorCoord size, start, end;

		//
		// get pointer to image we want to draw depending on our state,
		// see GadgetPushButton.h for info
		//
		image = window->m_enabledDrawData[ 0 ].image;

		if( !BitTest( window->winGetStatus(), WIN_STATUS_USE_OVERLAY_STATES ) &&
				!BitTest( window->winGetStatus(), WIN_STATUS_NO_STATE_IMAGES ) )
		{
			if( BitTest( window->winGetStatus(), WIN_STATUS_ENABLED ) == FALSE )
			{

				if( BitTest( instData->getState(), WIN_STATE_SELECTED ) )
					image			= window->m_disabledDrawData[ 1 ].image;
				else
					image			= window->m_disabledDrawData[ 0 ].image;

			}  // end if, disabled
			else if( BitTest( instData->getState(), WIN_STATE_HILITED ) )
			{

				if( BitTest( instData->getState(), WIN_STATE_SELECTED ) )
					image			= window->m_hiliteDrawData[ 1 ].image;
				else
					image			= window->m_hiliteDrawData[ 0 ].image;

			}  // end else if, hilited and enabled
			else
			{

				if( BitTest( instData->getState(), WIN_STATE_SELECTED ) )
					image			= window->m_hiliteDrawData[ 1 ].image;

			}  // end else, enabled only
		}

		Bool radial = BitTest( window->winGetStatus(), WIN_STATUS_RADIAL );

		// draw the image
		if( image )
		{

			// get window position
			window->winGetScreenPosition( &start.x, &start.y );
			window->winGetSize( &size.x, &size.y );

			// offset position by image offset
			start.x += instData->m_imageOffset.x;
			start.y += instData->m_imageOffset.y;

			// find end point
			end.x = start.x + size.x;
			end.y = start.y + size.y;

			Int drawMode = DRAW_IMAGE_ALPHA;
			Int colorMultiplier = 0xffffffff;

			if( BitTest( window->winGetStatus(), WIN_STATUS_USE_OVERLAY_STATES ) &&
					!BitTest( window->winGetStatus(), WIN_STATUS_NO_STATE_IMAGES ) )
			{
				if( !BitTest( window->winGetStatus(), WIN_STATUS_ENABLED ) )
				{
					if( !BitTest( window->winGetStatus(), WIN_STATUS_NOT_READY ) )
					{
						if( !BitTest( window->winGetStatus(), WIN_STATUS_ALWAYS_COLOR ) )
						{
							drawMode = DRAW_IMAGE_GRAYSCALE;
							if( Rva00327E0EGet( window ) )
								colorMultiplier = 0xff808080;
						}
						else
						{
							colorMultiplier = 0xff909090;
						}
					}
				}
			}

			if( radial )
			{
				drawMode = ( drawMode == DRAW_IMAGE_GRAYSCALE ) ? DRAW_IMAGE_RADIAL_GRAYSCALE : DRAW_IMAGE_SOLID;
				Rva00118AC0();
				Rva00118BA0();
				((Rva000A4826 *)TheDisplay)->rva000A47DE( start.x, start.y, end.x - start.x, end.y - start.y, -1 );
				Rva00118C20();
			}

			((W3DDisplay *)TheDisplay)->rva0004D6B3( (Image *)image, start.x, start.y, end.x, end.y, colorMultiplier, drawMode );

			if( radial )
				Rva00118B50();

		}  // end if

		// draw the button text
		if( instData->getTextLength() )
			drawButtonText( window, instData );

		// get window position
		window->winGetScreenPosition( &start.x, &start.y );
		window->winGetSize( &size.x, &size.y );

		// if we have a video buffer, draw the video buffer
		if ( instData->m_videoBuffer )
		{
			TheDisplay->drawVideoBuffer( instData->m_videoBuffer, start.x, start.y, start.x + size.x, start.y + size.y );
		}

		PushButtonData *pData = (PushButtonData *)window->winGetUserData();
		if( pData )
		{
			if( pData->overlayImage )
			{
				//Render the overlay image now.
				((W3DDisplay *)TheDisplay)->rva0004D6B3( pData->overlayImage, start.x, start.y, start.x + size.x, start.y + size.y, -1, DRAW_IMAGE_ALPHA );
			}

			if( pData->drawClock )
			{
				if( pData->drawClock == NORMAL_CLOCK && pData->percentClock > 0 )
				{
					((Rva000A4826 *)TheDisplay)->rva000A4826( start.x, start.y, size.x, size.y, pData->percentClock, pData->colorClock );
				}
				else if( pData->drawClock == INVERSE_CLOCK && pData->percentClock < 100 )
				{
					Color clockColor = 0;
					if( ThePlayerList && ThePlayerList->m_local )
					{
						LocalPlayerInfo *info = ThePlayerList->m_local->m_info;
						if( info && info->m_flag1BC )
							clockColor = ((const BfmePushButtonGlobalDataView *)TheWritableGlobalData)->m_radialClockColorFlagged;
						else
							clockColor = ((const BfmePushButtonGlobalDataView *)TheWritableGlobalData)->m_radialClockColor;
					}

					Real radiusX = size.x * 0.5f;
					Real radiusY = size.y * 0.5f;
					Real centerX = start.x + radiusX;
					Real centerY = start.y + radiusY;
					radiusX *= RADIAL_CLOCK_SCALE;
					radiusY *= RADIAL_CLOCK_SCALE;

					// the image pointers travel through the helper's Int parameter
					((Rva000A4826 *)TheDisplay)->rva000A48C4( (Int)radialClockOverlay1, centerX - radiusX, centerY - radiusY,
						centerX + radiusX, centerY + radiusY, pData->percentClock, pData->colorClock );
					((Rva000A4826 *)TheDisplay)->rva000A48C4( (Int)radialClockOverlay2, centerX - radiusX, centerY - radiusY,
						centerX + radiusX, centerY + radiusY, pData->percentClock, clockColor );
				}
				pData->drawClock = NO_CLOCK;
				window->winSetUserData( pData );
			}

			if( !radial && pData->drawBorder && pData->colorBorder != WIN_COLOR_UNDEFINED )
			{
				((W3DDisplay *)TheDisplay)->rva0008EEF0( start.x - 1, start.y - 1, size.x + 2, size.y + 2, 1, pData->colorBorder );
			}

			if( pData->drawNumber == 1 )
				Rva000A52AEDrawNumber( window, instData, pData );
		}

		//Handle cameo flashing
		if( BitTest( window->winGetStatus(), WIN_STATUS_FLASHING ) && !radial )
		{
			((W3DDisplay *)TheDisplay)->rva0004D6B3( (Image *)hilitedOverlayIcon, start.x, start.y, start.x + size.x, start.y + size.y, -1, DRAW_IMAGE_ALPHA );
		}

		//Now render overlays that pertain to the correct state.
		static Color overlayColor = GameMakeColor( 255, 255, 255, 255 );
		static Color grayOverlayColor = GameMakeColor( 144, 144, 144, 255 );
		Color color = BitTest( window->winGetStatus(), WIN_STATUS_GRAY_OVERLAY ) ? grayOverlayColor : overlayColor;

		if( BitTest( window->winGetStatus(), WIN_STATUS_USE_OVERLAY_STATES ) &&
				BitTest( window->winGetStatus(), WIN_STATUS_ENABLED ) )
		{
			if( BitTest( instData->getState(), WIN_STATE_HILITED ) )
			{
				if( BitTest( instData->getState(), WIN_STATE_SELECTED ) )
				{
					//The button is hilited and pushed
					if( radial )
						drawRadialOverlay( radialPushedIcon, &start, &size, color );
					else
						((W3DDisplay *)TheDisplay)->rva0004D6B3( (Image *)pushedOverlayIcon, start.x, start.y, start.x + size.x, start.y + size.y, color, DRAW_IMAGE_ALPHA );
				}
				else
				{
					//The button is hilited
					if( radial )
						drawRadialOverlay( radialHilitedIcon, &start, &size, color );
					else
						((W3DDisplay *)TheDisplay)->rva0004D6B3( (Image *)hilitedOverlayIcon, start.x, start.y, start.x + size.x, start.y + size.y, color, DRAW_IMAGE_ALPHA );
				}
				return;
			}
			else if( !radial && BitTest( instData->getState(), WIN_STATE_SELECTED ) )
			{
				//The button appears to be pushed -- CHECK_LIKE buttons that are on.
				((W3DDisplay *)TheDisplay)->rva0004D6B3( (Image *)pushedOverlayIcon, start.x, start.y, start.x + size.x, start.y + size.y, color, DRAW_IMAGE_ALPHA );
			}
		}

		if( radial )
			drawRadialOverlay( radialBorderIcon, &start, &size, color );

	}

}  // end W3DGadgetPushButtonImageDrawOne
