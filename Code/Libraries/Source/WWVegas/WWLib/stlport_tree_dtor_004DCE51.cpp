// cl: /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ??1?$_Rb_tree@GU?$pair@$$CBGH@_STL@@U?$_Select1st@U?$pair@$$CBGH@_STL@@@2@U?$less@G@2@V?$allocator@U?$pair@$$CBGH@_STL@@@2@@_STL@@QAE@XZ @0x004DCE51, 56B.
// GH map tree dtor: calls clear 0x004DCC39 then frees header via 0x00030830.
// Same 56B EH shape as 0x001DDB8E. Chain from clear. Callers 0x004DCEA6.
#include <map>

typedef _STL::_Rb_tree<unsigned short, _STL::pair<const unsigned short, int>, _STL::_Select1st<_STL::pair<const unsigned short, int> >, _STL::less<unsigned short>, _STL::allocator<_STL::pair<const unsigned short, int> > > GHMapTree004DCE51;

template GHMapTree004DCE51::~_Rb_tree();
