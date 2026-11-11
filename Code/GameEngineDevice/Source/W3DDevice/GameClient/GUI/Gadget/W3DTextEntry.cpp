// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// platformsdk
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
//
// drawTextEntryText 0x0009FE49 (1398B) follows Zero Hour's IME composition
// block, then draws BFME2's selection-aware layout: the text scrolled to the
// first character in view (+0x24), the part before the selection, the IME
// composition at the cursor, the selection over a filled focus box in the
// inverted drop colour (0x0009FE01), the timeGetTime-blinking cursor and the
// rest of the text.
// Its only native callers are the two callbacks in this unit (direct calls
// at 0x000A0575 and 0x000A0860). Internal linkage reproduces its argument
// homes without an artificial x-dependent font comparison; the corresponding
// BFME1 helper uses this linkage at Open-BFME-1 revision 4483e88.

#include "unicode_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned short WideChar;
typedef unsigned char Bool;
typedef float Real;
typedef int Color;

// Only the height is read here, at +0x10.
#include "../../../../../../GameEngine/Include/GameClient/GameFontClass.h"

#include "../../../../../../Libraries/Include/Lib/ICoord2D.h"
#include "../../../../../../Libraries/Include/Lib/IRegion2D.h"

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

// BFME DisplayString slots: setText +0x04, getTextLength +0x0C, setFont +0x18,
// getFont +0x1C, setTextColor +0x28, a two-coordinate draw with the colours
// already set +0x34, draw +0x38, getSize +0x3C, getWidth +0x40,
// setClipRegion +0x50 and appendChar +0x58.
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
	virtual void drawAt( Int x, Int y );
	virtual void draw( Int x, Int y, Int xDrop, Int yDrop );
	virtual void getSize( Int *width, Int *height );
	virtual Int getWidth( Int charPos = -1 );
	virtual void unused17();
	virtual void unused18();
	virtual void unused19();
	virtual void setClipRegion( IRegion2D *region );
	virtual void unused21();
	virtual void appendChar( WideChar c );
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

#include "../../../../../../GameEngine/Include/GameClient/WinDrawData.h"

