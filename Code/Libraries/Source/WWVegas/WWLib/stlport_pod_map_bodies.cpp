// cl: /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
//
// Pristine STLport 4.5.3 map members for placeholder POD values, placed by a
// single masked whole-.text hit. BfmePod8 stands for the real 8-byte mapped
// type; the key is int (the placed body compares signed). No retail caller is
// claimed, so no real value type is asserted.
#include <map>
struct BfmePod8 { int a[2]; };
template class _STL::map<int, BfmePod8, _STL::less<int>, _STL::allocator<_STL::pair<const int, BfmePod8> > >;
