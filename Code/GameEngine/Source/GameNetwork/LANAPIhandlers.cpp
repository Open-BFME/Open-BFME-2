// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /O1
//
// LANAPI message handlers, Zero Hour's GameNetwork/LANAPIhandlers.cpp, as
// LANAPI::update (slot 10, 0x0044AAED) dispatches them by message type
// through its jump table at 0x0084B22F. The sender arrives as a pointer to
// its address, as in Open-BFME-1's handlers.
//
// LANAPI::handleRequestLobbyLeave, retail 0x005815AB (63 bytes), message type
// 7: in the lobby, remove the lobby player (list +0x0C, next +0x10, address
// +0x14) whose address equals the sender's (0x00248CBF) and refresh the
// player list -- BFME 2's slot 33 (0x00248E87) takes no list.
//
// LANAPI::handleJoinDeny, retail 0x00581E3E (105 bytes), message type 5:
// Open-BFME-1's body. A denial addressed to us (IP +0x46 and port +0x4A
// against the local address, slot 64) while a join is pending reports the
// reason (+0x4C) and the game looked up by name (+0x1E, slot 49) to
// OnGameJoin (slot 34) with the message, then clears the pending action.
//
// LANAPI::handleHasMap, retail 0x00581EA7 (217 bytes), message type 10: Zero
// Hour's map check (CRC of the portable map path against +0x40), but BFME 2
// finds the sender among the current game's eight slot addresses (+0x114,
// stride 0x1D0) instead of by name and reports the status byte (+0x44) to
// OnHasMap (slot 39) with the sender's address. Retail tests the counter at
// the bottom of the walk, so the loop is written that way.
//
// LANAPI::handleLobbyAnnounce, retail 0x00581C4E (223 bytes), message type 2:
// Zero Hour's body, the remote half of the rowed RequestSetName. The player is
// looked up by address (slot 63), allocated or unlinked, takes the name (+0x04)
// and the one-character host (+0x1C) and login (+0x1A) fields, is re-added
// and reported to OnNameChange (slot 48). LANPlayer is RequestSetName's view.

typedef int Int;
typedef bool Bool;
typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned short WideChar;

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime( void );

#include "ascii_string.h"
#include "unicode_string.h"

struct BfmeNetAddress
{
	Bool Rva00248CBF( const BfmeNetAddress *other ) const;

	UnsignedInt m_ip;
	UnsignedShort m_port;
};

class LANPlayer
{
public:
	LANPlayer() : m_lastHeard( 0 ), m_next( 0 )
	{
		m_address.m_ip = 0;
		m_address.m_port = 0;
	}

	LANPlayer *getNext( void ) { return m_next; }
	const BfmeNetAddress *getAddress( void ) const { return &m_address; }

	UnicodeString m_name;				// +0x00
	UnicodeString m_login;				// +0x04
	UnicodeString m_host;				// +0x08
	UnsignedInt m_lastHeard;			// +0x0C
	LANPlayer *m_next;				// +0x10
	BfmeNetAddress m_address;			// +0x14
};

UnsignedInt ComputeCRC( const UnsignedByte *buf, UnsignedInt len, UnsignedInt crc );

class CRC
{
public:
	CRC( void ) { crc = 0; }
	__forceinline void computeCRC( const void *buf, Int len ) { crc = ComputeCRC( (const UnsignedByte *)buf, len, crc ); }
	UnsignedInt get( void ) { return crc; }

private:
	UnsignedInt crc;
};

class GameState
{
public:
	AsciiString realMapPathToPortableMapPath( const AsciiString &in ) const;
};
extern GameState *TheGameState;

enum
{
	MAX_SLOTS = 8
};

struct LANSlotAddress
{
	BfmeNetAddress m_address;			// slot +0x38
	UnsignedByte m_rest[0x1D0 - 8];
};

class GameInfo
{
public:
	AsciiString getMap( void ) const;
};

class LANGameInfo : public GameInfo
{
public:
	const BfmeNetAddress *getAddress( Int slot ) const { return &m_slots[slot].m_address; }
	const LANSlotAddress *getSlots( void ) const { return m_slots; }

private:
	UnsignedByte m_pre114[0x114];
	LANSlotAddress m_slots[MAX_SLOTS];		// addresses from +0x114
};

class LANAPIInterface
{
public:
	enum ReturnType
	{
		RET_OK = 0
	};
};

#pragma pack(push, 1)
struct LANMessage
{
	Int LANMessageType;
	WideChar name[11];				// +0x04
	char userName[2];				// +0x1A
	char hostName[2];				// +0x1C
	union
	{
		struct
		{
			WideChar gameName[20];			// +0x1E
			UnsignedInt playerIP;			// +0x46
			UnsignedShort playerPort;		// +0x4A
			LANAPIInterface::ReturnType reason;	// +0x4C
		} JoinDeny;
		struct
		{
			WideChar gameName[17];			// +0x1E
			UnsignedInt mapCRC;			// +0x40
			Bool hasMap;				// +0x44
		} MapStatus;
	};
};
#pragma pack(pop)

#define BFME_VSLOT(n) virtual void slot##n( void ) = 0;

class LANAPI
{
public:
	enum PendingAction
	{
		ACT_NONE = 0,
		ACT_JOIN
	};

