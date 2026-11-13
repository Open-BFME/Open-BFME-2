// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport

#include <stl/_alloc.h>
namespace _STL { template <> void __malloc_alloc<0>::deallocate(void *, size_t); }
#include <map>
// Bind map<int, int> members to the retail copies rowed in stlport_map_int_int*.cpp
// (or, for the unrowed default ctors, to the kept copy) instead of emitting this unit's own.
namespace _STL {
template <> map<int, int, less<int>, allocator<pair<int const, int> > >::map();
}
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> bool map<int,int,less<int>,allocator<pair<int const ,int> > >::value_compare::operator()(pair<int const ,int> const &,pair<int const ,int> const &)const ; }
namespace _STL { template<> pair<map<int,int>::iterator,bool> map<int,int>::insert(const value_type&); }
// bfme link decl-only begin
namespace _STL { template <> _Rb_tree_iterator<pair<int const, int>, _Const_traits<pair<int const, int> > > _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::upper_bound(int const &) const; }
namespace _STL { template <> _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::_Rb_tree(_Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > > const &); }
namespace _STL { template <> map<int, int, less<int>, allocator<pair<int const, int> > >::map(map<int, int, less<int>, allocator<pair<int const, int> > > const &); }
namespace _STL { template <> _Rb_tree_node<pair<int const, int> > * _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::_M_copy(_Rb_tree_node<pair<int const, int> > *, _Rb_tree_node<pair<int const, int> > *); }
namespace _STL { template <> void map<int, int, less<int>, allocator<pair<int const, int> > >::clear(); }
namespace _STL { template <> unsigned int map<int, int, less<int>, allocator<pair<int const, int> > >::count(int const &) const; }
namespace _STL { template <> pair<_Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >, _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > > > _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::equal_range(int const &); }
namespace _STL { template <> pair<_Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >, _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > > > map<int, int, less<int>, allocator<pair<int const, int> > >::equal_range(int const &); }
namespace _STL { template <> pair<_Rb_tree_iterator<pair<int const, int>, _Const_traits<pair<int const, int> > >, _Rb_tree_iterator<pair<int const, int>, _Const_traits<pair<int const, int> > > > map<int, int, less<int>, allocator<pair<int const, int> > >::equal_range(int const &) const; }
namespace _STL { template <> _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > > map<int, int, less<int>, allocator<pair<int const, int> > >::insert(_Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >, pair<int const, int> const &); }
namespace _STL { template <> void _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::swap(_Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > > &); }
namespace _STL { template <> _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > > _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::upper_bound(int const &); }
namespace _STL { template <> _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > > map<int, int, less<int>, allocator<pair<int const, int> > >::upper_bound(int const &); }
namespace _STL { template <> _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::~_Rb_tree(); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ??0?$_Rb_tree_base@U?$pair@$$CBHH@_STL@@V?$allocator@U?$pair@$$CBHH@_STL@@@2@@_STL@@QAE@AB:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> _Rb_tree_base<pair<const int, int>, allocator<pair<const int, int> > >::_Rb_tree_base(const allocator<pair<const int, int> > &); }

// Preserve retail's inlined buffer release while using the canonical public allocator.
namespace _STL {
#pragma optimize("gsy", on)
// The explicit map instantiation below emits this copy constructor out of line
// although nothing here calls it; under this unit's /O2 it would take edx
// (retail 0x6CFE10 form) and differ from the /O1 ecx form every other tree
// copy carries (retail 0x27EA56 form). The size profile keeps them identical.
template <> inline _Rb_tree_iterator<pair<const int, int>, _Nonconst_traits<pair<const int, int> > >::_Rb_tree_iterator(const _Rb_tree_iterator<pair<const int, int>, _Nonconst_traits<pair<const int, int> > > &__it) { _M_node = __it._M_node; }
template <> __declspec(dllimport) __forceinline void allocator<_Rb_tree_node<pair<const int, int> > >::deallocate(_Rb_tree_node<pair<const int, int> > *p, size_t) const { if (p != 0) free(p); }
#pragma optimize("", on)
// Every node allocation here is inlined; imported force-inline stock bodies keep this
// unit from emitting its own (first in link order, non-majority) allocator copies.
template <> __declspec(dllimport) __forceinline _Rb_tree_node<pair<const int, int> > *allocator<_Rb_tree_node<pair<const int, int> > >::allocate(size_t __n, const void *) const
{ return __n != 0 ? reinterpret_cast<_Rb_tree_node<pair<const int, int> > *>(__sgi_alloc::allocate(__n * sizeof(_Rb_tree_node<pair<const int, int> >))) : 0; }
template <> __declspec(dllimport) __forceinline _Rb_tree_node<pair<const int, int> > *_STLP_alloc_proxy<_Rb_tree_node<pair<const int, int> > *, _Rb_tree_node<pair<const int, int> >, allocator<_Rb_tree_node<pair<const int, int> > > >::allocate(size_t __n)
{ return __stl_alloc_rebind(static_cast<allocator<_Rb_tree_node<pair<const int, int> > >&>(*this), (_Rb_tree_node<pair<const int, int> > *)0).allocate(__n, 0); }
template <> __declspec(dllimport) __forceinline void _STLP_alloc_proxy<_Rb_tree_node<pair<const int, int> > *, _Rb_tree_node<pair<const int, int> >, allocator<_Rb_tree_node<pair<const int, int> > > >::deallocate(_Rb_tree_node<pair<const int, int> > *__p, size_t __n)
{ __stl_alloc_rebind(static_cast<allocator<_Rb_tree_node<pair<const int, int> > >&>(*this), (_Rb_tree_node<pair<const int, int> > *)0).deallocate(__p, __n); }
}

