// cl: /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2 /ICode/GameEngine/Include
// platformsdk
// ?update@LANAPI@@UAEXXZ retail 0x0044AAED (1938 bytes incl. the 80-byte
// switch table at 0x0084B22F): LANAPI::update, vtable slot 10.
// Provenance: Open-BFME-1 f98983a7d lanapi.cpp (Zero Hour's LANAPI::update)
// plus native BFME 2 dispatch and layout. The by-value player name comes from
// rowed 0x004482B7 (Rva004482B7::rva004482B7, Zero Hour's
// LANGameInfo::getPlayerName returning UnicodeString).
// Cases 13/14: retail keeps case 13's copy of the shared handleGameStart
// call and branches back to it from case 14; MSVC 7.1 cross-jumps that way
// only when the statement after the switch is a labelled jump target (without
// the label it keeps case 14's copy and case 13 jumps forward), hence markRead.
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
// LANAPI::handleGameStart, retail 0x00582EB0 (273 bytes), message type 13:
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
//
// Retail registers no unwind state for a name compared with text:
// StringBase<unsigned short>::compare is taken not to throw (as in
// LANAPIAddGame.cpp).
//
// The handlers' helpers, as their views named them: the saved game filed
// under a printed digest (0x004360B3), as MpGameSetupSlots.cpp declares it;
// the 16 bytes at a game's +0xCC, restored by 0x00381D02 under the ledger's
// class name; setPlayerLastHeard (0x00248D35), under the ledger's class name,
// which retail calls on the current game directly; BFME 1's writeLANGameInfo,
// which serializes the game into a message's options; fillCurrentLANGameInfo,
// the current game's options, as Open-BFME-1 names BFME's helper. The slots
// seen from their addresses have the same stride, starting at slot +0x38. A
// zeroed connection info built at the call is setState's no-connection
// argument.

// The slots seen from their addresses: same stride, starting at slot +0x38.
// The saved game filed under a printed digest (0x004360B3), as
// MpGameSetupSlots.cpp declares it.
// The 16 bytes at a game's +0xCC, restored by 0x00381D02 under the ledger's
// class name.
// setPlayerLastHeard (0x00248D35), under the ledger's class name; retail
// calls it on the current game directly.
#include <windows.h>
#include <string.h>

typedef int Int;
typedef bool Bool;
typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned short WideChar;

// Layout-only access to the two packed native rings; Transport stays canonical.
#pragma pack(push,1)
struct LANReceivePacket { unsigned crc; unsigned char data[1024];unsigned length;unsigned ip;unsigned short port;};
#pragma pack(pop)
struct LANTransportRings {LANReceivePacket out[128],in[128];};

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
#include "ascii_string.h"
#include "unicode_string.h"
class GameTextInterface
{
public:
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
	virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
	virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14();
	virtual UnicodeString fetch( const char *label, Bool *exists = 0 );	// slot 15 (+0x3C)
	virtual void v16();
	virtual const UnicodeString *fetchPointer( const char *label, Bool *exists = 0 );	// slot 17 (+0x44)
};
extern GameTextInterface *TheGameText;
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
// The ledger's inequality test of two addresses (0x00248CDD) is a method of
// a class named by its address; an empty base puts it on BfmeNetAddress.
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
// getSlotNum (0x004483BC), under the ledger's class name, that of the
// LANGameInfo destructor.
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

extern Bool LANbuttonPushed;
Bool LANSocketErrorDetected=false;

