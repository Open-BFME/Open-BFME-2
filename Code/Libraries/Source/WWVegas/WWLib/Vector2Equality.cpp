// cl: /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// ??8?$VectorClass@VVector2@@@@UBE_NABV0@@Z, retail 0x0017ECE0, 116 bytes:
// WWLib VectorClass<Vector2>::operator==, the slot between the rowed
// ??_G?$VectorClass@VVector2@@@@ (0x0017F100) and Resize (0x0017ED60) in the
// table Vector2's constructor installs. Element compares are SSE (ucomiss),
// so this instantiation needs /arch:SSE beside Vector2Resize.cpp's /G7.

// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
#include "../../../../GameEngine/Include/Common/BfmeVciAnchorElem.h"
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
// bfmeHeadersForSize: the headers' out-of-line inline copies that retail keeps are
// the size-optimised bodies (decalsys.cpp pattern); the rows below keep the unit's flags.
#pragma optimize("s", on)
#include "always.h"
#include "vector.h"
#include "vector2.h"
#pragma optimize("", on)

// BFME 2's element test is !(a == b) where WWLib's template has a != b:
// retail ANDs the two component equalities (jp, test) instead of ORing the
// inequalities (jnp, or), so the member is specialized here.
template<>
bool VectorClass<Vector2>::operator == (VectorClass<Vector2> const & vec) const
{
	if (VectorMax == vec.Length()) {
		for (int index = 0; index < VectorMax; index++) {
			if (!(Vector[index] == vec[index])) {
				return(false);
			}
		}
		return(true);
	}
	return(false);
}
