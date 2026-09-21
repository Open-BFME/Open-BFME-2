// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Pristine STLport 4.5.3 hash_map/hash_set members for placeholder values,
// each placed by a single masked whole-.text hit. BfmePodN stands for the real
// N-byte mapped type and int for any 4-byte key/value that folds with it; the
// placed bodies' node sizes and copy lengths fix those sizes. No retail caller
// is claimed.
#include <hash_map>
#include <hash_set>
struct BfmePod16 { int a[4]; };
inline bool operator==(const BfmePod16 &x, const BfmePod16 &y) { return x.a[0] == y.a[0]; }
struct BfmePod20 { int a[5]; };
inline bool operator==(const BfmePod20 &x, const BfmePod20 &y) { return x.a[0] == y.a[0]; }
struct BfmePod24 { int a[6]; };
inline bool operator==(const BfmePod24 &x, const BfmePod24 &y) { return x.a[0] == y.a[0]; }
struct BfmePod32 { int a[8]; };
inline bool operator==(const BfmePod32 &x, const BfmePod32 &y) { return x.a[0] == y.a[0]; }
struct BfmePod48 { int a[12]; };
inline bool operator==(const BfmePod48 &x, const BfmePod48 &y) { return x.a[0] == y.a[0]; }
template class _STL::hash_set<int, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<int> >;
template class _STL::hash_map<int, BfmePod16, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<_STL::pair<const int, BfmePod16> > >;
template class _STL::hash_map<int, BfmePod20, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<_STL::pair<const int, BfmePod20> > >;
template class _STL::hash_map<int, BfmePod24, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<_STL::pair<const int, BfmePod24> > >;
template class _STL::hash_map<int, BfmePod32, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<_STL::pair<const int, BfmePod32> > >;
template class _STL::hash_map<int, BfmePod48, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<_STL::pair<const int, BfmePod48> > >;
