// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport

// _STL::__make_heap<S4SortElem8 *, S4Cmp00625BB0, S4SortElem8, int>,
// retail 0x00625F30, 103 bytes.  Ascending heap build verbatim (BFME1
// S4StlSortHelpers shape): parent starts at (len-2)/2 and each level calls
// the matched __adjust_heap at 0x00625C70 (no new pins).  Explicit worker
// instantiation; the public three-argument wrappers live at 0x00626090+.

#include <algorithm>

#include "S4SortElem8.h"

#include "S4Cmp00625BB0.h"

namespace _STL
{

template void __make_heap<S4SortElem8 *, S4Cmp00625BB0, S4SortElem8, int>(
	S4SortElem8 *, S4SortElem8 *, S4Cmp00625BB0, S4SortElem8 *, int *);

}
