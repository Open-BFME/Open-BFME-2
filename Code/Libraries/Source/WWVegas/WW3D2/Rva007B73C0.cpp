// cl: /O2 /G7 /Ob2 /MD /DNDEBUG /Ireference/shims/bfmevector /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
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
#include "vector3.h"
#include "vector.h"
// bfme link decl-only begin
template <> bool VectorClass<Vector3>::Resize(int, Vector3 const *);
extern template bool VectorClass<Vector3>::operator == (VectorClass<Vector3> const &) const;
extern template int VectorClass<Vector3>::ID(Vector3 const &);
template <> int VectorClass<Vector3>::ID(Vector3 const *);
// bfme link decl-only end
class PointGroupClass {friend void Rva007B73C0(); static VectorClass<Vector3> transformed_loc;};
// Native global9F709C is PointGroupClass::transformed_loc, read and resized by17E920.
// Native complete7B73C0..7B73FB restores VectorClass<Vector3> vptr and clears owned storage.
void Rva007B73C0() { PointGroupClass::transformed_loc.~VectorClass<Vector3>(); }
