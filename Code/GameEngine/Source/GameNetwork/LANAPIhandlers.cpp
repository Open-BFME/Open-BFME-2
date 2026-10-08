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
//
// LANAPI::handleInActive, retail 0x0058219D (234 bytes), message type 17:
// Zero Hour's body (Open-BFME-1's LANAPI_handleInActive.cpp). The host of a
// game not yet in progress (+0x11) un-accepts the named player's slot when
// the sender owns it (0x00248CDD against slot +0x38), is not us and the start
// timer (+0x20) is idle; BFME 2 then re-sends the game info through slot 26
// with no address and refreshes the slot list with 0x00446A77 where Zero Hour
// sent the options string.
//
// LANAPI::handleRequestGameInfo, retail 0x00581D2D (273 bytes), message type
// 18: Zero Hour's body, the reply half of the rowed RequestGameAnnounce
// (0x0044A214). The host (slot 0's address against ours) or the packet router
// of a game in progress answers the sender with a type-1 announce: the game
// serialized by the writer 0x00447CA9 into the options at +0x42, its name
// (LANGameInfo vslot 23) at +0x1E, the in-progress (+0x11) and direct-connect
// (+0xF68) flags at +0x40/+0x41 and, as in RequestGameAnnounce, 16 bytes from
// the game at +0xCC in the message tail at +0x1C8. The LAN slots are 0x1D0
// bytes from +0xDC.
//
// LANAPI::handleGameOptions, retail 0x00582EB0 (273 bytes), message type 13:
// BFME 2's three-argument form of Zero Hour's handler. Options from the host
// (slot 0's address) of a game not in progress go, with the 0x186-byte blob
// at +0x1E, to slot 46 (BFME's OnGameOptions, as slot 0); the options string
// is regenerated before and after and compared (result unused). On success
// the lobby flag goes off through slot 61 and slot 43 or 42 runs by the third
// argument (update passes false); on failure we leave as RequestGameLeave's
// host path does: OnPlayerLeave (slot 37) with our name, removeGame and
// delete the game, back to the lobby.
//
// LANAPI::handleChat, retail 0x00581F80 (440 bytes), message type 11: Zero
// Hour's body (game name +0x1E, chat type +0x40, text +0x44) reporting to
// OnChat (slot 40), plus BFME 2's first branch: type-1 chat is reported with
// the sender's own name and address wherever we are. In a game the sender is
// found among the current game's slot addresses, its last-heard time set
// through 0x00248D35.
//
// LANAPI::handleJoinAccept, retail 0x00582287 (529 bytes), message type 4:
// Zero Hour's body (Open-BFME-1's LANAPIHandleJoinAcceptRva0068CF00.cpp
// without its LANPreferences block). An accept addressed to us (IP +0x46,
// port +0x4A) while joining makes the game looked up by name (+0x1E) current,
// re-parses its options after entering it -- keeping the 16 bytes at +0xCC
// across the parse (restored by 0x00381D02) -- seats us at the given position
// (+0x4C) with RequestGameCreate's slot sequence, takes the host's login and
// host names (+0x1A/+0x1C) into slot 0 and reports to OnGameJoin; a game that
// is gone reports RET_UNKNOWN. update first calls slot 30 with true.
//
// LANAPI::handleRequestGameLeave, retail 0x00582498 (740 bytes), message
// types 6 and 8 (update passes true for 8, false for 6 and for the leave it
// fabricates for a timed-out player): Zero Hour's body with addresses. In a
// game not in progress, a leaving host (slot 0's address) makes us
// OnHostLeave (slot 36), drop and delete the game and re-add ourselves to the
// lobby players (looked up by the local address, slot 63/64); any other
// player's slot is opened (by the host through setSlot first), reported to
// OnPlayerLeave (slot 37), the acceptances reset (GameInfo vslot 14) and the
// game info re-sent to the sender through slot 26. In the lobby the game
// named at +0x1E is found in the list (+0x10, next +0xF5C); only with the
// flag is it removed and deleted (clearing the current game if it is that
// one) before OnGameList (slot 32) runs.
//
// LANAPI::handleGameAnnounce, retail 0x00581984 (714 bytes), message type 1:
// Open-BFME-1's body (LANAPIhandlers_handleGameAnnounce_Thunk.cpp), Zero
// Hour's with addresses. Our own announces and any while our game is in
// progress are ignored; the game named at +0x1E is looked up (slot 49) or
// created, named (0x00449A81) and added, and its options (+0x42, 0x186 bytes)
// parsed by 0x00449258. BFME 2 also fails an announce whose 16-byte digest
// (+0x1C8), printed by MD5Print, is not all zeros and names no saved game
// (0x004360B3) -- from the direct-connect host only when the parse succeeded.
// A failed game is dropped; otherwise it takes the in-progress (+0x40) and
// direct-connect (+0x41) flags, the time heard (+0xF60) and the digest
// (0x00381D02, as handleJoinAccept), and is joined (slot 16) when it is the
// direct-connect host's (+0x34) with no current game; any other sender's
// announce refreshes OnGameList. Retail keeps the current game in a register
// across the address compare, so it is read once.
//
// LANAPI::handleRequestLocations, retail 0x00581795 (495 bytes), message type
// 0: Zero Hour's body (Open-BFME-1's LANAPIHandleRequestLocationsThunk.cpp).
// In the lobby we broadcast a lobby announce (type 2) and note the resend
// time (+0x3C); as host (slot 0's address is ours) we broadcast a game
// announce (type 1) with the options from 0x0044802D, the name, the
// in-progress flag and the game's 16 bytes at +0xCC, as handleRequestGameInfo
// does. Either way the sender is (re)added to the lobby players exactly as
// handleLobbyAnnounce does it.

