// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /O1
//
// LANAPI callbacks of the vtable 0x0083E680, Zero Hour's
// GameNetwork/LANAPICallbacks.cpp.
//
// LANAPI::OnPlayerLeave, retail 0x0024A0C7 (177 bytes), slot 37 (dispatched
// at +0x94 by RequestGameLeave). Zero Hour's body without the preferences
// save: out of the lobby, with a current game that is not in progress (+0x11),
// a leave by our own name (m_name +0x14) hands off to the LAN menu at VA
// 0x00E03354 (its 0x00444E8A, rowed as AptLanLobby::rva00444E8A) or, with
// no menu, pops the shell (0x0035BEC7) and sets LANbuttonPushed -- the
// OnHostLeave pattern (LANAPILobbyMenuForwarders.cpp). Anyone else leaving a
// game we host (slot-0 address +0x114 equal to the local address, vslot 64)
// forces a resend (m_lastResendTime +0x3C), refreshes the slot list (the rowed
// 0x00248D84) and re-requests the game options through vslot 26 with a public
// flag and a zero address.
//
// LANAPI::OnChat, retail 0x0024A178 (464 bytes), slot 40. Zero Hour's body
// with the window lookup moved into the cdecl chat helper 0x00381C82 (window,
// text, color) and one more chat type: BFME 2 numbers emote 2 and system 3
// (RequestChat's callers, OnGameStartTimer's SYSTEM line), and type 1 builds
// the normal "[player] message" line, filtered, for window 0 in the default
// color. Both "[player]" variants still test the sender against the local
// address and then add the line the same way either way (retail keeps the
// dead test al,al). The colors are Zero Hour's table at 0x009BA744:
// chatActionColor 0x009BA754, chatLocalActionColor 0x009BA75C and
// chatSystemColor 0x009BA760. The sender's color comes from his slot
// (LANGameInfo::getSlotNum, the rowed 0x004483BC on the class named for the
// LANGameInfo destructor 0x004482FB; GameInfo::getSlot; MultiplayerSettings
// ::getColor), default -1.
//
// LANAPI::OnHasMap, retail 0x002498FA (526 bytes), slot 39. Zero Hour's body
// in BFME 2's shape (Open-BFME-1's LANAPIOnHasMap_Bfme.cpp): as host
// (AmIHost, vslot 54, read as its low byte as every retail caller does),
// find the sender among the eight slot addresses (+0x114, 0x1D0 apart), set
// that slot's map availability (GameSlot::setMapAvailability on the slot from
// the rowed 0x00447773), then name the map -- the cached metadata's
// bfme_getDisplayName(true) or the raw map path -- and, when the player lacks
// it, post "GUI:PlayerNoMap[WillTransfer]" with the slot's name (+0x30) as a
// SYSTEM chat line before refreshing the slot list (0x00248D84). willTransfer
// is the pinned cdecl 0x00300E42 on the game, whatever the metadata says.
//
// LANAPI slot 41, retail 0x00249B08 (574 bytes), named by address: the
// living-world counterpart of OnGameStart's map half, given the battle. The
// map is maps\<name>\<name>.map for the name of the battle's holder (+0x24,
// its AsciiString at +0x18), written to TheWritableGlobalData's pending file
// and the game (setMapForwarder); the map transfer then fails exactly as in
// OnGameStart, or every slot gets its battle data (0x003EFDDB on the holder
// and 0x003F486C on the battle, both by the slot's +0x4C, the latter into
// +0x1A4) before the game starts and the logic random is seeded. The holder
// goes through locals: the name's for retail's folded [eax+0x18] load, the
// loop's (fetched after the slot's index) for its ecx-first scheduling.
//
// LANAPI::OnGameStart, retail 0x002495CC (814 bytes), slot 42: Open-BFME-1's
// LANAPIOnGameStart.cpp without the preferences save, with BFME 2's hero
// transfer check (0x0044C3D4, failing with GUI:CouldNotTransferHero) ahead of
// the map transfer (DoAnyMapTransfers 0x0044D06D, MapCache::updateCache,
// findMap, failing with GUI:CouldNotTransferMap). On success it starts the
// game, sets TheWritableGlobalData's pending file (+0xAC0) to the map, posts
// MSG_NEW_GAME (0x1E) with GAME_LAN, sets TheGameLogic's byte +0x9D and seeds
// the logic random. Retail tail-merges the two failure paths' OnChat calls.
//
// LANAPI slot 43, retail 0x0024900D (576 bytes): a BFME 2 twin of
// OnGameStart (slot 42), whose body it repeats up to the hero check and then
// starts a living-world game without the map transfer. Named by address. Like BFME 1's OnGameStart
// (Open-BFME-1's LANAPIOnGameStart.cpp) without the preferences save: leave
// the LAN menu (+0x40), create the network (the rowed 0x0025E46D),
// bind it and the game (+0x38) to the local address with the port bumped by
// 8, bump every human slot's address (+0x38) the same way, then
// parseUserList and TheGameLogic's two-flag 0x00376E92. When the cdecl
// transfer check 0x0044C3D4 fails, leave by our own name, drop and ::delete
// the game and TheNetwork, raise GUI:ErrorStartingGame /
// GUI:CouldNotTransferHero in MessageBoxOk (0x0044C0A8) and post the body
// text as a SYSTEM line from no address. Otherwise start the game (vslot
// 11), poke the living-world manager and logic, post message 0x1F with the
// game's +0x58 and 1 when 0x00E0333C is set, and seed the logic random from
// +0x50. The check result is named (filesOk) for retail's cmp al,bl; the
// zero address is a temporary so its stores sink below the text fetch.
//
// LANAPI slot 46, retail 0x0024924D (367 bytes), named by address: Zero
// Hour's OnGameOptions branch for options from the host (slot 0 while we are
// not host), split into its own Bool virtual with BFME 2's (data, length)
// options. Sender checked against the slot address with the ledger's
// inequality test 0x00248CDD; setLastHeard (+0xF60), GameInfoToAsciiString
// saves the old options, ParseGameOptionsString (0x00449258) applies the new
// ones, and when no slot 1..7 holds the local address we were booted: count
// it (0x00DFE95C), restore the old options and leave after 16 boots.
// Otherwise refresh the slot list and the options view (0x00248D84, then the
// lobby 0x00E03354 or 0x00248E98) and return true. ZH's nested
// if( playerSlot == 0 && !amIHost() ) scope is what puts oldOptions in
// playerSlot's home rather than the sender's.
//
// LANAPI slot 45, retail 0x0024A348 (1088 bytes), named by address: the rest
// of Zero Hour's OnGameOptions, everything but slot 46's branch. Same sender,
// in-progress and host checks; "User=" and "Host=" go to the slot's rowed
// setters 0x0024955E / 0x00249595. When we host and the sender is not us,
// refresh the sender's last-heard time (0x00248D35) and apply the request:
// Color, PlayerTemplate, StartPos, Team as in ZH but without the color
// availability loop or the StartPos upper bound, a StartPos also vetted by
// the open game setup screen (0x00E0333C, 0x0043DCFA) and stored at +0x10 and
// +0x14, and BFME 2's Hero (decodeHero, a change when +0x50..+0x5C move),
// Handicap (0, -5 .. -100) and NAT (1..0x80, +0x40). A change resets the
// accepts (GameInfo slot 14) unless only the color or NAT moved, broadcasts
// the game (slot 26) and refreshes the slot list. The flat host check and
// the direct 0x00248D35 call (no inline wrapper) give retail's allocation:
// edi as the zero register, then the slot, and ebx lent to the old hero kind.
//
// LANAPI::OnGameJoin, retail 0x00249D46 (897 bytes), slot 34: Open-BFME-1's
// LANAPIOnGameJoin.cpp (third argument the join message, the lobby at
// 0x00E03354 taking the success through its OnGameJoin 0x00446A1C, the
// headless timeout retry through RequestGameJoin, slot 16, and the lobby's
// 0x00444357 before the failure box) with BFME 2's preferences: nothing
// without TheLAN's game (GetMyGame, slot 56), LANPreferences keyed by the
// game's mode (+0x5C), and unless the game's byte +0x8C is set the preferred
// template, color and hero (GameModePreferences 0x0044D88C, 0x0044D836 and
// 0x0044D774 into a scratch GameSlot, sent as encodeHero) go out first, the
// hero kind (+0x5C) also handed to the open game setup screen (0x00E0333C,
// +0x2B4). RequestGameOptions is slot 25; both requests take a zeroed
// address temporary by reference.

