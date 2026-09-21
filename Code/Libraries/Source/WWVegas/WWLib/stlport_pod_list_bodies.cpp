// cl: /Ireference/shims/bfmelist /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Pristine STLport 4.5.3 list members for fixed-size POD elements; same
// evidence and naming rule as stlport_pod_vector_bodies.cpp.
//
// BfmePodN is a placeholder for the real N-byte element type at each site.
// Where retail's copy construct for that element is non-trivial (it calls a
// copy constructor), _Construct<BfmePodN> is pinned in symbols.csv at the
// address the byte-true call site proves; that body is not compiled from here.
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
struct BfmePod72 { int a[18]; };
inline bool operator==(const BfmePod72 &x, const BfmePod72 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod72 &x, const BfmePod72 &y) { return x.a[0] < y.a[0]; }
struct BfmePod80 { int a[20]; };
inline bool operator==(const BfmePod80 &x, const BfmePod80 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod80 &x, const BfmePod80 &y) { return x.a[0] < y.a[0]; }
struct BfmePod124 { int a[31]; };
inline bool operator==(const BfmePod124 &x, const BfmePod124 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod124 &x, const BfmePod124 &y) { return x.a[0] < y.a[0]; }
struct BfmePod196 { int a[49]; };
inline bool operator==(const BfmePod196 &x, const BfmePod196 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod196 &x, const BfmePod196 &y) { return x.a[0] < y.a[0]; }
template class _STL::list<BfmePod12, _STL::allocator<BfmePod12 > >;
template class _STL::list<BfmePod20, _STL::allocator<BfmePod20 > >;
template class _STL::list<BfmePod24, _STL::allocator<BfmePod24 > >;
template class _STL::list<BfmePod8, _STL::allocator<BfmePod8 > >;
template class _STL::list<BfmePod28, _STL::allocator<BfmePod28 > >;
template class _STL::list<BfmePod32, _STL::allocator<BfmePod32 > >;
template class _STL::list<BfmePod60, _STL::allocator<BfmePod60 > >;
template class _STL::list<BfmePod72, _STL::allocator<BfmePod72 > >;
template class _STL::list<BfmePod80, _STL::allocator<BfmePod80 > >;
template class _STL::list<BfmePod124, _STL::allocator<BfmePod124 > >;
template class _STL::list<BfmePod196, _STL::allocator<BfmePod196 > >;