typedef int Int;
typedef bool Bool;
typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned short WideChar;

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime( void );
extern "C" __declspec(dllimport) unsigned short * __cdecl wcsncpy( unsigned short *dest, const unsigned short *source, unsigned int count );
extern "C" void * __cdecl memcpy( void *dest, const void *source, unsigned int count );
#pragma function(memcpy)
extern "C" int __cdecl strcmp( const char *left, const char *right );
extern "C" void MD5Print( unsigned char digest[16], char output[33] );

#include "ascii_string.h"
#include "unicode_string.h"

// Retail registers no unwind state for a name compared with text:
// StringBase<unsigned short>::compare is taken not to throw (as in
// LANAPIAddGame.cpp).
template <> int StringBase<unsigned short>::compare( const unsigned short *str ) const throw();

// The ledger's inequality test of two addresses (0x00248CDD) is a method of
// a class named by its address; an empty base puts it on BfmeNetAddress.
class Rva00248CDD
{
public:
	Bool rva00248CDD( const Rva00248CDD &other ) const;
};

struct BfmeNetAddress : public Rva00248CDD
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
	MAX_SLOTS = 8,
	g_lanGameNameLength = 16,
	g_lanMaxOptionsLength = 0x186
};

#define BFME_VSLOT(n) virtual void slot##n( void ) = 0;
#define BFME_GSLOT(n) virtual void slot##n( void );

struct GameSlotConnectInfo
{
	Int m_nat;
	UnsignedShort m_port;
};

// A zeroed connection info built at the call, as setState's no-connection
// argument.
struct NoConnectInfo : public GameSlotConnectInfo
{
	NoConnectInfo( void ) { m_nat = 0; m_port = 0; }
	const GameSlotConnectInfo *self( void ) const { return this; }
};

enum SlotState
{
	SLOT_OPEN = 0,
	SLOT_PLAYER = 6
};

class GameSlot
{
public:
	virtual ~GameSlot( void );
	void setState( SlotState state, UnicodeString name, const GameSlotConnectInfo *connectInfo );
	void setAddress( const BfmeNetAddress &address ) { m_address = address; }
	void unAccept( void );

	UnsignedByte m_pre38[0x38 - 4];
	BfmeNetAddress m_address;			// +0x38
	UnsignedByte m_pad40[0x1AC - 0x40];
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
	UnsignedByte m_user[0x1C];			// +0x1AC LANPlayer
	UnsignedByte m_serial[4];			// +0x1C8
	UnsignedInt m_lastHeard;			// +0x1CC
};

// The slots seen from their addresses: same stride, starting at slot +0x38.
struct LANSlotAddress
{
	BfmeNetAddress m_address;
	UnsignedByte m_rest[sizeof( LANGameSlot ) - 8];
};

