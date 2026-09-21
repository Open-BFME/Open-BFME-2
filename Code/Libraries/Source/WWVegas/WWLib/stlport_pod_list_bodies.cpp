// cl: /Ireference/shims/bfmelist /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Pristine STLport 4.5.3 list members for fixed-size POD elements; same
// evidence and naming rule as stlport_pod_vector_bodies.cpp.
#include <list>
struct BfmePod12 { int a[3]; };

struct BfmePod20 { int a[5]; };
struct BfmePod24 { int a[6]; };
inline bool operator==(const BfmePod12 &x, const BfmePod12 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod12 &x, const BfmePod12 &y) { return x.a[0] < y.a[0]; }
inline bool operator==(const BfmePod20 &x, const BfmePod20 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod20 &x, const BfmePod20 &y) { return x.a[0] < y.a[0]; }
inline bool operator==(const BfmePod24 &x, const BfmePod24 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod24 &x, const BfmePod24 &y) { return x.a[0] < y.a[0]; }
template class _STL::list<BfmePod12, _STL::allocator<BfmePod12 > >;
template class _STL::list<BfmePod20, _STL::allocator<BfmePod20 > >;
template class _STL::list<BfmePod24, _STL::allocator<BfmePod24 > >;
