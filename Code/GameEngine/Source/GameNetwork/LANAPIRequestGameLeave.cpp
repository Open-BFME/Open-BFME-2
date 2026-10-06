// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /O1
//
// LANAPI::RequestGameLeave, retail 0x0044A0CF (325 bytes): slot 18 of the
// LANAPI vtable 0x0083E680, between the rowed slot-17 join (0x00449FE8) and
// RequestAccept (slot 19). Ported from Open-BFME-1's
// LANAPIRequestGameLeave.cpp (BFME 1 retail 0x00687CE0), itself Zero Hour's
// LANAPI::RequestGameLeave with the host check: the host sends
// MSG_REQUEST_HOST_LEAVE (8), anyone else MSG_REQUEST_GAME_LEAVE (6); the host
// then leaves at once (OnPlayerLeave, removeGame, ::delete the game and
// re-enter the lobby), a joiner waits for ACT_LEAVE (3) to expire.
// BFME 2 differences: the host is the current game whose slot-0 address
// (+0x114: the slots at +0xDC, the address at slot +0x38) equals the local
// address (vslot 64), compared through the rowed BfmeNetAddress helper
// 0x00248CBF; the game is deleted through its virtual destructor with flag 0
// followed by the global operator delete.
// Built /EHsc, yet no EH frame: only the extern "C" wcsncpy runs while the
// conditional getName temporary lives, which is released under a flag; the
// by-value OnPlayerLeave argument still records its stack slot at [ebp-4].
// Members: m_name +0x14, m_pendingAction +0x28, m_expiration +0x2C,
// m_actionTimeout +0x30, m_inLobby +0x41, m_currentGame +0x44, m_transport
// +0x50. Callees: fillInLANMessage (vslot 57), OnPlayerLeave (vslot 37), the
// rowed send helper 0x004495A2, Transport::update 0x004D54C1 and removeGame
// 0x00449913.
//
// LANAPI::RequestChat, retail 0x0044A652 (267 bytes), slot 21: Zero Hour's
// body (message type MSG_CHAT 11, game name, chat type at +0x40, a 100-char
// message at +0x44, then OnChat). BFME 2 differences: OnChat is vslot 40
// taking both strings by reference and the local address from vslot 64; the
// body pops a third stack argument it never reads, which both retail callers
// (0x00381830, 0x00444916) pass as a pushed zero, so it is typed Int here.
//
// LANAPI::RequestEnableMPSetupUI, retail 0x0044A75D (171 bytes), slot 22:
// Open-BFME-1's LANAPIRequestEnableMPSetupUI.cpp (BFME 1 retail 0x00686780),
// MSG_ENABLE_MPSETUP_UI (12) with the Bool at +0x40, sent and flushed through
// Transport::update.

typedef int Int;
typedef bool Bool;
typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned short WideChar;

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime( void );
extern "C" __declspec(dllimport) WideChar * __cdecl wcsncpy(
	WideChar *, const WideChar *, unsigned int );

#include "unicode_string.h"

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
	MSG_CHAT = 11,
	MSG_ENABLE_MPSETUP_UI = 12,
	ACT_LEAVE = 3,
	LAN_GAME_NAME_LENGTH = 16,
	LAN_MAX_CHAT_LENGTH = 100
};

class LANAPIInterface
{
public:
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

class LANGameInfo
{
public:
	virtual ~LANGameInfo( void );
	virtual void slot01( void ) = 0; virtual void slot02( void ) = 0;
	virtual void slot03( void ) = 0; virtual void slot04( void ) = 0;
	virtual void slot05( void ) = 0; virtual void slot06( void ) = 0;
	virtual void slot07( void ) = 0; virtual void slot08( void ) = 0;
	virtual void slot09( void ) = 0; virtual void slot10( void ) = 0;
	virtual void slot11( void ) = 0; virtual void slot12( void ) = 0;
	virtual void slot13( void ) = 0; virtual void slot14( void ) = 0;
	virtual void slot15( void ) = 0; virtual void slot16( void ) = 0;
	virtual void slot17( void ) = 0; virtual void slot18( void ) = 0;
	virtual void slot19( void ) = 0; virtual void slot20( void ) = 0;
	virtual void slot21( void ) = 0; virtual void slot22( void ) = 0;
	virtual UnicodeString getName( void ) = 0;

	const BfmeNetAddress *getHostAddress( void ) const { return &m_hostAddress; }

private:
	UnsignedByte m_pre114[0x114 - 4];
	BfmeNetAddress m_hostAddress;			// +0x114, slot 0's address
};

#pragma pack(push, 1)
struct LANMessage
{
	Int LANMessageType;
	UnsignedByte m_prefix[0x1E - 4];
	union
	{
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
			LANAPIInterface::ChatType chatType;
			WideChar message[LAN_MAX_CHAT_LENGTH + 1];
		} Chat;
		UnsignedByte m_body[0x1D8 - 0x1E];
	};
};
#pragma pack(pop)

class Transport
{
public:
	Bool Rva004D54C1( Bool flag );
};

