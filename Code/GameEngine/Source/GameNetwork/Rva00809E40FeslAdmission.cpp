// Retail 0x00809E40: FESL game-browser admission and request.
// cl: /O2 /GX- /GS

#include <new>

// Absolute .rdata operands. The donor spells BFME 1 addresses here; the map below
// is read from the retail bytes at each site (site -> BFME 2 address -> content):
//   bfmeRdata00BBFD88 -> 0x00BBFD88  "c"
//   bfmeRdata00C0C048 -> 0x00C0C048  "NAME"
//   bfmeRdata00C6AC00 -> 0x00C6AC00  "ticket"
//   bfmeRdata00C71658 -> 0x00C71658  "IP"
//   bfmeRdata00CE2D70 -> 0x00CE2D70  "PID"
//   bfmeRdata00CE2D84 -> 0x00CE2D84  "GID"
//   bfmeRdata00CE2DA4 -> 0x00CE2DA4  "REASON"
//   bfmeRdata00CE2DAC -> 0x00CE2DAC  "TICKET"
//   bfmeRdata00CE3F98 -> 0x00CE3F98  "->L"
//   bfmeRdata00CE3FB0 -> 0x00CE3FB0  "debug path"
//   bfmeRdata00CE4050 -> 0x00CE4050  "!players[pindex]"
//   bfmeRdata00CE4064 -> 0x00CE4064  "mHostedLanGame"
//   bfmeRdata00CE4074 -> 0x00CE4074  "lan game closed\n"
//   bfmeRdata00CE4088 -> 0x00CE4088  "f"
//   bfmeRdata00CE408C -> 0x00CE408C  "lan game full\n"
// Declared, never defined: the DIR32 slot is a relocation the comparison masks,
// which is how an absolute-address operand is reproduced (AGENTS.md).

// The copy is msvcr71's strncpy (import thunk 0x0062983E), from <string.h>
// with _CRTIMP empty (the header's own guard) so the call is direct.
#define _CRTIMP
#include <string.h>

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
	char m_pad10[ 0x0c ];
	int m_category;
	int m_field20;
	char m_pad24[ 0x0c ];
	char m_tail30;
};

class Rva007E8810Message
{
public:
	int getInt( const char *key, int defaultValue );
	bool getString( const char *key, char *out, int capacity );

	int m_field00;
	int m_field04;
	int m_field08;
	int m_field0c;
	char m_pad10[ 0x0c ];
	int m_category;
};

class Rva00802040Owner;

class Rva00802680Owner
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0c();
	virtual int getIndex();
	virtual void v14();
	virtual void v18();
	virtual void v1c();
	virtual void v20();
};

class Rva00802040Owner
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0c();
	virtual void v10();
	virtual void v14();
	virtual int rva00801460();
	Rva00802680Owner *findFree();
};

class Rva008038F0Sender
{
public:
	void send( BfmeC994 *message );
};

class Rva00809E40Record;

class Rva00808920LanGame
{
public:
	int m_state;
	int m_maxPlayers;
	Rva00809E40Record **m_players;
};

class SnapshotDupReplica
{
public:
	SnapshotDupReplica();
	virtual void crc();
	virtual void xfer();
	virtual void loadPostProcess();
};

class Energy : public SnapshotDupReplica
{
public:
	Energy();

	void *m_owner;
	int m_energyProduction;
	int m_energyConsumption;
	int m_powerSabotagedTillFrame;
};

class Rva00809E40Record : public Energy
{
public:
	int m_gameID;
	char m_ipAddress[ 0x20 ];
};

struct Rva00809E40State
{
	char m_pad00[ 0x2d8 ];
	Rva00802040Owner *m_manager;
};

class Rva00809E40Owner
{
public:
	void rva00809E40( Rva007E8810Message *input );

	char m_pad00[ 4 ];
	Rva008038F0Sender *m_sender;
	Rva00809E40State *m_state;
	char m_pad0c[ 4 ];
	void *m_routeOwner;
	char m_pad14[ 0x44 ];
	Rva00808920LanGame *m_game;
};

struct Rva007EB810Diag
{
	virtual void v00();
	virtual void report( const char *text );
	virtual void v08();
	virtual void fail( const char *expression, const char *file, int line );
};

Rva007EB810Diag *Rva007EB810Get();
void *Rva007F93E0( void *message, void *route, void *owner );

class Gen007F0130
{
public:
	static void *operator new( unsigned int size );
};

