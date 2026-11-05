// cl: /O2 /GX- /GS
// Retail 0x0080AB50: advance timed requests and emit the MAGE response.
// The argument is an unsigned timestamp; the member ABI is thiscall/ret4.

class Rva007E86B0Base
{
public:
	Rva007E86B0Base();
	virtual ~Rva007E86B0Base();

	int m_field04;
};

class BfmeC994 : public Rva007E86B0Base
{
public:
	virtual ~BfmeC994();
	BfmeC994( char *buffer, int capacity );
	void addInt( const char *key, int value );
	void addString( const char *key, const char *value );

	int m_field08;
	int m_field0c;
	char *m_buffer;
	int m_capacity;
	int m_field18;
	int m_category;
	int m_field20;
	int m_field24;
	int m_field28;
	int m_field2c;
	char m_field30;
};

class BfmeThingCIB
{
public:
	void bfmeGoCIB( void *key, void *value );
};

class BfmeMsgVJJ
{
public:
	void bfmeSetVJJ(const char *k, const char *v) throw();
	int m_bfme00; // +0x00
	int m_bfme04; // +0x04
	int m_bfme08; // +0x08
	int m_bfme0c; // +0x0C
	char m_pad10[0x24];
};

class BfmeThingVJJ
{
public:
	void bfmeGoVJJ(BfmeMsgVJJ *out);
	void bfmeFmtVJJ(char *buf, int n) throw();
	int m_bfme00; // +0x00
	int m_bfme04; // +0x04
	int m_bfme08; // +0x08
	int m_bfme0c; // +0x0C
};

class Gen_007e86c0
{
public:
	void m();
};

class BfmeSinkSKA
{
public:
	void bfmeSendSKA(int tag, int a, int v);
	void sendCreateGameRequest( int transactionId, int gameId, int maxPlayers, const char *userGameId );
};

struct Rva0080F100Object;
class Rva00808CB0LanGameEntry;
class Rva0080A940Owner
{
public:
	bool finish();
	void *m_field00; // +0x00
	void *m_field04; // +0x04
	void *m_field08; // +0x08
	Rva0080F100Object *m_field0c; // +0x0C
	void *m_field10; // +0x10
	int m_nextLanGameId; // +0x14
	Rva00808CB0LanGameEntry *m_lanGames[ 16 ]; // +0x18
	void *m_game; // +0x58
	unsigned int m_t0; // +0x5C +0x5C
	unsigned int m_t1; // +0x60 +0x60
	int m_tid; // +0x64 +0x64
	char m_favGameUid[ 0x100 ]; // +0x68 +0x68
	char m_pad168[0x4];
};

struct LanGameEntryView
{
	char m_pad00[ 0x10 ];
	int m_gameId;
};

struct HostedLanGameView
{
	char m_pad00[ 4 ];
	int m_maxPlayers;
	char m_pad08[ 0x84 ];
	char m_userGameId[ 0x20 ];
};

#include "../../Include/GameNetwork/Rva007EB810Diag.h"

Rva007EB810Diag *Rva007EB810Get();
void *Rva007F93E0( void *message, void *route, void *owner );

struct Rva00809520Entry;
class Rva008038F0Sender;
class Gen0080AB50
{
public:
	void process( unsigned int timestamp );
	int handle( unsigned int timestamp );

	char m_pad00[ 0x04 ];
	Rva008038F0Sender *m_sender;
	char m_pad08[ 0x08 ];
	void *m_route;
	char m_pad14[ 0x04 ];
	Rva00809520Entry *m_entries[ 16 ];
	struct HostedLanGameView *m_game;
	unsigned int m_deadline;
	unsigned int m_retryTime;
	int m_tid;
	char m_pad68[ 0x100 ];
	char m_status;
	char m_pad169[ 3 ];
	int m_pendingTid;
	int m_joinTid;
	char m_name[ 0x20 ];
};

int Gen0080AB50::handle( unsigned int timestamp )
{
	if( m_tid != 0 )
	{
		if( m_status == 0 && m_retryTime < timestamp )
		{
			m_retryTime = timestamp + 0x64;
			m_status = (unsigned char)reinterpret_cast< Rva0080A940Owner * >( this )->finish();
			if( m_status == 1 )
				m_deadline = timestamp + 0x5dc;
		}

		if( m_deadline != 0 && m_deadline < timestamp )
			process( timestamp );
	}

	if( m_pendingTid != 0 )
	{
		reinterpret_cast< BfmeSinkSKA * >( m_sender )->sendCreateGameRequest(
			m_pendingTid,
			reinterpret_cast< LanGameEntryView * >( m_entries[ 0 ] )->m_gameId,
			m_game->m_maxPlayers, m_game->m_userGameId );
		m_pendingTid = 0;
	}

	if( m_joinTid != 0 )
	{
		char buffer[ 0x40 ];
		BfmeC994 message( buffer, sizeof( buffer ) );

		LanGameEntryView *entry =
			reinterpret_cast< LanGameEntryView * >( m_entries[ 0 ] );
		if( entry == 0 )
		{
			Rva007EB810Get()->fail(
				"lg",
				"\\views\\feslbuild_main\\jabba\\fesl\\source\\gamebrowser\\lantheateremulator.cpp",
				0x496 );
		}
		else
		{
			message.m_field20 = (int)0xC0000000;
			message.m_category = 0x4547414d;
			BfmeThingCIB *cib = reinterpret_cast< BfmeThingCIB * >( &message );
			cib->bfmeGoCIB( (int *)"TID", (void *)m_joinTid );
			cib->bfmeGoCIB( (void *)"GID", (void *)entry->m_gameId );
			cib->bfmeGoCIB( (char *)"LID", (void *)-2 );

			reinterpret_cast< BfmeThingVJJ * >( entry )->bfmeGoVJJ(
				reinterpret_cast< BfmeMsgVJJ * >( &message ) );
			message.addString( "NAME", m_name );
			Rva007F93E0( &message, (void *)"->L", m_route );
		}
		m_joinTid = 0;
	}
	return 0;
}
