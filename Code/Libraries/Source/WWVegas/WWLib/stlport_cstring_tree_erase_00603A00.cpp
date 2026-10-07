// cl: /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?_M_erase@?$_Rb_tree@PBDU?$pair@QBDURva00603A00Mapped@@@_STL@@U?$_Select1st@U?$pair@QBDURva00603A00Mapped@@@_STL@@@2@U?$less@PBD@2@V?$allocator@U?$pair@QBDURva00603A00Mapped@@@_STL@@@2@@_STL@@AAEXPAU?$_Rb_tree_node@U?$pair@QBDURva00603A00Mapped@@@_STL@@@2@@Z @ 0x00603A00 (45B).
// ?clear@?$_Rb_tree@PBDU?$pair@QBDURva00603A00Mapped@@@_STL@@U?$_Select1st@U?$pair@QBDURva00603A00Mapped@@@_STL@@@2@U?$less@PBD@2@V?$allocator@U?$pair@QBDURva00603A00Mapped@@@_STL@@@2@@_STL@@QAEXXZ @ 0x00603A7F (41B).
// ??1?$_Rb_tree@PBDU?$pair@QBDURva00603A00Mapped@@@_STL@@U?$_Select1st@U?$pair@QBDURva00603A00Mapped@@@_STL@@@2@U?$less@PBD@2@V?$allocator@U?$pair@QBDURva00603A00Mapped@@@_STL@@@2@@_STL@@QAE@XZ @ 0x00603AA8 (56B).
// C-string keyed red-black tree node eraser in the 0x00600854-0x00604518 strcmp-keyed family.
// Evidence: self-recursive right then left-walk with GameMemory free 0x00030830 matches the rowed
// 45B int-int erase 0x000692F5 modulo reloc; caller is clear 0x00603A7F which passes root [eax+4];
// sibling find 0x00603A2D uses the same header layout ([ebx]=header [edi+4]=root left+8 right+12)
// with node key at +0x10 compared via the rowed C-string Less 0x006038D4, proving key PBD.
// Comparator less<PBD> here is unproven by erase (no calls) and is a standard placeholder; the true
// C-string ordering is proven by the sibling find. Mapped is an opaque trivial 4-byte placeholder;
// erase/find bytes are independent of trivial mapped size and type, true mapped unknown.
#include <stl/_alloc.h>
namespace _STL { template <> void __malloc_alloc<0>::deallocate(void *, size_t); }
#include <map>

struct Rva00603A00Mapped
{
	unsigned int m_bits;
};

typedef _STL::pair<const char* const, Rva00603A00Mapped> Rva00603A00Pair;

// Preserve retail's inline node/buffer free; the public allocator is supplied by its verified owner.
namespace _STL {
#pragma optimize("gsy", on)
template <> __forceinline void allocator<_Rb_tree_node< ::Rva00603A00Pair > >::deallocate(_Rb_tree_node< ::Rva00603A00Pair > *p, size_t) const { if (p != 0) free(p); }
#pragma optimize("", on)
}

typedef _STL::_Rb_tree<const char*, Rva00603A00Pair, _STL::_Select1st<Rva00603A00Pair>, _STL::less<const char*>, _STL::allocator<Rva00603A00Pair> > Rva00603A00Tree;

template void Rva00603A00Tree::_M_erase(Rva00603A00Tree::_Link_type);
template void Rva00603A00Tree::clear();
template Rva00603A00Tree::~_Rb_tree();
