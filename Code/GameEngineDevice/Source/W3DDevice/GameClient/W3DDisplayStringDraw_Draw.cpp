// cl: /O1 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// Split from W3DDisplayStringDraw.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
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

// W3DDisplayString's BFME 2 draw pair, from Zero Hour's draw( x, y, color,
// dropColor, xDrop, yDrop ): retail 0x00106277 rebuilds the sentences when the
// text or font changed (and flags new polys when the colour callback's value
// for the first text colour changes); retail 0x00106405 is the vftable's
// four-argument draw (the two-argument draw 0x00105E65 forwards to it with
// zero offsets) drawing four-colour sentences. Declarations follow
// W3DDisplayStringWordWrap.cpp, itself ported from Zero Hour's
// GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayString.cpp and the
// inline Render2DSentenceClass::Set_Wrapping_Width of WW3D2/render2dsentence.h
// (GeneralsMD tree vendored under reference/open-bfme-1/inputs/reference).
//
// Built on the BFME 2 layout of W3DDisplayStringComputeExtents.cpp (renderers
// at +0x14/+0xD8, m_textChanged at +0x1A0); the ZH-layout W3DDisplayString.cpp
// beside this file places them elsewhere. In the 0xC4-byte BFME 2
// Render2DSentenceClass the wrap width sits at +0x84 and the hard-wrap flag at
// +0xAE. The class views below are W3DDisplayString.cpp's, verbatim, so the
// three units compose into that retail TU.

#include "ascii_string.h"
#include "unicode_string.h"
#include "../../../../Libraries/Include/Lib/ICoord2D.h"
#include "../../../../Libraries/Include/Lib/IRegion2D.h"
#include "../../../../../reference/shims/wwmath/Vector2.h"

typedef bool Bool;

typedef int Int;

typedef int Color;

class GameFont;

class FontCharsClass
{
public:
 int Get_Char_Spacing(unsigned short ch);
};

class RectClass
{
public:
	RectClass( float left, float top, float right, float bottom ) : Left( left ), Top( top ), Right( right ), Bottom( bottom ) {}
	float Left;
	float Top;
	float Right;
	float Bottom;
	RectClass &operator=( const RectClass &r );
};

class DisplayString
{
public:
	DisplayString();
	virtual ~DisplayString();
	virtual void setText( UnicodeString text );
	virtual UnicodeString getText( void );
	virtual Int getTextLength( void );
	virtual void notifyTextChanged( void );
	virtual void reset( void );
	virtual void setFont( GameFont *font ) { m_font = font; }
	virtual GameFont *getFont( void );
	virtual void setWordWrap( Int wordWrap ) = 0;
	virtual void setWordWrapCentered( Bool isCentered ) = 0;
	virtual void setColors( Color textColor, Color dropColor ) = 0;
	virtual void setTextColor( Color *colors ) = 0;
	virtual void setDropColor( Color *colors ) = 0;
	// MSVC lays out overloaded virtuals in reverse declaration order: the
	// two-argument draw is slot 13, the four-argument draw slot 14.
	virtual void draw( Int x, Int y, Color color, Color dropColor ) = 0;
	virtual void draw( Int x, Int y ) = 0;
	virtual void getSize( Int *width, Int *height ) = 0;
	virtual Int getWidth( Int charPos = -1 ) = 0;
	virtual void bfmeSetFloats17( float a, float b ) = 0;
	virtual void bfmeSetFloats18( float a, float b ) = 0;
	virtual void setUseHotkey( Bool useHotkey, Color hotKeyColor ) = 0;
	virtual void setClipRegion( IRegion2D *region );
	virtual void removeLastChar( void );
	virtual void appendChar( wchar_t c );
	virtual void appendString( const UnicodeString &text );
protected:
	UnicodeString m_textString;
	GameFont *m_font;
	DisplayString *m_next;
	DisplayString *m_prev;
};

class Gen_00942BC0 { public: void process( void *text, void *hkX, void *hkY ); };
class Rva00155AD0 { public: void rva00155AD0( void ); };

class Render2DSentenceClass
{
public:
	Render2DSentenceClass();
	~Render2DSentenceClass();
	Vector2 Get_Formatted_Text_Extents(const unsigned short *text);
	FontCharsClass *Peek_Font() { return Font; }
	bool Set_Word_Wrap_Centered(bool centered)
	{
		if (IsWordWrapCentered == centered)
			return false;
		IsWordWrapCentered = centered;
		return true;
	}
	virtual void Reset();
	bool	Set_Wrapping_Width (float width)					{ if(WrapWidth == width)
																											return false;
																										WrapWidth = width; 
																										return true;	}
	void Set_Use_Hard_Word_Wrap( bool onoff ) { UseHardWordWrap = onoff; }
	void Set_Hot_Key_Parse( bool parseHotKey ) { ParseHotKey = parseHotKey; }
	void Set_Font( FontCharsClass *font );
	void	Set_Clipping_Rect( const RectClass &rect )	{ ClipRect = rect; IsClippedEnabled = true; }
	// Rowed under address-derived names: Build_Sentence 0x00159FC0 and Render
	// 0x00155AD0; the four-colour Draw_Sentence 0x00155B00 is pinned.
	void Build_Sentence( const wchar_t *text, Int *hkX, Int *hkY )
	{ reinterpret_cast<Gen_00942BC0 *>(this)->process( (void *)text, hkX, hkY ); }
	void Reset_Polys( void );
	void Set_Location( const Vector2 &loc );
	void Draw_Sentence( unsigned long c0, unsigned long c1, unsigned long c2, unsigned long c3 );
	void Render( void ) { reinterpret_cast<Rva00155AD0 *>(this)->rva00155AD0(); }
private:
	char m_unrecovered04[ 0x4C - 0x04 ];
	FontCharsClass *Font;
	char m_unrecovered50[ 0x84 - 0x50 ];
	float WrapWidth;																		///< 0x84
	bool IsWordWrapCentered;
	char m_unrecovered89[ 0x8C - 0x89 ];
	RectClass ClipRect;																	///< 0x8C
	char m_unrecovered9C[ 0xAC - 0x9C ];
	bool IsClippedEnabled;															///< 0xAC
	bool ParseHotKey;																		///< 0xAD
	bool UseHardWordWrap;																///< 0xAE
	char m_unrecoveredAF[ 0xC4 - 0xAF ];
};

