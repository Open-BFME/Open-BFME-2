// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport

// _STL::__pop_heap_aux<S4SortElem8 *, S4SortElem8, S4Cmp00625C10>,
// retail 0x00626050, 57 bytes.  Descending pop auxiliary: the vendored aux
// inlines the six-argument worker, so the body lifts *(last-1), moves *first
// down, and calls the matched __adjust_heap at 0x00625CF0 directly (the
// fourth parameter slot carries comp, no new pins).  Twin of the ascending
// aux at 0x00626010.

#include <algorithm>

#include "S4SortElem8.h"

#include "S4Cmp00625C10.h"

namespace _STL
{

template void __pop_heap_aux<S4SortElem8 *, S4SortElem8, S4Cmp00625C10>(
	S4SortElem8 *, S4SortElem8 *, S4SortElem8 *, S4Cmp00625C10);

}
// bfme link decl-only begin
namespace _STL { template <> void __adjust_heap<S4SortElem8 *,int,S4SortElem8,S4Cmp00625C10>(S4SortElem8 *,int,int,S4SortElem8,S4Cmp00625C10); }
// bfme link decl-only end
