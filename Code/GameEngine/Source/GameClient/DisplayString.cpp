// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// FILE: DisplayString.cpp
// Ported from Zero Hour's GameEngine/Source/GameClient/DisplayString.cpp
// (GeneralsMD tree vendored under reference/open-bfme-1/inputs/reference).
//
// BFME 2 unit at 0x00358933-0x00358A53, vftable ??_7DisplayString 0x00C15338
// (installed by the constructor at 0x0035897D). The table drops ZH's
// MemoryPoolObject glue: slot 0 is the virtual destructor. Its order is ZH's
// with the six-argument draw gone, three colour setters and a two-argument
// draw added after setWordWrapCentered, two float setters after getWidth, and
// one BFME 2 virtual after appendChar that appends a whole string (slot 23).

class GameFont;
struct IRegion2D;
#include "unicode_string.h"

typedef int Int;
typedef int Color;
typedef bool Bool;
typedef unsigned short WideChar;

class DisplayString
{
public:
	DisplayString( void );
	virtual ~DisplayString( void );

	virtual void setText( UnicodeString text );
	virtual UnicodeString getText( void );
	virtual Int getTextLength( void );
	virtual void notifyTextChanged( void ) {}
	virtual void reset( void );
	virtual void setFont( GameFont *font ) { m_font = font; }
	virtual GameFont *getFont( void ) { return m_font; }
	virtual void setWordWrap( Int wordWrap ) = 0;
	virtual void setWordWrapCentered( Bool isCentered ) = 0;
	virtual void setColors( Color textColor, Color dropColor ) = 0;
	virtual void setTextColor( Color *colors ) = 0;
	virtual void setDropColor( Color *colors ) = 0;
	virtual void draw( Int x, Int y, Color color, Color dropColor ) = 0;
	virtual void draw( Int x, Int y ) = 0;
	virtual void getSize( Int *width, Int *height ) = 0;
	virtual Int getWidth( Int charPos = -1 ) = 0;
	virtual void bfmeSetFloats17( float a, float b ) = 0;
	virtual void bfmeSetFloats18( float a, float b ) = 0;
	virtual void setUseHotkey( Bool useHotkey, Color hotKeyColor ) = 0;
	virtual void setClipRegion( IRegion2D *region ) {}
	virtual void removeLastChar( void );
	virtual void appendChar( WideChar c );
	virtual void appendString( const UnicodeString &text );

protected:
	UnicodeString m_textString;											///< 0x04
	GameFont *m_font;																///< 0x08
	DisplayString *m_next;													///< 0x0C
	DisplayString *m_prev;													///< 0x10
};

// DisplayString::DisplayString ===============================================
/** */
//=============================================================================
DisplayString::DisplayString( void )
{
	// m_textString = "";	// not necessary, done by default
	m_font = 0;
	m_next = 0;
	m_prev = 0;

}  // end DisplayString

// DisplayString::~DisplayString ==============================================
/** */
//=============================================================================
DisplayString::~DisplayString( void )
{

	// free any data
	reset();

}  // end ~DisplayString

// DisplayString::setText =====================================================
/** Copy the text to this instance */
//=============================================================================
void DisplayString::setText( UnicodeString text )
{
	if( text.compare( m_textString ) != 0 )
	{
		m_textString.set( text );

		// our text has now changed
		notifyTextChanged();
	}

}  // end setText

// DisplayString::reset =======================================================
/** Free and reset all the data for this string, effectively making this
	* instance like brand new */
//=============================================================================
void DisplayString::reset( void )
{

	m_textString.clear();

	// no font
	m_font = 0;

}  // end reset

// DisplayString::removeLastChar ==============================================
/** Remove the last character from the string text */
//=============================================================================
void DisplayString::removeLastChar( void )
{

	m_textString.removeLastChar();

	// our text has now changed
	notifyTextChanged();

}  // end removeLastChar

// DisplayString::appendChar ==================================================
/** Append character to the end of the string */
//=============================================================================
void DisplayString::appendChar( WideChar c )
{

	// UnicodeString::operator+=( WideChar ), expanded inline in retail
	WideChar text = c;
	m_textString.concat( &text, 1 );

	// text has now changed
	notifyTextChanged();

}  // end appendchar

// DisplayString::appendString ================================================
/** BFME 2 (vftable slot 23): append a whole string to the end */
//=============================================================================
void DisplayString::appendString( const UnicodeString &text )
{

	m_textString += text;

	// text has now changed
	notifyTextChanged();

}  // end appendString
