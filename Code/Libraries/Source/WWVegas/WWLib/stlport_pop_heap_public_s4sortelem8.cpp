// cl: /DNDEBUG /MD /EHsc C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport

// _STL::pop_heap<S4SortElem8 *, S4Cmp00625BB0>, retail 0x006260D0, 57 bytes.
// Ascending public pop: the vendored chain inlines aux plus worker, so the
// body lifts *(last-1), moves *first down, and calls the matched
// __adjust_heap at 0x00625C70 directly (comp stays in its third-parameter
// home, no new pins).  Twin of the descending pop at 0x00626110.

#include <algorithm>

#include "S4SortElem8.h"

struct S4Cmp00625BB0
{
	void *m_bfmeState;

	bool operator()(const S4SortElem8 &a, const S4SortElem8 &b) const
	{
		return a.m_bfmeKey < b.m_bfmeKey;
	}
};

namespace _STL
{

template void pop_heap<S4SortElem8 *, S4Cmp00625BB0>(
	S4SortElem8 *, S4SortElem8 *, S4Cmp00625BB0);

}
// bfme link decl-only begin
namespace _STL { template <> void __adjust_heap<S4SortElem8 *,int,S4SortElem8,S4Cmp00625BB0>(S4SortElem8 *,int,int,S4SortElem8,S4Cmp00625BB0); }
// bfme link decl-only end
