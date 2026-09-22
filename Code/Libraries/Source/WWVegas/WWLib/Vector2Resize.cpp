// cl: /G7 /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// Donor: BFME1 VectorClassResizeNothrowDelete.cpp and WWLib vector.h.
// Target: Vector2 ctor 0x001797E0 installs the vtable containing this Resize;
// its 481-byte body matches with /G7 and nonthrowing array delete.

void __cdecl operator delete[](void *) throw();

#include "always.h"
#include "vector.h"
#include "vector2.h"

template bool VectorClass<Vector2>::Resize(int, Vector2 const *);