class W3DDisplayString : public DisplayString
{
public:
	W3DDisplayString();
	virtual ~W3DDisplayString();
	virtual void reset();
	virtual Int getWidth(Int charPos = -1);
	virtual void setWordWrapCentered(Bool isCentered);
	virtual void notifyTextChanged();
	virtual void setWordWrap( Int wordWrap );
	virtual void setFont( GameFont *font );
	virtual void setColors( Color textColor, Color dropColor );
	virtual void setTextColor( Color *colors );
	virtual void setDropColor( Color *colors );
	virtual void draw( Int x, Int y );
	virtual void draw( Int x, Int y, Color color, Color dropColor );
	virtual void getSize( Int *width, Int *height );
	virtual void setUseHotkey( Bool useHotkey, Color hotKeyColor );
	virtual void setClipRegion( IRegion2D *region );
protected:
	void computeExtents();
public:
	Bool rva00106277( void );
private:
	Render2DSentenceClass m_textRenderer;								///< 0x14
	Render2DSentenceClass m_textRendererHotKey;					///< 0xD8
	UnicodeString m_hotkey;															///< 0x19C
	Bool m_textChanged;																	///< 0x1A0
	Bool m_fontChanged;																	///< 0x1A1
	Bool m_bfmeColorsChanged;														///< 0x1A2
	Bool m_useHotKey;																		///< 0x1A3
	ICoord2D m_hotKeyPos;																///< 0x1A4
	ICoord2D m_textPos;																	///< 0x1AC
	Color m_hotKeyColor;																///< 0x1B4
	Color m_textColors[ 4 ];														///< 0x1B8
	Color m_dropColors[ 4 ];														///< 0x1C8
	Int m_colorKey;																			///< 0x1D8, callback value of m_textColors[0]
	Int m_sizeX;																				///< 0x1DC
	Int m_sizeY;																				///< 0x1E0
	IRegion2D m_clipRegion;															///< 0x1E4
	unsigned int m_lastResourceFrame;										///< 0x1F4
};

#define TRUE true
#define FALSE false

// The hot key lookup (Zero Hour HotKeyManager::searchHotKey) on the manager at
// retail [0x00E01E28]; pinned at 0x00358B9E.
class HotKeyManager
{
public:
	AsciiString searchHotKey( const UnicodeString &uStr );
};
class HotKeyManager;
extern HotKeyManager *TheHotKeyManager;

// The colour callback slot shared with W3DAptAux.cpp (retail [0x00DB5FC8]).
extern int g_Va00DB5FC8;
typedef Int (*BfmeColorCallback)( Color color );

class GameClient
{
public:
#define S(n) virtual void slot##n();
	S(00) S(01) S(02) S(03) S(04) S(05) S(06) S(07) S(08) S(09) S(10) S(11) S(12) S(13) S(14) S(15)
	S(16) S(17) S(18) S(19) S(20) S(21) S(22) S(23) S(24) S(25) S(26) S(27) S(28) S(29) S(30)
#undef S
	virtual unsigned int getFrame( void );	// slot 31
};
extern GameClient *TheGameClient;


// ?draw@W3DDisplayString@@UAEXHHHH@Z
void W3DDisplayString::draw( Int x, Int y, Color xDrop, Color yDrop )
{
	if( !rva00106277() )
		return;
	if( m_bfmeColorsChanged || x != m_textPos.x || y != m_textPos.y )
	{
		m_textPos.x = x;
		m_textPos.y = y;
		m_textRenderer.Reset_Polys();
		if( xDrop || yDrop )
		{
			m_textRenderer.Set_Location( Vector2( m_textPos.x + xDrop, m_textPos.y + yDrop ) );
			m_textRenderer.Draw_Sentence( m_dropColors[ 0 ], m_dropColors[ 1 ], m_dropColors[ 2 ], m_dropColors[ 3 ] );
		}
		m_textRenderer.Set_Location( Vector2( m_textPos.x, m_textPos.y ) );
		m_textRenderer.Draw_Sentence( m_textColors[ 0 ], m_textColors[ 1 ], m_textColors[ 2 ], m_textColors[ 3 ] );
		if( m_useHotKey )
		{
			m_textRendererHotKey.Reset_Polys();
			m_textRendererHotKey.Set_Location( Vector2( m_textPos.x + m_hotKeyPos.x, m_textPos.y + m_hotKeyPos.y ) );
			m_textRendererHotKey.Draw_Sentence( m_hotKeyColor, m_hotKeyColor, m_hotKeyColor, m_hotKeyColor );
			m_textRendererHotKey.Render();
		}
		m_bfmeColorsChanged = FALSE;
	}
	m_textRenderer.Render();
	if( TheGameClient )
		m_lastResourceFrame = TheGameClient->getFrame();
}