class GameInfo
{
public:
	virtual ~GameInfo( void );
	BFME_GSLOT(01) BFME_GSLOT(02) BFME_GSLOT(03) BFME_GSLOT(04)
	BFME_GSLOT(05) BFME_GSLOT(06) BFME_GSLOT(07) BFME_GSLOT(08) BFME_GSLOT(09)
	BFME_GSLOT(10) BFME_GSLOT(11) BFME_GSLOT(12) BFME_GSLOT(13)
	virtual void resetAccepted( void );		// slot 14
	BFME_GSLOT(15) BFME_GSLOT(16) BFME_GSLOT(17) BFME_GSLOT(18) BFME_GSLOT(19)
	BFME_GSLOT(20) BFME_GSLOT(21) BFME_GSLOT(22)
	virtual UnicodeString getName( void );	// slot 23

	AsciiString getMap( void ) const;
	GameSlot *getSlot( Int slotNum );
	void enterGame( void );
	Bool isGameInProgress( void ) const { return m_inProgress; }
	void setGameInProgress( Bool inProgress ) { m_inProgress = inProgress; }

private:
	UnsignedByte m_pre11[0x11 - 4];
	Bool m_inProgress;				// +0x11
	UnsignedByte m_preCC[0xCC - 0x12];
public:
	UnsignedByte m_bfmeCC[16];			// +0xCC
};

// getLANSlot (0x00447773), under the ledger's class name. Retail calls it
// directly at each use, with no inline wrapper between.
class Rva00447773 : public GameInfo
{
public:
	void *rva00447773( Int index );
};

// getSlotNum (0x004483BC), under the ledger's class name, that of the
// LANGameInfo destructor.
class Rva004482FB : public Rva00447773
{
public:
	Int rva004483BC( UnicodeString name );
};

class LANGameInfo : public Rva004482FB
{
public:
	LANGameInfo( void );
	void setName( UnicodeString name );
	Bool amIHost( void ) const;			// amIHost
	void setSlot( Int slotNum, LANGameSlot slotInfo );
	const BfmeNetAddress *getAddress( Int slot ) const { return &m_slots[slot].m_address; }
	const LANSlotAddress *getSlotAddresses( void ) const { return (const LANSlotAddress *)&m_slots[0].m_address; }
	Bool getIsDirectConnect( void ) const { return m_isDirectConnect; }
	void setIsDirectConnect( Bool isDirectConnect ) { m_isDirectConnect = isDirectConnect; }
	LANGameInfo *getNext( void ) { return m_next; }
	void setLastHeard( UnsignedInt lastHeard ) { m_lastHeard = lastHeard; }

private:
	LANGameSlot m_slots[MAX_SLOTS];			// +0xDC, addresses from +0x114
	LANGameInfo *m_next;				// +0xF5C
	UnsignedInt m_lastHeard;			// +0xF60
	UnsignedByte m_preF68[0xF68 - 0xF64];
	Bool m_isDirectConnect;				// +0xF68
};

class NetworkInterface
{
public:
	BFME_VSLOT(00) BFME_VSLOT(01) BFME_VSLOT(02) BFME_VSLOT(03) BFME_VSLOT(04)
	BFME_VSLOT(05) BFME_VSLOT(06) BFME_VSLOT(07) BFME_VSLOT(08) BFME_VSLOT(09)
	BFME_VSLOT(10) BFME_VSLOT(11) BFME_VSLOT(12) BFME_VSLOT(13) BFME_VSLOT(14)
	BFME_VSLOT(15) BFME_VSLOT(16) BFME_VSLOT(17) BFME_VSLOT(18) BFME_VSLOT(19)
	BFME_VSLOT(20) BFME_VSLOT(21) BFME_VSLOT(22) BFME_VSLOT(23) BFME_VSLOT(24)
	BFME_VSLOT(25) BFME_VSLOT(26) BFME_VSLOT(27) BFME_VSLOT(28) BFME_VSLOT(29)
	BFME_VSLOT(30) BFME_VSLOT(31) BFME_VSLOT(32) BFME_VSLOT(33) BFME_VSLOT(34)
	BFME_VSLOT(35) BFME_VSLOT(36) BFME_VSLOT(37) BFME_VSLOT(38) BFME_VSLOT(39)
	BFME_VSLOT(40) BFME_VSLOT(41) BFME_VSLOT(42)
	virtual Bool isPacketRouter( void ) = 0;	// slot 43
};
extern NetworkInterface *TheNetwork;

