// cl: /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport46
//
// ??$__uninitialized_copy@PAUCoord3D@@PAU1@@_STL@@YAPAUCoord3D@@PAU1@00ABU__false_type@0@@Z @0x00346C2D 38B: STLport __uninitialized_copy for 12-byte Coord3D.
// Retail calls the pinned Coord3D _Construct at 0x002CA82C (UCoord3D pin thermodynamics via list node 0x27F4A9) with stride 0x0C adds.
// Callers 0x000E016A 0x0034C0D0 0x002CDF8A pass (first last result false_type) with add esp 0x10 and idiv/imul 0x0C counts; returns result end.
// Dedicated TU so the _Construct stays an out-of-line call (specialization, no body) like WeaponTemplateSetUninitializedCopy 0x004AE927.
// _STLP_NO_EXCEPTIONS drops STLport's try/unwind around the loop: retail has no EH frame here.
#include "../../../Libraries/Include/Lib/Coord3D.h"
#include <memory>

// The element construction is the out-of-line copy at 0x002CA82C.
namespace _STL { template <> void _Construct<Coord3D, Coord3D>(Coord3D *, const Coord3D &); }

template Coord3D *_STL::__uninitialized_copy(Coord3D *, Coord3D *, Coord3D *, const _STL::__false_type &);
