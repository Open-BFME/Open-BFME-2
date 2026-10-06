// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /O1
//
// LANAPI callbacks of the vtable 0x0083E680, Zero Hour's
// GameNetwork/LANAPICallbacks.cpp.
//
// LANAPI::OnPlayerLeave, retail 0x0024A0C7 (177 bytes), slot 37 (dispatched
// at +0x94 by RequestGameLeave). Zero Hour's body without the preferences
// save: out of the lobby, with a current game that is not in progress (+0x11),
// a leave by our own name (m_name +0x14) hands off to the LAN menu at VA
// 0x00E03354 (its 0x00444E8A, rowed under the class name GameEngine) or, with
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
// LANAPI slot 43, retail 0x0024900D (576 bytes): a BFME 2 twin of
// OnGameStart (slot 42), whose body it repeats with the map transfer swapped
// for another check. Named by address. Like BFME 1's OnGameStart
// (Open-BFME-1's LANAPIOnGameStart.cpp) without the preferences save: leave
// the LAN menu (+0x40), create the network (the rowed 0x0025E46D),
// bind it and the game (+0x38) to the local address with the port bumped by
// 8, bump every human slot's address (+0x38) the same way, then
// parseUserList and TheGameLogic's two-flag 0x00376E92. When the cdecl
// transfer check 0x0044C3D4 fails, leave by our own name, drop and ::delete
// the game and TheNetwork, raise GUI:ErrorStartingGame /
// GUI:CouldNotTransferHero in the message box 0x0044C0A8 and post the body
// text as a SYSTEM line from no address. Otherwise start the game (vslot
// 11), poke the living-world manager and logic, post message 0x1F with the
// game's +0x58 and 1 when 0x00E0333C is set, and seed the logic random from
// +0x50. The check result is named (filesOk) for retail's cmp al,bl; the
// zero address is a temporary so its stores sink below the text fetch.

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
};

enum
{
	MAX_SLOTS = 8
};

class GameSlot
{
public:
	void setMapAvailability( Bool hasMap );
	Bool isHuman( void ) const;
	Int getColor( void ) const { return m_color; }
	const UnicodeString &getName( void ) const { return m_name; }

private:
	UnsignedByte m_pre0C[0x0C];
	Int m_color;					// +0x0C
	UnsignedByte m_pre30[0x30 - 0x10];
	UnicodeString m_name;				// +0x30
	UnsignedByte m_pre38[0x38 - 0x34];

public:
	BfmeNetAddress m_address;			// +0x38
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
	const MapMetaData *findMap( AsciiString mapName );
};
extern MapCache *TheMapCache;

class GameInfo
{
public:
	virtual ~GameInfo();
	virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
	virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
	virtual void v9(); virtual void v10();
	virtual void startGame( Int gameID );		// slot 11 (+0x2C)

	GameSlot *getSlot( Int slotNum );
	AsciiString getMap( void ) const;

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

protected:
	UnsignedByte m_preDC[0xDC - 0x5C];
	LANSlotAddress m_slots[MAX_SLOTS];		// +0xDC, addresses from +0x114
};

Bool Rva00300E42( GameInfo *game );

// LANGameInfo, under the ledger's names for the classes of its getLANSlot
// (0x00447773) and its destructor (0x004482FB).
class Rva00447773 : public GameInfo
{
public:
	void *rva00447773( Int index );			// getLANSlot

	GameSlot *getLANSlot( Int index ) { return (GameSlot *)rva00447773( index ); }
	const BfmeNetAddress *getSlotAddress( Int index ) const { return &m_slots[index].m_address; }
};

class Rva004482FB : public Rva00447773
{
public:
	Int rva004483BC( UnicodeString name );		// getSlotNum

	const BfmeNetAddress *getHostAddress( void ) const { return &m_slots[0].m_address; }
};
class LANGameInfo : public Rva004482FB
{
};

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
	void rva0035BEC7( void );
};
extern Shell *TheShell;
extern Bool LANbuttonPushed;

