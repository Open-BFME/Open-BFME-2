// cl: /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport46
//
// ??$__uninitialized_fill_n@PAUCoord3D@@IU1@@_STL@@YAPAUCoord3D@@PAU1@IABU1@ABU__false_type@0@@Z @0x002CA849 37B: STLport __uninitialized_fill_n for 12-byte Coord3D.
// Retail null-guards the count then constructs each element out-of-line through the pinned Coord3D _Construct at 0x002CA82C with stride 0x0C.
// Callers 0x000CA1D3 (27B wrapper with false_type tag at ebp-1) and 0x002CDF8A (deque overflow fill path with tag at ebp+0x1B) pass (first n value tag) with add esp 0x10; returns the end pointer.
// _STLP_NO_EXCEPTIONS drops STLport's try/unwind around the loop: retail has no EH frame here.
#include "../../../Libraries/Include/Lib/Coord3D.h"
#include <memory>

// The element construction is the out-of-line copy at 0x002CA82C.
namespace _STL { template <> void _Construct<Coord3D, Coord3D>(Coord3D *, const Coord3D &); }

template Coord3D *_STL::__uninitialized_fill_n(Coord3D *, unsigned int, const Coord3D &, const _STL::__false_type &);
