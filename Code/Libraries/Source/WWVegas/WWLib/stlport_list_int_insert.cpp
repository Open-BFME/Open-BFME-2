// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Dedicated unit without the bfmelist __forceinline _M_create_node shim so
// list<int>::insert can call the already-landed create_node at 0xB6447.
#include <list>
template class _STL::list<int, _STL::allocator<int> >;
