// cl: /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ??1?$_Rb_tree@HU?$pair@$$CBHURva00462D08Mapped@@@_STL@@U?$_Select1st@U?$pair@$$CBHURva00462D08Mapped@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHURva00462D08Mapped@@@_STL@@@2@@_STL@@QAE@XZ @ 0x004636C6 (56B).
// _Rb_tree<int pair<const int Rva00462D08Mapped>> dtor sibling of rowed _M_erase 0x00462D08 and clear 0x004633D3.
// Evidence: 56B EH-prolog calls clear 0x004633D3 then null-checked header free 0x00030830; identical shape to rowed tree dtor 0x00286852; member at +0x5c of OpenContain dtor 0x00464692.
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

template Rva00462D08Tree::~_Rb_tree();
