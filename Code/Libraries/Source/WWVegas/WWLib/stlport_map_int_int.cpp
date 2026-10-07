// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport

#include <stl/_alloc.h>
namespace _STL { template <> void __malloc_alloc<0>::deallocate(void *, size_t); }
#include <map>

// Preserve retail's inlined buffer release while using the canonical public allocator.
namespace _STL {
#pragma optimize("gsy", on)
template <> __forceinline void allocator<_Rb_tree_node<pair<const int, int> > >::deallocate(_Rb_tree_node<pair<const int, int> > *p, size_t) const { if (p != 0) free(p); }
#pragma optimize("", on)
}

class GameWindow;
typedef _STL::_Rb_tree<GameWindow *, GameWindow *, _STL::_Identity<GameWindow *>, _STL::less<GameWindow *>, _STL::allocator<GameWindow *> > RetailRangeTree;
typedef _STL::_Rb_tree<int, _STL::pair<const int, int>, _STL::_Select1st<_STL::pair<const int, int> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > > IntMapTree;

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

template class _STL::map<int, int, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > >;
