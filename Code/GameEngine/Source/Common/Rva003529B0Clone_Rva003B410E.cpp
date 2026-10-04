// cl: -EHsc -MD /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common

// Rva003529B0::Rva003529B0(const Rva003529B0*) is the donor
// Rva003529B0Clone.cpp clone constructor. It copies the 8-byte
// Rva003525E0Pair at +4 through its copy ctor (retail 0x003B3FCD), installs the
// record vtable, then copies the +0xC..+0xE bytes. Only this ctor is emitted
// here; the donor's rva00352a00 body is omitted.
extern int Gen010E855C;

class Rva003525E0Pair
{
public:
	Rva003525E0Pair( const Rva003525E0Pair &other );

private:
	void *m_a;
	void *m_b;
};

class Rva003529B0
{
public:
	Rva003529B0( const Rva003529B0 *other );

private:
	void *m_vptr;
	Rva003525E0Pair m_pair;
	char m_0C;
	char m_0D;
	char m_0E;
};

Rva003529B0::Rva003529B0( const Rva003529B0 *other )
	: m_pair( *(other ? &other->m_pair : 0) )
{
	m_vptr = &Gen010E855C;
	m_0C = other->m_0C;
	m_0D = other->m_0D;
	m_0E = 0;
}
