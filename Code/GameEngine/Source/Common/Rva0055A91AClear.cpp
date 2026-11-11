// cl: /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
// ?rva0055A91A@ScoredKillTracker@@QAEXXZ @ 0x0055A91A 34B
// Evidence: LINK BONUS via 0x0039C09C; inner Rva0039BCF8 at +0x10 via rowed rva0039BCF8 0x0039BCF8; flag +0x14 set -1; list<int> at +0x18 via rowed clear 0x0023DAA5; count +0x1C set 0; callers 0x0039C0CA 0x0041453E 0x0055A93F 0x0055AC2D 0x0055A993; layout like Rva0055AA06 list/count.
#include <list>

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> void _List_base<int, allocator<int> >::clear();
}

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> list<int, allocator<int> >::iterator list<int, allocator<int> >::erase(list<int, allocator<int> >::iterator);
}

// Declaration-only: retail has one list<int>::insert (rowed in stlport_list_int_insert.cpp, node creation out of line);
// this unit calls it rather than emitting a copy with the node creation inlined.
namespace _STL {
template <> list<int, allocator<int> >::iterator list<int, allocator<int> >::insert(list<int, allocator<int> >::iterator, const int &);
}

// vector<int> fill/insert otherwise instantiates the _Construct<int,int>
// COMDAT (one byte shape per TU flags); a file-static overload takes those
// calls instead so this TU emits no external copy.
#include <new>
namespace _STL {
static inline void _Construct(int *__p, const int &__val)
{ new (__p) int(__val); }
}

// list<int> destruction otherwise instantiates per-TU deallocate
// COMDATs (one byte shape per TU flags); explicit dllimport+forceinline
// specializations take those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<_List_node<int> >::deallocate(_List_node<int>* __p, size_t __n) const {
  _STLP_ASSERT( (__p == 0) == (__n == 0) )
    if (__p != 0) __sgi_alloc::deallocate((void*)__p, __n * sizeof(value_type));
}
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<_List_node<int> *, _List_node<int>, allocator<_List_node<int> > >::deallocate(_List_node<int> *__p, size_t __n) {
  allocator<_List_node<int> >().deallocate(__p, __n);
}
}

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}


class Rva0039BCF8
{
public:
	void **rva0039BCF8(void *val);
	char m_pad00[0x100];
	int m_100; // +0x100
};

class ModuleData;

class Rva0039C7A5Holder
{
public:
	void add(const ModuleData *data);
};

// LoadPostProcess is a virtual: slot 1 of vtable 0x00C3A08C, which the dtor
// 0x00414520 and the copy ctor 0x0055AB99 store at +0.
#include "ScoredKillTrackerView.h"

class Player
{
public:
	char m_pad00[0x3BC];
	Rva0039BCF8 m_3BC; // +0x3BC
};

#include "../../Include/Common/PlayerList.h"

extern PlayerList *ThePlayerList;

void ScoredKillTracker::rva0055A91A()
{
	if (m_keeper == 0)
		return;
	m_keeper->rva0039BCF8(this);
	m_playerIndex = -1;
	m_trackedKills.clear();
	m_trackedKillsCount = 0;
}

void ScoredKillTracker::hookToKeeper(Rva0039BCF8 *p)
{
	rva0055A91A();
	if (p == 0)
		return;
	m_keeper = p;
	m_playerIndex = p->m_100;
	((Rva0039C7A5Holder *)p)->add((const ModuleData *)this);
}

void ScoredKillTracker::LoadPostProcess()
{
	if (m_playerIndex == -1 || m_playerIndex < 0)
		return rva0055A91A();
	Player *player = ThePlayerList->getNthPlayer(m_playerIndex);
	if (player == 0)
		return rva0055A91A();
	hookToKeeper(&player->m_3BC);
}

// Retail 0x0055AC1F: the class's own assignment, reached from the vector copy at 0x004143A4. It drops the old
// keeper link, copies everything but the keeper and player index, then re-hooks to the source's keeper.
ScoredKillTracker &ScoredKillTracker::operator=(const ScoredKillTracker &other)
{
	if (this == &other)
		return *this;
	rva0055A91A();
	m_lifetime = other.m_lifetime;
	m_filter = other.m_filter;
	m_value0c = other.m_value0c;
	m_trackedKills = other.m_trackedKills;
	m_trackedKillsCount = other.m_trackedKillsCount;
	m_position = other.m_position;
	if (other.m_keeper != 0)
		hookToKeeper(other.m_keeper);
	return *this;
}
