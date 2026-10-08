// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// InGameUI's on-screen message family: the three ZH formatters (also recovered
// in BFME 1 donor 847fc2a5406da49baed14adf987ff6830204b9d0, InGameUI.cpp), the
// shared addMessageText they feed, and three BFME 2 formatters that only post
// while TheGameLogic's multiplayer predicate 0x0023C6FD holds.
//
// Target facts: the six formatters are InGameUI vftable 0x007FD400 slots 18-23
// (also 0x007C7A64); each is a cdecl variadic member with an __EH_prolog frame,
// an 8192-character wide buffer, vswprintf (0x00BBA5AC) capped at 8191,
// ErrorCode 0xDEAD0002 thrown on failure and addMessageText 0x0029BA58 called
// on the result. Slots 21-23 match ZH's messageColor, message(AsciiString) and
// message(UnicodeString) (MSVC's reversed overload order); slots 18-20 are the
// same three bodies behind the gate, so their names stay address names.
// addMessageText's message ring (6 x 0x10 at +0x5D0), colors (+0x814/+0x818)
// and font triple (+0x82C/+0x830/+0x834) are retail-measured; the ring entry's
// copy assignment is the out-of-line 0x0029A778. Semantics come from ZH.

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
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void setFont( GameFont *font ) = 0;
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
	SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14)
#undef SLOT
	virtual UnicodeString fetch( const char *label, bool *exists = 0 ) = 0;
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

class InGameUI
{
public:
	virtual void __cdecl rva0029E99F( const RGBColor *rgbColor, UnicodeString format, ... );
	virtual void __cdecl rva0029E656( AsciiString stringManagerLabel, ... );
	virtual void __cdecl rva0029E846( UnicodeString format, ... );
	virtual void __cdecl messageColor( const RGBColor *rgbColor, UnicodeString format, ... );
	virtual void __cdecl message( AsciiString stringManagerLabel, ... );
	virtual void __cdecl message( UnicodeString format, ... );

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

	char m_opaque004[ 0x5D0 - 0x4 ];
	UIMessage m_uiMessages[ MAX_UI_MESSAGES ];	// +0x5D0
	char m_opaque630[ 0x814 - 0x630 ];
	Color m_messageColor1;						// +0x814
	Color m_messageColor2;						// +0x818
	char m_opaque81C[ 0x82C - 0x81C ];
	AsciiString m_messageFont;					// +0x82C
	int m_messagePointSize;						// +0x830
	bool m_messageBold;							// +0x834
};

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
