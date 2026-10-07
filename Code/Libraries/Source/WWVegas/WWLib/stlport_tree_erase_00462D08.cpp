// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?_M_erase@?$_Rb_tree@HU?$pair@$$CBHURva00462D08Mapped@@@_STL@@U?$_Select1st@U?$pair@$$CBHURva00462D08Mapped@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHURva00462D08Mapped@@@_STL@@@2@@_STL@@AAEXPAU?$_Rb_tree_node@U?$pair@$$CBHURva00462D08Mapped@@@_STL@@@2@@Z @ 0x00462D08 (45B).
// Trivial red-black tree node eraser, byte-identical shape to rowed 45B erases
// 0x00603A00 and 0x000692F5 plus sibling 0x00462D35 (recurse-right via
// [esi+0x0C], walk-left via [esi+0x08], release via GameMemory free 0x00030830,
// ret 4). Caller is 0x004633D3 which passes root [eax+0x04] same as clear
// 0x00603A7F. True key/value unknown; opaque trivial 4-byte placeholder,
// erase bytes independent of trivial type, identity via call chain.
#include <stl/_alloc.h>
namespace _STL { template <> void __malloc_alloc<0>::deallocate(void *, size_t); }
#include <map>

struct Rva00462D08Mapped
{
	unsigned int m_bits;
};

typedef _STL::pair<const int, Rva00462D08Mapped> Rva00462D08Pair;

// Preserve retail's inline node/buffer free; the public allocator is supplied by its verified owner.
namespace _STL {
#pragma optimize("gsy", on)
template <> __forceinline void allocator<_Rb_tree_node< ::Rva00462D08Pair > >::deallocate(_Rb_tree_node< ::Rva00462D08Pair > *p, size_t) const { if (p != 0) free(p); }
#pragma optimize("", on)
}

typedef _STL::_Rb_tree<int, Rva00462D08Pair, _STL::_Select1st<Rva00462D08Pair>, _STL::less<int>, _STL::allocator<Rva00462D08Pair> > Rva00462D08Tree;

template void Rva00462D08Tree::_M_erase(Rva00462D08Tree::_Link_type);

// Retain only the matched clear body at 0x004633D3. The former whole-class
// instantiation emitted wrong COMDAT copies; explicit instantiation keeps
// just clear (plus _M_erase above).
template void Rva00462D08Tree::clear();
