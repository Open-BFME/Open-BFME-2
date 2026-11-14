// flags: region default (reverse/retail_inventory/flag_regions.csv)
// stlport
// ?rva002E2285@Rva002E2285@@QAEXPAHABVRva0020E449@@@Z retail 0x002E2285 102 bytes.
// Unlock lane: if map<int,int> at +0x2A8 lacks *elem, broadcast via
// Rva002E1E6FList::forEach at +0x04 with rowed forwarder 0x005CB260,
// then insert key into set<int> at +0x29C and accumulate Rva0020E449
// at +0x258. Evidence: callees rowed 0x388F63 0x2E1E6F 0xBC15D 0x20E250;
// caller 0x0020F3B9 passes (elem, scaled Rva) with this=manager;
// prev/next share /O1.
#include <map>
#include <set>

// vector<int> fill/insert otherwise instantiates the _Construct<int,int>
// COMDAT (one byte shape per TU flags); a file-static overload takes those
// calls instead so this TU emits no external copy.
#include <new>

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
typedef _Rb_tree<int, int, _Identity<int>, less<int>, allocator<int> > Lk11RbIntSet;
template <> pair<Lk11RbIntSet::iterator, bool> Lk11RbIntSet::insert_unique(const int &);
}
namespace _STL {
static inline void _Construct(int *__p, const int &__val)
{ new (__p) int(__val); }
}

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

#include "../../Include/Common/Rva002E1E6FListener.h"

class Rva002E1E6FList
{
public:
	void forEach(void (Rva002E1E6FListener::*notify)(void *, int, int), void *arg, int value, int extra);
private:
	Rva002E1E6FListener **m_begin;
	Rva002E1E6FListener **m_end;
	Rva002E1E6FListener **m_capacity;
	unsigned int m_index;
};

class Rva0020E449
{
public:
	void rva0020E250(const Rva0020E449 &other);
private:
	char m_pad[4];
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
};

#include "../../Include/Common/Rva005CB260.h"

class Rva002E2285
{
public:
	void rva002E2285(int *elem, const Rva0020E449 &other);
private:
	void *m_vptr;
	Rva002E1E6FList m_list;
	char m_pad14[0x258 - 0x14];
	Rva0020E449 m_accum;
	char m_pad274[0x29C - 0x274];
	_STL::set<int> m_ranks;
	_STL::map<int, int> m_lookup;
};

void Rva002E2285::rva002E2285(int *elem, const Rva0020E449 &other)
{
	int key = *elem;
	if (m_lookup.find(key) == m_lookup.end()) {
		m_list.forEach(
			reinterpret_cast<void (Rva002E1E6FListener::*)(void *, int, int)>(static_cast<void (Rva005CB260::*)()>(&Rva005CB260::rva005CB260)),
			this,
			(int)elem,
			(int)&other);
	}
	key = *elem;
	m_ranks.insert(key);
	m_accum.rva0020E250(other);
}
