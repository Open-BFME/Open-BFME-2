// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// InGameUI's on-screen message family: the three ZH formatters (also recovered
// in BFME 1 donor 847fc2a5406da49baed14adf987ff6830204b9d0, InGameUI.cpp), the
// shared addMessageText they feed, three BFME 2 formatters that only post
// while TheGameLogic's multiplayer predicate 0x0023C6FD holds, and the military
// subtitle setup and teardown.
//
// Target facts: the six formatters are InGameUI vftable 0x007FD410 slots 14-19
// (also 0x007C7A88); each is a cdecl variadic member with an __EH_prolog frame,
// an 8192-character wide buffer, vswprintf (0x00BBA5AC) capped at 8191,
// ErrorCode 0xDEAD0002 thrown on failure and addMessageText 0x0029BA58 called
// on the result. Slots 17-19 match ZH's messageColor, message(AsciiString) and
// message(UnicodeString) (MSVC's reversed overload order); slots 14-16 are the
// same three bodies behind the gate, so their names stay address names.
// addMessageText's message ring (6 x 0x10 at +0x5D0), colors (+0x814/+0x818)
// and font triple (+0x82C/+0x830/+0x834) are retail-measured; the ring entry's
// copy assignment is the out-of-line 0x0029A778. Semantics come from ZH.
//
// Slots 22-24 are ZH's militarySubtitle(UnicodeString, Int) 0x0029F530,
// militarySubtitle(const AsciiString&, Int) 0x0029C2F6 and
// removeMilitarySubtitle 0x002A0C87. The 0x48-byte MilitarySubtitleData at
// +0x7F0 and the caption settings at +0x83C..+0x870 are retail-measured; BFME 2
// adds per-line offsets, a word display string and timeGetTime pacing to ZH's
// layout, so the field names past ZH's are descriptive. Retail folded the
// struct's implicit destructor into ~UnicodeString at 0x005B804E.

#include "unicode_string.h"
#include "ascii_string.h"
#include "../Common/GameLogicObjectLookupView.h"

// The gated label formatter expands isEmpty in place, as retail does here.
template <> inline bool StringBase<unsigned short>::isEmpty() const { return m_data == 0 || m_data->length == 0; }

typedef unsigned short WideChar;
typedef int Color;

#define _DLL
#include <stdarg.h>
__declspec(dllimport) int __cdecl vswprintf(unsigned short *buffer, unsigned int size, const unsigned short *format, va_list args);

enum ErrorCode
{
	ERROR_BASE = 0xDEAD0001,
	ERROR_OUT_OF_MEMORY = (ERROR_BASE + 0x0001)
};

struct RGBColor
{
	float red, green, blue;
	int getAsInt() const;
};

class GameFont;

class DisplayString
{
public:
	virtual void slot00() = 0;
	virtual void setText( UnicodeString text ) = 0;
	virtual UnicodeString getText() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void reset() = 0;
	virtual void setFont( GameFont *font ) = 0;
#define SLOT(N) virtual void slot##N() = 0;
	SLOT(07) SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14)
#undef SLOT
	virtual void getSize( int *width, int *height ) = 0;
#define SLOT(N) virtual void slot##N() = 0;
	SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20)
#undef SLOT
	virtual void clearText() = 0;
	virtual void appendChar( WideChar c ) = 0;
	virtual void appendText( const UnicodeString &text ) = 0;
};

class DisplayStringManager
{
public:
#define SLOT(N) virtual void slot##N() = 0;
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
	SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13)
#undef SLOT
	virtual DisplayString *newDisplayString() = 0;
	virtual void freeDisplayString( DisplayString *string ) = 0;
};
extern DisplayStringManager *TheDisplayStringManager;

class GameTextInterface
{
public:
#define SLOT(N) virtual void slot##N() = 0;
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
	SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13)
#undef SLOT
	virtual UnicodeString fetch( const char *label, bool *exists = 0 ) = 0;
	virtual UnicodeString fetch( const AsciiString &label, bool *exists = 0 ) = 0;
};
extern GameTextInterface *TheGameText;

class FontLibrary
{
public:
	GameFont *getFont( const AsciiString *name, float pointSize, bool bold );
};
extern FontLibrary *TheFontLibrary;

class GlobalLanguage
{
public:
	int adjustFontSize( int theFontSize );
};
extern GlobalLanguage *TheGlobalLanguageData;

extern GameLogic *TheGameLogic;

// TheGameLogic's multiplayer predicate 0x0023C6FD, rowed under this name.
class BfmeGlob939D
{
public:
	char bfmeCall939D();
};
#define TheBfmeGlob (*(BfmeGlob939D **)&TheGameLogic)

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime( void );

void Rva00433C18( const UnicodeString &text, bool flag );

