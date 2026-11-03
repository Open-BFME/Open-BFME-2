// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport

// _STL::__introsort_loop<S4SortElem8 *, S4SortElem8, int, S4Cmp00625C10>,
// retail 0x00626860, 224 bytes.  Descending twin: inline median, the matched
// __unguarded_partition at 0x00625E30, the matched __partial_sort at
// 0x006265B0, self-recursion.  All callees are matched rows (no new pins).

#include <algorithm>

#include "S4SortElem8.h"

#include "S4Cmp00625C10.h"

namespace _STL
{

template<> __declspec(dllimport) __forceinline void iter_swap<S4SortElem8*,S4SortElem8*>(S4SortElem8* left,S4SortElem8* right) {
 S4SortElem8 temporary=*left; *left=*right; *right=temporary;
}

template void __introsort_loop<S4SortElem8 *, S4SortElem8, int,
	S4Cmp00625C10>(S4SortElem8 *, S4SortElem8 *, S4SortElem8 *, int,
	S4Cmp00625C10);

}
