// cl: /O1 /arch:SSE /G7 /DNDEBUG /Ireference/shims/bfme2_ascii /MD /EHsc
// ?setCursor@Mouse@@UAEXW4MouseCursor@1@@Z, retail 0x001EEFD2, 137 bytes.
// Mouse::setCursor from Zero Hour's Mouse.cpp. Win32Mouse::setCursor
// (0x00041A83) extends it with a direct call, which names the address.
// BFME 2 differs from Zero Hour in two guards read off the target: the
// cursor text display string at +0x4FA8 must exist, and the cursor must lie
// in [0, NUM_MOUSE_CURSORS) before m_cursorInfo (+0x0C, stride 0x54) is
// indexed. The text comes from TheGameText's const-char fetch at slot 15
// (+0x3C) and goes to the rowed setMouseText 0x001EEBD5, whose colour
// parameters are named _MouseSixteen there.
class Mouse;
#include "ascii_string.h"
#include "unicode_string.h"

struct _MouseSixteen { int v[4]; };
typedef _MouseSixteen RGBAColorInt;

class GameTextInterface
{
public:
	virtual void slot00( void ) = 0;
	virtual void slot01( void ) = 0;
	virtual void slot02( void ) = 0;
	virtual void slot03( void ) = 0;
	virtual void slot04( void ) = 0;
	virtual void slot05( void ) = 0;
	virtual void slot06( void ) = 0;
	virtual void slot07( void ) = 0;
	virtual void slot08( void ) = 0;
	virtual void slot09( void ) = 0;
	virtual void slot10( void ) = 0;
	virtual void slot11( void ) = 0;
	virtual void slot12( void ) = 0;
	virtual void slot13( void ) = 0;
	virtual void slot14( void ) = 0;
	virtual UnicodeString fetch( const char *label, bool *exists = 0 ) = 0; // slot 15 (+0x3C)
};
extern GameTextInterface *TheGameText;

struct CursorInfo
{
	AsciiString cursorName;
	AsciiString cursorText;
	RGBAColorInt cursorTextColor;
	RGBAColorInt cursorTextDropColor;
	char m_rest[0x54 - 0x28];
};

class DisplayString;

class Mouse
{
public:
	enum MouseCursor
	{
		NONE = 0,
		NUM_MOUSE_CURSORS = 0x38
	};

	virtual ~Mouse();
	virtual void setCursor( MouseCursor cursor );
	// Retail folds this empty hook with the shared 1B ret at 0x000B3FD0
	// (pin: ResetResolution calls it on TheMouse; ZH mouseNotifyResolution-
	// Change is the identity lead). Defined here because this TU makes no
	// calls to it, so nothing inlines or deletes the out-of-line call that
	// GameClientDisplayModeChange's rowed body needs.
	void rva000B3FD0();
	void rva001EEBD5( UnicodeString text, const _MouseSixteen *color, const _MouseSixteen *dropColor );

protected:
	char m_pad004[0x0C - 4];
	CursorInfo m_cursorInfo[NUM_MOUSE_CURSORS];
	char m_pad126C[0x4FA4 - 0x126C];
	MouseCursor m_currentCursor;
	DisplayString *m_cursorTextDisplayString;
};

void Mouse::rva000B3FD0()
{
}

void Mouse::setCursor( MouseCursor cursor )
{
	// only if changing
	if( m_currentCursor == cursor )
		return;

	if( m_cursorTextDisplayString == 0 )
		return;

	if( cursor < NONE || (unsigned int)cursor >= NUM_MOUSE_CURSORS )
		return;

	CursorInfo &info = m_cursorInfo[ cursor ];

	// set the new cursor text
	if( info.cursorText.isEmpty() == false )
	{
		rva001EEBD5( TheGameText->fetch( info.cursorText.str() ),
								 &info.cursorTextColor,
								 &info.cursorTextDropColor );
	}
	else
		rva001EEBD5( UnicodeString( L"" ), 0, 0 );
}
