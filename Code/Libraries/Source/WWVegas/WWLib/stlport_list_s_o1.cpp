// cl: /Ireference/shims/bfmelist /O1 /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <list>
template class _STL::list<short, _STL::allocator<short > >;
