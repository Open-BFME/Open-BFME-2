// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// W3DGadgetTextEntryDraw 0x000A03BF (450B) and W3DGadgetTextEntryImageDraw
// 0x000A0581 (748B): Zero Hour's W3DTextEntry.cpp through BFME1's banked
// reconstructions of the same two callbacks (Open-BFME-1 targets/game/reverse/
// attempts/0x00798f30.cpp and 0x007991a0.cpp).
//
// Target evidence: text-entry gadget vtables 0x00BC8C54 and 0x00BC8C80 slot 3
// (W3DGadgetWindowDrawSlots.cpp) call these two. Both clear the user data's
// +0x15 byte, pick the text and IME composite colours exactly as Zero Hour's
// pair does (disabled text colours for both when disabled), size the
// DisplayString at the user data's +0x00 and hand window, text, text border,
// composite, composite border, x and y to 0x0009FE49, Zero Hour's
// drawTextEntryText with the old width/height arguments gone. BFME2 deltas:
// the back and image look-ups read the GameWindow draw data directly, the
// width is still computed into a dead store (kept volatile, as in BFME1), and
// the edit text goes through BFME's DisplayString slots. Built /O1 (x87 fld1
// for the line width, so no /arch:SSE); the coordinate locals carry the empty
// default constructor of W3DCheckBox.cpp, which fixes the operand order of the
// fill rectangle's end.x and of the image-end arithmetic.

#include "unicode_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char Bool;
typedef float Real;
typedef int Color;

class GameFont;

struct ICoord2D
{
	Int x;
	Int y;
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

// BFME DisplayString slots: getSize +0x3C.
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
	virtual void unused08();
	virtual void unused09();
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

