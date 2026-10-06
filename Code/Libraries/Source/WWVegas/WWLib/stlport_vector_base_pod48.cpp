// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0?$_Vector_base@UBfmePod48@@V?$allocator@UBfmePod48@@@_STL@@@_STL@@QAE@IABV?$allocator@UBfmePod48@@@1@@Z @0x003F4443 60B leaf Vector_base Pod48 ctor via allocate plus init; caller vector Pod48 ctor 0x003F5B8A; prev Pod104 base same TU family
#include <vector>

struct BfmePod48 { int a[12]; };

template _STL::_Vector_base<BfmePod48, _STL::allocator<BfmePod48> >::_Vector_base(unsigned int, const _STL::allocator<BfmePod48> &);
