// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?_M_insert@?$_Rb_tree@MU?$pair@$$CBMUTreeOpaqueMapped00372FF4@@@_STL@@U?$_Select1st@U?$pair@$$CBMUTreeOpaqueMapped00372FF4@@@_STL@@@2@U?$less@M@2@V?$allocator@U?$pair@$$CBMUTreeOpaqueMapped00372FF4@@@_STL@@@2@@_STL@@AAE?AU?$_Rb_tree_iterator@U?$pair@$$CBMUTreeOpaqueMapped00372FF4@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBMUTreeOpaqueMapped00372FF4@@@_STL@@@2@@2@PAU_Rb_tree_node_base@2@0ABU?$pair@$$CBMUTreeOpaqueMapped00372FF4@@@2@0@Z @ 0x00372FF4 139B.
// STLport _Rb_tree<float,pair<const float,opaque>>::_M_insert. Donor vendor/stlport/stl/_tree.c _M_insert.
// Retail float ordering proven by movss/comiss at 0x372FF4 (key at +0x10) and caller 0x005AD1A7 float walk.
// Node 0x18 (24B = 16 header + 8 value) proves 4-byte opaque mapped; calls rowed _M_create_node 0x382B7F (ICF) and _Rebalance 0x25490.
// Landing unblocks 0x005AD1A7.
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>
struct TreeOpaqueMapped00372FF4 { unsigned int m_bits; };
typedef _STL::pair<const float, TreeOpaqueMapped00372FF4> TreeValue00372FF4;
typedef _STL::_Rb_tree<float, TreeValue00372FF4, _STL::_Select1st<TreeValue00372FF4>, _STL::less<float>, _STL::allocator<TreeValue00372FF4> > Tree00372FF4;
// ?clear@?$_Rb_tree@MU?$pair@$$CBMUTreeOpaqueMapped00372FF4@@@_STL@@U?$_Select1st@U?$pair@$$CBMUTreeOpaqueMapped00372FF4@@@_STL@@@2@U?$less@M@2@V?$allocator@U?$pair@$$CBMUTreeOpaqueMapped00372FF4@@@_STL@@@2@@_STL@@QAEXXZ @ 0x00372F2D 41B.
// STLport _Rb_tree<float,pair<const float,opaque>>::clear. Donor vendor/stlport/stl/_tree.h clear.
// ?insert_unique@?$_Rb_tree@MU?$pair@$$CBMUTreeOpaqueMapped00372FF4@@@_STL@@U?$_Select1st@U?$pair@$$CBMUTreeOpaqueMapped00372FF4@@@_STL@@@2@U?$less@M@2@V?$allocator@U?$pair@$$CBMUTreeOpaqueMapped00372FF4@@@_STL@@@2@@_STL@@QAE?AU?$pair@U?$_Rb_tree_iterator@U?$pair@$$CBMUTreeOpaqueMapped00372FF4@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBMUTreeOpaqueMapped00372FF4@@@_STL@@@2@@_STL@@_N@2@ABU?$pair@$$CBMUTreeOpaqueMapped00372FF4@@@2@@Z @ 0x005AD1A7 136B.
// STLport _Rb_tree<float,pair<const float,opaque>>::insert_unique. Donor vendor/stlport/stl/_tree.c insert_unique.
// Retail float walk proven by movss/comiss at 0x5AD1BD/0x5AD1FA (key at +0x10); calls rowed _M_insert 0x00372FF4 and _M_decrement 0x242C0.
template Tree00372FF4::iterator Tree00372FF4::_M_insert(_STL::_Rb_tree_node_base *, _STL::_Rb_tree_node_base *, const TreeValue00372FF4 &, _STL::_Rb_tree_node_base *);
// Retail's 57-byte 0x004EA301 walk compares pair.first and calls this typed _M_insert.
template Tree00372FF4::iterator Tree00372FF4::insert_equal(const TreeValue00372FF4 &);
template void Tree00372FF4::_M_erase(Tree00372FF4::_Link_type);
template void Tree00372FF4::clear();
template _STL::pair<Tree00372FF4::iterator, bool> Tree00372FF4::insert_unique(const TreeValue00372FF4 &);
