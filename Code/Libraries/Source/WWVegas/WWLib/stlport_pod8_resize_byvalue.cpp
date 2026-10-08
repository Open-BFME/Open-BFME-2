// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
//
// Pod8 vector resize with the fill value taken BY VALUE (retail 0x005FF96A,
// 63B, ends ret 0xC). STLport 4.5.3 only declares the const-ref resize, so
// this TU derives from the real _STL::vector<BfmePod8> instantiation (same
// headers and flags as stlport_pod_vector_malloc_bodies.cpp, whose prologue
// already matches retail through the erase call) and adds the by-value
// overload retail was built with. The by-value parameter is what emits
// retail's lea edi,[esp+0x10] plus push edi argument forwarding. Callees
// resolve to the rowed 2-argument erase (0x003FA4DB) and _M_fill_insert
// (0x000B02B6).
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>

#include "../../../../GameEngine/Source/Common/BattlePromptArmyPanelClipImplView.h"

void BfmePod8Vector::resize(unsigned int n, BfmePod8 x)
{
	if (n < size())
		erase(begin() + n, end());
	else
		_M_fill_insert(end(), n - size(), x);
}

// ?resize@BfmePod8Vector@@QAEXI@Z @ 0x000B0857 (23B). One-argument resize
// forwarding an indeterminate default pod to the rowed by-value resize
// above; the two filler pushes carry the incoming ecx. Callers 0x000B0DA8
// and 0x000B0F82.
void BfmePod8Vector::resize(unsigned int n)
{
	BfmePod8 x;
	resize(n, x);
}
