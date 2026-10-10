// ?drawTextEntryText@@YAXPAVGameWindow@@HHHHHH@Z
// partial score=0.9698002111250066 date=2026-10-10
// ?drawTextEntryText@@YAXPAVGameWindow@@HHHHHH@Z
// partial score=0.98 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// NEAR draft for 0x0009FE49 drawTextEntryText (1398B), built from the
// banked reverse/attempts/0x0009fe49.cpp. Changes: non-static (callers in
// W3DTextEntry.cpp declare it extern), region flags /O1 /G7 /arch:SSE, and
// winSetCursorPosition called through its rowed name ?set@Rva00478180@@QAEHHH@Z
// (0x00313B0A has no winSetCursorPosition pin). Writing the first block's
// cursor update as "cursorPos += width" (not "cursorPos = x") flips the
// register allocation to retail's (param x cached in EDI with write-through
// and cursorPos memory-only at [ebp-0x10]) without volatile. Residue (1393B vs
// 1398B): after each "x += width" retail reloads the x+width temp through EAX
// (first block: mov eax,[tv] / store x / store cursorPos / mov edi,eax;
// selection block: x stays memory-only through the nested composition draw
// and is reloaded into EDI at the join) while cl loads it straight into EDI.
#include "unicode_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned short WideChar;
typedef unsigned char Bool;
typedef float Real;
typedef int Color;

// Only the height is read here, at +0x10.
class GameFont
{
public:
	unsigned char m_unreconstructed00[ 0x10 ];
	Int height;                                            // +0x10
};

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
	UnsignedInt winGetStyle( void );
	GameWindow *winGetParent( void );
	GameFont *winGetFont( void );
	Int winSetCursorPosition( Int x, Int y );
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
	virtual GameWindow *winGetFocus( void );                // +0xC0
	virtual void unused49(); virtual void unused50(); virtual void unused51();
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

// IMEManager slots: isAttachedTo +0x4C, isComposing +0x54,
// getCompositionString +0x58, getCompositionCursorPosition +0x5C.
class IMEManager
{
public:
	virtual void unused00(); virtual void unused01(); virtual void unused02(); virtual void unused03();
	virtual void unused04(); virtual void unused05(); virtual void unused06(); virtual void unused07();
	virtual void unused08(); virtual void unused09(); virtual void unused10(); virtual void unused11();
	virtual void unused12(); virtual void unused13(); virtual void unused14(); virtual void unused15();
	virtual void unused16S(); virtual void unused17S(); virtual void unused18S();
	virtual Bool isAttachedTo( GameWindow *window );
	virtual void unused20();
	virtual Bool isComposing( void );
	virtual void getCompositionString( UnicodeString &string );
	virtual Int getCompositionCursorPosition( void );
};

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

// WWLib's always.h min and max.
template <class T> inline const T& min( const T& a, const T& b )
{
	if( a < b ) {
		return a;
	} else {
		return b;
	}
}

template <class T> inline const T& max( const T& a, const T& b )
{
	if( a > b ) {
		return a;
	} else {
		return b;
	}
}

inline Int BitTest( UnsignedInt bits, UnsignedInt mask )
{
	return ( bits & mask ) != 0;
}

#define WIN_DRAW_LINE_WIDTH 1.0f
#define FALSE 0
#define NULL 0

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

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime( void );

// Inverts a colour's RGB and keeps its alpha (color_ops.cpp).
Color Rva0009FE01Get( Color color );

// Coordinates with an empty default constructor; see W3DCheckBox.cpp.
struct CtorCoord : ICoord2D
{
	CtorCoord() {}
};

// drawTextEntryText ==========================================================
/** Draw the text of a text entry: the part before the selection, the IME
  * composition at the cursor, the selection inverted over a filled box, the
  * blinking cursor and the rest */
//=============================================================================
__forceinline Int getEntryAdvance(const Int& v) { return v; }
void drawTextEntryText( GameWindow *window, Color textColor, Color textDropColor,
															 Color compositeColor, Color compositeDropColor,
															 Int x, Int y )
{
	EntryData *e = (EntryData *)window->winGetUserData();
	Int cursorPos;
	Int compositeCursorPos = 0;
	DisplayString *text = e->text;
	IRegion2D clipRegion, box;
	CtorCoord origin, size;

	// Check to see if the IME manager is composing text
	e->constructText->setText( UnicodeString::TheEmptyString );
	if( TheIMEManager && TheIMEManager->isAttachedTo( window ) && TheIMEManager->isComposing() )
	{
		// The user is composing a string.
		// Show the composition in the text gadget.
		UnicodeString composition;

		TheIMEManager->getCompositionString( composition );

		if( e->secretText )
		{
			e->sText->setText( UnicodeString::TheEmptyString );
			Int len = composition.getLength() + e->text->getTextLength();
			for( int i = 0; i < len; i++ )
			{
				e->sText->appendChar( '*' );
			}
		}
		else
		{
			e->constructText->setText( composition );
			compositeCursorPos = TheIMEManager->getCompositionCursorPosition();
		}

	}

	// get out of here if no text color to show up
	if( textColor == WIN_COLOR_UNDEFINED )
		return;

	// if our text is "secret" we will print only '*' characters
	if( e->secretText )
		text = e->sText;

	// make sure our font is the same as our parents
	if( text->getFont() != window->winGetFont() )
		text->setFont( window->winGetFont() );
	if( e->constructText->getFont() != window->winGetFont() )
		e->constructText->setFont( window->winGetFont() );

	// clip the text to the edit window
	window->winGetScreenPosition( &origin.x, &origin.y );
	window->winGetSize( &size.x, &size.y );
	clipRegion.lo.x = origin.x;
	clipRegion.hi.x = origin.x + size.x;
	clipRegion.lo.y = origin.y;
	clipRegion.hi.y = origin.y + size.y;
	IRegion2D region = clipRegion;

	Int textWidth = text->getWidth( e->charPos );

	// scroll the text so the first character in view starts the entry
	x += 2 - text->getWidth( e->scrollPos );
	cursorPos = x;

	UnsignedInt selectPos = e->selectPos;
	UnsignedInt charPos = e->charPos;
	UnsignedInt selStart = min( selectPos, charPos );
	UnsignedInt selEnd = max( selectPos, charPos );
	Int height = max( size.y - 4, window->winGetFont()->height );

	// draw the text before the selection
	if( selStart > 0 )
	{
		Int width = text->getWidth( selStart );

		Int nextX=x+width; region.hi.x = min( clipRegion.hi.x, nextX );
		text->setClipRegion( &region );
		text->setTextColor( textColor, textDropColor );
		text->draw( x, y, 1, 1 );
		x = nextX;
		cursorPos += width;
	}

	// draw the composition at the cursor
	if( e->constructText->getTextLength() > 0 && charPos == selStart )
	{
		e->constructText->setClipRegion( &clipRegion );
		e->constructText->setTextColor( compositeColor, compositeDropColor );
		e->constructText->draw( x, y, 1, 1 );
		cursorPos += e->constructText->getWidth( compositeCursorPos );
		x += e->constructText->getWidth();
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
			if( e->constructText->getTextLength() > 0 )
			{
				Int compositeWidth = e->constructText->getWidth( compositeCursorPos );
				e->constructText->setTextColor( compositeColor, compositeDropColor );
				e->constructText->draw( x, y, 1, 1 );
				cursorPos += e->constructText->getWidth( compositeCursorPos );
				x += e->constructText->getWidth();
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


