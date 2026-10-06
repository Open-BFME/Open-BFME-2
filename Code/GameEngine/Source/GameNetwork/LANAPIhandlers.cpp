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

typedef int Int;
typedef bool Bool;
typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned short WideChar;

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
	LANPlayer *getNext( void ) { return m_next; }
	const BfmeNetAddress *getAddress( void ) const { return &m_address; }

private:
	UnsignedByte m_pre10[0x10];
	LANPlayer *m_next;				// +0x10
	BfmeNetAddress m_address;			// +0x14
};

class LANGameInfo;

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
	WideChar name[13];
	union
	{
		struct
		{
			WideChar gameName[20];			// +0x1E
			UnsignedInt playerIP;			// +0x46
			UnsignedShort playerPort;		// +0x4A
			LANAPIInterface::ReturnType reason;	// +0x4C
		} JoinDeny;
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
	BFME_VSLOT(35) BFME_VSLOT(36) BFME_VSLOT(37) BFME_VSLOT(38) BFME_VSLOT(39)
	BFME_VSLOT(40) BFME_VSLOT(41) BFME_VSLOT(42) BFME_VSLOT(43) BFME_VSLOT(44)
	BFME_VSLOT(45) BFME_VSLOT(46) BFME_VSLOT(47) BFME_VSLOT(48)
	virtual LANGameInfo *LookupGame( UnicodeString gameName );
	BFME_VSLOT(50) BFME_VSLOT(51) BFME_VSLOT(52) BFME_VSLOT(53) BFME_VSLOT(54)
	BFME_VSLOT(55) BFME_VSLOT(56) BFME_VSLOT(57) BFME_VSLOT(58) BFME_VSLOT(59)
	BFME_VSLOT(60) BFME_VSLOT(61) BFME_VSLOT(62) BFME_VSLOT(63)
	virtual BfmeNetAddress *getLocalAddress( void ) = 0;

protected:
	void removePlayer( LANPlayer *player );
	void handleRequestLobbyLeave( LANMessage *msg, const BfmeNetAddress *sender );
	void handleJoinDeny( LANMessage *msg, const BfmeNetAddress *sender );

	UnsignedByte m_pre0C[0x0C - 4];
	LANPlayer *m_lobbyPlayers;			// +0x0C
	UnsignedByte m_pre28[0x28 - 0x10];
	Int m_pendingAction;				// +0x28
	UnsignedInt m_expiration;			// +0x2C
	UnsignedByte m_pre41[0x41 - 0x30];
	Bool m_inLobby;					// +0x41
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
