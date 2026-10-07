// ??1?$_Rb_tree@HU?$pair@$$CBHURva0016CB50Mapped@@@_STL@@U?$_Select1st@U?$pair@$$CBHURva0016CB50Mapped@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHURva0016CB50Mapped@@@_STL@@@2@@_STL@@QAE@XZ
// partial score=0.98 date=2026-09-29
// cl: /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// Dtor @0x0016DAA0 (121B) of the trivial Rb tree at 0x0016CB50: clear plus
// header free with EH handler 0x767788. Same TU as the rowed _M_erase but
// with /EHs (fixes the missing mov [esp+0x10],-1 state store). Only diff is
// the inherited clear wall: mov eax+test vs retail cmp at +0x1D (122 vs 121).
// Try /O1 for size (cmp 4B vs mov+test 5B).
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
template Rva0016CB50Tree::~_Rb_tree();
