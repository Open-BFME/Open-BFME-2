// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// cl: /Og /Os /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#define _STLP_BFME_LOWER_BOUND_EXTERN  // call retail's one __lower_bound<const size_t*> (vendor/stlport/stl/_hashtable.c)
#include <hash_map>
#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> void swap<_STLP_alloc_proxy<void **, void *, allocator<void *> > >(_STLP_alloc_proxy<void **, void *, allocator<void *> > &, _STLP_alloc_proxy<void **, void *, allocator<void *> > &); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::_Vector_base(allocator<void *> const &); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::_Vector_base(unsigned int, allocator<void *> const &); }
namespace _STL { template <> vector<void *, allocator<void *> >::vector(allocator<void *> const &); }
namespace _STL { template <> vector<void *, allocator<void *> >::vector(unsigned int, void *const &, allocator<void *> const &); }
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::~_Vector_base(); }
namespace _STL { template <> vector<void *, allocator<void *> >::~vector(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_clear(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_fill_insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_insert_overflow(void **, void *const &, __true_type const &, unsigned int, bool); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_set(void **, void **, void **); }
namespace _STL { template <> void ** allocator<void *>::allocate(unsigned int, void const *) const; }
namespace _STL { template <> unsigned int vector<void *, allocator<void *> >::capacity() const; }
namespace _STL { template <> allocator<void *> vector<void *, allocator<void *> >::get_allocator() const; }
namespace _STL { template <> void vector<void *, allocator<void *> >::reserve(unsigned int); }
namespace _STL { template <> void vector<void *, allocator<void *> >::swap(vector<void *, allocator<void *> > &); }
namespace _STL { template <> allocator<void *>::~allocator(); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ??0?$hash_map@HHU?$hash@H@_STL@@U?$equal_to@H@2@V?$allocator@U?$pair@$$CBHH@_STL@@@2@@_STL:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> hash_map<int,int,hash<int>,equal_to<int>,allocator<pair<int const ,int> > >::hash_map(); }
// Suppress this TU's non-retail copy of ??1?$hashtable@U?$pair@$$CBHH@_STL@@HU?$hash@H@2@U?$_Select1st@U?$pair@$$CBHH@_STL@@@2@U?$:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> hashtable<pair<const int, int>, int, hash<int>, _Select1st<pair<const int, int> >, equal_to<int>, allocator<pair<const int, int> > >::~hashtable(); }
// Suppress this TU's non-retail copy of ??0?$hashtable@U?$pair@$$CBHH@_STL@@HU?$hash@H@2@U?$_Select1st@U?$pair@$$CBHH@_STL@@@2@U?$:
// the kept copy serves the link. Plain declaration-only form (no __imp_).


namespace _STL { template <> hashtable<pair<const int, int>, int, hash<int>, _Select1st<pair<const int, int> >, equal_to<int>, allocator<pair<const int, int> > >::hashtable(size_t, const hash<int> &, const equal_to<int> &, const allocator<pair<const int, int> > &); }
// Suppress this TU's non-retail copy of ?_M_initialize_buckets@?$hashtable@U?$pair@$$CBHH@_STL@@HU?$hash@H@2@U?$_Select1st@U?$pair:
// the kept copy serves the link. Plain declaration-only form (no __imp_).


namespace _STL { template <> void hashtable<pair<const int, int>, int, hash<int>, _Select1st<pair<const int, int> >, equal_to<int>, allocator<pair<const int, int> > >::_M_initialize_buckets(size_t); }
// Suppress this TU's non-retail copy of ?clear@?$hashtable@U?$pair@$$CBHH@_STL@@HU?$hash@H@2@U?$_Select1st@U?$pair@$$CBHH@_STL@@@2:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> void hashtable<pair<const int, int>, int, hash<int>, _Select1st<pair<const int, int> >, equal_to<int>, allocator<pair<const int, int> > >::clear(); }
// Suppress this TU's non-retail copy of ??A?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@QBEABQAXI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void *const &vector<void *>::operator[](size_t) const; }
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

// map/set<unsigned> internals otherwise instantiate the less<unsigned>::operator()
// COMDAT (one byte shape per TU flags); a declaration-only specialization
// stops this TU emitting its copy so callers bind the kept copy.
// Plain (non-dllimport) form: no __imp_ reference is emitted.
namespace _STL {
template <> bool less<unsigned>::operator()(const unsigned &a, const unsigned &b) const;
}
// Suppress this TU's non-retail vector<void*> size copy (family2-LK3 row 17):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> size_t vector<void*>::size() const;
template <> void **vector<void*>::begin();
// end() and the fill insert(pos, n, x) are taken inline, as retail's
// hashtable::_M_initialize_buckets does (59 bytes: it reads _M_finish and
// calls the rowed _M_fill_insert); dllimport + forceinline emits no copy.
template <> __declspec(dllimport) __forceinline void **vector<void*>::end()
{ return _M_finish; }
template <> __declspec(dllimport) __forceinline void vector<void*>::insert(void **pos, size_t n, void *const &x)
{ _M_fill_insert(pos, n, x); }
// /Ob1 would leave __less<unsigned> out of line in _M_next_size; retail
// expands it (48 bytes). Inline only, no external copy.
template <> __declspec(dllimport) __forceinline less<unsigned int> __less(unsigned int *)
{ return less<unsigned int>(); }
}

// The element is Rva004E007AElement: this constructor's only call (0x004E02CD) goes to the
// rowed hashtable<pair<const int, Rva004E007AElement> > constructor at 0x004E007A
// (StlSweepW5Rva004E007A.cpp), which declares the same element view. Only the rowed
// hash_map constructor is instantiated (the whole hash_map would emit members that
// reference the element's undefined ctors and ==).
struct Rva004E007AElement {Rva004E007AElement();Rva004E007AElement(const Rva004E007AElement&);Rva004E007AElement&operator=(const Rva004E007AElement&);~Rva004E007AElement(){}char bytes[8]; bool operator==(const Rva004E007AElement&)const;};
typedef _STL::pair<const int, Rva004E007AElement> Rva004E007AElementPair;
// The bucket-size helper is declared only: the kept copy serves its call.
namespace _STL { template <> unsigned int hashtable<Rva004E007AElementPair, int, hash<int>, _Select1st<Rva004E007AElementPair>, equal_to<int>, allocator<Rva004E007AElementPair> >::_M_next_size(unsigned int) const; }
template _STL::hash_map<int, Rva004E007AElement, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<Rva004E007AElementPair> >::hash_map();
// AIStatCollector::Register increments the mapped four-byte count at node+8;
// its constructor's empty count-map call uses this same retail body. Keep
// the original opaque owner while proving the actual int-count instantiation
// against its whole body and all callee relocations through pin_admission.
template _STL::hash_map<int,int>::hash_map();
