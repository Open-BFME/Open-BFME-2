// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport46
#include <list>

// __node_alloc<1,0>::allocate (STLport node path) otherwise emits a per-TU
// COMDAT that loses to another unit's copy in link order; this explicit
// dllimport+forceinline specialization keeps the body inline and emits none.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__node_alloc<true, 0>::allocate(size_t __n)
{ return (__n > (size_t)_MAX_BYTES) ? __stl_new(__n) : _M_allocate(__n); }
}
class Rva00453B06Obj;
template void _STL::list<Rva00453B06Obj *>::push_back(Rva00453B06Obj *const &);
