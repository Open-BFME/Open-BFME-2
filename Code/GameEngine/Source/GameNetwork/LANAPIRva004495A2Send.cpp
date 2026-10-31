// cl: /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2 /ICode/GameEngine/Include
//
// ?Rva004495A2@LANAPI@@QAEXPAULANMessage@@I@Z, retail 0x004495A2 (184 bytes;
// Ghidra split it at +0x0D, the true end is the ret 8 at 0x00449659).
// Zero Hour's LANAPI::sendMessage(msg, ip) reworked for BFME 2's
// address+port destinations: the second argument (declared unsigned int by
// the callers' pinned spelling) is really a pointer to an {ip, port} pair.
//   - a non-null destination with a non-zero ip or port: send there;
//   - else, in a direct-connect game (+0x44, flag byte +0xF68): send to the
//     {ip, port} at GameSlot+0x38 of every human slot but the local one;
//   - else: broadcast to m_broadcastAddr (+0x54) on each of the eight lobby
//     ports 0x1F96..0x1F9D.
// Every send goes through the transport at +0x50 (queueSend at 0x004D4EC6) with
// the 0x1D8-byte LANMessage. Native queueSend reads the same ip/port
// pair as the local address view; it copies the message as bytes. Callee identities beyond the rowed
// GameInfo::getSlot / GameSlot::isHuman stay address-derived.

typedef int Int;
typedef bool Bool;
typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned short WideChar;
#include "ascii_string.h"
#include "unicode_string.h"
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
		LANCHAT_TYPE1,
		LANCHAT_EMOTE,
		LANCHAT_SYSTEM
	};
};
class Rva00248CDD
{
public:
	Bool rva00248CDD( const Rva00248CDD &other ) const;
};
struct BfmeNetAddress : public Rva00248CDD
{
	BfmeNetAddress( void ) {}
	BfmeNetAddress( UnsignedInt ip, UnsignedShort port ) : m_ip( ip ), m_port( port ) {}
	BfmeNetAddress *self( void ) { return this; }
	Bool Rva00248CBF( const BfmeNetAddress *other ) const;

	UnsignedInt m_ip;
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
struct GameSlotConnectInfo
{
	Int m_nat;
	UnsignedShort m_port;
};
class GameSlot
{
public:
	GameSlot( const GameSlot &other );
	virtual ~GameSlot( void );
	void setState( SlotState state, UnicodeString name, const GameSlotConnectInfo *connectInfo );
	void setAddress( const BfmeNetAddress &address ) { m_address = address; }
	Bool isHuman( void ) const;
	Bool hasMap( void ) const { return m_hasMap; }

private:
	UnsignedByte m_pre09[9 - 4];
	Bool m_hasMap;					// +0x09
public:
	UnsignedByte m_pre38[0x38 - 0x0A];
	BfmeNetAddress m_address;		// +0x38
	UnsignedByte m_pad40[0x1AC - 0x40];
};
class LANPlayer
{
public:
	LANPlayer() : m_lastHeard(0), m_next(0)
	{
		m_address.m_ip = 0;
		m_address.m_port = 0;
	}
	LANPlayer( const LANPlayer &other );
	~LANPlayer();

	const UnicodeString &getName(void) const { return m_name; }
	LANPlayer *getNext(void) const { return m_next; }
	void setNext(LANPlayer *next) { m_next = next; }
	UnsignedInt getIP(void) const { return m_address.m_ip; }

	UnicodeString m_name;
	UnicodeString m_login;
	UnicodeString m_host;
	UnsignedInt m_lastHeard;
	LANPlayer *m_next;
	BfmeNetAddress m_address;
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
	LANPlayer m_user;				// +0x1AC
	AsciiString m_serial;				// +0x1C8
	UnsignedInt m_lastHeard;			// +0x1CC
};
class GameInfo
{
public:
	virtual ~GameInfo( void );
	virtual void slot01( void ); virtual void slot02( void );
	virtual void slot03( void ); virtual void slot04( void );
	virtual void slot05( void ); virtual void slot06( void );
	virtual void slot07( void ); virtual void slot08( void );
	virtual void slot09( void ); virtual void reset( void );	// slot 10
	virtual void slot11( void ); virtual void slot12( void );
	virtual Int getLocalSlotNum( void ) const;	// slot 13 (+0x34)
	virtual void slot14( void );
	virtual void slot15( void ); virtual void slot16( void );
	virtual void slot17( void ); virtual void slot18( void );
	virtual void slot19( void ); virtual void slot20( void );
	virtual void slot21( void ); virtual void slot22( void );

