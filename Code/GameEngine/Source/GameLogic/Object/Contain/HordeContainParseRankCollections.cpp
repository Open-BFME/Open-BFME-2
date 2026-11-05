// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfmelist /Ireference/shims/bfmealloc
// stlport
// Donor: Open-BFME-1 HordeContainParseRanksThatStopAdvance.cpp and
// HordeContainParseRankSets.cpp; donor RVAs are NOT BFME2 addresses.
// BFME2 PC table VA C45530 identifies these field callbacks. The PC bodies
// use INI separators at +418 (donor +414), imported atoi at IAT BBA624,
// and out-of-line STLport insertion rather than the donor's inlined nodes.
// Names describe table roles; original parser symbol names are not recovered.
// Xbox retail/TU2 schema correspondence is a lead, not PC ABI/byte proof.
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include <list>

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> list<int, allocator<int> >::_Node *list<int, allocator<int> >::_M_create_node(const int &);
}

// Declaration-only: retail has one list<int>::insert (rowed in stlport_list_int_insert.cpp, node creation out of line);
// this unit calls it rather than emitting a copy with the node creation inlined.
namespace _STL {
template <> list<int, allocator<int> >::iterator list<int, allocator<int> >::insert(list<int, allocator<int> >::iterator, const int &);
}
#include <set>

// vector<int> fill/insert otherwise instantiates the _Construct<int,int>
// COMDAT (one byte shape per TU flags); a file-static overload takes those
// calls instead so this TU emits no external copy.
#include <new>
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

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator==(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node == b._M_node; }
}

#include "../../../../Include/Common/INI/INI.h"

void parseHordeContainRanksThatStopAdvance(INI *ini, void *, void *store, const void *)
{
    for (const char *token = ini->getNextTokenOrNull(ini->m_seps); token;
         token = ini->getNextTokenOrNull(ini->m_seps))
        ((_STL::list<int> *)store)->push_back(_STL::atoi(token));
}

void parseHordeContainRankSets(INI *ini, void *, void *store, const void *)
{
    for (const char *token = ini->getNextTokenOrNull(ini->m_seps); token;
         token = ini->getNextTokenOrNull(ini->m_seps))
        ((_STL::set<int> *)store)->insert(_STL::atoi(token));
}
