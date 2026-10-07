// cl: /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ??1?$_Rb_tree@HU?$pair@$$CBHURva00462D35Mapped@@@_STL@@U?$_Select1st@U?$pair@$$CBHURva00462D35Mapped@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHURva00462D35Mapped@@@_STL@@@2@@_STL@@QAE@XZ @ 0x004636FE (56B).
// _Rb_tree<int pair<const int Rva00462D35Mapped>> dtor calling clear 0x004633FC then header free 0x00030830.
// Evidence: 56B EH-prolog shape identical to sibling dtor 0x004636C6; callee clear row names Rva00462D35Mapped tree.
#include <stl/_alloc.h>
namespace _STL { template <> void __malloc_alloc<0>::deallocate(void *, size_t); }
#include <map>

struct Rva00462D35Mapped
{
	unsigned int m_bits;
};

typedef _STL::pair<const int, Rva00462D35Mapped> Rva004636FEPair;

// Preserve retail's inline node/buffer free; the public allocator is supplied by its verified owner.
namespace _STL {
#pragma optimize("gsy", on)
template <> __forceinline void allocator<_Rb_tree_node< ::Rva004636FEPair > >::deallocate(_Rb_tree_node< ::Rva004636FEPair > *p, size_t) const { if (p != 0) free(p); }
#pragma optimize("", on)
}

typedef _STL::_Rb_tree<int, Rva004636FEPair, _STL::_Select1st<Rva004636FEPair>, _STL::less<int>, _STL::allocator<Rva004636FEPair> > Rva004636FETree;

template Rva004636FETree::~_Rb_tree();
