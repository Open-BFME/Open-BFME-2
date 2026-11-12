// cl: /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /EHsc
// stlport46
// ??0?$vector@VRva005DE5B5@@V?$allocator@VRva005DE5B5@@@_STL@@@_STL@@QAE@I@Z
// retail 0x005DE870, 93 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/Common/R5VectorDtorEHFramedPolymorphic.cpp: the donor
// preamble and this one vector member, the donor's other elements omitted.
#include <vector>
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}

// The element is the 0x18-byte class the ledger rows as Rva005DE5B5 (ctor 0x005DE5EA,
// dtor 0x005DE5B5, both called directly here: its dtor is not virtual).
#include "../../../Libraries/Source/WWVegas/WWLib/Rva005DE5B5.h"

// The forwarder is rowed at 0x005DE833; this TU calls it and emits no copy.
namespace _STL { template <> Rva005DE5B5 *uninitialized_fill_n<Rva005DE5B5 *, unsigned int, Rva005DE5B5>(Rva005DE5B5 *, unsigned int, const Rva005DE5B5 &); }

template _STL::vector<Rva005DE5B5>::vector(unsigned int);
