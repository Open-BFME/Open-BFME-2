// cl: /GS
// Retail 0x0080A9B0 copies a game address record and sends its IP through ->L.

class BfmeC994
{
public:
	BfmeC994( char *buffer, int capacity );
	char *m_vft;
	int m_04;
	int m_08;
	int m_0c;
	char *m_10;
	int m_14;
	int m_18;
	int m_1c;
	int m_20;
	int m_24;
	int m_28;
	int m_2c;
	char m_30;
};

class BfmeThingCIC
{
public:
	void bfmeGoCIC( void *one, void *two );
};

class Gen_007e86c0
{
public:
	void m();
};

class Rva007E8760Addr
{
public:
	void format( char *buffer, unsigned size );
};

struct Rva00809500Entry
{
	char m_pad00[ 0x10 ];
	const char *m_text;
	int m_gdatBufferSize;
	int m_pad18;
	int m_length;
};

struct Rva00809500Sink
{
	void accept( Rva00809500Entry *entry );

	int m_pad00;
	int m_value04;
	int m_value08;
	int m_value0c;
	int m_pad10;
	char *m_gdatBuffer;
	int m_gdatBufferSize;
	unsigned int m_gdatTimestamp;
};

class Rva007EFFC0Allocator
{
public:
	virtual void v0();
	virtual void v1();
	virtual void *allocate( int size, int flags );
	virtual void release( void *block, int flags );
};

struct Rva007EB810Diag
{
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void fail( const char *expr, const char *file, int line );
};

struct Rva007E9B70Obj
{
	virtual void v0();
	virtual void v1();
	virtual unsigned int now();
};

Rva007EFFC0Allocator *Rva007EFFC0Get();
Rva007EB810Diag *Rva007EB810Get();
Rva007E9B70Obj *Rva007E9B70Get();

// Rva00809500Sink::accept: defined in Y4FeslFavGameAddress_accept.cpp (its row's unit).

class Rva00809010Finder
{
public:
	Rva00809500Sink *find( Rva00809500Entry *entry );
};

void *Rva007F93E0( void *message, void *route, void *owner );
char * __cdecl ji_009f70ba( char *dest, const char *src, unsigned count );

void Rva007E8640Copy(char *dest, unsigned int capacity, const char *source);

class Rva00808900Owner
{
public:
	void copy(char *source);

private:
	char m_pad[0x18];
	char m_dest[0x20];
};

void Rva00808900Owner::copy(char *source)
{
	ji_009f70ba(m_dest, source, 0x20);
}

class Rva00808AC0Owner
{
public:
	void copy(char *source);

private:
	char m_pad[0x0c];
	char m_dest[0x80];
};

void Rva00808AC0Owner::copy(char *source)
{
	ji_009f70ba(m_dest, source, 0x80);
}

// The BFME1 donor also defines Rva00808AF0Owner::copy here, but BFME2 range
// 0x00674A50 is already matched by Y2FeslSafeStrCopy.cpp as
// ?set@Rva00674A50Holder@@QAEXPBD@Z. Omit that duplicate range without
// transferring the donor's identity to the existing BFME2 body.

class LanTheaterEmulator
{
public:
	void notifyAddress( Rva00809500Entry *entry );
	char m_pad00[ 0x10 ];
	void *m_field10;
};

// LanTheaterEmulator::notifyAddress: defined in Y4FeslFavGameAddress_notify.cpp (its row's unit).

// Retail's call sites in this unit's matched rows land on bodies rowed under
// other spellings at the same addresses (same ABI). Bind the spellings used here.
#pragma comment(linker, "/alternatename:?ji_009f70ba@@YAPADPADPBDI@Z=?ji_0062983e@@YAXXZ")
