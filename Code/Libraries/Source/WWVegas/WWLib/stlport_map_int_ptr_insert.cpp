// cl: /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// retail 0x00534827 134B: _Rb_tree<unsigned, pair<const unsigned, Rva00534743Record> >::insert_unique(const
// value_type&) without hint. Calls rowed _M_decrement 0x000242C0 and the rowed _M_insert 0x0053479F, declared
// only here. Donor vendor/stlport/stl/_tree.c
// with _BFME_RETAIL_TREE_INSERT_LAYOUT for the leftmost fast path _M_insert(__y __y __v).
// Flags copy the sibling map<unsigned void*> TU stlport_map_int_ptr_lower.cpp plus the retail layout macro.
#include <map>
// The outer pathfinder map's value: retail's _M_create_node 0x00534743 allocates 0x20-byte nodes, a 16-byte
// pair<const unsigned int, Rva00534743Record> (tools/retail_identity.py MAP_UINT_RECORD_INSERT).
struct Rva00534743Record { int word0; int word1; int word2; };

// Inline unsigned comparison belongs to the caller; the retail owner supplies
// the external less<unsigned> body without a competing local COMDAT.
namespace _STL {
template<> __declspec(dllimport) __forceinline
bool less<unsigned int>::operator()(const unsigned int& a, const unsigned int& b) const
{ return a < b; }
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

namespace _STL { template <> _Rb_tree_iterator<pair<unsigned int const, Rva00534743Record>, _Nonconst_traits<pair<unsigned int const, Rva00534743Record> > > _Rb_tree<unsigned int, pair<unsigned int const, Rva00534743Record>, _Select1st<pair<unsigned int const, Rva00534743Record> >, less<unsigned int>, allocator<pair<unsigned int const, Rva00534743Record> > >::_M_insert(_Rb_tree_node_base *, _Rb_tree_node_base *, pair<unsigned int const, Rva00534743Record> const &, _Rb_tree_node_base *); }
typedef _STL::_Rb_tree<unsigned, _STL::pair<const unsigned, Rva00534743Record>, _STL::_Select1st<_STL::pair<const unsigned, Rva00534743Record> >, _STL::less<unsigned>, _STL::allocator<_STL::pair<const unsigned, Rva00534743Record> > > MapIntPtrTree;

template _STL::pair<MapIntPtrTree::iterator, bool> MapIntPtrTree::insert_unique(const MapIntPtrTree::value_type &);
