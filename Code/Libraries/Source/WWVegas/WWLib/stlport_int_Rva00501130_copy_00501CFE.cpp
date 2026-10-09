// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_STLP_NO_EXCEPTIONS /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?_M_copy@?$_Rb_tree@HU?$pair@$$CBHURva00501130Mapped@@@_STL@@U?$_Select1st@U?$pair@$$CBHURva00501130Mapped@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHURva00501130Mapped@@@_STL@@@2@@_STL@@AAEPAU?$_Rb_tree_node@U?$pair@$$CBHURva00501130Mapped@@@_STL@@@2@PAU32@0@Z @0x00501CFE 115B: _Rb_tree<int pair<const int Rva00501E3FElement>>::_M_copy; evidence rowed _M_clone_node 0x005014E1 plus self recursion unlocks 0x00501E88
#include <map>

struct Rva00501E3FElement { int a; };

typedef _STL::_Rb_tree<int, _STL::pair<const int, Rva00501E3FElement>, _STL::_Select1st<_STL::pair<const int, Rva00501E3FElement> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, Rva00501E3FElement> > > IntRva00501130Tree;
template IntRva00501130Tree::_Link_type IntRva00501130Tree::_M_copy(IntRva00501130Tree::_Link_type, IntRva00501130Tree::_Link_type);
