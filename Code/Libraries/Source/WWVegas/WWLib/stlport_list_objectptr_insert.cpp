// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Dedicated unit without the bfmelist __forceinline _M_create_node shim so
// list<Object*>::insert calls the out-of-line create_node (landed alongside
// at 0x5EB9AC), mirroring stlport_list_int_insert.cpp.
#include <list>
class Object;
template class _STL::list<Object *, _STL::allocator<Object *> >;