void Rva00809E40Owner::rva00809E40( Rva007E8810Message *input )
{
	char buffer[ 0x40 ];
	BfmeC994 message( buffer, 0x40 );
	message.m_category = input->m_category;
	void *value = (void *)( long )input->getInt(
		"TID", -1 );
	if( value != (void *)-1 )
		message.addInt( "TID", (int)( long )value );

	message.m_field04 = input->m_field04;
	message.m_field08 = input->m_field08;
	message.m_field0c = input->m_field0c;

	Rva00802040Owner *manager = m_state->m_manager;
	if( manager == 0 )
	{
		message.m_field20 = 'ngam';
		Rva007F93E0( &message, (void *)"->L", m_routeOwner );
		return;
	}

	Rva00802680Owner *slot = manager->findFree();
	if( slot == 0 )
	{
		Rva007EB810Get()->report( (const char *)"lan game full\n" );
		message.m_field20 = 'jden';
		message.addString(
			(const char *)"REASON", (const char *)"f" );
		Rva007F93E0( &message, (void *)"->L", m_routeOwner );
		return;
	}
	if( manager->rva00801460() != 0 )
	{
		Rva007EB810Get()->report( (const char *)"lan game closed\n" );
		message.m_field20 = 'jden';
		message.addString(
			(const char *)"REASON", (const char *)"c" );
		Rva007F93E0( &message, (void *)"->L", m_routeOwner );
		return;
	}

	int index = slot->getIndex();
	if( m_game == 0 )
		Rva007EB810Get()->fail(
			(const char *)"mHostedLanGame",
			(const char *)"\\views\\feslbuild_main\\jabba\\fesl\\source\\gamebrowser\\lantheateremulator.cpp",
			0x307 );
	Rva00809E40Record **players = m_game->m_players;
	if( players[ index ] != 0 )
		Rva007EB810Get()->fail(
			(const char *)"!players[pindex]",
			(const char *)"\\views\\feslbuild_main\\jabba\\fesl\\source\\gamebrowser\\lantheateremulator.cpp",
			0x309 );

	void *raw = Gen007F0130::operator new( 0x38 );
	Rva00809E40Record *record = raw != 0
		? reinterpret_cast< Rva00809E40Record * >( new( raw ) Energy )
		: (Rva00809E40Record *)0;
	players[ index ] = record;
	record->m_owner = (void *)( long )input->m_field04;
	record->m_energyProduction = input->m_field08;
	record->m_energyConsumption = input->m_field0c;
	int state = m_game->m_state;
	++m_game->m_state;
	record->m_powerSabotagedTillFrame = state;
	record->m_gameID = reinterpret_cast< Rva007E8810Message * >( input )->getInt(
		(const char *)"GID", 0 );
	Rva007F93E0( &message, (void *)"->L", m_routeOwner );

	{
		char first[ 0x20 ];
		input->getString( (const char *)"NAME", first, 0x20 );
		{
			char second[ 0x20 ];
			input->getString( (const char *)"IP", second, 0x20 );
			strncpy( record->m_ipAddress, second, 0x20 );
		}

		BfmeC994 request( buffer, 0x40 );
		request.m_category = 'EGRQ';
		request.addString( (const char *)"NAME", first );
		request.addInt( (const char *)"PID", record->m_powerSabotagedTillFrame );
		request.addString( (const char *)"TICKET", (const char *)"ticket" );
		m_sender->send( &request );
	}
}

// BFME2 0x00674BB0 (25 B), from Open-BFME-1 5cae4bdff (BFME1 0x00808C60): forward
// one message on the admission route. Reads the route owner at +0x10 and sends
// the caller's message through Rva007F93E0 with the route operand this TU maps to
// bfmeRdata00CE3F98 (retail pushes 0x00CE3F98 here too). Identity of the owning
// forwarder is not recovered, so the name is address-derived as in the donor.
class Rva00808C60Owner
{
public:
	void forwardToLRoute( void *message );
	char m_pad00[ 0x10 ];
	void *m_routeOwner;
};

// ?forwardToLRoute@Rva00808C60Owner@@QAEXPAX@Z
void Rva00808C60Owner::forwardToLRoute( void *message )
{
	Rva007F93E0( message, (void *)"->L", m_routeOwner );
}

// Retail 0x0066CC40 (25B, after the connect-reply handler 0x0066CB90): the
// same forwarder shape with the "->D" route literal (VA 0x00CE3AE0).
class Rva0066CC40Owner
{
public:
	void forwardToDRoute( void *message );
	char m_pad00[ 0x10 ];
	void *m_routeOwner;
};

// ?forwardToDRoute@Rva0066CC40Owner@@QAEXPAX@Z
void Rva0066CC40Owner::forwardToDRoute( void *message )
{
	Rva007F93E0( message, (void *)"->D", m_routeOwner );
}

// Existing thiscall teardown pin at RVA 0x655780 names the matched
// seven-byte base-vptr reinstall worker; no receiver adjustment is needed.
#pragma comment(linker, "/alternatename:??1BfmeC994@@UAE@XZ=??1BfmeMsg@@UAE@XZ")
