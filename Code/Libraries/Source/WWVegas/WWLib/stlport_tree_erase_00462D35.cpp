// cl: /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?_M_erase@?$_Rb_tree@HU?$pair@$$CBHURva00462D35Mapped@@@_STL@@U?$_Select1st@U?$pair@$$CBHURva00462D35Mapped@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHURva00462D35Mapped@@@_STL@@@2@@_STL@@AAEXPAU?$_Rb_tree_node@U?$pair@$$CBHURva00462D35Mapped@@@_STL@@@2@@Z @ 0x00462D35 (45B).
// Trivial red-black tree node eraser, byte-identical shape to rowed 45B erases
// 0x00603A00 and 0x000692F5 (recurse-right via [esi+0x0C], walk-left via
// [esi+0x08], release via GameMemory free 0x00030830, ret 4). Caller is clear
// 0x004633FC which passes root [eax+0x04] same as clear 0x00603A7F; dtor
// 0x004636FE calls that clear. True key/value unknown; opaque trivial 4-byte
// placeholder, erase bytes independent of trivial type, identity via call chain.
#include <map>

struct Rva00462D35Mapped
{
	unsigned int m_bits;
};

typedef _STL::pair<const int, Rva00462D35Mapped> Rva00462D35Pair;
typedef _STL::_Rb_tree<int, Rva00462D35Pair, _STL::_Select1st<Rva00462D35Pair>, _STL::less<int>, _STL::allocator<Rva00462D35Pair> > Rva00462D35Tree;

template void Rva00462D35Tree::_M_erase(Rva00462D35Tree::_Link_type);

// Retain only the matched clear body at 0x004633FC. The former whole-class
// instantiation also emitted a wrong destructor keeper, displacing the exact
// 0x004636FE provider used by native 0x004DD206 constructor unwind cleanup.
// The two retained bodies still verify in full; allocator COMDAT debt remains.
template void Rva00462D35Tree::clear();