class LANAPI : public VSlots<18>
{
public:
	virtual void RequestGameLeave( void );
	virtual void slot19( void ) = 0; virtual void slot20( void ) = 0;
	virtual void RequestChat( UnicodeString message, LANAPIInterface::ChatType format, Int unused );
	virtual void RequestEnableMPSetupUI( Bool enable );
	virtual void slot23( void ) = 0; virtual void slot24( void ) = 0;
	virtual void slot25( void ) = 0; virtual void slot26( void ) = 0;
	virtual void slot27( void ) = 0; virtual void slot28( void ) = 0;
	virtual void slot29( void ) = 0; virtual void slot30( void ) = 0;
	virtual void slot31( void ) = 0; virtual void slot32( void ) = 0;
	virtual void slot33( void ) = 0; virtual void slot34( void ) = 0;
	virtual void slot35( void ) = 0; virtual void slot36( void ) = 0;
	virtual void OnPlayerLeave( UnicodeString player ) = 0;
	virtual void slot38( void ) = 0; virtual void slot39( void ) = 0;
	virtual void OnChat( const UnicodeString &player, const BfmeNetAddress *ip,
		const UnicodeString &message, LANAPIInterface::ChatType format ) = 0;
	virtual void slot41( void ) = 0;
	virtual void slot42( void ) = 0; virtual void slot43( void ) = 0;
	virtual void slot44( void ) = 0; virtual void slot45( void ) = 0;
	virtual void slot46( void ) = 0; virtual void slot47( void ) = 0;
	virtual void slot48( void ) = 0; virtual void slot49( void ) = 0;
	virtual void slot50( void ) = 0; virtual void slot51( void ) = 0;
	virtual void slot52( void ) = 0; virtual void slot53( void ) = 0;
	virtual void slot54( void ) = 0; virtual void slot55( void ) = 0;
	virtual void slot56( void ) = 0;
	virtual void fillInLANMessage( LANMessage *msg ) = 0;
	virtual void slot58( void ) = 0; virtual void slot59( void ) = 0;
	virtual void slot60( void ) = 0; virtual void slot61( void ) = 0;
	virtual void slot62( void ) = 0; virtual void slot63( void ) = 0;
	virtual BfmeNetAddress *getLocalAddress( void ) = 0;

	void Rva004495A2( LANMessage *msg, UnsignedInt ip );

protected:
	void removeGame( LANGameInfo *game );

	UnsignedByte m_pre14[0x14 - 4];
	UnicodeString m_name;				// +0x14
	UnsignedByte m_pre28[0x28 - 0x18];
	Int m_pendingAction;				// +0x28
	UnsignedInt m_expiration;			// +0x2C
	UnsignedInt m_actionTimeout;			// +0x30
	UnsignedByte m_pre41[0x41 - 0x34];
	Bool m_inLobby;					// +0x41
	LANGameInfo *m_currentGame;			// +0x44
	UnsignedByte m_pre50[0x50 - 0x48];
	Transport *m_transport;				// +0x50
};

void LANAPI::RequestGameLeave( void )
{
	LANMessage msg;
	msg.LANMessageType = ( m_currentGame && m_currentGame->getHostAddress()->Rva00248CBF( getLocalAddress() ) )
		? MSG_REQUEST_HOST_LEAVE : MSG_REQUEST_GAME_LEAVE;
	fillInLANMessage( &msg );
	wcsncpy( msg.GameToLeave.gameName, ( m_currentGame ) ? m_currentGame->getName().str() : L"", LAN_GAME_NAME_LENGTH );
	msg.GameToLeave.gameName[LAN_GAME_NAME_LENGTH] = 0;
	Rva004495A2( &msg, 0 );
	m_transport->Rva004D54C1( false );

	if( m_currentGame && m_currentGame->getHostAddress()->Rva00248CBF( getLocalAddress() ) )
	{
		OnPlayerLeave( m_name );
		removeGame( m_currentGame );
		::delete m_currentGame;
		m_currentGame = 0;
		m_inLobby = true;
	}
	else
	{
		m_pendingAction = ACT_LEAVE;
		m_expiration = timeGetTime() + m_actionTimeout;
	}
}

void LANAPI::RequestChat( UnicodeString message, LANAPIInterface::ChatType format, Int unused )
{
	LANMessage msg;
	fillInLANMessage( &msg );
	wcsncpy( msg.Chat.gameName, ( m_currentGame ) ? m_currentGame->getName().str() : L"", LAN_GAME_NAME_LENGTH );
	msg.Chat.gameName[LAN_GAME_NAME_LENGTH] = 0;
	msg.LANMessageType = MSG_CHAT;
	msg.Chat.chatType = format;
	wcsncpy( msg.Chat.message, message.str(), LAN_MAX_CHAT_LENGTH );
	msg.Chat.message[LAN_MAX_CHAT_LENGTH] = 0;
	Rva004495A2( &msg, 0 );

	OnChat( m_name, getLocalAddress(), message, format );
}

void LANAPI::RequestEnableMPSetupUI( Bool enable )
{
	LANMessage msg;
	msg.LANMessageType = MSG_ENABLE_MPSETUP_UI;
	fillInLANMessage( &msg );
	wcsncpy( msg.EnableMPSetupUI.gameName, ( m_currentGame ) ? m_currentGame->getName().str() : L"", LAN_GAME_NAME_LENGTH );
	msg.EnableMPSetupUI.gameName[LAN_GAME_NAME_LENGTH] = 0;
	msg.EnableMPSetupUI.enable = enable;
	Rva004495A2( &msg, 0 );
	m_transport->Rva004D54C1( false );
}
