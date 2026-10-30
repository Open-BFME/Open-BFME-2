// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// BfmeThingDGD destructor, retail 0x007F8090, 363 bytes. The matched
// allocator wrapper at 0x007F86A0 hands 0x6E0 bytes to the constructor at
// 0x007F7FA0, and the scalar deleting destructor at 0x007F86D0 calls this
// body and then frees the same 0x6E0 bytes. The field layout is the one the
// constructor attempt at reverse/attempts/0x007f7fa0.cpp recovered.
//
// Two levers shape the body. Each _ReadWriteBarrier keeps a zero store ahead
// of the compare that follows it, because the optimiser otherwise hoists the
// load of the next handle above that store. The whole tail is written as
// member and base destructors, so the compiler emits the reverse array loop
// over the four children itself, and /EHs-c- keeps that tail out of an
// unwind frame retail does not have.

#pragma intrinsic(_ReadWriteBarrier)
extern "C" void _ReadWriteBarrier( void );

// Retail installs six different vtables across this dtor (0xCE3018/0xCE3010/
// 0xCE3008 at the head, 0xCE2DE0/0xCE2DB4 in the child, 0xCE2E10 in the base);
// the BFME1 donor baked its own vtable VAs as literals, which cannot transfer.
// The address of a sacrificial anchor stands in (mov-imm-DIR32, patched from
// retail per site); a plain extern would load through a register and
// reschedule the stores.
// One anchor per distinct retail vtable, so each anchor resolves to a single
// address: child entry 0xCE2DE0, child exit 0xCE2DB4, base 0xCE2E10. The
// head's three tables (0xCE3018/0xCE3010/0xCE3008) are the ones
// BfmeThingDGDConstructor.cpp defines; their array names are address
// constants, so each store stays mov-imm-DIR32 as retail.
extern const void *const g_00CE3018[36];
extern const void *const g_00CE3010[1];
extern const void *const g_00CE3008[2];
static int BfmeThingDGDChildVTableAnchorIn;
static int BfmeThingDGDChildVTableAnchorOut;
static int BfmeThingDGDBaseVTableAnchor;

class Rva00803080
{
public:
	Rva00803080 &set( int value );
	void initPool();
	void clear( void );
	virtual void slot0( void ) = 0;
	virtual ~Rva00803080();
};

class Rva007F8090Owned0
{
public:
	virtual ~Rva007F8090Owned0();
};

class Rva007F8090Owned4
{
public:
	virtual void slot0( void ) = 0;
	virtual void slot1( void ) = 0;
	virtual void slot2( void ) = 0;
	virtual void slot3( void ) = 0;
	virtual ~Rva007F8090Owned4();
};

class Rva007F78E0Block
{
public:
	~Rva007F78E0Block() { clear(); }

	void clear( void );

private:
	unsigned char m_unmodelled[ 8 ];
};

class Rva007F6C60
{
public:
	~Rva007F6C60() { clear(); }

	void clear( void );

private:
	unsigned char m_unmodelled[ 0x10 ];
};

class Rva007F6BA0
{
public:
	~Rva007F6BA0() { clear(); }

	void clear( void );

private:
	unsigned char m_unmodelled[ 0x10 ];
};

class Gen_007e86c0
{
public:
	void m();
private:
	unsigned char m_unmodelled[ 0x10 ]; // +0x00
};

class Rva00800290Buffer
{
public:
	void reset( void );

private:
	unsigned char m_unmodelled[ 0x10 ];
};

// The handle registry the release calls go through.
class Rva007EFFC0Registry
{
public:
	virtual void slot0( void ) = 0;
	virtual void slot1( void ) = 0;
	virtual void slot2( void ) = 0;
	virtual void release( unsigned handle, int flag ) = 0;
};

class GenAlloc; GenAlloc *Gen007EFFC0();

// One 0x94-byte record of the four the holder owns at this+0x58.
struct Rva007F6D60Child
{
	~Rva007F6D60Child()
	{
		m_vftable = (unsigned)&BfmeThingDGDChildVTableAnchorIn;
		m_08 = 0;
		m_chain3C.m();
		m_chain2C.m();
		m_buffer1C.reset();
		m_vftable = (unsigned)&BfmeThingDGDChildVTableAnchorOut;
	}

