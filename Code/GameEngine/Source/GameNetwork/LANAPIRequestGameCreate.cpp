// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /O1
//
// Retail 0x0044B55A, 591 bytes: LANAPI::RequestGameCreate, slot 27 of the
// LANAPI vtable 0x0083E680 (UnicodeString by value plus Bool, ret 8).
// Ported from BFME 1's LANAPI::RequestGameCreate
// (LANAPIRequestGameCreateThunk.cpp, retail 0x00687E90): report busy unless
// in the lobby without a game (or direct connecting) and idle; build a
// LANGameInfo named by the local address and seed plus the game or player
// name (at most 16 characters); seat the local player in slot 0 with login
// and host; take the preferred map; record direct connect and last heard;
// make it current, add it and report success.
// BFME 2 differences: the new game is reset (GameInfo vslot 10) before
// entering it; OnGameCreate is slot 47 and the local address slot 64; the
// name concatenates the whole string; SLOT_PLAYER is 6; slots are 0x1D0
// bytes and LANGameInfo 0xF6C (next +0xF5C, last heard +0xF60, name +0xF64,
// direct connect +0xF68, as BFME 1's order); LANPreferences takes a mode.
// Callees: the LANGameInfo and LANGameSlot constructors 0x004481D4 and
// 0x00448150 (the LANGameInfo constructor builds its eight slots with them and
// the slot destructor 0x00447B0E, then stores vtable 0x00C3E518),
// GameInfo::enterGame 0x003FF268 (sets in-game, clears in-progress, as Zero
// Hour's), the slot copy constructor 0x0044B27F, LANGameInfo::setSlot
// 0x00448352 and setName 0x00449A81 (stores the +0xF64 name), the
// LANGameSlot login/host setters 0x0024955E/0x00249595 (translate into the
// LANPlayer strings at +0x1B0/+0x1B4), LANAPI::addGame 0x0044B2EA, and the
// rowed GameSlot::setState, GameInfo::setMapForwarder, LANPreferences
// constructor, preferred-map getter and destructor 0x0044D285.

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;

extern "C" __declspec(dllimport) UnsignedInt __stdcall timeGetTime( void );

#include "ascii_string.h"
#include "unicode_string.h"

// Retail expands UnicodeString::isEmpty inline as the header test
// (m_data == 0 || m_data->length == 0); the shared shim keeps it out of line
// (as MpGameSetupSlots.cpp also notes).
static inline Bool unicodeIsEmpty( const UnicodeString &text )
{
	const unsigned char *data = *(const unsigned char *const *)&text;
	return data == 0 || *(const UnsignedShort *)(data + 4) == 0;
}

template <int N> class VSlots : public VSlots<N - 1>
{
public:
	virtual void gap( char (*)[N] );
};
template <> class VSlots<0>
{
};

struct BfmeNetAddress
{
	UnsignedInt m_ip;
	UnsignedInt m_port;
};

struct GameSlotConnectInfo
{
	Int m_nat;
	UnsignedShort m_port;
};

enum SlotState
{
	SLOT_OPEN = 0,
	SLOT_CLOSED = 1,
	SLOT_EASY_AI = 2,
	SLOT_MED_AI = 3,
	SLOT_BRUTAL_AI = 4,
	SLOT_AI_5 = 5,
	SLOT_PLAYER = 6
};

class GameSlot
{
public:
	virtual ~GameSlot( void );
	void setState( SlotState state, UnicodeString name, const GameSlotConnectInfo *connectInfo );
	void setIP( UnsignedInt ip ) { m_address.m_ip = ip; }
	void setPort( UnsignedInt port ) { m_address.m_port = port; }

protected:
	unsigned char m_pre38[0x38 - 4];
	BfmeNetAddress m_address;			// +0x38
	unsigned char m_pad40[0x1AC - 0x40];
};

class LANGameSlot : public GameSlot
{
public:
	LANGameSlot( void );
	LANGameSlot( const LANGameSlot &other );
	virtual ~LANGameSlot( void );

	void setLogin( AsciiString name );
	void setHost( AsciiString name );
	void setLastHeard( UnsignedInt time ) { m_lastHeard = time; }

private:
	unsigned char m_user[0x1C];			// +0x1AC LANPlayer
	unsigned char m_serial[4];			// +0x1C8
	UnsignedInt m_lastHeard;			// +0x1CC
};

class GameInfo : public VSlots<10>
{
public:
	virtual void reset( void );
	void enterGame( void );
	void setMapForwarder( AsciiString mapName );
	Int getSeed( void ) const { return m_seed; }

protected:
	unsigned char m_pre50[0x50 - 4];
	Int m_seed;					// +0x50
	unsigned char m_padDC[0xDC - 0x54];
};

