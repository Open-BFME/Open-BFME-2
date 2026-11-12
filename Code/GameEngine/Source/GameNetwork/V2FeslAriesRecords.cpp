// EA FESL client SDK ("jabba") -- Aries record constructors.
//
// Same translation-unit cluster as V2FeslTxnRequests.cpp; see that file's head
// comment for how the span was identified (the assert path
// \views\feslbuild_main\jabba\fesl\source\ariesudp.cpp) and for the message
// object at RVA 0x007E8810 whose accessors every row here calls.
//
// WHAT THE BYTES SHOW.  Every row is __thiscall, takes ONE pointer argument,
// returns `this` in eax and ends `ret 4` -- the MSVC shape of a constructor.
// Each fills its object entirely out of the message by key:
//     getInt   ( key, defaultValue )        RVA 0x007E8900, returns int
//     getString( key, dest, destSize )      RVA 0x007E8A80, returns bool
//     getInt64 ( key, defaultValue )        RVA 0x007E8930, returns __int64
// The BUFFER SIZES are immediates with no relocation, so every char array
// length below (0x80, 0x40, 0x400, 0x25, 0x100, 0x20, 8) is hard evidence, as
// is every member OFFSET -- each is either an `lea this+N` handed to getString
// or a `mov [this+N],eax` taking a getInt result.  The key spellings are the
// pushed literals and are real; the C++ member names are not.
//
// Three rows (0x007F5010, 0x007F5080, 0x007F5120) open with a __thiscall call
// to RVA 0x007FBC30 passing the same message pointer, before touching anything
// at or above offset 8.  RVA 0x007FBC30 is itself a two-field constructor of
// this same shape (LID at +0, GID at +4), so that call is a BASE constructor
// and those three objects start with its eight bytes.  It lives outside this
// file's span and is only declared and pinned here, never defined.
//
// WHAT THE BYTES CANNOT DECIDE.  Nothing names any of these record types or
// the fields whose keys are numeric ("QPOS", "QLEN").  All class and member
// names are address- or key-derived.  0x007F41B0 and 0x007F4E20 are the same
// two-field body under two different keys; the bytes do not say they are
// related types.

typedef __int64 FeslInt64;

// g_Rva0130A708: the matched result-cursor references place this const
// pointer at VA 0x00E0A124, in .data's zero-filled tail; retail starts null.
extern const char * const g_Rva0130A708 = 0;

// FESL request-string slots: matched DIR32 references establish these target
// VAs; each is a null 32-bit pointer in .data's zero-filled tail.
// g_Rva0130A678: VA 0x00E0A094.
extern const char * const g_Rva0130A678 = 0;
// g_Rva0130A684: VA 0x00E0A0A0.
extern const char * const g_Rva0130A684 = 0;
// g_Rva0130A6D8: VA 0x00E0A0F4.
extern const char * const g_Rva0130A6D8 = 0;
// g_Rva0130A720: VA 0x00E0A13C.
extern const char * const g_Rva0130A720 = 0;
// g_Rva0130A72C: VA 0x00E0A148.
extern const char * const g_Rva0130A72C = 0;
// g_Rva0130A738: VA 0x00E0A154.
extern const char * const g_Rva0130A738 = 0;
// g_Rva0130A744: VA 0x00E0A160.
extern const char * const g_Rva0130A744 = 0;
// g_Rva0130A750: VA 0x00E0A16C.
extern const char * const g_Rva0130A750 = 0;
// g_Rva0130A75C: VA 0x00E0A178.
extern const char * const g_Rva0130A75C = 0;
// g_Rva0130A774: VA 0x00E0A190.
extern const char * const g_Rva0130A774 = 0;
// g_Rva0130A78C: VA 0x00E0A1A8.
extern const char * const g_Rva0130A78C = 0;

#include "../../Include/GameNetwork/Rva007E8810Message.h"

// ------------------------------------------------------------ endpoint pair
class Rva007F4130Endpoints
{
public:
	Rva007F4130Endpoints( Rva007E8810Message *msg );
	Rva007E8810Message *m_msg;
	char m_theaterIp[ 0x40 ];
	char m_messengerIp[ 0x40 ];
	char m_addressRemapping[ 0x400 ];
	int m_theaterPort;
	int m_messengerPort;
};

Rva007F4130Endpoints::Rva007F4130Endpoints( Rva007E8810Message *msg )
{
	m_msg = msg;
	m_theaterPort = m_msg->getInt( "theaterPort", 0 );
	m_messengerPort = m_msg->getInt( "messengerPort", 0 );
	m_msg->getString( "theaterIp", m_theaterIp, 0x40 );
	m_msg->getString( "messengerIp", m_messengerIp, 0x40 );
	m_msg->getString( "addressRemapping", m_addressRemapping, 0x400 );
}

