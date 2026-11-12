// cl: /GX- /GS
//
// ?go@Rva00803730Host@@QAEXPAVRva00803730Getter@@@Z, retail 0x0066F770,
// 97 bytes. Dedicated TU holding only go (the donor file also defines
// Rva00803730Sink::apply, which lives at 0x00675B60 and lands separately).
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngine/Source/GameNetwork/Rva00803730FeslAttrs.cpp):
// verbatim go body. The two pushed-literal drifts in the sweep packet are
// string-literal DIR32s ("TID" 0xCE3930, "ALLOWED" 0xCE38E4), auto-patched.

// C994 and BfmeMsgVJH share the 8-byte message base and fields through +0x30;
// the keyed calls use the matched FESL accessors' record/capacity slots +0x10/+0x14.
// getPtr's PID/REASON results are consumed as ints, getBool's char default is 0,
// and the FESL route helper's returned pointer is ignored by this caller.
#pragma comment(linker, "/alternatename:??0BfmeC994@@QAE@PADH@Z=??0BfmeMsgVJH@@QAE@PADH@Z")
#pragma comment(linker, "/alternatename:?addInt@BfmeC994@@QAEXPBDH@Z=?addInt@Rva007E8810Message@@QAEXPBDH@Z")
#pragma comment(linker, "/alternatename:?addString@BfmeC994@@QAEXPBD0@Z=?addString@Rva007E8810Message@@QAEXPBD0@Z")
#pragma comment(linker, "/alternatename:?getBool@Rva00803730Getter@@QAE_NPBDD@Z=?getBool@Rva007E8810Message@@QAE_NPBD_N@Z")
#pragma comment(linker, "/alternatename:?getPtr@Rva00803730Getter@@QAEPAXPAX0@Z=?getInt@Rva007E8810Message@@QAEHPBDH@Z")
#pragma comment(linker, "/alternatename:?sendFeslMessage@@YAXPAXPBD0@Z=?Rva007F93E0@@YAPAXPAX00@Z")

class Rva00803730Getter
{
public:
	void *getPtr( void *key, void *fallback );
	bool getBool( const char *key, char flag );
};

class Rva00803730Sink
{
public:
	void apply( void *tid, bool allowed, void *pid, void *reason );

	char m_pad00[ 0x08 ];
	class Rva00809C60Identity *m_identity;
	void *m_field0c;
	void *m_connection;
	char m_pad14[ 0x44 ];
	class LanGame *m_game;
};

class Rva00803730Host
{
public:
	void go( Rva00803730Getter *r );

	char m_pad[0x18];
	Rva00803730Sink *m_sink;
};

void Rva00803730Host::go( Rva00803730Getter *r )
{
	void *tid = r->getPtr( (void *)"TID", 0 );
	bool allowed = r->getBool( "ALLOWED", 0 );
	void *pid = r->getPtr( (void *)"PID", 0 );
	void *reason = r->getPtr( (void *)"REASON", 0 );
	m_sink->apply( tid, allowed, pid, reason );
}

class Gen007F0130
{
public:
	static void *operator new( unsigned int size );
};

#include "../../Include/Common/Rva007E86B0Base.h"

class BfmeC994 : public Rva007E86B0Base
{
public:
	BfmeC994( char *buffer, int capacity );
	~BfmeC994();
	void addInt( const char *key, int value );
	void addString( const char *key, const char *value );

	int m_field08;
	int m_field0c;
	char *m_field10;
	int m_field14;
	int m_field18;
	int m_field1c;
	int m_field20;
	int m_field24;
	int m_field28;
	int m_field2c;
	char m_field30;
};

struct Rva00809C60Player
{
	int m_field00;
	int m_field04;
	int m_field08;
	int m_field0c;
	int m_pid;
	int m_gid;
	char m_i[ 0x20 ];
};

class LanGame
{
public:
	int m_state;
	int m_maxPlayers;
	Rva00809C60Player **m_players;
};

class Rva00809C60IdentityValue
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0c();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual const char *getValue();
};

class Rva00809C60Identity
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0c();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1c();
	virtual void v20();
	virtual void v24();
	virtual void v28();
	virtual void v2c();
	virtual void v30();
	virtual void v34();
	virtual void v38();
	virtual void v3c();
	virtual void v40();
	virtual void v44();
	virtual void v48();
	virtual void v4c();
	virtual void v50();
	virtual void v54();
	virtual void v58();
	virtual void v5c();
	virtual Rva00809C60IdentityValue *getValue();

	char m_pad04[ 0x24 ];
	int m_p28;
	int m_p2c;
};

#include "../../Include/GameNetwork/Rva007EB810Diag.h"

Rva007EB810Diag *Rva007EB810Get();
void sendFeslMessage( void *message, const char *route, void *connection ) throw();

static __forceinline Rva00809C60Player *Rva00809C60FindPlayer(
	const LanGame *game, int pid )
{
	for( int index = 0; index < game->m_maxPlayers; ++index )
	{
		Rva00809C60Player *player = game->m_players[ index ];
		if( player != 0 && player->m_pid == pid )
			return player;
	}
	return 0;
}

void Rva00803730Sink::apply( void *tid, bool allowed, void *pid, void *reason )
{
	char buffer[ 0x80 ];
	BfmeC994 message( buffer, sizeof( buffer ) );
	Rva00809C60Player *player = Rva00809C60FindPlayer(
		m_game, (int)(long)pid );
	if( player == 0 )
	{
		Rva007EB810Get()->fail(
			"lanPlayer",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\gamebrowser\\lantheateremulator.cpp",
			0x2a0 );
	}

	message.m_field1c = 'EGEG';
	message.m_field04 = player->m_field04;
	message.m_field08 = player->m_field08;
	message.m_field0c = player->m_field0c;
	message.addInt( "LID", -2 );
	message.addInt( "GID", player->m_gid );
	if( allowed )
	{
		message.addInt( "PID", player->m_pid );
		message.addString( "TICKET", "ticket" );
		message.addString( "I", player->m_i );
		int port = m_identity->m_p2c != 0 ? m_identity->m_p2c : m_identity->m_p28;
		message.addInt( "P", port );
		message.addString( "PL", "IP-LAN" );
		message.addString( "UGID", m_identity->getValue()->getValue() );
	}
	else
	{
		message.m_field20 = 'jden';
		message.addInt( "REASON", (int)(long)reason );
	}
	sendFeslMessage( &message, "->L", m_connection );
}
