// cl: /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// Dedicated /O1 + bfmealloc instantiation so _M_create_node calls the byte
// allocator at 0x307F0 and out-of-line _Construct. The existing map<int,int>
// units lack bfmealloc and inlined a different shape.
#include <map>
template class _STL::map<int, int, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > >;
