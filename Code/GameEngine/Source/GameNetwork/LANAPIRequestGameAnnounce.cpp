// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs-c- /O1
//
// Retail 0x0044A214, 283 bytes: LANAPI vtable 0x0083E680 slot 28, the slot
// before RequestSetName (slot 29) where Zero Hour's LANAPIInterface puts
// RequestGameAnnounce. Ported from BFME 1's LANAPI::RequestGameAnnounce
// (LANAPISendPath.cpp, retail 0x00685FC0): a host, or the packet router of a
// game in progress, of a current game that is not direct-connect fills a
// type-1 announce, serializes the game into the options at +0x42 (0x186
// bytes) with the unrowed writer 0x00447CA9 (BFME 1's writeLANGameInfo),
// copies the game's name (LANGameInfo vslot 23) to +0x1E, its in-progress
// (+0x11) and direct-connect (+0xF68) flags to +0x40 and +0x41, and sends it.
// BFME 2 differences from the donor: the host test calls the rowed address
// compare 0x00248CBF on the game's host address (+0x114) and the local
// address (vslot 64), and 16 bytes from the game at +0xCC are copied into
// the message tail at +0x1C8 before sending.

#include <string.h>

typedef int Int;
typedef bool Bool;
typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned short WideChar;

#pragma function(memcpy)

class UnicodeStringData
{
public:
	UnsignedByte m_prefix[8];
	WideChar m_data[1];
};

#include "unicode_string.h"

enum
{
	g_lanGameNameLength = 16,
	g_lanMaxOptionsLength = 0x186
};

typedef int Int;
typedef bool Bool;
typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned short WideChar;
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../../../reference/shims/bfme2_ascii/unicode_string.h"
#include "../../Include/GameNetwork/Transport.h"
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"
class GameSlot;
class LANGameInfo;
class LANPlayer;

template <int N> class VSlots : public VSlots<N - 1>
{
public:
	virtual void gap( char (*)[N] ) = 0;
};
template <> class VSlots<0>
{
};
enum
{
	MSG_REQUEST_GAME_LEAVE = 6,
	MSG_REQUEST_HOST_LEAVE = 8,
	MSG_MAP_AVAILABILITY = 10,
	MSG_CHAT = 11,
	MSG_ENABLE_MPSETUP_UI = 12,
	ACT_LEAVE = 3,
	LAN_GAME_NAME_LENGTH = 16,
	LAN_MAX_CHAT_LENGTH = 100
};
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

class LANAPIInterface : public SubsystemInterface
{
public:
	LANAPIInterface( void ) {}
	virtual ~LANAPIInterface( void ) {}
	enum ReturnType { RET_OK = 0, RET_TIMEOUT, RET_GAME_FULL, RET_DUPLICATE_NAME, RET_CRC_MISMATCH, RET_SERIAL_DUPE, RET_GAME_STARTED, RET_GAME_EXISTS, RET_GAME_GONE, RET_BUSY };
	enum ChatType
	{
		LANCHAT_NORMAL = 0,
		LANCHAT_EMOTE,
		LANCHAT_SYSTEM = 3
	};
};

struct BfmeNetAddress
{
	Bool Rva00248CBF( const BfmeNetAddress *other ) const;

	UnsignedInt m_ip;
	UnsignedShort m_port;
};

struct TransportAddress
{
	UnsignedInt m_ip;
	UnsignedShort m_port;
};

class Rva00237E28
{
public:
	void rva00237E28( Rva00237E28 *dest );

private:
	UnsignedInt m_words[4];
};

#pragma pack(push, 1)
struct LANMessage
{
	enum { MSG_REQUEST_JOIN = 3 };
	Int LANMessageType;
	UnsignedByte m_prefix[0x1E - 4];
	union
	{
		UnsignedInt m_arg;
		struct
		{
			WideChar gameName[17];
			Bool inProgress;
			Bool isDirectConnect;
			char options[0x186];
			UnsignedByte m_bfmeTail[16];
		} GameAnnounce;
		struct
		{
			UnsignedInt ip;
			UnsignedShort port;
			WideChar name[11];
		} DirectConnect;
		struct
		{
			UnsignedInt gameIP;			// +0x1E
			Rva00237E28 exeCRC;			// +0x22
			UnsignedInt iniCRC;			// +0x32
			UnsignedInt bfmeExtraCRC;		// +0x36
			char serial[0x17];		// +0x3A
		} GameToJoin;
		struct
		{
			WideChar gameName[LAN_GAME_NAME_LENGTH + 1];
			Bool accepted;
		} GameAccept;
		struct
		{
			WideChar gameName[LAN_GAME_NAME_LENGTH + 1];
		} GameToLeave;
		struct
		{
			WideChar gameName[LAN_GAME_NAME_LENGTH + 1];
			Bool enable;
		} EnableMPSetupUI;
		struct
		{
			WideChar gameName[LAN_GAME_NAME_LENGTH + 1];
			UnsignedInt mapCRC;
			Bool hasMap;
		} MapStatus;
		struct
		{
			WideChar gameName[LAN_GAME_NAME_LENGTH + 1];
			LANAPIInterface::ChatType chatType;
			WideChar message[LAN_MAX_CHAT_LENGTH + 1];
		} Chat;
		UnsignedByte m_body[0x1D8 - 0x1E];
	};
};
#pragma pack(pop)

