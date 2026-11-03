// cl: /DNDEBUG /MD /EHsc C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport

// _STL::sort_heap<S4SortElem8 *, S4Cmp00625BB0>, retail 0x00626360, 89 bytes.
// Ascending drain verbatim: inline swap plus a direct call into the matched
// __adjust_heap at 0x00625C70 on every pass (no new pins).  The vendored
// pop_heap inlines here; the out-of-line pop_heap bodies at 0x00626010+
// have no callers and stay unclaimed.

#include <algorithm>

#include "S4SortElem8.h"

#include "S4Cmp00625BB0.h"

namespace _STL
{

template void sort_heap<S4SortElem8 *, S4Cmp00625BB0>(
	S4SortElem8 *, S4SortElem8 *, S4Cmp00625BB0);

}
// bfme link decl-only begin
namespace _STL { template <> void __adjust_heap<S4SortElem8 *,int,S4SortElem8,S4Cmp00625BB0>(S4SortElem8 *,int,int,S4SortElem8,S4Cmp00625BB0); }
// bfme link decl-only end
