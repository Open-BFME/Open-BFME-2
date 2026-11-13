// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??$__uninitialized_fill_n@PAURva00541021@@IU1@@_STL@@YAPAURva00541021@@PAU1@IABU1@ABU__false_type@0@@Z @0x005410E3 37B: vector fill helper for 28-byte Rva00541021 (int plus Region3D). Evidence: calls rowed _Construct 0x0054105B; stride 0x1C; caller is vector insert-overflow 0x00541709.
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
#include "../../../Include/Lib/Region3D.h"
#include "../../../../GameEngine/Include/Common/Rva00541021.h"
namespace _STL {
template <> void _Construct<Rva00541021, Rva00541021>(Rva00541021 *, const Rva00541021 &);
}
// Retail's _M_allocate_and_copy at 0x54124E calls this element's rowed
// copy worker 0x5411C8 (StlSweepW5Rva005411C8.cpp), not BfmePod28's.
// Emit the rowed growth family; the unused default-insert members of a
// whole-class instantiation would require an unrowed element constructor.
template void _STL::vector<Rva00541021>::_M_insert_overflow(
    Rva00541021 *, const Rva00541021 &, const _STL::__false_type &, unsigned int, bool);
template void _STL::vector<Rva00541021>::push_back(const Rva00541021 &);
template Rva00541021 *_STL::vector<Rva00541021>::_M_allocate_and_copy<const Rva00541021 *>(
    unsigned int, const Rva00541021 *, const Rva00541021 *);