// The enabled, disabled and hilite draw data sit at +0x48, +0xB4 and +0x120.
class GameWindow
{
public:
	Int winGetScreenPosition( Int *x, Int *y );
	Int winGetSize( Int *width, Int *height );
	UnsignedInt winGetStatus( void );
	void *winGetUserData( void );
	UnsignedInt winGetStyle( void );
	GameWindow *winGetParent( void );
	GameFont *winGetFont( void );
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

#include "../../../../../../GameEngine/Include/GameClient/GameWindowManager.h"

// IMEManager slots: isAttachedTo +0x4C, isComposing +0x54,
// getCompositionString +0x58, getCompositionCursorPosition +0x5C.
#include "../../../../../../GameEngine/Include/GameClient/IMEManagerClass.h"

// BFME2's EntryData: the three strings lead as in Zero Hour; the byte at
// +0x15 is the one both draw callbacks clear (Zero Hour's receivedUnichar).
// The cursor and the other end of the selection are character indices at
// +0x1C and +0x1E, and +0x24 is the first character in view.
struct EntryData
{
	DisplayString *text;                                   // +0x00
	DisplayString *sText;                                  // +0x04
	DisplayString *constructText;                          // +0x08
	unsigned char m_unreconstructed0C[ 0x06 ];
	Bool secretText;                                       // +0x12
	unsigned char m_unreconstructed13[ 0x02 ];
	Bool receivedUnichar;                                  // +0x15
	unsigned char m_unreconstructed16[ 0x06 ];
	UnsignedShort charPos;                                 // +0x1C
	UnsignedShort selectPos;                               // +0x1E
	unsigned char m_unreconstructed20[ 0x04 ];
	Int scrollPos;                                         // +0x24
};

enum
{
	WIN_STATUS_ENABLED = 0x00000008,
	WIN_STATUS_ONE_LINE = 0x00004000,
	WIN_STATE_HILITED = 0x00000002,
	GWS_COMBO_BOX = 0x00008000,
	WIN_COLOR_UNDEFINED = 0x00FFFFFF
};

// min and max in the ternary form of the matched min<int>/max<int> and
// max<unsigned> providers (cmovge/cmovle leaves at 0x57B0, 0x57C0, 0x9FDE5);
// min<unsigned> 0x9FDD5 is rowed here, the unit that calls it.
template <class T> inline const T& min( const T& lhs, const T& rhs )
{
	return lhs < rhs ? lhs : rhs;
}

template <class T> inline const T& max( const T& lhs, const T& rhs )
{
	return lhs > rhs ? lhs : rhs;
}

inline Int BitTest( UnsignedInt bits, UnsignedInt mask )
{
	return ( bits & mask ) != 0;
}

#define WIN_DRAW_LINE_WIDTH 1.0f
#define NOMINMAX
#include <windows.h>

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

// GameWindow::winSetCursorPosition 0x00313B0A (rowed under this view name).
class Rva00478180
{
public:
	Int set( Int x, Int y );
};

extern GameWindowManager *TheWindowManager;
extern IMEManager *TheIMEManager;

// Inverts a colour's RGB and keeps its alpha (color_ops.cpp).
Color Rva0009FE01Get( Color color );

// Coordinates with an empty default constructor; see W3DCheckBox.cpp.
#include "../../../../../../GameEngine/Include/Common/CtorCoord.h"

// drawTextEntryText ==========================================================
/** Draw the text of a text entry: the part before the selection, the IME
	* composition at the cursor, the selection inverted over a filled box, the
	* blinking cursor and the rest. Retail 0x0009FE49 (1398B). */
//=============================================================================
static void drawTextEntryText( GameWindow *window, Color textColor, Color textDropColor,
												Color compositeColor, Color compositeDropColor,
												Int x, Int y )
{
	EntryData *entryData = (EntryData *)window->winGetUserData();
	Int cursorPos;
	Int compositeCursorPos = 0;
	DisplayString *text = entryData->text;
	IRegion2D clipRegion, box;
	CtorCoord origin, size;

	// Check to see if the IME manager is composing text
	entryData->constructText->setText( UnicodeString::TheEmptyString );
	if( TheIMEManager && TheIMEManager->isAttachedTo( window ) && TheIMEManager->isComposing() )
	{
		// The user is composing a string.
		// Show the composition in the text gadget.
		UnicodeString composition;

		TheIMEManager->getCompositionString( composition );

		if( entryData->secretText )
		{
			entryData->sText->setText( UnicodeString::TheEmptyString );
			Int len = composition.getLength() + entryData->text->getTextLength();
			for( int i = 0; i < len; i++ )
				entryData->sText->appendChar( '*' );
		}
		else
		{
			entryData->constructText->setText( composition );
			compositeCursorPos = TheIMEManager->getCompositionCursorPosition();
		}

	}

	// get out of here if no text color to show up
	if( textColor == WIN_COLOR_UNDEFINED )
		return;

	// if our text is "secret" we will print only '*' characters
	if( entryData->secretText )
		text = entryData->sText;

	// Make sure our font is the same as our parent's.
	if( text->getFont() != window->winGetFont() )
		text->setFont( window->winGetFont() );
	if( entryData->constructText->getFont() != window->winGetFont() )
		entryData->constructText->setFont( window->winGetFont() );

	// clip the text to the edit window
	window->winGetScreenPosition( &origin.x, &origin.y );
	window->winGetSize( &size.x, &size.y );
	clipRegion.lo.x = origin.x;
	clipRegion.hi.x = origin.x + size.x;
	clipRegion.lo.y = origin.y;
	clipRegion.hi.y = origin.y + size.y;
	IRegion2D region = clipRegion;
	Int textWidth = text->getWidth( entryData->charPos );

	// scroll the text so the first character in view starts the entry
	x += 2 - text->getWidth( entryData->scrollPos );
	cursorPos = x;

	UnsignedInt selectPos = entryData->selectPos;
	UnsignedInt charPos = entryData->charPos;
	UnsignedInt selStart = min( selectPos, charPos );
	UnsignedInt selEnd = max( selectPos, charPos );
	Int height = max( size.y - 4, window->winGetFont()->height );

	// draw the text before the selection
	if( selStart > 0 )
	{
		Int width = text->getWidth( selStart );
		region.hi.x = min( clipRegion.hi.x, x + width );
		text->setClipRegion( &region );
		text->setTextColor( textColor, textDropColor );
		text->draw( x, y, 1, 1 );
		x += width;
		cursorPos += width;
	}

	// draw the composition at the cursor
	if( entryData->constructText->getTextLength() > 0 && charPos == selStart )
	{
		entryData->constructText->setClipRegion( &clipRegion );
		entryData->constructText->setTextColor( compositeColor, compositeDropColor );
		entryData->constructText->draw( x, y, 1, 1 );
		cursorPos += entryData->constructText->getWidth( compositeCursorPos );
		x += entryData->constructText->getWidth();
	}

	// draw the selection
	if( selEnd > selStart )
	{
		Int width = text->getWidth( selEnd ) - text->getWidth( selStart );

		// the selection box shows only while we (or our combo box) have the focus
		GameWindow *parent;
		parent = window->winGetParent();
		if( parent && !BitTest( parent->winGetStyle(), GWS_COMBO_BOX ) )
			parent = NULL;

		if( window == TheWindowManager->winGetFocus() || ( parent && parent == TheWindowManager->winGetFocus() ) )
		{
			box.lo.x = max( x, origin.x );
			box.lo.y = origin.y + 2;
			box.hi.x = min( x + width, origin.x + size.x );
			box.hi.y = origin.y + height + 2;
			if( box.lo.x < box.hi.x )
				TheWindowManager->winFillRect( textColor, WIN_DRAW_LINE_WIDTH,
																			 box.lo.x, box.lo.y, box.hi.x, box.hi.y );
		}

		region.lo.x = max( clipRegion.lo.x, x );
		region.hi.x = min( clipRegion.hi.x, x + width );
		text->setClipRegion( &region );
		text->setTextColor( 0xFF000000, Rva0009FE01Get( textDropColor ) );
		text->drawAt( x - text->getWidth( selStart ), y );
		x += width;

		// the cursor sits at the end of the selection
		if( selEnd == charPos )
		{
			cursorPos += width;
			if( entryData->constructText->getTextLength() > 0 )
			{
				Int compositeWidth = entryData->constructText->getWidth( compositeCursorPos );
				entryData->constructText->setTextColor( compositeColor, compositeDropColor );
				entryData->constructText->draw( x, y, 1, 1 );
				cursorPos += entryData->constructText->getWidth( compositeCursorPos );
				x += entryData->constructText->getWidth();
			}
		}

	}

	// draw blinking cursor
	GameWindow *parent;
	parent = window->winGetParent();
	if( parent && !BitTest( parent->winGetStyle(), GWS_COMBO_BOX ) )
		parent = NULL;

	if( ( window == TheWindowManager->winGetFocus() || ( parent && parent == TheWindowManager->winGetFocus() ) ) && ( timeGetTime() & 0x200 ) )
		TheWindowManager->winFillRect( textColor, WIN_DRAW_LINE_WIDTH,
																	 cursorPos, origin.y + 2,
																	 cursorPos + 3, origin.y + height + 2 );
	((Rva00478180 *)window)->set( cursorPos + 2 - origin.x, 0 );

	// draw the text after the selection
	if( selEnd < text->getTextLength() )
	{
		region.lo.x = max( clipRegion.lo.x, x );
		region.hi.x = clipRegion.hi.x;
		Int width = text->getWidth( selEnd );
		text->setClipRegion( &region );
		text->setTextColor( textColor, textDropColor );
		text->draw( x - width, y, 1, 1 );
	}

}  // end drawTextEntryText

// W3DGadgetTextEntryDraw =====================================================
/** Draw colored entry field using standard graphics */
//=============================================================================
void W3DGadgetTextEntryDraw( GameWindow *window, WinInstanceData *instData )
{
	EntryData *entryData = (EntryData *)window->winGetUserData();
	CtorCoord origin, size, start, end;
	Color backBorder, backColor, textColor, textBorder,
			compositeColor, compositeBorder;

	// cancel unichar flag
	entryData->receivedUnichar = FALSE;

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
	entryData->text->getSize( &textWidth, &fontHeight );
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
	EntryData *entryData = (EntryData *)window->winGetUserData();
	CtorCoord origin, size, start, end;
	Color textColor, textBorder;
	Color compositeColor, compositeBorder;
	const Image *leftImage, *rightImage, *centerImage, *smallCenterImage;
	Int xOffset, yOffset;
	Int i;

	// cancel unichar flag
	entryData->receivedUnichar = FALSE;

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
	entryData->text->getSize( &textWidth, &fontHeight );
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
