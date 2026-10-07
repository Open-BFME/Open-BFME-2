// ?rva0021386C@Rva00056F61@@QAEPAXPBVAsciiString@@@Z
// partial score=0.93 date=2026-10-07
// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?rva0021386C@Rva00056F61@@QAEPAXPBVAsciiString@@@Z @0x0021386C 121B. Find-or-insert.
// Evidence: unlock lane; caller 0x0021399A; callees rva0041534B StringBase copy _M_insert releaseBuffer; returns node+8 or insert+4.
#include "ascii_string.h"
#include <hash_map>

class Rva00056F61;
struct Rva0041534BIter
{
	void *m_node;
	Rva00056F61 *m_table;
};

struct Rva00212A16Record : public AsciiString
{
	Rva00212A16Record() {}
	Rva00212A16Record(const Rva00212A16Record &o) : AsciiString(o) {}
	bool operator==(const Rva00212A16Record &o) const { return compare(o.str()) == 0; }
	bool operator<(const Rva00212A16Record &o) const { return compare(o.str()) < 0; }
};

namespace _STL {
template<> void _Construct<Rva00212A16Record, Rva00212A16Record>(Rva00212A16Record *, const Rva00212A16Record &);
template<> struct hash<Rva00212A16Record> { unsigned operator()(const Rva00212A16Record &) const; };
}

class Rva00056F61
{
public:
	Rva0041534BIter rva0041534B(const AsciiString *key);
	void *rva0021386C(const AsciiString *key);
	typedef _STL::pair<Rva00212A16Record const, Rva00212A16Record> Pair;
	typedef _STL::hashtable<Pair, Rva00212A16Record, _STL::hash<Rva00212A16Record>, _STL::_Select1st<Pair>, _STL::equal_to<Rva00212A16Record>, _STL::allocator<Pair> > Table;
	Table m_table;
};

void *Rva00056F61::rva0021386C(const AsciiString *key)
{
	{
		Rva0041534BIter it = rva0041534B(key);
		if (it.m_node != 0)
			return (char *)it.m_node + 8;
	}
	Pair p((const Rva00212A16Record &)*(const Rva00212A16Record *)(const void *)key, Rva00212A16Record());
	Pair &res = m_table._M_insert(p);
	return (char *)&res + 4;
}