AsciiString GenerateGameOptionsString( void );
AsciiString GameInfoToAsciiString( const GameInfo *game, Bool isPublic );
Bool ParseAsciiStringToGameInfo( GameInfo *game, AsciiString options, Bool isPublic );
Bool ParseGameOptionsString( LANGameInfo *game, AsciiString options, const void *data, Int length );

// The saved game filed under a printed digest (0x004360B3), as
// MpGameSetupSlots.cpp declares it.
struct TreeHintOpaque0043671B;
TreeHintOpaque0043671B *Rva004360B3( AsciiString key );

// The 16 bytes at a game's +0xCC, restored by 0x00381D02 under the ledger's
// class name.
class Rva00381D02
{
public:
	void rva00381D02( void *source );
};

// setPlayerLastHeard (0x00248D35), under the ledger's class name; retail
// calls it on the current game directly.
class Rva00248D35
{
public:
	void rva00248D35( Int index, Int value );
};

// BFME 1's writeLANGameInfo: serializes the game into a message's options.
void Rva00447CA9( LANGameInfo *game, char *buffer, Int size );

// fillCurrentLANGameInfo: the current game's options, as Open-BFME-1 names
// BFME's helper.
void Rva0044802D( char *buffer, Int size );

void Rva00446A77Enable( void );

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
		RET_UNKNOWN
	};

	enum ChatType
	{
		LANCHAT_NORMAL = 0,
		LANCHAT_TYPE1,
		LANCHAT_EMOTE,
		LANCHAT_SYSTEM
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
			WideChar gameName[20];			// +0x1E
			UnsignedInt playerIP;			// +0x46
			UnsignedShort playerPort;		// +0x4A
			Int slotPosition;			// +0x4C
		} GameJoined;
		struct
		{
			WideChar gameName[17];			// +0x1E
			UnsignedInt mapCRC;			// +0x40
			Bool hasMap;				// +0x44
		} MapStatus;
		struct
		{
			WideChar gameName[g_lanGameNameLength + 1];	// +0x1E
			Bool inProgress;			// +0x40
			Bool isDirectConnect;			// +0x41
			char options[g_lanMaxOptionsLength];	// +0x42
			UnsignedByte bfmeTail[16];		// +0x1C8
		} GameInfo;
		struct
		{
			char options[g_lanMaxOptionsLength];	// +0x1E
		} GameOptions;
		struct
		{
			WideChar gameName[17];			// +0x1E
		} GameToLeave;
		struct
		{
			WideChar gameName[17];			// +0x1E
			LANAPIInterface::ChatType chatType;	// +0x40
			WideChar message[101];			// +0x44
		} Chat;
	};
};
#pragma pack(pop)

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
	BFME_VSLOT(15)
	virtual void RequestGameJoin( LANGameInfo *game, const BfmeNetAddress &ip );	// slot 16
	BFME_VSLOT(17) BFME_VSLOT(18) BFME_VSLOT(19)
	BFME_VSLOT(20) BFME_VSLOT(21) BFME_VSLOT(22) BFME_VSLOT(23) BFME_VSLOT(24)
	BFME_VSLOT(25)
	virtual void rva004497EC( Bool isPublic, BfmeNetAddress *ip );	// slot 26
	BFME_VSLOT(27) BFME_VSLOT(28) BFME_VSLOT(29)
	BFME_VSLOT(30) BFME_VSLOT(31)
	virtual void OnGameList( LANGameInfo *gameList );	// slot 32
	virtual void rva00248E87( void );		// slot 33, the player list refresh
	virtual void OnGameJoin( LANAPIInterface::ReturnType ret, LANGameInfo *theGame, LANMessage *msg );
	BFME_VSLOT(35)
	virtual void OnHostLeave( void );		// slot 36
	virtual void OnPlayerLeave( UnicodeString player );	// slot 37
	BFME_VSLOT(38)
	virtual void OnHasMap( const BfmeNetAddress *ip, Bool status );
	virtual void OnChat( const UnicodeString &player, const BfmeNetAddress *ip,
		const UnicodeString &message, LANAPIInterface::ChatType format );	// slot 40
	BFME_VSLOT(41)
	virtual void OnGameStart( void );		// slot 42
	virtual void OnWOTRGameStart( void );		// slot 43
	BFME_VSLOT(44) BFME_VSLOT(45)
	virtual Bool rva0024924D( const BfmeNetAddress &sender, Int playerSlot, const void *data, Int length );	// slot 46
	BFME_VSLOT(47)
	virtual void OnNameChange( BfmeNetAddress *from, UnicodeString newName );
	virtual LANGameInfo *LookupGame( UnicodeString gameName );
	BFME_VSLOT(50) BFME_VSLOT(51) BFME_VSLOT(52) BFME_VSLOT(53)
	virtual Bool AmIHost( void );			// slot 54
	BFME_VSLOT(55) BFME_VSLOT(56)
	virtual void fillInLANMessage( LANMessage *msg ) = 0;	// slot 57
	BFME_VSLOT(58) BFME_VSLOT(59)
	BFME_VSLOT(60)
	virtual void rva00248E2F( Bool value );		// slot 61
	BFME_VSLOT(62)
	virtual LANPlayer *LookupPlayer( const BfmeNetAddress *who );
	virtual BfmeNetAddress *getLocalAddress( void ) = 0;

	void Rva004495A2( LANMessage *msg, UnsignedInt ip );	// sendMessage