	GameSlot *getSlot( Int slotNum );
	AsciiString getMap( void ) const;
	void enterGame( void );
	void setMapForwarder( AsciiString mapName );
	__declspec(dllimport) __forceinline Int getSeed( void ) const { return m_seed; }
	__declspec(dllimport) __forceinline Bool isGameInProgress( void ) const { return m_inProgress; }

protected:
	friend class LANAPI;
	UnsignedByte m_pre11[0x11 - 4];
	Bool m_inProgress;			// +0x11
	UnsignedByte m_pre50[0x50 - 0x12];
	Int m_seed;				// +0x50
	UnsignedByte m_preCC[0xCC - 0x54];
	UnsignedByte m_bfmeCC[16];		// +0xCC
};
// getLANSlot (0x00447773), under the ledger's class name. Retail calls it
// directly at each use, with no inline wrapper between.
class Rva00447773 : public GameInfo
{
public:
	void *getLANSlot( Int index );
	void *rva00449522(Int index);
};
class Rva004482FB : public Rva00447773
{
public:
	Int getSlotNum( UnicodeString name );
};
class LANGameInfo : public Rva004482FB
{
public:
	LANGameInfo( void );
	virtual UnicodeString getName( void );	// slot 23

	void setName( UnicodeString name );
	void setSlot( Int slotNum, LANGameSlot slotInfo );
	const BfmeNetAddress *getAddress( Int slot ) const { return &m_slots[slot].m_address; }
	const BfmeNetAddress *getHostAddress( void ) const { return &m_slots[0].m_address; }
	LANGameInfo *getNext( void ) { return m_next; }
	void setNext( LANGameInfo *next ) { m_next = next; }
	UnsignedInt getLastHeard( void ) const { return m_lastHeard; }
	void setLastHeard( UnsignedInt lastHeard ) { m_lastHeard = lastHeard; }
	void setIsDirectConnect( Bool isDirectConnect ) { m_isDirectConnect = isDirectConnect; }

private:
	friend class LANAPI;
	LANGameSlot m_slots[8];			// +0xDC, addresses from +0x114
	LANGameInfo *m_next;			// +0xF5C
	UnsignedInt m_lastHeard;		// +0xF60
	UnsignedByte m_gameName[4];		// +0xF64
	Bool m_isDirectConnect;		// +0xF68
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
	WideChar name[11];				// +0x04
	char userName[2];				// +0x1A
	char hostName[2];				// +0x1C
	union
	{
		UnsignedInt m_arg;
		struct
		{
			char options[0x186 + 1];		// +0x1E
		} GameOptions;
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
#include "../../Include/GameNetwork/Transport.h"
class LANGameInfo;
struct TransportAddress
{
	UnsignedInt m_ip;
	UnsignedShort m_port;
};
class LivingWorldBattle;
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
	virtual void ResetGameStartTimer( void ); virtual void OnGameList( LANGameInfo *gameList );	// slot 32
	virtual void rva00248E87( void );		// slot 33, the player list refresh
	virtual void OnGameJoin( LANAPIInterface::ReturnType ret, LANGameInfo *game, LANMessage *msg );
	virtual void OnPlayerJoin( Int slot, UnicodeString playerName );	// slot 35
	virtual void OnHostLeave( void );		// slot 36
	virtual void OnPlayerLeave( UnicodeString player );
	virtual void OnAccept( const BfmeNetAddress *address, Bool status );
	virtual void OnHasMap( const BfmeNetAddress *address, Bool status );
	virtual void OnChat( const UnicodeString &player, const BfmeNetAddress *ip,
		const UnicodeString &message, LANAPIInterface::ChatType format );	// slot 40
	virtual void rva00249B08( LivingWorldBattle *battle );
	virtual void OnGameStart( void );		// slot 42
	virtual void OnWOTRGameStart( void );		// slot 43
	virtual void OnGameStartTimer( Int seconds );
	virtual void OnGameOptions( const BfmeNetAddress &sender, Int playerSlot, AsciiString options );	// slot 45
	virtual Bool OnGameOptionsPacked( const BfmeNetAddress &sender, Int playerSlot, const void *data, Int length );
	virtual void OnGameCreate( LANAPIInterface::ReturnType ret );
	virtual void OnNameChange( UnsignedInt ip, UnicodeString newName ); virtual LANGameInfo *LookupGame( UnicodeString name );
	virtual LANGameInfo *LookupGameByListOffset( Int offset );	// slot 50
	virtual LANGameInfo *GetGameList( void ) { return m_games; }	// slot 51 (folded +0x10 getter 0x001DB09D)
	virtual Bool SetLocalIP( UnsignedInt localIP );
	virtual void SetLocalIP( AsciiString localIP );
	virtual Int AmIHost( void );
	virtual UnicodeString GetMyName( void );	// slot 55
	virtual LANGameInfo *GetMyGame( void ) { return m_currentGame; }	// slot 56 (folded +0x44 getter 0x005C4AF9)
	virtual void fillInLANMessage( LANMessage *msg );	// slot 57
	virtual void checkMOTD( void ) = 0; virtual void slot59( void ) = 0;
	virtual Bool rva00449B79( void );
	virtual void rva00248E2F( Bool value );	// slot 61
	virtual void slot62( void ) = 0; virtual LANPlayer *LookupPlayer( const BfmeNetAddress *address );
	virtual BfmeNetAddress *getLocalAddress( void ) = 0;