inline Color GameMakeColor( unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha )
{
	return ( alpha << 24 ) | ( red << 16 ) | ( green << 8 ) | blue;
}

struct RGBAColorInt
{
	int red, green, blue, alpha;
};

class InGameUI
{
public:
#define SLOT(N) virtual void vslot##N();
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
	SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13)
#undef SLOT
	virtual void __cdecl rva0029E99F( const RGBColor *rgbColor, UnicodeString format, ... );
	virtual void __cdecl rva0029E656( AsciiString stringManagerLabel, ... );
	virtual void __cdecl rva0029E846( UnicodeString format, ... );
	virtual void __cdecl messageColor( const RGBColor *rgbColor, UnicodeString format, ... );
	virtual void __cdecl message( UnicodeString format, ... );
	virtual void __cdecl message( AsciiString stringManagerLabel, ... );
	virtual void vslot20();
	virtual void vslot21();
	virtual void militarySubtitle( const AsciiString &label, int duration );
	virtual void militarySubtitle( UnicodeString subtitle, int duration );
	virtual void removeMilitarySubtitle();
#define SLOT(N) virtual void vslot##N();
	SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29)
	SLOT(30) SLOT(31) SLOT(32) SLOT(33) SLOT(34) SLOT(35) SLOT(36) SLOT(37) SLOT(38) SLOT(39)
	SLOT(40) SLOT(41) SLOT(42) SLOT(43) SLOT(44) SLOT(45) SLOT(46) SLOT(47) SLOT(48) SLOT(49)
	SLOT(50) SLOT(51) SLOT(52) SLOT(53) SLOT(54) SLOT(55) SLOT(56) SLOT(57) SLOT(58) SLOT(59)
	SLOT(60) SLOT(61) SLOT(62) SLOT(63) SLOT(64) SLOT(65) SLOT(66) SLOT(67) SLOT(68) SLOT(69)
	SLOT(70) SLOT(71) SLOT(72) SLOT(73) SLOT(74) SLOT(75) SLOT(76) SLOT(77) SLOT(78) SLOT(79)
	SLOT(80) SLOT(81) SLOT(82) SLOT(83) SLOT(84) SLOT(85) SLOT(86) SLOT(87) SLOT(88) SLOT(89)
	SLOT(90) SLOT(91) SLOT(92) SLOT(93) SLOT(94) SLOT(95) SLOT(96) SLOT(97) SLOT(98) SLOT(99)
	SLOT(100) SLOT(101) SLOT(102) SLOT(103) SLOT(104) SLOT(105) SLOT(106) SLOT(107) SLOT(108)
#undef SLOT
	virtual void setRva0029B04D( int value );
	virtual void clearRva0029B060();

protected:
	void addMessageText( const UnicodeString &formattedMessage, const RGBColor *rgbColor = 0 );

	struct UIMessage
	{
		UnicodeString fullText;
		DisplayString *displayString;
		unsigned int timestamp;
		Color color;
	};
	enum { MAX_UI_MESSAGES = 6 };

	enum { MAX_SUBTITLE_LINES = 4 };
	struct MilitarySubtitleData
	{
		UnicodeString subtitle;									// +0x00
		unsigned int index;										// +0x04
		DisplayString *displayStrings[ MAX_SUBTITLE_LINES ];	// +0x08
		int lineOffsets[ MAX_SUBTITLE_LINES ];					// +0x18
		DisplayString *wordString;								// +0x28
		unsigned int currentDisplayString;						// +0x2C
		unsigned int lifetime;									// +0x30
		unsigned int nextCharTime;								// +0x34
		unsigned int elapsed;									// +0x38
		unsigned int lastTime;									// +0x3C
		Color color;											// +0x40
		bool finished;											// +0x44
	};

	char m_opaque004[ 0x5D0 - 0x4 ];
	UIMessage m_uiMessages[ MAX_UI_MESSAGES ];	// +0x5D0
	char m_opaque630[ 0x7F0 - 0x630 ];
	MilitarySubtitleData *m_militarySubtitle;	// +0x7F0
	char m_opaque7F4[ 0x814 - 0x7F4 ];
	Color m_messageColor1;						// +0x814
	Color m_messageColor2;						// +0x818
	char m_opaque81C[ 0x82C - 0x81C ];
	AsciiString m_messageFont;					// +0x82C
	int m_messagePointSize;						// +0x830
	bool m_messageBold;							// +0x834
	char m_opaque838[ 0x83C - 0x838 ];
	RGBAColorInt m_militaryCaptionColor;		// +0x83C
	char m_opaque84C[ 0x854 - 0x84C ];
	bool m_militaryCaptionCentered;				// +0x854
	AsciiString m_militaryCaptionTitleFont;		// +0x858
	int m_militaryCaptionTitlePointSize;		// +0x85C
	bool m_militaryCaptionTitleBold;			// +0x860
	AsciiString m_militaryCaptionFont;			// +0x864
	int m_militaryCaptionPointSize;				// +0x868
	bool m_militaryCaptionBold;					// +0x86C
	int m_militaryCaptionSpeed;					// +0x870
};
extern InGameUI *TheInGameUI;

