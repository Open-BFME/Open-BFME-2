// cl: /O2 /G6 /MD /D_CRTIMP= /DNDEBUG
//
// View::worldToScreen, retail 0x00050F29 (24 bytes, ret 8).
// Donor: ZH GameEngine/Include/GameClient/View.h, where it is inline:
//   return worldToScreenTriReturn( w, s ) == WTS_INSIDE_FRUSTUM;
// Target evidence: the body calls slot 88 (+0x160) of the receiver with both
// arguments and returns result == 0 (neg/sbb/inc). Slot 88 of W3DView's
// primary vftable 0x00BC7568 is 0x0008619F, the rowed
// W3DView::worldToScreenTriReturn. Earlier slots are opaque in this view.
struct Coord3D;
struct ICoord2D;

#include "../../Include/GameClient/View.h"

// ?worldToScreen@View@@QAE_NPBUCoord3D@@PAUICoord2D@@@Z
// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline bool View::worldToScreen( const Coord3D *w, ICoord2D *s )
{
	return worldToScreenTriReturn( w, s ) == WTS_INSIDE_FRUSTUM;
}

// ?bfmeAnchorViewWorldToScreen absent-from-retail
bool bfmeAnchorViewWorldToScreen(View *view, const Coord3D *w, ICoord2D *s)
{
	return view->worldToScreen(w, s);
}

