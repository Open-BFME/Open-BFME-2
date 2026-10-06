// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ??$__uninitialized_copy@PBV?$vector@IV?$allocator@I@_STL@@@_STL@@PAV12@@_STL@@YAPAV?$vector@IV?$allocator@I@_STL@@@0@PBV10@0PAV10@ABU__false_type@0@@Z
// retail 0x00460F45 38 bytes. STLport __uninitialized_copy for 12-byte
// retail 0x00460F45 38 bytes. Stride-0xC sibling of the rowed AsciiString
// copy at 0x0002C4B2 and E8/E16 38B rows. Calls the vector _Construct dupe
// at 0x00460F18 (true name rowed at 0x00796E8). Declared-only _Construct
// specialization keeps the call out-of-line; explicit instantiation of the
// real __uninitialized_copy emits the 38B push-esi/edi loop.

#include <vector>
#include <memory>

typedef _STL::vector<unsigned int, _STL::allocator<unsigned int> > VecUint;

namespace _STL
{
template <> void _Construct<VecUint, VecUint>(VecUint *, const VecUint &);
}

template VecUint *_STL::__uninitialized_copy(const VecUint *, const VecUint *, VecUint *, const _STL::__false_type &);
