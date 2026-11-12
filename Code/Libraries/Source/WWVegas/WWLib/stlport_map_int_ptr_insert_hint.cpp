// cl: /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /D_CRTIMP=
// stlport
//
// retail 0x00534A0D 29B: map<unsigned int, Rva00534743Record>::insert(iterator position, const value_type&)
// hint-forwarding wrapper over the rowed _Rb_tree hint insert_unique at 0x005348E7.
// Called once by the unclaimed operator[]-style worker at 0x00534A2A via 0x00534A7B.
// Flags copy the sibling map<unsigned void*> TU stlport_map_int_ptr_lower.cpp.
#include <map>
// The outer pathfinder map's value: retail's _M_create_node 0x00534743 allocates 0x20-byte nodes, a 16-byte
// pair<const unsigned int, Rva00534743Record> (tools/retail_identity.py MAP_UINT_RECORD_INSERT).
struct Rva00534743Record { int word0; int word1; int word2; };
// bfme link decl-only begin
namespace _STL { template <> _Rb_tree_iterator<pair<unsigned int const, Rva00534743Record>, _Nonconst_traits<pair<unsigned int const, Rva00534743Record> > > _Rb_tree<unsigned int, pair<unsigned int const, Rva00534743Record>, _Select1st<pair<unsigned int const, Rva00534743Record> >, less<unsigned int>, allocator<pair<unsigned int const, Rva00534743Record> > >::_M_insert(_Rb_tree_node_base *, _Rb_tree_node_base *, pair<unsigned int const, Rva00534743Record> const &, _Rb_tree_node_base *); }
namespace _STL { template <> _Rb_tree_iterator<pair<unsigned int const, Rva00534743Record>, _Nonconst_traits<pair<unsigned int const, Rva00534743Record> > > _Rb_tree<unsigned int, pair<unsigned int const, Rva00534743Record>, _Select1st<pair<unsigned int const, Rva00534743Record> >, less<unsigned int>, allocator<pair<unsigned int const, Rva00534743Record> > >::insert_unique(_Rb_tree_iterator<pair<unsigned int const, Rva00534743Record>, _Nonconst_traits<pair<unsigned int const, Rva00534743Record> > >, pair<unsigned int const, Rva00534743Record> const &); }
namespace _STL { template <> pair<_Rb_tree_iterator<pair<unsigned int const, Rva00534743Record>, _Nonconst_traits<pair<unsigned int const, Rva00534743Record> > >, bool> _Rb_tree<unsigned int, pair<unsigned int const, Rva00534743Record>, _Select1st<pair<unsigned int const, Rva00534743Record> >, less<unsigned int>, allocator<pair<unsigned int const, Rva00534743Record> > >::insert_unique(pair<unsigned int const, Rva00534743Record> const &); }
// bfme link decl-only end

// map/set<unsigned> internals otherwise instantiate the less<unsigned>::operator()
// COMDAT (one byte shape per TU flags); a declaration-only specialization
// stops this TU emitting its copy so callers bind the kept copy.
// Plain (non-dllimport) form: no __imp_ reference is emitted.
namespace _STL {
template <> bool less<unsigned>::operator()(const unsigned &a, const unsigned &b) const;
}

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

typedef _STL::map<unsigned, Rva00534743Record, _STL::less<unsigned>, _STL::allocator<_STL::pair<const unsigned, Rva00534743Record> > > MapIntPtr;

template MapIntPtr::iterator MapIntPtr::insert(MapIntPtr::iterator, const MapIntPtr::value_type &);
