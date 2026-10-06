// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc /DNDEBUG
//
// Non-virtual record destructors built from string members (0x00036410 is
// the folded AsciiString/StringBase<char> teardown, 0x00036E70 the wide one,
// 0x0002CC70 the AsciiString vector dtor). None of these bodies stores a
// vptr, and each tears down a member at +0x00, so the records are
// non-polymorphic; the older ??1Rva...@@UAE@XZ pin spelling at 0x00111B25
// cannot describe this body and is left as recorded. Owner types are
// unrecovered: the names are address-derived, and only the member offsets
// and callees are target facts.
//
// ??1Rva00111B25Record@@QAE@XZ         @0x00111B25 53B: strings +0x18, +0x00
// ??1Rva0007BB16Record@@QAE@XZ         @0x0007BB16 53B: strings +0x08, +0x00,
//   0x24-byte element proven by the rowed range destroy at 0x0007C2D7 (steps
//   0x24 via this dtor) and its vector callers at 0x0007C5D5/0x0007C614; tail
//   bytes past +0x0C are unrecovered. The 0x24 stride also matches the retail
//   copy at 0x00151336 (two strings at +0x00/+0x08 plus tail).
// ??1BfmeStringRecord000B94D2@@QAE@XZ  @0x000B6CF1 53B: strings +0x04, +0x00
// ??1Rva000543F5Record@@QAE@XZ         @0x000543F5 53B: wide +0x04, narrow +0x00
// ??1Rva000BEDF0Record@@QAE@XZ         @0x000BEDF0 53B: vector +0x04, string +0x00
// ??1Rva0033B352Record@@QAE@XZ         @0x0033B352 53B: wide +0x04, narrow +0x00

#include "ascii_string.h"

class BfmeWideString000543F5
{
public:
	~BfmeWideString000543F5();

private:
	void *m_data;
};

class RvaVecAscii
{
public:
	~RvaVecAscii();

private:
	int m_x[3];
};

struct Rva00111B25Record
{
	~Rva00111B25Record();
	AsciiString m_00;
	int m_pad04[5];
	AsciiString m_18;
};
Rva00111B25Record::~Rva00111B25Record() {}

struct Rva0007BB16Record
{
	~Rva0007BB16Record();
	AsciiString m_00;
	int m_04;
	AsciiString m_08;
	int m_tail0C[6];
};
Rva0007BB16Record::~Rva0007BB16Record() {}

struct BfmeStringRecord000B94D2
{
	~BfmeStringRecord000B94D2();
	AsciiString m_00;
	AsciiString m_04;
};
inline BfmeStringRecord000B94D2::~BfmeStringRecord000B94D2() {}

struct Rva000543F5Record
{
	~Rva000543F5Record();
	AsciiString m_00;
	BfmeWideString000543F5 m_04;
};
Rva000543F5Record::~Rva000543F5Record() {}

struct Rva000BEDF0Record
{
	~Rva000BEDF0Record();
	AsciiString m_00;
	RvaVecAscii m_04;
};
Rva000BEDF0Record::~Rva000BEDF0Record() {}

struct Rva0033B352Record
{
	~Rva0033B352Record();
	AsciiString m_00;
	BfmeWideString000543F5 m_04;
};
Rva0033B352Record::~Rva0033B352Record() {}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeBfmeStringRecord000B94D2InlineAnchor@@YAXPAVBfmeStringRecord000B94D2@@@Z absent-from-retail
void _bfmeBfmeStringRecord000B94D2InlineAnchor(BfmeStringRecord000B94D2 *p)
{
    p->BfmeStringRecord000B94D2::~BfmeStringRecord000B94D2();
}
#pragma inline_depth()

// -------------------------------------------------------------------------
// 0x00111B5A 42B find record by first string; walks 0x1c-byte
// Rva00111B25Record array from m_begin to m_end comparing m_00.
// Evidence: stride 0x1c matches Rva00111B25Record layout, callee is the rowed
// StringBase<char>::compare, callers are the unclaimed 0x000AFD85 body.
class Rva00111B5A
{
public:
	Rva00111B25Record *rva00111B5A( const char *name );
private:
	Rva00111B25Record *m_begin;
	Rva00111B25Record *m_end;
};

Rva00111B25Record *Rva00111B5A::rva00111B5A( const char *name )
{
	Rva00111B25Record *p = m_begin;
	while( p != m_end )
	{
		if( p->m_00.compare( name ) == 0 )
			return p;
		++p;
	}
	return 0;
}

// 0x000C4D34 (30B) is the one-argument STLport resize wrapper for
// BfmeStringRecord000B94D2. Its callee at 0x000C4733 destroys the eight-byte
// by-value record through the rowed destructor at 0x000B6CF1. The callee's
// shrink path calls rowed erase 0x000C0628; its growth path calls 0x000C225D,
// an unrecovered fill-insert candidate. The separate caller at 0x008B5293
// advances the range by eight bytes. These target relationships support the
// element view; the vector's owning class remains unknown.
namespace _STL
{
template <class Type> class allocator {};

template <class Type, class Allocator> class vector
{
public:
	typedef unsigned int size_type;
	void resize(size_type newSize, Type value);
	void resize(size_type newSize) { resize(newSize, Type()); }

private:
	Type *m_start;
	Type *m_finish;
	Type *m_endOfStorage;
};

template void vector<BfmeStringRecord000B94D2, allocator<BfmeStringRecord000B94D2> >::resize(unsigned int);
}
