// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Dedicated unit without the bfmelist __forceinline _M_create_node shim so
// list<BfmePod264>::insert calls the already-landed create_node at 0x00289EB2.
// Retail 0x00289ED7 (37 bytes) is the insert worker; same pattern as
// stlport_list_int_insert.cpp.
#include <list>
struct BfmePod264 { int a[66]; };
inline bool operator==(const BfmePod264 &x, const BfmePod264 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod264 &x, const BfmePod264 &y) { return x.a[0] < y.a[0]; }
template class _STL::list<BfmePod264, _STL::allocator<BfmePod264> >;