void InGameUI::rva0029E656( AsciiString stringManagerLabel, ... )
{
	if( !TheBfmeGlob->bfmeCall939D() )
		return;

	UnicodeString stringManagerString;
	UnicodeString formattedMessage;

	stringManagerString = TheGameText->fetch( stringManagerLabel.str() );
	if( stringManagerString.isEmpty() )
		return;

	va_list args;
	va_start( args, stringManagerLabel );
	WideChar buf[ 8192 ];
	if( vswprintf( buf, sizeof( buf ) / sizeof( WideChar ) - 1, stringManagerString.str(), args ) < 0 )
		throw ERROR_OUT_OF_MEMORY;
	formattedMessage.set( buf );
	va_end( args );

	addMessageText( formattedMessage );
}

void InGameUI::message( AsciiString stringManagerLabel, ... )
{
	UnicodeString stringManagerString;
	UnicodeString formattedMessage;

	stringManagerString = TheGameText->fetch( stringManagerLabel.str() );

	va_list args;
	va_start( args, stringManagerLabel );
	WideChar buf[ 8192 ];
	if( vswprintf( buf, sizeof( buf ) / sizeof( WideChar ) - 1, stringManagerString.str(), args ) < 0 )
		throw ERROR_OUT_OF_MEMORY;
	formattedMessage.set( buf );
	va_end( args );

	addMessageText( formattedMessage );
}

void InGameUI::rva0029E846( UnicodeString format, ... )
{
	if( TheBfmeGlob->bfmeCall939D() )
	{
		UnicodeString formattedMessage;

		va_list args;
		va_start( args, format );
		WideChar buf[ 8192 ];
		if( vswprintf( buf, sizeof( buf ) / sizeof( WideChar ) - 1, format.str(), args ) < 0 )
			throw ERROR_OUT_OF_MEMORY;
		formattedMessage.set( buf );
		va_end( args );

		addMessageText( formattedMessage );
	}
}

void InGameUI::message( UnicodeString format, ... )
{
	UnicodeString formattedMessage;

	va_list args;
	va_start( args, format );
	WideChar buf[ 8192 ];
	if( vswprintf( buf, sizeof( buf ) / sizeof( WideChar ) - 1, format.str(), args ) < 0 )
		throw ERROR_OUT_OF_MEMORY;
	formattedMessage.set( buf );
	va_end( args );

	addMessageText( formattedMessage );
}

void InGameUI::rva0029E99F( const RGBColor *rgbColor, UnicodeString format, ... )
{
	if( TheBfmeGlob->bfmeCall939D() )
	{
		UnicodeString formattedMessage;

		va_list args;
		va_start( args, format );
		WideChar buf[ 8192 ];
		if( vswprintf( buf, sizeof( buf ) / sizeof( WideChar ) - 1, format.str(), args ) < 0 )
			throw ERROR_OUT_OF_MEMORY;
		formattedMessage.set( buf );
		va_end( args );

		addMessageText( formattedMessage, rgbColor );
	}
}

void InGameUI::messageColor( const RGBColor *rgbColor, UnicodeString format, ... )
{
	UnicodeString formattedMessage;

	va_list args;
	va_start( args, format );
	WideChar buf[ 8192 ];
	if( vswprintf( buf, sizeof( buf ) / sizeof( WideChar ) - 1, format.str(), args ) < 0 )
		throw ERROR_OUT_OF_MEMORY;
	formattedMessage.set( buf );
	va_end( args );

	addMessageText( formattedMessage, rgbColor );
}

