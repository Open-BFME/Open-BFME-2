// cl: /Ireference/shims/bfmerendobj /O1 /Oy- /arch:SSE2 /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep

// TriClass::Compute_Normal is inline in the reference WWMath header.  Keep
// this small TU at the retail size-optimized settings and take its address so
// MSVC emits the COMDAT body for the ledger's unexported collision helper.
#include "rendobj.h"
#include "tri.h"

#pragma optimize("s", on)
#pragma optimize("y", off)
#pragma auto_inline(off)

void (TriClass::*kTriComputeNormal)() = &TriClass::Compute_Normal;
