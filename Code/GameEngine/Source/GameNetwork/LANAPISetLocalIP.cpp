// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /O1 /Oy-
//
// Retail 0x0044A9E6, 158 bytes: LANAPI::SetLocalIP(UnsignedInt), slot 53 of
// the LANAPI vtable 0x0083E680; slot 52 is the rowed string overload
// 0x0044AA84, which resolves its AsciiString and calls this slot.
// Ported from Zero Hour's LANAPI::SetLocalIP (LANAPI.cpp) with BFME 1's port
// scan (LANAPILocalAddress.cpp at 6583b3c1, also used by the rowed
// LANAPI::init 0x00449BAA): store the address, reset the transport and bind
// the first free port of 8086..8093 offset by the _EA_RTS_HEADLESS instance.
// BFME 2 adds a loopback-aware broadcast address: on 127.0.0.1 broadcasts
// are disabled and the local address is used instead of 0xFFFFFFFF. The
// literals and msvcr71 getenv/atoi imports are read from the target.
// Members follow LANAPIInit.cpp: local address +0x48, transport +0x50,
// broadcast address +0x54. Callees: Transport reset (rowed 0x004D5496), the
// address-struct Transport::init (pinned 0x004D5219), allowBroadcasts (rowed
// 0x004D5112) and ResolveIP (rowed 0x00581339).

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;

extern "C" __declspec(dllimport) char * __cdecl getenv( const char *name );
extern "C" __declspec(dllimport) Int __cdecl atoi( const char *text );

#include "ascii_string.h"

enum
{
	LAN_BASE_PORT = 8086,
	LAN_LAST_PORT = 8094
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

UnsignedInt ResolveIP( AsciiString host );

class LANAPI
{
public:
	virtual Bool SetLocalIP( UnsignedInt localIP );

protected:
	unsigned char m_pre48[0x48 - 4];
	TransportAddress m_localAddress;		// +0x48
	Transport *m_transport;				// +0x50
	UnsignedInt m_broadcastAddr;			// +0x54
};

Bool LANAPI::SetLocalIP( UnsignedInt localIP )
{
	m_localAddress.m_ip = localIP;
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

	if( m_localAddress.m_ip == ResolveIP( AsciiString( "127.0.0.1" ) ) )
	{
		m_transport->allowBroadcasts( false );
		m_broadcastAddr = m_localAddress.m_ip;
	}
	else
	{
		m_transport->allowBroadcasts( true );
		m_broadcastAddr = 0xFFFFFFFF;
	}
	return (UnsignedShort)port < LAN_LAST_PORT;
}