protected:
	void removePlayer( LANPlayer *player );
	void addPlayer( LANPlayer *player );
	void removeGame( LANGameInfo *game );
	void addGame( LANGameInfo *game );
	void handleRequestLobbyLeave( LANMessage *msg, const BfmeNetAddress *sender );
	void handleLobbyAnnounce( LANMessage *msg, const BfmeNetAddress *sender );
	void handleJoinDeny( LANMessage *msg, const BfmeNetAddress *sender );
	void handleHasMap( LANMessage *msg, const BfmeNetAddress *sender );
	void handleInActive( LANMessage *msg, const BfmeNetAddress *sender );
	void handleRequestGameInfo( LANMessage *msg, const BfmeNetAddress *sender );
	void handleGameOptions( LANMessage *msg, const BfmeNetAddress *sender, Bool flag );
	void handleChat( LANMessage *msg, const BfmeNetAddress *sender );
	void handleJoinAccept( LANMessage *msg, const BfmeNetAddress *sender );
	void handleRequestGameLeave( LANMessage *msg, const BfmeNetAddress *sender, Bool flag );
	void handleGameAnnounce( LANMessage *msg, const BfmeNetAddress *sender );
	void handleRequestLocations( LANMessage *msg, const BfmeNetAddress *sender );

	UnsignedByte m_pre0C[0x0C - 4];
	LANPlayer *m_lobbyPlayers;			// +0x0C
	LANGameInfo *m_games;				// +0x10
	UnicodeString m_name;				// +0x14
	AsciiString m_userName;				// +0x18
	AsciiString m_hostName;				// +0x1C
	UnsignedInt m_gameStartTime;			// +0x20
	Int m_gameStartSeconds;				// +0x24
	Int m_pendingAction;				// +0x28
	UnsignedInt m_expiration;			// +0x2C
	UnsignedInt m_actionTimeout;			// +0x30
	BfmeNetAddress m_directConnectRemoteAddress;	// +0x34
	UnsignedInt m_lastResendTime;			// +0x3C
	Bool m_isInLANMenu;				// +0x40
	Bool m_inLobby;					// +0x41
	LANGameInfo *m_currentGame;			// +0x44
};

#undef BFME_VSLOT
#undef BFME_GSLOT

extern LANAPI *TheLAN;

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
			const LANSlotAddress *slot = m_currentGame->getSlotAddresses();
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