typedef int Int;
typedef bool Bool;
typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned short WideChar;

#include "ascii_string.h"
#include "unicode_string.h"

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
	const BfmeNetAddress *self( void ) const { return this; }

	UnsignedInt m_ip;
	UnsignedShort m_port;
};

// The zero address of a SYSTEM line nobody sent, built as a temporary.
struct NoAddress : public BfmeNetAddress
{
	NoAddress( void ) { m_ip = 0; m_port = 0; }
};

class LANAPIInterface
{
public:
	enum ChatType
	{
		LANCHAT_NORMAL = 0,
		LANCHAT_TYPE1,
		LANCHAT_EMOTE,
		LANCHAT_SYSTEM
	};
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
		RET_BUSY
	};

	UnicodeString getErrorStringFromReturnType( ReturnType ret );
};

enum FirewallType
{
	FIREWALL_TYPE_SIMPLE = 1
};

enum
{
	MAX_SLOTS = 8
};

enum
{
	PLAYERTEMPLATE_OBSERVER = -2,
	PLAYERTEMPLATE_MIN = PLAYERTEMPLATE_OBSERVER
};

class GameSlot
{
public:
	GameSlot( void );
	virtual ~GameSlot( void );
	UnsignedByte encodeHero( void ) const;
	void setMapAvailability( Bool hasMap );
	Bool isHuman( void ) const;
	Bool decodeHero( UnsignedByte hero );
	void setPlayerTemplate( Int playerTemplate );
	Int getColor( void ) const { return m_color; }
	void setColor( Int color ) { m_color = color; }
	Int getStartPos( void ) const { return m_startPos; }
	void setStartPos( Int startPos ) { m_startPos = startPos; }
	void setBfme14( Int startPos ) { m_bfme14 = startPos; }
	Int getPlayerTemplate( void ) const { return m_playerTemplate; }
	Int getTeamNumber( void ) const { return m_teamNumber; }
	void setTeamNumber( Int teamNumber ) { m_teamNumber = teamNumber; }
	void setHandicap( Int handicap ) { m_handicap = handicap; }
	void setNATBehavior( Int behavior ) { m_NATBehavior = behavior; }
	const UnicodeString &getName( void ) const { return m_name; }

private:
	UnsignedByte m_pre0C[0x0C - 4];
	Int m_color;					// +0x0C
	Int m_startPos;					// +0x10
	Int m_bfme14;					// +0x14, set with the start position
	Int m_playerTemplate;				// +0x18
	Int m_teamNumber;				// +0x1C
	Int m_handicap;					// +0x20
	UnsignedByte m_pre30[0x30 - 0x24];
	UnicodeString m_name;				// +0x30
	UnsignedByte m_pre38[0x38 - 0x34];

public:
	BfmeNetAddress m_address;			// +0x38
	Int m_NATBehavior;				// +0x40
	UnsignedByte m_pre4C[0x4C - 0x44];
	Int m_bfme4C;					// +0x4C, the living-world battle's index
	Int m_hero[4];					// +0x50, what decodeHero sets
	UnsignedByte m_pre1A4[0x1A4 - 0x60];
	Bool m_bfme1A4;					// +0x1A4
	UnsignedByte m_pre1AC[0x1AC - 0x1A5];
};

