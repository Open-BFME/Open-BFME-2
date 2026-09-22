// ?Resize@?$VectorClass@VVector4@@@@UAE_NHPBVVector4@@@Z
// partial score=0.9927272727 date=2026-09-23
// cl: /G7 /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// BFME1 VectorClassResizeNothrowDelete.cpp donor; name linked by target ctor.
// BFME2 Vector4 ctor 0x001792F0 installs vtable VA0x00BD4EB4; Resize slot
// points to 0x001793A0 (550B). Two independent stack reloads remain reversed.

void __cdecl operator delete[](void *) throw();

#include "always.h"
#include "vector.h"
#include "vector2.h"
#include "vector3.h"
#include "vector4.h"

template bool VectorClass<Vector4>::Resize(int, Vector4 const *);
