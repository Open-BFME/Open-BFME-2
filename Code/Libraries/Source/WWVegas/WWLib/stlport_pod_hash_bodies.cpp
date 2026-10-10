// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Pristine STLport 4.5.3 hash_map/hash_set members for placeholder values,
// each placed by a single masked whole-.text hit. BfmePodN stands for the real
// N-byte mapped type and int for any 4-byte key/value that folds with it; the
// placed bodies' node sizes and copy lengths fix those sizes. No retail caller
// is claimed.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

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
struct BfmePod44 { int a[11]; };
inline bool operator==(const BfmePod44 &x, const BfmePod44 &y) { return x.a[0] == y.a[0]; }
struct BfmePod52 { int a[13]; };
inline bool operator==(const BfmePod52 &x, const BfmePod52 &y) { return x.a[0] == y.a[0]; }
struct BfmePod72 { int a[18]; };
inline bool operator==(const BfmePod72 &x, const BfmePod72 &y) { return x.a[0] == y.a[0]; }
template class _STL::hash_set<int, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<int> >;
template class _STL::hash_map<int, BfmePod16, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<_STL::pair<const int, BfmePod16> > >;
template class _STL::hash_map<int, BfmePod20, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<_STL::pair<const int, BfmePod20> > >;
template class _STL::hash_map<int, BfmePod24, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<_STL::pair<const int, BfmePod24> > >;
template class _STL::hash_map<int, BfmePod48, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<_STL::pair<const int, BfmePod48> > >;
template class _STL::hash_map<int, BfmePod44, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<_STL::pair<const int, BfmePod44> > >;
template class _STL::hash_map<int, BfmePod52, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<_STL::pair<const int, BfmePod52> > >;
// Native4198C6 is now the typed string-key node creator in Rva004197E8Pair.cpp.
template class _STL::hash_map<int, BfmePod72, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<_STL::pair<const int, BfmePod72> > >;

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?eraseSlot@ObjectLookupMap@@QAEXPAH@Z=?erase@?$hashtable@HHU?$hash@H@_STL@@U?$_Identity@H@2@U?$equal_to@H@2@V?$allocator@H@2@@_STL@@QAEIABH@Z")
