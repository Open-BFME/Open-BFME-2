// ??4?$vector@UBfmePod24@@V?$allocator@UBfmePod24@@@_STL@@@_STL@@QAEAAV01@ABV01@@Z
// partial score=0.55 date=2026-09-25
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// STLport 4.5.3 vector assignment emitter for target boundary 0x000BC20D/209.
// BfmePod24 is only a 24-byte emitter placeholder; no application type or
// payload identity is claimed.
#include <vector>

struct BfmePod24 { int a[6]; };
inline bool operator==(const BfmePod24 &x, const BfmePod24 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod24 &x, const BfmePod24 &y) { return x.a[0] < y.a[0]; }

template class _STL::vector<BfmePod24, _STL::allocator<BfmePod24> >;