void InGameUI::addMessageText( const UnicodeString &formattedMessage, const RGBColor *rgbColor )
{
	int i;
	Color color1 = m_messageColor1;
	Color color2 = m_messageColor2;

	if( rgbColor )
	{
		color1 = rgbColor->getAsInt() | 0xFF000000;
		color2 = rgbColor->getAsInt() | 0xFF000000;
	}

	m_uiMessages[ MAX_UI_MESSAGES - 1 ].fullText.clear();
	if( m_uiMessages[ MAX_UI_MESSAGES - 1 ].displayString )
		TheDisplayStringManager->freeDisplayString( m_uiMessages[ MAX_UI_MESSAGES - 1 ].displayString );
	m_uiMessages[ MAX_UI_MESSAGES - 1 ].displayString = 0;
	m_uiMessages[ MAX_UI_MESSAGES - 1 ].timestamp = 0;

	for( i = MAX_UI_MESSAGES - 1; i >= 1; i-- )
		m_uiMessages[ i ] = m_uiMessages[ i - 1 ];

	m_uiMessages[ 0 ].fullText = formattedMessage;
	m_uiMessages[ 0 ].timestamp = TheGameLogic->getFrame();
	m_uiMessages[ 0 ].displayString = TheDisplayStringManager->newDisplayString();
	m_uiMessages[ 0 ].displayString->setFont( TheFontLibrary->getFont( &m_messageFont,
		TheGlobalLanguageData->adjustFontSize( m_messagePointSize ), m_messageBold ) );
	m_uiMessages[ 0 ].displayString->setText( m_uiMessages[ 0 ].fullText );

	if( m_uiMessages[ 1 ].displayString == 0 || m_uiMessages[ 1 ].color == color2 )
		m_uiMessages[ 0 ].color = color1;
	else
		m_uiMessages[ 0 ].color = color2;
}

void InGameUI::militarySubtitle( const AsciiString &label, int duration )
{
	UnicodeString subtitle = TheGameText->fetch( label );
	militarySubtitle( subtitle, duration );
}

template <typename T>
inline T StringBase<T>::getCharAt( int index ) const throw()
{
	return m_data ? m_data->data[ index ] : 0;
}

// Width of the line of text starting at start, measured on ds.
static int getLineWidth( DisplayString *ds, const UnicodeString *text, int start )
{
	int end = start;
	while( end < text->getLength() && text->getCharAt( end ) != L'\n' )
		end++;
	if( end > start )
	{
		int width, height;
		UnicodeString saved = ds->getText();
		ds->setText( UnicodeString( *text, start, end - start ) );
		ds->getSize( &width, &height );
		ds->setText( saved );
		return width;
	}
	return 0;
}

void InGameUI::militarySubtitle( UnicodeString subtitle, int duration )
{
	removeMilitarySubtitle();
	Rva00433C18( subtitle, false );

	if( subtitle.isEmpty() || duration <= 0 )
		return;

	subtitle += L' ';
	m_militarySubtitle = new MilitarySubtitleData;
	m_militarySubtitle->subtitle.set( subtitle );
	m_militarySubtitle->lifetime = duration;
	m_militarySubtitle->elapsed = 0;
	m_militarySubtitle->nextCharTime = 0;
	m_militarySubtitle->lastTime = timeGetTime();
	m_militarySubtitle->index = 0;
	m_militarySubtitle->finished = false;
	for( int i = 1; i < MAX_SUBTITLE_LINES; i++ )
	{
		m_militarySubtitle->displayStrings[ i ] = 0;
		m_militarySubtitle->lineOffsets[ i ] = 0;
	}

	GameFont *font = TheFontLibrary->getFont( &m_militaryCaptionTitleFont,
		TheGlobalLanguageData->adjustFontSize( m_militaryCaptionTitlePointSize ), m_militaryCaptionTitleBold );

	m_militarySubtitle->currentDisplayString = 0;
	m_militarySubtitle->displayStrings[ 0 ] = TheDisplayStringManager->newDisplayString();
	m_militarySubtitle->displayStrings[ 0 ]->reset();
	m_militarySubtitle->displayStrings[ 0 ]->setFont( font );
	if( m_militaryCaptionCentered )
		m_militarySubtitle->lineOffsets[ 0 ] = getLineWidth( m_militarySubtitle->displayStrings[ 0 ], &m_militarySubtitle->subtitle, 0 ) / -2;

	m_militarySubtitle->wordString = TheDisplayStringManager->newDisplayString();
	m_militarySubtitle->wordString->reset();
	m_militarySubtitle->wordString->setFont( font );

	m_militarySubtitle->color = GameMakeColor( m_militaryCaptionColor.red, m_militaryCaptionColor.green,
		m_militaryCaptionColor.blue, m_militaryCaptionColor.alpha );

	if( (float)m_militaryCaptionSpeed < 1.0f )
		m_militaryCaptionSpeed = 1;
}

void InGameUI::removeMilitarySubtitle()
{
	if( !m_militarySubtitle )
		return;

	TheInGameUI->clearRva0029B060();

	for( unsigned int i = 0; i <= m_militarySubtitle->currentDisplayString; i++ )
	{
		TheDisplayStringManager->freeDisplayString( m_militarySubtitle->displayStrings[ i ] );
		m_militarySubtitle->displayStrings[ i ] = 0;
	}
	TheDisplayStringManager->freeDisplayString( m_militarySubtitle->wordString );

	delete m_militarySubtitle;
	m_militarySubtitle = 0;
}
