// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?_M_erase@?$_Rb_tree@GU?$pair@$$CBGH@_STL@@U?$_Select1st@U?$pair@$$CBGH@_STL@@@2@U?$less@G@2@V?$allocator@U?$pair@$$CBGH@_STL@@@2@@_STL@@AAEXPAU?$_Rb_tree_node@U?$pair@$$CBGH@_STL@@@2@@Z @0x004DC87E, 45B.
// Trivial RB erase for map<unsigned short,int>: recurse-right via +0xC
// walk-left via +0x8 free via 0x00030830 ret 4. Same 45B shape as
// stlport_tree_erase_00462D35.cpp. Unblocks clear 0x004DCC39. Callers
// self 0x004DC890 and 0x004DCC47. Value trivial so no _Destroy.
#include <map>

typedef _STL::_Rb_tree<unsigned short, _STL::pair<const unsigned short, int>, _STL::_Select1st<_STL::pair<const unsigned short, int> >, _STL::less<unsigned short>, _STL::allocator<_STL::pair<const unsigned short, int> > > GHMapTree004DC87E;

template void GHMapTree004DC87E::_M_erase(GHMapTree004DC87E::_Link_type);
template void GHMapTree004DC87E::clear();
