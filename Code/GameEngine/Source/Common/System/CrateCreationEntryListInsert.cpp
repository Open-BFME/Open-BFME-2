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

struct crateCreationEntry
{
	AsciiString crateName;
	float crateChance;
};

bool operator==(const crateCreationEntry &a, const crateCreationEntry &b);
bool operator<(const crateCreationEntry &a, const crateCreationEntry &b);

template class _STL::list<crateCreationEntry, _STL::allocator<crateCreationEntry> >;
