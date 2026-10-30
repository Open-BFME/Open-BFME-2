class BfmeThingRF
{
public:
	void *bfmeGoRF( void *key, void *defaultValue );
};

struct Rva00809500Entry;
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

struct Rva00809500Entry
{
	char m_pad00[ 4 ];
};

class Rva00809010Finder
{
public:
	Rva00809500Sink *find( Rva00809500Entry *entry );
	char m_pad00[0x18];
	Rva00809500Sink *m_sinks[ 16 ]; // +0x18
};

Rva00809500Sink *Rva00809010Finder::find( Rva00809500Entry *entry )
{
	void *match = reinterpret_cast< BfmeThingRF * >( entry )->bfmeGoRF(
		// Retail's key is the pooled "GID" literal (not an image pointer).
		const_cast< char * >( "GID" ), 0 );
	for( int index = 0; index < 16; ++index )
	{
		Rva00809500Sink *sink = m_sinks[ index ];
		if( sink != 0 && sink->m_match == match )
			return sink;
	}
	return 0;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?Rva00809010Find@@YGPAURva00809500Sink@@PAURva00809500Entry@@@Z=?find@Rva00809010Finder@@QAEPAURva00809500Sink@@PAURva00809500Entry@@@Z")
