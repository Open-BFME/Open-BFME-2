// cl: /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1?$vector@UBfmeStringRecord005D511F@@V?$allocator@UBfmeStringRecord005D511F@@@_STL@@@_STL@@QAE@XZ @0x005D5434 63B.
// Vector dtor over 0x14-byte BfmeStringRecord005D511F via rowed _Destroy 0x005D541B and _free 0x00030830.
// Same EH shape (and/or -1 states) as BfmeStringRecord00111ACF vector dtor @0x003F6936 and Prereq vector dtor @0x002D040C.
// Callers 0x005D56D0 and 0x005D574C.
#include <vector>
struct BfmeStringRecord005D511F { ~BfmeStringRecord005D511F(); };
template _STL::vector<BfmeStringRecord005D511F>::~vector();
