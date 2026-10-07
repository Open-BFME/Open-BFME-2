// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?_M_erase@?$_Rb_tree@HU?$pair@$$CBHURva0016CB50Mapped@@@_STL@@U?$_Select1st@U?$pair@$$CBHURva0016CB50Mapped@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHURva0016CB50Mapped@@@_STL@@@2@@_STL@@AAEXPAU?$_Rb_tree_node@U?$pair@$$CBHURva0016CB50Mapped@@@_STL@@@2@@Z @0x0016CB50 51B.
// Trivial red-black tree node eraser: recurse-right via [esi+0x0C],
// walk-left via [esi+0x08], release via GameMemory free 0x00030830, ret 4.
// Same byte shape as rowed 45B erase 0x00462D08. Callers at 0x0016D511 and
// 0x0016DAD3 clear plus re-init the header sentinel. True key/value unknown;
// opaque trivial 4-byte placeholder, erase bytes independent of trivial type.
#include <stl/_alloc.h>
namespace _STL { template <> void __malloc_alloc<0>::deallocate(void *, size_t); }
#include <map>

struct Rva0016CB50Mapped
{
	unsigned int m_bits;
};

typedef _STL::pair<const int, Rva0016CB50Mapped> Rva0016CB50Pair;

// Preserve retail's inline node/buffer free; the public allocator is supplied by its verified owner.
namespace _STL {
template <> __forceinline void allocator<_Rb_tree_node< ::Rva0016CB50Pair > >::deallocate(_Rb_tree_node< ::Rva0016CB50Pair > *p, size_t) const { if (p != 0) free(p); }
}

typedef _STL::_Rb_tree<int, Rva0016CB50Pair, _STL::_Select1st<Rva0016CB50Pair>, _STL::less<int>, _STL::allocator<Rva0016CB50Pair> > Rva0016CB50Tree;

template void Rva0016CB50Tree::_M_erase(Rva0016CB50Tree::_Link_type);
