// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Dedicated unit without the bfmelist __forceinline _M_create_node shim so
// list<crateCreationEntry>::insert calls the out-of-line create_node rowed at
// 0x0035CAB4 from the companion CrateCreationEntryList TU, mirroring
// stlport_list_asciistring_insert.cpp. Retail 0x0035CB8D (37 bytes) is the
// insert worker and 0x0035CBFE (26 bytes) is push_back; the node is 16 bytes
// (8 links plus 8-byte crate entry) and create delegates per element to the
// crate _Construct twin pin at 0x0035CA02.
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}


#include "ascii_string.h"
// Suppress this TU's non-retail copy of ?erase@?$list@UcrateCreationEntry@@V?$allocator@UcrateCreationEntry@@@_STL@@@_STL@@QAE?AU?:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct crateCreationEntry;
namespace _STL { template <> _List_iterator<crateCreationEntry,_Nonconst_traits<crateCreationEntry> > list<crateCreationEntry,allocator<crateCreationEntry> >::erase(_List_iterator<crateCreationEntry,_Nonconst_traits<crateCreationEntry> >); }
// Suppress this TU's non-retail copy of ?_M_create_node@?$list@UcrateCreationEntry@@V?$allocator@UcrateCreationEntry@@@_STL@@@_STL:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> _List_node<crateCreationEntry> * list<crateCreationEntry,allocator<crateCreationEntry> >::_M_create_node(crateCreationEntry const &); }
// Suppress this TU's non-retail copy of ?clear@?$_List_base@UcrateCreationEntry@@V?$allocator@UcrateCreationEntry@@@_STL@@@_STL@@Q:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> void _List_base<crateCreationEntry,allocator<crateCreationEntry> >::clear(); }

struct crateCreationEntry
{
	AsciiString crateName;
	float crateChance;
};

bool operator==(const crateCreationEntry &a, const crateCreationEntry &b);
bool operator<(const crateCreationEntry &a, const crateCreationEntry &b);

// The sort wrapper calls the rowed worker in CrateCreationEntryList.cpp.
namespace _STL {
template <> void _S_sort<crateCreationEntry, allocator<crateCreationEntry>, less<crateCreationEntry> >(
    list<crateCreationEntry> &, less<crateCreationEntry>);
}

template _STL::list<crateCreationEntry>::iterator _STL::list<crateCreationEntry>::insert(iterator, const crateCreationEntry &);
template void _STL::list<crateCreationEntry>::push_back(const crateCreationEntry &);
template void _STL::list<crateCreationEntry>::sort();
