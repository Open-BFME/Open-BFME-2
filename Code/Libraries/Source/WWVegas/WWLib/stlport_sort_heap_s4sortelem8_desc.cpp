// cl: /DNDEBUG /MD /EHsc C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport

// _STL::sort_heap<S4SortElem8 *, S4Cmp00625C10>, retail 0x006263C0, 89 bytes.
// Descending twin: inline swap plus a direct call into the matched
// __adjust_heap at 0x00625CF0 (no new pins).

#include <algorithm>

#include "S4SortElem8.h"

#include "S4Cmp00625C10.h"

namespace _STL
{

template <> void __adjust_heap<S4SortElem8 *, int, S4SortElem8, S4Cmp00625C10>(
	S4SortElem8 *, int, int, S4SortElem8, S4Cmp00625C10);

template void sort_heap<S4SortElem8 *, S4Cmp00625C10>(
	S4SortElem8 *, S4SortElem8 *, S4Cmp00625C10);

}
