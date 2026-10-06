// cl: /Ireference/shims/bfme2_ascii /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfmealloc
// stlport
// ?_M_erase@?$_Rb_tree@HU?$pair@$$CBHURva004D1B38Mapped@@@_STL@@U?$_Select1st@U?$pair@$$CBHURva004D1B38Mapped@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHURva004D1B38Mapped@@@_STL@@@2@@_STL@@AAEXPAU?$_Rb_tree_node@U?$pair@$$CBHURva004D1B38Mapped@@@_STL@@@2@@Z @ 0x004D1B38 (53B).
// Recursive subtree eraser: recurse-right via [esi+0x0C] walk-left via [esi+0x08] destroy value at node+0x10
// via pair dtor pinned to ICF-shared 0x29D7C2 and release node via GameMemory free 0x00030830 ret 4.
// Same 53B Destroy-and-free shape as rowed color-tree erase 0x380EB1 and string-pair erase 0x2E44BD.
// Called by clear 0x004D1EF1 with root and self-recursive. True key/value unknown; opaque int key plus
// string-carrying mapped placeholder. Erase bytes independent of key and trailing trivial members.
// Identity via call chain and value-at-+16 plus free. Donor vendor/stlport/stl/_tree.c::_M_erase.
#include <map>

#include "ascii_string.h"


struct Rva004D1B38Mapped
{
	AsciiString m_name;
};

typedef _STL::pair<const int, Rva004D1B38Mapped> Rva004D1B38Pair;
typedef _STL::_Rb_tree<int, Rva004D1B38Pair, _STL::_Select1st<Rva004D1B38Pair>, _STL::less<int>, _STL::allocator<Rva004D1B38Pair> > Rva004D1B38Tree;

// ?clear@?$_Rb_tree@HU?$pair@$$CBHURva004D1B38Mapped@@@_STL@@U?$_Select1st@U?$pair@$$CBHURva004D1B38Mapped@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHURva004D1B38Mapped@@@_STL@@@2@@_STL@@QAEXXZ @ 0x004D1EF1 (41B).
template void Rva004D1B38Tree::_M_erase(Rva004D1B38Tree::_Link_type);
template void Rva004D1B38Tree::clear();