class LANAPI : public LANAPIInterface
{
public:
	enum PendingAction { ACT_NONE = 0, ACT_JOIN, ACT_JOINDIRECTCONNECT };
	LANAPI( void );
	virtual ~LANAPI( void );
	virtual void init( void );
	virtual void slot02( void ) = 0;
	virtual void slot03( void ) = 0;
	virtual void slot04( void ) = 0;
	virtual void slot05( void ) = 0;
	virtual void slot06( void ) = 0;
	virtual void slot07( void ) = 0;
	virtual void slot08( void ) = 0;
	virtual void reset( void );
	virtual void update( void );
	virtual void slot11( void ) = 0;
	virtual void slot12( void ) = 0;
	virtual void slot13( void ) = 0;
	virtual void setIsActive( Bool active );
	virtual void RequestLocations( void );
	virtual void RequestGameJoin( LANGameInfo *game, const BfmeNetAddress &ip );
	virtual void RequestGameJoinDirectConnect( void *data );
	virtual void RequestGameLeave( void );
	virtual void RequestAccept( Bool accepted );
	virtual void RequestHasMap( void );
	virtual void RequestChat( UnicodeString message, LANAPIInterface::ChatType format, Int unused );
	virtual void RequestEnableMPSetupUI( Bool enable );
	virtual void RequestGameStart( Bool force ); virtual void RequestGameStartTimer( UnsignedInt seconds );
	virtual void RequestGameOptions( AsciiString options, Int isPublic, UnsignedInt ip ); virtual void RequestGameOptionsPacked( Bool unused, BfmeNetAddress *destination );
	virtual void RequestGameCreate( UnicodeString gameName, Bool isDirectConnect ); virtual void RequestGameAnnounce( void );
	virtual void RequestSetName( UnicodeString newName ); virtual void RequestLobbyLeave( Bool forced );
	virtual void ResetGameStartTimer( void ); virtual void slot32( void ) = 0;
	virtual void slot33( void ) = 0; virtual void OnGameJoin( LANAPIInterface::ReturnType ret, LANGameInfo *game, LANMessage *msg ) = 0;
	virtual void slot35( void ) = 0; virtual void slot36( void ) = 0;
	virtual void OnPlayerLeave( UnicodeString player ) = 0;
	virtual void slot38( void ) = 0; virtual void slot39( void ) = 0;
	virtual void OnChat( const UnicodeString &player, const BfmeNetAddress *ip,
		const UnicodeString &message, LANAPIInterface::ChatType format ) = 0;
	virtual void slot41( void ) = 0;
	virtual void slot42( void ) = 0; virtual void slot43( void ) = 0;
	virtual void OnGameStartTimer( UnsignedInt seconds ) = 0; virtual void slot45( BfmeNetAddress *address, Int slot, AsciiString options ) = 0;
	virtual void slot46( BfmeNetAddress *address, Int slot, char *data, UnsignedInt size ) = 0; virtual void slot47( void ) = 0;
	virtual void OnNameChange( BfmeNetAddress *from, UnicodeString newName ); virtual LANGameInfo *LookupGame( UnicodeString name );
	virtual LANGameInfo *LookupGameByListOffset( Int offset ); virtual void slot51( void ) = 0;
	virtual Bool SetLocalIP( UnsignedInt localIP );
	virtual void SetLocalIP( AsciiString localIP );
	virtual Int AmIHost( void ); virtual void slot55( void ) = 0;
	virtual void slot56( void ) = 0;
	virtual void fillInLANMessage( LANMessage *msg ) = 0;
	virtual void slot58( void ) = 0; virtual void slot59( void ) = 0;
	virtual Bool rva00449B79( void ); virtual void slot61( void ) = 0;
	virtual void slot62( void ) = 0; virtual LANPlayer *LookupPlayer( const BfmeNetAddress *address );
	virtual BfmeNetAddress *getLocalAddress( void ) = 0;

	void Rva004495A2( LANMessage *msg, UnsignedInt ip );

protected:
	void removeGame( LANGameInfo *game );
	Bool ValidateGameInfo( LANGameInfo *game );
	void addGame( LANGameInfo *game );
	void removePlayer( LANPlayer *player );
	void addPlayer( LANPlayer *player );