// The LAN slot's login and host setters (0x0024955E, 0x00249595), under the
// ledger's class name.
class Rva0024955E : public GameSlot
{
public:
	void rva0024955E( AsciiString login );
	void rva00249595( AsciiString host );
};

struct LANSlotAddress
{
	UnsignedByte m_pre38[0x38];
	BfmeNetAddress m_address;			// slot +0x38
	UnsignedByte m_rest[0x1D0 - 0x40];
};

class GameTextInterface
{
public:
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
	virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
	virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14();
	virtual UnicodeString fetch( const char *label, Bool *exists = 0 );	// slot 15 (+0x3C)
	virtual void v16();
	virtual const UnicodeString *fetchPointer( const char *label, Bool *exists );	// slot 17 (+0x44)
};
extern GameTextInterface *TheGameText;

class MapMetaData
{
public:
	UnicodeString bfme_getDisplayName( Bool full );
};

class MapCache
{
public:
	void updateCache( void );
	const MapMetaData *findMap( AsciiString mapName );
};
extern MapCache *TheMapCache;

class GlobalData
{
public:
	UnsignedByte m_preAC0[0xAC0];
	AsciiString m_pendingFile;			// +0xAC0
};
extern GlobalData *TheWritableGlobalData;

class GameInfo
{
public:
	virtual ~GameInfo();
	virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
	virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
	virtual void v9(); virtual void v10();
	virtual void startGame( Int gameID );		// slot 11 (+0x2C)
	virtual void v12(); virtual void v13();
	virtual void resetAccepted( void );		// slot 14 (+0x38)

	GameSlot *getSlot( Int slotNum );
	AsciiString getMap( void ) const;
	void setMapForwarder( AsciiString mapName );

	Bool isGameInProgress( void ) const { return m_inProgress; }
	UnsignedInt getSeed( void ) const { return m_seed; }

protected:
	UnsignedByte m_pre11[0x11 - 4];
	Bool m_inProgress;				// +0x11
	UnsignedByte m_pre38[0x38 - 0x12];

public:
	BfmeNetAddress m_localAddress;			// +0x38

protected:
	UnsignedByte m_pre50[0x50 - 0x40];
	UnsignedInt m_seed;				// +0x50
	UnsignedByte m_pre58[0x58 - 0x54];

public:
	Int m_bfme58;					// +0x58
	Int m_gameMode;					// +0x5C, the preferences' mode

protected:
	UnsignedByte m_pre8C[0x8C - 0x60];

public:
	Bool m_bfme8C;					// +0x8C, keeps the preferred side

protected:
	UnsignedByte m_preDC[0xDC - 0x8D];
	LANSlotAddress m_slots[MAX_SLOTS];		// +0xDC, addresses from +0x114
};

Bool Rva00300E42( GameInfo *game );

// LANGameInfo, under the ledger's names for the classes of its getLANSlot
// (0x00447773) and its destructor (0x004482FB).
class Rva00447773 : public GameInfo
{
public:
	void *rva00447773( Int index );			// getLANSlot

	Rva0024955E *getLANSlot( Int index ) { return (Rva0024955E *)rva00447773( index ); }
	const BfmeNetAddress *getSlotAddress( Int index ) const { return &m_slots[index].m_address; }
};

class Rva004482FB : public Rva00447773
{
public:
	Int rva004483BC( UnicodeString name );		// getSlotNum

	const BfmeNetAddress *getHostAddress( void ) const { return &m_slots[0].m_address; }
};
// setPlayerLastHeard (0x00248D35), under the ledger's class name; retail
// calls it on the current game directly, not through an inline wrapper.
class Rva00248D35
{
public:
	void rva00248D35( Int index, Int value );
};

class LANGameInfo : public Rva004482FB
{
public:
	Bool amIHost( void ) const;
	void setLastHeard( UnsignedInt lastHeard ) { m_lastHeard = lastHeard; }

private:
	UnsignedInt m_preF60;
	UnsignedInt m_lastHeard;			// +0xF60
};

AsciiString GameInfoToAsciiString( const GameInfo *game, Bool flag );
Bool ParseGameOptionsString( LANGameInfo *game, AsciiString options, const void *data, Int length );

class MultiplayerColorDefinition
{
public:
	Int getColor( void ) const { return m_color; }

private:
	UnsignedByte m_pre10[0x10];
	Int m_color;					// +0x10
};

class MultiplayerSettings
{
public:
	MultiplayerColorDefinition *getColor( Int which );
	Int getNumColors( void )
	{
		if( m_numColors == 0 )
			m_numColors = m_colorCount;
		return m_numColors;
	}

private:
	UnsignedByte m_pre38[0x38];
	Int m_colorCount;				// +0x38
	UnsignedByte m_pre40[0x40 - 0x3C];
	Int m_numColors;				// +0x40
};
extern MultiplayerSettings *TheMultiplayerSettings;

class LanguageFilter
{
public:
	void filterLine( UnicodeString &line );
};
extern LanguageFilter *TheLanguageFilter;

extern const Int chatActionColor;
extern const Int chatLocalActionColor;
extern const Int chatSystemColor;

void Rva00381C82AddChatText( Int window, const UnicodeString &text, Int color );

class Shell
{
public:
	void push( AsciiString filename, Bool shutdownImmediate = false );
	void rva0035BEC7( void );
};
extern Shell *TheShell;
extern Bool LANbuttonPushed;

struct Rva004469D1Receiver;
extern Rva004469D1Receiver *g_Va00E03354;

