// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs-c- /O1
//
// Retail 0x00449BAA, 256 bytes: LANAPI::init, slot 1 of the LANAPI vtable
// 0x0083E680 (slot 0 is the rowed ??_GLANAPI, slot 9 the rowed reset).
// Ported from BFME 1's LANAPI::init (LANAPILocalAddress.cpp, retail
// 0x00685690, 325 bytes): clear the start timer, reset the transport, bind
// the first free port of 8086..8093 offset by the _EA_RTS_HEADLESS instance,
// allow broadcasts, enter the lobby with no pending action or current game,
// and record the user and computer names ("unknown" when unavailable).
// BFME 2 keeps the BFME 1 member order four bytes further on: start time
// +0x20, seconds +0x24, pending action +0x28, expiration +0x2C, direct-connect
// address +0x34, LAN menu +0x40, lobby +0x41, current game +0x44, local
// address +0x48, transport +0x50; the names are AsciiStrings at +0x18/+0x1C.
// Callees: Transport reset (rowed 0x004D5496), the address-struct
// Transport::init (pinned 0x004D5219) and allowBroadcasts (rowed).

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;

extern "C" __declspec(dllimport) char * __cdecl getenv( const char *name );
extern "C" __declspec(dllimport) Int __cdecl atoi( const char *text );
extern "C" char * __cdecl strcpy( char *dest, const char *source );
#pragma function(strcpy)
extern "C" __declspec(dllimport) Int __stdcall GetUserNameA( char *buffer, UnsignedInt *size );
extern "C" __declspec(dllimport) Int __stdcall GetComputerNameA( char *buffer, UnsignedInt *size );

#include "ascii_string.h"

enum
{
	LAN_BASE_PORT = 8086,
	LAN_LAST_PORT = 8094,
	USER_NAME_BUFFER = 257,
	COMPUTER_NAME_BUFFER = 16
};

struct BfmeNetAddress
{
	UnsignedInt m_ip;
	UnsignedShort m_port;
};

struct TransportAddress
{
	UnsignedInt m_ip;
	UnsignedShort m_port;
};

class Transport
{
public:
	void Rva004D5496( void );
	Bool init( const TransportAddress *address );
	Bool allowBroadcasts( Bool value );
};

class LANGameInfo;

class LANAPI
{
public:
	virtual void slot00( void ) = 0;
	virtual void init( void );

protected:
	unsigned char m_pre18[0x18 - 4];
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
	TransportAddress m_localAddress;		// +0x48
	Transport *m_transport;				// +0x50
};

void LANAPI::init( void )
{
	m_gameStartTime = 0;
	m_gameStartSeconds = 0;
	m_transport->Rva004D5496();

	const char *headlessInstance = getenv( "_EA_RTS_HEADLESS" );
	Int port = LAN_BASE_PORT + atoi( headlessInstance ? headlessInstance : "0" );
	while( (UnsignedShort)port < LAN_LAST_PORT )
	{
		m_localAddress.m_port = (UnsignedShort)port;
		if( m_transport->init( &m_localAddress ) )
			break;
		++port;
	}

	m_transport->allowBroadcasts( true );

	m_pendingAction = 0;
	m_expiration = 0;
	m_inLobby = true;
	m_isInLANMenu = true;
	m_currentGame = 0;
	BfmeNetAddress noAddress = { 0, 0 };
	m_directConnectRemoteAddress = noAddress;

	UnsignedInt bufferSize = USER_NAME_BUFFER;
	char userName[USER_NAME_BUFFER];
	if( !GetUserNameA( userName, &bufferSize ) )
		strcpy( userName, "unknown" );
	m_userName = userName;

	bufferSize = COMPUTER_NAME_BUFFER;
	char computerName[COMPUTER_NAME_BUFFER];
	if( !GetComputerNameA( computerName, &bufferSize ) )
		strcpy( computerName, "unknown" );
	m_hostName = computerName;
}
