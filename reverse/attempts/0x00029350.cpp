// ?insert@?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@QAEPAPAXPAPAX@Z
// partial score=0.99 date=2026-10-08
// cl: /Od /Ob1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// STLport 4.5.3 vector<void*> insert(iterator) trial. Native29350..29376
// RET4 forwards an initialized null pointer to insert(iterator,const_reference).
#define __PLACEMENT_NEW_INLINE
void *__cdecl operator new(unsigned int size, void *place);
#include <stl/_alloc.h>
namespace _STL {
template<> inline void **allocator<void *>::allocate(size_type count, const void *) const
{
    void **result = count != 0 ? reinterpret_cast<void **>(allocator<char>::allocate(count * sizeof(void *), 0)) : 0;
    return result;
}
}
#include <vector>
template void **_STL::vector<void *, _STL::allocator<void *> >::insert(void **);