struct Rva004469D1Receiver;
extern Rva004469D1Receiver *g_Va00E03354;

class GameEngine
{
public:
	void rva00444E8A( void );
};

void Rva00248D84Enable( void );

// BFME 2's createTheNetwork: replaces TheNetwork with a new BFME2NativeNetwork.
void Rva0025E46DReset( void );

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
};
extern GameLogic *TheGameLogic;

class LivingWorldManager
{
public:
	void rva0021427A( void );
};
extern LivingWorldManager *TheLivingWorldManager;

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

Bool Rva0044C3D4( void );
void Rva0044C0A8( UnicodeString title, UnicodeString body, void *callback );
void InitGameLogicRandom( UnsignedInt seed );

#define BFME_VSLOT(n) virtual void slot##n( void ) = 0;

class LANAPI
{
public:
	BFME_VSLOT(00) BFME_VSLOT(01) BFME_VSLOT(02) BFME_VSLOT(03) BFME_VSLOT(04)
	BFME_VSLOT(05) BFME_VSLOT(06) BFME_VSLOT(07) BFME_VSLOT(08) BFME_VSLOT(09)
	BFME_VSLOT(10) BFME_VSLOT(11) BFME_VSLOT(12) BFME_VSLOT(13) BFME_VSLOT(14)
	BFME_VSLOT(15) BFME_VSLOT(16) BFME_VSLOT(17) BFME_VSLOT(18) BFME_VSLOT(19)
	BFME_VSLOT(20) BFME_VSLOT(21) BFME_VSLOT(22) BFME_VSLOT(23) BFME_VSLOT(24)
	BFME_VSLOT(25)
	virtual void rva004497EC( Bool isPublic, BfmeNetAddress *ip ) = 0;
	BFME_VSLOT(27) BFME_VSLOT(28) BFME_VSLOT(29)
	BFME_VSLOT(30) BFME_VSLOT(31) BFME_VSLOT(32) BFME_VSLOT(33) BFME_VSLOT(34)
	BFME_VSLOT(35) BFME_VSLOT(36)
	virtual void OnPlayerLeave( UnicodeString player );
	BFME_VSLOT(38)
	virtual void OnHasMap( const BfmeNetAddress *ip, Bool status );
	virtual void OnChat( const UnicodeString &player, const BfmeNetAddress *ip,
		const UnicodeString &message, LANAPIInterface::ChatType format );
	BFME_VSLOT(41) BFME_VSLOT(42)
	virtual void rva0024900D( void );
	BFME_VSLOT(44)
	BFME_VSLOT(45) BFME_VSLOT(46) BFME_VSLOT(47) BFME_VSLOT(48) BFME_VSLOT(49)
	BFME_VSLOT(50) BFME_VSLOT(51) BFME_VSLOT(52) BFME_VSLOT(53)
	virtual Int AmIHost( void ) = 0;
	BFME_VSLOT(55) BFME_VSLOT(56) BFME_VSLOT(57) BFME_VSLOT(58) BFME_VSLOT(59)
	BFME_VSLOT(60) BFME_VSLOT(61) BFME_VSLOT(62) BFME_VSLOT(63)
	virtual BfmeNetAddress *getLocalAddress( void ) = 0;

protected:
	UnsignedByte m_pre14[0x14 - 4];
	UnicodeString m_name;				// +0x14
	UnsignedByte m_pre3C[0x3C - 0x18];
	UnsignedInt m_lastResendTime;			// +0x3C
	Bool m_isInLANMenu;				// +0x40
	Bool m_inLobby;					// +0x41
	LANGameInfo *m_currentGame;			// +0x44

	void removeGame( LANGameInfo *game );
};

#undef BFME_VSLOT

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
			((GameEngine *)g_Va00E03354)->rva00444E8A();
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

void LANAPI::rva0024900D( void )
{
	if( m_currentGame )
	{
		m_isInLANMenu = false;

		Rva0025E46DReset();
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
			Rva0044C0A8( TheGameText->fetch( "GUI:ErrorStartingGame" ),
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
