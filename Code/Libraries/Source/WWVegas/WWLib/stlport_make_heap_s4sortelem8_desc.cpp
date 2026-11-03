// cl: /DNDEBUG /MD /EHsc C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport

// _STL::__make_heap<S4SortElem8 *, S4Cmp00625C10, S4SortElem8, int>,
// retail 0x00625FA0, 103 bytes.  Descending twin: same parent schedule,
// each level calls the matched __adjust_heap at 0x00625CF0 (no new pins).

#include <algorithm>

#include "S4SortElem8.h"

struct S4Cmp00625C10
{
	void *m_bfmeState;

	bool operator()(const S4SortElem8 &a, const S4SortElem8 &b) const
	{
		return a.m_bfmeKey > b.m_bfmeKey;
	}
};

namespace _STL
{

template void __make_heap<S4SortElem8 *, S4Cmp00625C10, S4SortElem8, int>(
	S4SortElem8 *, S4SortElem8 *, S4Cmp00625C10, S4SortElem8 *, int *);

}
