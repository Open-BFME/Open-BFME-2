// cl: /O1 /DNDEBUG /MD /EHsc
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

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase() { releaseBuffer(); }

	void releaseBuffer();

	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString( const unsigned short *text ) : StringBase<unsigned short>( text ) {}
	UnicodeString( const UnicodeString &other ) : StringBase<unsigned short>( other ) {}
	~UnicodeString() {}
};

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
struct Rva004469D1Receiver
{
	void Rva004469D1Advance( void );
};
extern Rva004469D1Receiver *g_Va00E03354;

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

class LANAPIInterface
{
public:
	enum ReturnType
	{
		RET_OK = 0,
		RET_TIMEOUT,
		RET_GAME_FULL,
		RET_DUPLICATE_NAME,
		RET_CRC_MISMATCH,
		RET_SERIAL_DUPE,
		RET_GAME_STARTED,
		RET_GAME_EXISTS,
		RET_GAME_GONE,
		RET_BUSY,
		RET_UNKNOWN,
		RET_MAX
	};
};

// Keep only the proven LANAPI prefix and the virtual slots this body needs.
class LANAPI
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
	virtual void slot15( void ) = 0;
	virtual void slot16( void ) = 0;
	virtual void slot17( void ) = 0;
	virtual void slot18( void ) = 0;
	virtual void slot19( void ) = 0;
	virtual void slot20( void ) = 0;
	virtual void slot21( void ) = 0;
	virtual void slot22( void ) = 0;
	virtual void slot23( void ) = 0;
	virtual void slot24( void ) = 0;
	virtual void slot25( void ) = 0;
	virtual void slot26( void ) = 0;
	virtual void slot27( void ) = 0;
	virtual void slot28( void ) = 0;
	virtual void slot29( void ) = 0;
	virtual void RequestLobbyLeave( Bool forced ) = 0; // slot 30 (+0x78)
	virtual void OnGameCreate( LANAPIInterface::ReturnType ret );

protected:
	unsigned char m_beforeLobby[0x41 - 4];
	Bool m_inLobby; // +0x41
};

// ?OnGameCreate@LANAPI@@UAEXW4ReturnType@LANAPIInterface@@@Z
void LANAPI::OnGameCreate( LANAPIInterface::ReturnType ret )
{
	if( ret == LANAPIInterface::RET_OK )
	{
		if( g_Va00E03354 )
		{
			g_Va00E03354->Rva004469D1Advance();
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