class AptLanLobby
{
public:
	void OnGameJoin( void );
	void rva00444E8A( void );
};

class Rva00444357DwordImmSetter
{
public:
	void apply( void );
};

class Rva00444462
{
public:
	void rva00444462( void );
};

void Rva00248D84Enable( void );
void Rva00248E98Enable( void );

// Retries of an options update from the host that leaves us out of the game.
extern Int LANGameOptionsRetries;

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime( void );

// BFME 2's CreateTheNetwork (0x0025E46D): replaces TheNetwork with a new BFME2NativeNetwork.
void CreateTheNetwork( void );

class NetworkInterface
{
public:
	virtual ~NetworkInterface();
	virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
	virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
	virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12();
	virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16();
	virtual void parseUserList( const GameInfo *game );		// slot 17 (+0x44)
	virtual void setLocalAddress( const BfmeNetAddress *address );	// slot 18 (+0x48)
	virtual void v19();
	virtual void initTransport( void );				// slot 20 (+0x50)
};
extern NetworkInterface *TheNetwork;

class GameLogic
{
public:
	void rva00376E92( Bool first, Bool second );

	UnsignedByte m_pre9D[0x9D];
	Bool m_bfme9D;					// +0x9D, set as a LAN game starts
};
extern GameLogic *TheGameLogic;

class LivingWorldManager
{
public:
	void rva0021427A( void );
};
extern LivingWorldManager *TheLivingWorldManager;

struct Rva003EFDDBOut;

class Rva003EFDDBHolder
{
public:
	void rva003EFDDB( Int index, Rva003EFDDBOut *out );

	UnsignedByte m_pre18[0x18];
	AsciiString m_mapName;				// +0x18
};

class LivingWorldBattle
{
public:
	Bool rva003F486C( Int index );

	UnsignedByte m_pre24[0x24];
	Rva003EFDDBHolder *m_holder;			// +0x24
};

class LivingWorldLogic
{
public:
	UnsignedByte m_preEC[0xEC];
	Int m_bfmeEC;					// +0xEC
};
extern LivingWorldLogic *TheLivingWorldLogic;

class Rva002D3627Host
{
public:
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
	virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
	virtual void v8(); virtual void v9();
	virtual void rva10( Int value );			// slot 10 (+0x28)
};
extern Rva002D3627Host *g_00DFEF18;

class GameMessage
{
public:
	void appendIntegerArgument( Int arg );
};

class MessageStream
{
public:
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
	virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
	virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17();
	virtual GameMessage *appendMessage( Int type );	// slot 18 (+0x48)
};
extern MessageStream *MessageStreamSubsystem;

extern Int g_Va00E0333C;

class AptMpGameSetup
{
public:
	Bool rva0043DCFA( Int startPos );

	UnsignedByte m_pre2B4[0x2B4];
	Int m_pendingHero;				// +0x2B4
};

class GameModePreferences
{
public:
	virtual ~GameModePreferences( void );
	Bool rva0044D774( GameSlot *slot );		// the preferred hero
	Int rva0044D836( void );			// the preferred color
	Int rva0044D88C( void );			// the preferred player template

private:
	UnsignedByte m_body[0x1C - 4];
};

class LANPreferences : public GameModePreferences
{
public:
	LANPreferences( Int mode );
	virtual ~LANPreferences( void );
};

extern "C" __declspec(dllimport) char * __cdecl getenv( const char *name );
struct LANMessage;

class PlayerTemplate
{
	UnsignedByte m_data[0x1DC];
};

class PlayerTemplateStore
{
public:
	Int getPlayerTemplateCount( void ) const { return m_end - m_begin; }

private:
	UnsignedByte m_pre0C[0x0C];
	PlayerTemplate *m_begin;			// +0x0C
	PlayerTemplate *m_end;				// +0x10
};
extern PlayerTemplateStore *ThePlayerTemplateStore;

extern "C" __declspec(dllimport) Int __cdecl atoi( const char *text );

Bool Rva0044C3D4( void );
class GameWindow;
GameWindow *MessageBoxOk( UnicodeString titleString, UnicodeString bodyString, void (*okCallback)( void ) );
Bool DoAnyMapTransfers( GameInfo *game );
void InitGameLogicRandom( UnsignedInt seed );

#define BFME_VSLOT(n) virtual void slot##n( void ) = 0;