	void Rva004495A2( LANMessage *msg, UnsignedInt ip );

	void handleSetAccept( LANMessage *msg, const BfmeNetAddress *sender );
	void rva00581641( LANMessage *msg, const BfmeNetAddress *sender );
	void handleGameStartTimer( LANMessage *msg, const BfmeNetAddress *sender );
	void handleGameOptions( LANMessage *msg, const BfmeNetAddress *sender );
	void rva005816E3( LANMessage *msg, const BfmeNetAddress *sender );

protected:
	void removeGame( LANGameInfo *game );
	Bool ValidateGameInfo( LANGameInfo *game );
	void addGame( LANGameInfo *game );
	void removePlayer( LANPlayer *player );
	void addPlayer( LANPlayer *player );
	void handleRequestLobbyLeave( LANMessage *msg, const BfmeNetAddress *sender );
	void handleLobbyAnnounce( LANMessage *msg, const BfmeNetAddress *sender );
	void handleJoinDeny( LANMessage *msg, const BfmeNetAddress *sender );
	void handleHasMap( LANMessage *msg, const BfmeNetAddress *sender );
	void handleInActive( LANMessage *msg, const BfmeNetAddress *sender );
	void handleRequestGameInfo( LANMessage *msg, const BfmeNetAddress *sender );
	void handleGameStart( LANMessage *msg, const BfmeNetAddress *sender, Bool flag );
	void handleChat( LANMessage *msg, const BfmeNetAddress *sender );
	void handleJoinAccept( LANMessage *msg, const BfmeNetAddress *sender );
	void handleRequestGameLeave( LANMessage *msg, const BfmeNetAddress *sender, Bool flag );
	void handleGameAnnounce( LANMessage *msg, const BfmeNetAddress *sender );
	void handleRequestLocations( LANMessage *msg, const BfmeNetAddress *sender );
	void handleRequestJoin( LANMessage *msg, const BfmeNetAddress *sender );

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
	UnsignedInt m_lastUpdate;			// +0x58
	Bool m_isActive;				// +0x5C
	Bool m_unused5D;				// +0x5D
};

void LANAPI::Rva004495A2( LANMessage *msg, UnsignedInt ip )
{
	const BfmeNetAddress *to = (const BfmeNetAddress *)ip;
	if (to != 0 && (to->m_ip != 0 || to->m_port != 0))
	{
		m_transport->queueSend((NetPacketAddress *)to, (const unsigned char *)msg, sizeof(LANMessage));
	}
	else if (m_currentGame != 0 && m_currentGame->m_isDirectConnect)
	{
		Int localSlot = m_currentGame->getLocalSlotNum();
		for (Int i = 0; i < 8; ++i)
		{
			if (i != localSlot)
			{
				GameSlot *slot = m_currentGame->getSlot(i);
				if (slot != 0 && slot->isHuman())
					m_transport->queueSend((NetPacketAddress *)&slot->m_address, (const unsigned char *)msg, sizeof(LANMessage));
			}
		}
	}
	else
	{
		for (UnsignedShort port = 0x1F96; port < 0x1F9E; ++port)
		{
			BfmeNetAddress broadcast;
			broadcast.m_ip = m_broadcastAddr;
			broadcast.m_port = port;
			m_transport->queueSend((NetPacketAddress *)&broadcast, (const unsigned char *)msg, sizeof(LANMessage));
		}
	}
}
