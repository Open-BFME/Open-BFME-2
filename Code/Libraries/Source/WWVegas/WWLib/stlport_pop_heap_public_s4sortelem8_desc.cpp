// cl: /DNDEBUG /MD /EHsc C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport

// _STL::pop_heap<S4SortElem8 *, S4Cmp00625C10>, retail 0x00626110, 57 bytes.
// Descending public pop: the vendored chain inlines aux plus worker, so the
// body lifts *(last-1), moves *first down, and calls the matched
// __adjust_heap at 0x00625CF0 directly (comp stays in its third-parameter
// home, no new pins).  Twin of the ascending pop at 0x006260D0.

#include <algorithm>

#include "S4SortElem8.h"

#include "S4Cmp00625C10.h"

namespace _STL
{

template void pop_heap<S4SortElem8 *, S4Cmp00625C10>(
	S4SortElem8 *, S4SortElem8 *, S4Cmp00625C10);

}
// bfme link decl-only begin
namespace _STL { template <> void __adjust_heap<S4SortElem8 *,int,S4SortElem8,S4Cmp00625C10>(S4SortElem8 *,int,int,S4SortElem8,S4Cmp00625C10); }
// bfme link decl-only end
