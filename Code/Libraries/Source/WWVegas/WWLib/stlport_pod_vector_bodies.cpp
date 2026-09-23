// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Pristine STLport 4.5.3 vector members for fixed-size POD elements.
// Each body was placed by a single masked whole-.text hit of this unit, but
// none of its retail callers is claimed, so no real element type is proven:
// BfmePodN is a placeholder naming only the element size (the BfmeE16 /
// Rva..Element convention), and char likewise stands for any 1-byte element.
//
// BfmePodN (BfmeShortPodN: 2-byte aligned) is a placeholder for the real
// N-byte element type at each site.
// Where retail's copy construct for that element is non-trivial (it calls a
// copy constructor), _Construct<BfmePodN> is pinned in symbols.csv at the
// address the byte-true call site proves; that body is not compiled from here.
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
struct BfmePod68 { int a[17]; };
inline bool operator==(const BfmePod68 &x, const BfmePod68 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod68 &x, const BfmePod68 &y) { return x.a[0] < y.a[0]; }
struct BfmePod76 { int a[19]; };
inline bool operator==(const BfmePod76 &x, const BfmePod76 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod76 &x, const BfmePod76 &y) { return x.a[0] < y.a[0]; }
struct BfmePod80 { int a[20]; };
inline bool operator==(const BfmePod80 &x, const BfmePod80 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod80 &x, const BfmePod80 &y) { return x.a[0] < y.a[0]; }
struct BfmePod88 { int a[22]; };
inline bool operator==(const BfmePod88 &x, const BfmePod88 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod88 &x, const BfmePod88 &y) { return x.a[0] < y.a[0]; }
struct BfmePod92 { int a[23]; };
inline bool operator==(const BfmePod92 &x, const BfmePod92 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod92 &x, const BfmePod92 &y) { return x.a[0] < y.a[0]; }
struct BfmePod104 { int a[26]; };
inline bool operator==(const BfmePod104 &x, const BfmePod104 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod104 &x, const BfmePod104 &y) { return x.a[0] < y.a[0]; }
struct BfmePod128 { int a[32]; };
inline bool operator==(const BfmePod128 &x, const BfmePod128 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod128 &x, const BfmePod128 &y) { return x.a[0] < y.a[0]; }
struct BfmePod144 { int a[36]; };
inline bool operator==(const BfmePod144 &x, const BfmePod144 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod144 &x, const BfmePod144 &y) { return x.a[0] < y.a[0]; }
struct BfmePod148 { int a[37]; };
inline bool operator==(const BfmePod148 &x, const BfmePod148 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod148 &x, const BfmePod148 &y) { return x.a[0] < y.a[0]; }
struct BfmePod160 { int a[40]; };
inline bool operator==(const BfmePod160 &x, const BfmePod160 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod160 &x, const BfmePod160 &y) { return x.a[0] < y.a[0]; }
struct BfmePod172 { int a[43]; };
inline bool operator==(const BfmePod172 &x, const BfmePod172 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod172 &x, const BfmePod172 &y) { return x.a[0] < y.a[0]; }
struct BfmePod180 { int a[45]; };
inline bool operator==(const BfmePod180 &x, const BfmePod180 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod180 &x, const BfmePod180 &y) { return x.a[0] < y.a[0]; }
struct BfmePod216 { int a[54]; };
inline bool operator==(const BfmePod216 &x, const BfmePod216 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod216 &x, const BfmePod216 &y) { return x.a[0] < y.a[0]; }
struct BfmePod248 { int a[62]; };
inline bool operator==(const BfmePod248 &x, const BfmePod248 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod248 &x, const BfmePod248 &y) { return x.a[0] < y.a[0]; }
struct BfmePod252 { int a[63]; };
inline bool operator==(const BfmePod252 &x, const BfmePod252 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod252 &x, const BfmePod252 &y) { return x.a[0] < y.a[0]; }
struct BfmePod260 { int a[65]; };
inline bool operator==(const BfmePod260 &x, const BfmePod260 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod260 &x, const BfmePod260 &y) { return x.a[0] < y.a[0]; }
struct BfmePod340 { int a[85]; };
inline bool operator==(const BfmePod340 &x, const BfmePod340 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod340 &x, const BfmePod340 &y) { return x.a[0] < y.a[0]; }
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
template class _STL::vector<BfmePod68, _STL::allocator<BfmePod68 > >;
template class _STL::vector<BfmePod76, _STL::allocator<BfmePod76 > >;
template class _STL::vector<BfmePod80, _STL::allocator<BfmePod80 > >;
template class _STL::vector<BfmePod88, _STL::allocator<BfmePod88 > >;
template class _STL::vector<BfmePod92, _STL::allocator<BfmePod92 > >;
template class _STL::vector<BfmePod104, _STL::allocator<BfmePod104 > >;
template class _STL::vector<BfmePod128, _STL::allocator<BfmePod128 > >;
template class _STL::vector<BfmePod144, _STL::allocator<BfmePod144 > >;
template class _STL::vector<BfmePod148, _STL::allocator<BfmePod148 > >;
template class _STL::vector<BfmePod160, _STL::allocator<BfmePod160 > >;
template class _STL::vector<BfmePod172, _STL::allocator<BfmePod172 > >;
template class _STL::vector<BfmePod180, _STL::allocator<BfmePod180 > >;
template class _STL::vector<BfmePod216, _STL::allocator<BfmePod216 > >;
template class _STL::vector<BfmePod248, _STL::allocator<BfmePod248 > >;
template class _STL::vector<BfmePod252, _STL::allocator<BfmePod252 > >;
// Only allocation and plain assignment are claimed for this size-only view.
template class _STL::allocator<BfmePod260>;
template BfmePod260* _STL::__copy<BfmePod260*, BfmePod260*, int>(
    BfmePod260*, BfmePod260*, BfmePod260*,
    const _STL::random_access_iterator_tag&, int*);
template class _STL::vector<BfmePod340, _STL::allocator<BfmePod340 > >;
