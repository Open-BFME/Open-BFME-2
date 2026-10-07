// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?_M_erase@?$_Rb_tree@IU?$pair@$$CBIPAX@_STL@@U?$_Select1st@U?$pair@$$CBIPAX@_STL@@@2@U?$less@I@2@V?$allocator@U?$pair@$$CBIPAX@_STL@@@2@@_STL@@AAEXPAU?$_Rb_tree_node@U?$pair@$$CBIPAX@_STL@@@2@@Z @ 0x00357153 (45B).
// ?clear@?$_Rb_tree@IU?$pair@$$CBIPAX@_STL@@U?$_Select1st@U?$pair@$$CBIPAX@_STL@@@2@U?$less@I@2@V?$allocator@U?$pair@$$CBIPAX@_STL@@@2@@_STL@@QAEXXZ @ 0x00357416 (41B).
// Unsigned-int to void* RB-tree eraser sibling of rowed unsigned _M_find 0x00357180.
// Evidence: 45B recurse-right via [esi+0x0C] walk-left via [esi+0x08] with GameMemory free 0x00030830 ret 4
// identical shape to rowed signed erase 0x004ABAD6; caller is 41B clear 0x00357416 passing root [eax+4].
#include <stl/_alloc.h>
namespace _STL { template <> void __malloc_alloc<0>::deallocate(void *, size_t); }
#include <map>

typedef _STL::pair<const unsigned, void *> Rva00357153Pair;

// Preserve retail's inline node/buffer free; the public allocator is supplied by its verified owner.
namespace _STL {
#pragma optimize("gsy", on)
template <> __forceinline void allocator<_Rb_tree_node< ::Rva00357153Pair > >::deallocate(_Rb_tree_node< ::Rva00357153Pair > *p, size_t) const { if (p != 0) free(p); }
#pragma optimize("", on)
}

typedef _STL::_Rb_tree<unsigned, Rva00357153Pair, _STL::_Select1st<Rva00357153Pair>, _STL::less<unsigned>, _STL::allocator<Rva00357153Pair> > Rva00357153Tree;

template void Rva00357153Tree::_M_erase(Rva00357153Tree::_Link_type);
template void Rva00357153Tree::clear();
