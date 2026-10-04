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

// Target 0x0066E440, 13 bytes; preceding int3 padding; terminal ret and int3 padding.
// Donor b1 RVA 0x00802180; target instructions corroborate these accesses.
class Rva0066E440
{
public:
	__int64 get() const;

	char m_lead[ 0x90 ];
	__int64 m_90;
};

__int64 Rva0066E440::get() const
{
	return m_90;
}

// Target 0x0066E4A0, 12 bytes; preceding int3 padding; terminal ret and int3 padding.
// Donor b1 RVA 0x008021F0; target instructions corroborate these accesses.
class Rva0066E4A0
{
public:
	void clear();

	int m_0;
	int m_4;
	char m_lead[ 0x1C ];
	int m_24;
	int m_28;
};

void Rva0066E4A0::clear()
{
	m_4 = 0;
	m_24 = 0;
	m_28 = 0;
}

// Target 0x0066F550, 12 bytes; preceding int3 padding; terminal ret and int3 padding.
// Donor b1 RVA 0x00803500; target instructions corroborate these accesses.
class Rva0066F550
{
public:
	void clear();

	char m_lead[ 0xC ];
	int m_c;
	int m_10;
	int m_14;
};

void Rva0066F550::clear()
{
	m_c = 0;
	m_10 = 0;
	m_14 = 0;
}

// Target 0x00699700, 11 bytes; preceding int3 padding; terminal ret and int3 padding.
// Donor b1 RVA 0x00858140; target instructions corroborate these accesses.
struct Rva00699700Record
{
	char m_lead[ 0x18D4 ];
	int m_18d4;
};

int Rva00699700( const Rva00699700Record *record )
{
	return record->m_18d4;
}

