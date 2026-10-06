// cl: /Ireference/shims/bfmelist /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// _STL::hash_map<int, _STL::list<BfmePod264> >::operator[] @0x0028A104 166B.
// Retail finds the key via hashtable find (rowed dup 0x00148B27), inserts a
// default pair on miss via _M_insert 0x0028A0BB and returns the mapped list.
// Caller 0x0028A237 pushes key and reuses it; callee itself takes one arg
// (ret 4). Evidence: STLport _hash_map.h operator[] shape, prev/next rows in
// this family (stlport_hash_map_int_list_pod264.cpp flags), callees rowed,
// unlock lane unblocks 0x0028A1AA.

#include <hash_map>
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}


struct BfmePod264 { int a[66]; };

template _STL::list<BfmePod264> &_STL::hash_map<int, _STL::list<BfmePod264>, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<_STL::pair<const int, _STL::list<BfmePod264> > > >::operator[](const int &);
