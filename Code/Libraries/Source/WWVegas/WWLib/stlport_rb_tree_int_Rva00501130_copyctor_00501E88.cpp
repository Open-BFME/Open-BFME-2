// cl: /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??0?$_Rb_tree@HU?$pair@$$CBHURva00501130Mapped@@@_STL@@U?$_Select1st@U?$pair@$$CBHURva00501130Mapped@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHURva00501130Mapped@@@_STL@@@2@@_STL@@QAE@ABV01@@Z @0x00501E88 165B: _Rb_tree<int pair<const int Rva00501130Mapped>> copy ctor; evidence calls rowed _M_copy 0x00501CFE rowed get_allocator 0x0021983A and base ctor 0x004FF4F1 unlocks 0x005026EE
#include <map>

struct Rva00501130Mapped { int a[5]; };

typedef _STL::_Rb_tree<int, _STL::pair<const int, Rva00501130Mapped>, _STL::_Select1st<_STL::pair<const int, Rva00501130Mapped> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, Rva00501130Mapped> > > IntRva00501130Tree2;
template IntRva00501130Tree2::_Rb_tree(const IntRva00501130Tree2 &);