class LANAPI
{
public:
	BFME_VSLOT(00) BFME_VSLOT(01) BFME_VSLOT(02) BFME_VSLOT(03) BFME_VSLOT(04)
	BFME_VSLOT(05) BFME_VSLOT(06) BFME_VSLOT(07) BFME_VSLOT(08) BFME_VSLOT(09)
	BFME_VSLOT(10) BFME_VSLOT(11) BFME_VSLOT(12) BFME_VSLOT(13) BFME_VSLOT(14)
	BFME_VSLOT(15)
	virtual void RequestGameJoin( LANGameInfo *game, const BfmeNetAddress &ip = NoAddress() ) = 0;
	BFME_VSLOT(17) BFME_VSLOT(18) BFME_VSLOT(19)
	BFME_VSLOT(20) BFME_VSLOT(21) BFME_VSLOT(22) BFME_VSLOT(23) BFME_VSLOT(24)
	virtual void RequestGameOptions( AsciiString gameOptions, Bool isPublic,
		const BfmeNetAddress &ip = NoAddress() ) = 0;
	virtual void rva004497EC( Bool isPublic, BfmeNetAddress *ip ) = 0;
	BFME_VSLOT(27) BFME_VSLOT(28) BFME_VSLOT(29)
	BFME_VSLOT(30) BFME_VSLOT(31) BFME_VSLOT(32) BFME_VSLOT(33)
	virtual void OnGameJoin( LANAPIInterface::ReturnType ret, LANGameInfo *theGame, LANMessage *msg );
	BFME_VSLOT(35) BFME_VSLOT(36)
	virtual void OnPlayerLeave( UnicodeString player );
	BFME_VSLOT(38)
	virtual void OnHasMap( const BfmeNetAddress *ip, Bool status );
	virtual void OnChat( const UnicodeString &player, const BfmeNetAddress *ip,
		const UnicodeString &message, LANAPIInterface::ChatType format );
	virtual void rva00249B08( LivingWorldBattle *battle );
	virtual void OnGameStart( void );
	virtual void OnWOTRGameStart( void );
	BFME_VSLOT(44)
	virtual void rva0024A348( const BfmeNetAddress &sender, Int playerSlot, AsciiString options );
	virtual Bool rva0024924D( const BfmeNetAddress &sender, Int playerSlot, const void *data, Int length );
	BFME_VSLOT(47) BFME_VSLOT(48) BFME_VSLOT(49)
	BFME_VSLOT(50) BFME_VSLOT(51) BFME_VSLOT(52) BFME_VSLOT(53)
	virtual Int AmIHost( void ) = 0;
	BFME_VSLOT(55)
	virtual LANGameInfo *GetMyGame( void ) = 0;
	BFME_VSLOT(57) BFME_VSLOT(58) BFME_VSLOT(59)
	BFME_VSLOT(60) BFME_VSLOT(61) BFME_VSLOT(62) BFME_VSLOT(63)
	virtual BfmeNetAddress *getLocalAddress( void ) = 0;

protected:
	UnsignedByte m_pre14[0x14 - 4];
	UnicodeString m_name;				// +0x14
	AsciiString m_userName;				// +0x18
	AsciiString m_hostName;				// +0x1C
	UnsignedByte m_pre3C[0x3C - 0x20];
	UnsignedInt m_lastResendTime;			// +0x3C
	Bool m_isInLANMenu;				// +0x40
	Bool m_inLobby;					// +0x41
	LANGameInfo *m_currentGame;			// +0x44

	void removeGame( LANGameInfo *game );
};

#undef BFME_VSLOT
extern LANAPI *TheLAN;

void LANAPI::OnGameJoin( LANAPIInterface::ReturnType ret, LANGameInfo *theGame, LANMessage *msg )
{
	if( ret == LANAPIInterface::RET_OK )
	{
		if( g_Va00E03354 )
			((AptLanLobby *)g_Va00E03354)->OnGameJoin();
		else
		{
			LANbuttonPushed = true;
			TheShell->push( AsciiString( "Menus/LanGameOptionsMenu.wnd" ), false );
		}

		LANGameInfo *game = TheLAN->GetMyGame();
		if( !game )
			return;

		LANPreferences pref( game->m_gameMode );
		AsciiString options;
		if( !TheLAN->GetMyGame()->m_bfme8C )
		{
			options.format( "PlayerTemplate=%d", pref.rva0044D88C() );
			RequestGameOptions( options, true );
			options.format( "Color=%d", pref.rva0044D836() );
			RequestGameOptions( options, true );
			GameSlot slot;
			pref.rva0044D774( &slot );
			options.format( "Hero=%d", slot.encodeHero() );
			RequestGameOptions( options, true );
			if( g_Va00E0333C )
				((AptMpGameSetup *)g_Va00E0333C)->m_pendingHero = slot.m_hero[3];
		}
		options.format( "User=%s", m_userName.str() );
		RequestGameOptions( options, true );
		options.format( "Host=%s", m_hostName.str() );
		RequestGameOptions( options, true );
		options.format( "NAT=%d", FIREWALL_TYPE_SIMPLE );
		RequestGameOptions( options, true );
	}
	else if( ret != LANAPIInterface::RET_BUSY )
	{
		if( getenv( "_EA_RTS_HEADLESS" ) && ret == LANAPIInterface::RET_TIMEOUT && theGame )
		{
			RequestGameJoin( theGame );
			return;
		}

		UnicodeString title, body;
		title = TheGameText->fetch( "LAN:JoinFailed" );
		body = ((LANAPIInterface *)this)->getErrorStringFromReturnType( ret );
		if( g_Va00E03354 )
			((Rva00444357DwordImmSetter *)g_Va00E03354)->apply();
		MessageBoxOk( title, body, 0 );
	}
}

void LANAPI::OnPlayerLeave( UnicodeString player )
{
	LANGameInfo *game;
	if( m_inLobby || ( game = m_currentGame ) == 0 || game->isGameInProgress() )
		return;

	if( m_name.compare( player ) == 0 )
	{
		if( !g_Va00E03354 )
		{
			TheShell->rva0035BEC7();
			LANbuttonPushed = true;
		}
		else
		{
			((AptLanLobby *)g_Va00E03354)->rva00444E8A();
		}
	}
	else
	{
		const BfmeNetAddress *host = game->getHostAddress();
		if( host->Rva00248CBF( getLocalAddress() ) )
		{
			m_lastResendTime = 0;
			Rva00248D84Enable();
			BfmeNetAddress noAddress;
			noAddress.m_ip = 0;
			noAddress.m_port = 0;
			rva004497EC( true, &noAddress );
		}
	}
}

