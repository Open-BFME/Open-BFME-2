// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Small bodies from .text gaps no Ghidra function covers (forty-fifth
// batch; see GapBodiesGE01.cpp), from the /O1 retail regions
// 0x00148B42..0x001493EF and 0x0014CD63..0x001541DF
// (reverse/retail_inventory/flag_regions.csv). Each begins after its
// neighbour's padding or ret and ends in its own ret. Retail bytes establish
// every shape; owning classes are not recovered, so each keeps an
// address-derived name and a view of only the members it touches. Callees
// and globals use the ledger's existing spellings.

class AsciiString;

// --- 0x00148DB3 (16B): a name key's string through TheNameKeyGenerator's
// rowed keyToName 0x00148C95.
enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

#include "../../Include/Common/NameKeyGenerator.h"

extern NameKeyGenerator *TheNameKeyGenerator;

const AsciiString &rva00148DB3(NameKeyType key)
{
	return TheNameKeyGenerator->keyToName(key);
}

// --- 0x0014D1B7 (24B): three words at +0x10; 0x0014D1CF (20B): a pointer at
// +0x1C with its presence at +0x18.
class Rva0014D1B7
{
public:
	void rva0014D1B7(int a, int b, int c);
	void rva0014D1CF(void *p);
private:
	char m_pad00[0x10];
	int m_10;
	int m_14;
	int m_18;
	void *m_1C;
};

void Rva0014D1B7::rva0014D1B7(int a, int b, int c)
{
	m_10 = a;
	m_14 = b;
	m_18 = c;
}

void Rva0014D1B7::rva0014D1CF(void *p)
{
	m_1C = p;
	m_18 = p != 0;
}

// --- 0x0014DB40 (11B): zero the +0x1C float, returning this; 0x0014DB4B
// (6B): the +4 word less two.
class Rva0014DB40
{
public:
	Rva0014DB40 *rva0014DB40();
	int rva0014DB4B() const;
private:
	int m_00;
	int m_04;
	char m_pad08[0x1C - 0x08];
	float m_1C;
};

Rva0014DB40 *Rva0014DB40::rva0014DB40()
{
	m_1C = 0.0f;
	return this;
}

int Rva0014DB40::rva0014DB4B() const
{
	return m_04 - 2;
}

// --- 0x0014F89B (19B): construct the leading member through the rowed
// Rva00080221 constructor from the address of the by-value argument.
class Rva00080221
{
public:
	Rva00080221(const int *value);
};

class Rva0014F89B
{
public:
	Rva0014F89B(int value);
private:
	Rva00080221 m_inner;
};

Rva0014F89B::Rva0014F89B(int value) : m_inner(&value)
{
}

// --- 0x001524DC (18B): copy construction of a leading Rva0007BB16Record
// vector through its rowed assignment 0x001522CF; 0x001524EE (11B): clear a
// Rva0015229CVector through its rowed EraseRange 0x0015229C.
struct Rva0007BB16Record;

namespace _STL
{
	template <class T> class allocator;
	template <class T, class A = allocator<T> > class vector
	{
	public:
		vector() {}
		vector &operator=(const vector &that);
	private:
		T *m_start;
		T *m_finish;
		T *m_endOfStorage;
	};
}

class Rva001524DC
{
public:
	Rva001524DC(const Rva001524DC &that);
private:
	_STL::vector<Rva0007BB16Record> m_records;
};

Rva001524DC::Rva001524DC(const Rva001524DC &that)
{
	m_records = that.m_records;
}

class Rva0015229CVector
{
public:
	Rva0007BB16Record *EraseRange(Rva0007BB16Record *first, Rva0007BB16Record *last);
	void rva001524EE();
private:
	Rva0007BB16Record *m_start;
	Rva0007BB16Record *m_finish;
};

void Rva0015229CVector::rva001524EE()
{
	EraseRange(m_start, m_finish);
}
