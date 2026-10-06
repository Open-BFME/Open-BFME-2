// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Dedicated unit without the bfmelist __forceinline _M_create_node shim so
// list<BfmePod196>::insert calls the already-landed create_node at 0x00438F82.
// Retail 0x004390A2 (37 bytes) is the insert worker; same pattern as
// stlport_list_pod264_insert.cpp.
#include <list>
struct BfmePod196 { int a[49]; };
inline bool operator==(const BfmePod196 &x, const BfmePod196 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod196 &x, const BfmePod196 &y) { return x.a[0] < y.a[0]; }
template class _STL::list<BfmePod196, _STL::allocator<BfmePod196> >;
