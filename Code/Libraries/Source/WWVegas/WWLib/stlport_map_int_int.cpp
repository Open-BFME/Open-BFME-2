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

// Use the separately compiled size-optimized subtree erase at retail 0x692F5.
// Suppress this speed-profile copy so callers select the verified provider.
namespace _STL {
template <> void IntMapTree::_M_erase(_Rb_tree_node<pair<const int, int> > *);
// Native clone owner is the verified 30B body at 0x0053444F.
// This speed-profile unit emits a different allocation/cleanup shape.
template <> IntMapTree::_Link_type IntMapTree::_M_clone_node(IntMapTree::_Link_type);
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

template class _STL::map<int, int, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > >;

// Unsigned four-byte key view used by the asset-manager set operations at
// 0x61F910/0x61FAA0. The range release is the complete 144-byte ICF twin of
// this unit's int-map owner at 0x61F7B0, including its allocation release and
// 0x692F5 subtree callee. No original key or application class name is claimed.
extern void __cdecl Rva00030830FreeAllocation(void *);
struct Rva0061F910Key { unsigned int a; };
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
