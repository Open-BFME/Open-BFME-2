// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Pristine STLport 4.5.3 hash_map/hash_set members for placeholder values,
// each placed by a single masked whole-.text hit. BfmePodN stands for the real
// N-byte mapped type and int for any 4-byte key/value that folds with it; the
// placed bodies' node sizes and copy lengths fix those sizes. No retail caller
// is claimed.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#define _STLP_BFME_LOWER_BOUND_EXTERN  // call retail's one __lower_bound<const size_t*> (vendor/stlport/stl/_hashtable.c)
#include <stl/_algobase.h>

// vector<int> fill/insert otherwise instantiates the _Construct<int,int>
// COMDAT (one byte shape per TU flags); a file-static overload takes those
// calls instead so this TU emits no external copy.
#include <new>
namespace _STL {
static inline void _Construct(int *__p, const int &__val)
{ new (__p) int(__val); }
}
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <hash_map>
#include <hash_set>
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline unsigned int vector<void *,allocator<void *> >::size()const  { return (unsigned int)(this->_M_finish - this->_M_start); } }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void * const * vector<void *,allocator<void *> >::begin()const  { return this->_M_start; } }

// map/set<unsigned> internals otherwise instantiate the less<unsigned>::operator()
// COMDAT (one byte shape per TU flags); a declaration-only specialization
// stops this TU emitting its copy so callers bind the kept copy.
// Plain (non-dllimport) form: no __imp_ reference is emitted.
namespace _STL {
template <> bool less<unsigned>::operator()(const unsigned &a, const unsigned &b) const;
}
struct BfmePod16 { int a[4]; };
inline bool operator==(const BfmePod16 &x, const BfmePod16 &y) { return x.a[0] == y.a[0]; }
struct BfmePod20 { int a[5]; };
inline bool operator==(const BfmePod20 &x, const BfmePod20 &y) { return x.a[0] == y.a[0]; }
struct BfmePod24 { int a[6]; };
inline bool operator==(const BfmePod24 &x, const BfmePod24 &y) { return x.a[0] == y.a[0]; }
struct BfmePod32 { int a[8]; };
inline bool operator==(const BfmePod32 &x, const BfmePod32 &y) { return x.a[0] == y.a[0]; }
struct BfmePod48 { int a[12]; };
inline bool operator==(const BfmePod48 &x, const BfmePod48 &y) { return x.a[0] == y.a[0]; }
struct BfmePod44 { int a[11]; };
inline bool operator==(const BfmePod44 &x, const BfmePod44 &y) { return x.a[0] == y.a[0]; }
struct BfmePod52 { int a[13]; };
inline bool operator==(const BfmePod52 &x, const BfmePod52 &y) { return x.a[0] == y.a[0]; }
struct BfmePod72 { int a[18]; };
inline bool operator==(const BfmePod72 &x, const BfmePod72 &y) { return x.a[0] == y.a[0]; }
// bfme link decl-only begin
// Retail's pair<const int,BfmePod72> ctor (0x002E00AF, StlportPairConstructFamily.cpp) copies through a
// non-trivial BfmePod72 copy ctor: a different real type. This unit's unreferenced copy loop is not it.
namespace _STL { template <> pair<const int, BfmePod72>::pair(const int &, const BfmePod72 &); }
// Native pair copying uses the non-trivial provider rowed in StlportPairConstructFamily.cpp.
namespace _STL {
template <> pair<const int, BfmePod72>::pair(const pair<const int, BfmePod72> &);
template <> void _Construct<pair<const int, BfmePod72>, pair<const int, BfmePod72> >(pair<const int, BfmePod72> *, const pair<const int, BfmePod72> &);
}
// Retail's pair<const int,BfmePod20> placement copy (0x004192A4,
// StlportPairConstructPod20.cpp) constructs through the rowed Rva0041922E copy
// ctor; this unit's trivial copies of it are not retail's.
namespace _STL {
template <> pair<const int, BfmePod20>::pair(const pair<const int, BfmePod20> &);
template <> void _Construct<pair<const int, BfmePod20>, pair<const int, BfmePod20> >(pair<const int, BfmePod20> *, const pair<const int, BfmePod20> &);
}
namespace _STL {
// As in Armor.cpp, this allocator is stateless; exchanging the stored pointer
// avoids instantiating the allocator proxy's unrelated copy constructor.
template <> inline void swap(_STLP_alloc_proxy<void **, void *, allocator<void *> > &left,
                            _STLP_alloc_proxy<void **, void *, allocator<void *> > &right)
{
    swap(left._M_data, right._M_data);
}
}
namespace _STL { template <> __declspec(dllimport) __forceinline void *& vector<void *, allocator<void *> >::operator[](unsigned int n) { return *(this->_M_start + n); } }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_clear(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_fill_insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_insert_overflow(void **, void *const &, __true_type const &, unsigned int, bool); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_set(void **, void **, void **); }
namespace _STL { template <> void ** vector<void *, allocator<void *> >::begin(); }
namespace _STL { template <> unsigned int vector<void *, allocator<void *> >::capacity() const; }
namespace _STL { template <> void ** vector<void *, allocator<void *> >::end(); }
namespace _STL { template <> allocator<void *> vector<void *, allocator<void *> >::get_allocator() const; }
namespace _STL { template <> void vector<void *, allocator<void *> >::insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::reserve(unsigned int); }
// bfme link decl-only end
template class _STL::hash_set<int, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<int> >;
template class _STL::hash_map<int, BfmePod16, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<_STL::pair<const int, BfmePod16> > >;
template class _STL::hash_map<int, BfmePod20, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<_STL::pair<const int, BfmePod20> > >;
template class _STL::hash_map<int, BfmePod24, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<_STL::pair<const int, BfmePod24> > >;
template class _STL::hash_map<int, BfmePod48, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<_STL::pair<const int, BfmePod48> > >;
template class _STL::hash_map<int, BfmePod44, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<_STL::pair<const int, BfmePod44> > >;
template class _STL::hash_map<int, BfmePod52, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<_STL::pair<const int, BfmePod52> > >;
// Native4198C6 is now the typed string-key node creator in Rva004197E8Pair.cpp.
template class _STL::hash_map<int, BfmePod72, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<_STL::pair<const int, BfmePod72> > >;

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?eraseSlot@ObjectLookupMap@@QAEXPAH@Z=?erase@?$hashtable@HHU?$hash@H@_STL@@U?$_Identity@H@2@U?$equal_to@H@2@V?$allocator@H@2@@_STL@@QAEIABH@Z")
