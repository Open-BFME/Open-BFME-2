// cl: /G7 /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// Donor: BFME1 VectorClassResizeNothrowDelete.cpp and WWLib vector.h.
// Target: Vector2 ctor 0x001797E0 installs the vtable containing this Resize;
// its 481-byte body matches with /G7 and nonthrowing array delete. The
// Vector4 instantiation (pinned 0x001793A0, called at 0x0017F19D to grow the
// point-group VertexDiffuse array) matches only instantiated after Vector2's:
// on its own two loads in the copy-back loop swap.
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

void __cdecl operator delete[](void *) throw();

#include "always.h"
#include "vector.h"
#include "vector2.h"
#include "vector4.h"

template bool VectorClass<Vector2>::Resize(int, Vector2 const *);
template bool VectorClass<Vector4>::Resize(int, Vector4 const *);
