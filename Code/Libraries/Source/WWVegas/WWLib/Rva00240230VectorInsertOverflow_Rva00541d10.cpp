// cl: -DNDEBUG -MD -EHsc -D_STLP_USE_STATIC_LIB -D_STLP_NO_EXCEPTIONS -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// stlport
// ?insert@?$vector@URva00541021@@V?$allocator@URva00541021@@@_STL@@@_STL@@QAEPAURva00541021@@PAU3@ABU3@@Z
// retail 0x00541D10, 152 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/Libraries/Source/WWVegas/WWLib/Rva00240230VectorInsertOverflow.cpp: the
// donor preamble and this one vector member, the donor's other
// instantiations omitted.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}

// The element is Rva00541021 (an int, then a Region3D; Rva00541021CopyCtor.cpp):
// this body calls its _Construct 0x0054105B and its copy/assignment fold
// 0x00541021, which are rowed in their own units, so only insert and its
// copy_backward pair are emitted here. The donor's opaque 28-byte view keeps
// retail's register allocation.
#include "../../../../GameEngine/Include/Common/Rva00541021.h"
namespace _STL {
template <> void _Construct<Rva00541021, Rva00541021>(Rva00541021 *, const Rva00541021 &);
// The growth path's helpers are kept from stlport_vector_rva00541021_allocate_copy.cpp.
template <> void allocator<Rva00541021>::deallocate(Rva00541021 *, size_t) const;
template <> Rva00541021 *_STLP_alloc_proxy<Rva00541021 *, Rva00541021, allocator<Rva00541021> >::allocate(size_t);
template <> void vector<Rva00541021>::_M_clear();
}

template Rva00541021 * _STL::vector<Rva00541021>::insert(
	Rva00541021 *, const Rva00541021 &);
