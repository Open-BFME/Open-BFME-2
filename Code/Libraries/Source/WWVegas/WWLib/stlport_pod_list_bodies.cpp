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
struct BfmePod8 { int a[2]; };
inline bool operator==(const BfmePod8 &x, const BfmePod8 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod8 &x, const BfmePod8 &y) { return x.a[0] < y.a[0]; }
struct BfmePod28 { int a[7]; };
inline bool operator==(const BfmePod28 &x, const BfmePod28 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod28 &x, const BfmePod28 &y) { return x.a[0] < y.a[0]; }
struct BfmePod32 { int a[8]; };
inline bool operator==(const BfmePod32 &x, const BfmePod32 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod32 &x, const BfmePod32 &y) { return x.a[0] < y.a[0]; }
struct BfmePod60 { int a[15]; };
inline bool operator==(const BfmePod60 &x, const BfmePod60 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod60 &x, const BfmePod60 &y) { return x.a[0] < y.a[0]; }
template class _STL::list<BfmePod12, _STL::allocator<BfmePod12 > >;
template class _STL::list<BfmePod20, _STL::allocator<BfmePod20 > >;
template class _STL::list<BfmePod24, _STL::allocator<BfmePod24 > >;
template class _STL::list<BfmePod8, _STL::allocator<BfmePod8 > >;
template class _STL::list<BfmePod28, _STL::allocator<BfmePod28 > >;
template class _STL::list<BfmePod32, _STL::allocator<BfmePod32 > >;
template class _STL::list<BfmePod60, _STL::allocator<BfmePod60 > >;
