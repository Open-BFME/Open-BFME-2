// cl: /O2 /Oi /Ob0 /GS
// EA FESL client SDK ("jabba") -- pending-request removal and the reply pump
// from gamebrowserpinger.cpp.  The assertion text and source path are retained
// in the retail image; the class and member names below remain
// address-derived.

#include <string.h>
#pragma intrinsic( memcpy )

struct Rva007EB810Diag
{
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void fail( const char *expr, const char *file, int line );
};

extern Rva007EB810Diag *Rva007EB810Get();

struct Rva00803080;

struct Rva007EAServiceList
{
	void add( Rva00803080 *owner );
	void remove( Rva00803080 *owner );
};

// What a ping reply is written back into: the hub looks the game up by the
// request's first key (slot 21), the game looks the entry up by the second
// (slot 14), and the entry keeps the round trip at +0x4C.
struct Rva007EAPingEntry
{
	char m_pad[ 0x4C ];
	int m_ping;                     // +0x4C
};

struct Rva007EAPingGame
{
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual Rva007EAPingEntry *find( int key );
};

// Told about every entry whose ping changed, by both keys (slot 8).
struct Rva007EAPingListener
{
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void pinged( int key0, int key1 );
};

struct Rva007EAServiceHub
{
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual Rva007EAPingGame *find( int key );

	char m_pad04[ 0x08 ];
	Rva007EAServiceList *m_services;    // +0x0C
	char m_pad10[ 0x0C ];
	Rva007EAPingListener *m_listener;   // +0x1C
};

struct Rva00803080Request
{
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
};

// DirtySock's ping reply fetch (0x00808660); see Y2Rva00807900Module.cpp.
struct Rva00807BA0Ping;

struct Rva00808660Result
{
	char         m_text[ 0x14 ];   // +0x00
	unsigned int m_from;           // +0x14
	int          m_elapsed;        // +0x18
	int          m_sequence;       // +0x1C
	int          m_icmpType;       // +0x20
	int          m_server;         // +0x24
	int          m_pad28;          // +0x28
};

int Rva00808660( Rva00807BA0Ping *ping, void *data, int *dataLen,
	Rva00808660Result *result );

class Rva00803080
{
	Rva007EAServiceHub *m_04;
	Rva00807BA0Ping *m_08;
	Rva00803080Request *m_0C;
	int m_10;

public:
	virtual void update( unsigned int now );
	virtual ~Rva00803080();

	void removePendingRequest( int index );
};

void Rva00803080::removePendingRequest( int index )
{
	if( index < 0 || index >= m_10 )
	{
		Rva007EB810Get()->fail(
			"index >= 0 && index < mNumPendingRequests",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\gamebrowser\\gamebrowserpinger.cpp",
			0x11F );
	}

	if( index < m_10 - 1 )
	{
		memcpy( &m_0C[ index ], &m_0C[ index + 1 ],
			( m_10 - index - 1 ) * sizeof( Rva00803080Request ) );
	}

	memset( &m_0C[ m_10 - 1 ], 0, sizeof( Rva00803080Request ) );
	int new_count = m_10 - 1;
	if( new_count > 0 )
	{
		if( m_10 == 0 )
		{
			m_04->m_services->add( this );
			m_10 = new_count;
			return;
		}
	}
	if( new_count != 0 || m_10 <= 0 )
		goto store_count;
	m_04->m_services->remove( this );

store_count:
	m_10 = new_count;
	return;
}

// Slot 0 of the pinger's vtable (0x008E3ED4, beside the deleting destructor),
// so the service list runs it while requests are pending.  It drains every
// reply DirtySock holds: a reply whose sequence matches a pending request
// retires that request and, if its payload is the 8 bytes the add path sent,
// hands the round trip to the entry those two keys name.  Then any request
// older than five seconds is retired as a timeout and its entry marked -3.
void Rva00803080::update( unsigned int now )
{
	int payload[ 2 ];
	int length;
	Rva00808660Result result;
	int i;

	payload[ 0 ] = 0;
	payload[ 1 ] = 0;
	length = sizeof( payload );
	memset( &result, 0, sizeof( result ) );
	result.m_sequence = 0x7FFFFFFF;
	Rva00808660( m_08, payload, &length, &result );

	while( result.m_sequence != 0x7FFFFFFF )
	{
		// Retail reloads mNumPendingRequests from the object on every
		// iteration of this search; the volatile read keeps /O2 from caching
		// it in a register across the loop.
		bool found = false;
		for( i = 0; i < *(volatile int *)&m_10; ++i )
		{
			if( m_0C[ i ].m_00 == result.m_sequence )
			{
				found = true;
				break;
			}
		}

		if( found )
		{
			removePendingRequest( i );
			if( length != sizeof( payload ) )
			{
				Rva007EB810Get()->fail( "FALSE",
					"\\views\\feslbuild_main\\jabba\\fesl\\source\\gamebrowser\\gamebrowserpinger.cpp",
					0xD6 );
				continue;
			}

			Rva007EAPingGame *game = m_04->find( payload[ 0 ] );
			if( game != 0 )
			{
				Rva007EAPingEntry *entry = game->find( payload[ 1 ] );
				if( entry != 0 )
				{
					entry->m_ping = result.m_elapsed;
					Rva007EAPingListener *listener = m_04->m_listener;
					if( listener != 0 )
						listener->pinged( payload[ 0 ], payload[ 1 ] );
				}
			}
		}

		memset( &result, 0, sizeof( result ) );
		result.m_sequence = 0x7FFFFFFF;
		Rva00808660( m_08, payload, &length, &result );
	}

	unsigned int expire = now - 5000;
	for( i = 0; i < m_10; ++i )
	{
		if( m_0C[ i ].m_04 >= expire )
			break;

		Rva007EAPingGame *game = m_04->find( m_0C[ i ].m_08 );
		if( game != 0 )
		{
			Rva007EAPingEntry *entry = game->find( m_0C[ i ].m_0C );
			if( entry != 0 )
			{
				entry->m_ping = -3;
				Rva007EAPingListener *listener = m_04->m_listener;
				if( listener != 0 )
					listener->pinged( m_0C[ i ].m_08, m_0C[ i ].m_0C );
			}
		}
		removePendingRequest( i );
	}
}
