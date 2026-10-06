// cl: /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad
// VectorClass<Vector3>::Resize, native [0x000F0BF1,0x000F0CD4), RET8.
// Semantic source: Open-BFME-1 6583b3c1ff21db4a561285717028fdafc780b7db,
// game/Libraries/Source/WWVegas/WWLib/vector.h and WWMath/vector3.h.
//
// The served Curve3DClass::KeyClass instantiation has a 16-byte stride and
// cannot own this 12-byte body. The matched pointgr vertex-pool sizing
// helper at 0x0017F150 calls here at 0x0017F183 with VertexLoc (VA
// 0x00DF708C), the VectorClass<Vector3> identified by its source declaration.
// The target constructor at
// 0x000F0D2F independently installs its six-slot vtable VA 0x00BCEFAC;
// slot +8 points here, and the array iterator receives stride 12 and the
// empty Vector3 constructor. Other three-float types may share the body.
//
// Vector3's memberwise assignment reproduces the three scalar copies;
// the implicit TCBClass assignment instead emits a block copy. The target
// omits the exception-state reset after array construction: declaring array
// delete nonthrowing, as in the existing scalar VectorClass resize unit,
// removes that four-byte difference without changing the allocation logic.

#include "vector3.h"
void __cdecl operator delete[](void *) throw();
#include "vector.h"

template bool VectorClass<Vector3>::Resize(int, const Vector3 *);
