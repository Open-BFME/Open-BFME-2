// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Pristine STLport 4.5.3 vector members for fixed-size POD elements.
// Each body was placed by a single masked whole-.text hit of this unit, but
// none of its retail callers is claimed, so no real element type is proven:
// BfmePodN is a placeholder naming only the element size (the BfmeE16 /
// Rva..Element convention), and char likewise stands for any 1-byte element.
#include <vector>
struct BfmePod20 { int a[5]; };
struct BfmePod24 { int a[6]; };
inline bool operator==(const BfmePod20 &x, const BfmePod20 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod20 &x, const BfmePod20 &y) { return x.a[0] < y.a[0]; }
inline bool operator==(const BfmePod24 &x, const BfmePod24 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod24 &x, const BfmePod24 &y) { return x.a[0] < y.a[0]; }
template class _STL::vector<char, _STL::allocator<char > >;
template class _STL::vector<BfmePod20, _STL::allocator<BfmePod20 > >;
template class _STL::vector<BfmePod24, _STL::allocator<BfmePod24 > >;
