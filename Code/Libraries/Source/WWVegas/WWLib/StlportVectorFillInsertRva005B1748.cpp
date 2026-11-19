// Target boundary 0x005B1748/232 is STLport vector::_M_fill_insert: the
// boundary checks the 20-byte capacity/position/count cases, calls the
// false_type vector overflow helper when growth is needed, and returns with
// ret 0x0C. Target caller 0x005B1A07 passes the iterator/count/value form.
//
// BfmePod20 is a size-only emitter view (five DWORDs); no concrete application
// record identity or field layout is claimed. Target evidence establishes a
// 0x14 stride and the helper-call ABI, not the retail type name.
// cl: /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
// Suppress this TU's non-retail copy of ??$_Construct@UBfmePod20@@U1@@_STL@@YAXPAUBfmePod20@@ABU1@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod20;
namespace _STL { template <> void _Construct<BfmePod20,BfmePod20>(BfmePod20 *,BfmePod20 const &); }
// Suppress this TU's non-retail copy of ?_M_clear@?$vector@UBfmePod20@@V?$allocator@UBfmePod20@@@_STL@@@_STL@@IAEXXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> void vector<BfmePod20,allocator<BfmePod20> >::_M_clear(); }
// Suppress this TU's non-retail copy of ?deallocate@?$_STLP_alloc_proxy@PAUBfmePod20@@U1@V?$allocator@UBfmePod20@@@_STL@@@_STL@@QA:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> void _STLP_alloc_proxy<BfmePod20 *,BfmePod20,allocator<BfmePod20> >::deallocate(BfmePod20 *,unsigned int); }
// Suppress this TU's non-retail copy of ?allocate@?$_STLP_alloc_proxy@PAUBfmePod20@@U1@V?$allocator@UBfmePod20@@@_STL@@@_STL@@QAEP:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> BfmePod20 * _STLP_alloc_proxy<BfmePod20 *,BfmePod20,allocator<BfmePod20> >::allocate(unsigned int); }

struct BfmePod20 { int a[5]; };

// /Ob0 preserves retail's out-of-line false_type copy-backward wrapper call.
template void _STL::vector<BfmePod20>::_M_fill_insert(
	BfmePod20 *, unsigned int, const BfmePod20 &);