class LANGameInfo : public GameInfo
{
public:
	LANGameInfo( void );
	void setSlot( Int slotNum, LANGameSlot slotInfo );
	void setName( UnicodeString name );
	void setNext( LANGameInfo *next ) { m_next = next; }
	void setLastHeard( UnsignedInt lastHeard ) { m_lastHeard = lastHeard; }
	void setIsDirectConnect( Bool isDirectConnect ) { m_isDirectConnect = isDirectConnect; }

private:
	unsigned char m_LANSlot[8 * 0x1D0];		// +0xDC
	LANGameInfo *m_next;				// +0xF5C
	UnsignedInt m_lastHeard;			// +0xF60
	unsigned char m_gameName[4];			// +0xF64
	Bool m_isDirectConnect;				// +0xF68
};

class GameModePreferences
{
public:
	virtual ~GameModePreferences( void );
	AsciiString rva0044D986( void );

private:
	unsigned char m_body[0x1C - 4];
};

class LANPreferences : public GameModePreferences
{
public:
	LANPreferences( Int mode );
	virtual ~LANPreferences( void );
};

enum ReturnType
{
	RET_OK = 0,
	RET_BUSY = 9
};

class LANAPI : public VSlots<27>
{
public:
	virtual void RequestGameCreate( UnicodeString gameName, Bool isDirectConnect );
	virtual void slot28( void ) = 0;
	virtual void slot29( void ) = 0;
	virtual void slot30( void ) = 0;
	virtual void slot31( void ) = 0;
	virtual void slot32( void ) = 0;
	virtual void slot33( void ) = 0;
	virtual void slot34( void ) = 0;
	virtual void slot35( void ) = 0;
	virtual void slot36( void ) = 0;
	virtual void slot37( void ) = 0;
	virtual void slot38( void ) = 0;
	virtual void slot39( void ) = 0;
	virtual void slot40( void ) = 0;
	virtual void slot41( void ) = 0;
	virtual void slot42( void ) = 0;
	virtual void slot43( void ) = 0;
	virtual void slot44( void ) = 0;
	virtual void slot45( void ) = 0;
	virtual void slot46( void ) = 0;
	virtual void OnGameCreate( ReturnType ret ) = 0;
	virtual void slot48( void ) = 0;
	virtual void slot49( void ) = 0;
	virtual void slot50( void ) = 0;
	virtual void slot51( void ) = 0;
	virtual void slot52( void ) = 0;
	virtual void slot53( void ) = 0;
	virtual void slot54( void ) = 0;
	virtual void slot55( void ) = 0;
	virtual void slot56( void ) = 0;
	virtual void slot57( void ) = 0;
	virtual void slot58( void ) = 0;
	virtual void slot59( void ) = 0;
	virtual void slot60( void ) = 0;
	virtual void slot61( void ) = 0;
	virtual void slot62( void ) = 0;
	virtual void slot63( void ) = 0;
	virtual BfmeNetAddress *getLocalAddress( void ) = 0;

protected:
	void addGame( LANGameInfo *game );

	unsigned char m_pre14[0x14 - 4];
	UnicodeString m_name;				// +0x14
	AsciiString m_userName;				// +0x18
	AsciiString m_hostName;				// +0x1C
	UnsignedInt m_gameStartTime;			// +0x20
	Int m_gameStartSeconds;				// +0x24
	Int m_pendingAction;				// +0x28
	unsigned char m_pad2C[0x41 - 0x2C];
	Bool m_inLobby;					// +0x41
	LANGameInfo *m_currentGame;			// +0x44
};

void LANAPI::RequestGameCreate( UnicodeString gameName, Bool isDirectConnect )
{
	if( (!m_inLobby || m_currentGame) && !isDirectConnect )
	{
		OnGameCreate( RET_BUSY );
		return;
	}

	if( m_pendingAction != 0 )
	{
		OnGameCreate( RET_BUSY );
		return;
	}

	m_inLobby = false;
	LANGameInfo *myGame = new LANGameInfo;
	myGame->reset();
	myGame->enterGame();

	UnicodeString name;
	name.format( L"%8.8X%8.8X", getLocalAddress()->m_ip, myGame->getSeed() );
	if( unicodeIsEmpty( gameName ) )
		name.concat( m_name );
	else
		name.concat( gameName );

	while( name.getLength() > 16 )
		name.removeLastChar();

	myGame->setName( name );

	LANGameSlot newSlot;
	GameSlotConnectInfo connectInfo;
	connectInfo.m_nat = 0;
	connectInfo.m_port = 0;
	newSlot.setState( SLOT_PLAYER, m_name, &connectInfo );
	BfmeNetAddress *localAddress = getLocalAddress();
	newSlot.setIP( localAddress->m_ip );
	newSlot.setPort( localAddress->m_port );
	newSlot.setLastHeard( 0 );
	newSlot.setLogin( m_userName );
	newSlot.setHost( m_hostName );

	myGame->setSlot( 0, newSlot );
	myGame->setNext( 0 );

	LANPreferences pref( 0 );
	AsciiString mapName = pref.rva0044D986();
	myGame->setMapForwarder( mapName );
	myGame->setIsDirectConnect( isDirectConnect );
	myGame->setLastHeard( timeGetTime() );
	m_currentGame = myGame;

	addGame( myGame );
	OnGameCreate( RET_OK );
}
