// cl: /O1 /EHsc /MD
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/Common/Rva003529B0Clone.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// Rva003529B0::Rva003529B0 0x003B410E (57B), Rva003529B0::rva00352a00
// 0x003B4147 (55B). Callee addresses are read off retail's call sites
// (reverse/symbols.csv). Only the placed bodies are carried; the donor's other
// definitions are omitted.
// The 0x00352A00 body allocates and copies the 0x000E855C-vtable record.
// The vtable and the exact Rva003529B0 copy constructor at 0x003529B0 identify
// the record. The method name remains address-derived because retail exposes no
// named caller or vtable slot for this non-virtual copy operation.

extern int Gen010E855C;

class Rva003525E0Pair
{
public:
	Rva003525E0Pair(const Rva003525E0Pair &other);

private:
	void *m_a;
	void *m_b;
};

class Rva003529B0
{
public:
	Rva003529B0(const Rva003529B0 *other)
		: m_pair(*(other ? &other->m_pair : 0))
	{
		m_vptr = &Gen010E855C;
		m_0C = other->m_0C;
		m_0D = other->m_0D;
		m_0E = 0;
	}

	Rva003529B0 *rva00352a00() const;

private:
	void *m_vptr;
	Rva003525E0Pair m_pair;
	char m_0C;
	char m_0D;
	char m_0E;
};

Rva003529B0 *Rva003529B0::rva00352a00() const
{
	return new Rva003529B0(this);
}
