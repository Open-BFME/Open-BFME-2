// cl: /O2 /GX- /GS
// Retail 0x0080AA80 is the CGAM arm of the FESL browser dispatcher at
// 0x00803D30.  The dispatcher loads its +0x18 sink, the same sink passed by
// the named Rva00803620Host::go/apply pair.  The method name remains
// address-derived: the retail bytes prove the raw entry ABI and the
// lantheateremulator.cpp family, but do not preserve the original spelling.

class Rva007E8810Message
{
public:
	int getInt( const char *key, int defaultValue );

	char m_pad00[ 0x10 ];
	const char *m_payload;
	char m_pad14[ 8 ];
	int m_category;
	char m_pad20[ 0x10 ];
};

struct Rva00809500Entry
{
	char m_pad00[ 4 ];
};

struct Rva00809500Sink
{
	char m_pad00[ 8 ];
	int m_value08;
};

class Rva00809010Finder
{
public:
	Rva00809500Sink *find( Rva00809500Entry *entry );
};

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
	void addString( const char *key, const char *value );

	char m_pad08[ 8 ];
	char *m_buffer;
	int m_capacity;
	int m_field18;
	int m_category;
	int m_field20;
	char m_tail24[ 0x10 ];
};

void bfmeCopyBZD( char *dest, const char *source, unsigned int size );

class BfmeMsgVJJ
{
public:
	int m_bfme00;
	int m_bfme04;
	int m_bfme08;
	int m_bfme0c;
};

class BfmeThingVJJ
{
public:
	void bfmeGoVJJ( BfmeMsgVJJ *out );
};

void *Rva007F93E0( void *message, void *route, void *owner );

class Rva00803620Sink
{
public:
	void rva0080AA80( Rva00809500Entry *entry );

	char m_pad00[ 0x10 ];
	void *m_field10;
	char m_pad14[ 0x15c ];
	int m_transactionId;
	char m_name[ 0x20 ];
};

void Rva00803620Sink::rva0080AA80( Rva00809500Entry *entry )
{
	Rva00809500Entry *incoming = entry;
	Rva00809500Sink *sink;
	char buffer[ 0x40 ];
	BfmeC994 reply( buffer, sizeof( buffer ) );
	sink = reinterpret_cast< Rva00809010Finder * >( this )->find( incoming );

	if( sink->m_value08 == 0 )
	{
		m_transactionId = reinterpret_cast< Rva007E8810Message * >( incoming )->getInt(
			"TID", 0 );
	}
	else
	{
		Rva007E8810Message *message = reinterpret_cast< Rva007E8810Message * >( incoming );
		reply.m_category = message->m_category;
		reply.m_field20 = 0xC0000000;
		bfmeCopyBZD( reply.m_buffer, message->m_payload, reply.m_capacity );
		reinterpret_cast< BfmeThingVJJ * >( sink )->bfmeGoVJJ(
			reinterpret_cast< BfmeMsgVJJ * >( &reply ) );
		reply.addString( "NAME", m_name );
		Rva007F93E0( &reply, "->L", m_field10 );
	}
}

// Retail's call sites in this unit's matched rows land on bodies rowed under
// other spellings at the same addresses (same ABI). Bind the spellings used here.
#pragma comment(linker, "/alternatename:?bfmeCopyBZD@@YAXPADPBDI@Z=?ji_0062983e@@YAXXZ")

// Existing thiscall teardown pin at RVA 0x655780 names the matched
// seven-byte base-vptr reinstall worker; no receiver adjustment is needed.
#pragma comment(linker, "/alternatename:??1BfmeC994@@UAE@XZ=??1BfmeMsg@@UAE@XZ")

// ?rva0066F750@Rva0066F750@@QAEXPAURva00809500Entry@@@Z @0x0066F750 8B member
// forwarder to rowed ?rva0080AA80@Rva00803620Sink@@QAEXPAURva00809500Entry@@@Z
// (0x00676980; entry arg passes through the shared stack slot). No callers.
// Honest address name.
class Rva0066F750
{
public:
	void rva0066F750(Rva00809500Entry *entry);
private:
	char m_pad[0x18];
	Rva00803620Sink *m_member;
};
void Rva0066F750::rva0066F750(Rva00809500Entry *entry)
{
	return m_member->rva0080AA80(entry);
}