void LANAPI::handleInActive( LANMessage *msg, const BfmeNetAddress *sender )
{
	if( m_inLobby || !m_currentGame || m_currentGame->isGameInProgress() )
		return;

	// check to see if we are the host of this game.
	if( !m_currentGame->amIHost() )
		return;

	UnicodeString playerName;
	playerName = msg->name;

	Int slotNum = m_currentGame->rva004483BC( playerName );
	if( slotNum < 0 )
		return;

	GameSlot *slot = m_currentGame->getSlot( slotNum );
	if( !slot )
		return;

	if( sender->rva00248CDD( slot->m_address ) )
		return;

	// don't want to unaccept the host, that's silly.
	if( sender->Rva00248CBF( TheLAN->getLocalAddress() ) )
		return;

	// only unaccept if the timer hasn't started yet.
	if( m_gameStartTime != 0 )
		return;

	slot->unAccept();
	BfmeNetAddress noAddress;
	noAddress.m_ip = 0;
	noAddress.m_port = 0;
	rva004497EC( true, &noAddress );
	Rva00446A77Enable();
}

void LANAPI::handleRequestGameInfo( LANMessage *msg, const BfmeNetAddress *sender )
{
	// In game, are we a host?
	if( m_currentGame )
	{
		// if we're in game we should reply if we're the packet router
		if( m_currentGame->getAddress( 0 )->Rva00248CBF( getLocalAddress() )
			|| ( m_currentGame->isGameInProgress() && TheNetwork && TheNetwork->isPacketRouter() ) )
		{
			LANMessage reply;
			fillInLANMessage( &reply );
			reply.LANMessageType = 1;	// MSG_GAME_ANNOUNCE

			Rva00447CA9( m_currentGame, reply.GameInfo.options, g_lanMaxOptionsLength );
			wcsncpy( reply.GameInfo.gameName, m_currentGame->getName().str(), g_lanGameNameLength );
			reply.GameInfo.gameName[g_lanGameNameLength] = 0;
			reply.GameInfo.inProgress = m_currentGame->isGameInProgress();
			reply.GameInfo.isDirectConnect = m_currentGame->getIsDirectConnect();
			memcpy( reply.GameInfo.bfmeTail, m_currentGame->m_bfmeCC, sizeof( reply.GameInfo.bfmeTail ) );

			Rva004495A2( &reply, (UnsignedInt)sender );
		}
	}
}

void LANAPI::handleGameOptions( LANMessage *msg, const BfmeNetAddress *sender, Bool flag )
{
	if( !m_inLobby )
	{
		LANGameInfo *game = m_currentGame;
		if( game && game->getAddress( 0 )->Rva00248CBF( sender ) && !game->isGameInProgress() )
		{
			AsciiString oldOptions = GenerateGameOptionsString();
			Bool ok = rva0024924D( *sender, 0, msg->GameOptions.options, g_lanMaxOptionsLength );
			if( ok )
			{
				{
					AsciiString newOptions = GenerateGameOptionsString();
					oldOptions.compare( newOptions );
				}
				rva00248E2F( false );
				if( flag )
					OnWOTRGameStart();
				else
					OnGameStart();
			}
			else
			{
				OnPlayerLeave( m_name );
				removeGame( m_currentGame );
				::delete m_currentGame;
				m_currentGame = 0;
				m_inLobby = true;
			}
		}
	}
}

void LANAPI::handleChat( LANMessage *msg, const BfmeNetAddress *sender )
{
	if( msg->Chat.chatType == LANAPIInterface::LANCHAT_TYPE1 )
	{
		OnChat( UnicodeString( msg->name ), sender, UnicodeString( msg->Chat.message ), msg->Chat.chatType );
	}
	else if( m_inLobby )
	{
		LANPlayer *player;
		if( ( player = LookupPlayer( sender ) ) != 0 )
		{
			OnChat( UnicodeString( player->m_name ), &player->m_address, UnicodeString( msg->Chat.message ), msg->Chat.chatType );
			player->m_lastHeard = timeGetTime();
		}
	}
	else
	{
		if( LookupGame( UnicodeString( msg->Chat.gameName ) ) != m_currentGame )
			return;

		Int player;
		const LANSlotAddress *slot;
		for( player = 0, slot = m_currentGame->getSlotAddresses(); player < MAX_SLOTS; ++player, ++slot )
		{
			if( m_currentGame && slot->m_address.Rva00248CBF( sender ) )
			{
				((Rva00248D35 *)m_currentGame)->rva00248D35( player, timeGetTime() );
				OnChat( UnicodeString( msg->name ), m_currentGame->getAddress( player ), UnicodeString( msg->Chat.message ), msg->Chat.chatType );
				break;
			}
		}
	}
}