class GameWindow;
typedef _STL::_Rb_tree<GameWindow *, GameWindow *, _STL::_Identity<GameWindow *>, _STL::less<GameWindow *>, _STL::allocator<GameWindow *> > RetailRangeTree;
typedef _STL::_Rb_tree<int, _STL::pair<const int, int>, _STL::_Select1st<_STL::pair<const int, int> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > > IntMapTree;

// Use the separately compiled size-optimized subtree erase at retail 0x692F5.
// Suppress this speed-profile copy so callers select the verified provider.
namespace _STL {
template <> void IntMapTree::_M_erase(_Rb_tree_node<pair<const int, int> > *);
// Native clone owner is the verified 30B body at 0x0053444F.
// This speed-profile unit emits a different allocation/cleanup shape.
template <> IntMapTree::_Link_type IntMapTree::_M_clone_node(IntMapTree::_Link_type);
// This unit inlines the tree walk into map::lower_bound; retail calls the
// worker (rows 59 family2-LK3). Suppress both overloads so the link keeps
// the retail copy another unit provides.
template <> _STL::map<int, int, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > >::iterator _STL::map<int, int, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > >::lower_bound(const int &);
template <> _STL::map<int, int, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > >::const_iterator _STL::map<int, int, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > >::lower_bound(const int &) const;
// Same for map::find (row 38): suppress so the link keeps the retail copy.
template <> _STL::map<int, int, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > >::iterator _STL::map<int, int, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > >::find(const int &);
template <> _STL::map<int, int, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > >::const_iterator _STL::map<int, int, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > >::find(const int &) const;
// Same for operator[] (row 39 S): suppress so the link keeps the retail copy.
template <> int &_STL::map<int, int, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > >::operator[](const int &);
// Member-template suppression attempt (row 37 _Rb_tree::find).
template <> template <> IntMapTree::iterator IntMapTree::find<int>(const int &);
// Plain-member suppression for _Rb_tree::lower_bound (row 40).
template <> IntMapTree::iterator IntMapTree::lower_bound(const int &);
template <> IntMapTree::const_iterator IntMapTree::lower_bound(const int &) const;
}

// The historical int-map spelling of erase at 0x61F8A0 reaches the existing
// pointer-tree range owner at 0x61F840. Preserve that call explicitly: its
// unsigned pointer comparison is not the signed int-map range at 0x2F1C89.
// The int-map row name is a legacy structural view, not an application identity.
template <> inline IntMapTree::size_type IntMapTree::erase(const int &key)
{
	_STL::pair<RetailRangeTree::iterator, RetailRangeTree::iterator> range =
		reinterpret_cast<RetailRangeTree *>(this)->equal_range(reinterpret_cast<GameWindow *const &>(key));
	size_type count = _STL::distance(reinterpret_cast<iterator &>(range.first), reinterpret_cast<iterator &>(range.second));
	erase(reinterpret_cast<iterator &>(range.first), reinterpret_cast<iterator &>(range.second));
	return count;
}

// The size-profile providers own retail clear (0x6AA1C), tree assignment
// (0x2CF742), and map assignment (0x2CF9CA). Do not emit speed-profile copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline void IntMapTree::clear()
{
    if (_M_node_count != 0) {
        _M_erase(_M_root());
        _M_leftmost() = _M_header._M_data;
        _M_root() = 0;
        _M_rightmost() = _M_header._M_data;
        _M_node_count = 0;
    }
}
template <> IntMapTree &IntMapTree::operator=(const IntMapTree &);
template <> map<int, int> &map<int, int>::operator=(const map<int, int> &);
}

template class _STL::map<int, int, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > >;

// Unsigned four-byte key view used by the asset-manager set operations at
// 0x61F910/0x61FAA0. The range release is the complete 144-byte ICF twin of
// this unit's int-map owner at 0x61F7B0, including its allocation release and
// 0x692F5 subtree callee. No original key or application class name is claimed.
extern void __cdecl Rva00030830FreeAllocation(void *);
#include "../../assetmanager/Rva0061F910Key.h"
inline bool operator<(const Rva0061F910Key &left, const Rva0061F910Key &right)
{
    return left.a < right.a;
}
typedef _STL::_Rb_tree<Rva0061F910Key, Rva0061F910Key,
    _STL::_Identity<Rva0061F910Key>, _STL::less<Rva0061F910Key>,
    _STL::allocator<Rva0061F910Key> > NativeTree;
namespace _STL {
template <> __forceinline void allocator<_Rb_tree_node<Rva0061F910Key> >::deallocate(
    _Rb_tree_node<Rva0061F910Key> *p, size_t) const
{
    if (p != 0) Rva00030830FreeAllocation(p);
}
template <> void NativeTree::_M_erase(_Rb_tree_node<Rva0061F910Key> *);
}
template void NativeTree::erase(NativeTree::iterator, NativeTree::iterator);


namespace _STL {
typedef _Rb_tree_iterator<pair<const int,int>,_Nonconst_traits<pair<const int,int> > > CBSpeedIterator;
typedef _Rb_tree<int,pair<const int,int>,_Select1st<pair<const int,int> >,less<int>,allocator<pair<const int,int> > > CBSpeedTree;
typedef _Rb_tree_node<pair<const int,int> > CBSpeedNode;
template pair<CBSpeedIterator,bool>::pair(const CBSpeedIterator&,const bool&);
template CBSpeedNode*& CBSpeedTree::_S_left(CBSpeedNode*);
template CBSpeedNode*& CBSpeedTree::_S_right(CBSpeedNode*);
template CBSpeedNode*& CBSpeedTree::_S_parent(CBSpeedNode*);
template CBSpeedIterator& CBSpeedIterator::operator--();
}
