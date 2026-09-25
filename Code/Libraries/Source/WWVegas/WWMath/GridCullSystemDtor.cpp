// cl: /Ireference/shims/bfmerendobj /Ob2 /arch:SSE /G7 /DNDEBUG /MD /GX- /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep

// GridCullSystemClass::~GridCullSystemClass on its own: retail carries no
// exception frame for it (delete of the cell pointer array plus the trivial
// base dtor cannot throw), while gridcull.cpp as a whole builds with the
// default EH switch on.  Same body tokens as gridcull.cpp; the base dtor
// tail-jump target 0x00724560 is pinned from the retail displacement.
#include "rendobj.h"	// the bfmerendobj shim has to win the include guard
#include "gridcull.h"

GridCullSystemClass::~GridCullSystemClass(void)
{
	if (Cells != NULL) {
		delete Cells;
		Cells = NULL;
	}
}
