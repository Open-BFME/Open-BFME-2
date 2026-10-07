// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?_M_erase@?$_Rb_tree@HU?$pair@$$CBHURva002B60F9Mapped@@@_STL@@U?$_Select1st@U?$pair@$$CBHURva002B60F9Mapped@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHURva002B60F9Mapped@@@_STL@@@2@@_STL@@AAEXPAU?$_Rb_tree_node@U?$pair@$$CBHURva002B60F9Mapped@@@_STL@@@2@@Z @ 0x002B60F9 (45B).
// Trivial red-black tree node eraser, byte-identical shape to rowed 45B erases
// 0x00462D35 0x00603A00 and 0x000692F5 (recurse-right via [esi+0x0C], walk-left via
// [esi+0x08], release via GameMemory free 0x00030830, ret 4). Caller is clear
// 0x002B70B3. True key/value unknown; opaque trivial 4-byte placeholder, erase
// bytes independent of trivial type, identity via call chain. Pinned
// AsciiString name at this address would need a destroy call (all AsciiString
// erases are 53B); retail has none, so the pin is a wrong-type candidate.
#include <stl/_alloc.h>
namespace _STL { template <> void __malloc_alloc<0>::deallocate(void *, size_t); }
#include <map>

struct Rva002B60F9Mapped
{
	unsigned int m_bits;
};

typedef _STL::pair<const int, Rva002B60F9Mapped> Rva002B60F9Pair;

// Preserve retail's inline node/buffer free; the public allocator is supplied by its verified owner.
namespace _STL {
#pragma optimize("gsy", on)
template <> __forceinline void allocator<_Rb_tree_node< ::Rva002B60F9Pair > >::deallocate(_Rb_tree_node< ::Rva002B60F9Pair > *p, size_t) const { if (p != 0) free(p); }
#pragma optimize("", on)
}

typedef _STL::_Rb_tree<int, Rva002B60F9Pair, _STL::_Select1st<Rva002B60F9Pair>, _STL::less<int>, _STL::allocator<Rva002B60F9Pair> > Rva002B60F9Tree;

template void Rva002B60F9Tree::_M_erase(Rva002B60F9Tree::_Link_type);