	LANPlayer *m_lobbyPlayers;
	LANGameInfo *m_games;
	UnicodeString m_name;				// +0x14
	AsciiString m_userName;		// +0x18
	AsciiString m_hostName;		// +0x1C
	UnsignedInt m_gameStartTime;
	UnsignedInt m_gameStartSeconds;		// +0x24
	Int m_pendingAction;				// +0x28
	UnsignedInt m_expiration;			// +0x2C
	UnsignedInt m_actionTimeout;			// +0x30
	BfmeNetAddress m_directConnectRemoteAddress;		// +0x34
	UnsignedInt m_lastResendTime;		// +0x3C
	Bool m_isInLANMenu;		// +0x40
	Bool m_inLobby;					// +0x41
	LANGameInfo *m_currentGame;			// +0x44
	TransportAddress m_localAddress;		// +0x48
	Transport *m_transport;				// +0x50
	UnsignedInt m_broadcastAddr;		// +0x54
	UnsignedInt m_unused58;
	Bool m_isActive;				// +0x5C
};


class GameInfo
{
public:
	virtual ~GameInfo( void );
	virtual void slot01( void ) = 0; virtual void slot02( void ) = 0;
	virtual void slot03( void ) = 0; virtual void slot04( void ) = 0;
	virtual void slot05( void ) = 0; virtual void slot06( void ) = 0;
	virtual void slot07( void ) = 0; virtual void slot08( void ) = 0;
	virtual void slot09( void ) = 0; virtual void slot10( void ) = 0;
	virtual void slot11( void ) = 0; virtual void slot12( void ) = 0;
	virtual Int getLocalSlotNum( void ) const = 0;
	virtual void slot14( void ) = 0;
	virtual void slot15( void ) = 0; virtual void slot16( void ) = 0;
	virtual void slot17( void ) = 0; virtual void slot18( void ) = 0;
	virtual void slot19( void ) = 0; virtual void slot20( void ) = 0;
	virtual void slot21( void ) = 0; virtual void slot22( void ) = 0;

	GameSlot *getSlot( Int slotNum );
	AsciiString getMap( void ) const;

protected:
	friend class LANAPI;
	UnsignedByte m_pre11[0x11 - 4];
	Bool m_inProgress;			// +0x11
	UnsignedByte m_preCC[0xCC - 0x12];
	UnsignedByte m_bfmeCC[16];		// +0xCC
	UnsignedByte m_pre114[0x114 - 0xDC];
	BfmeNetAddress m_hostAddress;			// +0x114, slot 0's address
};

class LANGameInfo : public GameInfo
{
public:
	virtual UnicodeString getName( void ) = 0;

	const BfmeNetAddress *getHostAddress( void ) const { return &m_hostAddress; }
	LANGameInfo *getNext( void ) { return m_next; }
	void setNext( LANGameInfo *next ) { m_next = next; }

private:
	friend class LANAPI;
	UnsignedByte m_preF5C[0xF5C - 0x11C];
	LANGameInfo *m_next;
	UnsignedByte m_preF68[0xF68 - 0xF60];
	Bool m_isDirectConnect;		// +0xF68
};


class NetworkInterface : public VSlots<43>
{
public:
	virtual Bool isPacketRouter( void ) = 0;
};

extern NetworkInterface *TheNetwork;

void GameInfoToByteBuffer( LANGameInfo *game, char *buffer, Int size );


void LANAPI::RequestGameAnnounce( void )
{
	// In game - are we a game host?
	if( m_currentGame && !m_currentGame->m_isDirectConnect )
	{
		BfmeNetAddress *host = &m_currentGame->m_hostAddress;

		// if we are in game we should reply if we are the packet router
		if( host->Rva00248CBF( getLocalAddress() )
			|| ( m_currentGame->m_inProgress && TheNetwork && TheNetwork->isPacketRouter() ) )
		{
			LANMessage reply;
			fillInLANMessage( &reply );
			reply.LANMessageType = 1;

			GameInfoToByteBuffer( m_currentGame, reply.GameAnnounce.options, g_lanMaxOptionsLength );
			wcsncpy( reply.GameAnnounce.gameName, m_currentGame->getName().str(), g_lanGameNameLength );
			reply.GameAnnounce.gameName[g_lanGameNameLength] = 0;
			reply.GameAnnounce.inProgress = m_currentGame->m_inProgress;
			reply.GameAnnounce.isDirectConnect = m_currentGame->m_isDirectConnect;
			memcpy( reply.GameAnnounce.m_bfmeTail, m_currentGame->m_bfmeCC, sizeof( reply.GameAnnounce.m_bfmeTail ) );

			Rva004495A2( &reply, 0 );
		}
	}
}
