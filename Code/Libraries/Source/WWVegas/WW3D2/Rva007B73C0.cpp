// cl: /O2 /G7 /Ob2 /MD /DNDEBUG /Ireference/shims/bfmevector /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
void __cdecl operator delete[](void *) throw();
#include "vector3.h"
#include "vector.h"
class PointGroupClass {friend void Rva007B73C0(); static VectorClass<Vector3> transformed_loc;};
// Native global9F709C is PointGroupClass::transformed_loc, read and resized by17E920.
// Native complete7B73C0..7B73FB restores VectorClass<Vector3> vptr and clears owned storage.
void Rva007B73C0() { PointGroupClass::transformed_loc.~VectorClass<Vector3>(); }