void LANAPI::OnChat( const UnicodeString &player, const BfmeNetAddress *ip,
	const UnicodeString &message, LANAPIInterface::ChatType format )
{
	UnicodeString unicodeChat;
	switch( format )
	{
		case LANAPIInterface::LANCHAT_TYPE1:
			unicodeChat = L"[";
			unicodeChat.concat( player );
			unicodeChat.concat( L"] " );
			unicodeChat.concat( message );
			TheLanguageFilter->filterLine( unicodeChat );
			if( ip->Rva00248CBF( getLocalAddress() ) )
				Rva00381C82AddChatText( 0, unicodeChat, -1 );
			else
				Rva00381C82AddChatText( 0, unicodeChat, -1 );
			break;
		case LANAPIInterface::LANCHAT_EMOTE:
			unicodeChat = player;
			{
				WideChar space = L' ';
				unicodeChat.concat( &space, 1 );
			}
			unicodeChat.concat( message );
			if( ip->Rva00248CBF( getLocalAddress() ) )
				Rva00381C82AddChatText( 1, unicodeChat, chatLocalActionColor );
			else
				Rva00381C82AddChatText( 1, unicodeChat, chatActionColor );
			break;
		case LANAPIInterface::LANCHAT_SYSTEM:
			unicodeChat = L"";
			unicodeChat.concat( message );
			unicodeChat.concat( L"" );
			Rva00381C82AddChatText( 1, unicodeChat, chatSystemColor );
			break;
		case LANAPIInterface::LANCHAT_NORMAL:
		default:
		{
			Int chatColor = -1;
			if( m_currentGame )
			{
				Int slotNum = m_currentGame->rva004483BC( player );
				if( slotNum >= 0 )
				{
					GameSlot *gs = m_currentGame->getSlot( slotNum );
					if( gs )
					{
						MultiplayerColorDefinition *def = TheMultiplayerSettings->getColor( gs->getColor() );
						if( def )
							chatColor = def->getColor();
					}
				}
			}

			unicodeChat = L"[";
			unicodeChat.concat( player );
			unicodeChat.concat( L"] " );
			unicodeChat.concat( message );
			TheLanguageFilter->filterLine( unicodeChat );
			if( ip->Rva00248CBF( getLocalAddress() ) )
				Rva00381C82AddChatText( 1, unicodeChat, chatColor );
			else
				Rva00381C82AddChatText( 1, unicodeChat, chatColor );
			break;
		}
	}
}

void LANAPI::OnHasMap( const BfmeNetAddress *ip, Bool status )
{
	if( !(UnsignedByte)AmIHost() )
		return;

	LANGameInfo *game = m_currentGame;
	Int i;
	for( i = 0; i < MAX_SLOTS; ++i )
	{
		if( game->getSlotAddress( i )->Rva00248CBF( ip ) )
		{
			game->getLANSlot( i )->setMapAvailability( status );
			break;
		}
	}
	if( i == MAX_SLOTS )
		return;

	UnicodeString mapDisplayName;
	const MapMetaData *mapData = TheMapCache->findMap( m_currentGame->getMap() );
	Bool willTransfer = Rva00300E42( m_currentGame );
	if( mapData )
	{
		mapDisplayName.format( L"%ls", ((MapMetaData *)mapData)->bfme_getDisplayName( true ).str() );
	}
	else
	{
		mapDisplayName.format( L"%hs", m_currentGame->getMap().str() );
	}

	if( !status )
	{
		UnicodeString text;
		if( willTransfer )
			text.format( TheGameText->fetchPointer( "GUI:PlayerNoMapWillTransfer", 0 ),
				m_currentGame->getLANSlot( i )->getName().str(), mapDisplayName.str() );
		else
			text.format( TheGameText->fetchPointer( "GUI:PlayerNoMap", 0 ),
				m_currentGame->getLANSlot( i )->getName().str(), mapDisplayName.str() );
		OnChat( UnicodeString( L"SYSTEM" ), getLocalAddress(), text, LANAPIInterface::LANCHAT_SYSTEM );
	}
	Rva00248D84Enable();
}

void LANAPI::rva00249B08( LivingWorldBattle *battle )
{
	if( !battle )
		return;

	Rva003EFDDBHolder *battleHolder = battle->m_holder;
	const char *name = battleHolder->m_mapName.str();
	AsciiString mapName;
	mapName.format( "maps\\%s\\%s.map", name, name );
	TheWritableGlobalData->m_pendingFile.format( &mapName );

	if( m_currentGame )
	{
		m_currentGame->setMapForwarder( mapName );
		Bool filesOk = DoAnyMapTransfers( m_currentGame );

		TheMapCache->updateCache();
		if( !filesOk || TheMapCache->findMap( m_currentGame->getMap() ) == 0 )
		{
			OnPlayerLeave( m_name );
			removeGame( m_currentGame );
			::delete m_currentGame;
			m_currentGame = 0;
			m_inLobby = true;
			if( TheNetwork )
			{
				::delete TheNetwork;
				TheNetwork = 0;
			}
			MessageBoxOk( TheGameText->fetch( "GUI:ErrorStartingGame" ),
				TheGameText->fetch( "GUI:CouldNotTransferMap" ), 0 );
			OnChat( UnicodeString::TheEmptyString, NoAddress().self(),
				TheGameText->fetch( "GUI:CouldNotTransferMap" ), LANAPIInterface::LANCHAT_SYSTEM );
			return;
		}

		for( Int i = 0; i < MAX_SLOTS; ++i )
		{
			GameSlot *slot = m_currentGame->getSlot( i );
			Int index = slot->m_bfme4C;
			Rva003EFDDBHolder *holder = battle->m_holder;
			holder->rva003EFDDB( index, (Rva003EFDDBOut *)slot );
			slot->m_bfme1A4 = battle->rva003F486C( index );
		}

		m_currentGame->startGame( 0 );
		TheWritableGlobalData->m_pendingFile = m_currentGame->getMap();
		InitGameLogicRandom( m_currentGame->getSeed() );
	}
}

