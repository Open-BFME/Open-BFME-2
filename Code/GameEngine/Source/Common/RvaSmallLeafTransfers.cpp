// cl: /O2 /DNDEBUG /MD /EHsc
// BFME 1 donor: UnclaimedSmallLeaves02.cpp, revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76.
// The full donor TU was compiled under BFME 2 settings and searched in game.dat.
// Each body below has a unique placement and passes full-byte verification.
// Identity is not recovered: target-address names replace donor-address names.
// Field names describe target instructions; donor structure is the source lead.
// Lead arrays preserve only witnessed access offsets, not a complete layout.

// Target 0x007588E0, 28 bytes; preceding int3 padding; terminal ret and int3 padding.
// Donor b1 RVA 0x009A2940; target instructions corroborate these accesses.
class Rva007588E0
{
public:
	void set( int value );

	char m_lead[ 0xC068 ];
	int m_value;
	char m_dirty;
};

void Rva007588E0::set( int value )
{
	if ( value != m_value )
	{
		m_value = value;
		m_dirty = 1;
	}
}

// Target 0x00674E70, 19 bytes; preceding int3 padding; terminal ret and int3 padding.
// Donor b1 RVA 0x00808F50; target instructions corroborate these accesses.
class Rva00674E70
{
public:
	int isRecent( unsigned int now ) const;

	char m_lead[ 0x1C ];
	unsigned int m_1c;
};

int Rva00674E70::isRecent( unsigned int now ) const
{
	return now - m_1c < 3000;
}

// Target 0x0061FC30, 15 bytes; preceding int3 padding; terminal ret and int3 padding.
// Donor b1 RVA 0x009ECA50; target instructions corroborate these accesses.
struct Rva0061FC30Block
{
	char m_lead[ 4 ];
	unsigned short m_refs;
};

class Rva0061FC30
{
public:
	Rva0061FC30( Rva0061FC30Block *block );

	Rva0061FC30Block *m_block;
};

Rva0061FC30::Rva0061FC30( Rva0061FC30Block *block )
{
	m_block = block;
	++block->m_refs;
}

// Target 0x0073A360, 15 bytes; preceding int3 padding; terminal ret and int3 padding.
// Donor b1 RVA 0x008F7DC0; target instructions corroborate these accesses.
class Rva0073A360
{
public:
	void clear( int index );

	char m_lead[ 0x24 ];
	int m_slots[ 1 ];
};

void Rva0073A360::clear( int index )
{
	m_slots[ index ] = 0;
}

// Target 0x00674B60, 14 bytes; preceding int3 padding; terminal ret and int3 padding.
// Donor b1 RVA 0x00808C10; target instructions corroborate these accesses.
struct Rva00674B60Record
{
	char m_lead[ 0x20 ];
	unsigned int m_20;
};

void __stdcall Rva00674B60( Rva00674B60Record *record )
{
	record->m_20 = 0xC0000000;
}

// Target 0x00758CA0, 13 bytes; preceding int3 padding; terminal ret and int3 padding.
// Donor b1 RVA 0x009A2F20; target instructions corroborate these accesses.
class Rva00758CA0
{
public:
	int bit0() const;

	char m_lead[ 0xC ];
	unsigned int m_c;
};

int Rva00758CA0::bit0() const
{
	return ( m_c & 1 ) == 1;
}