void LANAPI::handleJoinAccept( LANMessage *msg, const BfmeNetAddress *sender )
{
	if( msg->GameJoined.playerIP != getLocalAddress()->m_ip )
		return;
	if( msg->GameJoined.playerPort != getLocalAddress()->m_port )
		return;

	if( m_pendingAction == ACT_JOIN ) // Are we trying to join?
	{
		m_currentGame = LookupGame( UnicodeString( msg->GameJoined.gameName ) );

		if( !m_currentGame )
		{
			OnGameJoin( LANAPIInterface::RET_UNKNOWN, 0, 0 );
		}
		else
		{
			m_inLobby = false;
			AsciiString options = GameInfoToAsciiString( m_currentGame, true );
			UnsignedByte saved[16];
			memcpy( saved, m_currentGame->m_bfmeCC, sizeof( saved ) );
			m_currentGame->enterGame();
			ParseAsciiStringToGameInfo( m_currentGame, options, true );
			((Rva00381D02 *)m_currentGame)->rva00381D02( saved );

			Int pos = msg->GameJoined.slotPosition;

			LANGameSlot slot;
			GameSlotConnectInfo connectInfo;
			connectInfo.m_nat = 0;
			connectInfo.m_port = 0;
			slot.setState( SLOT_PLAYER, m_name, &connectInfo );
			slot.setAddress( *getLocalAddress() );
			slot.setLastHeard( 0 );
			slot.setLogin( m_userName );
			slot.setHost( m_hostName );
			m_currentGame->setSlot( pos, slot );

			((LANGameSlot *)m_currentGame->rva00447773( 0 ))->setHost( msg->hostName );
			((LANGameSlot *)m_currentGame->rva00447773( 0 ))->setLogin( msg->userName );

			OnGameJoin( LANAPIInterface::RET_OK, m_currentGame, 0 );
		}
		m_pendingAction = ACT_NONE;
		m_expiration = 0;
	}
}

void LANAPI::handleRequestGameLeave( LANMessage *msg, const BfmeNetAddress *sender, Bool flag )
{
	if( !m_inLobby && m_currentGame && !m_currentGame->isGameInProgress() )
	{
		Int player = 0;
		const LANSlotAddress *slot = m_currentGame->getSlotAddresses();
		do
		{
			if( slot->m_address.Rva00248CBF( sender ) )
			{
				if( player == 0 )
				{
					OnHostLeave();
					removeGame( m_currentGame );
					::delete m_currentGame;
					m_currentGame = 0;

					LANPlayer *lanPlayer = LookupPlayer( getLocalAddress() );
					if( !lanPlayer )
					{
						lanPlayer = new LANPlayer;
						lanPlayer->m_address = *getLocalAddress();
					}
					else
					{
						removePlayer( lanPlayer );
					}
					lanPlayer->m_name.set( UnicodeString( m_name ) );
					lanPlayer->m_host.translate( m_hostName.str() );
					lanPlayer->m_login.translate( m_userName.str() );
					lanPlayer->m_lastHeard = timeGetTime();
					addPlayer( lanPlayer );
				}
				else
				{
					if( AmIHost() )
					{
						LANGameSlot slot;
						slot.setState( SLOT_OPEN, UnicodeString::TheEmptyString, NoConnectInfo().self() );
						m_currentGame->setSlot( player, slot );
					}
					OnPlayerLeave( UnicodeString( msg->name ) );
					((GameSlot *)m_currentGame->rva00447773( player ))->setState( SLOT_OPEN, UnicodeString::TheEmptyString, NoConnectInfo().self() );
					m_currentGame->resetAccepted();
					rva004497EC( false, (BfmeNetAddress *)sender );
				}
				break;
			}
			++player;
			++slot;
		} while( player < MAX_SLOTS );
	}
	else if( m_inLobby )
	{
		LANGameInfo *game = m_games;
		while( game )
		{
			if( game->getName().compare( msg->GameToLeave.gameName ) == 0 )
			{
				if( flag )
				{
					removeGame( game );
					if( game == m_currentGame )
						m_currentGame = 0;
					::delete game;
				}
				OnGameList( m_games );
				break;
			}
			game = game->getNext();
		}
	}
}