// -------------------------------------------------------------------- lobby

// Rva007F4EF0Lobby::Rva007F4EF0Lobby: defined in V2FeslAriesLobby.cpp (its row's unit).

class Rva007F4F90LobbyCounts
{
public:
	Rva007F4F90LobbyCounts( Rva007E8810Message *msg );
	int m_numGames;
	int m_lid;
	int m_lobbyMaxGames;
	int m_lobbyNumGames;
};

Rva007F4F90LobbyCounts::Rva007F4F90LobbyCounts( Rva007E8810Message *msg )
{
	m_numGames = msg->getInt( "NUM-GAMES", 0 );
	m_lid = msg->getInt( "LID", 0 );
	m_lobbyMaxGames = msg->getInt( "LOBBY-MAX-GAMES", 0 );
	m_lobbyNumGames = msg->getInt( "LOBBY-NUM-GAMES", 0 );
}

// ------------------------------------------------------------- ticket record
class Rva007F51D0Ticket
{
public:
	Rva007F51D0Ticket( Rva007E8810Message *msg );
	int m_pid;
	FeslInt64 m_uid;
	int m_port;
	char m_name[ 0x80 ];
	char m_ip[ 0x20 ];
	char m_ticket[ 0x80 ];
};

Rva007F51D0Ticket::Rva007F51D0Ticket( Rva007E8810Message *msg )
{
	msg->getString( "NAME", m_name, 0x80 );
	m_uid = msg->getInt64( "UID", 0 );
	msg->getString( "IP", m_ip, 0x20 );
	m_pid = msg->getInt( "PID", 0 );
	msg->getString( "TICKET", m_ticket, 0x80 );
	m_port = msg->getInt( "PORT", 0 );
}

// ------------------------------------- LID/GID base and the three rows on it
class Rva007FBC30GameKey
{
public:
	Rva007FBC30GameKey( Rva007E8810Message *msg );                    // 0x007FBC30
	int m_lid;
	int m_gid;
};

class Rva007F5010Player : public Rva007FBC30GameKey
{
public:
	Rva007F5010Player( Rva007E8810Message *msg );
	Rva007E8810Message *m_msg;
	int m_pid;
	char m_name[ 0x80 ];
	FeslInt64 m_uid;
};

Rva007F5010Player::Rva007F5010Player( Rva007E8810Message *msg )
	: Rva007FBC30GameKey( msg )
{
	m_msg = msg;
	m_pid = m_msg->getInt( "PID", 0 );
	m_msg->getString( "NAME", m_name, 0x80 );
	m_uid = m_msg->getInt64( "UID", 0 );
}

class Rva007F5080Game : public Rva007FBC30GameKey
{
public:
	Rva007F5080Game( Rva007E8810Message *msg );
	int m_maxPlayers;
	char m_ugid[ 0x25 ];
	char m_secret[ 0x80 ];
	int m_lobbyId;
	int m_gameId;
};

Rva007F5080Game::Rva007F5080Game( Rva007E8810Message *msg )
	: Rva007FBC30GameKey( msg )
{
	m_maxPlayers = msg->getInt( "MAX-PLAYERS", 0 );
	m_lobbyId = msg->getInt( "LID", 0 );
	m_gameId = msg->getInt( "GID", 0 );
	msg->getString( "SECRET", m_secret, 0x80 );
	msg->getString( "UGID", m_ugid, 0x25 );
}

class Rva007F5120Queue : public Rva007FBC30GameKey
{
public:
	Rva007F5120Queue( Rva007E8810Message *msg );
	char m_reason[ 0x100 ];
	int m_qpos;
	int m_qlen;
};

Rva007F5120Queue::Rva007F5120Queue( Rva007E8810Message *msg )
	: Rva007FBC30GameKey( msg )
{
	if( !msg->getString( "REASON", m_reason, 0x100 ) )
		m_reason[ 0 ] = 0;
	m_qpos = msg->getInt( "QPOS", 0 );
	m_qlen = msg->getInt( "QLEN", 0 );
}

// ---------------------------------------------------------------- two-field
class Rva007F41B0Reason
{
public:
	Rva007F41B0Reason( Rva007E8810Message *msg );
	Rva007E8810Message *m_msg;
	int m_reason;
};

Rva007F41B0Reason::Rva007F41B0Reason( Rva007E8810Message *msg )
{
	m_msg = msg;
	m_reason = m_msg->getInt( "reason", 0 );
}

