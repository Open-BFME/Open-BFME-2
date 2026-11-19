// ?_M_fill_insert@?$vector@UBfmePod52@@V?$allocator@UBfmePod52@@@_STL@@@_STL@@QAEXPAUBfmePod52@@IABU3@@Z
// partial score=0.98 date=2026-09-29
// cl: /Ob0 /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?_M_fill_insert@?$vector@UBfmePod52@@V?$allocator@UBfmePod52@@@_STL@@@_STL@@QAEXPAUBfmePod52@@IABU3@@Z @0x001DE5D2 225B
// vector<BfmePod52> fill-insert with non-trivial temp copy via twin-pinned
// BfmePod52 copy ctor at 0x001DD0A0. Same flags as neighbours 0x001DE556/0x001DE6E1.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#define _STLP_NO_EXCEPTIONS 1
#include <vector>
// Suppress this TU's non-retail copy of ??$_Construct@UBfmePod52@@U1@@_STL@@YAXPAUBfmePod52@@ABU1@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod52;
namespace _STL { template <> void _Construct<BfmePod52,BfmePod52>(BfmePod52 *,BfmePod52 const &); }
// Suppress this TU's non-retail copy of ?_M_clear@?$vector@UBfmePod52@@V?$allocator@UBfmePod52@@@_STL@@@_STL@@IAEXXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> void vector<BfmePod52,allocator<BfmePod52> >::_M_clear(); }
// Suppress this TU's non-retail copy of ?deallocate@?$_STLP_alloc_proxy@PAUBfmePod52@@U1@V?$allocator@UBfmePod52@@@_STL@@@_STL@@QA:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> void _STLP_alloc_proxy<BfmePod52 *,BfmePod52,allocator<BfmePod52> >::deallocate(BfmePod52 *,unsigned int); }
// Suppress this TU's non-retail copy of ?allocate@?$_STLP_alloc_proxy@PAUBfmePod52@@U1@V?$allocator@UBfmePod52@@@_STL@@@_STL@@QAEP:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> BfmePod52 * _STLP_alloc_proxy<BfmePod52 *,BfmePod52,allocator<BfmePod52> >::allocate(unsigned int); }

struct BfmePod52 {
    BfmePod52(const BfmePod52 &other);
    char m_body[52];
};

template void _STL::vector<BfmePod52>::_M_fill_insert(
    BfmePod52 *, unsigned int, const BfmePod52 &);
