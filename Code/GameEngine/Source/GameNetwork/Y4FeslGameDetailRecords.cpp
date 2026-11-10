// cl: /GS
#include <string.h>

// EA FESL client SDK ("jabba") -- the two wide Aries record constructors.
//
// Same SDK cluster as V2FeslAriesRecords.cpp, and the same __thiscall
// constructor shape: one message argument, `this` returned in eax, `ret 4`,
// every member filled by key out of the message.
//
// Every buffer length and every member offset below is an immediate with no
// relocation and is therefore hard evidence; the C++ member NAMES are derived
// from the wire keys, which are themselves real (they are pushed literals).
// The short keys of the game record -- MP PW AP JP QP HN HU NF PL I P -- are
// the EA game-browser per-game attribute set.
//
// Both records finish with the same platform test: the "PL" field is compared
// against a five-byte literal ("XBOX" / "xbox" -- the two rows use DIFFERENT
// literals, which is what distinguishes them) and, only on a match, a 0x20
// field is filled by strncpy.  MSVC expands that comparison inline as
// `repe cmpsb`, so the length 5 is visible in the bytes.
//
// This lane may not add a .h file, so the message class is re-declared here.

typedef __int64 FeslInt64;

#include "../../Include/GameNetwork/BfmeThingRF.h"

class BfmeThingVMQ
{
public:
	bool bfmeGoVMQ( const char *key, char defaultValue );
};

#include "../../Include/GameNetwork/BfmeThingUPB.h"

class Rva007E8810Message
{
public:
	FeslInt64 getInt64( const char *key, FeslInt64 defaultValue );   // 0x007E8930
};

#define FESL_GET_INT(message, key, defaultValue) \
	(int)((BfmeThingRF *)(message))->bfmeGoRF((void *)(key), (void *)(defaultValue))
#define FESL_GET_BOOL(message, key, defaultValue) \
	((BfmeThingVMQ *)(message))->bfmeGoVMQ((key), (char)(defaultValue))
#define FESL_GET_STRING(message, key, dest, destSize) \
	((BfmeThingUPB *)(message))->bfmeGoUPB((void *)(key), (dest), (void *)(destSize))

// ----------------------------------------------------------- the game record
class Rva007FBC60Game
{
public:
	Rva007FBC60Game( Rva007E8810Message *msg );

	int m_lid;                      // +0x000
	int m_gid;                      // +0x004
	Rva007E8810Message *m_msg;      // +0x008
	int m_ap;                       // +0x00C
	int m_jp;                       // +0x010
	int m_qp;                       // +0x014
	int m_mp;                       // +0x018
	int m_p;                        // +0x01C
	int m_nf;                       // +0x020
	bool m_f;                       // +0x024
	bool m_pw;                      // +0x025
	char m_n[ 0x80 ];               // +0x026
	char m_hn[ 0x80 ];              // +0x0A6
	FeslInt64 m_hu;                 // +0x128
	char m_v[ 0x40 ];               // +0x130
	char m_i[ 0x20 ];               // +0x170
	char m_platform[ 0x20 ];        // +0x190
	int m_join;                     // +0x1B0
};

Rva007FBC60Game::Rva007FBC60Game( Rva007E8810Message *msg )
{
	char joinText[ 10 ];

	m_lid = FESL_GET_INT(msg, "LID", 0);
	m_gid = FESL_GET_INT(msg, "GID", 0);
	m_msg = msg;
	FESL_GET_STRING(msg, "N", m_n, 0x80);
	m_mp = FESL_GET_INT(m_msg, "MP", 0);
	FESL_GET_STRING(m_msg, "I", m_i, 0x20);
	m_p = FESL_GET_INT(m_msg, "P", 0);
	m_pw = FESL_GET_BOOL(m_msg, "PW", false);
	m_ap = FESL_GET_INT(m_msg, "AP", 0);
	m_jp = FESL_GET_INT(m_msg, "JP", 0);
	m_qp = FESL_GET_INT(m_msg, "QP", 0);
	FESL_GET_STRING(m_msg, "HN", m_hn, 0x80);
	m_hu = m_msg->getInt64( "HU", 0 );
	FESL_GET_STRING(m_msg, "V", m_v, 0x40);
	m_f = FESL_GET_BOOL(m_msg, "F", false);
	m_nf = FESL_GET_INT(m_msg, "NF", 0);
	FESL_GET_STRING(msg, "PL", m_platform, 0x20);
	if( strcmp( m_platform, "XBOX" ) == 0 )
		strncpy( m_platform, m_i, 0x20 );
	else
		m_platform[ 0 ] = 0;
	FESL_GET_STRING(msg, "J", joinText, 10);
	switch( joinText[ 0 ] )
	{
		case 'O':
			m_join = 0;
			break;
		case 'W':
			m_join = 1;
			break;
		case 'C':
			m_join = 2;
			break;
		default:
			m_join = 0;
			break;
	}
}

// ---------------------------------------------------------- the ticket record
class Rva007FC020Ticket
{
public:
	Rva007FC020Ticket( Rva007E8810Message *msg );

	int m_lid;                      // +0x000
	int m_gid;                      // +0x004
	int m_pid;                      // +0x008
	int m_p;                        // +0x00C
	char m_ticket[ 0x80 ];          // +0x010
	char m_reason[ 0x100 ];         // +0x090
	char m_i[ 0x20 ];               // +0x190
	char m_host[ 0x20 ];            // +0x1B0
	char m_platform[ 0x10 ];        // +0x1D0
	char m_ugid[ 0x25 ];            // +0x1E0
};

Rva007FC020Ticket::Rva007FC020Ticket( Rva007E8810Message *msg )
{
	m_lid = FESL_GET_INT(msg, "LID", 0);
	m_gid = FESL_GET_INT(msg, "GID", 0);
	m_pid = FESL_GET_INT(msg, "PID", 0);
	FESL_GET_STRING(msg, "TICKET", m_ticket, 0x80);
	FESL_GET_STRING(msg, "REASON", m_reason, 0x100);
	FESL_GET_STRING(msg, "I", m_i, 0x20);
	FESL_GET_STRING(msg, "PL", m_platform, 0x10);
	_strlwr( m_platform );
	FESL_GET_STRING(msg, "UGID", m_ugid, 0x25);
	m_p = FESL_GET_INT(msg, "P", 0);
	m_host[ 0 ] = 0;
	if( strcmp( m_platform, "xbox" ) == 0 )
		strncpy( m_host, m_i, 0x20 );
}