void LANAPI::OnGameStart( void )
{
	if( m_currentGame )
	{
		m_isInLANMenu = false;

		CreateTheNetwork();
		BfmeNetAddress localAddress = *getLocalAddress();
		localAddress.m_port += 8;
		TheNetwork->setLocalAddress( &localAddress );
		TheNetwork->initTransport();
		LANGameInfo *game = m_currentGame;
		game->m_localAddress = localAddress;

		for( Int i = 0; i < MAX_SLOTS; ++i )
		{
			GameSlot *slot = m_currentGame->getSlot( i );
			if( m_currentGame->getSlot( i )->isHuman() )
			{
				BfmeNetAddress address = slot->m_address;
				address.m_port += 8;
				slot->m_address = address;
			}
		}

		TheNetwork->parseUserList( m_currentGame );
		TheGameLogic->rva00376E92( false, false );

		Bool heroesOk = Rva0044C3D4();
		if( !heroesOk )
		{
			OnPlayerLeave( m_name );
			removeGame( m_currentGame );
			::delete m_currentGame;
			m_currentGame = 0;
			m_inLobby = true;
			if( TheNetwork )
			{
				::delete TheNetwork;
				TheNetwork = 0;
			}
			MessageBoxOk( TheGameText->fetch( "GUI:ErrorStartingGame" ),
				TheGameText->fetch( "GUI:CouldNotTransferHero" ), 0 );
			OnChat( UnicodeString::TheEmptyString, NoAddress().self(),
				TheGameText->fetch( "GUI:CouldNotTransferHero" ), LANAPIInterface::LANCHAT_SYSTEM );
			return;
		}

		Bool filesOk = DoAnyMapTransfers( m_currentGame );

		TheMapCache->updateCache();
		if( !filesOk || TheMapCache->findMap( m_currentGame->getMap() ) == 0 )
		{
			OnPlayerLeave( m_name );
			removeGame( m_currentGame );
			::delete m_currentGame;
			m_currentGame = 0;
			m_inLobby = true;
			if( TheNetwork )
			{
				::delete TheNetwork;
				TheNetwork = 0;
			}
			MessageBoxOk( TheGameText->fetch( "GUI:ErrorStartingGame" ),
				TheGameText->fetch( "GUI:CouldNotTransferMap" ), 0 );
			OnChat( UnicodeString::TheEmptyString, NoAddress().self(),
				TheGameText->fetch( "GUI:CouldNotTransferMap" ), LANAPIInterface::LANCHAT_SYSTEM );
			return;
		}

		m_currentGame->startGame( 0 );
		TheWritableGlobalData->m_pendingFile = m_currentGame->getMap();

		GameMessage *msg = MessageStreamSubsystem->appendMessage( 0x1E );
		msg->appendIntegerArgument( 1 );
		TheGameLogic->m_bfme9D = true;

		InitGameLogicRandom( m_currentGame->getSeed() );
	}
}

void LANAPI::OnWOTRGameStart( void )
{
	if( m_currentGame )
	{
		m_isInLANMenu = false;

		CreateTheNetwork();
		BfmeNetAddress localAddress = *getLocalAddress();
		localAddress.m_port += 8;
		TheNetwork->setLocalAddress( &localAddress );
		TheNetwork->initTransport();
		LANGameInfo *game = m_currentGame;
		game->m_localAddress = localAddress;

		for( Int i = 0; i < MAX_SLOTS; ++i )
		{
			GameSlot *slot = m_currentGame->getSlot( i );
			if( m_currentGame->getSlot( i )->isHuman() )
			{
				BfmeNetAddress address = slot->m_address;
				address.m_port += 8;
				slot->m_address = address;
			}
		}

		TheNetwork->parseUserList( m_currentGame );
		TheGameLogic->rva00376E92( false, false );

		Bool filesOk = Rva0044C3D4();
		if( !filesOk )
		{
			OnPlayerLeave( m_name );
			removeGame( m_currentGame );
			::delete m_currentGame;
			m_currentGame = 0;
			m_inLobby = true;
			if( TheNetwork )
			{
				::delete TheNetwork;
				TheNetwork = 0;
			}
			MessageBoxOk( TheGameText->fetch( "GUI:ErrorStartingGame" ),
				TheGameText->fetch( "GUI:CouldNotTransferHero" ), 0 );
			OnChat( UnicodeString::TheEmptyString, NoAddress().self(),
				TheGameText->fetch( "GUI:CouldNotTransferHero" ), LANAPIInterface::LANCHAT_SYSTEM );
			return;
		}

		m_currentGame->startGame( 0 );
		if( TheLivingWorldManager )
			TheLivingWorldManager->rva0021427A();
		TheLivingWorldLogic->m_bfmeEC = 0;
		TheGameLogic->rva00376E92( false, false );
		g_00DFEF18->rva10( 1 );

		GameMessage *msg = MessageStreamSubsystem->appendMessage( 0x1F );
		if( msg && g_Va00E0333C )
		{
			msg->appendIntegerArgument( m_currentGame->m_bfme58 );
			msg->appendIntegerArgument( 1 );
		}

		InitGameLogicRandom( m_currentGame->getSeed() );
	}
}

Bool LANAPI::rva0024924D( const BfmeNetAddress &sender, Int playerSlot, const void *data, Int length )
{
	LANGameInfo *game = m_currentGame;
	if( !game )
		return false;
	if( game->getSlotAddress( playerSlot )->rva00248CDD( sender ) )
		return false;
	if( game->isGameInProgress() )
		return false;

	if( playerSlot == 0 && !game->amIHost() )
	{
		m_currentGame->setLastHeard( timeGetTime() );
		AsciiString oldOptions = GameInfoToAsciiString( m_currentGame, true );
		Bool booted = true;
		if( ParseGameOptionsString( m_currentGame, AsciiString( "" ), data, length ) )
		{
			for( Int player = 1; player < MAX_SLOTS; ++player )
			{
				if( m_currentGame->getSlotAddress( player )->Rva00248CBF( getLocalAddress() ) )
				{
					booted = false;
					break;
				}
			}
		}

		if( booted )
		{
			// restore the options with us in
			++LANGameOptionsRetries;
			ParseGameOptionsString( m_currentGame, oldOptions, 0, 0 );
			if( LANGameOptionsRetries > 16 )
			{
				OnPlayerLeave( m_name );
				LANGameOptionsRetries = 0;
			}
			return false;
		}

		Rva00248D84Enable();
		if( !g_Va00E03354 )
			Rva00248E98Enable();
		else
			((Rva00444462 *)g_Va00E03354)->rva00444462();
		LANGameOptionsRetries = 0;
		return true;
	}
	return false;
}

