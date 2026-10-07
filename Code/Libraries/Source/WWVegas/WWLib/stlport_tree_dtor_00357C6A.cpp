// cl: /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ??1?$_Rb_tree@IU?$pair@$$CBIPAX@_STL@@U?$_Select1st@U?$pair@$$CBIPAX@_STL@@@2@U?$less@I@2@V?$allocator@U?$pair@$$CBIPAX@_STL@@@2@@_STL@@QAE@XZ @ 0x00357C6A (56B).
// Unsigned-int to void* RB-tree dtor sibling of rowed unsigned _M_find 0x00357180 and clear 0x00357416.
// Evidence: 56B EH-prolog calls clear 0x00357416 then null-checked header free 0x00030830 ret;
// identical shape to rowed signed tree dtor 0x00286852 modulo reloc; callers include dtor 0x0035822E.
#include <stl/_alloc.h>
namespace _STL { template <> void __malloc_alloc<0>::deallocate(void *, size_t); }
#include <map>

typedef _STL::pair<const unsigned, void *> Rva00357C6APair;

// Preserve retail's inline node/buffer free; the public allocator is supplied by its verified owner.
namespace _STL {
#pragma optimize("gsy", on)
template <> __forceinline void allocator<_Rb_tree_node< ::Rva00357C6APair > >::deallocate(_Rb_tree_node< ::Rva00357C6APair > *p, size_t) const { if (p != 0) free(p); }
#pragma optimize("", on)
}

typedef _STL::_Rb_tree<unsigned, Rva00357C6APair, _STL::_Select1st<Rva00357C6APair>, _STL::less<unsigned>, _STL::allocator<Rva00357C6APair> > Rva00357C6ATree;

template Rva00357C6ATree::~_Rb_tree();
