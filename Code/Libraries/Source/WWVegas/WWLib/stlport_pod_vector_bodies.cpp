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
struct BfmePod28 { int a[7]; };
inline bool operator==(const BfmePod28 &x, const BfmePod28 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod28 &x, const BfmePod28 &y) { return x.a[0] < y.a[0]; }
struct BfmePod32 { int a[8]; };
inline bool operator==(const BfmePod32 &x, const BfmePod32 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod32 &x, const BfmePod32 &y) { return x.a[0] < y.a[0]; }
struct BfmePod36 { int a[9]; };
inline bool operator==(const BfmePod36 &x, const BfmePod36 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod36 &x, const BfmePod36 &y) { return x.a[0] < y.a[0]; }
struct BfmePod40 { int a[10]; };
inline bool operator==(const BfmePod40 &x, const BfmePod40 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod40 &x, const BfmePod40 &y) { return x.a[0] < y.a[0]; }
struct BfmePod44 { int a[11]; };
inline bool operator==(const BfmePod44 &x, const BfmePod44 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod44 &x, const BfmePod44 &y) { return x.a[0] < y.a[0]; }
struct BfmePod48 { int a[12]; };
inline bool operator==(const BfmePod48 &x, const BfmePod48 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod48 &x, const BfmePod48 &y) { return x.a[0] < y.a[0]; }
struct BfmePod52 { int a[13]; };
inline bool operator==(const BfmePod52 &x, const BfmePod52 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod52 &x, const BfmePod52 &y) { return x.a[0] < y.a[0]; }
struct BfmePod60 { int a[15]; };
inline bool operator==(const BfmePod60 &x, const BfmePod60 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod60 &x, const BfmePod60 &y) { return x.a[0] < y.a[0]; }
template class _STL::vector<char, _STL::allocator<char > >;
template class _STL::vector<BfmePod20, _STL::allocator<BfmePod20 > >;
template class _STL::vector<BfmePod24, _STL::allocator<BfmePod24 > >;
template class _STL::vector<BfmePod28, _STL::allocator<BfmePod28 > >;
template class _STL::vector<BfmePod32, _STL::allocator<BfmePod32 > >;
template class _STL::vector<BfmePod36, _STL::allocator<BfmePod36 > >;
template class _STL::vector<BfmePod40, _STL::allocator<BfmePod40 > >;
template class _STL::vector<BfmePod44, _STL::allocator<BfmePod44 > >;
template class _STL::vector<BfmePod48, _STL::allocator<BfmePod48 > >;
template class _STL::vector<BfmePod52, _STL::allocator<BfmePod52 > >;
template class _STL::vector<BfmePod60, _STL::allocator<BfmePod60 > >;
