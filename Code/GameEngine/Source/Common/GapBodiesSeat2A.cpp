// Small bodies from .text gaps no ledger row covered (each begins after its
// neighbour's padding or return and ends in its own ret or tail jump), none
// reached by a direct caller in retail. Retail bytes establish every shape;
// the owning classes are not recovered, so each keeps an address-derived name
// and a view of only the members it touches. Callees are the ledger's
// existing rows under their current spellings.
#include <stdlib.h>

// --- 0x000B3F75 (15B): address of element `index` in the 0xFC-byte record
// array whose base pointer is at +0.
struct Rva000B3F75Record
{
	unsigned char m_data[0xFC];
};

class Rva000B3F75
{
public:
	Rva000B3F75Record *rva000B3F75(int index);
private:
	Rva000B3F75Record *m_records;
};

Rva000B3F75Record *Rva000B3F75::rva000B3F75(int index)
{
	return &m_records[index];
}

// --- 0x000B693D (15B): when the object at +0x68 exists, assign the argument
// to it through the rowed ?bfmeAssign@Gen_0075EF90@@QAEAAV1@ABV1@@Z
// (0x000B4682) as a tail jump.
class Gen_0075EF90
{
public:
	Gen_0075EF90 &bfmeAssign(const Gen_0075EF90 &that);
};

class Rva000B693D
{
public:
	void rva000B693D(const Gen_0075EF90 &that);
private:
	unsigned char m_pad00[0x68];
	Gen_0075EF90 *m_68;
};

void Rva000B693D::rva000B693D(const Gen_0075EF90 &that)
{
	if (m_68)
		m_68->bfmeAssign(that);
}

// --- 0x000FB85D (15B): holder destructor freeing the block at +0x18
// through the rowed _free (0x00030830).
struct Rva000FB85D
{
	~Rva000FB85D();
	unsigned char m_pad00[0x18];
	void *m_18;
};

Rva000FB85D::~Rva000FB85D()
{
	if (m_18)
		free(m_18);
}

// --- 0x000D167A (13B): ORs the argument into the flag word at +0x118.
class Rva000D167A
{
public:
	void addFlags(unsigned int flags);
private:
	unsigned char m_pad00[0x118];
	unsigned int m_118;
};

void Rva000D167A::addFlags(unsigned int flags)
{
	m_118 |= flags;
}
