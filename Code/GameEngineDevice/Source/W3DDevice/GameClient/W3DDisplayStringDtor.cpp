// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ??1W3DDisplayString@@UAE@XZ, retail 0x00106162, 92 bytes (pinned; rowed
// deleting wrapper 0x0010625B). The Zero Hour destructor is empty; what
// retail runs is member and base teardown. Retail's unwind map destroys
// the DisplayString base (rowed dtor 0x00358994) in state 0 and two
// Render2DSentenceClass members at +0x14 and +0xD8 in states 1 and 2
// (m_textRenderer, m_textRendererHotKey), whose destructor is 0x00157C70.
// The UnicodeString released first at +0x19C directly follows them, so
// Render2DSentenceClass is 0xC4 bytes here. 0x00157C70 restores vtable
// 0x007D3C80, whose only slot is the rowed Render2DSentenceClass::Reset, so
// it is that class's non-virtual destructor, pinned from these calls.
// Supersedes the blocked BFME1 transfer, which had those members at
// +0xE0/+0x1B0.
#include "unicode_string.h"
#include "../../../../Libraries/Include/Lib/ICoord2D.h"
#include "../../../../Libraries/Include/Lib/IRegion2D.h"
#include "../../../../../reference/shims/wwmath/Vector2.h"
#include "ascii_string.h"
#define TRUE true
#define FALSE false
#define TRUE true
#define FALSE false

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
	virtual UnicodeString getText( void ) { return m_textString; }  // ZH DisplayString.h inline; ICF-folded into 0x0022C4DF
	virtual Int getTextLength( void );
	virtual void notifyTextChanged( void );
	virtual void reset( void );
	virtual void setFont( GameFont *font ) { m_font = font; }
	virtual GameFont *getFont( void ) { return m_font; }  // ZH DisplayString.h inline; ICF-folded into 0x0030F45F
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

W3DDisplayString::~W3DDisplayString()
{
}

void W3DDisplayString::reset()
{
	DisplayString::reset();
	(&m_textRenderer)->Reset();
	(&m_textRendererHotKey)->Reset();
	m_textChanged = false;
	m_textPos.x = 0;
	m_textPos.y = 0;
	for (int i = 0; i < 4; ++i) {
		m_textColors[i] = 0;
		m_dropColors[i] = 0;
	}
	m_hotKeyColor = -1;
	m_sizeX = 0;
	m_sizeY = 0;
	m_fontChanged = false;
	m_clipRegion.lo.x = 0;
	m_clipRegion.lo.y = 0;
	m_clipRegion.hi.x = 0;
	m_clipRegion.hi.y = 0;
	m_lastResourceFrame = 0;
	m_useHotKey = false;
	m_hotKeyPos.x = 0;
	m_hotKeyPos.y = 0;
	m_bfmeColorsChanged = true;
	m_hotkey.clear();
}
