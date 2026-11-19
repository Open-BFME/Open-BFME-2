// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// Exact no-EH STLport vector allocation/copy for the retail 44-byte POD element.
// The allocator and the trivial-copy worker are both rowed; the placeholder
// BfmePod44 names only the 44-byte stride, matching the pod-vector TU convention.
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
// Suppress this TU's non-retail copy of ??0?$vector@UBfmePod44@@V?$allocator@UBfmePod44@@@_STL@@@_STL@@QAE@ABV01@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod44;
namespace _STL { template <> vector<BfmePod44, allocator<BfmePod44> >::vector(const vector<BfmePod44, allocator<BfmePod44> > &); }
// Suppress this TU's non-retail copy of ?resize@?$vector@UBfmePod44@@V?$allocator@UBfmePod44@@@_STL@@@_STL@@QAEXI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> void vector<BfmePod44, allocator<BfmePod44> >::resize(size_t); }
// Suppress this TU's non-retail copy of ?erase@?$vector@UBfmePod44@@V?$allocator@UBfmePod44@@@_STL@@@_STL@@QAEPAUBfmePod44@@PAU3@0:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> BfmePod44 *vector<BfmePod44, allocator<BfmePod44> >::erase(BfmePod44 *, BfmePod44 *); }
// Suppress this TU's non-retail copy of ?_M_fill_insert@?$vector@UBfmePod44@@V?$allocator@UBfmePod44@@@_STL@@@_STL@@QAEXPAUBfmePod:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> void vector<BfmePod44, allocator<BfmePod44> >::_M_fill_insert(BfmePod44 *, size_t, const BfmePod44 &); }
struct BfmePod44 { int a[11]; };
// Emit the rowed allocation/copy member without unrelated whole-class copies.
template BfmePod44 *_STL::vector<BfmePod44, _STL::allocator<BfmePod44> >::_M_allocate_and_copy<const BfmePod44 *>(unsigned int, const BfmePod44 *, const BfmePod44 *);
template BfmePod44 *_STL::vector<BfmePod44, _STL::allocator<BfmePod44> >::_M_allocate_and_copy<BfmePod44 *>(unsigned int, BfmePod44 *, BfmePod44 *);
