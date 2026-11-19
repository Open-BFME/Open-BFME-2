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
#include <cstddef>
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline bool less<unsigned int>::operator()(unsigned int const &x,unsigned int const &y)const  { return x < y; } }
// bfme link decl-only begin
namespace _STL { template <> void swap<_STLP_alloc_proxy<void **, void *, allocator<void *> > >(_STLP_alloc_proxy<void **, void *, allocator<void *> > &, _STLP_alloc_proxy<void **, void *, allocator<void *> > &); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::_Vector_base(unsigned int, allocator<void *> const &); }
namespace _STL { template <> vector<void *, allocator<void *> >::vector(unsigned int, void *const &, allocator<void *> const &); }
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::~_Vector_base(); }
namespace _STL { template <> vector<void *, allocator<void *> >::~vector(); }
namespace _STL { template <> void ** allocator<void *>::allocate(unsigned int, void const *) const; }
namespace _STL { template <> allocator<void *> vector<void *, allocator<void *> >::get_allocator() const; }
namespace _STL { template <> void vector<void *, allocator<void *> >::swap(vector<void *, allocator<void *> > &); }
namespace _STL { template <> allocator<void *>::~allocator(); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?_M_insert@?$hashtable@U?$pair@$$CBHV?$list@UBfmePod264@@V?$allocator@UBfmePod264@@@_STL@@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod264;
namespace _STL { template <> pair<int const ,list<BfmePod264,allocator<BfmePod264> > > & hashtable<pair<int const ,list<BfmePod264,allocator<BfmePod264> > >,int,hash<int>,_Select1st<pair<int const ,list<BfmePod264,allocator<BfmePod264> > > >,equal_to<int>,allocator<pair<int const ,list<BfmePod264,allocator<BfmePod264> > > > >::_M_insert(pair<int const ,list<BfmePod264,allocator<BfmePod264> > > const &); }
// Suppress this TU's non-retail copy of ?insert@?$list@UBfmePod264@@V?$allocator@UBfmePod264@@@_STL@@@_STL@@QAE?AU?$_List_iterator:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> _List_iterator<BfmePod264,_Nonconst_traits<BfmePod264> > list<BfmePod264,allocator<BfmePod264> >::insert(_List_iterator<BfmePod264,_Nonconst_traits<BfmePod264> >,BfmePod264 const &); }
// Suppress this TU's non-retail copy of ?_M_bkt_num_key@?$hashtable@U?$pair@$$CBHV?$list@UBfmePod264@@V?$allocator@UBfmePod264@@@_:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> unsigned int hashtable<pair<int const ,list<BfmePod264,allocator<BfmePod264> > >,int,hash<int>,_Select1st<pair<int const ,list<BfmePod264,allocator<BfmePod264> > > >,equal_to<int>,allocator<pair<int const ,list<BfmePod264,allocator<BfmePod264> > > > >::_M_bkt_num_key(int const &) const; }
// Keep bucket access inline so the key-only search reproduces retail's
// complete 47-byte body without emitting a competing public accessor.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *const &vector<void *>::operator[](size_t n) const { return _M_start[n]; }
}
// Suppress this TU's non-retail vector<void*> operator[] copy (family2-LK3 row 25):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void *&_STL::vector<void*>::operator[](size_t);
}
// Suppress this TU's non-retail const-begin copy (row 47 family2-LK3): the
// /Od retail copy in stlport_vector_voidptr.cpp serves the link instead.
namespace _STL {
template <> vector<void *>::const_iterator _STL::vector<void *>::begin() const;
}
// Keep the bucket count inline with the const accessor above; neither
// specialization emits a competing public vector helper.
namespace _STL {
template <> __declspec(dllimport) __forceinline
size_t vector<void*>::size() const { return size_t(_M_finish - _M_start); }
}
// Suppress this TU's non-retail vector<void*> begin/end copies (family2-LK3 rows 6/9):
// the retail copies serve the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void **vector<void*>::begin();
template <> void **vector<void*>::end();
}

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}


struct BfmePod264 { int a[66]; };
// bfme link decl-only BfmePod264
namespace _STL { template <> void _Construct<BfmePod264, BfmePod264>(BfmePod264 *, BfmePod264 const &); }

// Use the fold-proven lookup owner at 0x002888D4.
namespace _STL {
template <> template <> __declspec(dllimport) __forceinline _Hashtable_node<pair<const int, list<BfmePod264> > > *
hashtable<pair<const int, list<BfmePod264> >, int, hash<int>,
          _Select1st<pair<const int, list<BfmePod264> > >, equal_to<int>,
          allocator<pair<const int, list<BfmePod264> > > >::_M_find<int>(const int &key) const {
    size_type n = _M_hash(key) % _M_buckets.size();
    _Node *first;
    for (first = (_Node *)_M_buckets[n];
         first && !_M_equals(_M_get_key(first->_M_val), key);
         first = first->_M_next) {}
    return first;
}
}

template _STL::list<BfmePod264> &_STL::hash_map<int, _STL::list<BfmePod264>, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<_STL::pair<const int, _STL::list<BfmePod264> > > >::operator[](const int &);
