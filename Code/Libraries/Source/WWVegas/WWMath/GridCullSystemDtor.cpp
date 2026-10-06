// cl: /Ireference/shims/bfmerendobj /Ob2 /DNDEBUG /MD /GX- /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)

// GridCullSystemClass::~GridCullSystemClass on its own: retail carries no
// exception frame for it (delete of the cell pointer array plus the trivial
// base dtor cannot throw), while gridcull.cpp as a whole builds with the
// default EH switch on.  Same body tokens as gridcull.cpp; the base dtor
// tail-jump target 0x00724560 is pinned from the retail displacement.
#include "rendobj.h"	// the bfmerendobj shim has to win the include guard
#include "gridcull.h"

__declspec(noinline) GridCullSystemClass::~GridCullSystemClass(void)
{
	if (Cells != NULL) {
		delete Cells;
		Cells = NULL;
	}
}
