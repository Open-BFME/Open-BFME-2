// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ThingTemplate float-map store (shared float helper). The map access uses
// the rowed integer-float subscript directly.

#include <map>
// bfme link decl-only begin
namespace _STL { template <> float & map<int, float, less<int>, allocator<pair<int const, float> > >::operator[](int const &); }
namespace _STL { template <> _Rb_tree_iterator<pair<int const, float>, _Nonconst_traits<pair<int const, float> > > _Rb_tree<int, pair<int const, float>, _Select1st<pair<int const, float> >, less<int>, allocator<pair<int const, float> > >::insert_unique(_Rb_tree_iterator<pair<int const, float>, _Nonconst_traits<pair<int const, float> > >, pair<int const, float> const &); }
namespace _STL { template <> pair<_Rb_tree_iterator<pair<int const, float>, _Nonconst_traits<pair<int const, float> > >, bool> _Rb_tree<int, pair<int const, float>, _Select1st<pair<int const, float> >, less<int>, allocator<pair<int const, float> > >::insert_unique(pair<int const, float> const &); }
// bfme link decl-only end

// __malloc_alloc<0> allocate/deallocate otherwise instantiate per-TU
// COMDATs (one byte shape per TU malloc/free wiring); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__malloc_alloc<0>::allocate(size_t __n)
{ void *__r = malloc(__n); if (!__r) __r = _S_oom_malloc(__n); return __r; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

#include "../../../Include/Common/ThingTemplate.h"

void ThingTemplate::Rva0033D396StoreFloat(int key, float value)
{
	(*reinterpret_cast<_STL::map<int, float> *>(m3A0))[key] = value;
}