	BFME_VSLOT(00) BFME_VSLOT(01) BFME_VSLOT(02) BFME_VSLOT(03) BFME_VSLOT(04)
	BFME_VSLOT(05) BFME_VSLOT(06) BFME_VSLOT(07) BFME_VSLOT(08) BFME_VSLOT(09)
	BFME_VSLOT(10) BFME_VSLOT(11) BFME_VSLOT(12) BFME_VSLOT(13) BFME_VSLOT(14)
	BFME_VSLOT(15) BFME_VSLOT(16) BFME_VSLOT(17) BFME_VSLOT(18) BFME_VSLOT(19)
	BFME_VSLOT(20) BFME_VSLOT(21) BFME_VSLOT(22) BFME_VSLOT(23) BFME_VSLOT(24)
	BFME_VSLOT(25) BFME_VSLOT(26) BFME_VSLOT(27) BFME_VSLOT(28) BFME_VSLOT(29)
	BFME_VSLOT(30) BFME_VSLOT(31) BFME_VSLOT(32)
	virtual void rva00248E87( void );		// slot 33, the player list refresh
	virtual void OnGameJoin( LANAPIInterface::ReturnType ret, LANGameInfo *theGame, LANMessage *msg );
	BFME_VSLOT(35) BFME_VSLOT(36) BFME_VSLOT(37) BFME_VSLOT(38)
	virtual void OnHasMap( const BfmeNetAddress *ip, Bool status );
	BFME_VSLOT(40) BFME_VSLOT(41) BFME_VSLOT(42) BFME_VSLOT(43) BFME_VSLOT(44)
	BFME_VSLOT(45) BFME_VSLOT(46) BFME_VSLOT(47)
	virtual void OnNameChange( BfmeNetAddress *from, UnicodeString newName );
	virtual LANGameInfo *LookupGame( UnicodeString gameName );
	BFME_VSLOT(50) BFME_VSLOT(51) BFME_VSLOT(52) BFME_VSLOT(53) BFME_VSLOT(54)
	BFME_VSLOT(55) BFME_VSLOT(56) BFME_VSLOT(57) BFME_VSLOT(58) BFME_VSLOT(59)
	BFME_VSLOT(60) BFME_VSLOT(61) BFME_VSLOT(62)
	virtual LANPlayer *LookupPlayer( const BfmeNetAddress *who );
	virtual BfmeNetAddress *getLocalAddress( void ) = 0;

protected:
	void removePlayer( LANPlayer *player );
	void addPlayer( LANPlayer *player );
	void handleRequestLobbyLeave( LANMessage *msg, const BfmeNetAddress *sender );
	void handleLobbyAnnounce( LANMessage *msg, const BfmeNetAddress *sender );
	void handleJoinDeny( LANMessage *msg, const BfmeNetAddress *sender );
	void handleHasMap( LANMessage *msg, const BfmeNetAddress *sender );

	UnsignedByte m_pre0C[0x0C - 4];
	LANPlayer *m_lobbyPlayers;			// +0x0C
	UnsignedByte m_pre28[0x28 - 0x10];
	Int m_pendingAction;				// +0x28
	UnsignedInt m_expiration;			// +0x2C
	UnsignedByte m_pre41[0x41 - 0x30];
	Bool m_inLobby;					// +0x41
	LANGameInfo *m_currentGame;			// +0x44
};

#undef BFME_VSLOT

void LANAPI::handleRequestLobbyLeave( LANMessage *msg, const BfmeNetAddress *sender )
{
	if( m_inLobby )
	{
		LANPlayer *player = m_lobbyPlayers;
		while( player )
		{
			if( player->getAddress()->Rva00248CBF( sender ) )
			{
				removePlayer( player );
				rva00248E87();
				break;
			}
			player = player->getNext();
		}
	}
}

void LANAPI::handleJoinDeny( LANMessage *msg, const BfmeNetAddress *sender )
{
	if( msg->JoinDeny.playerIP != getLocalAddress()->m_ip )
		return;
	if( msg->JoinDeny.playerPort != getLocalAddress()->m_port )
		return;

	if( m_pendingAction == ACT_JOIN )
	{
		OnGameJoin( msg->JoinDeny.reason, LookupGame( UnicodeString( msg->JoinDeny.gameName ) ), msg );
		m_pendingAction = ACT_NONE;
		m_expiration = 0;
	}
}

void LANAPI::handleHasMap( LANMessage *msg, const BfmeNetAddress *sender )
{
	if( !m_inLobby && m_currentGame )
	{
		CRC mapNameCRC;
		AsciiString portableMapName = TheGameState->realMapPathToPortableMapPath( m_currentGame->getMap() );
		mapNameCRC.computeCRC( portableMapName.str(), portableMapName.getLength() );
		if( msg->MapStatus.mapCRC == mapNameCRC.get() )
		{
			Int i = 0;
			const LANSlotAddress *slot = m_currentGame->getSlots();
			do
			{
				if( slot->m_address.Rva00248CBF( sender ) )
				{
					OnHasMap( sender, msg->MapStatus.hasMap );
					break;
				}
				++i;
				++slot;
			} while( i < MAX_SLOTS );
		}
	}
}

void LANAPI::handleLobbyAnnounce( LANMessage *msg, const BfmeNetAddress *sender )
{
	LANPlayer *player = LookupPlayer( sender );
	if( !player )
	{
		player = new LANPlayer;
		player->m_address = *sender;
	}
	else
	{
		removePlayer( player );
	}

	player->m_name.set( UnicodeString( msg->name ) );
	player->m_host.translate( msg->hostName );
	player->m_login.translate( msg->userName );
	player->m_lastHeard = timeGetTime();

	addPlayer( player );

	OnNameChange( &player->m_address, player->m_name );
}
