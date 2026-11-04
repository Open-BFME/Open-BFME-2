// cl: /Ireference/shims/subsystem_bfme2 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// Retail 0x0044B992, 124 bytes. The body calls the matched LANAPI::reset,
// deletes the optional Transport at +0x50, destroys host/login/name at
// +0x1C/+0x18/+0x14, then chains through LANAPIInterface to
// SubsystemInterface. The target vtable stores and member offsets come from
// this body; the destructor operation follows BFME1 LANAPI::~LANAPI.

typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned short WideChar;
typedef unsigned char UnsignedByte;
typedef bool Bool;
typedef int Int;

#include "ascii_string.h"


#include "unicode_string.h"

// SubsystemInterface's 14-slot interface from the shared native header: slots 0..13 of
// retail's LANAPI vftable 0x0083E680 (init at 1, reset at 9, update at 10).
#include "subsystem_interface.h"

class LANGameInfo;
class LANPlayer;
class LivingWorldBattle;

class LANAPIInterface : public SubsystemInterface
{
public:
	enum ReturnType { RET_OK = 0, RET_TIMEOUT, RET_GAME_FULL, RET_DUPLICATE_NAME, RET_CRC_MISMATCH, RET_SERIAL_DUPE, RET_GAME_STARTED, RET_GAME_EXISTS, RET_GAME_GONE, RET_BUSY };
	enum ChatType { LANCHAT_NORMAL = 0, LANCHAT_TYPE1, LANCHAT_EMOTE, LANCHAT_SYSTEM };
	LANAPIInterface( void ) {}
	virtual ~LANAPIInterface( void ) {}
};

#include "../../Include/GameNetwork/Transport.h"

#include "../../Include/GameNetwork/BfmeNetAddress.h"

struct LANMessage
{
	UnsignedInt type;
	UnsignedByte payload[0x1D8 - sizeof(UnsignedInt)];
};

// Retail vftable 0x0083E680 (58 slots); every LANAPI slot names its row.
class LANAPI : public LANAPIInterface
{
public:
	virtual ~LANAPI(void);
	virtual void init(void);										// 1  0x00449BAA
	virtual void reset(void);										// 9  0x0044B49B
	virtual void update(void);										// 10 0x0044AAED
	virtual void setIsActive(Bool isActive);						// 14 0x00449A29
	virtual void RequestLocations(void);							// 15
	virtual void RequestGameJoin(LANGameInfo *game, const BfmeNetAddress &address);
	virtual void RequestGameJoinDirectConnect(void *data);							// 17
	virtual void RequestGameLeave(void);
	virtual void RequestAccept(Bool accept);
	virtual void RequestHasMap(void);								// 20
	virtual void RequestChat(UnicodeString message, ChatType format, Int target);
	virtual void RequestEnableMPSetupUI(Bool enable);
	virtual void RequestGameStart(Bool force);
	virtual void RequestGameStartTimer(UnsignedInt seconds);
	virtual void RequestGameOptions(AsciiString gameOptions, Int isPublic, UnsignedInt ip);	// 25
	virtual void RequestGameOptionsPacked(Bool isPublic, BfmeNetAddress *address);
	virtual void RequestGameCreate(UnicodeString gameName, Bool isDirectConnect);
	virtual void RequestGameAnnounce(void);
	virtual void RequestSetName(UnicodeString newName);
	virtual void RequestLobbyLeave(Bool forced);					// 30
	virtual void ResetGameStartTimer(void);
	virtual void OnGameList(LANGameInfo *gameList);
	virtual void rva00248E87(void);
	virtual void OnGameJoin(ReturnType ret, LANGameInfo *theGame, LANMessage *message);
	virtual void OnPlayerJoin(Int slot, UnicodeString playerName);	// 35
	virtual void OnHostLeave(void);
	virtual void OnPlayerLeave(UnicodeString player);
	virtual void OnAccept(const BfmeNetAddress *address, Bool status);
	virtual void OnHasMap(const BfmeNetAddress *address, Bool status);
	virtual void OnChat(const UnicodeString &player, const BfmeNetAddress *address,
		const UnicodeString &message, ChatType format);			// 40
	virtual void rva00249B08(LivingWorldBattle *battle);
	virtual void OnGameStart(void);
	virtual void OnWOTRGameStart(void);
	virtual void OnGameStartTimer(Int seconds);
	virtual void OnGameOptions(const BfmeNetAddress &sender, Int playerSlot, AsciiString options);	// 45
	virtual Bool OnGameOptionsPacked(const BfmeNetAddress &sender, Int playerSlot, const void *data, Int length);
	virtual void OnGameCreate(ReturnType ret);
	virtual void OnNameChange(UnsignedInt ip, UnicodeString newName);
	virtual LANGameInfo *LookupGame(UnicodeString gameName);
	virtual LANGameInfo *LookupGameByListOffset(Int offset);		// 50
	virtual LANGameInfo *GetGameList(void) { return m_games; }		// 51 (folded +0x10 getter 0x001DB09D)
	virtual Bool SetLocalIP(UnsignedInt localIP);					// 53 (overloads land in reverse order)
	virtual void SetLocalIP(AsciiString localIP);					// 52
	virtual Int AmIHost(void);
	virtual UnicodeString GetMyName(void);							// 55
	virtual LANGameInfo *GetMyGame(void) { return m_currentGame; }	// 56 (folded +0x44 getter 0x005C4AF9)
	virtual void fillInLANMessage(LANMessage *message);			// 57

protected:
	LANPlayer *m_lobbyPlayers;		// +0x0C
	LANGameInfo *m_games;		// +0x10
	UnicodeString m_name;		// +0x14
	AsciiString m_userName;		// +0x18
	AsciiString m_hostName;		// +0x1C
	UnsignedByte m_beforePending[0x28 - 0x20];
	UnsignedInt m_pendingAction;	// +0x28
	UnsignedInt m_expiration;		// +0x2C
	UnsignedByte m_beforeDirectConnect[0x34 - 0x30];
	BfmeNetAddress m_directConnectAddress;	// +0x34
	UnsignedByte m_beforeFlags[0x40 - 0x3C];
	Bool m_isInLANMenu;		// +0x40
	Bool m_inLobby;			// +0x41
	UnsignedByte m_beforeCurrentGame[0x44 - 0x42];
	LANGameInfo *m_currentGame;	// +0x44
	UnsignedByte m_beforeTransport[0x50 - 0x48];
	Transport *m_transport;		// +0x50
};

LANAPI::~LANAPI(void)
{
	reset();
	if (m_transport)
		delete m_transport;
}
