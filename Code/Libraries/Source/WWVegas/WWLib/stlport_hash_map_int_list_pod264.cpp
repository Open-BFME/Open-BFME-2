// cl: /Ireference/shims/bfmelist /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// hash_map<int, list<BfmePod264>>: its pair copy (0x0028A02F) calls the rowed list<BfmePod264> copy constructor (stlport_pod_list_bodies.cpp, whose bfmelist layout shim this unit shares), and its node constructor (0x0028A096) zeroes the next link and places the pair at +4.
// The key is a 32-bit int-hashed type; int stands in, as in
// stlport_pod_hash_bodies.cpp, whose whole-class instantiation this follows.

// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <hash_map>
#include <list>

#include <cstddef>
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline bool less<unsigned int>::operator()(unsigned int const &x,unsigned int const &y)const  { return x < y; } }
namespace _STL { template <> inline allocator<void *>::~allocator() _STLP_NOTHROW {} }
// bfme link decl-only begin
namespace _STL { template <> inline void swap(_STLP_alloc_proxy<void **, void *, allocator<void *> > &left, _STLP_alloc_proxy<void **, void *, allocator<void *> > &right) { swap(left._M_data, right._M_data); } }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::_Vector_base(allocator<void *> const &); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::_Vector_base(unsigned int, allocator<void *> const &); }
namespace _STL { template <> vector<void *, allocator<void *> >::vector(allocator<void *> const &); }
namespace _STL { template <> vector<void *, allocator<void *> >::vector(unsigned int, void *const &, allocator<void *> const &); }
namespace _STL { template <> __declspec(dllimport) __forceinline _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy() {} }
namespace _STL { template <> __declspec(dllimport) __forceinline _Vector_base<void *, allocator<void *> >::~_Vector_base() { if (_M_start != 0) _M_end_of_storage.deallocate(_M_start, _M_end_of_storage._M_data - _M_start); } }
namespace _STL { template <> inline vector<void *, allocator<void *> >::~vector() { _Destroy(_M_start, _M_finish); } }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_clear(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_fill_insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_insert_overflow(void **, void *const &, __true_type const &, unsigned int, bool); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_set(void **, void **, void **); }
namespace _STL { template <> void ** allocator<void *>::allocate(unsigned int, void const *) const; }
namespace _STL { template <> unsigned int vector<void *, allocator<void *> >::capacity() const; }
namespace _STL { template <> allocator<void *> vector<void *, allocator<void *> >::get_allocator() const; }
namespace _STL { template <> void vector<void *, allocator<void *> >::insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::reserve(unsigned int); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?clear@?$_List_base@UBfmePod264@@V?$allocator@UBfmePod264@@@_STL@@@_STL@@QAEXXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod264;
namespace _STL { template <> void _List_base<BfmePod264,allocator<BfmePod264> >::clear(); }
// Suppress this TU's non-retail copy of ?insert@?$list@UBfmePod264@@V?$allocator@UBfmePod264@@@_STL@@@_STL@@QAE?AU?$_List_iterator:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod264;
namespace _STL { template <> _List_iterator<BfmePod264,_Nonconst_traits<BfmePod264> > list<BfmePod264,allocator<BfmePod264> >::insert(_List_iterator<BfmePod264,_Nonconst_traits<BfmePod264> >,BfmePod264 const &); }
// Keep bucket access inline so the key-only search reproduces retail's
// complete 47-byte body without emitting a competing public accessor.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *const &vector<void *>::operator[](size_t n) const { return _M_start[n]; }
}
// Suppress this TU's non-retail const-begin copy (row 47 family2-LK3): the
// /Od retail copy in stlport_vector_voidptr.cpp serves the link instead.
namespace _STL {
template <> vector<void *>::const_iterator _STL::vector<void *>::begin() const;
}

// vector<void*> size/operator[] otherwise instantiate per-TU COMDATs (one
// byte shape per TU flags); explicit dllimport+forceinline specializations
// take those calls inline so this TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
size_t vector<void*>::size() const
{ return size_t(this->_M_finish - this->_M_start); }
template <> __declspec(dllimport) __forceinline
void *&vector<void*>::operator[](size_t __n)
{ return *(_M_start + __n); }
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
inline bool operator==(const BfmePod264 &x, const BfmePod264 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod264 &x, const BfmePod264 &y) { return x.a[0] < y.a[0]; }

// operator[] is rowed in stlport_hash_map_int_list_pod264_subscript.cpp;
// this unit's copy is not retail's, so only declare it.
namespace _STL { template <> list<BfmePod264> &hash_map<int, list<BfmePod264>, hash<int>, equal_to<int>, allocator<pair<const int, list<BfmePod264> > > >::operator[](const int &); }
typedef _STL::pair<const int, _STL::list<BfmePod264> > Pod264Pair;
typedef _STL::hashtable<Pod264Pair, int, _STL::hash<int>, _STL::_Select1st<Pod264Pair>, _STL::equal_to<int>, _STL::allocator<Pod264Pair> > Pod264Table;

namespace _STL {
// Relink each int key through stable references to the source and destination buckets.
template <> inline void Pod264Table::resize(size_type hint)
{
    const size_type old_size = _M_buckets.size();
    if (hint > old_size) {
        const size_type new_size = _M_next_size(hint);
        if (new_size > old_size) {
            _BucketVector temporary(new_size, (void *)0, _M_buckets.get_allocator());
            for (size_type bucket = 0; bucket < old_size; ++bucket) {
                _Node *first = (_Node *)_M_buckets[bucket];
                while (first) {
                    void *&source = _M_buckets[bucket];
                    size_type destination = (size_type)first->_M_val.first % new_size;
                    source = first->_M_next;
                    void *&slot = temporary[destination];
                    first->_M_next = (_Node *)slot;
                    slot = first;
                    first = (_Node *)_M_buckets[bucket];
                }
            }
            _M_buckets.swap(temporary);
        }
    }
}
}

template class _STL::hash_map<int, _STL::list<BfmePod264>, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<_STL::pair<const int, _STL::list<BfmePod264> > > >;

// The rows operator[] had instantiated here stay as explicit instantiations.
template Pod264Table::reference Pod264Table::_M_insert(const Pod264Table::value_type &);
template _STL::pair<const int, _STL::list<BfmePod264> >::pair(const int &, const _STL::list<BfmePod264> &);
template _STL::list<BfmePod264>::list(const _STL::allocator<BfmePod264> &);
