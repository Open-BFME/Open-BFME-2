// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ??$_M_find@G@?$_Rb_tree@GU?$pair@$$CBGH@_STL@@U?$_Select1st@U?$pair@$$CBGH@_STL@@@2@U?$less@G@2@V?$allocator@U?$pair@$$CBGH@_STL@@@2@@_STL@@ABEPAU?$_Rb_tree_node@U?$pair@$$CBGH@_STL@@@1@ABG@Z @0x004DC8AB, 60B.
// GH map _M_find ushort key: same 60B shape as 0x001559C0 AsciiString-mapped twin. Key at node+0x10 left+8 right+12 root via header+4. Callers 0x00470809 0x004709CD 0x004D1AAE 0x004D29F6 0x004DD137.
#include <map>

typedef _STL::_Rb_tree<unsigned short, _STL::pair<const unsigned short, int>, _STL::_Select1st<_STL::pair<const unsigned short, int> >, _STL::less<unsigned short>, _STL::allocator<_STL::pair<const unsigned short, int> > > GHMapTree004DC8AB;

template GHMapTree004DC8AB::_Link_type GHMapTree004DC8AB::_M_find<unsigned short>(const unsigned short &) const;