void LANAPI::rva0024A348( const BfmeNetAddress &sender, Int playerSlot, AsciiString options )
{
	LANGameInfo *game = m_currentGame;
	if( !game )
		return;
	if( game->getSlotAddress( playerSlot )->rva00248CDD( sender ) )
		return;
	if( game->isGameInProgress() )
		return;
	if( playerSlot == 0 && !game->amIHost() )
		return;

	// Check for user/host updates
	{
		AsciiString key;
		AsciiString munkee = options;
		munkee.nextToken( &key, "=" );

		Rva0024955E *slot = m_currentGame->getLANSlot( playerSlot );
		if( !slot )
			return;

		if( key.compare( "User" ) == 0 )
		{
			slot->rva0024955E( AsciiString( munkee.str() + 1 ) );
			return;
		}
		else if( key.compare( "Host" ) == 0 )
		{
			slot->rva00249595( AsciiString( munkee.str() + 1 ) );
			return;
		}
	}

	// Parse player requests (side, color, etc)
	if( !(UnsignedByte)AmIHost() || !getLocalAddress()->rva00248CDD( sender ) )
		return;
	if( options.compare( "HELLO" ) == 0 )
	{
		((Rva00248D35 *)m_currentGame)->rva00248D35( playerSlot, timeGetTime() );
	}
	else
	{
		((Rva00248D35 *)m_currentGame)->rva00248D35( playerSlot, timeGetTime() );
		Bool change = false;
		Bool shouldUnaccept = false;
		AsciiString key;
		options.nextToken( &key, "=" );
		Int val = atoi( options.str() + 1 );

		GameSlot *slot = m_currentGame->getLANSlot( playerSlot );
		if( !slot )
			return;

		if( key.compare( "Color" ) == 0 )
		{
			if( val >= -1 && val < TheMultiplayerSettings->getNumColors() && val != slot->getColor() && slot->getPlayerTemplate() != PLAYERTEMPLATE_OBSERVER )
			{
				slot->setColor( val );
				change = true;
			}
		}
		else if( key.compare( "PlayerTemplate" ) == 0 )
		{
			if( val >= PLAYERTEMPLATE_MIN && val < ThePlayerTemplateStore->getPlayerTemplateCount() && val != slot->getPlayerTemplate() )
			{
				slot->setPlayerTemplate( val );
				if( val == PLAYERTEMPLATE_OBSERVER )
				{
					slot->setColor( -1 );
					slot->setStartPos( -1 );
					slot->setTeamNumber( -1 );
				}
				change = true;
				shouldUnaccept = true;
			}
		}
		else if( key.compare( "StartPos" ) == 0 && slot->getPlayerTemplate() != PLAYERTEMPLATE_OBSERVER )
		{
			if( val >= -1 && val != slot->getStartPos() )
			{
				Bool startPosAvailable = true;
				if( val != -1 )
				{
					for( Int i = 0; i < MAX_SLOTS; i++ )
					{
						GameSlot *checkSlot = m_currentGame->getLANSlot( i );
						if( val == checkSlot->getStartPos() && slot != checkSlot )
						{
							startPosAvailable = false;
							break;
						}
					}
					if( startPosAvailable && g_Va00E0333C )
						startPosAvailable = ((AptMpGameSetup *)g_Va00E0333C)->rva0043DCFA( val );
				}
				if( startPosAvailable )
				{
					slot->setStartPos( val );
					slot->setBfme14( val );
				}
				change = true;
				shouldUnaccept = true;
			}
		}
		else if( key.compare( "Team" ) == 0 )
		{
			if( val >= -1 && val < MAX_SLOTS / 2 && val != slot->getTeamNumber() && slot->getPlayerTemplate() != PLAYERTEMPLATE_OBSERVER )
			{
				slot->setTeamNumber( val );
				change = true;
				shouldUnaccept = true;
			}
		}
		else if( key.compare( "Hero" ) == 0 )
		{
			if( slot->getPlayerTemplate() == PLAYERTEMPLATE_OBSERVER && val != 0 )
				val = 0;
			Int hero0 = slot->m_hero[0];
			Int hero1 = slot->m_hero[1];
			Int hero2 = slot->m_hero[2];
			Int hero3 = slot->m_hero[3];
			slot->decodeHero( (UnsignedByte)val );
			if( hero0 != slot->m_hero[0] || hero1 != slot->m_hero[1] || hero2 != slot->m_hero[2] || hero3 != slot->m_hero[3] )
			{
				change = true;
				shouldUnaccept = true;
			}
		}
		else if( key.compare( "Handicap" ) == 0 )
		{
			if( val <= 0 && val >= -100 && val % 5 == 0 )
			{
				slot->setHandicap( val );
				change = true;
				shouldUnaccept = true;
			}
		}
		else if( key.compare( "NAT" ) == 0 )
		{
			if( val >= 1 && val <= 0x80 )
			{
				slot->setNATBehavior( val );
				change = true;
			}
		}

		if( change )
		{
			if( shouldUnaccept )
				m_currentGame->resetAccepted();
			BfmeNetAddress noAddress;
			noAddress.m_ip = 0;
			noAddress.m_port = 0;
			rva004497EC( true, &noAddress );
			Rva00248D84Enable();
		}
	}
}
