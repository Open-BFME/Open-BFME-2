// cl: /EHsc /MD
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

extern int Gen00C1F470;

// The pair's two leaf chains (copy constructors and the first chain's clear
// rowed in Rva003BCopyLeaves.cpp and Rva003BClearLeaves.cpp).
class Rva003B31DF
{
public:
	Rva003B31DF(const Rva003B31DF &other);
	~Rva003B31DF() { clear(); }
	void clear();

private:
	Rva003B31DF *m_next;
	int m_a;
	int m_b;
};

class Rva003B3204
{
public:
	Rva003B3204(const Rva003B3204 &other);

private:
	Rva003B3204 *m_next;
	int m_a;
	int m_b;
};

class Rva003525E0Pair
{
public:
	Rva003525E0Pair(const Rva003525E0Pair &other);

private:
	Rva003B31DF *m_a;
	Rva003B3204 *m_b;
};

// ??0Rva003525E0Pair@@QAE@ABV0@@Z, retail 0x003B3FCD..0x003B4071 (164 bytes,
// EH, RET 4; Ghidra stops at its inline catch funclet, 108 bytes in): the
// pair copy the clone constructor 0x003B410E runs. Each chain is deep-copied
// when present; if the second copy throws, the first chain is cleared and
// freed and the exception rethrown.
Rva003525E0Pair::Rva003525E0Pair(const Rva003525E0Pair &other)
{
	m_a = other.m_a ? new Rva003B31DF(*other.m_a) : 0;
	try
	{
		m_b = other.m_b ? new Rva003B3204(*other.m_b) : 0;
	}
	catch (...)
	{
		delete m_a;
		throw;
	}
}

class Rva003529B0
{
public:
	Rva003529B0(const Rva003529B0 *other)
		: m_pair(*(other ? &other->m_pair : 0))
	{
		m_vptr = &Gen00C1F470;
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
