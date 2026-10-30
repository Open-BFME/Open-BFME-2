// cl: /O2 /GS
// Retail 0x0080AB50: advance timed requests and emit the MAGE response.
// The argument is an unsigned timestamp; the member ABI is thiscall/ret4.

class BfmeC994
{
public:
	BfmeC994( char *buffer, int capacity );
	void addString( const char *key, const char *value );

	char m_pad00[ 0x1c ];
	int m_category;
	int m_status;
	char m_pad24[ 0x0c ];
	char m_pad30;
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

class BfmeThingCIC
{
public:
	void bfmeGoCIC( void *key, void *value );
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

struct Rva007EB810Diag
{
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void fail( const char *expr, const char *file, int line );
};

Rva007EB810Diag *Rva007EB810Get();
void *Rva007F93E0( void *message, void *route, void *owner );

class Gen0080AB50
{
public:
	void process( unsigned int value );
	int handle( unsigned int timestamp );

	char m_pad00[ 4 ];
	BfmeSinkSKA *m_sink;
	char m_pad08[ 8 ];
	void *m_field10;
	char m_pad14[ 4 ];
	LanGameEntryView *m_entry;
	char m_pad1c[ 0x3c ];
	HostedLanGameView *m_game;
	unsigned int m_field5c;
	unsigned int m_field60;
	int m_tid;
	char m_pad68[ 0x100 ];
	unsigned char m_status;
	char m_pad169[ 3 ];
	int m_pending;
	int m_field170;
	char m_name[ 0x20 ];
};

int Gen0080AB50::handle( unsigned int timestamp )
{
	if( m_tid != 0 )
	{
		if( m_status == 0 && m_field60 < timestamp )
		{
			m_field60 = timestamp + 0x64;
			m_status = (unsigned char)reinterpret_cast< Rva0080A940Owner * >( this )->finish();
			if( m_status == 1 )
				m_field5c = timestamp + 0x5dc;
		}

		if( m_field5c != 0 && m_field5c < timestamp )
			process( timestamp );
	}

	if( m_pending != 0 )
	{
		m_sink->sendCreateGameRequest( m_pending, m_entry->m_gameId,
			m_game->m_maxPlayers, m_game->m_userGameId );
		m_pending = 0;
	}

	if( m_field170 != 0 )
	{
		char buffer[ 0x40 ];
		BfmeC994 message( buffer, sizeof( buffer ) );

		LanGameEntryView *entry = m_entry;
		if( entry == 0 )
		{
			Rva007EB810Get()->fail(
				"lg",
				"\\views\\feslbuild_main\\jabba\\fesl\\source\\gamebrowser\\lantheateremulator.cpp",
				0x496 );
		}
		else
		{
			message.m_status = (int)0xC0000000;
			message.m_category = 0x4547414d;
			BfmeThingCIB *cib = reinterpret_cast< BfmeThingCIB * >( &message );
			cib->bfmeGoCIB( (int *)"TID", (void *)m_field170 );
			cib->bfmeGoCIB( (void *)"GID", (void *)entry->m_gameId );
			cib->bfmeGoCIB( (char *)"LID", (void *)-2 );

			reinterpret_cast< BfmeThingVJJ * >( entry )->bfmeGoVJJ(
				reinterpret_cast< BfmeMsgVJJ * >( &message ) );
			message.addString( "NAME", m_name );
			Rva007F93E0( &message, (void *)"->L", m_field10 );
		}
		m_field170 = 0;
		reinterpret_cast< Gen_007e86c0 * >( &message )->m();
	}
	return 0;
}