class Rva004482B7 {public:UnicodeString rva004482B7(Int);};
void LANAPI::update() {
 if(LANbuttonPushed)return;
 UnsignedInt now=timeGetTime();
 if(now>m_lastUpdate+200)m_lastUpdate=now;else return;
 if(!m_transport->update(0) && !LANSocketErrorDetected && m_isInLANMenu==true)LANSocketErrorDetected=true;
 for(int i=0;i<128 && !LANbuttonPushed;++i) {
  Bool flag=false;
  if(((LANTransportRings*)m_transport)->in[i].length>0) {
   BfmeNetAddress sender(((LANTransportRings*)m_transport)->in[i].ip,((LANTransportRings*)m_transport)->in[i].port);
   if(sender.Rva00248CBF(getLocalAddress())){((LANTransportRings*)m_transport)->in[i].length=0;continue;}
   LANMessage *msg=(LANMessage*)((LANTransportRings*)m_transport)->in[i].data;
   switch(msg->LANMessageType) {
    case 0:handleRequestLocations(msg,&sender);break;
    case 1:handleGameAnnounce(msg,&sender);break;
    case 2:handleLobbyAnnounce(msg,&sender);break;
    case 18:handleRequestGameInfo(msg,&sender);break;
    case 3:handleRequestJoin(msg,&sender);break;
    case 4:RequestLobbyLeave(true);handleJoinAccept(msg,&sender);break;
    case 5:handleJoinDeny(msg,&sender);break;
    case 8:flag=true;
    case 6:handleRequestGameLeave(msg,&sender,flag);break;
    case 7:handleRequestLobbyLeave(msg,&sender);break;
    case 9:handleSetAccept(msg,&sender);break;
    case 10:handleHasMap(msg,&sender);break;
    case 11:handleChat(msg,&sender);break;
    case 12:rva00581641(msg,&sender);break;
    case 13:handleGameStart(msg,&sender,false);break;
    case 14:handleGameStart(msg,&sender,true);break;
    case 15:handleGameStartTimer(msg,&sender);break;
    case 16:handleGameOptions(msg,&sender);break;
    case 17:handleInActive(msg,&sender);break;
    case 19:rva005816E3(msg,&sender);break;
    default:goto markRead;
   }
   markRead:
   ((LANTransportRings*)m_transport)->in[i].length=0;
  }
 }
 if(LANbuttonPushed)return;
 UnsignedInt resendNow=*(volatile UnsignedInt*)&now;
 if(resendNow>2000+m_lastResendTime) {
  m_lastResendTime=resendNow;
  if(m_inLobby)RequestSetName(m_name);
  else if(m_currentGame && !m_currentGame->isGameInProgress()) {
   // Retail tests only the low byte of slot 54's result.
   if((UnsignedByte)AmIHost()) {RequestGameOptionsPacked(true,BfmeNetAddress(0,0).self());RequestGameAnnounce();}
   else {
    AsciiString text;text.format("User=%s",m_userName.str());
    RequestGameOptions(text,true,(UnsignedInt)BfmeNetAddress(0,0).self());
    text.format("Host=%s",m_hostName.str());RequestGameOptions(text,true,(UnsignedInt)BfmeNetAddress(0,0).self());
    RequestGameOptions("HELLO",false,(UnsignedInt)BfmeNetAddress(0,0).self());
   }
  } else if(m_currentGame)RequestGameAnnounce();
 }
 LANPlayer *player=m_lobbyPlayers;
 Bool playerListChanged=false,gameListChanged=false;
 while(player) {
  if(player->m_lastHeard+20000<now) {
   LANPlayer *next=player->getNext();removePlayer(player);delete player;player=next;playerListChanged=true;
  }else player=player->getNext();
 }
 LANGameInfo *game=m_games;
 while(game) {
  if(game!=m_currentGame && game->getLastHeard()+20000<now) {
   removeGame(game);LANGameInfo*next=game->getNext();::delete game;game=next;gameListChanged=true;
  } else game=game->getNext();
 }
 if(m_currentGame && !m_currentGame->isGameInProgress()) {
  if(!(UnsignedByte)AmIHost()) {
   if((UnsignedInt)m_currentGame->rva00449522(0)+20000<now) {
   LANMessage msg;fillInLANMessage(&msg);msg.LANMessageType=8;
   wcsncpy(msg.name,((Rva004482B7*)m_currentGame)->rva004482B7(0).str(),10);msg.name[10]=0;
   handleRequestGameLeave(&msg,m_currentGame->getAddress(0),false);
   UnicodeString text;text=TheGameText->fetch("LAN:HostNotResponding");OnChat(UnicodeString::TheEmptyString,getLocalAddress(),text,LANAPIInterface::LANCHAT_SYSTEM);
   }
  } else {
   int p=1;BfmeNetAddress none(0,0);_ReadWriteBarrier();
   for(;p<8;++p) {
    LANGameInfo *current=m_currentGame;
    if(current->getAddress(p)->Rva00248CDD::rva00248CDD(none) && (UnsignedInt)current->rva00449522(p)+20000<now) {
     LANMessage msg;fillInLANMessage(&msg);UnicodeString text;
     text.format(TheGameText->fetchPointer("LAN:PlayerDropped"),((Rva004482B7*)m_currentGame)->rva004482B7(p).str());
     msg.LANMessageType=6;wcsncpy(msg.name,((Rva004482B7*)m_currentGame)->rva004482B7(p).str(),10);msg.name[10]=0;
     handleRequestGameLeave(&msg,m_currentGame->getAddress(p),false);OnChat(UnicodeString::TheEmptyString,getLocalAddress(),text,LANAPIInterface::LANCHAT_SYSTEM);
    }
   }
  }
 }
 if(playerListChanged)rva00248E87();if(gameListChanged)OnGameList(m_games);
 if(m_pendingAction!=ACT_NONE && now>m_expiration) {
  switch(m_pendingAction) {
   case 1:OnGameJoin(LANAPIInterface::RET_TIMEOUT,0,0);m_currentGame=0;m_inLobby=true;break;
   case 2:OnGameJoin(LANAPIInterface::RET_TIMEOUT,0,0);m_currentGame=0;m_inLobby=true;break;
   case 3:OnPlayerLeave(m_name);m_currentGame=0;m_inLobby=true;break;
  }m_pendingAction=ACT_NONE;
 }
 if(m_gameStartTime && m_gameStartSeconds && m_gameStartTime<=now)RequestGameStartTimer(m_gameStartSeconds);
 else if(m_gameStartTime && m_gameStartTime<=now){ResetGameStartTimer();RequestGameStart(false);}
 static UnsignedInt lastMOTDCheck=0;
 if(now>lastMOTDCheck+30000){checkMOTD();lastMOTDCheck=now;}
}
