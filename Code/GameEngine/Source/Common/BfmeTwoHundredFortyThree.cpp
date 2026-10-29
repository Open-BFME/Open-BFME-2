// cl: /O1 /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport46
// ??$__copy@PAUCoord3D@@PAU1@H@_STL@@YAPAUCoord3D@@PAU1@00ABUrandom_access_iterator_tag@0@PAH@Z
// @0x002C97AC 60B: STLport 4.5.3 random-access __copy over Coord3D (12-byte
// elements: the count is (last-first)/12 by idiv; three dword moves per element).
// Target evidence: retail callers (e.g. 0x002CA86E) push five arguments
// (first, last, result, tag, distance*), the __copy signature, not the three of
// the BFME 1 donor's bfmeCopyOA name this row carried before; the existing
// symbols.csv pin already binds this name here. The body is STLport's loop with
// the element assignment spelled member by member, as the retail TU's Coord3D
// view assigned (an implicit struct copy compiles to movsd under /O1).
#include <stl/_algobase.h>
#include "../../../Libraries/Include/Lib/Coord3D.h"

namespace _STL {
template <>
Coord3D *__copy<Coord3D *, Coord3D *, int>(Coord3D *__first, Coord3D *__last, Coord3D *__result,
                                           const random_access_iterator_tag &, int *)
{
	for (int __n = __last - __first; __n > 0; --__n) {
		__result->x = __first->x;
		__result->y = __first->y;
		__result->z = __first->z;
		++__first;
		++__result;
	}
	return __result;
}
}
