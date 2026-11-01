// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// Retail 0x00249430, 254 bytes [0x00249430,0x0024952E).
// LANAPI::OnGameCreate. Ported from Open-BFME-1
// (Code/GameEngine/Source/GameNetwork/LANAPIOnGameCreate.cpp, retail
// 0x00689910, 243 bytes): the RET_OK arm pushes
// "Menus/LanGameOptionsMenu.wnd" through Shell::push unless the global at
// 0x00E03354 is set (its no-argument helper at 0x004469D1 runs instead),
// then leaves the lobby; otherwise, when in the lobby, the failure arm
// prints the fetched LAN:Error* string through the 0x00381C82 chat helper
// (window 1, text, chatSystemColor) instead of BFME1's direct
// GadgetListBoxAddEntryText call. Target deltas vs the BFME1 donor:
// m_inLobby lives at +0x41 (BFME1 +0x3D) and RequestLobbyLeave is vtable
// slot 30 (+0x78, BFME1 slot 25).

typedef int Int;
typedef int Color;
typedef bool Bool;

#include "ascii_string.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
#include "unicode_string.h"

class Shell
{
public:
	void push( AsciiString filename, bool shutdownImmediate = false );
};
extern Shell *TheShell;

extern Bool LANbuttonPushed;
extern const Color chatSystemColor;

// Retail global at VA 0x00E03354. Its no-argument helper at 0x004469D1 is
// called only on the success path when the pointer is present; called once
// in the whole image, so the helper identity stays address based.
// Rowed callee at 0x004469D1: ?OnGameCreate@AptLanLobby@@QAEXXZ (the LAN
// lobby screen, named from WorldBuilder's AptLanLobby.cpp). Declared exactly as its owner row spells it;
// the call casts the global.
class AptLanLobby
{
	static AptLanLobby *s_instance;
public:
	static AptLanLobby *Instance() { return s_instance; }
	void OnGameCreate( void );
};

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

// Retail helper at 0x00381C82. Takes a window index, the text and a color;
// the 0x0024A323 chat path calls it with (edi, text, -1), so the first
// parameter is an integer window, not a pointer. Semantic identity unproven.
void Rva00381C82AddChatText( Int window, const UnicodeString &text, Color color );

#include "../../Include/GameNetwork/LANAPI.h"

// Keep only the proven LANAPI prefix and the virtual slots this body needs.

// ?OnGameCreate@LANAPI@@UAEXW4ReturnType@LANAPIInterface@@@Z
void LANAPI::OnGameCreate( LANAPIInterface::ReturnType ret )
{
	if( ret == LANAPIInterface::RET_OK )
	{
		if( AptLanLobby::Instance() )
		{
			AptLanLobby::Instance()->OnGameCreate();
		}
		else
		{
			LANbuttonPushed = true;
			TheShell->push( AsciiString( "Menus/LanGameOptionsMenu.wnd" ), false );
		}
		RequestLobbyLeave( false );
	}
	else if( m_inLobby )
	{
		switch( ret )
		{
		case LANAPIInterface::RET_GAME_EXISTS:
			Rva00381C82AddChatText( 1, TheGameText->fetch( "LAN:ErrorGameExists" ), chatSystemColor );
			break;
		case LANAPIInterface::RET_BUSY:
			Rva00381C82AddChatText( 1, TheGameText->fetch( "LAN:ErrorBusy" ), chatSystemColor );
			break;
		default:
			Rva00381C82AddChatText( 1, TheGameText->fetch( "LAN:ErrorUnknown" ), chatSystemColor );
			break;
		}
	}
}