	unsigned m_vftable;									///< child+0x00
	unsigned m_04;
	unsigned m_08;										///< child+0x08
	unsigned char m_pad0C[ 0x10 ];
	Rva00800290Buffer m_buffer1C;						///< child+0x1c
	Gen_007e86c0 m_chain2C;								///< child+0x2c
	Gen_007e86c0 m_chain3C;								///< child+0x3c
	unsigned char m_pad4C[ 0x48 ];
};

// The base whose destructor restores the first vftable after every member is
// gone. Retail ends the body with that single store and no call.
class Rva007F8090Base
{
public:
	~Rva007F8090Base() { m_v0 = (unsigned)&BfmeThingDGDBaseVTableAnchor; }

	unsigned m_v0;
	unsigned m_v4;
	unsigned m_v8;
};

class BfmeThingDGD : public Rva007F8090Base
{
public:
	~BfmeThingDGD();

	unsigned m_0c;
	unsigned m_10;
	unsigned m_14;
	Rva007F8090Owned0 *m_18;							///< retail this+0x18
	unsigned m_1c;
	Rva00803080 *m_20;									///< retail this+0x20
	Rva007F8090Owned4 *m_24;							///< retail this+0x24
	unsigned char m_pad28[ 0x10 ];
	Rva007F6BA0 m_38;									///< retail this+0x38
	Rva007F6C60 m_48;									///< retail this+0x48
	Rva007F6D60Child m_children[ 4 ];					///< retail this+0x58
	Rva007F78E0Block m_2a8;								///< retail this+0x2a8
	Rva007F78E0Block m_2b0;								///< retail this+0x2b0
	Rva007F78E0Block m_2b8;								///< retail this+0x2b8
	unsigned m_2c0;
	unsigned m_2c4;
	unsigned m_2c8;
	unsigned m_2cc;
	unsigned m_2d0;
	unsigned m_2d4;
	Rva007F8090Owned0 *m_2d8;							///< retail this+0x2d8
	unsigned char m_tail[ 0x404 ];
};

// ??1BfmeThingDGD@@QAE@XZ
BfmeThingDGD::~BfmeThingDGD()
{
	m_v0 = (unsigned)g_00CE3018;
	m_v4 = (unsigned)g_00CE3010;
	m_v8 = (unsigned)g_00CE3008;

	if( m_20 != 0 )
	{
		m_20->clear();
		delete m_20;
		m_20 = 0;
	}

	m_14 = 0;
	m_10 = 0;
	m_0c = 0;

	delete m_2d8;
	m_2d8 = 0;
	delete m_18;
	m_18 = 0;
	delete m_24;
	m_24 = 0;
	_ReadWriteBarrier();

	if( m_2d0 != 0 )
	{
		((Rva007EFFC0Registry *)((void *)Gen007EFFC0()))->release( m_2d0, 0 );
		m_2d0 = 0;
	}
	m_2d4 = 0;
	_ReadWriteBarrier();

	if( m_2c8 != 0 )
	{
		((Rva007EFFC0Registry *)((void *)Gen007EFFC0()))->release( m_2c8, 0 );
		m_2c8 = 0;
	}
	m_2cc = 0;
	_ReadWriteBarrier();

	if( m_2c0 != 0 )
	{
		((Rva007EFFC0Registry *)((void *)Gen007EFFC0()))->release( m_2c0, 0 );
		m_2c0 = 0;
	}
	m_2c4 = 0;
}

typedef char BfmeThingDGDChildSize[ ( sizeof( Rva007F6D60Child ) == 0x94 ) ? 1 : -1 ];
typedef char BfmeThingDGDSize[ ( sizeof( BfmeThingDGD ) == 0x6e0 ) ? 1 : -1 ];

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??1Gen007F86D0@@UAE@XZ=??1BfmeThingDGD@@QAE@XZ")
