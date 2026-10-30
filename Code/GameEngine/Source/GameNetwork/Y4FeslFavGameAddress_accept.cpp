// cl: /O2 /GS
//
// Retail 0x00674DF0 (127B). FESL game-address accept path: frees the old
// gdat buffer, allocates the new size, fail-reports a null buffer, copies
// the address text and stamps Rva007E9B70 time.
// Transferred from the BFME1 reconstruction (BFME1 0x0080A9B0, same
// Y4FeslFavGameAddress.cpp TU family). Only accept is claimed here; the
// TU's notifyAddress sibling needs its own identity pass.

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

class GenAlloc; GenAlloc *Gen007EFFC0();
Rva007EB810Diag *Rva007EB810Get();
int Rva00656B60Get();

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
public:
	void accept(Rva00809500Entry *entry);
	char m_pad00[0x4];
	int m_value04; // +0x04
	int m_value08; // +0x08
	int m_value0c; // +0x0C
	void *m_match; // +0x10
	char *m_gdatBuffer; // +0x14
	int m_gdatBufferSize; // +0x18
	unsigned int m_gdatTimestamp; // +0x1C
};

void Rva00809500Sink::accept( Rva00809500Entry *entry )
{
	if( m_gdatBuffer != 0 )
		((Rva007EFFC0Allocator *)Gen007EFFC0())->release( m_gdatBuffer, 0 );

	m_gdatBufferSize = entry->m_gdatBufferSize;
	m_gdatBuffer = (char *)((Rva007EFFC0Allocator *)Gen007EFFC0())->allocate( m_gdatBufferSize, 0 );
	if( m_gdatBuffer == 0 )
	{
		Rva007EB810Get()->fail(
			"mGdatBuffer",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\gamebrowser\\lantheateremulator.cpp",
			0x4EA );
	}

	const char *source = entry->m_text;
	char *dest = m_gdatBuffer;
	char value;
	do
	{
		value = *source++;
		*dest++ = value;
	}
	while( value != 0 );

	m_gdatTimestamp = ((Rva007E9B70Obj *)Rva00656B60Get())->now();
}
