// cl: /O2 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable
// stlport
//
// Dedicated TU for hashtable<int,int>::resize. The shared hash_map_int
// unit is built with /EHsc and emits an EH prologue retail does not have.

#include <hash_map>
// Preserve inline allocation while binding outlined calls to the shared provider.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void **_STLP_alloc_proxy<void **, void *, allocator<void *> >::allocate(size_t n)
{ return __stl_alloc_rebind(static_cast<allocator<void *> &>(*this), (void **)0).allocate(n, 0); }
}
// The hash table reads its bucket vector's size() and begin() const inline; their
// unreferenced copies here differed from retail's. Declared imported and
// force-inlined, they are not emitted.
namespace _STL {
template <> __declspec(dllimport) __forceinline
size_t vector<void *>::size() const { return size_t(this->_M_finish - this->_M_start); }
template <> __declspec(dllimport) __forceinline
vector<void *>::const_iterator vector<void *>::begin() const { return this->_M_start; }
template <> __declspec(dllimport) __forceinline void *const &vector<void *>::operator[](size_t __n) const { return *(begin() + __n); }
}
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void * & vector<void *,allocator<void *> >::operator[](unsigned int n) { return *(this->_M_start + n); } }
// bfme link decl-only begin
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::_Vector_base(allocator<void *> const &); }
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_clear(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_fill_insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_insert_overflow(void **, void *const &, __true_type const &, unsigned int, bool); }
namespace _STL { template <> unsigned int vector<void *, allocator<void *> >::capacity() const; }
namespace _STL { template <> void ** vector<void *, allocator<void *> >::end(); }
namespace _STL { template <> allocator<void *> vector<void *, allocator<void *> >::get_allocator() const; }
namespace _STL { template <> void vector<void *, allocator<void *> >::insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::reserve(unsigned int); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ??$?8U?$pair@$$CBHH@_STL@@U?$_Nonconst_traits@U?$pair@$$CBHH@_STL@@@1@U21@HU?$hash@H@1@U?$:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> bool operator==<pair<int const ,int>,_Nonconst_traits<pair<int const ,int> >,_Nonconst_traits<pair<int const ,int> >,int,hash<int>,_Select1st<pair<int const ,int> >,equal_to<int>,allocator<pair<int const ,int> > >(_Ht_iterator<pair<int const ,int>,_Nonconst_traits<pair<int const ,int> >,int,hash<int>,_Select1st<pair<int const ,int> >,equal_to<int>,allocator<pair<int const ,int> > > const &,_Ht_iterator<pair<int const ,int>,_Nonconst_traits<pair<int const ,int> >,int,hash<int>,_Select1st<pair<int const ,int> >,equal_to<int>,allocator<pair<int const ,int> > > const &); }
// Suppress this TU's non-retail copy of ??$?8$$CBHH@_STL@@YA_NABU?$pair@$$CBHH@0@0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> bool operator==<int const ,int>(pair<int const ,int> const &,pair<int const ,int> const &); }
// Suppress this TU's non-retail copy of ??$advance@PBIH@_STL@@YAXAAPBIH@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void advance<unsigned int const *,int>(unsigned int const * &,int); }
// Suppress this TU's non-retail copy of ??0?$hash_map@HHU?$hash@H@_STL@@U?$equal_to@H@2@V?$allocator@U?$pair@$$CBHH@_STL@@@2@@_STL:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> hash_map<int,int,hash<int>,equal_to<int>,allocator<pair<int const ,int> > >::hash_map(); }
// Suppress this TU's non-retail copy of ??$__advance@PBIH@_STL@@YAXAAPBIHABUrandom_access_iterator_tag@0@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void __advance<unsigned int const *,int>(unsigned int const * &,int,random_access_iterator_tag const &); }
// Suppress this TU's non-retail copy of ??0?$hashtable@U?$pair@$$CBHH@_STL@@HU?$hash@H@2@U?$_Select1st@U?$pair@$$CBHH@_STL@@@2@U?$:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> hashtable<pair<const int, int>, int, hash<int>, _Select1st<pair<const int, int> >, equal_to<int>, allocator<pair<const int, int> > >::hashtable(size_t, const hash<int> &, const equal_to<int> &, const allocator<pair<const int, int> > &); }
// Suppress this TU's non-retail copy of ?_M_initialize_buckets@?$hashtable@U?$pair@$$CBHH@_STL@@HU?$hash@H@2@U?$_Select1st@U?$pair:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> void hashtable<pair<const int, int>, int, hash<int>, _Select1st<pair<const int, int> >, equal_to<int>, allocator<pair<const int, int> > >::_M_initialize_buckets(size_t); }

template void _STL::hashtable<_STL::pair<const int, int>, int,
    _STL::hash<int>, _STL::_Select1st<_STL::pair<const int, int> >,
    _STL::equal_to<int>, _STL::allocator<_STL::pair<const int, int> > >::resize(size_t);