void LANAPI::handleGameAnnounce( LANMessage *msg, const BfmeNetAddress *sender )
{
	if( sender->Rva00248CBF( getLocalAddress() ) )
		return;

	LANGameInfo *currentGame = m_currentGame;
	if( currentGame && currentGame->isGameInProgress() )
	{
		return;
	}
	else if( sender->Rva00248CBF( &m_directConnectRemoteAddress ) )
	{
		if( currentGame == 0 )
		{
			LANGameInfo *game = LookupGame( UnicodeString( msg->GameInfo.gameName ) );
			if( !game )
			{
				game = new LANGameInfo;
				game->setName( UnicodeString( msg->GameInfo.gameName ) );
				addGame( game );
			}
			Bool success = ParseGameOptionsString( game, AsciiString( "" ), msg->GameInfo.options, g_lanMaxOptionsLength );
			if( success )
			{
				char digest[33];
				MD5Print( msg->GameInfo.bfmeTail, digest );
				if( strcmp( "00000000000000000000000000000000", digest ) != 0 && !Rva004360B3( AsciiString( digest ) ) )
					success = false;
			}
			if( !success )
			{
				removeGame( game );
				::delete game;
				return;
			}
			game->setGameInProgress( msg->GameInfo.inProgress );
			game->setIsDirectConnect( msg->GameInfo.isDirectConnect );
			game->setLastHeard( timeGetTime() );
			((Rva00381D02 *)game)->rva00381D02( msg->GameInfo.bfmeTail );
			RequestGameJoin( game, m_directConnectRemoteAddress );
		}
	}
	else
	{
		LANGameInfo *game = LookupGame( UnicodeString( msg->GameInfo.gameName ) );
		if( !game )
		{
			game = new LANGameInfo;
			game->setName( UnicodeString( msg->GameInfo.gameName ) );
			addGame( game );
		}
		Bool success = ParseGameOptionsString( game, AsciiString( "" ), msg->GameInfo.options, g_lanMaxOptionsLength );
		char digest[33];
		MD5Print( msg->GameInfo.bfmeTail, digest );
		if( strcmp( "00000000000000000000000000000000", digest ) != 0 && !Rva004360B3( AsciiString( digest ) ) )
			success = false;
		if( !success )
		{
			removeGame( game );
			::delete game;
			game = 0;
		}
		else
		{
			game->setGameInProgress( msg->GameInfo.inProgress );
			game->setIsDirectConnect( msg->GameInfo.isDirectConnect );
			game->setLastHeard( timeGetTime() );
			((Rva00381D02 *)game)->rva00381D02( msg->GameInfo.bfmeTail );
		}
		OnGameList( m_games );
	}
}

void LANAPI::handleRequestLocations( LANMessage *msg, const BfmeNetAddress *sender )
{
	if( m_inLobby )
	{
		LANMessage reply;
		fillInLANMessage( &reply );
		reply.LANMessageType = 2;	// MSG_LOBBY_ANNOUNCE

		Rva004495A2( &reply, 0 );
		m_lastResendTime = timeGetTime();
	}
	else
	{
		// In game - are we a game host?
		if( m_currentGame )
		{
			if( m_currentGame->getAddress( 0 )->Rva00248CBF( getLocalAddress() ) )
			{
				LANMessage reply;
				fillInLANMessage( &reply );
				reply.LANMessageType = 1;	// MSG_GAME_ANNOUNCE
				Rva0044802D( reply.GameInfo.options, g_lanMaxOptionsLength );
				wcsncpy( reply.GameInfo.gameName, m_currentGame->getName().str(), g_lanGameNameLength );
				reply.GameInfo.gameName[g_lanGameNameLength] = 0;
				reply.GameInfo.inProgress = m_currentGame->isGameInProgress();
				memcpy( reply.GameInfo.bfmeTail, m_currentGame->m_bfmeCC, sizeof( reply.GameInfo.bfmeTail ) );

				Rva004495A2( &reply, 0 );
			}
		}
	}

	// Add the player to the lobby player list
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
