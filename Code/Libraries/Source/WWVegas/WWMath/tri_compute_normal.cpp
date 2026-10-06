// cl: /Ireference/shims/bfmerendobj /Oy- /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
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

// TriClass::Compute_Normal is inline in the reference WWMath header.  Keep
// this small TU at the retail size-optimized settings and take its address so
// MSVC emits the COMDAT body for the ledger's unexported collision helper.
// The TU needs /Oy- for its own rows, but that forces an EBP frame into every
// out-of-line Vector3 helper it also emits, while the kept copies elsewhere
// are frameless. Parse vector3.h first with FPO on so those helpers emit the
// kept frameless form; TriClass::Compute_Normal below is still parsed with the
// TU flags and keeps its frame.
#pragma optimize("y", on)
#include "vector3.h"
#pragma optimize("", on)
#include "rendobj.h"
#include "tri.h"

#pragma optimize("s", on)
#pragma optimize("y", off)
#pragma auto_inline(off)

void (TriClass::*kTriComputeNormal)() = &TriClass::Compute_Normal;