	unsigned char m_unreconstructed00[ 0x08 ];
	UnsignedInt m_state;                                   // +0x08
	unsigned char m_unreconstructed0C[ 0x170 ];
	ICoord2D m_imageOffset;                                // +0x17C
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
	Color winGetEnabledTextColor( void );
	Color winGetEnabledTextBorderColor( void );
	Color winGetDisabledTextColor( void );
	Color winGetDisabledTextBorderColor( void );
	Color winGetHiliteTextColor( void );
	Color winGetHiliteTextBorderColor( void );
	Color winGetIMECompositeTextColor( void );
	Color winGetIMECompositeBorderColor( void );

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

// BFME2's EntryData: the three strings lead as in Zero Hour; the byte at
// +0x15 is the one both draw callbacks clear (Zero Hour's receivedUnichar).
struct EntryData
{
	DisplayString *text;                                   // +0x00
	DisplayString *sText;                                  // +0x04
	DisplayString *constructText;                          // +0x08
	unsigned char m_unreconstructed0C[ 0x09 ];
	Bool receivedUnichar;                                  // +0x15
};

enum
{
	WIN_STATUS_ENABLED = 0x00000008,
	WIN_STATUS_ONE_LINE = 0x00004000,
	WIN_STATE_HILITED = 0x00000002,
	WIN_COLOR_UNDEFINED = 0x00FFFFFF
};

inline Int BitTest( UnsignedInt bits, UnsignedInt mask )
{
	return ( bits & mask ) != 0;
}

#define WIN_DRAW_LINE_WIDTH 1.0f
#define FALSE 0

#define GadgetTextEntryGetEnabledColor( window ) ( (window)->m_enabledDrawData[ 0 ].color )
#define GadgetTextEntryGetEnabledBorderColor( window ) ( (window)->m_enabledDrawData[ 0 ].borderColor )
#define GadgetTextEntryGetDisabledColor( window ) ( (window)->m_disabledDrawData[ 0 ].color )
#define GadgetTextEntryGetDisabledBorderColor( window ) ( (window)->m_disabledDrawData[ 0 ].borderColor )
#define GadgetTextEntryGetHiliteColor( window ) ( (window)->m_hiliteDrawData[ 0 ].color )
#define GadgetTextEntryGetHiliteBorderColor( window ) ( (window)->m_hiliteDrawData[ 0 ].borderColor )

#define GadgetTextEntryGetEnabledImageLeft( window ) ( (window)->m_enabledDrawData[ 0 ].image )
#define GadgetTextEntryGetEnabledImageRight( window ) ( (window)->m_enabledDrawData[ 1 ].image )
#define GadgetTextEntryGetEnabledImageCenter( window ) ( (window)->m_enabledDrawData[ 2 ].image )
#define GadgetTextEntryGetEnabledImageSmallCenter( window ) ( (window)->m_enabledDrawData[ 3 ].image )
#define GadgetTextEntryGetDisabledImageLeft( window ) ( (window)->m_disabledDrawData[ 0 ].image )
#define GadgetTextEntryGetDisabledImageRight( window ) ( (window)->m_disabledDrawData[ 1 ].image )
#define GadgetTextEntryGetDisabledImageCenter( window ) ( (window)->m_disabledDrawData[ 2 ].image )
#define GadgetTextEntryGetDisabledImageSmallCenter( window ) ( (window)->m_disabledDrawData[ 3 ].image )
#define GadgetTextEntryGetHiliteImageLeft( window ) ( (window)->m_hiliteDrawData[ 0 ].image )
#define GadgetTextEntryGetHiliteImageRight( window ) ( (window)->m_hiliteDrawData[ 1 ].image )
#define GadgetTextEntryGetHiliteImageCenter( window ) ( (window)->m_hiliteDrawData[ 2 ].image )
#define GadgetTextEntryGetHiliteImageSmallCenter( window ) ( (window)->m_hiliteDrawData[ 3 ].image )

extern GameWindowManager *TheWindowManager;

// Coordinates with an empty default constructor; see W3DCheckBox.cpp.
struct CtorCoord : ICoord2D
{
	CtorCoord() {}
};

void drawTextEntryText( GameWindow *window, Color textColor, Color textDropColor,
	Color compositeColor, Color compositeDropColor, Int x, Int y );

// W3DGadgetTextEntryDraw =====================================================
/** Draw colored entry field using standard graphics */
//=============================================================================
void W3DGadgetTextEntryDraw( GameWindow *window, WinInstanceData *instData )
{
	EntryData *e = (EntryData *)window->winGetUserData();
	CtorCoord origin, size, start, end;
	Color backBorder, backColor, textColor, textBorder,
			compositeColor, compositeBorder;

	// cancel unichar flag
	e->receivedUnichar = FALSE;

	// get size and position of window
	window->winGetScreenPosition( &origin.x, &origin.y );
	window->winGetSize( &size.x, &size.y );

	// get the right colors
	if( BitTest( window->winGetStatus(), WIN_STATUS_ENABLED ) == FALSE )
	{

		compositeColor	= window->winGetDisabledTextColor();
		compositeBorder	= window->winGetDisabledTextBorderColor();
		textColor		= window->winGetDisabledTextColor();
		textBorder	= window->winGetDisabledTextBorderColor();
		backColor		= GadgetTextEntryGetDisabledColor( window );
		backBorder	= GadgetTextEntryGetDisabledBorderColor( window );

	}  // end if, disabled
	else if( BitTest( instData->getState(), WIN_STATE_HILITED ) )
	{

		compositeColor	= window->winGetIMECompositeTextColor();
		compositeBorder	= window->winGetIMECompositeBorderColor();
		textColor		= window->winGetHiliteTextColor();
		textBorder	= window->winGetHiliteTextBorderColor();
		backColor		= GadgetTextEntryGetHiliteColor( window );
		backBorder	= GadgetTextEntryGetHiliteBorderColor( window );

	}  // end else if, hilited
	else
	{

		compositeColor	= window->winGetIMECompositeTextColor();
		compositeBorder	= window->winGetIMECompositeBorderColor();
		textColor		= window->winGetEnabledTextColor();
		textBorder	= window->winGetEnabledTextBorderColor();
		backColor		= GadgetTextEntryGetEnabledColor( window );
		backBorder	= GadgetTextEntryGetEnabledBorderColor( window );

	}  // end else, just enabled

	// draw the back border
	if( backBorder != WIN_COLOR_UNDEFINED )
	{

		start.x = origin.x;
		start.y = origin.y;
		end.x = start.x + size.x;
		end.y = start.y + size.y;
		TheWindowManager->winOpenRect( backBorder, WIN_DRAW_LINE_WIDTH,
																	 start.x, start.y, end.x, end.y );

	}  // end if

	// draw the filled back
	if( backColor != WIN_COLOR_UNDEFINED )
	{

		start.x = origin.x + 1;
		start.y = origin.y + 1;
		end.x = start.x + size.x - 2;
		end.y = start.y + size.y - 2;
		TheWindowManager->winFillRect( backColor, WIN_DRAW_LINE_WIDTH,
																	 start.x, start.y, end.x, end.y );

	}  // end if

	// draw the text
	Int textWidth, fontHeight;
	e->text->getSize( &textWidth, &fontHeight );
	Int startOffset = 5;
	volatile Int width;

	width = size.x - (2 * startOffset);
	start.x = origin.x + startOffset;  // offset a little bit into the entry
	if( BitTest( window->winGetStatus(), WIN_STATUS_ONE_LINE ) )
		start.y = size.y / 2 - (fontHeight + 1) / 2;
	else
		start.y = origin.y + startOffset;  // offset a little bit into the entry

	// draw the edit text
	drawTextEntryText( window, textColor, textBorder, compositeColor, compositeBorder,
										 start.x, start.y );

}  // end W3DGadgetTextEntryDraw

// W3DGadgetTextEntryImageDraw ================================================
/** Draw horizontal slider with user supplied images */
//=============================================================================
void W3DGadgetTextEntryImageDraw( GameWindow *window, WinInstanceData *instData )
{
	EntryData *e = (EntryData *)window->winGetUserData();
	CtorCoord origin, size, start, end;
	Color textColor, textBorder;
	Color compositeColor, compositeBorder;
	const Image *leftImage, *rightImage, *centerImage, *smallCenterImage;
	Int xOffset, yOffset;
	Int i;

	// cancel unichar flag
	e->receivedUnichar = FALSE;

	// get size and position of window
	window->winGetScreenPosition( &origin.x, &origin.y );
	window->winGetSize( &size.x, &size.y );

	// get image offset
	xOffset = instData->m_imageOffset.x;
	yOffset = instData->m_imageOffset.y;

	// get the right colors
	if( BitTest( window->winGetStatus(), WIN_STATUS_ENABLED ) == FALSE )
	{

		textColor					= window->winGetDisabledTextColor();
		textBorder				= window->winGetDisabledTextBorderColor();
		compositeColor		= window->winGetDisabledTextColor();
		compositeBorder		= window->winGetDisabledTextBorderColor();
		leftImage					= GadgetTextEntryGetDisabledImageLeft( window );
		rightImage				= GadgetTextEntryGetDisabledImageRight( window );
		centerImage				= GadgetTextEntryGetDisabledImageCenter( window );
		smallCenterImage	= GadgetTextEntryGetDisabledImageSmallCenter( window );

	}  // end if, disabled
	else if( BitTest( instData->getState(), WIN_STATE_HILITED ) )
	{

		textColor					= window->winGetHiliteTextColor();
		textBorder				= window->winGetHiliteTextBorderColor();
		compositeColor		= window->winGetIMECompositeTextColor();
		compositeBorder		= window->winGetIMECompositeBorderColor();
		leftImage					= GadgetTextEntryGetHiliteImageLeft( window );
		rightImage				= GadgetTextEntryGetHiliteImageRight( window );
		centerImage				= GadgetTextEntryGetHiliteImageCenter( window );
		smallCenterImage	= GadgetTextEntryGetHiliteImageSmallCenter( window );

	}  // end else if, hilited
	else
	{

		textColor					= window->winGetEnabledTextColor();
		textBorder				= window->winGetEnabledTextBorderColor();
		compositeColor		= window->winGetIMECompositeTextColor();
		compositeBorder		= window->winGetIMECompositeBorderColor();
		leftImage					= GadgetTextEntryGetEnabledImageLeft( window );
		rightImage				= GadgetTextEntryGetEnabledImageRight( window );
		centerImage				= GadgetTextEntryGetEnabledImageCenter( window );
		smallCenterImage	= GadgetTextEntryGetEnabledImageSmallCenter( window );

	}  // end else, just enabled

	if( leftImage && rightImage )
	{

		// get image sizes for the ends
		CtorCoord leftSize, rightSize;
		leftSize.x = leftImage->getImageWidth();
		leftSize.y = leftImage->getImageHeight();
		rightSize.x = rightImage->getImageWidth();
		rightSize.y = rightImage->getImageHeight();

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

		// how many whole repeating pieces will fit in that width
		pieces = centerWidth / centerImage->getImageWidth();

		// draw the pieces
		start.x = leftEnd.x;
		start.y = origin.y + yOffset;
		end.y = start.y + size.y;
		for( i = 0; i < pieces; i++ )
		{

			end.x = start.x + centerImage->getImageWidth();
			TheWindowManager->winDrawImage( centerImage,
																			start.x, start.y,
																			end.x, end.y );
			start.x += centerImage->getImageWidth();

		}  // end for i

		//
		// how many small repeating pieces will fit in the gap from where the
		// center repeating bar stopped and the right image, draw them
		// and overlapping underneath where the right end will go
		//
		centerWidth = rightStart.x - start.x;
		pieces = centerWidth / smallCenterImage->getImageWidth() + 1;
		end.y = start.y + size.y;
		for( i = 0; i < pieces; i++ )
		{

			end.x = start.x + smallCenterImage->getImageWidth();
			TheWindowManager->winDrawImage( smallCenterImage,
																			start.x, start.y,
																			end.x, end.y );
			start.x += smallCenterImage->getImageWidth();

		}  // end for i

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

	}  // end if

	// draw the text
	Int textWidth, fontHeight;
	e->text->getSize( &textWidth, &fontHeight );
	Int startOffset = 5;
	volatile Int width;

	width = size.x - (2 * startOffset);
	start.x = origin.x + startOffset;  // offset a little bit into the entry
	if( BitTest( window->winGetStatus(), WIN_STATUS_ONE_LINE ) )
		start.y = size.y / 2 - (fontHeight + 1) / 2;
	else
		start.y = origin.y + startOffset;  // offset a little bit into the entry

	// draw the edit text
	drawTextEntryText( window, textColor, textBorder, compositeColor, compositeBorder,
										 start.x, start.y );

}  // end W3DGadgetTextEntryImageDraw
